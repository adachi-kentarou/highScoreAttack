#include "Constants.h"
#include "Scene/Back/back3.h"
#include "Scene/Back/Back2.h"

//�f�X�g���N�^
back3::~back3() {
	
}
/**
*@desc �V�[���̐���
*@return CTitle���C���[�������V�[���N���X�C���X�^���X
*@tips �ÓI�����o�֐�
*/
cocos2d::Scene* back3::createScene() {
	//�V�[���̐���
	cocos2d::Scene* pScene = cocos2d::Scene::create();

	//CTitle���C���[�̐���
	back3* pLayer = back3::create();

	//Ctitle���C���[���V�[���Ɏ��t����
	pScene->addChild(pLayer);

	//���������V�[����Ԃ�
	return pScene;
}

/**
*@desc ������
*@return true...����false...���s
*/
bool back3::init() {

	//update�֐�(�X�V�����֐�)�Ăяo���ݒ�
	scheduleUpdate();
	//===================================================
	//�������珉�����A�����ݒ�̃R�[�h��ǉ�
	//===================================================
	//�^�C�g���w�i�̐����Ǝ��t��
	cocos2d::Sprite* pBg = cocos2d::Sprite::create(IMAGE_FILE_TITLE_BG);
	//�����ʒu�̐ݒ�
	pBg->setPosition(320.0f, 240.0f);
	//���C���[�Ɏ��t��
	this->addChild(pBg);
	return true;
}

/**
*@desc �X�V����
*@param �o�ߎ���
*/
void back3::update(float deltaTime) {
	if (a) {
		a = false;
		cocos2d::Scene* pScene = Back2::createScene();
		cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFadeTR::create(2.0f, pScene));
		
	}
}