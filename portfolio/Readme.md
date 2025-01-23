# SALVAGE
> ### 河原電子ビジネス　ゲームクリエイター科
> ### 氏名：武田　悠世 （たけだ　はるせ）



# 目次
- [SALVAGE](#salvage)
- [目次](#目次)
  - [作品概要](#作品概要)
- [作成したソースコード](#作成したソースコード)
- [◇ゲーム説明](#ゲーム説明)
- [◇操作説明](#操作説明)
- [◇技術紹介](#技術紹介)
  - [◇ステートマシン](#ステートマシン)
  - [◇集団制御(メタＡＩ)](#集団制御メタａｉ)
  - [川瀬式Bloomフィルターの実装](#川瀬式bloomフィルターの実装)
  - [◇デバッグ機能](#デバッグ機能)

<br />
  
<a id = "anchor1"></a>
## 作品概要
> <dl>
> <dt>タイトル</dt>
> <dd>SALVAGE</dd>
> <dt>制作期間</dt>
> <dd>2024年8月から現在まで</dd>
> <dt>ゲームジャンル</dt>
> <dd>ホラーゲーム</dd>
> <dt>プレイ人数</dt>
> <dd>一人</dd>
> <dt>使用言語</dt>
> <dd>C++</dd>
> <dd>HLSL</dd>
> <dt>使用ツール</dt>
> <dd>Visual Studio 2022</dd>
> <dd>Visual Studio Code</dd>
> <dd>Adobe Photoshop 2025</dd>
> <dd>3ds Max 2024</dd>
> <dd>Effekseer</dd>
> <dd>GitHub</dd>
> <dd>Fork</dd>
> <dd>Trello</dd>
> <dt>開発環境</dt>
> <dd>学校内製の簡易エンジン</dd>
> <dd>Windows11</dd>
> </dl>



<br />

<a id = "anchor2"></a>
# 作成したソースコード
>- Accessories.cpp
>- Accessories.h
>- BackGroundCeiling.cpp
>- BackGroundCeiling.h
>- BackGroundFloor.cpp
>- BackGroundFloor.h
>- BackGroundWalls.cpp
>- BackGroundWalls.h
>- BootObjectBase.cpp
>- BootObjectBase.h
>- Crystal.cpp
>- Crystal.h
>- CrystalDataHolder.h
>- CrystalGetCommandSprite.cpp
>- CrystalGetCommandSprite.h
>- DebugEnemyTrackingState.cpp
>- DebugEnemyTrackingState.h
>- Elevator.cpp
>- Elevator.h
>- Enemy_Warrior.cpp
>- Enemy_Warrior.h
>- EnemyAIBase.cpp
>- EnemyAIBase.h
>- EnemyAIConBase.cpp
>- EnemyAIConBase.h
>- EnemyAIConColPlayer.cpp
>- EnemyAIConColPlayer.h
>- EnemyAIConSearch.cpp
>- EnemyAIConSearch.h
>- EnemyAIConWaitTime.cpp
>- EnemyAIConWaitTime.h
>- EnemyAIConWallSearch.cpp
>- EnemyAIConWallSearch.h
>- EnemyAIMetaBase.cpp
>- EnemyAIMetaBase.h
>- EnemyAIMetaWarrior.cpp
>- EnemyAIMetaWarrior.h
>- EnemyAIMove.cpp
>- EnemyAIMove.h
>- EnemyAIMoveAstar.cpp
>- EnemyAIMoveAstar.h
>- EnemyBase.cpp
>- EnemyBase.h
>- EnemySM_Warrior.cpp
>- EnemySM_Warrior.h
>- EnemySMBase.cpp
>- EnemySMBase.h
>- EnemyWarriorTrackingState.h
>- Game.cpp
>- Game.h
>- GameCamera.cpp
>- GameCamera.h
>- Load.cpp
>- Load.h
>- Locker.cpp
>- Locker.h
>- ManagerCrystal.cpp
>- ManagerCrystal.h
>- ObjectBase.cpp
>- ObjectBase.h
>- PatrolRuteDataHolder.h
>- Player.cpp
>- Player.h
>- PlayerOxygenUi.cpp
>- PlayerOxygenUi.h
>- PlayerScanCrystalUi.cpp
>- PlayerScanCrystalUi.h
>- PlayerScoreUi.cpp
>- PlayerScoreUi.h
>- PlayerStaminaUi.cpp
>- PlayerStaminaUi.h
>- PlayerUIBase.h
>- Result.cpp 
>- Result.h

<br />

<a id = "anchor4"></a>
# ◇ゲーム説明
> ### このゲームは廃研究所に侵入した主人公が研究所内部にある鉱石を</dd>
> ### 残り酸素が続く限り採取して、内部にいるモンスターに襲われないように</dd>
> ### 研究所から脱出するホラー採取ゲームです</dd>
> ### 酸素ゲージがなくなる前に、できるだけ多くの鉱石を採取するのが目的の</dd>
> ### ゲームです。
>
> メインゲーム画面
> ![alt text](image1.png)
> ![alt text](image2.png)

<br />

<a id = "anchor3"></a>
# ◇操作説明
> ![alt text](image3.png)

<br />

<a id = "anchor4"></a>
# ◇技術紹介

<br />

<a id = "anchor5"></a>
## ◇ステートマシン
>実装理由:プログラムの順序を分かりやすく視覚化しておくことによって、
>プログラムの制御や追加がやりやすくなるため。
>
>例：モンスターのステートマシン
> ![alt text](image4.png)

<br />

<a id = "anchor6"></a>
## ◇集団制御(メタＡＩ)
>実装理由:モンスター3体の集団制御のため
>
>実際のメタAIの形式
> ![alt text](image5.png)

<br />

<a id = "anchor7"></a>
## 川瀬式Bloomフィルターの実装
>実装理由:暗がりでの光をよりリアルに見せるため
>
><dl>
><dt>実装方式</dt>
><dt>1.輝度抽出用のレンダリングターゲットを作成する。</dt>
><dd>本書や、サンプルプログラムでは、同じくレンダリングエンジンのプログラムファイルに記載されているが</dd>
><dd>今回はプログラム量の多さから、分かりにくくなってしまうためプログラムをクラスにして別に実装した。
><dd>説明上の分かりやすさのため輝度抽出クラスと呼びます。</dd>
><dd>この輝度抽出クラスをレンダリングエンジン側でメンバ変数として宣言、レンダリングエンジンの
><dd>初期化の際共に初期化し、その初期化のタイミングでレンダリングターゲットが作成される。
><dd>この初期化の際には、ほかにも</dd>
><dd>・輝度抽出用のスプライトの初期化</dd>
><dd>・ガウシアンブラークラスの初期化、ぼかすテクスチャのアドレスの設定</dd>
><dd>・生成したボケ画像を合成するスプライトの初期化
><dd>などが行われている。</dd>
><hr>
><hr>
><dt>2.輝度抽出をするタイミングでレンダリングターゲットを作成したものに変更する。</dt>
><dd>レンダリングターゲットをモデルの描画やライトの処理をしたレンダリングターゲットから変更する。
><dd>輝度抽出クラスの関数に変更からその後の処理までがプログラムされているため</dd>
><dd>関数から抜ける頃には輝度抽出の処理は終わっている。</dd>
><dt>3.ガウシアンブラーの実行</dt>
><dd>通常のBloomとは違い複数回ガウシアンブラーを実行します。こうすることで、光のあふれテクスチャを</dd>
><dd>生成することができます。</dd>
><dt>4.ボケ画像を合成しメインレンダリングターゲットに加算する</dt>
><dd>シェーダー側でボケ画像を合成し、メインレンダリングターゲットにレンダリングターゲットを変更</dd>
><dd>合成します。</dd>
><dd>この合成スプライトは輝度抽出クラスで宣言、初期化されているため、レンダリングエンジンのプログラム</dd>
><dd>から、輝度抽出クラスのメンバ変数を使ってクラスにあるドローコール関数を実行します。
><dd>これにより、川瀬式Bloomフィルターを使用した輝度抽出から合成描画までが完了します。</dd>
></dl>

<br />

<a id = "anchor8"></a>
## ◇デバッグ機能
>実装理由:デバッグのため
>
>今回の開発では、ifdef _DEBUGを使い、Debugの起動方式で自動的に
>デバックのプログラムが実行されるようにした。
><dl>
><dt>追加したデバッグ機能は</dt>
><dd>鉱石が採取可能かどうか画面に表示</dd>
><dd>鉱石採取時のコマンドステートを画面に表示</dd>
><dd>現在のエネミーのステートを色分けで画面に表示</dd>
><dd>カメラを一人称から三人称に切り替えるボタンを有効化(LB)</dd>
><dd>残り酸素量を時間で画面に表示</dd>
></dl>

<br />