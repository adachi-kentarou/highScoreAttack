#include "Constants.h"
#include "Scene/Back/back3.h"
#include "Scene/Back/Back2.h"

//デストラクタ
Back2::~Back2() {

}
/**
*@desc シーンの生成
*@return CTitleレイヤーを内包したシーンクラスインスタンス
*@tips 静的メンバ関数
*/
cocos2d::Scene* Back2::createScene() {
	//シーンの生成
	cocos2d::Scene* pScene = cocos2d::Scene::create();

	//CTitleレイヤーの生成
	Back2* pLayer = Back2::create();

	//Ctitleレイヤーをシーンに取り付ける
	pScene->addChild(pLayer);

	//生成したシーンを返す
	return pScene;
}

/**
*@desc 初期化
*@return true...成功false...失敗
*/
bool Back2::init() {

	//update関数(更新処理関数)呼び出し設定
	scheduleUpdate();
	//===================================================
	//ここから初期化、初期設定のコードを追加
	//===================================================
	
	return true;
}

/**
*@desc 更新処理
*@param 経過時間
*/
void Back2::update(float deltaTime) {

}