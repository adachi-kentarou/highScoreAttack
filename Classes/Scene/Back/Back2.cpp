#include "Constants.h"
#include "Scene/Back/back3.h"
#include "Scene/Back/Back2.h"

//�f�X�g���N�^
Back2::~Back2() {

}
/**
*@desc �V�[���̐���
*@return CTitle���C���[�������V�[���N���X�C���X�^���X
*@tips �ÓI�����o�֐�
*/
cocos2d::Scene* Back2::createScene() {
	//�V�[���̐���
	cocos2d::Scene* pScene = cocos2d::Scene::create();

	//CTitle���C���[�̐���
	Back2* pLayer = Back2::create();

	//Ctitle���C���[���V�[���Ɏ��t����
	pScene->addChild(pLayer);

	//���������V�[����Ԃ�
	return pScene;
}

/**
*@desc ������
*@return true...����false...���s
*/
bool Back2::init() {

	//update�֐�(�X�V�����֐�)�Ăяo���ݒ�
	scheduleUpdate();
	//===================================================
	//�������珉�����A�����ݒ�̃R�[�h��ǉ�
	//===================================================
	
	return true;
}

/**
*@desc �X�V����
*@param �o�ߎ���
*/
void Back2::update(float deltaTime) {

}