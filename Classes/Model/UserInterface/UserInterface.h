#ifndef __ShootingGame__UserInterface__
#define __ShootingGame__UserInterface__

#include "cocos2d.h"
#include "Data/Status/Status.h"

//=========================================================================
//　HP表示用のラベルクラスはここから書く
//=========================================================================
class CHpLabel :public cocos2d::Label {
public:
	CHpLabel();
	~CHpLabel();
	
	CREATE_FUNC(CHpLabel);

	//初期化処理
	virtual bool init();
	/**
	*@desc 更新処理
	*@param 経過時間
	*/
	virtual void update(float deltaTime_) override;

private:
	//このクラスで監視するステータスクラスのアドレスを補完するポインタ
	CStatus* m_pStatus;
	
public:
	//ステータスの設定
	void setStatus(CStatus* pStatus){
		this->m_pStatus = pStatus;
	}
};


//=========================================================================
//　HPゲージのクラスはここから書く
//=========================================================================
class CHpGuage :public cocos2d::ProgressTimer {
public:
	CHpGuage();
	~CHpGuage();
	CREATE_FUNC(CHpGuage);
	
	//初期化処理
	virtual bool init();
	/**
	*@desc 更新処理
	*@param 経過時間
	*/
	virtual void update(float deltaTimer_)override;
private:
	//参照するステータス
	CStatus* m_pStatus;
public:
	//参照するステータスの設定
	void setStatus(CStatus* pStatus) {
		this->m_pStatus = pStatus;
	}

};

//=========================================================================
//　スコア表示用のラベルクラスはここから書く
//=========================================================================
class CScoreLabel :public cocos2d::Label {
public:
	CScoreLabel();
	~CScoreLabel();

	CREATE_FUNC(CScoreLabel);

	//初期化処理
	virtual bool init();
	/**
	*@desc 更新処理
	*@param 経過時間
	*/
	virtual void update(float deltaTime_) override;
private:
	//参照するステータス
	CStatus* m_pStatus;
public:
	//参照するステータスの設定
	void setStatus(CStatus* pStatus) {
		this->m_pStatus = pStatus;
	}
};
//=========================================================================
//　ステージ表示用のラベルクラスはここから書く
//=========================================================================
class CStageNoLabel :public cocos2d::Label {
public:
	CStageNoLabel();
	~CStageNoLabel();

	CREATE_FUNC(CStageNoLabel);

	//初期化処理
	virtual bool init();
	/**
	*@desc 更新処理
	*@param 経過時間
	*/
	virtual void update(float deltaTime_) override;

private:
	//このクラスで監視するステータスクラスのアドレスを補完するポインタ
	int* m_pStage;

public:
	//ステータスの設定
	void setStage(int* pStage) {
		this->m_pStage = pStage;
	}
};

//=========================================================================
//　プレイヤー数表示用のラベルクラスはここから書く
//=========================================================================
class CPlayerLabel :public cocos2d::Label {
public:
	CPlayerLabel();
	~CPlayerLabel();

	CREATE_FUNC(CPlayerLabel);

	//初期化処理
	virtual bool init();
	/**
	*@desc 更新処理
	*@param 経過時間
	*/
	virtual void update(float deltaTime_) override;

private:
	//このクラスで監視するステータスクラスのアドレスを補完するポインタ
	int* m_pPlayer;

public:
	//ステータスの設定
	void setPlayer(int* pPlayer) {
		this->m_pPlayer = pPlayer;
	}
};

//=========================================================================
//　ボム数表示用のラベルクラスはここから書く
//=========================================================================
class CBomLabel :public cocos2d::Label {
public:
	CBomLabel();
	~CBomLabel();

	CREATE_FUNC(CBomLabel);

	//初期化処理
	virtual bool init();
	/**
	*@desc 更新処理
	*@param 経過時間
	*/
	virtual void update(float deltaTime_) override;

private:
	//このクラスで監視するステータスクラスのアドレスを補完するポインタ
	int* m_pBom;

public:
	//ステータスの設定
	void setBom(int* pBom) {
		this->m_pBom = pBom;
	}
};
#endif