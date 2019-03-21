#include "Title2.h"
#include "Constants.h"
#include "Scene/GameMain/GameMain.h"
#include "Lib/InputManager/InputManager.h"
#include "Lib/InputManager/InputJoystick.h"
#include "Scene/Option/Option.h"
#include "Scene/Loading/Loading.h"
#include "Data/MapData/MapData.h"
#include "Scene/StageTitle/StageTitle.h"
#include "Scene/Replay/Replay.h"
//cocos2d::�̏ȗ�
using namespace cocos2d;

//AudioEngine�̃C���N���[�h
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

//�f�X�g���N�^
CTitle2::~CTitle2() {
	//BGM�̒�~
	//AudioEngine::stopAll();
	/*
	if (audioFlug == true) {
	//BGM�̉��
	AudioEngine::uncacheAll();

	//AudioEngine�̏I��
	AudioEngine::end();
	}
	*/

	cocos2d::log("load end");
	//Director::getInstance()->pushScene(SCENE);
}
/**
*@desc �V�[���̐���
*@return CTitle���C���[�������V�[���N���X�C���X�^���X
*@tips �ÓI�����o�֐�
*/
cocos2d::Scene* CTitle2::createScene() {
	//�V�[���̐���
	cocos2d::Scene* pScene = cocos2d::Scene::create();

	//CTitle���C���[�̐���
	CTitle2* pLayer = CTitle2::create();

	//Ctitle���C���[���V�[���Ɏ��t����
	pScene->addChild(pLayer);

	//���������V�[����Ԃ�
	return pScene;
}

/**
*	@desc	�L�[�{�[�h�̃L�[���������ۂ̃C�x���g
*	@param	�L�[�R�[�h
*	@param	�C�x���g
*/
void CTitle2::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {

	// ���͊Ǘ��ɓ��͏������ϑ�
	CInputManager::getInstance()->onKeyPressed(keyCode);
}

/**
*	@desc	�L�[�{�[�h�̃L�[�𗣂����ۂ̃C�x���g
*	@param	�L�[�R�[�h
*	@param	�C�x���g
*/
void CTitle2::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event) {

	// ���͊Ǘ��ɓ��͏������ϑ�
	CInputManager::getInstance()->onKeyReleased(keyCode);
}
/*
void CTitle::onEnter(){
cocos2d::log("enter");
}
*/

//�^�C�g��BGM
int CTitle2::TitleBgm = -1;

/**
*@desc ������
*@return true...����false...���s
*/
bool CTitle2::init() {

	//update�֐�(�X�V�����֐�)�Ăяo���ݒ�
	this->scheduleUpdate();
	// �L�[�{�[�h���̓C�x���g�󂯎��ݒ�
	this->setKeyboardEnabled(true);

	//===================================================
	//�������珉�����A�����ݒ�̃R�[�h��ǉ�
	//===================================================
	//�^�C�g���w�i�̐����Ǝ��t��
	
	Sprite* pBg = Sprite::create(IMAGE_FILE_TITLE_BG);
	//�����ʒu�̐ݒ�
	pBg->setPosition(320.0f,240.0f);
	//���C���[�Ɏ��t��
	this->addChild(pBg);
	


	//===================================================
	//�w�i�Ɋւ���R�[�h�̒ǉ��͂�������
	//===================================================
	

	//�G�t�F�N�g�̐���
	background = CEfect::create();
	//�摜�̐ݒ�
	background->setTexture(IMAGE_FILE_TITLE_BACKGROUND);

	//�؂����`
	background->m_chip = CChip(0, 0, 640, 480);
	background->setTextureRect(background->m_chip);
	//�ړ��f�[�^�ɏ����ʒu�̐ݒ�
	background->m_move.setPos(320, 240);
	//�ړ��f�[�^�ɏ������x�̐ݒ�G
	background->m_move.setVel(0, 0);

	//�A�j���[�V�����f�[�^�̏�����
	background->m_anime.set(2, 10, true);

	//�����ʒu�𔻒�
	background->setPosition(320, 240);

	//�L���t���O��true������
	background->m_activeFlag = true;

	//�摜����
	background->maxX = 2;

	//�w�i����t��
	this->addChild(background);

	//===================================================
	//�^�C�g�����x���Ɋւ���R�[�h�̒ǉ��͂�������
	//===================================================
	//�^�C�g�����x���̐����Ǝ��t��
	Label* pTitleLabel = Label::createWithTTF("High Score Attack", FONT_FILE_STARWARS, 62);
	//�����ʒu�̐ݒ�
	pTitleLabel->setPosition(320.0f, 360.0f);
	//�����F�̐ݒ�
	pTitleLabel->setColor(Color3B(0, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pTitleLabel);
	//===================================================
	//�X�R�A���x���Ɋւ���R�[�h�̒ǉ��͂�������
	//===================================================
	//�X�R�A���x���̐����Ǝ��t��
	Label* pCcoreLabel = Label::createWithTTF(StringUtils::format("High Score %d", SCORE), FONT_FILE_STARWARS, 30);
	//�����ʒu�̐ݒ�
	pCcoreLabel->setPosition(320.0f, 260.0f);
	//�����F�̐ݒ�
	pCcoreLabel->setColor(Color3B(200, 80, 80));
	//���C���[�Ɏ��t��
	this->addChild(pCcoreLabel);

	
	//===================================================
	//�^�C�g�����x���Ɋւ���R�[�h�̒ǉ��͂�������
	//===================================================
	//�X�^�[�g�^�C�g�����x���̐����Ǝ��t��
	pStartLabel = cocos2d::Label::createWithTTF("START", FONT_FILE_STARWARS, 31);
	//�����ʒu�̐ݒ�
	pStartLabel->setPosition(320.0f, 200.0f);
	//�����F�̐ݒ�
	pStartLabel->setColor(Color3B(0, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pStartLabel);

	//�I�v�V�����^�C�g�����x���̐����Ǝ��t��
	pOptionLabel = cocos2d::Label::createWithTTF("OPTION", FONT_FILE_STARWARS, 31);
	//�����ʒu�̐ݒ�
	pOptionLabel->setPosition(320.0f, 160.0f);
	//�����F�̐ݒ�
	pOptionLabel->setColor(Color3B(0, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pOptionLabel);

	//�G���h�^�C�g�����x���̐����Ǝ��t��
	pReplayLabel = cocos2d::Label::createWithTTF("REPLAY", FONT_FILE_STARWARS, 31);
	//�����ʒu�̐ݒ�
	pReplayLabel->setPosition(320.0f, 120.0f);
	//�����F�̐ݒ�
	pReplayLabel->setColor(Color3B(0, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pReplayLabel);

	//�G���h�^�C�g�����x���̐����Ǝ��t��
	pEndLabel = cocos2d::Label::createWithTTF("END", FONT_FILE_STARWARS, 31);
	//�����ʒu�̐ݒ�
	pEndLabel->setPosition(320.0f, 80.0f);
	//�����F�̐ݒ�
	pEndLabel->setColor(Color3B(0, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pEndLabel);
	//�z��Ƀ��x�����i�[
	pLavelArray[3] = pStartLabel;
	pLavelArray[2] = pOptionLabel;
	pLavelArray[1] = pReplayLabel;
	pLavelArray[0] = pEndLabel;

	//===================================================
	//�J�[�\���Ɋւ���R�[�h�̒ǉ��͂�������
	//===================================================
	m_pCursor = CCursor::create();
	m_pCursor->set(
		IMAGE_FILE_CURSOR,//�t�@�C����
		0,			//�`�b�vX���W
		0,			//�`�b�vY���W
		20,			//�`�b�vX�T�C�Y
		20,			//�`�b�vY�T�C�Y
		2,			//�A�j���[�V������
		20,			//�A�j���[�V�����t���[����
		0,			//�J�[�\����X�ő�
		3,			//�J�[�\����Y�ő�
		0,			//�J�[�\����X�ʒu
		3,			//�J�[�\����Y�ʒu
		240,		//�J�[�\����X���W
		80,		//�J�[�\����Y���W
		0.0f,		//X�ړ��T�C�Y
		40.0f,		//Y�ړ��T�C�Y
		5,			//�ړ��A�j���[�V�����t���[��
		true,		//�����[�v
		true,		//�c���[�v
		10,			//�ᑬ�҂��t���[��
		5			//�����҂��t���[��
	);

	this->addChild(m_pCursor);

	//�t���[���J�E���^�[������
	m_frameCounter = 0;
	/*
	for (int i = 0; i < 100;i++) {
	cocos2d::log("rep= %d",REPLAY_DATA[i]);
	}
	*/

	//===================================================
	//BGM�ݒ�̃R�[�h��ǉ�
	//===================================================

	cocos2d::log("title bgm------------- %d", TitleBgm);
	if (TitleBgm == -1) {
		TitleBgm = AudioEngine::play2d(SOUND_FILE_TITLE);
		//���[�v�̐ݒ�(true...���[�v����@false...���[�v���Ȃ�)
		AudioEngine::setLoop(this->m_bgmid, true);
		AudioEngine::setVolume(TitleBgm, BGM_VOLUME / 100.0f);
	}


	//===================================================
	//�����܂ŏ������A�����ݒ�̃R�[�h��ǉ�
	//===================================================
	return true;
}

/**
*@desc �Q�[�����C���ɑJ��
@param �^�C�g�����C���[�̃C���X�^���X
*@tips �X�^�[�g�{�^���������ꂽ�Ƃ��ɌĂяo�����
*/
void CTitle2::callbackChangeGameMain(cocos2d::Ref* pSender) {
	OutputDebugString(L"�X�^�[�g�{�^���������ꂽ��\n");

	//���y�G���W���I�����
	audioFlug = false;

	//�J�ڒ��I�����
	SCENE_END = true;

	//BGM��~
	AudioEngine::stopAll();

	Scene* pScene = CGameMain::createScene();
	Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
	//Director::getInstance()->replaceScene(pScene);
}

/**
*@desc �X�V����
*@param �o�ߎ���
*/
void CTitle2::update(float deltaTime) {

	//===================================================
	//�����ɍX�V�����̃R�[�h��ǉ����Ă���
	//===================================================
	inputFunc();
	moveFunc();
	animetionFunc();
	applyFunc();
	
}


void CTitle2::onEnterTransitionDidFinish() {
	cocos2d::log("senni finish");
	//�I���L����
	SCENE_END = false;
}


/**
*@desc �Q�[���I��
*@param �^�C�g�����C���[�̃C���X�^���X
@tips �Q�[���I���{�^���������ꂽ�Ƃ��ɌĂяo�����
*/
void CTitle2::callbackEndGame(cocos2d::Ref* pSender) {
	OutputDebugString(L"�Q�[���̏I���{�^���������ꂽ��\n");
	Director::getInstance()->end();
}
//�L�[����
void CTitle2::inputFunc() {

	//�V�[���؂�ւ��t���O
	if (p_scene && !SCENE_END)
		return;

	//�J�[�\���̓��͏���
	m_pCursor->inputFunc();
	if (!pEndLabel)
		return;


	if (CInputJoystick::m_shot == true) {
		if (p_zFlg == false) {
			p_zFlg = true;
			cocos2d::log("push");
		}
	}
	else {
		if (p_zFlg == true) {
			//�{�^������������Ԃ��痣������
			p_zFlg = false;
			cocos2d::log("%d", m_pCursor->p_input);
			//�J�[�\�����͑҂��̎��Ƀ{�^����������
			if (m_pCursor->p_input == 0) {
				//�J�[�\��SE
				if (!p_scene) {
					int seId = AudioEngine::play2d(SOUND_FILE_CURSOR_2);
					AudioEngine::setVolume(seId, SE_VOLUME / 100.0f);
				}
				//�V�[���؂�ւ��t���O�L��
				p_scene = true;
			}

		}

	}

}

//�ړ�
void CTitle2::moveFunc() {
	if (!m_pCursor || !background)
		return;

	background->moveFunc();
	m_pCursor->moveFunc();
}

//�A�j���[�V����
void CTitle2::animetionFunc() {

	if (!m_pCursor || !background)
		return;

	background->animationFunc();

	m_pCursor->animationFunc();
}

//�ړ��l���f
void CTitle2::applyFunc() {
	if (!m_pCursor || !background)
		return;

	background->applyFunc();
	m_pCursor->applyFunc();

	//�{�^����������Ă����烉�x���_�ŊJ�n
	if (p_scene) {

		m_frameCounter++;

		if (m_frameCounter > 5) {
			//�_�Ŋm�F
			if (flashingflg) {
				pLavelArray[m_pCursor->p_y]->setColor(Color3B(0, 200, 200));
				flashingflg = false;
			}
			else {
				pLavelArray[m_pCursor->p_y]->setColor(Color3B(200, 200, 0));
				flashingflg = true;
			}
			//�_�ŃJ�E���g�A�b�v
			flashing++;
			//�t���[���J�E���g������
			m_frameCounter = 0;
		}
		//�_�ŏI��
		if (flashing > 5) {
			flashingflg = false;
			//p_scene = false;
			flashing = 0;
			//��ʑJ��
			switch (m_pCursor->p_y) {
			case 0:
			{
				//BGM�̉��
				AudioEngine::uncacheAll();

				//AudioEngine�̏I��
				AudioEngine::end();

				//�I��
				this->unscheduleUpdate();
				OutputDebugString(L"�Q�[���̏I���{�^���������ꂽ��\n");
				Director::getInstance()->end();
			}

			break;
			case 1:
				/*
				{
				//replay�t�@�C���m�F
				struct stat st;
				const char* file = "replay.dat";

				if (stat(file, &st) == 0) {
				cocos2d::log("replay.dat find");
				//�t�@�C������ǂݍ���
				//�t�@�C���|�C���^
				FILE *file;
				file = fopen("replay.dat", "rb");
				fread(REPLAY_DATA, sizeof(int), 12020, file);
				fclose(file);

				//�Q�[�����C����
				//���y�G���W���I�����
				audioFlug = false;

				//�J�ڒ��I�����
				SCENE_END = true;
				//BGM��~
				AudioEngine::stopAll();
				//���[�h���v���C
				CGameMain::mode = 2;
				//�X�e�[�W�i���o�[�ݒ�
				CGameMain::m_stageNo = 1;

				//�v���C���[�X�e�[�^�X������
				CGameMain::m_hp = 200;
				CGameMain::m_maxHp = 200;
				CGameMain::m_attackPt = 1;
				CGameMain::m_score = 0;
				CGameMain::m_speed = 2;
				CGameMain::playerCount = 2;
				CGameMain::bom = 3;
				//�U�����x���ݒ�
				CGameMain::pweponLevel[0] = 0;		//NORMAL
				CGameMain::pweponLevel[1] = 0;		//EXPLOSION
				CGameMain::pweponLevel[2] = 0;		//BACK
				CGameMain::pweponLevel[3] = 0;		//LASER
				CGameMain::pweponLevel[4] = 0;		//INDCTION
				CGameMain::pweponLevel[5] = 0;		//MULTIPLE
				CGameMain::weponSelect = 0;
				this->unscheduleUpdate();
				//pScene = CGameMain::createScene();
				pScene = CStageTitle::createScene();
				Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
				}
				else {
				p_scene = false;
				m_frameCounter = 0;

				}
				}
				*/
				//replay��ʂɈړ�
				//���y�G���W���I�����
				/*

				*/
			{
				audioFlug = false;

				//�J�ڒ��I�����
				SCENE_END = true;

				this->unscheduleUpdate();
				pScene = CReplay::createScene();
				Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
			}

			break;
			case 2:
			{
				//�I�v�V������
				//���y�G���W���I�����
				audioFlug = false;

				//�J�ڒ��I�����
				SCENE_END = true;

				this->unscheduleUpdate();
				pScene = COption::createScene();
				Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
			}

			break;
			case 3:
			{
				//�Q�[�����C����
				//���y�G���W���I�����
				audioFlug = false;

				//�J�ڒ��I�����
				SCENE_END = true;

				//���[�h���v���C
				CGameMain::mode = 0;

				//�X�e�[�W�i���o�[�ݒ�
				CGameMain::m_stageNo = 1;
				//�v���C���[�X�e�[�^�X������
				CGameMain::m_hp = 200;
				CGameMain::m_maxHp = 200;
				CGameMain::m_attackPt = 1;
				CGameMain::m_score = 0;
				CGameMain::m_speed = 2;
				CGameMain::playerCount = 2;
				CGameMain::bom = 3;
				//�U�����x���ݒ�
				CGameMain::pweponLevel[0] = 0;		//NORMAL
				CGameMain::pweponLevel[1] = 0;		//EXPLOSION
				CGameMain::pweponLevel[2] = 0;		//BACK
				CGameMain::pweponLevel[3] = 0;		//LASER
				CGameMain::pweponLevel[4] = 0;		//INDCTION
				CGameMain::pweponLevel[5] = 0;		//MULTIPLE
				CGameMain::weponSelect = 0;
				//�����V�[�h�ݒ�
				MapData::seed = time(NULL);

				//BGM��~
				AudioEngine::stopAll();
				this->unscheduleUpdate();
				//pScene = CGameMain::createScene();
				pScene = CStageTitle::createScene();
				Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
			}


			break;
			}

		}

	}
}

