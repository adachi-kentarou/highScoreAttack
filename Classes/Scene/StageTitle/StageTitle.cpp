#include "StageTitle.h"
#include "Constants.h"
#include "Scene/GameMain/GameMain.h"
#include "Lib/InputManager/InputManager.h"
#include "Lib/InputManager/InputJoystick.h"
#include "Scene/Option/Option.h"
#include "Scene/Loading/Loading.h"
#include "Data/MapData/MapData.h"
//cocos2d::の省略
using namespace cocos2d;

//AudioEngineのインクルード
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

//デストラクタ
CStageTitle::~CStageTitle() {

	cocos2d::log("load end");
}
/**
*@desc シーンの生成
*@return CTitleレイヤーを内包したシーンクラスインスタンス
*@tips 静的メンバ関数
*/
cocos2d::Scene* CStageTitle::createScene() {
	//シーンの生成
	cocos2d::Scene* pScene = cocos2d::Scene::create();

	//CTitleレイヤーの生成
	CStageTitle* pLayer = CStageTitle::create();

	//Ctitleレイヤーをシーンに取り付ける
	pScene->addChild(pLayer);

	//生成したシーンを返す
	return pScene;
}


/**
*@desc 初期化
*@return true...成功false...失敗
*/
bool CStageTitle::init() {
	//update関数(更新処理関数)呼び出し設定
	this->scheduleUpdate();

	//CCRenderTextureを作成
	pRenderTexture = CCRenderTexture::create(640, 480);
	pRenderTexture->setPosition(320, 240);
	pRenderTexture->beginWithClear(255, 0, 0, 255);

	//描画終了
	pRenderTexture->end();
	//レイヤーに取り付け
	this->addChild(pRenderTexture);

	//===================================================
	//タイトルラベルに関するコードの追加はここから
	//===================================================
	//タイトルラベルの生成と取り付け
	Label* pTitleLabel = cocos2d::Label::createWithTTF(
		cocos2d::StringUtils::format("Stage %d", CGameMain::m_stageNo),
		FONT_FILE_STARWARS, 30);
	//初期位置の設定
	pTitleLabel->setPosition(320.0f, 240.0f);
	//文字色の設定
	pTitleLabel->setColor(Color3B(200, 200, 200));
	//レイヤーに取り付け
	this->addChild(pTitleLabel);

	//難易度ラベルの生成と取り付け
	Label* pGameModeLabel = cocos2d::Label::createWithTTF(
		cocos2d::StringUtils::format(m_gameMode[GAME_MODE]),
		FONT_FILE_STARWARS, 30);
	//初期位置の設定
	pGameModeLabel->setPosition(320.0f, 280.0f);
	//文字色の設定
	pGameModeLabel->setColor(Color3B(200, 200, 200));
	//レイヤーに取り付け
	this->addChild(pGameModeLabel);


	//フレームカウンター初期化
	m_frameCounter = 0;

	//===================================================
	//ここまで初期化、初期設定のコードを追加
	//===================================================
	return true;
}


/**
*@desc 更新処理
*@param 経過時間
*/
void CStageTitle::update(float deltaTime) {

	//===================================================
	//ここに更新処理のコードを追加していく
	//===================================================
	
	if (m_frameCounter == 120) {
		//ゲームメインへ
		//音楽エンジン終了回避
		audioFlug = false;

		//遷移中終了回避
		SCENE_END = true;

		//BGM停止
		if (CGameMain::mode != 5) {
			AudioEngine::stopAll();
		}
		this->unscheduleUpdate();
		pScene = CGameMain::createScene();
		Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
	}
	m_frameCounter++;
	
}


void CStageTitle::onEnterTransitionDidFinish() {
	cocos2d::log("senni finish");
	//終了有効化
	SCENE_END = false;
}
