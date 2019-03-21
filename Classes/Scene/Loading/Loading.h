#pragma once
#ifndef __ShootingGame__Loading__
#define __ShootingGame__Loading__
#include "cocos2d.h"
#include "Constants.h"
#include "Scene/Title/Title.h"
#include "Scene/Title/Title2.h"
#include "audio/include/AudioEngine.h"
#include "Scene/StageTitle/StageTitle.h"

class CLoadingGuage;

/**
*タイトルレイヤー
*
*タイトルを表示するためのレイヤー
*
*/
class CLoading :public cocos2d::Layer {
public:
	/**
	*@desc ゲームタイトルに遷移
	*/
	void callbackChangeTitle();

	//デストラクタ
	~CLoading();
	/**
	*@desc シーンの生成
	*@return CTitleレイヤーを内包したシーンクラスインスタンス
	*@tips 静的メンバ関数
	*/
	static cocos2d::Scene* createScene();

	//create()静的メンバ関数の作成
	CREATE_FUNC(CLoading);

	/**
	*@desc 初期化
	*@return true...成功false...失敗
	*/
	bool init()override;

	/**
	*@desc 更新処理
	*@param 経過時間
	*/
	void update(float deltaTime)override;

	const int MAX_FILES = 65;

	//読み込んだ数
	static int m_pRoadFiles;
	
	CLoadingGuage* m_pLoadingGuage;
	
	cocos2d::Label* pTitleLabel;

	bool audioFlug;

	//音楽コールバック
	static void audioCallBack(bool isSucces);

	//画像コールバック
	static void textureCallBack(cocos2d::Texture2D* texture);
	//ファイル読み込みフラグ
	static bool flg;
	
	int aa;
	float bb;
	int countFrame = 0;

};

//=========================================================================
//ゲージのクラスはここから書く
//=========================================================================
class CLoadingGuage :public cocos2d::ProgressTimer {
public:
	CLoadingGuage();
	~CLoadingGuage();
	CREATE_FUNC(CLoadingGuage);

	//初期化処理
	virtual bool init();
};
#endif __ShootingGame__Loading__