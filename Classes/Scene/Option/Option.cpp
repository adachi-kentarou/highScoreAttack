#include "Option.h"
#include "Constants.h"
#include "Scene/GameMain/GameMain.h"
#include "Lib/InputManager/InputManager.h"
#include "Lib/InputManager/InputJoystick.h"
#include "Scene/Title/Title.h"
//cocos2d::の省略
using namespace cocos2d;

//AudioEngineのインクルード
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

//デストラクタ
COption::~COption() {
	cocos2d::log("config end");
	//config.datに設定を保存
	int buf[4] = { BGM_VOLUME ,SE_VOLUME,SCORE,GAME_PAD };
	//ファイルポインタ
	FILE *file1;
	file1 = fopen("config.dat", "wb");
	fwrite(buf, sizeof(int), 4, file1);
	fclose(file1);
	
}
/**
*@desc シーンの生成
*@return CTitleレイヤーを内包したシーンクラスインスタンス
*@tips 静的メンバ関数
*/
cocos2d::Scene* COption::createScene() {
	//シーンの生成
	cocos2d::Scene* pScene = cocos2d::Scene::create();

	//COptionレイヤーの生成
	COption* pLayer = COption::create();

	//COptionレイヤーをシーンに取り付ける
	pScene->addChild(pLayer);

	//生成したシーンを返す
	return pScene;
}

/**
*	@desc	キーボードのキーを押した際のイベント
*	@param	キーコード
*	@param	イベント
*/
void COption::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {

	// 入力管理に入力処理を委託
	CInputManager::getInstance()->onKeyPressed(keyCode);
}

/**
*	@desc	キーボードのキーを離した際のイベント
*	@param	キーコード
*	@param	イベント
*/
void COption::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event) {

	// 入力管理に入力処理を委託
	CInputManager::getInstance()->onKeyReleased(keyCode);
}

void COption::onEnterTransitionDidFinish() {
	cocos2d::log("senni finish");
	//終了有効化
	SCENE_END = false;
}

/**
*@desc 初期化
*@return true...成功false...失敗
*/
bool COption::init() {
	
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
	
	
	//===================================================
	//タイトルラベルに関するコードの追加はここから
	//===================================================
	//スタートタイトルラベルの生成と取り付け
	pBgmLabel = cocos2d::Label::createWithTTF("BGM", FONT_FILE_STARWARS, 62);
	//初期位置の設定
	pBgmLabel->setPosition(320.0f, 450.0f);
	//文字色の設定
	pBgmLabel->setColor(Color3B(0, 200, 200));
	//レイヤーに取り付け
	this->addChild(pBgmLabel);

	//BGMボリューム
	pBgmVolLabel = cocos2d::Label::createWithTTF(std::to_string(BGM_VOLUME), FONT_FILE_STARWARS, 62);
	//初期位置の設定
	pBgmVolLabel->setPosition(320.0f, 400.0f);
	//文字色の設定
	pBgmVolLabel->setColor(Color3B(0, 200, 200));
	//レイヤーに取り付け
	this->addChild(pBgmVolLabel);


	//オプションタイトルラベルの生成と取り付け
	pSeLabel = cocos2d::Label::createWithTTF("SE", FONT_FILE_STARWARS, 62);
	//初期位置の設定
	pSeLabel->setPosition(320.0f, 330.0f);
	//文字色の設定
	pSeLabel->setColor(Color3B(0, 200, 200));
	//レイヤーに取り付け
	this->addChild(pSeLabel);

	//SEボリューム
	pSeVolLabel = cocos2d::Label::createWithTTF(std::to_string(SE_VOLUME), FONT_FILE_STARWARS, 62);
	//初期位置の設定
	pSeVolLabel->setPosition(320.0f, 280.0f);
	//文字色の設定
	pSeVolLabel->setColor(Color3B(0, 200, 200));
	//レイヤーに取り付け
	this->addChild(pSeVolLabel);

	//オプションタイトルラベルの生成と取り付け
	pGamePadLabel = cocos2d::Label::createWithTTF("GAME PAD", FONT_FILE_STARWARS, 62);
	//初期位置の設定
	pGamePadLabel->setPosition(320.0f, 210.0f);
	//文字色の設定
	pGamePadLabel->setColor(Color3B(0, 200, 200));
	//レイヤーに取り付け
	this->addChild(pGamePadLabel);

	//ゲームパッドタイプ
	pPadTypeLabel = cocos2d::Label::createWithTTF(GAME_PAD ? "DirectInput" : "XInput", FONT_FILE_STARWARS, 62);
	//初期位置の設定
	pPadTypeLabel->setPosition(320.0f, 160.0f);
	//文字色の設定
	pPadTypeLabel->setColor(Color3B(0, 200, 200));
	//レイヤーに取り付け
	this->addChild(pPadTypeLabel);

	//エンドタイトルラベルの生成と取り付け
	pExitLabel = cocos2d::Label::createWithTTF("EXIT", FONT_FILE_STARWARS, 62);
	//初期位置の設定
	pExitLabel->setPosition(320.0f, 40.0f);
	//文字色の設定
	pExitLabel->setColor(Color3B(0, 200, 200));
	//レイヤーに取り付け
	this->addChild(pExitLabel);
	

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
		90,		//カーソルのX座標
		70,		//カーソルのY座標
		0.0f,		//X移動サイズ
		120.0f,		//Y移動サイズ
		5,			//移動アニメーションフレーム
		true,		//横ループ
		true,		//縦ループ
		30,			//低速待ちフレーム
		0			//高速待ちフレーム
	);

	this->addChild(m_pCursor);

	//フレームカウンター初期化
	m_frameCounter = 0;
	//ボタン押し判定初期化
	CInputJoystick::m_flg = true;

	cocos2d::log("bgm%d se%d", BGM_VOLUME, SE_VOLUME);

	//===================================================
	//ここまで初期化、初期設定のコードを追加
	//===================================================
	return true;
}

/**
*@desc 更新処理
*@param 経過時間
*/
void COption::update(float deltaTime) {
	//===================================================
	//ここに更新処理のコードを追加していく
	//===================================================
	inputFunc();
	moveFunc();
	animetionFunc();
	applyFunc();

}

//キー入力
void COption::inputFunc() {
	

	//シーン切り替えフラグ
	if (p_scene || SCENE_END)
		return;


	//カーソルの入力処理
	m_pCursor->inputFunc();
	if (CInputJoystick::m_flg == true)
		return;

	//移動終了フラグが有効ならばボリューム変更処理 上下カーソルを押してないこと
	if (m_pCursor->moveflg && !CInputJoystick::m_up && !CInputJoystick::m_down &&
		(CInputJoystick::m_left || CInputJoystick::m_right)) {
		//ボリューム変更
		if (CInputJoystick::m_left == true) {
			changeVolume = -1;
		} else if (CInputJoystick::m_right == true) {
			changeVolume = 1;
		} else if (CInputJoystick::m_left == false && CInputJoystick::m_right == false) {
			changeVolume = 0;
		}
		switch (m_pCursor->p_y) {
		case 3:
			//BGM
			BGM_VOLUME += changeVolume;
			if(BGM_VOLUME > 100 )
				BGM_VOLUME = 100;
		
			if (BGM_VOLUME < 0)
				BGM_VOLUME = 0;

			pBgmVolLabel->setString(std::to_string(BGM_VOLUME));
			//音量変更
			AudioEngine::setVolume(CTitle::TitleBgm, BGM_VOLUME / 100.0f);
			{
				int seid = AudioEngine::play2d(SOUND_FILE_CURSOR_1);
				AudioEngine::setVolume(seid, SE_VOLUME / 100.0f);
			}
			return;
			break;
		case 2:
			//SE
			SE_VOLUME += changeVolume;
			if (SE_VOLUME > 100)
				SE_VOLUME = 100;

			if (SE_VOLUME < 0)
				SE_VOLUME = 0;

			pSeVolLabel->setString(std::to_string(SE_VOLUME));
			{
				int seid = AudioEngine::play2d(SOUND_FILE_CURSOR_1);
				AudioEngine::setVolume(seid, SE_VOLUME / 100.0f);
			}
			return;
			break;
		case 1:
			//SE
			//GAME_PAD += changeVolume;
			if (GAME_PAD == 1) {
				GAME_PAD = 0;
			}
			else {
				GAME_PAD = 1;
			}
			pPadTypeLabel->setString(GAME_PAD == 1 ? "DirectInput" : "XInput");
			{
				int seid = AudioEngine::play2d(SOUND_FILE_CURSOR_1);
				AudioEngine::setVolume(seid, SE_VOLUME / 100.0f);
			}
			return;
			break;
		case 0:
			//EXIT
			break;

		}
	}

	

	if (CInputJoystick::m_shot == true) {
		if (p_zFlg == false) {
			p_zFlg = true;
		}
	}
	else {
		if (p_zFlg == true) {
			//ボタンを押した状態から離したら
			p_zFlg = false;

			//カーソル入力待ちの時にボタン押し判定
			if (m_pCursor->p_input == 0 && m_pCursor->p_y == 0) {
				//カーソルSE
				if (!p_scene) {
					int seid = AudioEngine::play2d(SOUND_FILE_CURSOR_2);
					AudioEngine::setVolume(seid, SE_VOLUME / 100.0f);
				}
				//シーン切り替えフラグ有効
				p_scene = true;
			}

		}

	}

}

//移動
void COption::moveFunc() {
	if (!m_pCursor)
		return;

	m_pCursor->moveFunc();
}

//アニメーション
void COption::animetionFunc() {
	if (!m_pCursor)
		return;

	m_pCursor->animationFunc();
}

//移動値反映
void COption::applyFunc() {
	if (!m_pCursor)
		return;

	m_pCursor->applyFunc();

	//ボタンが押されていたらラベル点滅開始
	if (p_scene) {

		m_frameCounter++;

		if (m_frameCounter > 5) {
			//点滅確認
			if (flashingflg) {
				pExitLabel->setColor(Color3B(0, 200, 200));
				flashingflg = false;
			}
			else {
				pExitLabel->setColor(Color3B(200, 200, 0));
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
			p_scene = false;
			flashing = 0;

			//画面遷移

			//ゲームメインへ
			//音楽エンジン終了回避
			audioFlug = false;

			//遷移中終了回避
			SCENE_END = true;

			this->unscheduleUpdate();
			Scene* pScene = CTitle::createScene();
			Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));


		}

	}
}

