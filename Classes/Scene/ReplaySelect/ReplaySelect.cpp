#include "Scene/Replay/Replay.h"
#include "Constants.h"
#include "Scene/GameMain/GameMain.h"
#include "Lib/InputManager/InputManager.h"
#include "Lib/InputManager/InputJoystick.h"
#include "Scene/Replay/Replay.h"
#include "Scene/Title/Title.h"
#include "Scene/StageTitle/StageTitle.h"
#include "Scene/StageTitle/StageTitle.h"
#include "Scene/ReplaySelect/ReplaySelect.h"
//cocos2d::の省略
using namespace cocos2d;

//AudioEngineのインクルード
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

int CReplaySelect::replay_no = 0;
bool CReplaySelect::replay_flg = true;
//デストラクタ
CReplaySelect::~CReplaySelect() {
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
cocos2d::Scene* CReplaySelect::createScene() {
	//シーンの生成
	cocos2d::Scene* pScene = cocos2d::Scene::create();

	//CTitleレイヤーの生成
	CReplaySelect* pLayer = CReplaySelect::create();

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
void CReplaySelect::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {

	// 入力管理に入力処理を委託
	CInputManager::getInstance()->onKeyPressed(keyCode);
}

/**
*	@desc	キーボードのキーを離した際のイベント
*	@param	キーコード
*	@param	イベント
*/
void CReplaySelect::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event) {

	// 入力管理に入力処理を委託
	CInputManager::getInstance()->onKeyReleased(keyCode);
}
/**
*@desc 初期化
*@return true...成功false...失敗
*/
bool CReplaySelect::init() {

	//update関数(更新処理関数)呼び出し設定
	this->scheduleUpdate();
	// キーボード入力イベント受け取り設定
	this->setKeyboardEnabled(true);
	
	//===================================================
	//ここから初期化、初期設定のコードを追加
	//===================================================
	//タイトル背景の生成と取り付け
	Sprite* pBg = Sprite::create(IMAGE_FILE_REPLAY);
	//初期位置の設定
	pBg->setPosition(320.0f, 240.0f);
	//レイヤーに取り付け
	this->addChild(pBg);

	//スタートタイトルラベルの生成と取り付け
	Label* pTitleLabel = cocos2d::Label::createWithTTF("REPLAY SELECT", FONT_FILE_STARWARS, 30);
	//初期位置の設定
	pTitleLabel->setPosition(320.0f, 450.0f);
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
	struct stat st;
	const char* file;
	std::string labelstr = "";
	//stage 1ラベルの生成と取り付け
	
	file = "replay_1.dat";
	if (stat(file, &st) == 0) {
		labelstr = asctime(localtime(&st.st_mtime));
	}
	else {
		labelstr = "NO SAVE DATA";
	}
	
	pReplay_1 = cocos2d::Label::createWithTTF(labelstr, FONT_FILE_STARWARS, 30);
	//初期位置の設定
	pReplay_1->setPosition(320.0f, 405.0f);
	//文字色の設定
	pReplay_1->setColor(Color3B(0, 200, 200));
	//レイヤーに取り付け
	this->addChild(pReplay_1);
	
	//stage 2ラベルの生成と取り付け
	
	file = "replay_2.dat";
	if (stat(file, &st) == 0) {
		labelstr = asctime(localtime(&st.st_mtime));
	}
	else {
		labelstr = "NO SAVE DATA";
	}

	pReplay_2 = cocos2d::Label::createWithTTF(labelstr, FONT_FILE_STARWARS, 30);
	//初期位置の設定
	pReplay_2->setPosition(320.0f, 365.0f);
	//文字色の設定
	pReplay_2->setColor(Color3B(0, 200, 200));
	//レイヤーに取り付け
	this->addChild(pReplay_2);

	//stage 3ラベルの生成と取り付け

	file = "replay_3.dat";
	if (stat(file, &st) == 0) {
		labelstr = asctime(localtime(&st.st_mtime));
	}
	else {
		labelstr = "NO SAVE DATA";
	}

	pReplay_3 = cocos2d::Label::createWithTTF(labelstr, FONT_FILE_STARWARS, 30);
	//初期位置の設定
	pReplay_3->setPosition(320.0f, 325.0f);
	//文字色の設定
	pReplay_3->setColor(Color3B(0, 200, 200));
	//レイヤーに取り付け
	this->addChild(pReplay_3);

	//stage 4ラベルの生成と取り付け

	file = "replay_4.dat";
	if (stat(file, &st) == 0) {
		labelstr = asctime(localtime(&st.st_mtime));
	}
	else {
		labelstr = "NO SAVE DATA";
	}

	pReplay_4 = cocos2d::Label::createWithTTF(labelstr, FONT_FILE_STARWARS, 30);
	//初期位置の設定
	pReplay_4->setPosition(320.0f, 285.0f);
	//文字色の設定
	pReplay_4->setColor(Color3B(0, 200, 200));
	//レイヤーに取り付け
	this->addChild(pReplay_4);

	//stage 5ラベルの生成と取り付け

	file = "replay_5.dat";
	if (stat(file, &st) == 0) {
		labelstr = asctime(localtime(&st.st_mtime));
	}
	else {
		labelstr = "NO SAVE DATA";
	}

	pReplay_5 = cocos2d::Label::createWithTTF(labelstr, FONT_FILE_STARWARS, 30);
	//初期位置の設定
	pReplay_5->setPosition(320.0f, 245.0f);
	//文字色の設定
	pReplay_5->setColor(Color3B(0, 200, 200));
	//レイヤーに取り付け
	this->addChild(pReplay_5);

	//stage 6ラベルの生成と取り付け

	file = "replay_6.dat";
	if (stat(file, &st) == 0) {
		labelstr = asctime(localtime(&st.st_mtime));
	}
	else {
		labelstr = "NO SAVE DATA";
	}

	pReplay_6 = cocos2d::Label::createWithTTF(labelstr, FONT_FILE_STARWARS, 30);
	//初期位置の設定
	pReplay_6->setPosition(320.0f, 205.0f);
	//文字色の設定
	pReplay_6->setColor(Color3B(0, 200, 200));
	//レイヤーに取り付け
	this->addChild(pReplay_6);

	//stage 7ラベルの生成と取り付け

	file = "replay_7.dat";
	if (stat(file, &st) == 0) {
		labelstr = asctime(localtime(&st.st_mtime));
	}
	else {
		labelstr = "NO SAVE DATA";
	}

	pReplay_7 = cocos2d::Label::createWithTTF(labelstr, FONT_FILE_STARWARS, 30);
	//初期位置の設定
	pReplay_7->setPosition(320.0f, 165.0f);
	//文字色の設定
	pReplay_7->setColor(Color3B(0, 200, 200));
	//レイヤーに取り付け
	this->addChild(pReplay_7);

	//stage 8ラベルの生成と取り付け

	file = "replay_8.dat";
	if (stat(file, &st) == 0) {
		labelstr = asctime(localtime(&st.st_mtime));
	}
	else {
		labelstr = "NO SAVE DATA";
	}

	pReplay_8 = cocos2d::Label::createWithTTF(labelstr, FONT_FILE_STARWARS, 30);
	//初期位置の設定
	pReplay_8->setPosition(320.0f, 125.0f);
	//文字色の設定
	pReplay_8->setColor(Color3B(0, 200, 200));
	//レイヤーに取り付け
	this->addChild(pReplay_8);

	//stage 9ラベルの生成と取り付け

	file = "replay_9.dat";
	if (stat(file, &st) == 0) {
		labelstr = asctime(localtime(&st.st_mtime));
	}
	else {
		labelstr = "NO SAVE DATA";
	}

	pReplay_9 = cocos2d::Label::createWithTTF(labelstr, FONT_FILE_STARWARS, 30);
	//初期位置の設定
	pReplay_9->setPosition(320.0f, 85.0f);
	//文字色の設定
	pReplay_9->setColor(Color3B(0, 200, 200));
	//レイヤーに取り付け
	this->addChild(pReplay_9);

	//stage 10ラベルの生成と取り付け

	file = "replay_10.dat";
	if (stat(file, &st) == 0) {
		labelstr = asctime(localtime(&st.st_mtime));
	}
	else {
		labelstr = "NO SAVE DATA";
	}
	
	pReplay_10 = cocos2d::Label::createWithTTF(labelstr, FONT_FILE_STARWARS, 30);
	//初期位置の設定
	pReplay_10->setPosition(320.0f, 45.0f);
	//文字色の設定
	pReplay_10->setColor(Color3B(0, 200, 200));
	//レイヤーに取り付け
	this->addChild(pReplay_10);


	//エンドタイトルラベルの生成と取り付け
	pExit = cocos2d::Label::createWithTTF("EXIT", FONT_FILE_STARWARS, 30);
	//初期位置の設定
	pExit->setPosition(320.0f, 15.0f);
	//文字色の設定
	pExit->setColor(Color3B(0, 200, 200));
	//レイヤーに取り付け
	this->addChild(pExit);
	//配列にラベルを格納
	pLavelArray[10] = pReplay_1;
	pLavelArray[9] = pReplay_2;
	pLavelArray[8] = pReplay_3;
	pLavelArray[7] = pReplay_4;
	pLavelArray[6] = pReplay_5;
	pLavelArray[5] = pReplay_6;
	pLavelArray[4] = pReplay_7;
	pLavelArray[3] = pReplay_8;
	pLavelArray[2] = pReplay_9;
	pLavelArray[1] = pReplay_10;
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
		10,			//カーソルのY最大
		0,			//カーソルのX位置
		10,			//カーソルのY位置
		100,		//カーソルのX座標
		20,			//カーソルのY座標
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
void CReplaySelect::update(float deltaTime) {

	//===================================================
	//ここに更新処理のコードを追加していく
	//===================================================
	inputFunc();
	moveFunc();
	animetionFunc();
	applyFunc();
}


void CReplaySelect::onEnterTransitionDidFinish() {
	cocos2d::log("senni finish");
	//終了有効化
	SCENE_END = false;
}


/**
*@desc ゲーム終了
*@param タイトルレイヤーのインスタンス
@tips ゲーム終了ボタンが押されたときに呼び出される
*/
void CReplaySelect::callbackEndGame(cocos2d::Ref* pSender) {
	OutputDebugString(L"ゲームの終了ボタンが押されたよ\n");
	Director::getInstance()->end();
}
//キー入力
void CReplaySelect::inputFunc() {

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
void CReplaySelect::moveFunc() {
	if (!m_pCursor)
		return;

	m_pCursor->moveFunc();
}

//アニメーション
void CReplaySelect::animetionFunc() {

	if (!m_pCursor)
		return;

	m_pCursor->animationFunc();
}

//移動値反映
void CReplaySelect::applyFunc() {
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
			//p_scene = false;
			flashing = 0;

			//リプレイ追加
			struct stat st;
			char* rep[11] = {
				"",
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
			const char* file;
			std::string labelstr = "";
			//stage 1ラベルの生成と取り付け

			if (m_pCursor->p_y > 0) {
				p_scene = false;
				m_frameCounter = 0;

				//読み書き
				if (replay_flg) {
					//書き込み
					FILE *file1;
					file1 = fopen(rep[m_pCursor->p_y], "wb");
					fwrite(REPLAY_DATA, sizeof(int), 12020, file1);
					fclose(file1);
					if (stat(rep[m_pCursor->p_y], &st) == 0) {
						pLavelArray[m_pCursor->p_y]->setString(cocos2d::StringUtils::format(asctime(localtime(&st.st_mtime))));
					}
				}
				else {
					//読み込み
					file = rep[m_pCursor->p_y];
					if (stat(file, &st) == 0) {
						//labelstr = asctime(localtime(&st.st_mtime));
						
						//ファイルから読み込む
						//ファイルポインタ
						FILE *file1;
						file1 = fopen(file, "rb");
						fread(REPLAY_DATA, sizeof(int), 12020, file1);
						fclose(file1);

						//ゲームメインへ
						//音楽エンジン終了回避
						audioFlug = false;

						//リプレイナンバー記録
						replay_no = m_pCursor->p_y;

						//遷移中終了回避
						SCENE_END = true;
						this->unscheduleUpdate();
						pScene = CReplay::createScene();
						Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
					}
					else {
						

					}
				}
				
				
			}
			else {
				//exit
				//ゲームメインへ
				//音楽エンジン終了回避
				audioFlug = false;

				//遷移中終了回避
				SCENE_END = true;
				this->unscheduleUpdate();
				pScene = CTitle::createScene();
				Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
			}
			

		}

	}
}

