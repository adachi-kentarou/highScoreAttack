
#include "GameMain.h"
#include "Lib/InputManager/InputManager.h"
#include "Lib/InputManager/InputJoystick.h"
#include <stdlib.h>
#include <time.h>
//AudioEngineのインクルード
#include "audio/include/AudioEngine.h"

using namespace cocos2d;

using namespace cocos2d::experimental;

/**
*	@desc	シーンの生成
*	@return	CMain レイヤーを内包したシーンクラスインスタンス
*	@tips	静的メンバ関数
*/
cocos2d::Scene* CGameMain::createScene() {

	// シーンの生成
	cocos2d::Scene* pScene = cocos2d::Scene::create();

	// GameMain レイヤーの生成
	CGameMain* pLayer = CGameMain::create();

	// CMain レイヤーをシーンに取り付ける
	pScene->addChild(pLayer);
	// 生成したシーンを返す
	return pScene;
}

/**
*	@desc	キーボードのキーを押した際のイベント
*	@param	キーコード
*	@param	イベント
*/
void CGameMain::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {

	// 入力管理に入力処理を委託
	CInputManager::getInstance()->onKeyPressed(keyCode);
}

/**
*	@desc	キーボードのキーを離した際のイベント
*	@param	キーコード
*	@param	イベント
*/
void CGameMain::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event) {

	// 入力管理に入力処理を委託
	CInputManager::getInstance()->onKeyReleased(keyCode);
}



// デストラクタ
CGameMain::~CGameMain() {
	//BGMの停止
	if (mode != 5) {
		AudioEngine::stop(this->m_bgmid);
	}

	//入力クリア
	CInputManager::getInstance()->clearInputFlag();
	//出撃データの配列を解放
	SAFE_DELETE_ARRAY(m_pEnemyLaunchData);
}

CEnemyCharacter* CGameMain::m_pEnemyCharas[];
CPlayerCharacter* CGameMain::m_pPlayerChara;
int CGameMain::pweponLevel[];
int CGameMain::m_frameCounter;
int CGameMain::mode;
int CGameMain::m_stageNo;
//プレイヤーキャラクターステータス
int CGameMain::m_hp;
int CGameMain::m_maxHp;
int CGameMain::m_attackPt;
int CGameMain::m_score;
int CGameMain::m_speed;
int CGameMain::weponSelect;
//オブジェクトカウント用
//敵キャラカウント
int CGameMain::m_pEnemyCount;
//プレイヤー弾カウント
int CGameMain::m_pPlayerBulletCount;
//敵弾カウント
int CGameMain::m_pEnemyBulletCount;
//エフェクトカウント
int CGameMain::m_pEfectCount;
//アイテムカウント
int CGameMain::m_pItemCount;
//壁カウント
int CGameMain::m_pWallCount;

//プレイヤー数
int CGameMain::playerCount;
//ボム数
int CGameMain::bom;

void CGameMain::onEnterTransitionDidFinish() {
	cocos2d::log("senni finish");
	//終了有効化
	SCENE_END = false;
}

/**
*	@desc	初期化
*	@return	true...成功	false...失敗
*/
bool CGameMain::init() {
	CInputManager::getInstance()->clearInputFlag();
	// 親レイヤーの初期化
	if (Layer::init() == false) {
		return false;
	}

	// 乱数生成
	//srand( time( NULL ) ) ;

	// キーボード入力イベント受け取り設定
	this->setKeyboardEnabled(true);

	// update 関数 ( 更新処理関数 ) 呼び出し設定
	// この部分を消したりコメントアウトすると update 関数が呼ばれなくなるので注意
	this->scheduleUpdate();




	//=========================================================================
	//
	//	ここから初期化、初期設定のコードを追加
	//
	//=========================================================================

	//=========================================================================
	//	リプレイ関係
	//=========================================================================

	//ステージ毎設定
	if (mode == 2 || mode == 5) {
		//リプレイの場合
		//ゲームモード設定
		GAME_MODE = REPLAY_DATA[0] & 0b11;
		playerData = REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4 + 1];
		
		CGameMain::bom = playerData & 0b1111;
		playerData >>= 4;
		CGameMain::playerCount = playerData & 0b1111;
		playerData >>= 4;
		CGameMain::m_speed = playerData & 0b1111;
		playerData >>= 4;
		CGameMain::weponSelect = playerData & 0b111;
		playerData >>= 3;
		CGameMain::m_maxHp = playerData & 0b11111111;
		playerData >>= 8;
		CGameMain::m_hp = playerData & 0b11111111;
		//data2
		CGameMain::m_score = REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4 + 2];


		playerData = REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4 + 3];
		//data3
		CGameMain::pweponLevel[5] = playerData & 0b1111;
		playerData >>= 4;
		CGameMain::pweponLevel[4] = playerData & 0b1111;
		playerData >>= 4;
		CGameMain::pweponLevel[3] = playerData & 0b1111;
		playerData >>= 4;
		CGameMain::pweponLevel[2] = playerData & 0b1111;
		playerData >>= 4;
		CGameMain::pweponLevel[1] = playerData & 0b1111;
		playerData >>= 4;
		CGameMain::pweponLevel[0] = playerData & 0b1111;

	}
	else if (CGameMain::m_stageNo == 1) {
		//リプレイ配列初期化
		if (mode == 0) {
			for (int i = 0; i < 12020; i++) {
				REPLAY_DATA[i] = 0;
			}
			REPLAY_DATA[0] = MapData::m_seed;
		}

		//プレイモードの場合はリプレイデータに初期値を設定
		//次ステージに現在のステータスを記録

		playerData = CGameMain::m_hp;
		playerData <<= 8;
		playerData += CGameMain::m_maxHp;
		playerData <<= 3;
		playerData += CGameMain::weponSelect;
		playerData <<= 4;
		playerData += CGameMain::m_speed;
		playerData <<= 4;
		playerData += CGameMain::playerCount;
		playerData <<= 4;
		playerData += CGameMain::bom;
		//data1
		REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4 + 1] = playerData;
		//data2
		REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4 + 2] = CGameMain::m_score;

		playerData = CGameMain::pweponLevel[0];
		playerData <<= 4;
		playerData += CGameMain::pweponLevel[1];
		playerData <<= 4;
		playerData += CGameMain::pweponLevel[2];
		playerData <<= 4;
		playerData += CGameMain::pweponLevel[3];
		playerData <<= 4;
		playerData += CGameMain::pweponLevel[4];
		playerData <<= 4;
		playerData += CGameMain::pweponLevel[5];
		//data3
		REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4 + 3] = playerData;
	}

	//=========================================================================
	//	レイヤーの初期化に関するコードの追加はここから
	//=========================================================================
	//背景レイヤー
	m_backGroundLayer = cocos2d::Layer::create();
	this->addChild(m_backGroundLayer);
	//壁レイヤー
	m_wallLayer = cocos2d::Layer::create();
	this->addChild(m_wallLayer);
	//キャラクターレイヤー
	m_characterLayer = cocos2d::Layer::create();
	this->addChild(m_characterLayer);
	//ステータスレイヤー
	m_interFaceLayer = cocos2d::Layer::create();
	this->addChild(m_interFaceLayer);
	//=========================================================================
	//	マップの初期化に関するコードの追加はここから
	//=========================================================================

	mapSeed = mode == 0 ? MapData::m_seed : REPLAY_DATA[0];
	//mapSeed = 1508591550;

	//ステージ毎にシード値設定
	srand(mapSeed);
	for (int i = 1; i < CGameMain::m_stageNo; i++) {
		rand();
	}
	mapSeed = rand();

	m_pMapData.create(mapSeed);
	srand(mapSeed);
	cocos2d::log("seed=%d mapdata=%d", mapSeed, MapData::m_seed);
	//=========================================================================
	//	マップの生成の設定
	//=========================================================================

	//m_pMap = CMap::create(MAP_FILE_STAGE_1);
	m_pMap = CMap::create(IMAGE_FILE_BACKGROUND);
	//スクロール速度の設定
	this->m_pMap->m_scrollMove.m_velX = 1.0f;
	//ループ設定(ループあり設定)
	this->m_pMap->m_isLoop = true;
	//レイヤーに取り付け
	m_backGroundLayer->addChild(this->m_pMap);
	//=========================================================================
	//	プレイヤーの初期化に関するコードの追加はここから
	//=========================================================================
	m_pPlayerChara = CPlayerCharacter::create();
	
	m_characterLayer->addChild(this->m_pPlayerChara);

	bomCount = 0;

	//=========================================================================
	//	プレイヤーバレット ( プレイヤーの弾 ) の初期化に関するコードの追加はここから
	//=========================================================================
	for (int i = 0; i < CBullet::MAX_BULLET; i++)
	{
		m_pPlayerBullets[i] = NULL;
	}

	//=========================================================================
	//	敵の初期化に関するコードの追加はここから
	//=========================================================================
	for (int i = 0; i < CEnemyCharacter::MAX_ENEMY; i++)
	{
		m_pEnemyCharas[i] = NULL;
	}
	//=========================================================================
	//	敵の弾の初期化に関するコードの追加はここから
	//=========================================================================
	//敵の弾の配列初期化
	for (int i = 0; i < CBullet::MAX_BULLET; i++) {
		m_pEnemyBullets[i] = NULL;
	}

	//=========================================================================
	//	敵出撃データの初期化に関するコードの追加はここから
	//=========================================================================
	//現在参照中の出撃データ番号の初期化
	this->m_enemyLaunchIndex = 0;

	//現在参照中の出撃警告番号の初期化
	this->m_enemyAleartIndex = 0;
	for (int i = 0; i < (int)MapData::m_pEnemyLaunchData.size(); i++) {
		if (MapData::m_pEnemyLaunchData[i].m_frame > 60) {
			this->m_enemyAleartIndex = i;
			cocos2d::log("aleartIndex = %d", i);
			break;
		}
	}

	//フレームカウンターの初期化
	this->m_frameCounter = 0;
	//ステージクリアフレームの初期化
	this->m_clearFrame = CLEAR_FRAME;
	//this->m_clearFrame = 600;

	//=========================================================================
	//　エフェクトの初期化に関するコードの追加はここから
	//=========================================================================
	for (int i = 0; i < CEfect::MAX_EFFECT; i++)
	{
		m_pEffects[i] = NULL;
	}

	//=========================================================================
	//　壁の初期化に関するコードの追加はここから
	//=========================================================================
	for (int i = 0; i < CWall::MAX_WALL; i++)
	{
		m_pWalls[i] = NULL;
	}

	//壁出現X座標
	m_pWallXpos = 0;
	//壁カウンター
	m_wallCounter = 0;
	//壁移動スピード
	//WALL_SPEED = 0.5;

	//BGMの再生
	if (mode != 5) {
		switch (CGameMain::m_stageNo) {
		case 1:
			this->m_bgmid = AudioEngine::play2d(SOUND_FILE_BGM_1);
			break;
		case 2:
			this->m_bgmid = AudioEngine::play2d(SOUND_FILE_BGM_2);
			break;
		case 3:
			this->m_bgmid = AudioEngine::play2d(SOUND_FILE_BGM_3);
			break;
		}
	}

	AudioEngine::setVolume(this->m_bgmid, BGM_VOLUME / 100.0f);

	//ループの設定(true...ループする　false...ループしない)
	AudioEngine::setLoop(this->m_bgmid, true);
	//なぜかこれで音が鳴る
	AudioEngine::getDuration(this->m_bgmid);
	//サウンドディレイ初期化
	soundDeray = 0;
	//=========================================================================
	//	ユーザーインターフェースの初期化に関するコードの追加はここから
	//=========================================================================
	//HPラベルの生成と初期化
	m_pHpLabel = CHpLabel::create();
	m_pHpLabel->setStatus(&m_pPlayerChara->m_status);

	//レイヤーに張り付ける
	m_interFaceLayer->addChild(m_pHpLabel);

	//HPゲージの生成と初期化

	CCRenderTexture* pRenderTexture = CCRenderTexture::create(204, 20);
	pRenderTexture->setPosition(180.0f, 468.0f);
	pRenderTexture->beginWithClear(255, 0, 0, 255);

	//描画終了
	pRenderTexture->end();
	//レイヤーに取り付け
	m_interFaceLayer->addChild(pRenderTexture);

	m_pHpGuage = CHpGuage::create();
	//プレイヤーのステータスを設定
	m_pHpGuage->setStatus(&m_pPlayerChara->m_status);
	//レイヤーに張り付ける
	m_interFaceLayer->addChild(m_pHpGuage);


	//スコアラベルの生成と初期化
	m_pScoreLabel = CScoreLabel::create();

	m_pScoreLabel->setStatus(&m_pPlayerChara->m_status);

	//レイヤーに張り付ける
	m_interFaceLayer->addChild(m_pScoreLabel);

	//ステージラベルの生成と初期化
	m_pStageLabel = CStageNoLabel::create();

	m_pStageLabel->setStage(&this->m_stageNo);

	//レイヤーに張り付ける
	m_interFaceLayer->addChild(m_pStageLabel);

	//プレイヤーラベルの生成と初期化
	m_pPlayerLabel = CPlayerLabel::create();

	m_pPlayerLabel->setPlayer(&this->playerCount);

	//レイヤーに張り付ける
	m_interFaceLayer->addChild(m_pPlayerLabel);

	//ボムラベルの生成と初期化
	m_pBomLabel = CBomLabel::create();

	m_pBomLabel->setBom(&this->bom);

	//レイヤーに張り付ける
	m_interFaceLayer->addChild(m_pBomLabel);

	//攻撃種類ラベルここから
	int fsize = 17;
	//ノーマル
	//タイトルラベルの生成と取り付け
	pweponLavel[0] = cocos2d::Label::createWithTTF("NORMAL", FONT_FILE_STARWARS, fsize);
	//初期位置の設定
	pweponLavel[0]->setPosition(51.0f, 10.0f);
	//文字色の設定
	pweponLavel[0]->setColor(Color3B(200, 200, 200));
	//レイヤーに取り付け
	m_interFaceLayer->addChild(pweponLavel[0]);

	//レベル表示
	pweponLevelLavel[0] = cocos2d::Label::createWithTTF(
		cocos2d::StringUtils::format("Level %d", CGameMain::pweponLevel[0] + 1),
		FONT_FILE_STARWARS, fsize);
	//初期位置の設定
	pweponLevelLavel[0]->setPosition(51.0f, 30.0f);
	//文字色の設定
	pweponLevelLavel[0]->setColor(Color3B(200, 200, 200));
	//レイヤーに取り付け
	m_interFaceLayer->addChild(pweponLevelLavel[0]);

	//爆発
	//タイトルラベルの生成と取り付け
	pweponLavel[1] = cocos2d::Label::createWithTTF("EXPLOSION", FONT_FILE_STARWARS, fsize);
	//初期位置の設定
	pweponLavel[1]->setPosition(157.0f, 10.0f);
	//文字色の設定
	pweponLavel[1]->setColor(Color3B(200, 200, 200));
	//レイヤーに取り付け
	m_interFaceLayer->addChild(pweponLavel[1]);

	//レベル表示
	pweponLevelLavel[1] = cocos2d::Label::createWithTTF(
		cocos2d::StringUtils::format("Level %d", CGameMain::pweponLevel[1] + 1),
		FONT_FILE_STARWARS, fsize);
	//初期位置の設定
	pweponLevelLavel[1]->setPosition(157.0f, 30.0f);
	//文字色の設定
	pweponLevelLavel[1]->setColor(Color3B(200, 200, 200));
	//レイヤーに取り付け
	m_interFaceLayer->addChild(pweponLevelLavel[1]);

	//後方
	//タイトルラベルの生成と取り付け
	pweponLavel[2] = cocos2d::Label::createWithTTF("BACK", FONT_FILE_STARWARS, fsize);
	//初期位置の設定
	pweponLavel[2]->setPosition(263.0f, 10.0f);
	//文字色の設定
	pweponLavel[2]->setColor(Color3B(200, 200, 200));
	//レイヤーに取り付け
	m_interFaceLayer->addChild(pweponLavel[2]);

	//レベル表示
	pweponLevelLavel[2] = cocos2d::Label::createWithTTF(
		cocos2d::StringUtils::format("Level %d", CGameMain::pweponLevel[2] + 1),
		FONT_FILE_STARWARS, fsize);
	//初期位置の設定
	pweponLevelLavel[2]->setPosition(263.0f, 30.0f);
	//文字色の設定
	pweponLevelLavel[2]->setColor(Color3B(200, 200, 200));
	//レイヤーに取り付け
	m_interFaceLayer->addChild(pweponLevelLavel[2]);

	//レーザー
	//タイトルラベルの生成と取り付け
	pweponLavel[3] = cocos2d::Label::createWithTTF("LASER", FONT_FILE_STARWARS, fsize);
	//初期位置の設定
	pweponLavel[3]->setPosition(369.0f, 10.0f);
	//文字色の設定
	pweponLavel[3]->setColor(Color3B(200, 200, 200));
	//レイヤーに取り付け
	m_interFaceLayer->addChild(pweponLavel[3]);

	//レベル表示
	pweponLevelLavel[3] = cocos2d::Label::createWithTTF(
		cocos2d::StringUtils::format("Level %d", CGameMain::pweponLevel[3] + 1),
		FONT_FILE_STARWARS, fsize);
	//初期位置の設定
	pweponLevelLavel[3]->setPosition(369.0f, 30.0f);
	//文字色の設定
	pweponLevelLavel[3]->setColor(Color3B(200, 200, 200));
	//レイヤーに取り付け
	m_interFaceLayer->addChild(pweponLevelLavel[3]);

	//誘導
	//タイトルラベルの生成と取り付け
	pweponLavel[4] = cocos2d::Label::createWithTTF("INDCTION", FONT_FILE_STARWARS, fsize);
	//初期位置の設定
	pweponLavel[4]->setPosition(475.0f, 10.0f);
	//文字色の設定
	pweponLavel[4]->setColor(Color3B(200, 200, 200));
	//レイヤーに取り付け
	m_interFaceLayer->addChild(pweponLavel[4]);

	//レベル表示
	pweponLevelLavel[4] = cocos2d::Label::createWithTTF(
		cocos2d::StringUtils::format("Level %d", CGameMain::pweponLevel[4] + 1),
		FONT_FILE_STARWARS, fsize);
	//初期位置の設定
	pweponLevelLavel[4]->setPosition(475.0f, 30.0f);
	//文字色の設定
	pweponLevelLavel[4]->setColor(Color3B(200, 200, 200));
	//レイヤーに取り付け
	m_interFaceLayer->addChild(pweponLevelLavel[4]);

	//散弾
	//タイトルラベルの生成と取り付け
	pweponLavel[5] = cocos2d::Label::createWithTTF("MULTIPLE", FONT_FILE_STARWARS, fsize);
	//初期位置の設定
	pweponLavel[5]->setPosition(581.0f, 10.0f);
	//文字色の設定
	pweponLavel[5]->setColor(Color3B(200, 200, 200));
	//レイヤーに取り付け
	m_interFaceLayer->addChild(pweponLavel[5]);

	//レベル表示
	pweponLevelLavel[5] = cocos2d::Label::createWithTTF(
		cocos2d::StringUtils::format("Level %d", CGameMain::pweponLevel[5] + 1),
		FONT_FILE_STARWARS, fsize);
	//初期位置の設定
	pweponLevelLavel[5]->setPosition(581.0f, 30.0f);
	//文字色の設定
	pweponLevelLavel[5]->setColor(Color3B(200, 200, 200));
	//レイヤーに取り付け
	m_interFaceLayer->addChild(pweponLevelLavel[5]);

	//選択攻撃タイプの色を変える
	pweponLavel[weponSelect]->setColor(Color3B(200, 0, 0));
	pweponLevelLavel[weponSelect]->setColor(Color3B(200, 0, 0));

	//アイテムクラスに攻撃レベルラベルを渡す
	CItem::pweponLevelLavel = pweponLevelLavel;

	//攻撃力設定
	m_pPlayerChara->m_shotPower = this->pweponPower[weponSelect][pweponLevel[weponSelect]];
	//攻撃間隔設定
	m_pPlayerChara->m_shotInterval = this->pweponInterval[weponSelect][pweponLevel[weponSelect]];
	//攻撃パラメータ設定
	m_pPlayerChara->m_shotParam = this->pweponParam[weponSelect][pweponLevel[weponSelect]];
	//攻撃移動量設定
	m_pPlayerChara->m_shotVel = this->pweponVel[weponSelect][pweponLevel[weponSelect]];


	//=========================================================================
	//	アイテム の初期化に関するコードの追加はここから
	//=========================================================================
	for (int i = 0; i < CItem::MAX_ITEM; i++)
	{
		m_pItems[i] = NULL;
	}

	//=========================================================================
	//	敵データの読み込み
	//=========================================================================
	//this->loadEnemyLaunchData(this->m_enemyLaunchDataFileNameList[this->m_stageNo - 1]);

	//=========================================================================
	//	ステージモード
	//=========================================================================
	this->m_stageMode = STAGE_MODE::UPDATE;

	//=========================================================================
	//	ラベル
	//=========================================================================
	pLavelArray[10] = { NULL };

	//=========================================================================
	//	オブジェクトカウントリセット
	//=========================================================================
	//オブジェクトカウント用
	//敵キャラカウント
	m_pEnemyCount = 0;
	//プレイヤー弾カウント
	m_pPlayerBulletCount = 0;
	//弾カウント
	m_pEnemyBulletCount = 0;
	//エフェクトカウント
	m_pEfectCount = 0;
	//アイテムカウント
	m_pItemCount = 0;
	//壁カウント
	m_pWallCount = 0;

	//=========================================================================
	//	背景惑星表示カウントフレームリセット
	//=========================================================================
	m_planetFrame = 0;
	//=========================================================================
	//	デモプレイ開始フレーム調整
	//=========================================================================
	if (mode == 5) {
		int buf_se_volume = SE_VOLUME;
		//音量を０にする
		SE_VOLUME = 0;
		int shift_frame;
		int testaa;
		if (DEMO_FRAME > REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4]) {
			shift_frame = 0;
			m_clearFrame = REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4];
			testaa = 0;
		}
		else {
			shift_frame = CTitle::Rand % (REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4] - DEMO_FRAME + 1) * 0.9f;

			m_clearFrame = shift_frame + DEMO_FRAME;
			testaa = REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4];
		}
		se_flg = false;
		//デモプレイラベル
		pLavelDemo = cocos2d::Label::createWithTTF("DEMO PLAY", FONT_FILE_STARWARS, 50);

		//初期位置の設定
		pLavelDemo->setPosition(320.0f, 240.0f);
		pLavelDemo->setColor(Color3B(200, 200, 200));
		//レイヤーに取り付け
		m_interFaceLayer->addChild(pLavelDemo);
		cocos2d::log("shift start");
		for (int i = 0; i < shift_frame; i++) {
			this->stageUpdateFunc(0);
		}
		cocos2d::log("shift end");
		se_flg = true;
		SE_VOLUME = buf_se_volume;


	}

	//=========================================================================
	//
	//	ここまでに初期化、初期設定のコードを追加
	//
	//=========================================================================

	return true;
}
void CGameMain::call_back(bool a) {
	OutputDebugString(L"コールバック実行----------------------------------------\n");
}
/**
*	@desc	更新処理
*	@param	１フレーム経過時間
*/
void CGameMain::update(float deltaTime_) {
	//AudioEngine::getDuration(this->m_bgmid), this->m_frameCounter;
	//リプレイ倍速なら音も倍速にする
	if (mode == 3) {
		AudioEngine::setCurrentTimeAll(0.066666666666666666f);
	}
	if (mode == 4) {
		AudioEngine::setCurrentTimeAll(0.133333333333333333f);
	}

	// esc キーを押したらゲーム終了
	if (inputflag.m_esc == true) {
		cocos2d::Director::getInstance()->end();
	}

	//モードによる切り替え
	switch (this->m_stageMode) {
	case STAGE_MODE::START:
		this->stageStartFunc();
		break;
	case STAGE_MODE::UPDATE:
		for (int i = 0; i < (mode >= 3 && mode != 5 ? (mode == 3 ? 4 : 8) : 1) && m_stageMode == STAGE_MODE::UPDATE; i++) {
			this->stageUpdateFunc(deltaTime_);
		}
		break;
		//ステージ終了処理
	case STAGE_MODE::END:
		this->stageEndFunc();
		break;
		//ステージ一時停止処理
	case STAGE_MODE::PAUSE:
		this->stagePauseFunc();
		break;
		//ステージ一時停止処理
	case STAGE_MODE::GAME_OVER:
		this->gameOverFunc();
		break;
	default:
		break;
	}

}


void CGameMain::inputFunc() {
	
	//入力フラグ設定
	CInputJoystick::inputFunc(mode);
	
	//攻撃タイプ切り替え
	if (CInputJoystick::m_change == true) {

		if (m_xKeyDownFlag == false) {
			m_xKeyDownFlag = true;

			//変更前文字色の設定
			pweponLavel[weponSelect]->setColor(Color3B(200, 200, 200));
			pweponLevelLavel[weponSelect]->setColor(Color3B(200, 200, 200));
			//攻撃タイプ変更
			weponSelect++;
			if (weponSelect >= 6)
				weponSelect = 0;

			//変更後文字色の設定
			pweponLavel[weponSelect]->setColor(Color3B(200, 0, 0));
			pweponLevelLavel[weponSelect]->setColor(Color3B(200, 0, 0));

			//攻撃力設定
			m_pPlayerChara->m_shotPower = this->pweponPower[weponSelect][pweponLevel[weponSelect]];
			//攻撃間隔設定
			m_pPlayerChara->m_shotInterval = this->pweponInterval[weponSelect][pweponLevel[weponSelect]];
			//攻撃パラメータ設定
			m_pPlayerChara->m_shotParam = this->pweponParam[weponSelect][pweponLevel[weponSelect]];
			//攻撃移動量設定
			m_pPlayerChara->m_shotVel = this->pweponVel[weponSelect][pweponLevel[weponSelect]];
			//レーザーフラグ確認
			if (laserFlg)
				laserFlg = false;
		}
	}
	else {
		if (m_xKeyDownFlag = true) {
			m_xKeyDownFlag = false;
		}
	}

	//プレイヤーが死んでいたら飛ばす。
	if (m_pPlayerChara->m_activeFlag == false) {
		return;
	}
	//復活と無敵時間
	if (resCount != 0) {

		//表示点滅
		if (resCount % 5 == 0 && playerCount >= 0) {
			if (resCount / 5 % 2 == 0) {
				m_pPlayerChara->setVisible(true);
			}
			else {
				m_pPlayerChara->setVisible(false);
			}
		}
		resCount--;
		if (resCount == 0) {
			//無敵時間終了
			resurrection = false;
			m_pPlayerChara->setVisible(true);
		}
		else if (resCount > 120) {
			//復活モーション中
			return;
		}

	}

	//デモ画面は操作入力でタイトル画面に遷移
	if (mode == 5) {

		if (m_frameCounter % 30 == 0) {
			pLavelDemo->setVisible(!pLavelDemo->isVisible());
		}
		if (!SCENE_END) {

			if (CInputJoystick::m_repPause ||
				CInputJoystick::m_repSpeed ||
				CInputJoystick::m_repSpeed2 ||
				CInputJoystick::m_repLeft ||
				CInputJoystick::m_repRight ||
				CInputJoystick::m_repUp ||
				CInputJoystick::m_repDown ||
				playerCount < 0 && resCount > 0 && resCount <= 120 ||
				m_frameCounter >= m_clearFrame ||
				m_frameCounter >= REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4]
				) {
				//遷移中終了回避
				SCENE_END = true;
				//タイトルBGMフラグを戻す
				//CTitle::TitleBgm = -1;
				AudioEngine::setLoop(CTitle::TitleBgm, true);
				this->unscheduleUpdate();
				Scene* pScene = CTitle::createScene();
				Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
				return;
			}
		}

	}

	if (playerCount < 0 && resCount > 0 && resCount <= 120 || m_frameCounter == (mode == 0 ? m_clearFrame : REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4])) {
		if (mode == 5) {
			return;
		}
		cocos2d::log(" clear = " + REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4]);
		//次ステージ処理
		if (playerCount >= 0 && mode == 0) {
			//プレイヤー残機があるなら次ステージへ

			//フレームカウント記録
			REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4] = m_frameCounter;

			//リプレイじゃなければ次ステージにカウントアップ
			if (mode == 0) {
				++CGameMain::m_stageNo;
				//現在ステータス設定
				CGameMain::m_hp = m_pPlayerChara->m_status.getHp(),
					CGameMain::m_maxHp = m_pPlayerChara->m_status.getMaxHp();
				CGameMain::m_attackPt = m_pPlayerChara->m_status.getAttackPt();
				CGameMain::m_score = m_pPlayerChara->m_status.getScore();
				CGameMain::m_speed = m_pPlayerChara->m_status.getSpeed();

				if (CGameMain::m_stageNo != 4) {
					//次ステージに現在のステータスを記録
					playerData = CGameMain::m_hp;
					playerData <<= 8;
					playerData += CGameMain::m_maxHp;
					playerData <<= 3;
					playerData += CGameMain::weponSelect;
					playerData <<= 4;
					playerData += CGameMain::m_speed;
					playerData <<= 4;
					playerData += CGameMain::playerCount;
					playerData <<= 4;
					playerData += CGameMain::bom;
					//data1
					REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4 + 1] = playerData;
					//data2
					REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4 + 2] = CGameMain::m_score;

					playerData = CGameMain::pweponLevel[0];
					playerData <<= 4;
					playerData += CGameMain::pweponLevel[1];
					playerData <<= 4;
					playerData += CGameMain::pweponLevel[2];
					playerData <<= 4;
					playerData += CGameMain::pweponLevel[3];
					playerData <<= 4;
					playerData += CGameMain::pweponLevel[4];
					playerData <<= 4;
					playerData += CGameMain::pweponLevel[5];
					//data3
					REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4 + 3] = playerData;

				}

			}



			//ステージクリア
			if (mode == 0) {

				//遷移中終了回避
				SCENE_END = true;

				//BGM停止
				AudioEngine::stopAll();
				this->unscheduleUpdate();

				//タイムアップ処理
				if (m_frameCounter >= CLEAR_FRAME) {
					//SE
					if (se_flg) {
						int seid = AudioEngine::play2d(SOUND_FILE_TIME_UP);
						AudioEngine::setVolume(seid, SE_VOLUME / 100.0f);
					}


				}

				if (CGameMain::m_stageNo == 4) {
					//ゲームクリア処理

					CReplaySelect::replay_flg = true;

					//スコア登録
					if (mode == 0 && m_pPlayerChara->m_status.getScore() > SCORE) {
						cocos2d::log("score=%d", m_pPlayerChara->m_status.getScore());
						//config.datに設定を保存
						int buf[3] = { BGM_VOLUME ,SE_VOLUME,m_pPlayerChara->m_status.getScore() };
						//ファイルポインタ
						FILE *file1;
						file1 = fopen("config.dat", "wb");
						fwrite(buf, sizeof(int), 3, file1);
						fclose(file1);
						SCORE = m_pPlayerChara->m_status.getScore();
					}
					//タイトルBGMフラグを戻す
					CTitle::TitleBgm = -1;

					this->unscheduleUpdate();
					Scene* pScene = CReplaySelect::createScene();
					Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
					return;
				}
				else {
					//ステージクリア処理
					Scene* pScene = CStageTitle::createScene();

					Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
					return;
				}

			}

		}
		//タイムアップ処理
		if (m_frameCounter >= CLEAR_FRAME) {
			//SE
			if (se_flg) {
				int seid = AudioEngine::play2d(SOUND_FILE_TIME_UP);
				AudioEngine::setVolume(seid, SE_VOLUME / 100.0f);
			}


		}
		//ゲームオーバー
		//モードをゲームオーバーに変更
		this->m_stageMode = STAGE_MODE::GAME_OVER;
		m_characterLayer->getParent();
		//音一時停止
		AudioEngine::pauseAll();
		//モード通常に変更
		if (mode >= 3) {
			mode = 2;
		}

		if (mode == 0) {
			if (se_flg) {
				int gameoverid = AudioEngine::play2d(SOUND_FILE_GAME_OVER);
				AudioEngine::setVolume(gameoverid, SE_VOLUME / 100.0f);
			}

		}

		//カーソルSE
		int seid = AudioEngine::play2d(SOUND_FILE_CURSOR_2);
		AudioEngine::setVolume(seid, SE_VOLUME / 100.0f);
		//ポーズ画面作成
		m_pCursor = CCursor::create();
		m_pCursor->set(
			IMAGE_FILE_CURSOR,//ファイル名
			0,			//チップX座標
			0,			//チップY座標
			20,			//チップXサイズ
			20,			//チップYサイズ
			2,			//アニメーション数
			20,			//アニメーションフレーム数
			0,			//カーソルのX最大
			1,			//カーソルのY最大
			0,			//カーソルのX位置
			1,			//カーソルのY位置
			150,		//カーソルのX座標
			200,		//カーソルのY座標
			0.0f,		//X移動サイズ
			100.0f,		//Y移動サイズ
			5,			//移動アニメーションフレーム
			true,		//横ループ
			true,		//縦ループ
			10,			//低速待ちフレーム
			5			//高速待ちフレーム
		);
		//カーソル配置
		m_interFaceLayer->addChild(m_pCursor);
		//カーソル用カウンター初期化
		c_frameCounter = 0;

		//ボタン検知防止
		this->m_spaceKeyDownFlag = true;

		//ボタン押しフラグ
		p_scene = false;

		//PLAYラベルの生成と取り付け
		pLavelArray[1] = cocos2d::Label::createWithTTF("RETURN", FONT_FILE_STARWARS, 62);
		//初期位置の設定
		pLavelArray[1]->setPosition(320.0f, 300.0f);
		//文字色の設定
		pLavelArray[1]->setColor(Color3B(0, 200, 200));
		//レイヤーに取り付け
		m_interFaceLayer->addChild(pLavelArray[1]);


		//ENDラベルの生成と取り付け
		pLavelArray[0] = cocos2d::Label::createWithTTF("END", FONT_FILE_STARWARS, 62);
		//初期位置の設定
		pLavelArray[0]->setPosition(320.0f, 200.0f);
		//文字色の設定
		pLavelArray[0]->setColor(Color3B(0, 200, 200));
		//レイヤーに取り付け
		m_interFaceLayer->addChild(pLavelArray[0]);

		//スコア登録
		if (m_pPlayerChara->m_status.getScore() > SCORE) {
			cocos2d::log("score=%d", m_pPlayerChara->m_status.getScore());
			//config.datに設定を保存
			int buf[3] = { BGM_VOLUME ,SE_VOLUME,m_pPlayerChara->m_status.getScore() };
			//ファイルポインタ
			FILE *file1;
			file1 = fopen("config.dat", "wb");
			fwrite(buf, sizeof(int), 3, file1);
			fclose(file1);
			SCORE = m_pPlayerChara->m_status.getScore();
		}
		return;
	}

	if (CInputJoystick::m_right == true)
	{
		//右矢印が押された
		//速度に値を設定する
		m_pPlayerChara->m_move.m_velX = m_pPlayerChara->m_status.getSpeed() / 2;
	}
	if (CInputJoystick::m_right == false && CInputJoystick::m_left == false)
	{
		//左右矢印が離された
		//速度をリセットする
		m_pPlayerChara->m_move.m_velX = 0;
	}
	if (CInputJoystick::m_left == true)
	{
		//右矢印が押された
		//速度に値を設定する
		m_pPlayerChara->m_move.m_velX = -m_pPlayerChara->m_status.getSpeed() / 2;
	}

	if (CInputJoystick::m_up == true)
	{
		//上矢印が押された
		//速度に値を設定する
		m_pPlayerChara->m_move.m_velY = m_pPlayerChara->m_status.getSpeed() / 2;
	}
	if (CInputJoystick::m_up == false && CInputJoystick::m_down == false)
	{
		//上下矢印が離された
		//速度をリセットする
		m_pPlayerChara->m_move.m_velY = 0;
	}
	if (CInputJoystick::m_down == true)
	{
		//下矢印が押された
		//速度に値を設定する
		m_pPlayerChara->m_move.m_velY = -m_pPlayerChara->m_status.getSpeed() / 2;
	}

	if (m_pPlayerChara->m_shotCounter > 0) {
		//弾発射用カウンターが0より上なら
		//弾発射用カウンターをデクリメント
		m_pPlayerChara->m_shotCounter--;
	}

	if (CInputJoystick::m_shot == true)
	{
		shotPlayerBullet((BULLET_TYPE)weponSelect);
	}
	else {
		//レーザーフラグ確認
		laserFlg = false;
	}


	//spaceキーを押したら
	if (!SCENE_END && (CInputJoystick::m_pause == true || (mode >= 2 && CInputJoystick::m_repPause == true))) {
		//aキーが離されていたら
		if (this->m_spaceKeyDownFlag == false) {
			//aキーが押された
			this->m_spaceKeyDownFlag = true;
			if (m_stageMode == STAGE_MODE::PAUSE) {
				//モードを一時停止解除に変更
				this->m_stageMode = STAGE_MODE::UPDATE;
				//音一時停止解除
				AudioEngine::resumeAll();
			}
			else {
				//モードを一時停止に変更
				this->m_stageMode = STAGE_MODE::PAUSE;
				m_characterLayer->getParent();
				//音一時停止
				AudioEngine::pauseAll();
				//モード通常に変更
				if (mode >= 3) {
					mode = 2;
				}
				//カーソルSE
				int seid = AudioEngine::play2d(SOUND_FILE_CURSOR_2);
				AudioEngine::setVolume(seid, SE_VOLUME / 100.0f);

				//ポーズ画面作成
				m_pCursor = CCursor::create();
				m_pCursor->set(
					IMAGE_FILE_CURSOR,//ファイル名
					0,			//チップX座標
					0,			//チップY座標
					20,			//チップXサイズ
					20,			//チップYサイズ
					2,			//アニメーション数
					20,			//アニメーションフレーム数
					0,			//カーソルのX最大
					2,			//カーソルのY最大
					0,			//カーソルのX位置
					2,			//カーソルのY位置
					150,		//カーソルのX座標
					100,		//カーソルのY座標
					0.0f,		//X移動サイズ
					100.0f,		//Y移動サイズ
					5,			//移動アニメーションフレーム
					true,		//横ループ
					true,		//縦ループ
					10,			//低速待ちフレーム
					5			//高速待ちフレーム
				);
				//カーソル配置
				m_interFaceLayer->addChild(m_pCursor);
				//カーソル用カウンター初期化
				c_frameCounter = 0;

				//ボタン検知防止
				this->m_spaceKeyDownFlag = true;

				//ボタン押しフラグ
				p_scene = false;

				//PLAYラベルの生成と取り付け
				pLavelArray[2] = cocos2d::Label::createWithTTF("PLAY", FONT_FILE_STARWARS, 62);
				//初期位置の設定
				pLavelArray[2]->setPosition(320.0f, 300.0f);
				//文字色の設定
				pLavelArray[2]->setColor(Color3B(0, 200, 200));
				//レイヤーに取り付け
				m_interFaceLayer->addChild(pLavelArray[2]);

				//PLAYラベルの生成と取り付け
				pLavelArray[1] = cocos2d::Label::createWithTTF("RETURN", FONT_FILE_STARWARS, 62);
				//初期位置の設定
				pLavelArray[1]->setPosition(320.0f, 200.0f);
				//文字色の設定
				pLavelArray[1]->setColor(Color3B(0, 200, 200));
				//レイヤーに取り付け
				m_interFaceLayer->addChild(pLavelArray[1]);


				//ENDラベルの生成と取り付け
				pLavelArray[0] = cocos2d::Label::createWithTTF("END", FONT_FILE_STARWARS, 62);
				//初期位置の設定
				pLavelArray[0]->setPosition(320.0f, 100.0f);
				//文字色の設定
				pLavelArray[0]->setColor(Color3B(0, 200, 200));
				//レイヤーに取り付け
				m_interFaceLayer->addChild(pLavelArray[0]);
			}
			return;
		}

	}
	else {
		//aキーが押されていたら
		if (this->m_spaceKeyDownFlag == true) {
			//aキーが離された
			this->m_spaceKeyDownFlag = false;
		}
	}
	//sキーを押したら
	if (CInputJoystick::m_stage == true) {
		//sキーが離されていたら
		if (this->m_sKeyDownFlag == false) {
			//sキーが押された
			this->m_sKeyDownFlag = true;
			//モードを一時停止に変更
			//this->m_stageMode = STAGE_MODE::END;
			//ボム処理
			if (bomCount == 0 && bom != 0) {
				bomCount = 120;
				//無敵設定
				bom--;
				//エフェクトを表示する
				int index = getFreeIndex(m_pEffects, CEfect::MAX_EFFECT);

				//空いている要素が存在しなければエフェクトの処理は行わない
				if (index != -1) {
					//エフェクトインスタンスの作成
					CEfect* pEfe = this->launchEffect(
						EFFECT_TYPE::BOM,
						320,
						240
					);

					//レイヤーに張り付ける
					m_characterLayer->addChild(pEfe);

					//配列にアドレスを取り付ける
					this->m_pEffects[index] = pEfe;
					//オブジェクトカウント更新
					if (index >= m_pEfectCount) {
						m_pEfectCount = index;
					}
					//爆発効果音
					if (se_flg) {
						int m_bomBgmid = AudioEngine::play2d(SOUND_FILE_BOM);
						AudioEngine::setVolume(m_bomBgmid, SE_VOLUME / 60.0f);
					}

				}
			}
			return;
		}

	}
	else {
		//sキーが押されていたら
		if (this->m_sKeyDownFlag == true) {
			//sキーが離された
			this->m_sKeyDownFlag = false;
		}
	}
	//ボムカウントダウン
	if (bomCount != 0) {
		bomCount--;
	}

	//リプレイ速度
	if (mode != 5) {
		if (mode >= 2) {
			if (CInputJoystick::m_repSpeed2 == true) {
				//4倍速
				mode = 4;
			}
			else if (CInputJoystick::m_repSpeed == true) {
				//2倍速
				mode = 3;
			}
			else {
				//等速
				mode = 2;
			}
		}
	}


}

void CGameMain::inputFunc2() {
	//ボタン押されたら飛ばす
	if (p_scene)
		return;

	//入力フラグ設定
	CInputJoystick::inputFunc(1);

	//zキーを押したら
	if (CInputJoystick::m_shot == true) {
		//zキーが離されていたら
		if (this->m_zKeyDownFlag == false) {
			//zキーが押された
			this->m_zKeyDownFlag = true;
			//カーソルSE
			if (!p_scene) {
				int seid = AudioEngine::play2d(SOUND_FILE_CURSOR_2);
				AudioEngine::setVolume(seid, SE_VOLUME / 100.0f);
			}
			//ボタン押しフラグ有効
			p_scene = true;

			return;
		}

	}
	else {
		//zキーが押されていたら
		if (this->m_zKeyDownFlag == true) {
			//zキーが離された
			this->m_zKeyDownFlag = false;

		}
	}

	//カーソル移動処理
	//カーソルの入力処理
	m_pCursor->inputFunc();

}
void CGameMain::moveFunc() {
	//マップの値の反映処理
	m_pMap->moveFunc();

	// プレイヤーの移動
	m_pPlayerChara->moveFunc();

	//プレイヤーの弾の移動処理
	for (int i = 0; i <= m_pPlayerBulletCount; i++) {
		//NULLが代入されていたら飛ばす
		if (m_pPlayerBullets[i] == NULL)
			continue;

		//移動処理を行う
		//m_pPlayerBullets[i]->m_move.moveByVell();
		m_pPlayerBullets[i]->moveFunc();
	}
	//敵の移動処理
	for (int i = 0; i <= m_pEnemyCount; i++) {
		//NULLが代入されていたら飛ばす
		if (m_pEnemyCharas[i] == NULL)
			continue;

		//移動処理を行う
		m_pEnemyCharas[i]->moveFunc();

		//ボスで倒された場合のエフェクト処理
		if (m_pEnemyCharas[i]->bossflg && m_pEnemyCharas[i]->m_activeFlag == false) {
			
			//透明度処理
			m_pEnemyCharas[i]->setOpacity(255.0f * ((float)m_pEnemyCharas[i]->bossCount / 300.0f));

			//落下処理
			m_pEnemyCharas[i]->m_move.m_posY -= 0.5f;

			//エフェクト処理
			if (m_pEnemyCharas[i]->bossCount % 10 == 0) {
				//エフェクトを表示する
				int index = getFreeIndex(m_pEffects, CEfect::MAX_EFFECT);

				//空いている要素が存在しなければエフェクトの処理は行わない
				if (index != -1) {
					//エフェクトインスタンスの作成
					CEfect* pEfe = this->launchEffect(
						EFFECT_TYPE::EXPLOSION,
						rand() % (int)m_pEnemyCharas[i]->m_chip.size.width -
						(m_pEnemyCharas[i]->m_chip.size.width / 2) +
						m_pEnemyCharas[i]->m_move.m_posX,
						rand() % (int)m_pEnemyCharas[i]->m_chip.size.height -
						(m_pEnemyCharas[i]->m_chip.size.height / 2) +
						m_pEnemyCharas[i]->m_move.m_posY
					);

					//レイヤーに張り付ける
					m_characterLayer->addChild(pEfe);

					//配列にアドレスを取り付ける
					this->m_pEffects[index] = pEfe;
					//オブジェクトカウント更新
					if (index >= m_pEfectCount) {
						m_pEfectCount = index;
					}
					//プレイヤー爆発効果音
					if (se_flg) {
						m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_PLAYER_EXPLOSION);
						AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 120.0f);
					}

				}

			}
			//ボスカウントダウン
			m_pEnemyCharas[i]->bossCount--;
		}
	}

	//敵の弾の移動処理
	for (int i = 0; i <= m_pEnemyBulletCount; i++) {
		//NULLが代入されていたら飛ばす
		if (m_pEnemyBullets[i] == NULL)
			continue;

		//移動処理を行う
		m_pEnemyBullets[i]->moveFunc();
	}

	//エフェクトの移動処理
	for (int i = 0; i <= m_pEfectCount; i++) {
		//NULLが代入されていたら飛ばす
		if (m_pEffects[i] == NULL)
			continue;

		//移動処理を行う
		m_pEffects[i]->moveFunc();
	}

	//アイテムの移動処理
	for (int i = 0; i <= m_pItemCount; i++) {
		//NULLが代入されていたら飛ばす
		if (m_pItems[i] == NULL)
			continue;

		//移動処理を行う
		m_pItems[i]->moveFunc();
	}

	//壁の移動処理
	for (int i = 0; i <= m_pWallCount; i++) {
		//NULLが代入されていたら飛ばす
		if (m_pWalls[i] == NULL)
			continue;

		//移動処理を行う
		m_pWalls[i]->moveFunc();
	}
}
void CGameMain::applyFunc() {
	//マップの値の反映処理
	m_pMap->applyFunc();

	m_pPlayerChara->applyFunc();
	//プレイヤーの弾の値の繁栄処理
	for (int i = 0; i <= m_pPlayerBulletCount; i++) {
		//NULLが代入されていたら飛ばす
		if (m_pPlayerBullets[i] == NULL)
			continue;

		//値の反映を行う
		m_pPlayerBullets[i]->applyFunc();
	}

	//敵の反映処理
	for (int i = 0; i <= m_pEnemyCount; i++) {
		//NULLが代入されていたら飛ばす
		if (m_pEnemyCharas[i] == NULL)
			continue;

		//移動処理を行う
		m_pEnemyCharas[i]->applyFunc();
		//ボス終了時移動処理
		if (m_pEnemyCharas[i]->bossflg && m_pEnemyCharas[i]->m_activeFlag == false) {
			m_pEnemyCharas[i]->setPosition(m_pEnemyCharas[i]->m_move.m_posX + rand() % 8 - 4,
				m_pEnemyCharas[i]->m_move.m_posY + rand() % 8 - 4);
		}
	}

	//敵の弾の反映処理
	for (int i = 0; i <= m_pEnemyBulletCount; i++) {
		//NULLが代入されていたら飛ばす
		if (m_pEnemyBullets[i] == NULL)
			continue;

		//移動処理を行う
		m_pEnemyBullets[i]->applyFunc();
	}

	//エフェクトの反映処理
	for (int i = 0; i <= m_pEfectCount; i++) {
		//NULLが代入されていたら飛ばす
		if (m_pEffects[i] == NULL)
			continue;

		//移動処理を行う
		m_pEffects[i]->applyFunc();
	}

	//アイテムの反映処理
	for (int i = 0; i <= m_pItemCount; i++) {
		//NULLが代入されていたら飛ばす
		if (m_pItems[i] == NULL)
			continue;

		//移動処理を行う
		m_pItems[i]->applyFunc();
	}

	//壁の移動処理
	for (int i = 0; i <= m_pWallCount; i++) {
		//NULLが代入されていたら飛ばす
		if (m_pWalls[i] == NULL)
			continue;

		//移動処理を行う
		m_pWalls[i]->applyFunc();
	}
}

void CGameMain::animationFunc() {
	m_pPlayerChara->animationFunc();

	//プレイヤー弾アニメーション
	for (int i = 0; i <= m_pPlayerBulletCount; i++) {
		//要素がNULLなら飛ばす
		if (m_pPlayerBullets[i] == NULL)
			continue;

		//プレイヤー弾のアニメーション
		m_pPlayerBullets[i]->animationFunc();

	}
	//敵アニメーション
	for (int i = 0; i <= m_pEnemyCount; i++) {
		//要素がNULLなら飛ばす
		if (m_pEnemyCharas[i] == NULL)
			continue;

		//敵のアニメーション
		m_pEnemyCharas[i]->animationFunc();
	}
	//敵弾アニメーション
	for (int i = 0; i <= m_pEnemyBulletCount; i++) {
		//要素がNULLなら飛ばす
		if (m_pEnemyBullets[i] == NULL)
			continue;

		//敵のアニメーション
		m_pEnemyBullets[i]->animationFunc();
	}

	//エフェクトアニメーション
	for (int i = 0; i <= m_pEfectCount; i++) {
		//要素がNULLなら飛ばす
		if (m_pEffects[i] == NULL)
			continue;

		//敵のアニメーション
		m_pEffects[i]->animationFunc();
	}

	//アイテムアニメーション
	for (int i = 0; i <= m_pItemCount; i++) {
		//NULLが代入されていたら飛ばす
		if (m_pItems[i] == NULL)
			continue;

		//アイテムのアニメーション
		m_pItems[i]->animationFunc();
	}
}

void CGameMain::endOfScreen() {
	//プレイヤーの画面端判定処理
	m_pPlayerChara->endOfScreen();

	//プレイヤーの弾の画面外判定処理
	for (int i = 0; i <= m_pPlayerBulletCount; i++) {
		//要素がNULLなら飛ばす
		if (m_pPlayerBullets[i] == NULL)
			continue;

		//弾画像の左端の座標が画面右端の座標より大きくなったら
		m_pPlayerBullets[i]->endOfScreen();
	}
	//敵の画面外判定処理
	for (int i = 0; i <= m_pEnemyCount; i++) {
		//要素がNULLなら飛ばす
		if (m_pEnemyCharas[i] == NULL)
			continue;

		//敵タイプがボスなら飛ばす
		if (m_pEnemyCharas[i]->bossflg)
			continue;

		//弾画像の左端の座標が画面右端の座標より大きくなったら
		m_pEnemyCharas[i]->endOfScreen();
	}

	//敵の弾の画面外判定処理
	for (int i = 0; i <= m_pEnemyBulletCount; i++) {
		//要素がNULLなら飛ばす
		if (m_pEnemyBullets[i] == NULL)
			continue;

		//弾画像の左端の座標が画面右端の座標より大きくなったら
		m_pEnemyBullets[i]->endOfScreen();
	}

	//アイテムの画面外判定処理
	for (int i = 0; i <= m_pItemCount; i++) {
		//NULLが代入されていたら飛ばす
		if (m_pItems[i] == NULL)
			continue;

		//アイテムの左端の座標が画面右端の座標より大きくなったら
		m_pItems[i]->endOfScreen();
	}

	//壁の画面外判定処理
	for (int i = 0; i <= m_pWallCount; i++) {
		//NULLが代入されていたら飛ばす
		if (m_pWalls[i] == NULL)
			continue;

		//壁の左端の座標が画面右端の座標より大きくなったら
		m_pWalls[i]->endOfScreen();
	}

	//エフェクトの画面外判定処理
	for (int i = 0; i <= m_pEfectCount; i++) {
		//NULLが代入されていたら飛ばす
		if (m_pEffects[i] == NULL)
			continue;

		//壁の左端の座標が画面右端の座標より大きくなったら
		m_pEffects[i]->endOfScreen();
	}
}

/**
*@desc 敵の出撃
*@param 参照する敵管理データのアドレス
*/
CEnemyCharacter* CGameMain::launchEnemy(CEnemyLaunchData* pEneLaunchData) {
	//敵の生成
	CEnemyCharacter* pEne = CEnemyCharacter::create();
	switch (pEneLaunchData->m_type) {
		//タイプAの敵
	case ENEMY_TYPE::TYPE_A:
		//敵の設定
		pEne->setTexture(IMAGE_FILE_CHARACTER_2);

		//切り取る矩形
		pEne->m_chip = CChip(0, 21, 40, 40);

		//切り取る矩形の設定
		pEne->setTextureRect(pEne->m_chip);

		//進行方向の設定
		pEne->direction = pEneLaunchData->direction;

		//進行方向が右なら画像反転
		if (pEne->direction == false) {
			pEne->setScaleX(-1.0f);
		}

		//移動データに初期位置の設定(チップの幅サイズの半分だけずらす)
		pEne->m_move.setPos(pEneLaunchData->m_posX, pEneLaunchData->m_posY);

		//移動データに初期速度の設定(X座標に-4ずつ)
		if (pEneLaunchData->action.size() != 0) {
			pEne->m_move.setVel(pEneLaunchData->action[0].x - WALL_SPEED, pEneLaunchData->action[0].y);
		}
		else {
			pEne->m_move.setVel(-WALL_SPEED, 0);
		}


		//アニメーションデータの初期化
		pEne->m_anime.set(10, 4);

		//衝突判定用データの初期化
		pEne->m_body.set(
			-16,
			16,
			16,
			-16
		);

		//発射する弾のタイプの設定
		//通常弾
		pEne->m_bulletType = BULLET_TYPE::ENEMY_NORMAL;
		//ステータスの初期化
		pEne->m_status.set(30, 30, 1, 100);

		//行動タイプの設定
		pEne->m_actionType = pEneLaunchData->m_actionType;

		break;
	case ENEMY_TYPE::TYPE_B:
		//敵の設定
		pEne->setTexture(IMAGE_FILE_CHARACTER_2);

		//切り取る矩形
		pEne->m_chip = CChip(0, 61, 40, 40);

		//切り取る矩形の設定
		pEne->setTextureRect(pEne->m_chip);

		//進行方向の設定
		pEne->direction = pEneLaunchData->direction;

		//進行方向が右なら画像反転
		if (pEne->direction == false) {
			pEne->setScaleX(-1.0f);
		}

		//移動データに初期位置の設定(チップの幅サイズの半分だけずらす)
		pEne->m_move.setPos(pEneLaunchData->m_posX, pEneLaunchData->m_posY);

		//移動データに初期速度の設定(X座標に-4ずつ)
		if (pEneLaunchData->action.size() != 0) {
			pEne->m_move.setVel(pEneLaunchData->action[0].x - WALL_SPEED, pEneLaunchData->action[0].y);
		}
		else {
			pEne->m_move.setVel(-WALL_SPEED, 0);
		}


		//アニメーションデータの初期化
		pEne->m_anime.set(10, 4);

		//衝突判定用データの初期化
		pEne->m_body.set(
			-16,
			16,
			16,
			-16
		);

		//発射する弾のタイプの設定
		//通常弾
		pEne->m_bulletType = BULLET_TYPE::ENEMY_FAN;

		//ステータスの初期化
		pEne->m_status.set(40, 40, 1, 500);

		//行動タイプの設定
		pEne->m_actionType = pEneLaunchData->m_actionType;

		break;
	case ENEMY_TYPE::TYPE_C:
		//敵の設定
		pEne->setTexture(IMAGE_FILE_CHARACTER_2);

		//切り取る矩形
		pEne->m_chip = CChip(0, 101, 40, 40);

		//切り取る矩形の設定
		pEne->setTextureRect(pEne->m_chip);

		//進行方向の設定
		pEne->direction = pEneLaunchData->direction;

		//進行方向が右なら画像反転
		if (pEne->direction == false) {
			pEne->setScaleX(-1.0f);
		}

		//設置方向
		pEne->setRotation(pEneLaunchData->install * 90);

		//移動データに初期位置の設定(チップの幅サイズの半分だけずらす)
		pEne->m_move.setPos(pEneLaunchData->m_posX, pEneLaunchData->m_posY);

		//移動データに初期速度の設定(X座標に-4ずつ)
		if (pEneLaunchData->action.size() != 0) {
			pEne->m_move.setVel(pEneLaunchData->action[0].x - WALL_SPEED, pEneLaunchData->action[0].y);
		}
		else {
			pEne->m_move.setVel(-WALL_SPEED, 0);
		}


		//アニメーションデータの初期化
		pEne->m_anime.set(10, 1);

		//衝突判定用データの初期化
		pEne->m_body.set(
			-16,
			10,
			16,
			-16
		);

		//発射する弾のタイプの設定
		//通常弾
		pEne->m_bulletType = BULLET_TYPE::ENEMY_AIMING;
		//ステータスの初期化
		pEne->m_status.set(30, 30, 1, 100);

		//行動タイプの設定
		pEne->m_actionType = pEneLaunchData->m_actionType;

		//砲身の生成と取り付け
		pEne->m_pChr = Sprite::create(IMAGE_FILE_CHARACTER_2);
		//初期位置の設定
		pEne->m_pChr->setPosition(20.0f, 20.0f);

		//切り取る矩形の設定
		pEne->m_pChr->setTextureRect(CChip(40, 100, 40, 40));

		//レイヤーに取り付け
		pEne->addChild(pEne->m_pChr);
		
		break;
		//タイプAの敵
	case ENEMY_TYPE::TYPE_D:
		//敵の設定
		pEne->setTexture(IMAGE_FILE_CHARACTER_2);

		//切り取る矩形
		pEne->m_chip = CChip(0, 141, 40, 40);

		//切り取る矩形の設定
		pEne->setTextureRect(pEne->m_chip);

		//進行方向の設定
		pEne->direction = pEneLaunchData->direction;

		//進行方向が右なら画像反転
		if (pEne->direction == false) {
			pEne->setScaleX(-1.0f);
		}

		//移動データに初期位置の設定(チップの幅サイズの半分だけずらす)
		pEne->m_move.setPos(pEneLaunchData->m_posX, pEneLaunchData->m_posY);

		//移動データに初期速度の設定(X座標に-4ずつ)
		if (pEneLaunchData->action.size() != 0) {
			pEne->m_move.setVel(pEneLaunchData->action[0].x - WALL_SPEED, pEneLaunchData->action[0].y);
		}
		else {
			pEne->m_move.setVel(-WALL_SPEED, 0);
		}


		//アニメーションデータの初期化
		pEne->m_anime.set(10, 4);

		//衝突判定用データの初期化
		pEne->m_body.set(
			-16,
			16,
			16,
			-16
		);

		//発射する弾のタイプの設定
		//通常弾
		pEne->m_bulletType = BULLET_TYPE::ENEMY_NORMAL;
		//ステータスの初期化
		pEne->m_status.set(20, 20, 1, 50);

		//行動タイプの設定
		pEne->m_actionType = pEneLaunchData->m_actionType;

		break;
	case ENEMY_TYPE::TYPE_E:
		//敵の設定
		pEne->setTexture(IMAGE_FILE_CHARACTER_2);

		//切り取る矩形
		pEne->m_chip = CChip(0, 181, 40, 40);

		//切り取る矩形の設定
		pEne->setTextureRect(pEne->m_chip);

		//進行方向の設定
		pEne->direction = pEneLaunchData->direction;

		//進行方向が右なら画像反転
		if (pEne->direction == false) {
			pEne->setScaleX(-1.0f);
		}

		//移動データに初期位置の設定(チップの幅サイズの半分だけずらす)
		pEne->m_move.setPos(pEneLaunchData->m_posX, pEneLaunchData->m_posY);

		//移動データに初期速度の設定(X座標に-4ずつ)
		if (pEneLaunchData->action.size() != 0) {
			pEne->m_move.setVel(pEneLaunchData->action[0].x - WALL_SPEED, pEneLaunchData->action[0].y);
		}
		else {
			pEne->m_move.setVel(-WALL_SPEED, 0);
		}


		//アニメーションデータの初期化
		pEne->m_anime.set(10, 4);

		//衝突判定用データの初期化
		pEne->m_body.set(
			-16,
			16,
			16,
			-16
		);

		//発射する弾のタイプの設定
		//通常弾
		pEne->m_bulletType = BULLET_TYPE::ENEMY_2WAY;

		//ステータスの初期化
		pEne->m_status.set(40, 40, 1, 500);

		//行動タイプの設定
		pEne->m_actionType = pEneLaunchData->m_actionType;

		break;
	case ENEMY_TYPE::TYPE_BOSS_1:
		//ボスフラグ有効
		pEne->bossflg = true;

		//敵の設定
		pEne->setTexture(IMAGE_FILE_BOSS_1);

		//切り取る矩形
		pEne->m_chip = CChip(0, 0, 200, 200);

		//切り取る矩形の設定
		pEne->setTextureRect(pEne->m_chip);

		//進行方向の設定
		pEne->direction = pEneLaunchData->direction;

		//進行方向が右なら画像反転
		if (pEne->direction == false) {
			pEne->setScaleX(-1.0f);
		}

		//移動データに初期位置の設定(チップの幅サイズの半分だけずらす)
		pEne->m_move.setPos(pEneLaunchData->m_posX, pEneLaunchData->m_posY);

		//移動データに初期速度の設定(X座標に-4ずつ)
		if (pEneLaunchData->action.size() != 0) {
			pEne->m_move.setVel(pEneLaunchData->action[0].x - WALL_SPEED, pEneLaunchData->action[0].y);
		}
		else {
			pEne->m_move.setVel(-WALL_SPEED, 0);
		}


		//アニメーションデータの初期化
		pEne->m_anime.set(10, 0, true);

		//衝突判定用データの初期化
		pEne->m_body.set(
			0,
			40,
			70,
			-40
		);

		//発射する弾のタイプの設定
		//通常弾
		switch (CGameMain::m_stageNo) {
		case 1:
			pEne->m_bulletType = BULLET_TYPE::ENEMY_NORMAL;
			break;
		case 2:
			pEne->m_bulletType = BULLET_TYPE::ENEMY_FAN;
			break;
		case 3:
			pEne->m_bulletType = BULLET_TYPE::ENEMY_AIMING;
			break;
		default:
			pEne->m_bulletType = BULLET_TYPE::ENEMY_NORMAL;
			break;
		}

		//ステータスの初期化
		pEne->m_status.set(1000, 1000, 1, 10000);

		//行動タイプの設定
		pEne->m_actionType = pEneLaunchData->m_actionType;
		break;
	default:
		break;
	}

	//敵のタイプを設定
	pEne->e_enemyType = pEneLaunchData->m_type;

	//有効フラグにtrueを入れる
	pEne->m_activeFlag = true;

	//アイテム設定
	pEne->m_item = pEneLaunchData->m_item;
	/*
	if (rand() % 4 == 0) {
		pEne->m_item = (ITEM_TYPE)(rand() % 11);
	}
	else {
		pEne->m_item = (ITEM_TYPE)-1;
	}
	*/
	

	//行動データの設定
	pEne->action = pEneLaunchData->action;
	return pEne;
}


void CGameMain::checkActiveFlagAndRemove() {

	//オブジェクトカウント用
	int count = 0;

	for (int i = 0; i <= m_pPlayerBulletCount; i++) {
		//要素がNULLなら飛ばす
		if (m_pPlayerBullets[i] == NULL)
			continue;
		if (m_pPlayerBullets[i]->m_activeFlag == false) {
			//レイヤーから取り外す
			m_pPlayerBullets[i]->removeFromParent();

			//配列情報にNULLを代入
			m_pPlayerBullets[i] = NULL;
		}
		else {
			//最後のアクティブなインデックスを記録
			count = i;
		}
	}
	//削除された数を反映させる
	m_pPlayerBulletCount = count;
	//各種カウントリセット
	count = 0;

	//敵のレイヤーからの取り外し処理
	for (int i = 0; i <= m_pEnemyCount; i++) {
		//要素がNULLなら飛ばす
		if (m_pEnemyCharas[i] == NULL)
			continue;

		if (m_pEnemyCharas[i]->m_activeFlag == false) {
			//ボスの場合
			if (m_pEnemyCharas[i]->bossflg) {
				//カウント0で取り外し
				if (m_pEnemyCharas[i]->bossCount == 0) {
					//レイヤーから取り外す
					m_pEnemyCharas[i]->removeFromParent();

					//配列情報にNULLを代入
					m_pEnemyCharas[i] = NULL;

					//ステージクリア処理
					//終了フレームを設定する
					m_clearFrame = m_frameCounter + 300;
					if (se_flg) {
						int m_clearBgmid = AudioEngine::play2d(SOUND_FILE_STAGE_CLEAR);
						AudioEngine::setVolume(m_clearBgmid, SE_VOLUME / 100.0f);
					}


				}
				else {
					//最後のアクティブなインデックスを記録
					count = i;
				}
			}
			else {
				//通常の場合
				//レイヤーから取り外す
				m_pEnemyCharas[i]->removeFromParent();

				//配列情報にNULLを代入
				m_pEnemyCharas[i] = NULL;
			}
		}
		else {
			//最後のアクティブなインデックスを記録
			count = i;
		}
	}
	//削除された数を反映させる
	m_pEnemyCount = count;
	//各種カウントリセット
	count = 0;

	//敵の弾のレイヤーからの取り外し処理
	for (int i = 0; i <= m_pEnemyBulletCount; i++) {
		//要素がNULLなら飛ばす
		if (m_pEnemyBullets[i] == NULL)
			continue;

		if (m_pEnemyBullets[i]->m_activeFlag == false) {
			//レイヤーから取り外す
			m_pEnemyBullets[i]->removeFromParent();

			//配列情報にNULLを代入
			m_pEnemyBullets[i] = NULL;
		}
		else {
			//最後のアクティブなインデックスを記録
			count = i;
		}
	}
	//削除された数を反映させる
	m_pEnemyBulletCount = count;
	//各種カウントリセット
	count = 0;

	//エフェクトのレイヤーからの取り外し処理
	for (int i = 0; i <= m_pEfectCount; i++) {
		//要素がNULLなら飛ばす
		if (m_pEffects[i] == NULL)
			continue;

		if (m_pEffects[i]->m_activeFlag == false) {
			//レイヤーから取り外す
			m_pEffects[i]->removeFromParent();

			//配列情報にNULLを代入
			m_pEffects[i] = NULL;
		}
		else {
			//最後のアクティブなインデックスを記録
			count = i;
		}
	}
	//最大インデックスを反映させる
	m_pEfectCount = count;
	//各種カウントリセット
	count = 0;

	//アイテムのレイヤーからの取り外し処理
	for (int i = 0; i <= m_pItemCount; i++) {
		//要素がNULLなら飛ばす
		if (m_pItems[i] == NULL)
			continue;

		if (m_pItems[i]->m_activeFlag == false) {
			//レイヤーから取り外す
			m_pItems[i]->removeFromParent();

			//配列情報にNULLを代入
			m_pItems[i] = NULL;
		}
		else {
			//最後のアクティブなインデックスを記録
			count = i;
		}
	}
	//削除された数を反映させる
	m_pItemCount = count;
	//各種カウントリセット
	count = 0;

	//壁のレイヤーからの取り外し処理
	for (int i = 0; i <= m_pWallCount; i++) {
		//要素がNULLなら飛ばす
		if (m_pWalls[i] == NULL)
			continue;

		if (m_pWalls[i]->m_activeFlag == false) {
			//レイヤーから取り外す
			m_pWalls[i]->removeFromParent();

			//配列情報にNULLを代入
			m_pWalls[i] = NULL;
		}
		else {
			//最後のアクティブなインデックスを記録
			count = i;
		}
	}
	//削除された数を反映させる
	m_pWallCount = count;
}

void CGameMain::shotEnemyBullet() {
	for (int i = 0; i <= m_pEnemyCount; i++) {

		//NULLが代入されていたら飛ばす
		if (m_pEnemyCharas[i] == NULL)
			continue;

		//死んでいたら飛ばす
		if (m_pEnemyCharas[i]->m_activeFlag == false)
			continue;

		//弾発射フラグがfalseなら飛ばす
		if (m_pEnemyCharas[i]->m_shotFlag == false) {
			continue;
		}

		//敵が持っている敵の弾のタイプを判定して弾を発射させる
		switch (m_pEnemyCharas[i]->m_bulletType) {
			//通常弾
		case BULLET_TYPE::ENEMY_NORMAL:
		{
			//配列のNULLが入っている添え字番号を取得
			int index = getFreeIndex(m_pEnemyBullets, CBullet::MAX_BULLET);

			//空いている要素が存在しなければ弾の発射処理は行わない
			if (index == -1) {
				return;
			}
			//進行方向確認
			int direction = m_pEnemyCharas[i]->direction ? 1 : -1;
			//プレイヤーの弾の発射
			CBullet* pBul = m_pEnemyCharas[i]->shotBullet(BULLET_TYPE::ENEMY_NORMAL,
				(direction == 1 ? -(m_pEnemyCharas[i]->m_body.m_left) : m_pEnemyCharas[i]->m_body.m_right) * direction,
				0,
				-8 * direction * m_shotVel[GAME_MODE],
				0);
			//NULLなら飛ばす
			if (pBul == NULL)
				continue;

			//ステータスの初期化
			pBul->m_status.set(1, 1, 10 - m_shotAttack[GAME_MODE], 0);

			m_characterLayer->addChild(pBul);

			//配列にアドレスを取り付ける
			this->m_pEnemyBullets[index] = pBul;
			//オブジェクトカウント更新
			if (index >= m_pEnemyBulletCount) {
				m_pEnemyBulletCount = index;
			}
		}
		break;

		//自機狙い弾(プレイヤー狙い弾)
		case BULLET_TYPE::ENEMY_AIMING:
		{

			//配列のNULLが入っている添え字番号を取得
			int index = getFreeIndex(m_pEnemyBullets, CBullet::MAX_BULLET);

			//空いている要素が存在しなければ弾の発射処理は行わない
			if (index == -1) {
				return;
			}

			//プレイヤーの位置を取得
			float playerPosX = m_pPlayerChara->m_move.m_posX;
			float playerPosY = m_pPlayerChara->m_move.m_posY;

			//敵の位置を取得
			float enePosX = m_pEnemyCharas[i]->m_move.m_posX;
			float enePosY = m_pEnemyCharas[i]->m_move.m_posY;

			//敵からプレイヤーまでのベクトルを計算
			float vecX = playerPosX - enePosX;
			float vecY = playerPosY - enePosY;

			//ベクトルの長さを求める
			float len = sqrt(vecX * vecX + vecY * vecY);

			//１フレーム単位のベクトルを計算する。つまり速度が１の時の速度を求める
			float velX = vecX / len;
			float velY = vecY / len;

			//速さを計算する
			float vel = m_pEnemyCharas[i]->bossflg ? 10.0f : 5.0f * m_shotVel[GAME_MODE];
			int pos = m_pEnemyCharas[i]->bossflg ? 0 : 4;
			velX = velX * vel;
			velY = velY * vel;

			//プレイヤーの弾の発射
			CBullet* pBul = m_pEnemyCharas[i]->shotBullet(BULLET_TYPE::ENEMY_AIMING,
				velX * pos,
				velY * pos,
				velX,
				velY);
			//NULLなら飛ばす
			if (pBul == NULL)
				continue;

			//ステータスの初期化
			pBul->m_status.set(1, 1, 10 - m_shotAttack[GAME_MODE], 0);

			m_characterLayer->addChild(pBul);

			//配列にアドレスを取り付ける
			this->m_pEnemyBullets[index] = pBul;
			//オブジェクトカウント更新
			if (index >= m_pEnemyBulletCount) {
				m_pEnemyBulletCount = index;
			}
		}
		break;
		case BULLET_TYPE::ENEMY_FAN:
		{
			for (int j = 0; j < 7; j++) {
				//配列のNULLが入っている添え字番号を取得
				int index = getFreeIndex(m_pEnemyBullets, CBullet::MAX_BULLET);

				//空いている要素が存在しなければ弾の発射処理は行わない
				if (index == -1) {
					return;
				}

				//角度
				float angle = j * 30.0f + 90.0f;

				//角度分二次ベクトルを取得
				float velX = cos(angle * M_PI / 180.0f) * 6.0f * m_shotVel[GAME_MODE];
				float velY = sin(angle * M_PI / 180.0f) * 6.0f * m_shotVel[GAME_MODE];
				//進行方向確認
				int direction = m_pEnemyCharas[i]->direction ? 1 : -1;
				CBullet* pBul = m_pEnemyCharas[i]->shotBullet(BULLET_TYPE::ENEMY_FAN,
					(direction == 1 ? -(m_pEnemyCharas[i]->m_body.m_left) : m_pEnemyCharas[i]->m_body.m_right) * direction,
					0.0f,
					velX * direction,
					velY);


				//NULLなら飛ばす
				if (pBul == NULL)
					return;

				//ステータスの初期化
				pBul->m_status.set(1, 1, 10 - m_shotAttack[GAME_MODE], 0);

				//レイヤーに張り付ける
				m_characterLayer->addChild(pBul);

				//配列にアドレスを張り付ける
				this->m_pEnemyBullets[index] = pBul;
				//オブジェクトカウント更新
				if (index >= m_pEnemyBulletCount) {
					m_pEnemyBulletCount = index;
				}
			}
		}
		break;
		//前後弾
		case BULLET_TYPE::ENEMY_2WAY:
		{
			for (int j = 0; j < 2; j++) {
				//配列のNULLが入っている添え字番号を取得
				int index = getFreeIndex(m_pEnemyBullets, CBullet::MAX_BULLET);

				//空いている要素が存在しなければ弾の発射処理は行わない
				if (index == -1) {
					return;
				}

				//進行方向確認
				int direction = j == 0 ? 1 : -1;
				CBullet* pBul = m_pEnemyCharas[i]->shotBullet(BULLET_TYPE::ENEMY_FAN,
					(direction == 1 ? -(m_pEnemyCharas[i]->m_body.m_left) : m_pEnemyCharas[i]->m_body.m_right) * direction,
					0.0f,
					-8 * direction * m_shotVel[GAME_MODE],
					0);


				//NULLなら飛ばす
				if (pBul == NULL)
					return;

				//ステータスの初期化
				pBul->m_status.set(1, 1, 10 - m_shotAttack[GAME_MODE], 0);

				//レイヤーに張り付ける
				m_characterLayer->addChild(pBul);

				//配列にアドレスを張り付ける
				this->m_pEnemyBullets[index] = pBul;
				//オブジェクトカウント更新
				if (index >= m_pEnemyBulletCount) {
					m_pEnemyBulletCount = index;
				}
			}

		}
		break;
		default:
			break;
		}
		//発射フラグを取り下げる
		m_pEnemyCharas[i]->m_shotFlag = false;

	}
}

/*
*@desc	プレイヤーの弾の発射
*@param	弾タイプ
*/
void CGameMain::shotPlayerBullet(BULLET_TYPE type) {
	//弾発射用カウンターが0以下なら弾の発射を行う
	if (m_pPlayerChara->m_shotCounter <= 0) {
		//zが押された
		switch (type) {
		case BULLET_TYPE::PLAYER_NORMAL:
		{
			//配列のNULLが入っている添え字番号を取得
			int index = getFreeIndex(m_pPlayerBullets, CBullet::MAX_BULLET);

			//空いてる要素が存在しなければ弾の発射処理は行わない
			if (index == -1) {
				return;
			}

			CBullet* pBul = m_pPlayerChara->shotBullet(BULLET_TYPE::PLAYER_NORMAL,
				m_pPlayerChara->m_chip.size.width * 0.5f, 0.0f, m_pPlayerChara->m_shotVel, 0.0f);

			//NULLなら飛ばす
			if (pBul == NULL)
				return;

			//ステータスの初期化
			pBul->m_status.set(1, 1, m_pPlayerChara->m_shotPower, 0);

			//レイヤーに張り付ける
			m_characterLayer->addChild(pBul);

			//配列にアドレスを張り付ける
			this->m_pPlayerBullets[index] = pBul;
			//オブジェクトカウント更新
			if (index >= m_pPlayerBulletCount) {
				m_pPlayerBulletCount = index;
			}
		}
		break;
		case BULLET_TYPE::PLAYER_EXPLOSION:
		{
			//配列のNULLが入っている添え字番号を取得
			int index = getFreeIndex(m_pPlayerBullets, CBullet::MAX_BULLET);

			//空いてる要素が存在しなければ弾の発射処理は行わない
			if (index == -1) {
				return;
			}

			CBullet* pBul = m_pPlayerChara->shotBullet(BULLET_TYPE::PLAYER_EXPLOSION,
				m_pPlayerChara->m_chip.size.width * 0.5f, 0.0f, m_pPlayerChara->m_shotVel, 0.0f);

			//NULLなら飛ばす
			if (pBul == NULL)
				return;

			//ステータスの初期化
			pBul->m_status.set(1, 1, m_pPlayerChara->m_shotPower, 0);

			//レイヤーに張り付ける
			m_characterLayer->addChild(pBul);

			//配列にアドレスを張り付ける
			this->m_pPlayerBullets[index] = pBul;
			//オブジェクトカウント更新
			if (index >= m_pPlayerBulletCount) {
				m_pPlayerBulletCount = index;
			}
		}
		break;
		case BULLET_TYPE::PLAYER_BACK:
		{
			for (int i = 0; i < 2; i++) {
				//配列のNULLが入っている添え字番号を取得
				int index = getFreeIndex(m_pPlayerBullets, CBullet::MAX_BULLET);

				//空いてる要素が存在しなければ弾の発射処理は行わない
				if (index == -1) {
					return;
				}

				float fixX = m_pPlayerChara->m_chip.size.width * 0.5f;
				fixX = (i == 0) ? fixX : fixX * -1;
				float velX = (i == 0) ? m_pPlayerChara->m_shotVel : -m_pPlayerChara->m_shotVel;

				CBullet* pBul = m_pPlayerChara->shotBullet(BULLET_TYPE::PLAYER_NORMAL, fixX, 0.0f, velX, 0.0f);

				//NULLなら飛ばす
				if (pBul == NULL)
					return;

				//ステータスの初期化
				pBul->m_status.set(1, 1, m_pPlayerChara->m_shotPower, 0);

				//レイヤーに張り付ける
				m_characterLayer->addChild(pBul);

				//配列にアドレスを張り付ける
				this->m_pPlayerBullets[index] = pBul;
				//オブジェクトカウント更新
				if (index >= m_pPlayerBulletCount) {
					m_pPlayerBulletCount = index;
				}
			}
		}
		break;
		case BULLET_TYPE::PLAYER_LASER:
		{

			//レーザーフラグが無効の場合レーザー処理開始
			if (laserFlg == false) {
				laserFlg = true;
				laserCounter = this->m_frameCounter;
				cocos2d::log("laser on");
			}
			else {
				return;
			}

			//配列のNULLが入っている添え字番号を取得
			int index = getFreeIndex(m_pPlayerBullets, CBullet::MAX_BULLET);

			//空いてる要素が存在しなければ弾の発射処理は行わない
			if (index == -1) {
				return;
			}

			//プレイヤーの弾の生成
			CBullet* pBul = CBullet::create();
			//画像の設定
			pBul->setTexture(IMAGE_FILE_LASER);
			//切り取る矩形
			pBul->m_chip = CChip(0, 0, 640, 1);
			pBul->setTextureRect(pBul->m_chip);
			//アンカーポイントを左に設定
			pBul->setAnchorPoint(Vec2(0, 0));
			//移動データに初期位置の設定
			pBul->m_move.setPos(m_pPlayerChara->m_move.m_posX + 15.0f, m_pPlayerChara->m_move.m_posY);

			//初期位置を判定
			pBul->setPosition(pBul->m_move.m_posX, pBul->m_move.m_posY);

			//有効フラグにtrueを入れる
			pBul->m_activeFlag = true;

			//弾タイプの設定
			pBul->m_bulletType = BULLET_TYPE::PLAYER_LASER;

			//アニメーションデータの初期化
			pBul->m_anime.set(1, 1, false);

			//衝突判定用データの初期化
			pBul->m_body.set(0, 1, 640, 0);

			//プレイヤー移動データを記録
			pBul->m_pmove = &m_pPlayerChara->m_move;

			//NULLなら飛ばす
			if (pBul == NULL)
				return;

			//ステータスの初期化
			pBul->m_status.set(1, 1, m_pPlayerChara->m_shotPower, 0);

			//レイヤーに張り付ける
			m_characterLayer->addChild(pBul);

			//配列にアドレスを張り付ける
			this->m_pPlayerBullets[index] = pBul;
			//オブジェクトカウント更新
			if (index >= m_pPlayerBulletCount) {
				m_pPlayerBulletCount = index;
			}
		}
		break;
		case BULLET_TYPE::PLAYER_INDUCTION:

		{
			//配列のNULLが入っている添え字番号を取得
			int index = getFreeIndex(m_pPlayerBullets, CBullet::MAX_BULLET);

			//空いてる要素が存在しなければ弾の発射処理は行わない
			if (index == -1) {
				return;
			}

			//移動角度
			float rotation = 0;
			//移動距離
			float vel = m_pPlayerChara->m_shotVel;

			CBullet* pBul = m_pPlayerChara->shotBullet(BULLET_TYPE::PLAYER_INDUCTION,
				m_pPlayerChara->m_chip.size.width * 0.5f, 0.0f, vel, 0.0f);

			//NULLなら飛ばす
			if (pBul == NULL)
				return;

			//ステータスの初期化
			pBul->m_status.set(1, 1, m_pPlayerChara->m_shotPower, 0);

			//レイヤーに張り付ける
			m_characterLayer->addChild(pBul);

			//モードを索敵にする
			pBul->mode = true;

			//回転角度
			pBul->rotation = rotation;

			//回転角度量
			pBul->param = m_pPlayerChara->m_shotParam;

			//移動距離
			pBul->vel = vel;

			//配列にアドレスを張り付ける
			this->m_pPlayerBullets[index] = pBul;
			//オブジェクトカウント更新
			if (index >= m_pPlayerBulletCount) {
				m_pPlayerBulletCount = index;
			}
		}
		break;
		case BULLET_TYPE::PLAYER_MULTIPLE:
		{
			for (int i = 0; i < this->pweponParam[weponSelect][pweponLevel[weponSelect]]; i++) {
				//配列のNULLが入っている添え字番号を取得
				int index = getFreeIndex(m_pPlayerBullets, CBullet::MAX_BULLET);

				//空いてる要素が存在しなければ弾の発射処理は行わない
				if (index == -1) {
					return;
				}

				//角度
				float angle = i * 5.0f - (5.0f * (this->pweponParam[weponSelect][pweponLevel[weponSelect]] - 1) / 2);
				//移動距離
				float vel = m_pPlayerChara->m_shotVel;

				//角度分二次ベクトルを取得
				float velX = cos(angle * M_PI / 180.0f) * vel;
				float velY = sin(angle * M_PI / 180.0f) * vel;

				CBullet* pBul = m_pPlayerChara->shotBullet(BULLET_TYPE::PLAYER_NORMAL,
					m_pPlayerChara->m_chip.size.width * 0.5f, 0.0f, velX, velY);

				//NULLなら飛ばす
				if (pBul == NULL)
					return;

				//ステータスの初期化
				pBul->m_status.set(1, 1, m_pPlayerChara->m_shotPower, 0);

				//レイヤーに張り付ける
				m_characterLayer->addChild(pBul);

				//配列にアドレスを張り付ける
				this->m_pPlayerBullets[index] = pBul;
				//オブジェクトカウント更新
				if (index >= m_pPlayerBulletCount) {
					m_pPlayerBulletCount = index;
				}
			}
		}
		break;
		case BULLET_TYPE::PLAYER_2WAY:
		{
			for (int i = 0; i < 2; i++) {
				//配列のNULLが入っている添え字番号を取得
				int index = getFreeIndex(m_pPlayerBullets, CBullet::MAX_BULLET);

				//空いてる要素が存在しなければ弾の発射処理は行わない
				if (index == -1) {
					return;
				}

				float fixX = (i == 0) ? 24 : -24;

				float velX = (i == 0) ? 6 : -6;

				CBullet* pBul = m_pPlayerChara->shotBullet(BULLET_TYPE::PLAYER_NORMAL, fixX, 0.0f, velX, 0.0f);

				//NULLなら飛ばす
				if (pBul == NULL)
					return;

				//ステータスの初期化
				pBul->m_status.set(1, 1, 1, 0);

				//レイヤーに張り付ける
				m_characterLayer->addChild(pBul);

				//配列にアドレスを張り付ける
				this->m_pPlayerBullets[index] = pBul;
				//オブジェクトカウント更新
				if (index >= m_pPlayerBulletCount) {
					m_pPlayerBulletCount = index;
				}
			}
		}
		break;
		case BULLET_TYPE::PLAYER_3WAY:
		{
			for (int i = 0; i < 3; i++) {
				//配列のNULLが入っている添え字番号を取得
				int index = getFreeIndex(m_pPlayerBullets, CBullet::MAX_BULLET);

				//空いてる要素が存在しなければ弾の発射処理は行わない
				if (index == -1) {
					return;
				}

				//角度
				float angle = i * 25.0f - 25.0f;

				//角度分二次ベクトルを取得
				float velX = cos(angle * M_PI / 180.0f) * 6.0f;
				float velY = sin(angle * M_PI / 180.0f) * 6.0f;

				CBullet* pBul = m_pPlayerChara->shotBullet(BULLET_TYPE::PLAYER_NORMAL, 24.0f, 0.0f, velX, velY);

				//NULLなら飛ばす
				if (pBul == NULL)
					return;

				//ステータスの初期化
				pBul->m_status.set(1, 1, 1, 0);

				//レイヤーに張り付ける
				m_characterLayer->addChild(pBul);

				//配列にアドレスを張り付ける
				this->m_pPlayerBullets[index] = pBul;
				//オブジェクトカウント更新
				if (index >= m_pPlayerBulletCount) {
					m_pPlayerBulletCount = index;
				}
			}
		}
		break;
		default:
			break;
		}

		//弾が発射されたらカウンターをインターバルでリセットする
		m_pPlayerChara->m_shotCounter = m_pPlayerChara->m_shotInterval;

		//弾発射効果音の再生
		if (se_flg) {
			int sound = AudioEngine::play2d(SOUND_FILE_LAUNCH_BULLET);
			AudioEngine::setVolume(sound, SE_VOLUME / 120.0f);
		}
	}
}
/**
*@desc プレイヤーと弾の衝突判定
*/
void CGameMain::collisionPlayerAndEnemyBullets() {
	//プレイヤーが死んでいたら飛ばす
	if (m_pPlayerChara->m_activeFlag == false || resurrection)
		return;

	//プレイヤーの衝突判定を行う際の位置を取得
	CBody playerCollisionBody = m_pPlayerChara->m_body.getApplyPositionBody(
		m_pPlayerChara->m_move.m_posX,
		m_pPlayerChara->m_move.m_posY
	);
	//敵の弾は配列なので敵の弾の１つ１つと衝突判定を取る
	for (int i = 0; i <= m_pEnemyBulletCount; i++) {
		//要素がNULLなら飛ばす
		if (m_pEnemyBullets[i] == NULL)
			continue;

		//有効フラグがfalseの」インスタンスも飛ばす
		if (m_pEnemyBullets[i]->m_activeFlag == false)
			continue;

		//敵の弾の１つ分の衝突判定を行う際の位置を取得
		CBody eneBulCollisionBody = m_pEnemyBullets[i]->m_body.getApplyPositionBody(
			m_pEnemyBullets[i]->m_move.m_posX,
			m_pEnemyBullets[i]->m_move.m_posY
		);

		//衝突判定を行う
		if (playerCollisionBody.collision(&eneBulCollisionBody) == true && bomCount == 0) {
			//衝突している

			//プレイヤーの衝突判定の計算を行う
			m_pPlayerChara->hits(&m_pEnemyBullets[i]->m_status);

			//敵の弾の有効フラグをfalseにする
			m_pEnemyBullets[i]->m_activeFlag = false;

			//エフェクトを表示する
			int index = getFreeIndex(m_pEffects, CEfect::MAX_EFFECT);

			//空いている要素が存在しなければエフェクトの処理は行わない
			if (index != -1) {
				EFFECT_TYPE efect = m_pPlayerChara->m_activeFlag ? EFFECT_TYPE::EXPLOSION : EFFECT_TYPE::EXPLOSION_FINISH;
				//エフェクトインスタンスの作成
				CEfect* pEfe = this->launchEffect(
					efect,
					m_pPlayerChara->m_move.m_posX,
					m_pPlayerChara->m_move.m_posY
				);

				//レイヤーに張り付ける
				m_characterLayer->addChild(pEfe);

				//配列にアドレスを取り付ける
				this->m_pEffects[index] = pEfe;
				//オブジェクトカウント更新
				if (index >= m_pEfectCount) {
					m_pEfectCount = index;
				}
				//プレイヤー爆発効果音
				if (se_flg) {
					m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_PLAYER_EXPLOSION);
					AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 120.0f);
				}

			}

			//プレイヤーがやられていたらレーザーフラグを下げる
			if (m_pPlayerChara->m_activeFlag == false) {
				laserFlg = false;
			}


		}


	}
}
/**
*@desc プレイヤーと敵の衝突判定
*/
void CGameMain::collisionPlayerAndEnemies() {
	//プレイヤーが死んでいたら飛ばす
	if (m_pPlayerChara->m_activeFlag == false || resurrection)
		return;

	//プレイヤーの衝突判定を行う際の位置を取得
	CBody playerCollisionBody = m_pPlayerChara->m_body.getApplyPositionBody(
		m_pPlayerChara->m_move.m_posX,
		m_pPlayerChara->m_move.m_posY
	);
	//敵は配列なので敵の１つ１つと衝突判定を取る
	for (int i = 0; i <= m_pEnemyCount; i++) {
		//要素がNULLなら飛ばす
		if (m_pEnemyCharas[i] == NULL)
			continue;

		//有効フラグがfalseの」インスタンスも飛ばす
		if (m_pEnemyCharas[i]->m_activeFlag == false)
			continue;

		//敵の弾の１つ分の衝突判定を行う際の位置を取得
		CBody eneCollisionBody = m_pEnemyCharas[i]->m_body.getApplyPositionBody(
			m_pEnemyCharas[i]->m_move.m_posX,
			m_pEnemyCharas[i]->m_move.m_posY
		);

		//衝突判定を行う
		if (playerCollisionBody.collision(&eneCollisionBody) == true && resCount == 0 && bomCount == 0) {
			//衝突している
			//５フレーム間無敵
			resCount = 5;
			//敵の衝突判定の計算を行う
			m_pEnemyCharas[i]->hits(&m_pPlayerChara->m_status);

			//敵を倒せていたらスコアの計算を行う
			if (m_pEnemyCharas[i]->m_activeFlag == false) {
				m_pPlayerChara->m_status.addScore(m_pEnemyCharas[i]->m_status.getScore());

				if (m_pEnemyCharas[i]->e_enemyType == ENEMY_TYPE::TYPE_C) {
					//アイテムドロップ判定
					//タイプCの場合アイテムドロップ処理
					//アイテムを表示する
					int index = getFreeIndex(m_pItems, CItem::MAX_ITEM);

					//空いている要素が存在しなければエフェクトの処理は行わない
					if (index != -1) {
						//アイテムインスタンスの作成

						CItem* pItem = this->launchItem(
							m_pEnemyCharas[i]->m_item,
							m_pEnemyCharas[i]->m_move.m_posX,
							m_pEnemyCharas[i]->m_move.m_posY
						);

						//レイヤーに張り付ける
						m_characterLayer->addChild(pItem);
						//配列にアドレスを取り付ける
						this->m_pItems[index] = pItem;
						//オブジェクトカウント更新
						if (index >= m_pItemCount) {
							m_pItemCount = index;
						}

						//アイテム効果音
						if (se_flg) {
							m_pItems[index]->m_bgmid = AudioEngine::play2d(SOUND_FILE_ENEMY_EXPLOSION);
							AudioEngine::setVolume(m_pItems[index]->m_bgmid, SE_VOLUME / 120.0f);
						}

					}
				}
			}

			//エフェクトを表示する
			int index = getFreeIndex(m_pEffects, CEfect::MAX_EFFECT);

			//空いている要素が存在しなければエフェクトの処理は行わない
			if (index != -1) {
				//エフェクトインスタンスの作成
				CEfect* pEfe = this->launchEffect(
					EFFECT_TYPE::EXPLOSION,
					m_pEnemyCharas[i]->m_move.m_posX,
					m_pEnemyCharas[i]->m_move.m_posY
				);

				//レイヤーに張り付ける
				m_characterLayer->addChild(pEfe);

				//配列にアドレスを取り付ける
				this->m_pEffects[index] = pEfe;
				//オブジェクトカウント更新
				if (index >= m_pEfectCount) {
					m_pEfectCount = index;
				}

				//敵爆発効果音
				if (se_flg) {
					m_pEnemyCharas[i]->m_bgmid = AudioEngine::play2d(SOUND_FILE_ENEMY_EXPLOSION);
					AudioEngine::setVolume(m_pEnemyCharas[i]->m_bgmid, SE_VOLUME / 120.0f);
				}

			}

			//エフェクトを表示する
			index = getFreeIndex(m_pEffects, CEfect::MAX_EFFECT);

			//空いている要素が存在しなければエフェクトの処理は行わない
			if (index != -1) {
				//エフェクトインスタンスの作成
				CEfect* pEfe = this->launchEffect(
					EFFECT_TYPE::EXPLOSION,
					m_pPlayerChara->m_move.m_posX,
					m_pPlayerChara->m_move.m_posY
				);

				//レイヤーに張り付ける
				m_characterLayer->addChild(pEfe);

				//配列にアドレスを取り付ける
				this->m_pEffects[index] = pEfe;
				//オブジェクトカウント更新
				if (index >= m_pEfectCount) {
					m_pEfectCount = index;
				}
				//プレイヤー爆発効果音
				if (se_flg) {
					m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_PLAYER_EXPLOSION);
					AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 120.0f);
				}

			}


			//プレイヤーの衝突判定の計算を行う
			m_pPlayerChara->hits(&m_pEnemyCharas[i]->m_status);

			//エフェクトを表示する
			index = getFreeIndex(m_pEffects, CEfect::MAX_EFFECT);

			//空いている要素が存在しなければエフェクトの処理は行わない
			if (index != -1) {
				EFFECT_TYPE efect = m_pPlayerChara->m_activeFlag ? EFFECT_TYPE::EXPLOSION : EFFECT_TYPE::EXPLOSION_FINISH;
				//エフェクトインスタンスの作成
				CEfect* pEfe = this->launchEffect(
					efect,
					m_pPlayerChara->m_move.m_posX,
					m_pPlayerChara->m_move.m_posY
				);

				//レイヤーに張り付ける
				m_characterLayer->addChild(pEfe);

				//配列にアドレスを取り付ける
				this->m_pEffects[index] = pEfe;
				//オブジェクトカウント更新
				if (index >= m_pEfectCount) {
					m_pEfectCount = index;
				}
				//プレイヤー爆発効果音
				if (se_flg) {
					m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_PLAYER_EXPLOSION);
					AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 120.0f);
				}

			}

			//プレイヤーがやられていたらレーザーフラグを下げる
			if (m_pPlayerChara->m_activeFlag == false) {
				laserFlg = false;
			}
		}

	}


}

/**
*@desc 敵とプレイヤーの弾の衝突判定
*/
void CGameMain::collisionEnemiesAndPlayerBullets() {
	
	for (int i = 0; i <= m_pPlayerBulletCount; i++) {
		//要素がNULLなら飛ばす
		if (m_pPlayerBullets[i] == NULL)
			continue;

		//有効フラグがfalseの」インスタンスも飛ばす
		if (m_pPlayerBullets[i]->m_activeFlag == false)
			continue;

		//プレイヤーの衝突判定を行う際の位置を取得
		CBody playerCollisionBody = m_pPlayerBullets[i]->m_body.getApplyPositionBody(
			m_pPlayerBullets[i]->m_move.m_posX,
			m_pPlayerBullets[i]->m_move.m_posY
		);

		//レーザー用配列添え字保存用
		int laser = -1;

		//敵は配列なので敵の弾の１つ１つと衝突判定を取る
		for (int j = 0; j <= m_pEnemyCount; j++) {
			//要素がNULLなら飛ばす
			if (m_pEnemyCharas[j] == NULL)
				continue;

			//有効フラグがfalseの」インスタンスも飛ばす
			if (m_pEnemyCharas[j]->m_activeFlag == false)
				continue;

			//敵の１つ分の衝突判定を行う際の位置を取得
			CBody eneCollisionBody = m_pEnemyCharas[j]->m_body.getApplyPositionBody(
				m_pEnemyCharas[j]->m_move.m_posX,
				m_pEnemyCharas[j]->m_move.m_posY
			);
			//衝突判定を行う
			if (playerCollisionBody.collision(&eneCollisionBody) == true) {
				//衝突している
				//敵の衝突判定の計算を行う
				//m_pEnemyCharas[j]->hits(&m_pPlayerBullets[i]->m_status);

				switch (m_pPlayerBullets[i]->m_bulletType) {
				case BULLET_TYPE::PLAYER_EXPLOSION:
					//敵の衝突判定の計算を行う
					m_pEnemyCharas[j]->hits(&m_pPlayerBullets[i]->m_status);
					//爆発タイプ切り替え
					m_pPlayerBullets[i]->m_bulletType = BULLET_TYPE::PLAYER_EXPLOSION_2;
					//画像の設定
					m_pPlayerBullets[i]->setTexture(IMAGE_FILE_EXPLOSION_2);
					//切り取る矩形
					m_pPlayerBullets[i]->m_chip = CChip(0, 0, 120, 120);
					m_pPlayerBullets[i]->setTextureRect(m_pEnemyCharas[j]->m_chip);
					//ステータスの設定
					m_pPlayerBullets[i]->m_status.set(1, 1, 1, 0);
					//移動データに初期速度の設定　停止状態
					m_pPlayerBullets[i]->m_move.setVel(0, 0);
					//アニメーションデータの初期化
					m_pPlayerBullets[i]->m_anime.set(10, 7, false);
					//衝突判定用データの初期化
					m_pPlayerBullets[i]->m_body.set(
						-20 * m_pPlayerChara->m_shotParam,
						20 * m_pPlayerChara->m_shotParam,
						20 * m_pPlayerChara->m_shotParam,
						-20 * m_pPlayerChara->m_shotParam
					);
					//画像サイズをレベル補正
					m_pPlayerBullets[i]->setScale(0.5f * m_pPlayerChara->m_shotParam);

					//取り外しフラグ有効
					m_pPlayerBullets[i]->m_delflg = true;
					//取り外しフレームカウント設定
					m_pPlayerBullets[i]->m_maxCount = 70;
					//敵を倒せていたらスコアの計算を行う
					calculationScore(j);
					//エフェクトを表示する
					createEffect(j);

					break;
				case BULLET_TYPE::PLAYER_EXPLOSION_2:
					//敵の衝突判定の計算を行う
					m_pEnemyCharas[j]->hits(&m_pPlayerBullets[i]->m_status);
					//敵を倒せていたらスコアの計算を行う
					calculationScore(j);
					//エフェクトを表示する
					if (m_pEnemyCharas[j]->m_activeFlag == false)
						createEffect(j);

					break;
				case BULLET_TYPE::PLAYER_LASER:


					if (laser == -1) {
						//最初は必ず敵の添え字を代入
						laser = j;
					}
					else {
						//一番自機に近い敵に添え字を上書き
						if (m_pEnemyCharas[laser]->m_move.m_posX - m_pEnemyCharas[laser]->m_body.m_left >=
							m_pEnemyCharas[j]->m_move.m_posX - m_pEnemyCharas[j]->m_body.m_left) {
							laser = j;
						}

					}
					break;
				default:
					//敵の衝突判定の計算を行う
					m_pEnemyCharas[j]->hits(&m_pPlayerBullets[i]->m_status);

					//通常弾、バック弾、散弾、誘導弾は消滅
					//プレイヤーの弾の有効フラグをfalseにする
					m_pPlayerBullets[i]->m_activeFlag = false;
					//敵を倒せていたらスコアの計算を行う
					calculationScore(j);
					//エフェクトを表示する
					createEffect(j);
					break;
				}


			}

		}
		//レーザーの場合ここで計算
		//壁判定用に保存する
		laserIndex = laser;
		if (m_pPlayerBullets[i]->m_bulletType == BULLET_TYPE::PLAYER_LASER) {

			if (laserFlg == false) {
				//レーザーの有効フラグをfalseにする
				m_pPlayerBullets[i]->m_activeFlag = false;
				cocos2d::log("laser off");
				continue;
			}

			//レーザーの長さ変更 デフォルト640
			m_pPlayerBullets[i]->m_chip.size.width = 640;

			
		}
	}
	//ボム処理
	if (bomCount != 0) {
		if (bomCount <= 100 && bomCount % 10 == 0) {
			//ボム用のステータス
			CStatus m_status;
			m_status.set(0, 0, 10, 0);

			//敵は配列なので敵の弾の１つ１つと衝突判定を取る
			for (int j = 0; j <= m_pEnemyCount; j++) {
				//要素がNULLなら飛ばす
				if (m_pEnemyCharas[j] == NULL)
					continue;

				//有効フラグがfalseの」インスタンスも飛ばす
				if (m_pEnemyCharas[j]->m_activeFlag == false)
					continue;

				//敵の衝突判定の計算を行う
				m_pEnemyCharas[j]->hits(&m_status);

				//敵を倒せていたらスコアの計算を行う
				calculationScore(j);
				//エフェクトを表示する
				createEffect(j);
			}
		}
	}

}

void CGameMain::calculationScore(int j) {
	//敵を倒せていたらスコアの計算を行う
	if (m_pEnemyCharas[j]->m_activeFlag == false) {
		m_pPlayerChara->m_status.addScore(m_pEnemyCharas[j]->m_status.getScore());
		//ボスならカウントを増やす
		if (m_pEnemyCharas[j]->bossflg) {
			m_pEnemyCharas[j]->bossCount = 300;
		}
		
		if (m_pEnemyCharas[j]->m_item != ITEM_TYPE::NONE) {
			//アイテム無し以外の場合
			//アイテムを表示する
			int index = getFreeIndex(m_pItems, CItem::MAX_ITEM);

			//空いている要素が存在しなければエフェクトの処理は行わない
			if (index != -1) {
				//アイテムインスタンスの作成

				CItem* pItem = this->launchItem(
					m_pEnemyCharas[j]->m_item,
					m_pEnemyCharas[j]->m_move.m_posX,
					m_pEnemyCharas[j]->m_move.m_posY
				);

				//レイヤーに張り付ける
				m_characterLayer->addChild(pItem);
				//配列にアドレスを取り付ける
				this->m_pItems[index] = pItem;
				//オブジェクトカウント更新
				if (index >= m_pItemCount) {
					m_pItemCount = index;
				}

				
			}
		}


	}

}

void CGameMain::createEffect(int j) {
	//エフェクトを表示する
	int index = getFreeIndex(m_pEffects, CEfect::MAX_EFFECT);
	//空いている要素が存在しなければエフェクトの処理は行わない
	if (index != -1) {
		EFFECT_TYPE type;
		if (m_pEnemyCharas[j]->m_activeFlag == true) {
			//敵爆発効果音
			if (!soundDeray) {
				soundDeray = 20;
				if (se_flg) {
					m_pEnemyCharas[j]->m_bgmid = AudioEngine::play2d(SOUND_FILE_ENEMY_EXPLOSION);
					AudioEngine::setVolume(m_pEnemyCharas[j]->m_bgmid, SE_VOLUME / 120.0f);
				}

			}
			type = EFFECT_TYPE::EXPLOSION;
		}
		else {
			if (se_flg) {
				m_pEnemyCharas[j]->m_bgmid = AudioEngine::play2d(SOUND_FILE_ENEMY_EXPLOSION_FINISH);
				AudioEngine::setVolume(m_pEnemyCharas[j]->m_bgmid, SE_VOLUME / 120.0f);
			}

			type = EFFECT_TYPE::EXPLOSION_FINISH;
		}

		//エフェクトインスタンスの作成
		CEfect* pEfe = this->launchEffect(
			type,
			m_pEnemyCharas[j]->m_move.m_posX,
			m_pEnemyCharas[j]->m_move.m_posY
		);

		//レイヤーに張り付ける
		m_characterLayer->addChild(pEfe);

		//配列にアドレスを取り付ける
		this->m_pEffects[index] = pEfe;
		//オブジェクトカウント更新
		if (index >= m_pEfectCount) {
			m_pEfectCount = index;
		}
	}
}

void CGameMain::createEffect2(int j, float x, float y) {
	//エフェクトを表示する
	int index = getFreeIndex(m_pEffects, CEfect::MAX_EFFECT);
	//空いている要素が存在しなければエフェクトの処理は行わない
	if (index != -1) {
		EFFECT_TYPE type;
		if (!soundDeray) {
			soundDeray = 20;
			//敵爆発効果音
			if (se_flg) {
				m_pWalls[j]->m_bgmid = AudioEngine::play2d(SOUND_FILE_ENEMY_EXPLOSION);
				AudioEngine::setVolume(m_pWalls[j]->m_bgmid, SE_VOLUME / 120.0f);
			}

		}
		type = EFFECT_TYPE::EXPLOSION;
		//エフェクトインスタンスの作成
		CEfect* pEfe = this->launchEffect(
			type,
			x,
			y
		);

		//レイヤーに張り付ける
		m_characterLayer->addChild(pEfe);

		//配列にアドレスを取り付ける
		this->m_pEffects[index] = pEfe;
		//オブジェクトカウント更新
		if (index >= m_pEfectCount) {
			m_pEfectCount = index;
		}
	}
}

/*
*@desc 敵を出撃させるかどうかのチェック

*/
void CGameMain::checkLaunchEnemy() {
	//参照する敵出撃データの番号が出撃最大数以上になったら出撃判定を行わない

	if (this->m_enemyLaunchIndex >= (int)MapData::m_pEnemyLaunchData.size()) {
		return;
	}

	//敵複製カウント
	int enemycount = 0;

	while (this->m_frameCounter == MapData::m_pEnemyLaunchData[this->m_enemyLaunchIndex].m_frame) {
		//配列のNULLが入っている添え字番号を取得
		int index = getFreeIndex(m_pEnemyCharas, CEnemyCharacter::MAX_ENEMY);

		//空いている要素が存在しなければ敵の出撃処理は行わない
		if (index != -1) {

			CEnemyCharacter* pEne = this->launchEnemy(
				&MapData::m_pEnemyLaunchData[this->m_enemyLaunchIndex]
			);
			
			//レイヤーに張り付ける
			m_characterLayer->addChild(pEne);
			
			//配列にアドレスを取り付ける
			this->m_pEnemyCharas[index] = pEne;
			//オブジェクトカウント更新
			if (index >= m_pEnemyCount) {
				m_pEnemyCount = index;
			}
			if (pEne->e_enemyType == ENEMY_TYPE::TYPE_D && 
				enemycount != (int)(this->m_frameCounter / 10) % 5) {
				pEne->m_item = ITEM_TYPE::NONE;
			}
			if (pEne->e_enemyType == ENEMY_TYPE::TYPE_D && enemycount != 5) {
				//敵を連続で配置
				
				if (enemycount != 0) {
					CEnemyAction action;
					action.x = 0;
					action.y = 0;
					action.frame = 10 * enemycount;
					pEne->action.insert(pEne->action.begin(), action);
					pEne->m_move.setVel(-WALL_SPEED, 0);
					pEne->shotCount -= 10 * enemycount;
					
				}


				enemycount++;
			}
			else {
				//出撃を行っていたら参照している出撃データの番号を次の出撃データに変更する
				this->m_enemyLaunchIndex++;
				enemycount = 0;
			}

			if (this->m_enemyLaunchIndex >= (int)MapData::m_pEnemyLaunchData.size()) {
				return;
			}
		}

	}
}

void CGameMain::checkEnemyAleart() {
	//参照する敵出撃データの番号が出撃最大数以上になったら出撃判定を行わない

	if (this->m_enemyAleartIndex >= (int)MapData::m_pEnemyLaunchData.size()) {
		return;
	}
	while (this->m_frameCounter + 60 == MapData::m_pEnemyLaunchData[this->m_enemyAleartIndex].m_frame) {
		//配列のNULLが入っている添え字番号を取得
		int index = getFreeIndex(m_pEffects, CEfect::MAX_EFFECT);

		//空いている要素が存在しなければエフェクト処理は行わない
		if (index != -1) {
			CEfect* pEfect = launchEffect(EFFECT_TYPE::ALEART,
				(float)MapData::m_pEnemyLaunchData[this->m_enemyAleartIndex].m_posX + 40,
				(float)MapData::m_pEnemyLaunchData[this->m_enemyAleartIndex].m_posY);

			//レイヤーに張り付ける
			m_characterLayer->addChild(pEfect);

			//配列にアドレスを取り付ける
			this->m_pEffects[index] = pEfect;
			//オブジェクトカウント更新
			if (index >= m_pEfectCount) {
				m_pEfectCount = index;
			}

			//出撃を行っていたら参照している出撃データの番号を次の出撃データに変更する
			this->m_enemyAleartIndex++;

			if (this->m_enemyAleartIndex >= (int)MapData::m_pEnemyLaunchData.size()) {
				return;
			}
		}

	}
}


//エフェクトの出現
/**
*@desc エフェクトの出現
*@param エフェクトタイプ
*@param 出現位置X
*@param 出現位置Y
*@return エフェクトクラスのポインタ
*/
CEfect* CGameMain::launchEffect(EFFECT_TYPE type, float posX, float posY) {
	//エフェクトの生成
	CEfect* pEfe = CEfect::create();

	switch (type) {
	case EFFECT_TYPE::EXPLOSION:
		//画像の設定
		pEfe->setTexture(IMAGE_FILE_EXPLOSION);
		//切り取る矩形
		pEfe->m_chip = CChip(0, 0, 48, 48);
		//アニメーションデータの初期化
		pEfe->m_anime.set(5, 8, false);
		break;
	case EFFECT_TYPE::EXPLOSION_FINISH:
		//画像の設定
		pEfe->setTexture(IMAGE_FILE_EXPLOSION_FINISH);
		//切り取る矩形
		pEfe->m_chip = CChip(0, 0, 120, 120);
		//アニメーションデータの初期化
		pEfe->m_anime.set(5, 5, false);
		break;
	case EFFECT_TYPE::BOM:
		//画像の設定
		pEfe->setTexture(IMAGE_FILE_BOM);
		//切り取る矩形
		pEfe->m_chip = CChip(0, 0, 640, 480);
		//アニメーションデータの初期化
		pEfe->m_anime.set(5, 24, false);
		pEfe->maxX = 3;

		break;
	case EFFECT_TYPE::ALEART:
		//画像の設定
		pEfe->setTexture(IMAGE_FILE_ALEART);
		//切り取る矩形
		pEfe->m_chip = CChip(0, 0, 40, 40);
		//アニメーションデータの初期化
		pEfe->m_anime.set(10, 6, false);
		break;
	case EFFECT_TYPE::PLANET1:
		//画像の設定
		pEfe->setTexture(IMAGE_FILE_PLANET_1);
		//切り取る矩形
		pEfe->m_chip = CChip(0, 0, 171, 171);
		//アニメーションデータの初期化
		pEfe->m_anime.set(60, 1, true);
		break;
	case EFFECT_TYPE::PLANET2:
		//画像の設定
		pEfe->setTexture(IMAGE_FILE_PLANET_2);
		//切り取る矩形
		pEfe->m_chip = CChip(0, 0, 233, 135);
		//アニメーションデータの初期化
		pEfe->m_anime.set(60, 1, true);
		break;
	case EFFECT_TYPE::PLANET3:
		//画像の設定
		pEfe->setTexture(IMAGE_FILE_PLANET_3);
		//切り取る矩形
		pEfe->m_chip = CChip(0, 0, 281, 162);
		//アニメーションデータの初期化
		pEfe->m_anime.set(60, 1, true);
		break;
	case EFFECT_TYPE::PLANET4:
		//画像の設定
		pEfe->setTexture(IMAGE_FILE_PLANET_4);
		//切り取る矩形
		pEfe->m_chip = CChip(0, 0, 142, 136);
		//アニメーションデータの初期化
		pEfe->m_anime.set(60, 1, true);
		break;
	case EFFECT_TYPE::PLANET5:
		//画像の設定
		pEfe->setTexture(IMAGE_FILE_PLANET_5);
		//切り取る矩形
		pEfe->m_chip = CChip(0, 0, 285, 164);
		//アニメーションデータの初期化
		pEfe->m_anime.set(60, 1, true);
		break;
	case EFFECT_TYPE::PLANET6:
		//画像の設定
		pEfe->setTexture(IMAGE_FILE_PLANET_6);
		//切り取る矩形
		pEfe->m_chip = CChip(0, 0, 236, 235);
		//アニメーションデータの初期化
		pEfe->m_anime.set(60, 1, true);
		break;
	case EFFECT_TYPE::PLANET7:
		//画像の設定
		pEfe->setTexture(IMAGE_FILE_PLANET_7);
		//切り取る矩形
		pEfe->m_chip = CChip(0, 0, 203, 203);
		//アニメーションデータの初期化
		pEfe->m_anime.set(60, 1, true);
		break;
	case EFFECT_TYPE::PLANET8:
		//画像の設定
		pEfe->setTexture(IMAGE_FILE_PLANET_8);
		//切り取る矩形
		pEfe->m_chip = CChip(0, 0, 172, 172);
		//アニメーションデータの初期化
		pEfe->m_anime.set(60, 1, true);
		break;
	case EFFECT_TYPE::PLANET9:
		//画像の設定
		pEfe->setTexture(IMAGE_FILE_PLANET_9);
		//切り取る矩形
		pEfe->m_chip = CChip(0, 0, 232, 217);
		//アニメーションデータの初期化
		pEfe->m_anime.set(60, 1, true);
		break;
	default:
		break;
	}
	//弾タイプの設定
	pEfe->type = type;

	pEfe->setTextureRect(pEfe->m_chip);
	//移動データに初期位置の設定
	pEfe->m_move.setPos(posX, posY);
	//移動データに初期速度の設定；
	pEfe->m_move.setVel(0, 0);

	//初期位置を判定
	pEfe->setPosition(pEfe->m_move.m_posX, pEfe->m_move.m_posY);

	//有効フラグにtrueを入れる
	pEfe->m_activeFlag = true;



	return pEfe;
}

/**
*@desc アイテムの出現
*@param アイテムタイプ
*@param 出現位置X
*@param 出現位置Y
*@return アイテムクラスのポインタ
*/
CItem* CGameMain::launchItem(ITEM_TYPE type, float posX, float posY) {
	//アイテムの生成
	CItem* pItem = CItem::create();
	//画像の設定
	pItem->setTexture(IMAGE_FILE_ITEM);
	//切り取る矩形
	switch (type) {
	case ITEM_TYPE::SPEEDUP:
		pItem->m_chip = CChip(0, 0, 40, 40);
		break;
	case ITEM_TYPE::RECOVERY:
		pItem->m_chip = CChip(0, 40, 40, 40);
		break;
	case ITEM_TYPE::NORMAL:
		pItem->m_chip = CChip(0, 80, 40, 40);
		break;
	case ITEM_TYPE::EXPLOSION:
		pItem->m_chip = CChip(0, 120, 40, 40);
		break;
	case ITEM_TYPE::BACK:
		pItem->m_chip = CChip(0, 160, 40, 40);
		break;
	case ITEM_TYPE::LASER:
		pItem->m_chip = CChip(0, 200, 40, 40);
		break;
	case ITEM_TYPE::INDUCTION:
		pItem->m_chip = CChip(0, 240, 40, 40);
		break;
	case ITEM_TYPE::MULTIPLE:
		pItem->m_chip = CChip(0, 280, 40, 40);
		break;
	case ITEM_TYPE::BOM:
		pItem->m_chip = CChip(0, 320, 40, 40);
		break;
	case ITEM_TYPE::ONE_UP:
		pItem->m_chip = CChip(0, 360, 40, 40);
		break;
	default:
		pItem->m_chip = CChip(0, 0, 40, 40);
		break;
	}
	
	pItem->setTextureRect(pItem->m_chip);
	//移動データに初期位置の設定
	pItem->m_move.setPos(posX, posY);
	//移動データに初期速度の設定；
	pItem->m_move.setVel(-WALL_SPEED, 0);
	//あたり判定設定
	pItem->m_body.set(-20, 20, 20, -20);
	//アニメーションデータの初期化
	pItem->m_anime.set(5, 6, true);

	//初期位置を判定
	pItem->setPosition(pItem->m_move.m_posX, pItem->m_move.m_posY);

	//有効フラグにtrueを入れる
	pItem->m_activeFlag = true;

	//アイテムタイプの設定
	pItem->type = type;

	return pItem;
}

/**
*@desc 壁の出現
*@param 壁タイプ
*@param 出現位置X
*@param 出現位置Y
*@return 壁クラスのポインタ
*/
CWall* CGameMain::launchWall(WALL_TYPE type, float posX, float posY) {
	//壁の生成
	CWall* pWall = CWall::create();
	//画像の設定
	switch (type) {
	case WALL_TYPE::STAGE_1_1:
		pWall->setTexture(IMAGE_FILE_WALL);
		break;
	case WALL_TYPE::STAGE_1_2:
		pWall->setTexture(IMAGE_FILE_WALL_2);
		break;
	case WALL_TYPE::STAGE_2_1:
		pWall->setTexture(IMAGE_FILE_WALL_3);
		break;
	case WALL_TYPE::STAGE_2_2:
		pWall->setTexture(IMAGE_FILE_WALL_4);
		break;
	case WALL_TYPE::STAGE_3_1:
		pWall->setTexture(IMAGE_FILE_WALL_5);
		break;
	case WALL_TYPE::STAGE_3_2:
		pWall->setTexture(IMAGE_FILE_WALL_6);
		break;
	}

	//切り取る矩形
	pWall->m_chip = CChip(0, 0, 40, 40);
	

	pWall->setTextureRect(pWall->m_chip);
	//移動データに初期位置の設定
	pWall->m_move.setPos(posX, posY);
	//移動データに初期速度の設定；
	pWall->m_move.setVel(-MapData::WALL_SPEED, 0);
	//あたり判定設定
	pWall->m_body.set(-20, 20, 20, -20);
	//アニメーションデータの初期化
	pWall->m_anime.set(1, 1, false);
	//ステータスの設定
	pWall->m_status.set(1, 1, 1, 0);
	//初期位置を判定
	pWall->setPosition(pWall->m_move.m_posX, pWall->m_move.m_posY);

	//有効フラグにtrueを入れる
	pWall->m_activeFlag = true;

	//アイテムタイプの設定
	pWall->type = type;

	return pWall;
}

/*
*@desc 壁を出現させるかどうかのチェック
*/
void CGameMain::checkLaunchWall() {
	//マップの端なら飛ばす
	if (m_pWallXpos == 100) {
		return;
	}
	if ((int)this->m_wallCounter / 40 == m_pWallXpos) {
		//端数を取得取得
		//壁の出現位置補正
		float wallRemainder = m_wallCounter - ((int)m_wallCounter / 40 * 40);
		//マップデータから壁情報を調べる
		for (int i = 1; i < 13; i++) {
			if (MapData::m_pMapData[m_pWallXpos][i].m_mapChipPatern >= 1) {
				//壁を配置
				//配列のNULLが入っている添え字番号を取得
				int index = getFreeIndex(m_pWalls, CWall::MAX_WALL);
				//空いている要素が存在しなければ壁の出現処理は行わない
				if (index != -1) {
					float xPos = 660 - wallRemainder;
					float yPos = 20 + (i - 1) * 40;
					CWall* pWall = this->launchWall(
						(WALL_TYPE)(MapData::m_pMapData[m_pWallXpos][i].m_mapChipPatern - 1),
						xPos,
						yPos
					);
					//壁の縁を作成
					char* img;
					switch (CGameMain::m_stageNo) {
					case 1:
						img = IMAGE_FILE_WALL_BORDER_1;
						break;
					case 2:
						img = IMAGE_FILE_WALL_BORDER_2;
						break;
					case 3:
						img = IMAGE_FILE_WALL_BORDER_3;
						break;
					}
					//左
					if (m_pWallXpos == 0 || !MapData::m_pMapData[m_pWallXpos - 1][i].m_mapChipPatern) {
						pWall->m_pWall_left = Sprite::create();
						pWall->m_pWall_left->setTexture(img);

						pWall->m_pWall_left->setTextureRect(CChip(0, 8 * (rand() % 3), 48, 8));
						pWall->m_pWall_left->setRotation(90);
						pWall->m_pWall_left->setPosition(0.0f, 20.0f);
						pWall->addChild(pWall->m_pWall_left);
					}
					
					//右
					if (m_pWallXpos == MapData::MAX_MAP_DATA_X - 1 || !MapData::m_pMapData[m_pWallXpos + 1][i].m_mapChipPatern) {
						pWall->m_pWall_right = Sprite::create();
						pWall->m_pWall_right->setTexture(img);

						pWall->m_pWall_right->setTextureRect(CChip(0, 8 * (rand() % 3), 48, 8));
						pWall->m_pWall_right->setRotation(270);
						pWall->m_pWall_right->setPosition(40.0f, 20.0f);
						pWall->addChild(pWall->m_pWall_right);
					}
					
					//上
					if (i != MapData::MAX_MAP_DATA_Y - 2 && !MapData::m_pMapData[m_pWallXpos][i + 1].m_mapChipPatern) {
						pWall->m_pWall_top = Sprite::create();
						pWall->m_pWall_top->setTexture(img);

						pWall->m_pWall_top->setTextureRect(CChip(0, 8 * (rand() % 3), 48, 8));
						pWall->m_pWall_top->setRotation(0);
						pWall->m_pWall_top->setPosition(20.0f, 40.0f);
						pWall->addChild(pWall->m_pWall_top);
					}
					
					//下
					if (i != 1 && !MapData::m_pMapData[m_pWallXpos][i - 1].m_mapChipPatern) {
						pWall->m_pWall_bottom = Sprite::create();
						pWall->m_pWall_bottom->setTexture(img);

						pWall->m_pWall_bottom->setTextureRect(CChip(0, 8 * (rand() % 3), 48, 8));
						pWall->m_pWall_bottom->setRotation(180);
						pWall->m_pWall_bottom->setPosition(20.0f, 0.0f);
						pWall->addChild(pWall->m_pWall_bottom);
					}
					

					//レイヤーに張り付ける
					m_wallLayer->addChild(pWall);

					//配列にアドレスを取り付ける
					this->m_pWalls[index] = pWall;
					//オブジェクトカウント更新
					if (index >= m_pWallCount) {
						m_pWallCount = index;
					}
				}
			}
		}
		
		//次のxポジションにする
		m_pWallXpos++;



	}

}

/*
*@desc 壁を出現させるかどうかのチェック
*/
void CGameMain::checkLaunchPlanet() {
	//マップの端なら飛ばす
	if (m_planetFrame > 0) {
		m_planetFrame--;
		return;
	}
	m_planetFrame = rand() % 300;
	//エフェクトを表示する
	int index = getFreeIndex(m_pEffects, CEfect::MAX_EFFECT);

	//空いている要素が存在しなければエフェクトの処理は行わない
	if (index != -1) {
		bool dir = (bool)(rand() % 2);
		float x = dir ? -190.0f : 830.0f;
		float y = rand() % 480;
		float vel_x = (dir ? 1 : -1) * ((float)(rand() % 200 / 100.0) + 1.0f);
		float vel_y = (y < 240 ? 1 : -1) * (float)(rand() % 100 / 100.0);
		//エフェクトインスタンスの作成
		CEfect* pEfe = this->launchEffect(
			(EFFECT_TYPE)(rand() % 9 + 4),
			x,
			y
		);

		//サイズ変更
		pEfe->setScale((float)((rand() % 100 + 20) / 100.0f));
		
		pEfe->m_move.setVel(vel_x, vel_y);
		//レイヤーに張り付ける
		m_backGroundLayer->addChild(pEfe);

		//配列にアドレスを取り付ける
		this->m_pEffects[index] = pEfe;
		//オブジェクトカウント更新
		if (index >= m_pEfectCount) {
			m_pEfectCount = index;
		}

	}


}

/**
*@desc 行動管理関数
*/
void CGameMain::actionFunc() {
	for (int i = 0; i <= m_pEnemyCount; i++) {
		//NULLチェック
		if (m_pEnemyCharas[i] == NULL) {
			continue;
		}
		//有効フラグチェック
		if (m_pEnemyCharas[i]->m_activeFlag == false) {
			continue;
		}

		switch (m_pEnemyCharas[i]->m_actionType) {
		case ACTION_TYPE::ZIGZAG:
			//ジグザグの行動を行う
			m_actCtrlZigZag.actionFunc(m_pEnemyCharas[i]);
			break;
		case ACTION_TYPE::STRAIGHT:
			//ジグザグの行動を行う
			m_actCtrlStraight.actionFunc(m_pEnemyCharas[i]);
			break;
		case ACTION_TYPE::CONVEX:
			//凸行動を行う
			m_actCtrlConvex.actionFunc(m_pEnemyCharas[i]);
			break;
		case ACTION_TYPE::ORIGINAL:
			//オリジナル行動を行う
			m_actCtrlOriginal.actionFunc(m_pEnemyCharas[i]);
			break;
		case ACTION_TYPE::ORIGINAL2:
			//オリジナル行動を行う
			m_actCtrlOriginal2.actionFunc(m_pEnemyCharas[i]);
			break;
		case ACTION_TYPE::BOSS_1:
			//ボス行動を行う
			m_actCtrlBoss.actionFunc(m_pEnemyCharas[i]);
			break;
		default:
			break;
		}

	}
}

/**
*@desc プレイヤーとアイテムの衝突判定
*/
void CGameMain::collisionPlayerAndItems() {
	//プレイヤーが死んでいたら飛ばす
	if (m_pPlayerChara->m_activeFlag == false)
		return;

	//プレイヤーの衝突判定を行う際の位置を取得
	CBody playerCollisionBody = m_pPlayerChara->m_body.getApplyPositionBody(
		m_pPlayerChara->m_move.m_posX,
		m_pPlayerChara->m_move.m_posY
	);
	//アイテムは配列なので敵の１つ１つと衝突判定を取る
	for (int i = 0; i <= m_pItemCount; i++) {
		//要素がNULLなら飛ばす
		if (m_pItems[i] == NULL)
			continue;

		//有効フラグがfalseの」インスタンスも飛ばす
		if (m_pItems[i]->m_activeFlag == false)
			continue;

		//アイテムの１つ分の衝突判定を行う際の位置を取得
		CBody itemCollisionBody = m_pItems[i]->m_body.getApplyPositionBody(
			m_pItems[i]->m_move.m_posX,
			m_pItems[i]->m_move.m_posY
		);

		//衝突判定を行う
		if (playerCollisionBody.collision(&itemCollisionBody) == true) {
			//衝突している
			m_pItems[i]->hits(&m_pPlayerChara->m_status);

			//攻撃力設定
			m_pPlayerChara->m_shotPower = this->pweponPower[weponSelect][pweponLevel[weponSelect]];
			//攻撃間隔設定
			m_pPlayerChara->m_shotInterval = this->pweponInterval[weponSelect][pweponLevel[weponSelect]];
			//攻撃パラメータ設定
			m_pPlayerChara->m_shotParam = this->pweponParam[weponSelect][pweponLevel[weponSelect]];
			//攻撃移動量設定
			m_pPlayerChara->m_shotVel = this->pweponVel[weponSelect][pweponLevel[weponSelect]];

			//有効フラグをfalse
			m_pItems[i]->m_activeFlag = false;

			//アイテム効果音
			if (se_flg) {
				switch (m_pItems[i]->type) {
				case ITEM_TYPE::SPEEDUP:
					m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_ITEM_SPEED_UP);
					AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 100.0f);
					break;
				case ITEM_TYPE::RECOVERY:
					m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_ITEM_RECEVERY);
					AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 100.0f);
					break;
				case ITEM_TYPE::NORMAL:
					m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_ITEM_NORMAL);
					AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 100.0f);
					break;
				case ITEM_TYPE::BACK:
					m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_ITEM_BACK);
					AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 100.0f);
					break;
				case ITEM_TYPE::EXPLOSION:
					m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_ITEM_EXPLOSION);
					AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 100.0f);
					break;
				case ITEM_TYPE::LASER:
					m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_ITEM_LASER);
					AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 100.0f);
					break;
				case ITEM_TYPE::INDUCTION:
					m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_ITEM_INDUCTION);
					AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 100.0f);
					break;
				case ITEM_TYPE::MULTIPLE:
					m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_ITEM_MULTIPLE);
					AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 100.0f);
					break;
				case ITEM_TYPE::BOM:
					m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_ITEM_BOM);
					AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 100.0f);
					break;
				case ITEM_TYPE::ONE_UP:
					m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_ITEM_ONE_UP);
					AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 100.0f);
					break;
				default:
					break;
				}
				//アイテム取得果音
				m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_ITEM_GET);
				AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 100.0f);
			}


		}

	}


}

/**
*@desc プレイヤーと壁の衝突判定
*/
void CGameMain::collisionPlayerAndWalls() {
	//プレイヤーが死んでいたら飛ばす
	if (m_pPlayerChara->m_activeFlag == false || resurrection)
		return;


	//壁は配列なので敵の１つ１つと衝突判定を取る
	for (int i = 0; i <= m_pWallCount; i++) {

		//要素がNULLなら飛ばす
		if (m_pWalls[i] == NULL)
			continue;

		//有効フラグがfalseの」インスタンスも飛ばす
		if (m_pWalls[i]->m_activeFlag == false)
			continue;

		//プレイヤーの衝突判定を行う際の位置を取得
		CBody playerCollisionBody = m_pPlayerChara->m_body.getApplyPositionBody(
			m_pPlayerChara->m_move.m_posX,
			m_pPlayerChara->m_move.m_posY
		);

		//アイテムの１つ分の衝突判定を行う際の位置を取得
		CBody wallCollisionBody = m_pWalls[i]->m_body.getApplyPositionBody(
			m_pWalls[i]->m_move.m_posX,
			m_pWalls[i]->m_move.m_posY
		);

		//衝突判定を行う

		if (playerCollisionBody.collision(&wallCollisionBody) == true) {
			//壁移動キャラクター座標補正
			if (colDir) {
				//横判定優先
				if (m_pPlayerChara->m_body.getApplyPositionBody(
					m_pPlayerChara->m_move.m_posX - WALL_SPEED - m_pPlayerChara->m_move.m_velX,
					m_pPlayerChara->m_move.m_posY
				).collision(&wallCollisionBody) == false) {
					m_pPlayerChara->m_move.m_posX -= m_pPlayerChara->m_move.m_velX + WALL_SPEED;

					colDir = true;
				}
				else if (m_pPlayerChara->m_body.getApplyPositionBody(
					m_pPlayerChara->m_move.m_posX,
					m_pPlayerChara->m_move.m_posY - m_pPlayerChara->m_move.m_velY
				).collision(&wallCollisionBody) == false) {
					m_pPlayerChara->m_move.m_posY -= m_pPlayerChara->m_move.m_velY;

					colDir = false;
				}
				else if (m_pPlayerChara->m_body.getApplyPositionBody(
					m_pPlayerChara->m_move.m_posX - WALL_SPEED - m_pPlayerChara->m_move.m_velX,
					m_pPlayerChara->m_move.m_posY - m_pPlayerChara->m_move.m_velY
				).collision(&wallCollisionBody) == false) {
					m_pPlayerChara->m_move.m_posX -= m_pPlayerChara->m_move.m_velX + WALL_SPEED;
					m_pPlayerChara->m_move.m_posY -= m_pPlayerChara->m_move.m_velY;

				}
			}
			else {
				//縦判定優先
				if (m_pPlayerChara->m_body.getApplyPositionBody(
					m_pPlayerChara->m_move.m_posX,
					m_pPlayerChara->m_move.m_posY - m_pPlayerChara->m_move.m_velY
				).collision(&wallCollisionBody) == false) {
					m_pPlayerChara->m_move.m_posY -= m_pPlayerChara->m_move.m_velY;

					colDir = false;
				}
				else if (m_pPlayerChara->m_body.getApplyPositionBody(
					m_pPlayerChara->m_move.m_posX - WALL_SPEED - m_pPlayerChara->m_move.m_velX,
					m_pPlayerChara->m_move.m_posY
				).collision(&wallCollisionBody) == false) {
					m_pPlayerChara->m_move.m_posX -= m_pPlayerChara->m_move.m_velX + WALL_SPEED;

					colDir = true;
				}
				else if (m_pPlayerChara->m_body.getApplyPositionBody(
					m_pPlayerChara->m_move.m_posX - WALL_SPEED - m_pPlayerChara->m_move.m_velX,
					m_pPlayerChara->m_move.m_posY - m_pPlayerChara->m_move.m_velY
				).collision(&wallCollisionBody) == false) {
					m_pPlayerChara->m_move.m_posX -= m_pPlayerChara->m_move.m_velX + WALL_SPEED;
					m_pPlayerChara->m_move.m_posY -= m_pPlayerChara->m_move.m_velY;

				}
			}



			//左端はみ出し確認 壁めり込み確認
			if (m_pPlayerChara->m_move.m_posX - m_pPlayerChara->m_body.m_left < WINDOW_LEFT ||
				m_pPlayerChara->m_body.getApplyPositionBody(
					m_pPlayerChara->m_move.m_posX,
					m_pPlayerChara->m_move.m_posY
				).collision(&wallCollisionBody) == true
				) {
				//はみ出したらアクティブ下げる
				m_pPlayerChara->m_activeFlag = false;
				//エフェクトを表示する
				int index = getFreeIndex(m_pEffects, CEfect::MAX_EFFECT);

				//空いている要素が存在しなければエフェクトの処理は行わない
				if (index != -1) {
					EFFECT_TYPE efect = m_pPlayerChara->m_activeFlag ? EFFECT_TYPE::EXPLOSION : EFFECT_TYPE::EXPLOSION_FINISH;
					//エフェクトインスタンスの作成
					CEfect* pEfe = this->launchEffect(
						efect,
						m_pPlayerChara->m_move.m_posX,
						m_pPlayerChara->m_move.m_posY
					);

					//レイヤーに張り付ける
					m_characterLayer->addChild(pEfe);

					//配列にアドレスを取り付ける
					this->m_pEffects[index] = pEfe;
					//オブジェクトカウント更新
					if (index >= m_pEfectCount) {
						m_pEfectCount = index;
					}
					//プレイヤー爆発効果音
					if (se_flg) {
						m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_PLAYER_EXPLOSION);
						AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 120.0f);
					}

				}
				return;
			}

			
		}

	}


}
// 壁とプレイヤーの弾の衝突
void CGameMain::collisionWallsAndPlayerBullets() {
	//プレイヤーが死んでいたら飛ばす
	//if (m_pPlayerChara->m_activeFlag == false)
	//return;

	for (int i = 0; i <= m_pPlayerBulletCount; i++) {
		//要素がNULLなら飛ばす
		if (m_pPlayerBullets[i] == NULL)
			continue;

		//有効フラグがfalseの」インスタンスも飛ばす
		if (m_pPlayerBullets[i]->m_activeFlag == false)
			continue;

		//プレイヤーの衝突判定を行う際の位置を取得
		CBody playerCollisionBody = m_pPlayerBullets[i]->m_body.getApplyPositionBody(
			m_pPlayerBullets[i]->m_move.m_posX,
			m_pPlayerBullets[i]->m_move.m_posY
		);

		//レーザー用配列添え字保存用
		int laser = -1;

		//壁は配列なので敵の弾の１つ１つと衝突判定を取る
		for (int j = 0; j <= m_pWallCount; j++) {
			//要素がNULLなら飛ばす
			if (m_pWalls[j] == NULL)
				continue;

			//有効フラグがfalseの」インスタンスも飛ばす
			if (m_pWalls[j]->m_activeFlag == false)
				continue;

			//壁の１つ分の衝突判定を行う際の位置を取得
			CBody wallCollisionBody = m_pWalls[j]->m_body.getApplyPositionBody(
				m_pWalls[j]->m_move.m_posX,
				m_pWalls[j]->m_move.m_posY
			);
			//衝突判定を行う
			if (playerCollisionBody.collision(&wallCollisionBody) == true) {
				//衝突している
				//壁の衝突判定の計算を行う
				
				switch (m_pPlayerBullets[i]->m_bulletType) {
				case BULLET_TYPE::PLAYER_EXPLOSION:
					
					//爆発タイプ切り替え
					m_pPlayerBullets[i]->m_bulletType = BULLET_TYPE::PLAYER_EXPLOSION_2;
					//画像の設定
					m_pPlayerBullets[i]->setTexture(IMAGE_FILE_EXPLOSION_2);
					//切り取る矩形
					m_pPlayerBullets[i]->m_chip = CChip(0, 0, 120, 120);
					m_pPlayerBullets[i]->setTextureRect(m_pWalls[j]->m_chip);
					//ステータスの設定
					m_pPlayerBullets[i]->m_status.set(1, 1, 1, 0);
					//移動データに初期速度の設定　停止状態
					m_pPlayerBullets[i]->m_move.setVel(0, 0);
					//アニメーションデータの初期化
					m_pPlayerBullets[i]->m_anime.set(10, 7, false);
					//衝突判定用データの初期化
					m_pPlayerBullets[i]->m_body.set(
						-20 * m_pPlayerChara->m_shotParam,
						20 * m_pPlayerChara->m_shotParam,
						20 * m_pPlayerChara->m_shotParam,
						-20 * m_pPlayerChara->m_shotParam
					);
					//画像サイズをレベル補正
					m_pPlayerBullets[i]->setScale(0.5f * m_pPlayerChara->m_shotParam);

					//取り外しフラグ有効
					m_pPlayerBullets[i]->m_delflg = true;
					//取り外しフレームカウント設定
					m_pPlayerBullets[i]->m_maxCount = 70;
					//エフェクトを表示する
					createEffect2(j, m_pPlayerBullets[i]->m_move.m_posX, m_pPlayerBullets[i]->m_move.m_posY);

					break;
				case BULLET_TYPE::PLAYER_EXPLOSION_2:
					
					break;
				case BULLET_TYPE::PLAYER_LASER:


					if (laser == -1) {
						//最初は必ず敵の添え字を代入
						laser = j;
					}
					else {
						//一番自機に近い敵に添え字を上書き
						if (m_pWalls[laser]->m_move.m_posX - m_pWalls[laser]->m_chip.size.width * 0.5f >=
							m_pWalls[j]->m_move.m_posX - m_pWalls[j]->m_chip.size.width * 0.5f) {
							laser = j;
						}
					}
					break;
				default:
					//通常弾、バック弾、散弾、誘導弾は消滅
					//プレイヤーの弾の有効フラグをfalseにする
					m_pPlayerBullets[i]->m_activeFlag = false;
					//エフェクトを表示する
					createEffect2(j, m_pPlayerBullets[i]->m_move.m_posX, m_pPlayerBullets[i]->m_move.m_posY);
					break;
				}


			}

		}
		//レーザーの場合ここで計算
		if (m_pPlayerBullets[i]->m_bulletType == BULLET_TYPE::PLAYER_LASER) {

			if (laserFlg == false) {
				//レーザーの有効フラグをfalseにする
				m_pPlayerBullets[i]->m_activeFlag = false;
				cocos2d::log("laser off");
				continue;
			}

			//敵より壁のｘ座標が低い場合 もしくは壁の判定が在り敵の判定が無い場合
			if (laser != -1 && laserIndex == -1 ||
				laser != -1 && laserIndex != -1 && m_pEnemyCharas[laserIndex]->m_move.m_posX > m_pWalls[laser]->m_move.m_posX) {
				//敵より壁のｘ座標が低い場合 もしくは壁の判定が在り敵の判定が無い場合

				//レーザーの長さ変更 壁の左端 - プレイヤーの右端
				m_pPlayerBullets[i]->m_chip.size.width = (m_pWalls[laser]->m_move.m_posX - m_pWalls[laser]->m_chip.size.width / 2) -
					(m_pPlayerChara->m_move.m_posX + m_pPlayerChara->m_chip.size.width / 2);

				if (m_pPlayerBullets[i]->m_activeFlag == true &&
					laserCounter <= this->m_frameCounter
					) {
					//レーザーダメージインターバル更新
					laserCounter = this->m_frameCounter + 5;

					//エフェクトを表示する	
					createEffect2(laser, (m_pWalls[laser]->m_move.m_posX - m_pWalls[laser]->m_chip.size.width / 2), m_pPlayerBullets[i]->m_move.m_posY);
				}
			}
			else if (laser == -1 && laserIndex != -1 ||
				laser != -1 && laserIndex != -1 && m_pEnemyCharas[laserIndex]->m_move.m_posX < m_pWalls[laser]->m_move.m_posX) {
				//壁より敵のｘ座標が低い場合 もしくは敵の判定が在り壁の判定が無い場合

				//レーザーの長さ変更 敵の左端 - プレイヤーの右端
				m_pPlayerBullets[i]->m_chip.size.width = (m_pEnemyCharas[laserIndex]->m_move.m_posX - m_pEnemyCharas[laserIndex]->m_body.m_left) -
					(m_pPlayerChara->m_move.m_posX + m_pPlayerChara->m_chip.size.width / 2);

				if (m_pPlayerBullets[i]->m_activeFlag == true &&
					laserCounter <= this->m_frameCounter
					) {
					//レーザーダメージインターバル更新
					laserCounter = this->m_frameCounter + 5;


					//敵の衝突判定の計算を行う
					m_pEnemyCharas[laserIndex]->hits(&m_pPlayerBullets[i]->m_status);

					//敵を倒せていたらスコアの計算を行う
					calculationScore(laserIndex);

					//エフェクトを表示する	
					createEffect(laserIndex);
				}
			}
		}
	}
}
// 壁と敵の弾の衝突
void CGameMain::collisionWallsAndEnemyBullets() {
	

	for (int i = 0; i <= m_pEnemyBulletCount; i++) {
		//要素がNULLなら飛ばす
		if (m_pEnemyBullets[i] == NULL)
			continue;

		//有効フラグがfalseの」インスタンスも飛ばす
		if (m_pEnemyBullets[i]->m_activeFlag == false)
			continue;

		//プレイヤーの衝突判定を行う際の位置を取得
		CBody playerCollisionBody = m_pEnemyBullets[i]->m_body.getApplyPositionBody(
			m_pEnemyBullets[i]->m_move.m_posX,
			m_pEnemyBullets[i]->m_move.m_posY
		);

		//壁は配列なので敵の弾の１つ１つと衝突判定を取る
		for (int j = 0; j <= m_pWallCount; j++) {
			//要素がNULLなら飛ばす
			if (m_pWalls[j] == NULL)
				continue;

			//有効フラグがfalseの」インスタンスも飛ばす
			if (m_pWalls[j]->m_activeFlag == false)
				continue;

			//壁の１つ分の衝突判定を行う際の位置を取得
			CBody wallCollisionBody = m_pWalls[j]->m_body.getApplyPositionBody(
				m_pWalls[j]->m_move.m_posX,
				m_pWalls[j]->m_move.m_posY
			);
			//衝突判定を行う
			if (playerCollisionBody.collision(&wallCollisionBody) == true) {
				//衝突している
				m_pEnemyBullets[i]->m_activeFlag = false;
				//エフェクトを表示する
				createEffect2(j, m_pEnemyBullets[i]->m_move.m_posX, m_pEnemyBullets[i]->m_move.m_posY);

			}

		}
	}
}


void CGameMain::stageStartFunc() {
	//=========================================================================
	//サウンドファイルのステージ切り替え時の読み込み
	//=========================================================================
	//次のステージのサウンドの読み込み
	switch (CGameMain::m_stageNo) {
	case 1:
		this->m_bgmid = AudioEngine::play2d(SOUND_FILE_BGM_1);
		break;
	case 2:
		this->m_bgmid = AudioEngine::play2d(SOUND_FILE_BGM_2);
		break;
	case 3:
		this->m_bgmid = AudioEngine::play2d(SOUND_FILE_BGM_3);
		break;
	}
	AudioEngine::setVolume(this->m_bgmid, BGM_VOLUME / 100.0f);
	//モードをステージ更新処理に切り替える
	this->m_stageMode = STAGE_MODE::UPDATE;
	
	//=========================================================================
	//マップのステージ切り替え時に関するコードの追加はここから
	//=========================================================================
	//次のステージマップの生成
	//マップの生成
	
	m_pMap = CMap::create(IMAGE_FILE_BACKGROUND);
	//スクロール速度の設定
	this->m_pMap->m_scrollMove.m_velX = 1.0f;
	//ループ設定(ループあり設定)
	this->m_pMap->m_isLoop = true;
	//レイヤーに取り付け
	m_backGroundLayer->addChild(this->m_pMap);
	//=========================================================================
	//壁のステージ切り替え時に関するコードの追加はここから
	//=========================================================================
	m_pWallXpos = 0;
	//=========================================================================
	//プレイヤーのステージ切り替え時に関するコードの追加はここから
	//=========================================================================
	//プレイヤーの有効フラグを上げる
	m_pPlayerChara->m_activeFlag = true;
	//プレイヤーを表示する
	m_pPlayerChara->setVisible(true);
	//プレイヤーの初期位置の設定
	m_pPlayerChara->m_move.setPos(320.0f, 240.0f);
	//初期位置の反映
	m_pPlayerChara->setPosition(m_pPlayerChara->m_move.m_posX, m_pPlayerChara->m_move.m_posY);
	//=========================================================================
	//ユーザーインターフェースのステージ切り替え時に関するコードの追加はここから
	//=========================================================================
	//HPラベルの表示
	m_pHpLabel->setVisible(true);
	//HPゲージの表示
	m_pHpGuage->setVisible(true);
	//スコアラベルの表示
	m_pScoreLabel->setVisible(true);
	//ステージラベルの表示
	m_pStageLabel->setVisible(true);
	//プレイヤー数ラベルの表示
	m_pPlayerLabel->setVisible(true);
	//ボム数ラベルの表示
	m_pBomLabel->setVisible(true);

	//サウンドの再生
	AudioEngine::setLoop(m_bgmid, true);

}

/**
*@desc ステージ更新処理
*@param 経過時間
*/
void CGameMain::stageUpdateFunc(float deltaTime_) {

	//=========================================================================
	//
	//	ここに更新処理のコードを追加していく
	//
	//=========================================================================
	//プレイ中
	this->inputFunc();

	//=========================================================================
	//	入力処理に関するコードの追加はここから
	//=========================================================================


	//=========================================================================
	//	壁の出現に関するコードの追加はここから
	//=========================================================================
	checkLaunchWall();

	//=========================================================================
	//	背景惑星の出現に関するコードの追加はここから
	//=========================================================================
	checkLaunchPlanet();

	//=========================================================================
	//	敵の出撃に関するコードの追加はここから
	//=========================================================================
	
	checkLaunchEnemy();
	checkEnemyAleart();

	//=========================================================================
	//	行動処理に関するコードの追加はここから
	//=========================================================================
	actionFunc();

	//=========================================================================
	//	移動処理に関するコードの追加はここから
	//=========================================================================
	//速度から位置を計算
	moveFunc();






	//=========================================================================
	//	画面端判定処理に関するコードの追加はここから
	//=========================================================================

	//画面端関数
	endOfScreen();


	//=========================================================================
	//	衝突判定に関するコードの追加はここから
	//=========================================================================
	//プレイヤーと敵の弾
	this->collisionPlayerAndEnemyBullets();
	//プレイヤーと敵
	this->collisionPlayerAndEnemies();
	//敵とプレイヤーの弾の衝突
	this->collisionEnemiesAndPlayerBullets();
	//プレイヤーとアイテムの衝突
	this->collisionPlayerAndItems();
	//プレイヤーと壁
	this->collisionPlayerAndWalls();
	//壁とプレイヤーの弾
	this->collisionWallsAndPlayerBullets();
	//壁と敵の弾
	this->collisionWallsAndEnemyBullets();
	//=========================================================================
	//	敵の弾の発射に関するコードの追加はここから
	//=========================================================================
	shotEnemyBullet();


	//=========================================================================
	//	アニメーション処理に関するコードの追加はここから
	//=========================================================================
	//プレイヤーキャラのアニメーション

	//アニメーション関数
	animationFunc();

	//=========================================================================
	//	非表示に関するコードの追加はここから
	//=========================================================================

	if (m_pPlayerChara->m_activeFlag == false) {
		//既に非表示の場合は非表示処理は行わない
		if (m_pPlayerChara->isVisible() == true) {
			//非表示にする
			m_pPlayerChara->setVisible(false);
		}
	}
	//=========================================================================
	//プレイヤー復活に関するコードの追加はここから
	//=========================================================================
	if (m_pPlayerChara->m_activeFlag == false) {
		playerCount--;

		m_pPlayerChara->m_activeFlag = true;

		if (playerCount >= 0) {
			//プレイヤー残機がある場合
			m_pPlayerChara->m_status.set(200, 200, 10, m_pPlayerChara->m_status.getScore());
			m_pPlayerChara->setVisible(true);
			m_pPlayerChara->m_move.setPos(-20, 240);
			m_pPlayerChara->setPosition(-20, 240);
			m_pPlayerChara->m_move.setVel(1, 0);
		}
		else {
			//プレイヤー残機がない場合
			m_pPlayerChara->m_move.setVel(0, 0);
		}

		m_pPlayerChara->m_move.setVel(1, 0);
		resurrection = true;
		resCount = 180;
	}


	//=========================================================================
	//	取り外し処理に関するコードの追加はここから
	//=========================================================================
	//プレイヤーの弾のレイヤーからの取り外し処理
	checkActiveFlagAndRemove();


	//=========================================================================
	//	計算用データを反映に関するコードの追加はここから
	//=========================================================================
	this->applyFunc();


	//=========================================================================
	//	ユーザーインターフェースの初期化に関するコードの追加はここから
	//=========================================================================


	//フレームカウンターの更新
	this->m_frameCounter++;
	//壁カウンターの更新
	this->m_wallCounter += MapData::WALL_SPEED;
	//サウンドディレイカウントダウン
	if (soundDeray)
		soundDeray--;
}

void CGameMain::stagePauseFunc() {
	//停止中
	this->inputFunc2();
	//カーソルNULLチェック
	if (m_pCursor) {
		m_pCursor->moveFunc();
		m_pCursor->animationFunc();
		m_pCursor->applyFunc();

		//画像点滅
		//ボタンが押されていたらラベル点滅開始
		if (p_scene && !SCENE_END) {

			c_frameCounter++;

			if (c_frameCounter > 5) {
				//点滅確認
				if (flashingflg) {
					pLavelArray[m_pCursor->p_y]->setColor(Color3B(0, 200, 200));
					flashingflg = false;
				}
				else {
					pLavelArray[m_pCursor->p_y]->setColor(Color3B(200, 200, 0));
					flashingflg = true;
				}
				//点滅カウントアップ
				flashing++;
				//フレームカウント初期化
				c_frameCounter = 0;
			}
			//点滅終了
			if (flashing > 5) {
				flashingflg = false;
				p_scene = false;
				flashing = 0;

				//画面遷移

				Scene* pScene;
				switch (m_pCursor->p_y) {
				case 0:
					//EXIT
					//ゲームメインへ
					//音楽エンジン終了回避
					audioFlug = false;

					//遷移中終了回避
					SCENE_END = true;
					//タイトルBGMフラグを戻す
					CTitle::TitleBgm = -1;

					//通常プレイならリプレイ保存
					if (mode == 0) {
						//リプレイ保存
						REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4] = m_frameCounter;
						
						CReplaySelect::replay_flg = true;

					}

					//スコア登録
					if (mode == 0 && m_pPlayerChara->m_status.getScore() > SCORE) {
						cocos2d::log("score=%d", m_pPlayerChara->m_status.getScore());
						//config.datに設定を保存
						int buf[3] = { BGM_VOLUME ,SE_VOLUME,m_pPlayerChara->m_status.getScore() };
						//ファイルポインタ
						FILE *file1;
						file1 = fopen("config.dat", "wb");
						fwrite(buf, sizeof(int), 3, file1);
						fclose(file1);
						SCORE = m_pPlayerChara->m_status.getScore();
					}
					//タイトルBGMフラグを戻す
					CTitle::TitleBgm = -1;

					this->unscheduleUpdate();
					if (mode == 0) {
						//タイトル画面に
						pScene = CReplaySelect::createScene();
					}
					else {
						//リプレイ画面に
						pScene = CReplay::createScene();
					}
					Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
					break;
				case 1:
					//REDO

					
					CGameMain::mode = mode >= 3 ? 2 : mode;
					if (mode == 0) {
						//ステージナンバー設定
						CGameMain::m_stageNo = 1;

						//プレイヤーステータス初期化
						CGameMain::m_hp = 200;
						CGameMain::m_maxHp = 200;
						CGameMain::m_attackPt = 1;
						CGameMain::m_score = 0;
						CGameMain::m_speed = 4;
						CGameMain::playerCount = 2;
						CGameMain::bom = 3;
						//攻撃レベル設定
						CGameMain::pweponLevel[0] = 0;		//NORMAL
						CGameMain::pweponLevel[1] = 0;		//EXPLOSION
						CGameMain::pweponLevel[2] = 0;		//BACK
						CGameMain::pweponLevel[3] = 0;		//LASER
						CGameMain::pweponLevel[4] = 0;		//INDCTION
						CGameMain::pweponLevel[5] = 0;		//MULTIPLE
					}


					//遷移中終了回避
					SCENE_END = true;

					//BGM停止
					AudioEngine::stopAll();
					this->unscheduleUpdate();
					pScene = CStageTitle::createScene();
					Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
					break;
				case 2:
					//PLAY
					//モードを一時停止解除に変更
					this->m_stageMode = STAGE_MODE::UPDATE;
					//音一時停止解除
					AudioEngine::resumeAll();
					break;
				}

				//ポーズ画面取り外し
				pLavelArray[0]->removeFromParent();
				pLavelArray[1]->removeFromParent();
				pLavelArray[2]->removeFromParent();
				m_pCursor->removeFromParent();
				pLavelArray[0] = NULL;
				pLavelArray[1] = NULL;
				pLavelArray[2] = NULL;
				m_pCursor = NULL;
				

			}

		}
	}

}

void CGameMain::gameOverFunc() {
	//停止中
	this->inputFunc2();
	//カーソルNULLチェック
	if (m_pCursor) {
		m_pCursor->moveFunc();
		m_pCursor->animationFunc();
		m_pCursor->applyFunc();

		//画像点滅
		//ボタンが押されていたらラベル点滅開始
		if (p_scene && !SCENE_END) {

			c_frameCounter++;

			if (c_frameCounter > 5) {
				//点滅確認
				if (flashingflg) {
					pLavelArray[m_pCursor->p_y]->setColor(Color3B(0, 200, 200));
					flashingflg = false;
				}
				else {
					pLavelArray[m_pCursor->p_y]->setColor(Color3B(200, 200, 0));
					flashingflg = true;
				}
				//点滅カウントアップ
				flashing++;
				//フレームカウント初期化
				c_frameCounter = 0;
			}
			//点滅終了
			if (flashing > 5) {
				flashingflg = false;
				p_scene = false;
				flashing = 0;

				//画面遷移

				Scene* pScene;
				switch (m_pCursor->p_y) {
				case 0:
					//EXIT
					//ゲームメインへ
					//音楽エンジン終了回避
					audioFlug = false;

					//遷移中終了回避
					SCENE_END = true;
					//タイトルBGMフラグを戻す
					CTitle::TitleBgm = -1;

					//通常プレイならリプレイ保存
					if (mode == 0) {
						//リプレイ保存
						//REPLAY_DATA[1] = m_frameCounter;
						//リプレイ保存
						REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4] = m_frameCounter;
						
						CReplaySelect::replay_flg = true;
					}
					//スコア登録
					if (mode == 0 && m_pPlayerChara->m_status.getScore() > SCORE) {
						cocos2d::log("score=%d", m_pPlayerChara->m_status.getScore());
						//config.datに設定を保存
						int buf[3] = { BGM_VOLUME ,SE_VOLUME,m_pPlayerChara->m_status.getScore() };
						//ファイルポインタ
						FILE *file1;
						file1 = fopen("config.dat", "wb");
						fwrite(buf, sizeof(int), 3, file1);
						fclose(file1);
						SCORE = m_pPlayerChara->m_status.getScore();
					}
					this->unscheduleUpdate();
					if (mode == 0) {
						//タイトル画面に
						pScene = CReplaySelect::createScene();
					}
					else {
						//リプレイ画面に
						pScene = CReplay::createScene();
					}

					Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
					break;
				case 1:
					//REDO

					
					//音楽エンジン終了回避
					audioFlug = false;

					//遷移中終了回避
					SCENE_END = true;

					CGameMain::mode = mode >= 3 ? 2 : mode;
					if (mode == 0) {
						//ステージナンバー設定
						CGameMain::m_stageNo = 1;

						//プレイヤーステータス初期化
						CGameMain::m_hp = 200;
						CGameMain::m_maxHp = 200;
						CGameMain::m_attackPt = 1;
						CGameMain::m_score = 0;
						CGameMain::m_speed = 4;
						CGameMain::playerCount = 2;
						CGameMain::bom = 3;
						//攻撃レベル設定
						CGameMain::pweponLevel[0] = 0;		//NORMAL
						CGameMain::pweponLevel[1] = 0;		//EXPLOSION
						CGameMain::pweponLevel[2] = 0;		//BACK
						CGameMain::pweponLevel[3] = 0;		//LASER
						CGameMain::pweponLevel[4] = 0;		//INDCTION
						CGameMain::pweponLevel[5] = 0;		//MULTIPLE
					}

					//BGM停止
					AudioEngine::stopAll();
					//タイトルBGMフラグ戻し
					CTitle::TitleBgm = -1;
					this->unscheduleUpdate();
					pScene = CStageTitle::createScene();
					Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
					break;
				}

				//ポーズ画面取り外し
				pLavelArray[0]->removeFromParent();
				pLavelArray[1]->removeFromParent();
				m_pCursor->removeFromParent();
				pLavelArray[0] = NULL;
				pLavelArray[1] = NULL;
				m_pCursor = NULL;
				

			}

		}
	}

}


void CGameMain::stageEndFunc() {
	//=======================================================
	//サウンドに関するコードの追加はここから
	//=======================================================
	//背景の停止
	AudioEngine::stop(this->m_bgmid);
	//全ての効果音の停止
	AudioEngine::stopAll();
	//=======================================================
	//プレイヤーキャラクターに関するコードの追加はここから
	//=======================================================
	//プレイヤーの有効フラグを下げて画面から非表示
	if (m_pPlayerChara != NULL) {
		//有効フラグもゲームの作りによっては下げる必要もない
		m_pPlayerChara->m_activeFlag = false;

		//プレイヤーは使いまわすのでいちいち削除せず非表示にするだけ
		m_pPlayerChara->setVisible(false);

	}
	//復活フラグ初期化
	resurrection = false;
	//復活カウント初期化
	resCount = 0;
	//プレイヤー数初期化
	playerCount = 2;
	//ボムカウント初期化
	bomCount = 0;
	//ボム数初期化
	bom = 3;
	//ステータス初期化
	m_pPlayerChara->m_status.set(20, 20, 10, 0, 2);
	//攻撃レベル設定
	pweponLevel[0] = 0;		//NORMAL
	pweponLevel[1] = 0;		//EXPLOSION
	pweponLevel[2] = 0;		//BACK
	pweponLevel[3] = 0;		//LASER
	pweponLevel[4] = 0;		//INDCTION
	pweponLevel[5] = 0;		//MULTIPLE
	pweponLevelLavel[0]->setString(cocos2d::StringUtils::format("Level %d", 1));
	pweponLevelLavel[1]->setString(cocos2d::StringUtils::format("Level %d", 1));
	pweponLevelLavel[2]->setString(cocos2d::StringUtils::format("Level %d", 1));
	pweponLevelLavel[3]->setString(cocos2d::StringUtils::format("Level %d", 1));
	pweponLevelLavel[4]->setString(cocos2d::StringUtils::format("Level %d", 1));
	pweponLevelLavel[5]->setString(cocos2d::StringUtils::format("Level %d", 1));
	//=======================================================
	//プレイヤーバレットに関するコードの追加はここから
	//=======================================================
	//プレイヤーバレットをレイヤーから取り外してNULLを代入
	for (int i = 0; i < CBullet::MAX_BULLET; i++) {
		if (m_pPlayerBullets[i] == NULL) {
			continue;
		}

		m_pPlayerBullets[i]->removeFromParent();
		m_pPlayerBullets[i] = NULL;
	}
	//カウントリセット
	m_pPlayerBulletCount = 0;
	//=======================================================
	//敵キャラクターに関するコードの追加はここから
	//=======================================================
	//敵キャラクターをレイヤーから取り外してNULLを代入
	for (int i = 0; i < CEnemyCharacter::MAX_ENEMY; i++) {
		if (m_pEnemyCharas[i] == NULL) {
			continue;
		}

		m_pEnemyCharas[i]->removeFromParent();
		m_pEnemyCharas[i] = NULL;
	}
	//カウントリセット
	m_pEnemyCount = 0;
	//=======================================================
	//エネミーバレットに関するコードの追加はここから
	//=======================================================
	//エネミーバレットーをレイヤーから取り外してNULLを代入
	for (int i = 0; i < CBullet::MAX_BULLET; i++) {
		if (m_pEnemyBullets[i] == NULL) {
			continue;
		}

		m_pEnemyBullets[i]->removeFromParent();
		m_pEnemyBullets[i] = NULL;
	}
	//カウントリセット
	m_pEnemyBulletCount = 0;
	//=======================================================
	//エフェクトに関するコードの追加はここから
	//=======================================================
	//エフェクトをレイヤーから取り外してNULLを代入
	for (int i = 0; i < CEfect::MAX_EFFECT; i++) {
		if (m_pEffects[i] == NULL) {
			continue;
		}

		m_pEffects[i]->removeFromParent();
		m_pEffects[i] = NULL;
	}
	//カウントリセット
	m_pEfectCount = 0;
	//=======================================================
	//アイテムに関するコードの追加はここから
	//=======================================================
	//アイテムをレイヤーから取り外してNULLを代入
	for (int i = 0; i < CItem::MAX_ITEM; i++) {
		if (m_pItems[i] == NULL) {
			continue;
		}

		m_pItems[i]->removeFromParent();
		m_pItems[i] = NULL;
	}
	//カウントリセット
	m_pItemCount = 0;
	//=======================================================
	//壁に関するコードの追加はここから
	//=======================================================
	//壁をレイヤーから取り外してNULLを代入
	for (int i = 0; i < CWall::MAX_WALL; i++) {
		if (m_pWalls[i] == NULL) {
			continue;
		}

		m_pWalls[i]->removeFromParent();
		m_pWalls[i] = NULL;
	}
	//カウントリセット
	m_pItemCount = 0;
	//=======================================================
	//敵出撃データに関するコードの追加はここから
	//=======================================================
	//敵出撃データの解放
	SAFE_DELETE_ARRAY(m_pEnemyLaunchData);

	//敵出撃インデックスのリセット
	m_enemyLaunchIndex = 0;

	//フレームカウンターのリセット
	m_frameCounter = 0;
	//=======================================================
	//マップに関するコードの追加はここから
	//=======================================================
	//マップをレイヤーから取り外してNULLを代入
	if (m_pMap != NULL) {
		m_pMap->removeFromParent();
		m_pMap = NULL;
	}
	//=======================================================
	//壁に関するコードの追加はここから
	//=======================================================
	//壁インデックスのリセット
	m_pWallXpos = 0;

	//壁カウンターのリセット
	m_wallCounter = 0;
	//=======================================================
	//UIに関するコードの追加はここから
	//=======================================================
	//全てのUIをいったん非表示にする
	m_pHpLabel->setVisible(false);
	m_pHpGuage->setVisible(false);
	m_pScoreLabel->setVisible(false);
	m_pStageLabel->setVisible(false);
	m_pPlayerLabel->setVisible(false);
	m_pBomLabel->setVisible(false);

	//=======================================================
	//リプレイに関するコードの追加はここから
	//=======================================================
	//リプレイ配列初期化
	if (mode == 0) {
		for (int i = 0; i < 4010; i++) {
			REPLAY_DATA[i] = 0;
		}
		REPLAY_DATA[0] = MapData::m_seed;
	}

	//ステージ毎にシード値設定
	srand(MapData::m_seed);
	for (int i = 0; i < CGameMain::m_stageNo; i++) {
		rand();
	}
	srand(rand());

	//=======================================================
	//ステージの切り替えに関するコードの追加はここから
	//=======================================================
	if (this->m_stageNo >= CGameMain::MAX_STAGE_COUNT) {
		//TODO:ここでエンディングシーンに進む
	}
	else {
		//ステージを更新(インクリメントするだけ)
		this->m_stageNo++;

		//モードをステージ開始に切り替える
		this->m_stageMode = STAGE_MODE::START;
	}

}