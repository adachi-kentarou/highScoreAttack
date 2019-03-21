#pragma once
#ifndef __ShootingGame__Map__
#define __ShootingGame__Map__
#include "Model/Character/Character.h"

//=======================================
//マップ表示用のクラスはここから書く
//=======================================

class CMap :public cocos2d::Sprite {
public:
	//コンストラクタ
	CMap();
	//デストラクタ
	~CMap();
	/**
	*@desc 生成
	*@param tmxファイル名
	*@return CMapクラスのインスタンス
	*@tips CREATE_FUMCマクロの中身
	*		静的メンバ関数
	*/
	static CMap* create(std::string tmxFile);

	/**
	*@desc マップクラスの初期化
	*/
	virtual bool init();
public:
	//スクロール(移動)用データ
	CMove m_scrollMove;

	//スクロール終了位置
	cocos2d::Point m_scrollEndPos;

	//ループするかどうかのフラグ true...ループする
	bool m_isLoop = false;

	//スクロールが終了したかどうか true...スクロール終了(画面端についた)
	bool m_isEnd = false;

	//スクロール(移動)処理
	void moveFunc();

	//反映処理
	void applyFunc();

};
#endif __ShootingGame__Map__