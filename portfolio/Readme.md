# SALVAGE
> ### 河原電子ビジネス ゲームクリエイター科
> ### 氏名：武田 悠世 （たけだ はるせ）



# 目次
- [SALVAGE](#salvage)
- [目次](#目次)
  - [作品概要](#作品概要)
- [1.作成したソースコード](#1作成したソースコード)
- [2.作成したエンジンコード](#2作成したエンジンコード)
- [3.作成したシェーダー](#3作成したシェーダー)
- [4.ゲーム説明](#4ゲーム説明)
  - [4-1.プレイヤーについて](#4-1プレイヤーについて)
  - [4-2.スタミナUIについて](#4-2スタミナuiについて)
  - [4-3.酸素UIについて](#4-3酸素uiについて)
  - [4-4.スコアUIについて](#4-4スコアuiについて)
  - [4-5.クリーチャーについて](#4-5クリーチャーについて)
  - [4-6.クリスタルについて](#4-6クリスタルについて)
  - [4-7.ウィンドウインフォメーションについて](#4-7ウィンドウインフォメーションについて)
- [5.操作説明](#5操作説明)
- [6.技術紹介](#6技術紹介)
  - [6-1.ステートマシン](#6-1ステートマシン)
  - [6-2.集団制御(メタＡＩ)](#6-2集団制御メタａｉ)
  - [6-3.川瀬式Bloomフィルターの実装](#6-3川瀬式bloomフィルターの実装)
  - [6-4.デバッグ機能](#6-4デバッグ機能)

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
> <dt>GitHubのURL</dt>
> <a href="https://github.com/harusame777/haruGame"><dd>https://github.com/harusame777/haruGame</dd></a>
> <dd>プレイ動画のURL</dd>
> <a href="https://youtu.be/jW00RJZBNB4"><dd>https://youtu.be/jW00RJZBNB4</dd></a>
> </dl>



<br />

<a id = "anchor2"></a>
# 1.作成したソースコード
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
>- Gameover.cpp
>- Gameover.h
>- GameSound.cpp
>- GameSound.h
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
>- Title.cpp
>- Title.h
>- WarriorAIMetaFootSteps.cpp
>- WarriorAIMetaFootSteps.h
>- WarriorAIMetapPatrol.cpp
>- WarriorAIMetapPatrol.h
>- WarriorAIMetaRetreat.cpp
>- WarriorAIMetaRetreat.h
>- WarriorAIMetaStop.cpp
>- WarriorAIMetaStop.h
>- WarriorAIMetaTracking.cpp
>- WarriorAIMetaTracking.h
>- WarriorDataHolder.h
>- Window.cpp
>- Window.h

<br />

<a id = "anchor3"></a>
# 2.作成したエンジンコード 
>- DirectionalLight.cpp
>- DirectionalLight.h
>- FontRender.cpp
>- FontRender.h
>- IRenderer.h
>- LevelRender.cpp 
>- LevelRender.h
>- LuminnceRender.cpp
>- LuminnceRender.h
>- ModelRender.cpp
>- ModelRender.h
>- PointLight.cpp
>- PointLight.h
>- RenderingEngine.cpp
>- RenderingEngine.h
>- SceneLight.cpp
>- SceneLight.h
>- ShadowMapRender.cpp
>- ShadowMapRender.h
>- SpotLight.cpp
>- SpotLight.h
>- SpriteRender.cpp
>- SpriteRender.h

<br />

<a id = "anchor4"></a>
# 3.作成したシェーダー
>- haruharuCircularGaugeSprite.fx
>- haruharuCrystalModel.fx
>- haruharuDeaphShadowReceiverModel.fx
>- haruharuDrawDeaphShadowMap.fx
>- haruharuDrawShadowMap.fx
>- haruharuLoadSpriteShader.fx
>- haruharuModel.fx
>- haruharuOxygenGaugeSpriteShader.fx
>- haruharuPostEffect.fx
>- haruharuRenderToGBufferFor3DModel.fx
>- haruharuShadowReceiverModel.fx
>- haruharuSprite.fx
>- haruharuStaminaBarSpriteShader.fx
>- haruharuWindowSpriteShader.fx
>- haruharuWipeSprite.fx
>- haruharuWipeSpriteMoveVer.fx

<br />

<a id = "anchor5"></a>
# 4.ゲーム説明
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

<a id = "anchor5-1"></a>
## 4-1.プレイヤーについて
>
><dl>
><dt>実装方式</dt>
><dt>FPS視点について</dt>
><dd>カメラをマップのちょうどプレイヤーの視点の高さに来るように配置し、そのカメラをキャラクターコントローラーに追従させる形で実装しました。</dd>
><dt>ダッシュについて</dt>
><dd>キャラクタークラス内でスタミナUIのインスタンスを取得し、そのインスタンスにスタミナ変数の値を渡すことによって外部出力を行っています。</dd>
>
> ![alt text](gif_image1.gif)
> 
><dt>工夫した点</dt>
><dt>なぜFPSか</dt>
><dd>FPSにすることにより、モンスターに追われる際や、モンスターから隠れている状況でより緊張感が生まれ、よりゲームに没入し楽しめるのではないかと思ったからです。</dd>
><dd>後述する方法で音を三次元的に表現しているため、FPS視点もあいまって、かなりリアルに近い緊張感を感じる事ができます。</dd>
></dl>

<br />

<a id = "anchor5-2"></a>
## 4-2.スタミナUIについて
>
><dl>
><dt>実装方式</dt>
><dt>UIの動きについて</dt>
><dd>UIの枠とゲージを別々に描画し、ゲージの方を円形ワイプを応用して増減を表現しました。そして、プレイヤー側のスタミナ変数の割合でゲージの割合を制御することでスタミナの数値によってスタミナゲージが変化するように設計しました。</dd>
>
> ![alt text](gif_image2.gif)
>
>
> ![alt text](gif_image2_cat.gif)
> 
><dt>工夫した点</dt>
><dt>プログラムの設計</dt>
><dd>外部から変数を設定できるようにし、再利用性を高め、変数の変更等があったりした時に対応できるようにしました。</dd>
><dt>演出面</dt>
><dd>スタミナ低下時にスタミナを点滅させるようにし、またスタミナがなくなった時はスタミナを赤く点滅させるようにして、ユーザーから見てスタミナの状態が分かりやすいようにしました。</dd>
></dl>

<br />

<a id = "anchor5-3"></a>
## 4-3.酸素UIについて
>
><dl>
><dt>実装方式</dt>
><dt>UIの動きについて<dt>
><dd>ゲージは通常のワイプを使用し増減を表現しました。そして、ゲーム側のタイマー変数の割合でゲージの割合を制御する事でタイマーの数値によってゲージが変化するように設計しました。</dd>
>
> ![alt text](gif_image3.gif)
>
>
> ![alt text](gif_image3_cat.gif)
> 
><dt>工夫した点</dt>
><dt>プログラムの設計</dt>
><dd>こちらもスタミナゲージと同じく、外部から変数を設定できるようにし、再利用性を高め、変数の変更等の理由があったりした時に対応できるようにしました。</dd>
><dt>演出面</dt>
><dd>タイマーが半分以下になった際にゲージを黄色に変更するようにし、タイマーが1分以下になった際にゲージを赤色にし、点滅させ、ユーザーに緊張感と焦りを与えよりスリルを味わえるようにしました。</dd>
</dl>

<br />

<a id = "anchor5-4"></a>
## 4-4.スコアUIについて
>
><dl>
><dt>実装方式</dt>
><dt>UIの動きについて</dt>
><dd>スコアは学校側のエンジンの元々の昨日である文字描画で表現しました。そして、クリスタルのクラス内の関数から、スコアUI内の関数に増加分の数値を引数として設定、実行することでスコアの増減を行えるように設計しました。</dd>
>
> ![alt text](gif_image4.gif)
>
>
> ![alt text](gif_image4_cat.gif)
>
><dt>工夫した点</dt>
><dt>増減の表現方式</dt>
><dd>増減の表現方式として、スコアを加算する際に、スコア加算分を計算したスコアに向けて、現在表示中のUIの変数を少しずつ増やす方式を取りました。こうする事で、デジタル感が表現できて、世界観にとてもマッチしているので、作ってよかったと思いました。</dd>
</dl>

<br />

<a id = "anchor5-5"></a>
## 4-5.クリーチャーについて
>
><dl>
><dt>実装方式</dt>
><dt>仕様</dt>
><dd>・数は全部で3体</dd>
><dd>・特殊能力等の設定などはない</dd>
><dd>・研究所をうろついている実験動物みたいなイメージ</dd>
><dt>行動について</dt>
><dd>行動は全部で3パターンあり、それぞれ、巡回、追跡、待機、となっている。
><dd>巡回状態では、エネミー生成時に設定される、いくつかのステージ内の座標を目的地とし、そこに向かって学校エンジン製のナビメッシュを使用したパス移動を行う、これをプレイヤーが見つかるか、目的地に到達する、後述するメタAIから指示が出るまで繰り返す。</dd>
><dd>追跡状態では、プレイヤーの座標を取得し、その座標を目的地としてナビメッシュを使用したパス移動、またはキャラクターコントローラーを使用した移動を行う、プレイヤーと自身の間に、壁があるかないかで、パス移動をするかキャラクターコントローラー移動をするかを切り替え、自然な移動、追跡をすることができる。こちらは、プレイヤーに自身が接触するか、プレイヤーを見失うまで繰り返す。
></dd>
><dd>待機状態では、３秒待ってから、次の巡回位置の決定をし、巡回へと行動を切り替える処理を行う。</dd>

<br />

<a id = "anchor5-6"></a>
## 4-6.クリスタルについて
>
><dl>
><dt>実装方式</dt>
><dt>仕様</dt>
><dd>・同時スポーンは3個まで</dd>
><dd>・発生場所はランダム</dd>
><dd>・一度採取した場合は5秒後に別の場所にリスポーンする</dd>
><dt>採取方法</dt>
><dd>視点を合わせ、Bボタンを押すと、採取コマンドが出現する、採取コマンドの真ん中にはA、B、X、Yのうちどれかが表示されており、対応しているボタンを時間内に押すと、次のコマンドが表示される、これを5回繰り返すと採取成功となり、スコアが加算される。
><dt>工夫した点</dt>
><dt>設置プログラム</dt>
><dd>クリスタル全体を管理するプログラムを作成し、マップの設置場所をレベルから取得し初期設置を行ったり、常に取得されたかどうかを監視し、取得されたら再設置タイマーを設定、再設置まで行うように設計しました。</dd>
><dt>採取コマンドのスプライト</dt>
><dd>採取コマンドのスプライトは動きをこだわりました、ツルハシの回転をイージングで行い動きをつけました。残りコマンド時間が分かりやすいように残り時間で、コマンド周辺の円が円形ワイプで減少するように作りました。</dd>
></dl>

<br />

<a id = "anchor5-7"></a>
## 4-7.ウィンドウインフォメーションについて
>
><dl>
><dt>実装方式</dt>
><dt>UIの動きについて</dt>
><dd>スプライトは、一番下に、文字を表示させる場所である、ウィンドウベースをもってきて、その上に、ウィンドウの枠である、ウィンドウバーを描画する構成にしています。そして、ウィンドウバーを上下に動かす際に、ウィンドウベースを上下からワイプすることによって、ウィンドウの開け閉めの演出をしています。</dd>
><dt>工夫した点</dt>
><dt>ワイプ方式</dt>
><dd>ウィンドウバーの上下によってワイプの割合を調整する方法は、上部のウィンドウバーの開閉割合を使用して、ウィンドウワイプの割合を計算することによって実現しました。</dd>
><dt>文字表示形式</dt>
><dd>ウィンドウインフォメーションを簡単に使いまわせるように、文字表示は外部クラスから簡単にインプットできるように設計しました。</dd>
><dt>小機能</dt>
><dd>文字表示中にBボタンを押すことで、文字送りが行われる機能を追加しました</dd>

<br />

<a id = "anchor6"></a>
# 5.操作説明
> ![alt text](image3.png)

<br />

<a id = "anchor7"></a>
# 6.技術紹介

<br />

<a id = "anchor8"></a>
## 6-1.ステートマシン
>実装理由:プログラムの順序を分かりやすく視覚化しておくことによって、
>プログラムの制御や追加がやりやすくなるため。
>
>例：モンスターのステートマシン
> ![alt text](image4.png)

<br />

<a id = "anchor9"></a>
## 6-2.集団制御(メタＡＩ)
>実装理由:モンスター3体の集団制御のため
>
>実際のメタAIの形式
> ![alt text](image5.png)

<br />

<a id = "anchor10"></a>
## 6-3.川瀬式Bloomフィルターの実装
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

> 以下輝度抽出_合成描画用のシェーダーのプログラム
> ```ruby : shader
>
> cbuffer cb : register(b0)
> {
>     float4x4 mvp;       // MVP行列
>     float4 mulColor;    // 乗算カラー
> };
> 
> struct VSInput
> {
>     float4 pos : POSITION;
>     float2 uv  : TEXCOORD0;
> };
> 
> struct PSInput
> {
>     float4 pos : SV_POSITION;
>     float2 uv  : TEXCOORD0;
> };
> 
> /*!
>  * @brief 頂点シェーダー
>  */
> PSInput VSMain(VSInput In)
> {
>     PSInput psIn;
>     psIn.pos = mul(mvp, In.pos);
>     psIn.uv = In.uv;
>     return psIn;
> }
> 
> Texture2D<float4> mainRenderTargetTexture : register(t0); // メインレンダリングターゲットのテクスチャ
> sampler Sampler : register(s0);
> 
> /////////////////////////////////////////////////////////
> // 輝度抽出用
> /////////////////////////////////////////////////////////
> /*!
>  * @brief 輝度抽出用のピクセルシェーダー
>  */
> float4 PSLuminance(PSInput In) : SV_Target0
> {
>     // 輝度を抽出するピクセルシェーダーを実装
>     float4 color = mainRenderTargetTexture.Sample(Sampler, In.uv);
>     
>     // サンプリングされたカラーの明るさを計算
>     float t = dot(color.xyz, float3(0.2125f, 0.7154f, 0.0721f));
>     
>     // clip関数は引数の値がマイナスになると以降の処理をスキップする
>     // なので、マイナスになるとピクセルカラーは出力されない
>     // 今回の実装はカラーの明るさが1以下ならピクセルキルする
>     clip(t - 0.9f);
>     
>     return color;
> }
> 
> // ボケ画にアクセスする為の変数
> Texture2D<float4> g_bokeTexture_0 : register(t0);
> Texture2D<float4> g_bokeTexture_1 : register(t1);
> Texture2D<float4> g_bokeTexture_2 : register(t2);
> Texture2D<float4> g_bokeTexture_3 : register(t3);
> 
> // ボケ画像合成用のピクセルシェーダー
> float4 PSBloomFinal(PSInput In) : SV_Target0
> {
>     // ボケ画像を合成
>     float4 combineColor = g_bokeTexture_0.Sample(Sampler, In.uv);
>     combineColor += g_bokeTexture_1.Sample(Sampler, In.uv);
>     combineColor += g_bokeTexture_2.Sample(Sampler, In.uv);
>     combineColor += g_bokeTexture_3.Sample(Sampler, In.uv);
>     combineColor /= 4.0f;
>     combineColor.a = 1.0f;
>     return combineColor;
> }
>
> ```


<br />

<a id = "anchor11"></a>
## 6-4.デバッグ機能
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