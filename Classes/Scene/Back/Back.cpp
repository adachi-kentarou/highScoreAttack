#include "Constants.h"
#include "Back.h"
//cocos2d::�̏ȗ�
using namespace cocos2d;

using namespace cocos2d::experimental;

//�f�X�g���N�^
CBack::~CBack() {
		OutputDebugString(L"�I�[�f�B�I�폜\n");
		//BGM�̉��
		AudioEngine::uncacheAll();

		//AudioEngine�̏I��
		AudioEngine::end();

}
/**
*@desc �V�[���̐���
*@return CTitle���C���[�������V�[���N���X�C���X�^���X
*@tips �ÓI�����o�֐�
*/
cocos2d::Scene* CBack::createScene() {
	//�V�[���̐���
	cocos2d::Scene* pScene = cocos2d::Scene::create();
	//���������V�[����Ԃ�

	//CTitle���C���[�̐���
	CBack* pLayer = CBack::create();
	pScene->addChild(pLayer);


	return pScene;
}

/**
*@desc ������
*@return true...����false...���s
*/
bool CBack::init() {
	//===================================================
	//�������珉�����A�����ݒ�̃R�[�h��ǉ�
	//===================================================
	cocos2d::Scene* pScene = CLoading::createScene();
	
	//�����ɍĐ��ł��鐔��128�ɐݒ�
	AudioEngine::setMaxAudioInstance(256);

	//update�֐�(�X�V�����֐�)�Ăяo���ݒ�
	this->scheduleUpdate();
	return true;
}

void CBack::update(float deltaTime) {
	if (flg) {
		flg = false;
		this->unscheduleUpdate();
		cocos2d::Scene* pScene = CLoading::createScene();
		Director::getInstance()->pushScene(pScene);
	}
		
}