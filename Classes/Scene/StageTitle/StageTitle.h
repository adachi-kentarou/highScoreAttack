#pragma once
#ifndef __ShootingGame__StageTitle__
#define __ShootingGame__StageTitle__
#include "cocos2d.h"
#include "Constants.h"
#include "Model/Character/Character.h"

/**
*タイトルレイヤー
*
*タイトルを表示するためのレイヤー
*
*/
class CStageTitle :public cocos2d::Layer {
public:
	
	//デストラクタ
	~CStageTitle();
	/**
	*@desc シーンの生成
	*@return CTitleレイヤーを内包したシーンクラスインスタンス
	*@tips 静的メンバ関数
	*/
	static cocos2d::Scene* createScene();

	//create()静的メンバ関数の作成
	CREATE_FUNC(CStageTitle);

	/**
	*@desc 初期化
	*@return true...成功false...失敗
	*/
	bool init()override;

	/**
	*@desc トランジション終了処理
	*/
	void onEnterTransitionDidFinish()override;

	/**
	*@desc 更新処理
	*@param 経過時間
	*/
	virtual void update(float deltaTime_) override;

	//音楽エンジン終了フラグ
	bool audioFlug = true;

	CCursor* m_pCursor;

	//フレームカウンター
	int m_frameCounter;

	//アップデート関数
	
	//ステージラベル
	cocos2d::Label* pStageLabel;
	
	//シーン
	cocos2d::Scene* pScene;


	cocos2d::RenderTexture* pRenderTexture;
	
	//難易度表示
	char* m_gameMode[3] = { "EASY","NORMAL","HARD" };
};

#endif __ShootingGame__StageTitle__