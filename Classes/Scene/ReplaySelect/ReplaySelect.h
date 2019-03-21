#pragma once
#ifndef __ShootingGame__ReplaySelect__
#define __ShootingGame__ReplaySelect__
#include "cocos2d.h"
#include "Constants.h"
#include "Model/Character/Character.h"

/**
*�^�C�g�����C���[
*
*�^�C�g����\�����邽�߂̃��C���[
*
*/
class CReplaySelect :public cocos2d::Layer {
public:
	//�f�X�g���N�^
	~CReplaySelect();
	/**
	*@desc �V�[���̐���
	*@return CTitle���C���[�������V�[���N���X�C���X�^���X
	*@tips �ÓI�����o�֐�
	*/
	static cocos2d::Scene* createScene();

	//create()�ÓI�����o�֐��̍쐬
	CREATE_FUNC(CReplaySelect);

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
	*@desc �g�����W�V�����I������
	*/
	void onEnterTransitionDidFinish()override;

	/**
	*@desc �X�V����
	*@param �o�ߎ���
	*/
	virtual void update(float deltaTime_) override;

	/**
	*@desc �Q�[���I��
	*@param �^�C�g�����C���[�̃C���X�^���X
	@tips �Q�[���I���{�^���������ꂽ�Ƃ��ɌĂяo�����
	*/
	void callbackEndGame(cocos2d::Ref* pSender);

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

	//replay1���x��
	cocos2d::Label* pReplay_1;
	//replay2���x��
	cocos2d::Label* pReplay_2;
	//replay3���x��
	cocos2d::Label* pReplay_3;
	//replay4���x��
	cocos2d::Label* pReplay_4;
	//replay5���x��
	cocos2d::Label* pReplay_5;
	//replay6���x��
	cocos2d::Label* pReplay_6;
	//replay7���x��
	cocos2d::Label* pReplay_7;
	//replay8���x��
	cocos2d::Label* pReplay_8;
	//replay9���x��
	cocos2d::Label* pReplay_9;
	//replay10���x��
	cocos2d::Label* pReplay_10;
	//exit���x��
	cocos2d::Label* pExit;

	//���x���z��
	cocos2d::Label* pLavelArray[11];

	//�_�Ńt���O
	bool flashingflg = false;
	//�_�ŉ�
	int flashing = 0;
	//�V�[��
	cocos2d::Scene* pScene;

	//���y
	int m_bgmid;

	//�w�i�A�j���[�V����
	CEfect* background;

	//���v���C�t�@�C���i���o�[
	static int replay_no;

	//�ǂݍ��ݏ������ݔ��� true�������� false�ǂݍ���
	static bool replay_flg;
};
#endif __ShootingGame__ReplaySelect__