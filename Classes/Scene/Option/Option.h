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
*�^�C�g�����C���[
*
*�^�C�g����\�����邽�߂̃��C���[
*
*/
class COption :public cocos2d::Layer {
public:
	
	//�f�X�g���N�^
	~COption();
	/**
	*@desc �V�[���̐���
	*@return CTitle���C���[�������V�[���N���X�C���X�^���X
	*@tips �ÓI�����o�֐�
	*/
	static cocos2d::Scene* createScene();

	//create()�ÓI�����o�֐��̍쐬
	CREATE_FUNC(COption);

	/**
	*	@desc	�L�[�{�[�h�̃L�[���������ۂ̃C�x���g
	*	@param	�L�[�R�[�h
	*	@param	�C�x���g
	*/
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;

	/**
	*	@desc	�L�[�{�[�h�̃L�[�𗣂����ۂ̃C�x���g
	*	@param	�L�[�R�[�h
	*	@param	�C�x���g
	*/
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event) override;

	/**
	*@desc ������
	*@return true...����false...���s
	*/
	bool init()override;

	/**
	*@desc �X�V����
	*@param �o�ߎ���
	*/
	virtual void update(float deltaTime_) override;
	
	/**
	*@desc �g�����W�V�����I������
	*/
	void onEnterTransitionDidFinish()override;

	//���y�G���W���I���t���O
	bool audioFlug = true;

	CCursor* m_pCursor;

	//�t���[���J�E���^�[
	int m_frameCounter;

	//�A�b�v�f�[�g�֐�
	//���̓C�x���g
	void inputFunc();

	//�ړ�
	void moveFunc();

	//�A�j���[�V����
	void animetionFunc();

	//�ړ��l���f
	void applyFunc();

	//z�{�^�������t���O true...������Ă� false...������ĂȂ�
	bool p_zFlg = false;

	//�V�[���؂�ւ��t���O false...�V�[���؂�ւ��� true...�V�[���؂�ւ��s��
	bool p_scene = false;

	//BGM
	cocos2d::Label* pBgmLabel;
	//SE
	cocos2d::Label* pSeLabel;
	//GAME PAD
	cocos2d::Label* pGamePadLabel;
	//EXIT
	cocos2d::Label* pExitLabel;

	//BGM�{�����[��
	cocos2d::Label* pBgmVolLabel;
	//SE�{�����[��
	cocos2d::Label* pSeVolLabel;
	//�Q�[���p�b�h�^�C�v
	cocos2d::Label* pPadTypeLabel;

	//���x���z��
	cocos2d::Label* pLavelArray[4];

	//�_�Ńt���O
	bool flashingflg = false;
	//�_�ŉ�
	int flashing = 0;

	//�{�����[���ύX�l
	int changeVolume;
	//�{�����[���ύX�t���O
	bool VolumeFlg = false;
};

#endif __ShootingGame__Option__