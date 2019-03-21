#pragma once
#ifndef __ShootingGame__Back__
#define __ShootingGame__Back__
#include "cocos2d.h"
#include "Constants.h"
#include "Scene/Loading/Loading.h"
#include "audio/include/AudioEngine.h"
//#include "Data/GameData/GameData.h"
/**
*�^�C�g�����C���[
*
*�^�C�g����\�����邽�߂̃��C���[
*
*/
class CBack :public cocos2d::Layer {
public:

	//�f�X�g���N�^
	~CBack();
	/**
	*@desc �V�[���̐���
	*@return CTitle���C���[�������V�[���N���X�C���X�^���X
	*@tips �ÓI�����o�֐�
	*/
	static cocos2d::Scene* createScene();

	//create()�ÓI�����o�֐��̍쐬
	CREATE_FUNC(CBack);

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
	bool flg = true;
};
#endif __ShootingGame__Back__