#pragma once
#ifndef __ShootingGame__Loading__
#define __ShootingGame__Loading__
#include "cocos2d.h"
#include "Constants.h"
#include "Scene/Title/Title.h"
#include "Scene/Title/Title2.h"
#include "audio/include/AudioEngine.h"
#include "Scene/StageTitle/StageTitle.h"

class CLoadingGuage;

/**
*�^�C�g�����C���[
*
*�^�C�g����\�����邽�߂̃��C���[
*
*/
class CLoading :public cocos2d::Layer {
public:
	/**
	*@desc �Q�[���^�C�g���ɑJ��
	*/
	void callbackChangeTitle();

	//�f�X�g���N�^
	~CLoading();
	/**
	*@desc �V�[���̐���
	*@return CTitle���C���[�������V�[���N���X�C���X�^���X
	*@tips �ÓI�����o�֐�
	*/
	static cocos2d::Scene* createScene();

	//create()�ÓI�����o�֐��̍쐬
	CREATE_FUNC(CLoading);

	/**
	*@desc ������
	*@return true...����false...���s
	*/
	bool init()override;

	/**
	*@desc �X�V����
	*@param �o�ߎ���
	*/
	void update(float deltaTime)override;

	const int MAX_FILES = 65;

	//�ǂݍ��񂾐�
	static int m_pRoadFiles;
	
	CLoadingGuage* m_pLoadingGuage;
	
	cocos2d::Label* pTitleLabel;

	bool audioFlug;

	//���y�R�[���o�b�N
	static void audioCallBack(bool isSucces);

	//�摜�R�[���o�b�N
	static void textureCallBack(cocos2d::Texture2D* texture);
	//�t�@�C���ǂݍ��݃t���O
	static bool flg;
	
	int aa;
	float bb;
	int countFrame = 0;

};

//=========================================================================
//�Q�[�W�̃N���X�͂������珑��
//=========================================================================
class CLoadingGuage :public cocos2d::ProgressTimer {
public:
	CLoadingGuage();
	~CLoadingGuage();
	CREATE_FUNC(CLoadingGuage);

	//����������
	virtual bool init();
};
#endif __ShootingGame__Loading__