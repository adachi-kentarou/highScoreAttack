#pragma once
#include "cocos2d.h"
#include "Constants.h"
#include "Scene/Back/Back2.h"

/**
*�^�C�g�����C���[
*
*�^�C�g����\�����邽�߂̃��C���[
*
*/
class back3 :public cocos2d::Layer {
public:
	
	//�f�X�g���N�^
	~back3();
	/**
	*@desc �V�[���̐���
	*@return CTitle���C���[�������V�[���N���X�C���X�^���X
	*@tips �ÓI�����o�֐�
	*/
	static cocos2d::Scene* createScene();

	//create()�ÓI�����o�֐��̍쐬
	CREATE_FUNC(back3);

	/**
	*@desc ������
	*@return true...����false...���s
	*/
	bool init()override;

	virtual void update(float deltaTime_) override;

	bool a = true;
};