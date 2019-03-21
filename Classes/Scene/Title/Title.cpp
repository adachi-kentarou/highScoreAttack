#include "Title.h"
#include "Constants.h"
#include "Scene/GameMain/GameMain.h"
#include "Lib/InputManager/InputManager.h"
#include "Lib/InputManager/InputJoystick.h"
#include "Scene/Option/Option.h"
#include "Scene/Loading/Loading.h"
#include "Data/MapData/MapData.h"
#include "Scene/StageTitle/StageTitle.h"
#include "Scene/Replay/Replay.h"
#include "Scene/ReplaySelect/ReplaySelect.h"
#include <time.h>
//cocos2d::の省略
using namespace cocos2d;

//AudioEngineのインクルード
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

//デストラクタ
CTitle::~CTitle() {

	cocos2d::log("load end");
	//Director::getInstance()->pushScene(SCENE);
}
/**
*@desc シーンの生成
*@return CTitleレイヤーを内包したシーンクラスインスタンス
*@tips 静的メンバ関数
*/
cocos2d::Scene* CTitle::createScene() {
	//シーンの生成
	cocos2d::Scene* pScene = cocos2d::Scene::create();

	//CTitleレイヤーの生成
	CTitle* pLayer = CTitle::create();

	//Ctitleレイヤーをシーンに取り付ける
	pScene->addChild(pLayer);

	//生成したシーンを返す
	return pScene;
}

/**
*	@desc	キーボードのキーを押した際のイベント
*	@param	キーコード
*	@param	イベント
*/
void CTitle::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {

	// 入力管理に入力処理を委託
	CInputManager::getInstance()->onKeyPressed(keyCode);
}

/**
*	@desc	キーボードのキーを離した際のイベント
*	@param	キーコード
*	@param	イベント
*/
void CTitle::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event) {

	// 入力管理に入力処理を委託
	CInputManager::getInstance()->onKeyReleased(keyCode);
}
/*
void CTitle::onEnter(){
cocos2d::log("enter");
}
*/

//タイトルBGM
int CTitle::TitleBgm = -1;
//デモ用シード値
int CTitle::Rand = 0;
/**
*@desc 初期化
*@return true...成功false...失敗
*/
bool CTitle::init() {

	//update関数(更新処理関数)呼び出し設定
	this->scheduleUpdate();
	// キーボード入力イベント受け取り設定
	this->setKeyboardEnabled(true);

	//===================================================
	//ここから初期化、初期設定のコードを追加
	//===================================================
	//タイトル背景の生成と取り付け

	//CCRenderTextureを作成
	CCRenderTexture* pRenderTexture = CCRenderTexture::create(640, 480);
	pRenderTexture->setPosition(320, 240);
	pRenderTexture->beginWithClear(0, 0, 0, 255);

	//描画終了
	pRenderTexture->end();
	//レイヤーに取り付け
	this->addChild(pRenderTexture);


	//===================================================
	//背景に関するコードの追加はここから
	//===================================================


	//エフェクトの生成
	background = CEfect::create();
	//画像の設定
	background->setTexture(IMAGE_FILE_TITLE_BACKGROUND);

	//切り取る矩形
	background->m_chip = CChip(0, 0, 640, 480);
	background->setTextureRect(background->m_chip);
	//移動データに初期位置の設定
	background->m_move.setPos(320, 240);
	//移動データに初期速度の設定；
	background->m_move.setVel(0, 0);

	//アニメーションデータの初期化
	background->m_anime.set(2, 10, true);

	//初期位置を判定
	background->setPosition(320, 240);

	//有効フラグにtrueを入れる
	background->m_activeFlag = true;

	//画像横個数
	background->maxX = 2;

	//背景張り付け
	this->addChild(background);

	//===================================================
	//タイトルラベルに関するコードの追加はここから
	//===================================================
	//タイトルラベルの生成と取り付け
	Label* pTitleLabel = Label::createWithTTF("High Score Attack", FONT_FILE_STARWARS, 62);
	//初期位置の設定
	pTitleLabel->setPosition(320.0f, 360.0f);
	//文字色の設定
	pTitleLabel->setColor(Color3B(0, 200, 200));
	//レイヤーに取り付け
	this->addChild(pTitleLabel);
	//===================================================
	//スコアラベルに関するコードの追加はここから
	//===================================================
	//スコアラベルの生成と取り付け
	Label* pCcoreLabel = Label::createWithTTF(StringUtils::format("High Score %d", SCORE), FONT_FILE_STARWARS, 30);
	//初期位置の設定
	pCcoreLabel->setPosition(320.0f, 260.0f);
	//文字色の設定
	pCcoreLabel->setColor(Color3B(200, 80, 80));
	//レイヤーに取り付け
	this->addChild(pCcoreLabel);


	//===================================================
	//タイトルラベルに関するコードの追加はここから
	//===================================================
	//スタートタイトルラベルの生成と取り付け
	pStartLabel = cocos2d::Label::createWithTTF(m_gameModeArray[0], FONT_FILE_STARWARS, 31);
	//初期位置の設定
	pStartLabel->setPosition(320.0f, 200.0f);
	//文字色の設定
	pStartLabel->setColor(Color3B(0, 200, 200));
	//レイヤーに取り付け
	this->addChild(pStartLabel);

	//オプションタイトルラベルの生成と取り付け
	pOptionLabel = cocos2d::Label::createWithTTF("OPTION", FONT_FILE_STARWARS, 31);
	//初期位置の設定
	pOptionLabel->setPosition(320.0f, 160.0f);
	//文字色の設定
	pOptionLabel->setColor(Color3B(0, 200, 200));
	//レイヤーに取り付け
	this->addChild(pOptionLabel);

	//エンドタイトルラベルの生成と取り付け
	pReplayLabel = cocos2d::Label::createWithTTF("REPLAY", FONT_FILE_STARWARS, 31);
	//初期位置の設定
	pReplayLabel->setPosition(320.0f, 120.0f);
	//文字色の設定
	pReplayLabel->setColor(Color3B(0, 200, 200));
	//レイヤーに取り付け
	this->addChild(pReplayLabel);

	//エンドタイトルラベルの生成と取り付け
	pEndLabel = cocos2d::Label::createWithTTF("END", FONT_FILE_STARWARS, 31);
	//初期位置の設定
	pEndLabel->setPosition(320.0f, 80.0f);
	//文字色の設定
	pEndLabel->setColor(Color3B(0, 200, 200));
	//レイヤーに取り付け
	this->addChild(pEndLabel);
	//配列にラベルを格納
	pLavelArray[3] = pStartLabel;
	pLavelArray[2] = pOptionLabel;
	pLavelArray[1] = pReplayLabel;
	pLavelArray[0] = pEndLabel;

	//===================================================
	//カーソルに関するコードの追加はここから
	//===================================================
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
		3,			//カーソルのY最大
		0,			//カーソルのX位置
		3,			//カーソルのY位置
		240,		//カーソルのX座標
		80,		//カーソルのY座標
		0.0f,		//X移動サイズ
		40.0f,		//Y移動サイズ
		5,			//移動アニメーションフレーム
		true,		//横ループ
		true,		//縦ループ
		10,			//低速待ちフレーム
		5			//高速待ちフレーム
	);

	this->addChild(m_pCursor);

	//フレームカウンター初期化
	m_frameCounter = 0;

	//ボタン押し判定初期化
	CInputJoystick::m_flg = true;


	//===================================================
	//BGM設定のコードを追加
	//===================================================

	cocos2d::log("title bgm------------- %d", TitleBgm);
	if (TitleBgm == -1) {
		TitleBgm = AudioEngine::play2d(SOUND_FILE_TITLE);
		//ループの設定(true...ループする　false...ループしない)
		AudioEngine::setLoop(this->m_bgmid, true);
		AudioEngine::setVolume(TitleBgm, BGM_VOLUME / 100.0f);
	}

	AudioEngine::setMaxAudioInstance(32);

	//===================================================
	//ゲームモード初期化
	//===================================================
	GAME_MODE = 0;

	//===================================================
	//ここまで初期化、初期設定のコードを追加
	//===================================================
	
	return true;
}

/**
*@desc ゲームメインに遷移
@param タイトルレイヤーのインスタンス
*@tips スタートボタンが押されたときに呼び出される
*/
void CTitle::callbackChangeGameMain(cocos2d::Ref* pSender) {
	OutputDebugString(L"スタートボタンが押されたよ\n");

	//音楽エンジン終了回避
	audioFlug = false;

	//遷移中終了回避
	SCENE_END = true;

	//BGM停止
	AudioEngine::stopAll();

	Scene* pScene = CGameMain::createScene();
	Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));

}

/**
*@desc 更新処理
*@param 経過時間
*/
void CTitle::update(float deltaTime) {

	//===================================================
	//ここに更新処理のコードを追加していく
	//===================================================
	inputFunc();
	moveFunc();
	animetionFunc();
	applyFunc();

}


void CTitle::onEnterTransitionDidFinish() {
	cocos2d::log("senni finish");
	//終了有効化
	SCENE_END = false;
}


/**
*@desc ゲーム終了
*@param タイトルレイヤーのインスタンス
@tips ゲーム終了ボタンが押されたときに呼び出される
*/
void CTitle::callbackEndGame(cocos2d::Ref* pSender) {
	OutputDebugString(L"ゲームの終了ボタンが押されたよ\n");
	Director::getInstance()->end();
}
//キー入力
void CTitle::inputFunc() {

	//シーン切り替えフラグ
	if (p_scene || SCENE_END)
		return;

	//カーソルの入力処理
	m_pCursor->inputFunc();
	if (!pEndLabel || CInputJoystick::m_flg)
		return;
	
	//移動終了フラグが有効ならば難易度変更処理 上下カーソルを押してないこと
	if (m_pCursor->moveflg && !CInputJoystick::m_up && !CInputJoystick::m_down &&
		m_pCursor->p_y == 3 && (CInputJoystick::m_left || CInputJoystick::m_right)) {
		int m_change = 0;
		//ボリューム変更
		if (CInputJoystick::m_left == true) {
			m_change = -1;
		}
		else if (CInputJoystick::m_right == true) {
			m_change = 1;
		}
		else if (CInputJoystick::m_left == false && CInputJoystick::m_right == false) {
			m_change = 0;
		}
		GAME_MODE += m_change;

		if (GAME_MODE < 0) {
			GAME_MODE = m_gameModeArray.size() - 1;
		}
		else if (GAME_MODE >= m_gameModeArray.size()) {
			GAME_MODE = 0;
		}

		pStartLabel->setString(cocos2d::StringUtils::format(m_gameModeArray[GAME_MODE]));

		int seid = AudioEngine::play2d(SOUND_FILE_CURSOR_1);
		AudioEngine::setVolume(seid, SE_VOLUME / 100.0f);
		
	}


	//デモ画面移動
	if (m_demoCount == 900) {
		

		char* m_pStr[10] = {
			"replay_10.dat",
			"replay_9.dat",
			"replay_8.dat",
			"replay_7.dat",
			"replay_6.dat",
			"replay_5.dat",
			"replay_4.dat",
			"replay_3.dat",
			"replay_2.dat",
			"replay_1.dat"
		};
		std::vector<char*>m_pStr2;
		struct stat st;
		FILE *file1;
		for (int i = 0; i < 10; i++) {
			if (stat(m_pStr[i], &st) == 0) {
				m_pStr2.push_back(m_pStr[i]);
			}
		}
		if (m_pStr2.size() == 0) {
			//データが無ければカウントリセット
			m_demoCount = 0;
		}
		else {

			//データがあればランダムに選択
			audioFlug = false;

			//遷移中終了回避
			SCENE_END = true;


			srand(time(NULL));
			file1 = fopen(m_pStr2[rand() % m_pStr2.size()], "rb");
			fread(REPLAY_DATA, sizeof(int), 12020, file1);
			fclose(file1);
			int stage = 0;
			if (REPLAY_DATA[1 + (0) * 4] != 0) {
				stage++;
			}
			if (REPLAY_DATA[1 + (1) * 4] != 0) {
				stage++;
			}
			if (REPLAY_DATA[1 + (2) * 4] != 0) {
				stage++;
			}

			//乱数
			Rand = rand();

			//モードリプレイ
			CGameMain::mode = 5;
			//ステージナンバー設定
			CGameMain::m_stageNo = rand() % stage + 1;

			this->unscheduleUpdate();
			pScene = CStageTitle::createScene();
			Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));

		}

		
	}
	else {
		m_demoCount++;
	}
	//入力があったらカウントリセット
	if (CInputJoystick::m_change ||
		CInputJoystick::m_down ||
		CInputJoystick::m_left ||
		CInputJoystick::m_pause ||
		CInputJoystick::m_shot ||
		CInputJoystick::m_right ||
		CInputJoystick::m_stage ||
		CInputJoystick::m_up
		) {
		m_demoCount = 0;
	}


	if (CInputJoystick::m_shot == true) {
		if (p_zFlg == false) {
			p_zFlg = true;
			cocos2d::log("push");
		}
	}
	else {
		if (p_zFlg == true) {
			//ボタンを押した状態から離したら
			p_zFlg = false;
			cocos2d::log("%d", m_pCursor->p_input);
			//カーソル入力待ちの時にボタン押し判定
			if (m_pCursor->p_input == 0) {
				//カーソルSE
				if (!p_scene) {
					int seId = AudioEngine::play2d(SOUND_FILE_CURSOR_2);
					AudioEngine::setVolume(seId, SE_VOLUME / 100.0f);
				}
				//シーン切り替えフラグ有効
				p_scene = true;
			}

		}

	}

}

//移動
void CTitle::moveFunc() {
	if (!m_pCursor || !background)
		return;

	background->moveFunc();
	m_pCursor->moveFunc();
}

//アニメーション
void CTitle::animetionFunc() {

	if (!m_pCursor || !background)
		return;

	background->animationFunc();

	m_pCursor->animationFunc();
}

//移動値反映
void CTitle::applyFunc() {
	if (!m_pCursor || !background)
		return;

	background->applyFunc();
	m_pCursor->applyFunc();

	//ボタンが押されていたらラベル点滅開始
	if (p_scene) {

		m_frameCounter++;

		if (m_frameCounter > 5) {
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
			m_frameCounter = 0;
		}
		//点滅終了
		if (flashing > 5) {
			flashingflg = false;
			//p_scene = false;
			flashing = 0;
			//画面遷移
			switch (m_pCursor->p_y) {
			case 0:
			{
				//BGMの解放
				AudioEngine::uncacheAll();

				//AudioEngineの終了
				AudioEngine::end();

				//終了
				this->unscheduleUpdate();
				OutputDebugString(L"ゲームの終了ボタンが押されたよ\n");
				Director::getInstance()->end();
			}

			break;
			case 1:

			{

				{

					//ゲームメインへ
					//音楽エンジン終了回避
					audioFlug = false;

					//遷移中終了回避
					SCENE_END = true;

					//ファイル読み込みフラグ設定
					CReplaySelect::replay_flg = false;

					this->unscheduleUpdate();
					//pScene = CReplay::createScene();
					pScene = CReplaySelect::createScene();
					Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));

				}

			}

			break;
			case 2:
			{
				//オプションへ
				//音楽エンジン終了回避
				audioFlug = false;

				//遷移中終了回避
				SCENE_END = true;

				this->unscheduleUpdate();
				pScene = COption::createScene();

				Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
			}

			break;
			case 3:
			{
				//ゲームメインへ
				//音楽エンジン終了回避
				audioFlug = false;

				//遷移中終了回避
				SCENE_END = true;

				//モードリプレイ
				CGameMain::mode = 0;

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
				CGameMain::weponSelect = 0;
				//乱数シード設定
				MapData::m_seed = time(NULL);
				MapData::m_seed >>= 2;
				MapData::m_seed <<= 2;
				MapData::m_seed += GAME_MODE;
				cocos2d::log("game mode = %d", MapData::m_seed & 3);

				//BGM停止
				AudioEngine::stopAll();
				this->unscheduleUpdate();
				//pScene = CGameMain::createScene();
				pScene = CStageTitle::createScene();
				Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
			}


			break;
			}

		}

	}
}

