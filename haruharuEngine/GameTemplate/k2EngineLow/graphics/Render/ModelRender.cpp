#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"

namespace nsK2EngineLow {


	//コンストラクタ
	ModelRender::ModelRender()
	{

	}

	//デストラクタ
	ModelRender::~ModelRender()
	{

	}

	//初期化処理
	void ModelRender::Init(
		const char* tkmfilePath,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis,
		bool isRecieveShadow
	)
	{
		//スケルトンの初期化
		InitSkeleton(tkmfilePath);

		//アニメーションの初期化
		InitAnimation(animationClips, numAnimationClips);

		// GBuffer描画用のモデルを初期化。
		// Gbufferは作りかけ
		//InitModelOnRenderGBuffer(*g_renderingEngine,tkmfilePath,enModelUpAxis,isRecieveShadow);

		//基本のモデル初期化
		InitNormalModel(tkmfilePath, animationClips, numAnimationClips, enModelUpAxis, isRecieveShadow);

		//シャドウマップ描画用モデルの初期化
		InitShadowModel(tkmfilePath, enModelUpAxis);
	}

	//GBuffer描画用のモデルを初期化
	void ModelRender::InitModelOnRenderGBuffer(
		RenderingEngine& renderingEngine,
		const char* tkmFilePath,
		EnModelUpAxis enModelUpAxis,
		bool isShadowReciever
	)
	{
		//基本モデルの初期化構造体を作成
		ModelInitData initData;
		initData.m_fxFilePath = "";
		
	}

	//基本モデルの初期化
	void ModelRender::InitNormalModel(
		const char* tkmfilePath,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis,
		bool isRecieveShadow
	)
	{
		//基本モデルの初期化構造体を作成
		ModelInitData initData;

		//ファイルパスを登録
		initData.m_tkmFilePath = tkmfilePath;

		if (isRecieveShadow)
		{
			initData.m_fxFilePath = "Assets/shader/haruharuShadowReceiverModel.fx";

			Camera lightCamera;

			lightCamera.SetAspectOneFlag(true);

			lightCamera.SetViewAngle(Math::DegToRad(80.0f));

			//カメラの位置を設定
			lightCamera.SetPosition(-2000.0f, 2000.0f, 2000.0f);

			// カメラの注視点を設定。これがライトが照らしている場所
			lightCamera.SetTarget(0, 0, 0);

			// 上方向を設定。今回はライトが真下を向いているので、X方向を上にしている
			//lightCamera.SetUp(1, 0, 0);

			//ライトビュープロジェクション行列を計算している
			lightCamera.Update();

			m_shadowLigData.m_light = *g_sceneLight->GetLightData();
			m_shadowLigData.m_mt = lightCamera.GetViewProjectionMatrix();

			initData.m_expandConstantBuffer = &m_shadowLigData;
			initData.m_expandConstantBufferSize = sizeof(m_shadowLigData);

			//シャドウマップを拡張SRVに設定する
			initData.m_expandShaderResoruceView[0] = &(g_renderingEngine
				->GetShadowMapRenderTarget()->GetRenderTargetTexture());
		}
		else
		{
			//描画シェーダーを登録
			initData.m_fxFilePath = "Assets/shader/haruharuModel.fx";

			//ライトの情報を登録
			initData.m_expandConstantBuffer = g_sceneLight->GetLightData();
			initData.m_expandConstantBufferSize = sizeof(Light);


		}

		//ノンスキンメッシュ用の頂点シェーダーのエントリーポイントを指定する。
		initData.m_vsEntryPointFunc = "VSMain";

		//スキンメッシュ用の頂点シェーダーのエントリーポイントを指定。
		initData.m_vsSkinEntryPointFunc = "VSSkinMain";

		//スケルトンが初期化されていたら
		if (m_skeleton.IsInited())
		{
			initData.m_skeleton = &m_skeleton;
		}

		//モデルの上方向情報
		initData.m_modelUpAxis = enModelUpAxis;

		//作成した初期化データをもとにモデルを初期化
		m_model.Init(initData);
	}

	//シャドウマップに表示するモデルの作成
	void ModelRender::InitShadowModel(const char* tkmFilePath, EnModelUpAxis modelUpAxis)
	{
		ModelInitData initData;
		initData.m_tkmFilePath = tkmFilePath;
		initData.m_modelUpAxis = modelUpAxis;

		//ノンスキンメッシュ用の頂点シェーダーのエントリーポイントを指定する。
		//initData.m_vsEntryPointFunc = "VSMain";
		//スキンメッシュ用の頂点シェーダーのエントリーポイントを指定。
		//initData.m_vsSkinEntryPointFunc = "VSSkinMain";

		if (m_animationClips != nullptr)
		{
			//スケルトン指定
			initData.m_skeleton = &m_skeleton;
		}

		initData.m_fxFilePath = "Assets/shader/haruharuDrawShadowMap.fx";

		//initData.m_colorBufferFormat[0] = DXGI_FORMAT_R32_FLOAT;デプスシャドウ用の設定

		//ノンスキンメッシュ用の頂点シェーダーのエントリーポイントを指定する
		initData.m_vsEntryPointFunc = "VSMain";
		//スキンメッシュ用の頂点シェーダーのエントリーポイントを指定する
		initData.m_vsSkinEntryPointFunc = "VSSkinMain";

		m_shadowModel.Init(initData);
	}

	//スケルトンの登録処理
	//tkmファイルのパスの.tkmの部分を.tksにして読み込む事で
	//いちいちtkmファイルパスとtksファイルパス両方を入力する必要が無くなる
	//代わりにtkmファイルがあるファイルにtksファイルがないと読み込めない。
	void ModelRender::InitSkeleton(const char* tkmFilePath)
	{
		//スケルトンのデータを読み込み。
		std::string skeletonFilePath = tkmFilePath;
		int pos = (int)skeletonFilePath.find(".tkm");
		skeletonFilePath.replace(pos, 4, ".tks");
		m_skeleton.Init(skeletonFilePath.c_str());
	}

	//アニメーションの登録処理
	void ModelRender::InitAnimation(AnimationClip* animationClips, int numAnimationClips)
	{
		m_animationClips = animationClips;
		m_numAnimationClips = numAnimationClips;
		if (m_animationClips != nullptr)
		{
			m_animation.Init(
				m_skeleton,
				m_animationClips,
				numAnimationClips //これなんでm_numAnimationClipsじゃないんだろ
			);
		}
	}

	//モデルレンダーの更新処理
	void ModelRender::Update()
	{
		m_shadowLigData.m_light = *g_sceneLight->GetLightData();
		//ワールド行列更新
		m_model.UpdateWorldMatrix(m_position,m_rotation, m_scale);

		m_shadowModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);

		//スケルトンが初期化済みの場合、スケルトンの更新
		if (m_skeleton.IsInited())
		{
			m_skeleton.Update(m_model.GetWorldMatrix());
		}

		//アニメーションを進める
		m_animation.Progress(g_gameTime->GetFrameDeltaTime() * m_animationSpeed);
	}

	//描画処理
	void ModelRender::Draw(RenderContext& rc)
	{
		g_renderingEngine->AddRenderObject(this);
	}

	//3Dモデルの描画処理
	void ModelRender::OnRenderModel(RenderContext& rc)
	{
		m_model.Draw(rc);
	}

	void ModelRender::OnRenderToGBuffer(RenderContext& rc)
	{
		//初期化されていたら
		if (m_gBufferModel.IsInited()){
			//描画
			m_gBufferModel.Draw(rc, 1);
		}
	}

	//影の描画処理
	void ModelRender::OnRenderShadowMap(RenderContext& rc, const Matrix& lvpMatrix)
	{
		if (m_isShadowChaster)
		{
			m_shadowModel.Draw(
				rc,
				g_matIdentity,
				lvpMatrix,
				1
			);
		}
	}
}