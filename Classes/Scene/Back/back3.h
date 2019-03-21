#pragma once
#include "cocos2d.h"
#include "Constants.h"
#include "Scene/Back/Back2.h"

/**
*タイトルレイヤー
*
*タイトルを表示するためのレイヤー
*
*/
class back3 :public cocos2d::Layer {
public:
	
	//デストラクタ
	~back3();
	/**
	*@desc シーンの生成
	*@return CTitleレイヤーを内包したシーンクラスインスタンス
	*@tips 静的メンバ関数
	*/
	static cocos2d::Scene* createScene();

	//create()静的メンバ関数の作成
	CREATE_FUNC(back3);

	/**
	*@desc 初期化
	*@return true...成功false...失敗
	*/
	bool init()override;

	virtual void update(float deltaTime_) override;

	bool a = true;
};