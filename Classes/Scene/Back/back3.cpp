#include "Constants.h"
#include "Scene/Back/back3.h"
#include "Scene/Back/Back2.h"

//デストラクタ
back3::~back3() {
	
}
/**
*@desc シーンの生成
*@return CTitleレイヤーを内包したシーンクラスインスタンス
*@tips 静的メンバ関数
*/
cocos2d::Scene* back3::createScene() {
	//シーンの生成
	cocos2d::Scene* pScene = cocos2d::Scene::create();

	//CTitleレイヤーの生成
	back3* pLayer = back3::create();

	//Ctitleレイヤーをシーンに取り付ける
	pScene->addChild(pLayer);

	//生成したシーンを返す
	return pScene;
}

/**
*@desc 初期化
*@return true...成功false...失敗
*/
bool back3::init() {

	//update関数(更新処理関数)呼び出し設定
	scheduleUpdate();
	//===================================================
	//ここから初期化、初期設定のコードを追加
	//===================================================
	//タイトル背景の生成と取り付け
	cocos2d::Sprite* pBg = cocos2d::Sprite::create(IMAGE_FILE_TITLE_BG);
	//初期位置の設定
	pBg->setPosition(320.0f, 240.0f);
	//レイヤーに取り付け
	this->addChild(pBg);
	return true;
}

/**
*@desc 更新処理
*@param 経過時間
*/
void back3::update(float deltaTime) {
	if (a) {
		a = false;
		cocos2d::Scene* pScene = Back2::createScene();
		cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFadeTR::create(2.0f, pScene));
		
	}
}