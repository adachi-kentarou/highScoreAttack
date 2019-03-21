#include "Title2.h"
#include "Constants.h"
#include "Scene/GameMain/GameMain.h"
#include "Lib/InputManager/InputManager.h"
#include "Lib/InputManager/InputJoystick.h"
#include "Scene/Option/Option.h"
#include "Scene/Loading/Loading.h"
#include "Data/MapData/MapData.h"
#include "Scene/StageTitle/StageTitle.h"
#include "Scene/Replay/Replay.h"
//cocos2d::の省略
using namespace cocos2d;

//AudioEngineのインクルード
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

//デストラクタ
CTitle2::~CTitle2() {
	//BGMの停止
	//AudioEngine::stopAll();
	/*
	if (audioFlug == true) {
	//BGMの解放
	AudioEngine::uncacheAll();

	//AudioEngineの終了
	AudioEngine::end();
	}
	*/

	cocos2d::log("load end");
	//Director::getInstance()->pushScene(SCENE);
}
/**
*@desc シーンの生成
*@return CTitleレイヤーを内包したシーンクラスインスタンス
*@tips 静的メンバ関数
*/
cocos2d::Scene* CTitle2::createScene() {
	//シーンの生成
	cocos2d::Scene* pScene = cocos2d::Scene::create();

	//CTitleレイヤーの生成
	CTitle2* pLayer = CTitle2::create();

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
void CTitle2::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {

	// 入力管理に入力処理を委託
	CInputManager::getInstance()->onKeyPressed(keyCode);
}

/**
*	@desc	キーボードのキーを離した際のイベント
*	@param	キーコード
*	@param	イベント
*/
void CTitle2::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event) {

	// 入力管理に入力処理を委託
	CInputManager::getInstance()->onKeyReleased(keyCode);
}
/*
void CTitle::onEnter(){
cocos2d::log("enter");
}
*/

//タイトルBGM
int CTitle2::TitleBgm = -1;

/**
*@desc 初期化
*@return true...成功false...失敗
*/
bool CTitle2::init() {

	//update関数(更新処理関数)呼び出し設定
	this->scheduleUpdate();
	// キーボード入力イベント受け取り設定
	this->setKeyboardEnabled(true);

	//===================================================
	//ここから初期化、初期設定のコードを追加
	//===================================================
	//タイトル背景の生成と取り付け
	
	Sprite* pBg = Sprite::create(IMAGE_FILE_TITLE_BG);
	//初期位置の設定
	pBg->setPosition(320.0f,240.0f);
	//レイヤーに取り付け
	this->addChild(pBg);
	


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
	pStartLabel = cocos2d::Label::createWithTTF("START", FONT_FILE_STARWARS, 31);
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
	/*
	for (int i = 0; i < 100;i++) {
	cocos2d::log("rep= %d",REPLAY_DATA[i]);
	}
	*/

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
void CTitle2::callbackChangeGameMain(cocos2d::Ref* pSender) {
	OutputDebugString(L"スタートボタンが押されたよ\n");

	//音楽エンジン終了回避
	audioFlug = false;

	//遷移中終了回避
	SCENE_END = true;

	//BGM停止
	AudioEngine::stopAll();

	Scene* pScene = CGameMain::createScene();
	Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
	//Director::getInstance()->replaceScene(pScene);
}

/**
*@desc 更新処理
*@param 経過時間
*/
void CTitle2::update(float deltaTime) {

	//===================================================
	//ここに更新処理のコードを追加していく
	//===================================================
	inputFunc();
	moveFunc();
	animetionFunc();
	applyFunc();
	
}


void CTitle2::onEnterTransitionDidFinish() {
	cocos2d::log("senni finish");
	//終了有効化
	SCENE_END = false;
}


/**
*@desc ゲーム終了
*@param タイトルレイヤーのインスタンス
@tips ゲーム終了ボタンが押されたときに呼び出される
*/
void CTitle2::callbackEndGame(cocos2d::Ref* pSender) {
	OutputDebugString(L"ゲームの終了ボタンが押されたよ\n");
	Director::getInstance()->end();
}
//キー入力
void CTitle2::inputFunc() {

	//シーン切り替えフラグ
	if (p_scene && !SCENE_END)
		return;

	//カーソルの入力処理
	m_pCursor->inputFunc();
	if (!pEndLabel)
		return;


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
void CTitle2::moveFunc() {
	if (!m_pCursor || !background)
		return;

	background->moveFunc();
	m_pCursor->moveFunc();
}

//アニメーション
void CTitle2::animetionFunc() {

	if (!m_pCursor || !background)
		return;

	background->animationFunc();

	m_pCursor->animationFunc();
}

//移動値反映
void CTitle2::applyFunc() {
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
				/*
				{
				//replayファイル確認
				struct stat st;
				const char* file = "replay.dat";

				if (stat(file, &st) == 0) {
				cocos2d::log("replay.dat find");
				//ファイルから読み込む
				//ファイルポインタ
				FILE *file;
				file = fopen("replay.dat", "rb");
				fread(REPLAY_DATA, sizeof(int), 12020, file);
				fclose(file);

				//ゲームメインへ
				//音楽エンジン終了回避
				audioFlug = false;

				//遷移中終了回避
				SCENE_END = true;
				//BGM停止
				AudioEngine::stopAll();
				//モードリプレイ
				CGameMain::mode = 2;
				//ステージナンバー設定
				CGameMain::m_stageNo = 1;

				//プレイヤーステータス初期化
				CGameMain::m_hp = 200;
				CGameMain::m_maxHp = 200;
				CGameMain::m_attackPt = 1;
				CGameMain::m_score = 0;
				CGameMain::m_speed = 2;
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
				this->unscheduleUpdate();
				//pScene = CGameMain::createScene();
				pScene = CStageTitle::createScene();
				Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
				}
				else {
				p_scene = false;
				m_frameCounter = 0;

				}
				}
				*/
				//replay画面に移動
				//音楽エンジン終了回避
				/*

				*/
			{
				audioFlug = false;

				//遷移中終了回避
				SCENE_END = true;

				this->unscheduleUpdate();
				pScene = CReplay::createScene();
				Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
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
				CGameMain::m_speed = 2;
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
				MapData::seed = time(NULL);

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

