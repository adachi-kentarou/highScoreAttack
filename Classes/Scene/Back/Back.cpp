#include "Constants.h"
#include "Back.h"
//cocos2d::の省略
using namespace cocos2d;

using namespace cocos2d::experimental;

//デストラクタ
CBack::~CBack() {
		OutputDebugString(L"オーディオ削除\n");
		//BGMの解放
		AudioEngine::uncacheAll();

		//AudioEngineの終了
		AudioEngine::end();

}
/**
*@desc シーンの生成
*@return CTitleレイヤーを内包したシーンクラスインスタンス
*@tips 静的メンバ関数
*/
cocos2d::Scene* CBack::createScene() {
	//シーンの生成
	cocos2d::Scene* pScene = cocos2d::Scene::create();
	//生成したシーンを返す

	//CTitleレイヤーの生成
	CBack* pLayer = CBack::create();
	pScene->addChild(pLayer);


	return pScene;
}

/**
*@desc 初期化
*@return true...成功false...失敗
*/
bool CBack::init() {
	//===================================================
	//ここから初期化、初期設定のコードを追加
	//===================================================
	cocos2d::Scene* pScene = CLoading::createScene();
	
	//同時に再生できる数を128に設定
	AudioEngine::setMaxAudioInstance(256);

	//update関数(更新処理関数)呼び出し設定
	this->scheduleUpdate();
	return true;
}

void CBack::update(float deltaTime) {
	if (flg) {
		flg = false;
		this->unscheduleUpdate();
		cocos2d::Scene* pScene = CLoading::createScene();
		Director::getInstance()->pushScene(pScene);
	}
		
}