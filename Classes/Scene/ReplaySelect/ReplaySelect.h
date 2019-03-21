#pragma once
#ifndef __ShootingGame__ReplaySelect__
#define __ShootingGame__ReplaySelect__
#include "cocos2d.h"
#include "Constants.h"
#include "Model/Character/Character.h"

/**
*タイトルレイヤー
*
*タイトルを表示するためのレイヤー
*
*/
class CReplaySelect :public cocos2d::Layer {
public:
	//デストラクタ
	~CReplaySelect();
	/**
	*@desc シーンの生成
	*@return CTitleレイヤーを内包したシーンクラスインスタンス
	*@tips 静的メンバ関数
	*/
	static cocos2d::Scene* createScene();

	//create()静的メンバ関数の作成
	CREATE_FUNC(CReplaySelect);

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

	//replay1ラベル
	cocos2d::Label* pReplay_1;
	//replay2ラベル
	cocos2d::Label* pReplay_2;
	//replay3ラベル
	cocos2d::Label* pReplay_3;
	//replay4ラベル
	cocos2d::Label* pReplay_4;
	//replay5ラベル
	cocos2d::Label* pReplay_5;
	//replay6ラベル
	cocos2d::Label* pReplay_6;
	//replay7ラベル
	cocos2d::Label* pReplay_7;
	//replay8ラベル
	cocos2d::Label* pReplay_8;
	//replay9ラベル
	cocos2d::Label* pReplay_9;
	//replay10ラベル
	cocos2d::Label* pReplay_10;
	//exitラベル
	cocos2d::Label* pExit;

	//ラベル配列
	cocos2d::Label* pLavelArray[11];

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

	//リプレイファイルナンバー
	static int replay_no;

	//読み込み書き込み判定 true書き込み false読み込み
	static bool replay_flg;
};
#endif __ShootingGame__ReplaySelect__