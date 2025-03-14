#include "k2EngineLowPreCompile.h"
#include "LevelRender.h"

namespace nsK2EngineLow {

	//デストラクタ
	LevelRender::~LevelRender()
	{

	}

	//初期化
	void LevelRender::Init(
		const char* filePath,
		std::function<bool(LevelObjectData_Render& objData)> hookFunc)
	{
		//tklファイルをロードする
		m_tklFile.Load(filePath);

		MatrixTklToLevel();

		//ルートボーンは要らない為、iを1から始めることで除外できる。
		for (int i = 1; i < m_boneList.size(); i++){
			auto bone = m_boneList[i].get();
			if (bone->GetParentBoneNo() == 0)
			{
				
				//マップチップを作成する
				//行列からポジションを作成
				LevelObjectData_Render levelObjData;
				bone->CalcWorldTRS(levelObjData.m_position, levelObjData.m_rotation,
					levelObjData.m_scalse);

				//ZupとYupの変更
				float fix = levelObjData.m_position.y;
				levelObjData.m_position.y = levelObjData.m_position.z;
				levelObjData.m_position.z = -fix;

				fix = levelObjData.m_rotation.y;
				levelObjData.m_rotation.y = levelObjData.m_rotation.z;
				levelObjData.m_rotation.z = -fix;

				std::swap(levelObjData.m_scalse.y, levelObjData.m_scalse.z);
				//Zup⇔Yup終わり。

				levelObjData.name = m_boneList[i]->GetName();
				std::wstring wstr_name = levelObjData.name;
				//@があるかどうかを検索
				int pos = static_cast<int>(wstr_name.find('@'));
				//@が存在していれば、@後の数字を取得する
				if (pos != std::wstring::npos)
				{
					std::wstring wstr_number = wstr_name.substr(static_cast<size_t>(pos) + 1);
					//wchar型をint型に変換
					levelObjData.number = std::stoi(wstr_number.c_str());
				}
				//パスの作成
				wchar_t filePath[256];
				swprintf_s(filePath, L"Assets/modelData/%s.tkm", levelObjData.name);
				//マルチバイトに変換 wchar→char
				//ベースの文字列。
				size_t origsize = wcslen(filePath) + 1;
				//変換した文字列
				size_t convertedChars = 0;
				//マルチバイト格納用変数
				char strCon[] = "";
				//サイズ
				size_t strConSize = (strlen(strCon) + 1) * 2;
				//返還後のサイズ
				const size_t newsize = origsize * 2;
				//連結後のサイズ。
				char* cFilePath = new char[newsize + strConSize];
				//マルチバイトに変換する(入りきらないものは切り捨てる)
				wcstombs_s(&convertedChars, cFilePath, newsize, filePath, _TRUNCATE);
				//マルチバイト文字列の連結
				_mbscat_s((unsigned char*)cFilePath, newsize + strConSize, (unsigned char*)strCon);

				//Hookが登録済みならばマップチップは作成不要
				//false のままなら作成する。
				bool isHooked = false;
				//hookFuncになにも入っていない＝Sobjectには何もない。
				if (hookFunc != nullptr) {
					isHooked = hookFunc(levelObjData);
				}
			}
		}

		//マップチップ作成機能は未実装

	}

	void LevelRender::MatrixTklToLevel()
	{
		m_tklFile.QuaryObject([&](TklFile::SObject& tklObj) {
			//コピー
			//バインドポーズ
			Matrix bindPoseMatrix;
			memcpy(bindPoseMatrix.m[0], &tklObj.bindPose[0], sizeof(tklObj.bindPose[0]));
			memcpy(bindPoseMatrix.m[1], &tklObj.bindPose[1], sizeof(tklObj.bindPose[1]));
			memcpy(bindPoseMatrix.m[2], &tklObj.bindPose[2], sizeof(tklObj.bindPose[2]));
			memcpy(bindPoseMatrix.m[3], &tklObj.bindPose[3], sizeof(tklObj.bindPose[3]));
			bindPoseMatrix.m[0][3] = 0.0f;
			bindPoseMatrix.m[1][3] = 0.0f;
			bindPoseMatrix.m[2][3] = 0.0f;
			bindPoseMatrix.m[3][3] = 1.0f;

			//バインドポーズの逆行列
			//列3はvector3変換の際に不要なので初期化
			Matrix invBindPoseMatrix;
			memcpy(invBindPoseMatrix.m[0], &tklObj.invBindPose[0], sizeof(tklObj.invBindPose[0]));
			memcpy(invBindPoseMatrix.m[1], &tklObj.invBindPose[1], sizeof(tklObj.invBindPose[1]));
			memcpy(invBindPoseMatrix.m[2], &tklObj.invBindPose[2], sizeof(tklObj.invBindPose[2]));
			memcpy(invBindPoseMatrix.m[3], &tklObj.invBindPose[3], sizeof(tklObj.invBindPose[3]));
			invBindPoseMatrix.m[0][3] = 0.0f;
			invBindPoseMatrix.m[1][3] = 0.0f;
			invBindPoseMatrix.m[2][3] = 0.0f;
			invBindPoseMatrix.m[3][3] = 1.0f;

			wchar_t boneName[256];

			mbstowcs(boneName, tklObj.name.get(), 256);
			BonePtr bone = std::make_unique<Bone>(
				boneName,
				bindPoseMatrix,
				invBindPoseMatrix,
				tklObj.parentNo,
				tklObj.no
			);
			//ボーン積む
			m_boneList.push_back(std::move(bone));
			//コピー終了
		});
	}

	void LevelRender::Update()
	{

	}

	void LevelRender::Draw(RenderContext& rc)
	{

	}
}

