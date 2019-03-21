#pragma once
#ifndef __ShootingGame__Option__
#define __ShootingGame__Option__
#include "cocos2d.h"
#include "Constants.h"
#include "Model/Character/Character.h"
#include <future>
#include <iostream>
#include <sys/stat.h>
/**
*タイトルレイヤー
*
*タイトルを表示するためのレイヤー
*
*/
class COption :public cocos2d::Layer {
public:
	
	//デストラクタ
	~COption();
	/**
	*@desc シーンの生成
	*@return CTitleレイヤーを内包したシーンクラスインスタンス
	*@tips 静的メンバ関数
	*/
	static cocos2d::Scene* createScene();

	//create()静的メンバ関数の作成
	CREATE_FUNC(COption);

	/**
	*	@desc	キーボードのキーを押した際のイベント
	*	@param	キーコード
	*	@param	イベント
	*/
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;

	/**
	*	@desc	キーボードのキーを離した際のイベント
	*	@param	キーコード
	*	@param	イベント
	*/
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event) override;

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
	
	/**
	*@desc トランジション終了処理
	*/
	void onEnterTransitionDidFinish()override;

	//音楽エンジン終了フラグ
	bool audioFlug = true;

	CCursor* m_pCursor;

	//フレームカウンター
	int m_frameCounter;

	//アップデート関数
	//入力イベント
	void inputFunc();

	//移動
	void moveFunc();

	//アニメーション
	void animetionFunc();

	//移動値反映
	void applyFunc();

	//zボタン押しフラグ true...押されてる false...押されてない
	bool p_zFlg = false;

	//シーン切り替えフラグ false...シーン切り替え可 true...シーン切り替え不可
	bool p_scene = false;

	//BGM
	cocos2d::Label* pBgmLabel;
	//SE
	cocos2d::Label* pSeLabel;
	//GAME PAD
	cocos2d::Label* pGamePadLabel;
	//EXIT
	cocos2d::Label* pExitLabel;

	//BGMボリューム
	cocos2d::Label* pBgmVolLabel;
	//SEボリューム
	cocos2d::Label* pSeVolLabel;
	//ゲームパッドタイプ
	cocos2d::Label* pPadTypeLabel;

	//ラベル配列
	cocos2d::Label* pLavelArray[4];

	//点滅フラグ
	bool flashingflg = false;
	//点滅回数
	int flashing = 0;

	//ボリューム変更値
	int changeVolume;
	//ボリューム変更フラグ
	bool VolumeFlg = false;
};

#endif __ShootingGame__Option__