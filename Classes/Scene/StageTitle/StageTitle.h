#pragma once
#ifndef __ShootingGame__StageTitle__
#define __ShootingGame__StageTitle__
#include "cocos2d.h"
#include "Constants.h"
#include "Model/Character/Character.h"

/**
*�^�C�g�����C���[
*
*�^�C�g����\�����邽�߂̃��C���[
*
*/
class CStageTitle :public cocos2d::Layer {
public:
	
	//�f�X�g���N�^
	~CStageTitle();
	/**
	*@desc �V�[���̐���
	*@return CTitle���C���[�������V�[���N���X�C���X�^���X
	*@tips �ÓI�����o�֐�
	*/
	static cocos2d::Scene* createScene();

	//create()�ÓI�����o�֐��̍쐬
	CREATE_FUNC(CStageTitle);

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

	//���y�G���W���I���t���O
	bool audioFlug = true;

	CCursor* m_pCursor;

	//�t���[���J�E���^�[
	int m_frameCounter;

	//�A�b�v�f�[�g�֐�
	
	//�X�e�[�W���x��
	cocos2d::Label* pStageLabel;
	
	//�V�[��
	cocos2d::Scene* pScene;


	cocos2d::RenderTexture* pRenderTexture;
	
	//��Փx�\��
	char* m_gameMode[3] = { "EASY","NORMAL","HARD" };
};

#endif __ShootingGame__StageTitle__