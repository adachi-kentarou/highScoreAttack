#include "Replay.h"
#include "Constants.h"
#include "Scene/GameMain/GameMain.h"
#include "Lib/InputManager/InputManager.h"
#include "Lib/InputManager/InputJoystick.h"
#include "Scene/Replay/Replay.h"
#include "Scene/Title/Title.h"
#include "Scene/StageTitle/StageTitle.h"
#include "Scene/ReplaySelect/ReplaySelect.h"
//cocos2d::の省略
using namespace cocos2d;

//AudioEngineのインクルード
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

//デストラクタ
CReplay::~CReplay() {

}
/**
*@desc シーンの生成
*@return CTitleレイヤーを内包したシーンクラスインスタンス
*@tips 静的メンバ関数
*/
cocos2d::Scene* CReplay::createScene() {
	//シーンの生成
	cocos2d::Scene* pScene = cocos2d::Scene::create();

	//CTitleレイヤーの生成
	CReplay* pLayer = CReplay::create();

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
void CReplay::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {

	// 入力管理に入力処理を委託
	CInputManager::getInstance()->onKeyPressed(keyCode);
}

/**
*	@desc	キーボードのキーを離した際のイベント
*	@param	キーコード
*	@param	イベント
*/
void CReplay::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event) {

	// 入力管理に入力処理を委託
	CInputManager::getInstance()->onKeyReleased(keyCode);
}
/**
*@desc 初期化
*@return true...成功false...失敗
*/
bool CReplay::init() {

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
	pBg->setPosition(320.0f, 240.0f);
	//レイヤーに取り付け
	this->addChild(pBg);

	//スタートタイトルラベルの生成と取り付け
	Label* pTitleLabel = cocos2d::Label::createWithTTF("STAGE SELECT", FONT_FILE_STARWARS, 62);
	//初期位置の設定
	pTitleLabel->setPosition(320.0f, 400.0f);
	//文字色の設定
	pTitleLabel->setColor(Color3B(0, 200, 200));
	//レイヤーに取り付け
	this->addChild(pTitleLabel);

	//===================================================
	//メニューに関するコードの追加はここから
	//===================================================


	//===================================================
	//タイトルラベルに関するコードの追加はここから
	//===================================================
	//stage 1ラベルの生成と取り付け
	pStage_1 = cocos2d::Label::createWithTTF("Stage 1", FONT_FILE_STARWARS, 31);
	//初期位置の設定
	pStage_1->setPosition(320.0f, 200.0f);
	//文字色の設定
	pStage_1->setColor(Color3B(0, 200, 200));
	//レイヤーに取り付け
	this->addChild(pStage_1);

	//stage 2ラベルの生成と取り付け
	pStage_2 = cocos2d::Label::createWithTTF("Stage 2", FONT_FILE_STARWARS, 31);
	//初期位置の設定
	pStage_2->setPosition(320.0f, 160.0f);
	//文字色の設定
	pStage_2->setColor(Color3B(0, 200, 200));
	//レイヤーに取り付け
	this->addChild(pStage_2);

	//stage 3ラベルの生成と取り付け
	pStage_3 = cocos2d::Label::createWithTTF("Stage 3", FONT_FILE_STARWARS, 31);
	//初期位置の設定
	pStage_3->setPosition(320.0f, 120.0f);
	//文字色の設定
	pStage_3->setColor(Color3B(0, 200, 200));
	//レイヤーに取り付け
	this->addChild(pStage_3);

	//エンドタイトルラベルの生成と取り付け
	pExit = cocos2d::Label::createWithTTF("EXIT", FONT_FILE_STARWARS, 31);
	//初期位置の設定
	pExit->setPosition(320.0f, 80.0f);
	//文字色の設定
	pExit->setColor(Color3B(0, 200, 200));
	//レイヤーに取り付け
	this->addChild(pExit);
	//配列にラベルを格納
	pLavelArray[3] = pStage_1;
	pLavelArray[2] = pStage_2;
	pLavelArray[1] = pStage_3;
	pLavelArray[0] = pExit;

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

	cocos2d::log("title bgm------------- %d", CTitle::TitleBgm);
	if (CTitle::TitleBgm == -1) {
		CTitle::TitleBgm = AudioEngine::play2d(SOUND_FILE_TITLE);
		//ループの設定(true...ループする　false...ループしない)
		AudioEngine::setLoop(this->m_bgmid, true);
		AudioEngine::setVolume(CTitle::TitleBgm, BGM_VOLUME / 100.0f);
	}

	//===================================================
	//ここまで初期化、初期設定のコードを追加
	//===================================================
	return true;
}


/**
*@desc 更新処理
*@param 経過時間
*/
void CReplay::update(float deltaTime) {

	//===================================================
	//ここに更新処理のコードを追加していく
	//===================================================
	inputFunc();
	moveFunc();
	animetionFunc();
	applyFunc();
}


void CReplay::onEnterTransitionDidFinish() {
	cocos2d::log("senni finish");
	//終了有効化
	SCENE_END = false;
}


/**
*@desc ゲーム終了
*@param タイトルレイヤーのインスタンス
@tips ゲーム終了ボタンが押されたときに呼び出される
*/
void CReplay::callbackEndGame(cocos2d::Ref* pSender) {
	OutputDebugString(L"ゲームの終了ボタンが押されたよ\n");
	Director::getInstance()->end();
}
//キー入力
void CReplay::inputFunc() {

	//シーン切り替えフラグ
	if (p_scene || SCENE_END)
		return;
	//カーソルの入力処理
	m_pCursor->inputFunc();
	if (!pExit || CInputJoystick::m_flg == true)
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
void CReplay::moveFunc() {
	if (!m_pCursor)
		return;

	m_pCursor->moveFunc();
}

//アニメーション
void CReplay::animetionFunc() {

	if (!m_pCursor)
		return;

	m_pCursor->animationFunc();
}

//移動値反映
void CReplay::applyFunc() {
	if (!m_pCursor)
		return;

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
			flashing = 0;

			//画面遷移
			switch (m_pCursor->p_y) {
			case 0:
			{
				//画面遷移

				//ゲームメインへ
				//音楽エンジン終了回避
				audioFlug = false;

				//遷移中終了回避
				SCENE_END = true;

				this->unscheduleUpdate();
				Scene* pScene = CReplaySelect::createScene();
				Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));

			}
				break;
			case 1:
				if (REPLAY_DATA[1 + (2) * 4] != 0) {

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
					CGameMain::m_stageNo = 3;
					
					this->unscheduleUpdate();
					pScene = CStageTitle::createScene();
					Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
				}
				else {
					p_scene = false;
					m_frameCounter = 0;

				}
			break;
			case 2:
				if (REPLAY_DATA[1 + (1) * 4] != 0) {

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
					CGameMain::m_stageNo = 2;

					this->unscheduleUpdate();
					pScene = CStageTitle::createScene();
					Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
				}
				else {
					p_scene = false;
					m_frameCounter = 0;

				}
			break;
			case 3:
				if (REPLAY_DATA[1 + (0) * 4] != 0) {
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

					this->unscheduleUpdate();
					pScene = CStageTitle::createScene();
					Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
				}
				else {
					p_scene = false;
					m_frameCounter = 0;

				}
			break;
			}

		}

	}
}

