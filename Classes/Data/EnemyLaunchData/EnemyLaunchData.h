#pragma once
#ifndef __ShootingGame__EnemyLaunchData__
#define __ShootingGame__EnemyLaunchData__

#include "Model/Character/Character.h"
#include "Data/ActionController/ActionController.h"
/*
*�G�̏o���f�[�^
*�G1�̕��̏o���̃f�[�^
*/
class CEnemyLaunchData {
public:
	int m_frame;		//�o�����鎞��(�t���[��)
	float m_posX;		//�o������ʒuX
	float m_posY;		//�o������ʒuY
	ENEMY_TYPE m_type;	//�o������G�̃^�C�v
	bool direction;		//�i�s����
	int install = 0;	//�ݒu�����@0...�� 1...�� 2...�� 3...�E
	
	/*
	*@desc �l�̐ݒ�
	*@param �o������t���[��
	*@param �o���ʒuX
	*@param �o���ʒuY
	*@param �o������^�C�v
	*/
	void set(int frame,float posX,float posY,ENEMY_TYPE type, ACTION_TYPE actionType) {
		this->m_frame = frame;
		this->m_posX = posX;
		this->m_posY = posY;
		this->m_type = type;
		this->m_actionType = actionType;
	}

	//�G�̏o���ő吔
	static int MAX_LAUNCH;

	//�s���^�C�v
	ACTION_TYPE m_actionType;

	//�ړ��f�[�^
	std::vector<CEnemyAction> action;

	//�A�C�e���ԍ�
	ITEM_TYPE m_item = (ITEM_TYPE)-1;

#endif
};