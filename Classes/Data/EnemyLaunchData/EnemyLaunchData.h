#pragma once
#ifndef __ShootingGame__EnemyLaunchData__
#define __ShootingGame__EnemyLaunchData__

#include "Model/Character/Character.h"
#include "Data/ActionController/ActionController.h"
/*
*敵の出撃データ
*敵1体分の出撃のデータ
*/
class CEnemyLaunchData {
public:
	int m_frame;		//出撃する時間(フレーム)
	float m_posX;		//出撃する位置X
	float m_posY;		//出撃する位置Y
	ENEMY_TYPE m_type;	//出撃する敵のタイプ
	bool direction;		//進行方向
	int install = 0;	//設置方向　0...下 1...左 2...上 3...右
	
	/*
	*@desc 値の設定
	*@param 出現するフレーム
	*@param 出現位置X
	*@param 出現位置Y
	*@param 出撃するタイプ
	*/
	void set(int frame,float posX,float posY,ENEMY_TYPE type, ACTION_TYPE actionType) {
		this->m_frame = frame;
		this->m_posX = posX;
		this->m_posY = posY;
		this->m_type = type;
		this->m_actionType = actionType;
	}

	//敵の出撃最大数
	static int MAX_LAUNCH;

	//行動タイプ
	ACTION_TYPE m_actionType;

	//移動データ
	std::vector<CEnemyAction> action;

	//アイテム番号
	ITEM_TYPE m_item = (ITEM_TYPE)-1;

#endif
};