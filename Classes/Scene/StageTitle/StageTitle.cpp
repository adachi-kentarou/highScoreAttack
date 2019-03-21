#include "StageTitle.h"
#include "Constants.h"
#include "Scene/GameMain/GameMain.h"
#include "Lib/InputManager/InputManager.h"
#include "Lib/InputManager/InputJoystick.h"
#include "Scene/Option/Option.h"
#include "Scene/Loading/Loading.h"
#include "Data/MapData/MapData.h"
//cocos2d::�̏ȗ�
using namespace cocos2d;

//AudioEngine�̃C���N���[�h
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

//�f�X�g���N�^
CStageTitle::~CStageTitle() {

	cocos2d::log("load end");
}
/**
*@desc �V�[���̐���
*@return CTitle���C���[�������V�[���N���X�C���X�^���X
*@tips �ÓI�����o�֐�
*/
cocos2d::Scene* CStageTitle::createScene() {
	//�V�[���̐���
	cocos2d::Scene* pScene = cocos2d::Scene::create();

	//CTitle���C���[�̐���
	CStageTitle* pLayer = CStageTitle::create();

	//Ctitle���C���[���V�[���Ɏ��t����
	pScene->addChild(pLayer);

	//���������V�[����Ԃ�
	return pScene;
}


/**
*@desc ������
*@return true...����false...���s
*/
bool CStageTitle::init() {
	//update�֐�(�X�V�����֐�)�Ăяo���ݒ�
	this->scheduleUpdate();

	//CCRenderTexture���쐬
	pRenderTexture = CCRenderTexture::create(640, 480);
	pRenderTexture->setPosition(320, 240);
	pRenderTexture->beginWithClear(255, 0, 0, 255);

	//�`��I��
	pRenderTexture->end();
	//���C���[�Ɏ��t��
	this->addChild(pRenderTexture);

	//===================================================
	//�^�C�g�����x���Ɋւ���R�[�h�̒ǉ��͂�������
	//===================================================
	//�^�C�g�����x���̐����Ǝ��t��
	Label* pTitleLabel = cocos2d::Label::createWithTTF(
		cocos2d::StringUtils::format("Stage %d", CGameMain::m_stageNo),
		FONT_FILE_STARWARS, 30);
	//�����ʒu�̐ݒ�
	pTitleLabel->setPosition(320.0f, 240.0f);
	//�����F�̐ݒ�
	pTitleLabel->setColor(Color3B(200, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pTitleLabel);

	//��Փx���x���̐����Ǝ��t��
	Label* pGameModeLabel = cocos2d::Label::createWithTTF(
		cocos2d::StringUtils::format(m_gameMode[GAME_MODE]),
		FONT_FILE_STARWARS, 30);
	//�����ʒu�̐ݒ�
	pGameModeLabel->setPosition(320.0f, 280.0f);
	//�����F�̐ݒ�
	pGameModeLabel->setColor(Color3B(200, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pGameModeLabel);


	//�t���[���J�E���^�[������
	m_frameCounter = 0;

	//===================================================
	//�����܂ŏ������A�����ݒ�̃R�[�h��ǉ�
	//===================================================
	return true;
}


/**
*@desc �X�V����
*@param �o�ߎ���
*/
void CStageTitle::update(float deltaTime) {

	//===================================================
	//�����ɍX�V�����̃R�[�h��ǉ����Ă���
	//===================================================
	
	if (m_frameCounter == 120) {
		//�Q�[�����C����
		//���y�G���W���I�����
		audioFlug = false;

		//�J�ڒ��I�����
		SCENE_END = true;

		//BGM��~
		if (CGameMain::mode != 5) {
			AudioEngine::stopAll();
		}
		this->unscheduleUpdate();
		pScene = CGameMain::createScene();
		Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
	}
	m_frameCounter++;
	
}


void CStageTitle::onEnterTransitionDidFinish() {
	cocos2d::log("senni finish");
	//�I���L����
	SCENE_END = false;
}
