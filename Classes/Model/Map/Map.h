#pragma once
#ifndef __ShootingGame__Map__
#define __ShootingGame__Map__
#include "Model/Character/Character.h"

//=======================================
//�}�b�v�\���p�̃N���X�͂������珑��
//=======================================

class CMap :public cocos2d::Sprite {
public:
	//�R���X�g���N�^
	CMap();
	//�f�X�g���N�^
	~CMap();
	/**
	*@desc ����
	*@param tmx�t�@�C����
	*@return CMap�N���X�̃C���X�^���X
	*@tips CREATE_FUMC�}�N���̒��g
	*		�ÓI�����o�֐�
	*/
	static CMap* create(std::string tmxFile);

	/**
	*@desc �}�b�v�N���X�̏�����
	*/
	virtual bool init();
public:
	//�X�N���[��(�ړ�)�p�f�[�^
	CMove m_scrollMove;

	//�X�N���[���I���ʒu
	cocos2d::Point m_scrollEndPos;

	//���[�v���邩�ǂ����̃t���O true...���[�v����
	bool m_isLoop = false;

	//�X�N���[�����I���������ǂ��� true...�X�N���[���I��(��ʒ[�ɂ���)
	bool m_isEnd = false;

	//�X�N���[��(�ړ�)����
	void moveFunc();

	//���f����
	void applyFunc();

};
#endif __ShootingGame__Map__