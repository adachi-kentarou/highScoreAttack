
#pragma once
#include "cocos2d.h"
#include "Constants.h"
#include "Model/Character/Character.h"

/**
*�^�C�g�����C���[
*
*�^�C�g����\�����邽�߂̃��C���[
*
*/
class CTitle2 :public cocos2d::Layer {
public:
	/**
	*@desc �Q�[�����C���ɑJ��
	@param �^�C�g�����C���[�̃C���X�^���X
	*/
	void callbackChangeGameMain(cocos2d::Ref* pSender);

	//�f�X�g���N�^
	~CTitle2();
	/**
	*@desc �V�[���̐���
	*@return CTitle���C���[�������V�[���N���X�C���X�^���X
	*@tips �ÓI�����o�֐�
	*/
	static cocos2d::Scene* createScene();

	//create()�ÓI�����o�֐��̍쐬
	CREATE_FUNC(CTitle2);

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

	//�X�^�[�g���x��
	cocos2d::Label* pStartLabel;
	//�I�v�V�����p�l��
	cocos2d::Label* pOptionLabel;
	//���v���C���x��
	cocos2d::Label* pReplayLabel;
	//�G���h���x��
	cocos2d::Label* pEndLabel;

	//���x���z��
	cocos2d::Label* pLavelArray[4];

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
	/*
	void ref();
	cocos2d::Sprite* pImg;
	cocos2d::RenderTexture* pRenderTexture;
	int testflg = 0;
	*/
	//�^�C�g��BGM
	static int TitleBgm;
};

