
#pragma once
#include "cocos2d.h"
#include "Constants.h"
#include "Model/Character/Character.h"

/**
*タイトルレイヤー
*
*タイトルを表示するためのレイヤー
*
*/
class CTitle2 :public cocos2d::Layer {
public:
	/**
	*@desc ゲームメインに遷移
	@param タイトルレイヤーのインスタンス
	*/
	void callbackChangeGameMain(cocos2d::Ref* pSender);

	//デストラクタ
	~CTitle2();
	/**
	*@desc シーンの生成
	*@return CTitleレイヤーを内包したシーンクラスインスタンス
	*@tips 静的メンバ関数
	*/
	static cocos2d::Scene* createScene();

	//create()静的メンバ関数の作成
	CREATE_FUNC(CTitle2);

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
	/*
	void ref();
	cocos2d::Sprite* pImg;
	cocos2d::RenderTexture* pRenderTexture;
	int testflg = 0;
	*/
	//タイトルBGM
	static int TitleBgm;
};

