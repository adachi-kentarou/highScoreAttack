#pragma once
#ifndef __ShootingGame__Back__
#define __ShootingGame__Back__
#include "cocos2d.h"
#include "Constants.h"
#include "Scene/Loading/Loading.h"
#include "audio/include/AudioEngine.h"
//#include "Data/GameData/GameData.h"
/**
*タイトルレイヤー
*
*タイトルを表示するためのレイヤー
*
*/
class CBack :public cocos2d::Layer {
public:

	//デストラクタ
	~CBack();
	/**
	*@desc シーンの生成
	*@return CTitleレイヤーを内包したシーンクラスインスタンス
	*@tips 静的メンバ関数
	*/
	static cocos2d::Scene* createScene();

	//create()静的メンバ関数の作成
	CREATE_FUNC(CBack);

	/**
	*@desc 初期化
	*@return true...成功false...失敗
	*/
	bool init()override;
	/**
	*@desc 更新処理
	*@param 経過時間
	*/
	virtual void update(float deltaTime_) override;
	bool flg = true;
};
#endif __ShootingGame__Back__