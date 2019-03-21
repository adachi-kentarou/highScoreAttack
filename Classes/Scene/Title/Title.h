#pragma once
#ifndef __ShootingGame__Title__
#define __ShootingGame__Title__
#include "cocos2d.h"
#include "Constants.h"
#include "Model/Character/Character.h"

/**
*タイトルレイヤー
*
*タイトルを表示するためのレイヤー
*
*/
class CTitle :public cocos2d::Layer {
public:
	/**
	*@desc ゲームメインに遷移
	@param タイトルレイヤーのインスタンス
	*/
	void callbackChangeGameMain(cocos2d::Ref* pSender);

	//デストラクタ
	~CTitle();
	/**
	*@desc シーンの生成
	*@return CTitleレイヤーを内包したシーンクラスインスタンス
	*@tips 静的メンバ関数
	*/
	static cocos2d::Scene* createScene();
	
	//create()静的メンバ関数の作成
	CREATE_FUNC(CTitle);

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
	*@desc トランジション終了処理
	*/
	void onEnterTransitionDidFinish()override;

	/**
	*@desc 更新処理
	*@param 経過時間
	*/
	virtual void update(float deltaTime_) override;

	/**
	*@desc ゲーム終了
	*@param タイトルレイヤーのインスタンス
	@tips ゲーム終了ボタンが押されたときに呼び出される
	*/
	void callbackEndGame(cocos2d::Ref* pSender);
	
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

	//スタートラベル
	cocos2d::Label* pStartLabel;
	//オプションパネル
	cocos2d::Label* pOptionLabel;
	//リプレイラベル
	cocos2d::Label* pReplayLabel;
	//エンドラベル
	cocos2d::Label* pEndLabel;

	//ラベル配列
	cocos2d::Label* pLavelArray[4];

	//点滅フラグ
	bool flashingflg = false;
	//点滅回数
	int flashing = 0;
	//シーン
	cocos2d::Scene* pScene;

	//音楽
	int m_bgmid;

	//背景アニメーション
	CEfect* background;
	//タイトルBGM
	static int TitleBgm;
	//デモ用乱数値
	static int Rand;
	//デモフレームカウント
	int m_demoCount = 0;
	//モード切替用
	int m_changeGameMode;
	//難易度
	std::vector<char*> m_gameModeArray = {
		"EASY","NORMAL","HARD"
	};
};

#endif __ShootingGame__Title__