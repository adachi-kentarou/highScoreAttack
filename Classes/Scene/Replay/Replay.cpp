#include "Replay.h"
#include "Constants.h"
#include "Scene/GameMain/GameMain.h"
#include "Lib/InputManager/InputManager.h"
#include "Lib/InputManager/InputJoystick.h"
#include "Scene/Replay/Replay.h"
#include "Scene/Title/Title.h"
#include "Scene/StageTitle/StageTitle.h"
#include "Scene/ReplaySelect/ReplaySelect.h"
//cocos2d::�̏ȗ�
using namespace cocos2d;

//AudioEngine�̃C���N���[�h
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

//�f�X�g���N�^
CReplay::~CReplay() {

}
/**
*@desc �V�[���̐���
*@return CTitle���C���[�������V�[���N���X�C���X�^���X
*@tips �ÓI�����o�֐�
*/
cocos2d::Scene* CReplay::createScene() {
	//�V�[���̐���
	cocos2d::Scene* pScene = cocos2d::Scene::create();

	//CTitle���C���[�̐���
	CReplay* pLayer = CReplay::create();

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
void CReplay::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {

	// ���͊Ǘ��ɓ��͏������ϑ�
	CInputManager::getInstance()->onKeyPressed(keyCode);
}

/**
*	@desc	�L�[�{�[�h�̃L�[�𗣂����ۂ̃C�x���g
*	@param	�L�[�R�[�h
*	@param	�C�x���g
*/
void CReplay::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event) {

	// ���͊Ǘ��ɓ��͏������ϑ�
	CInputManager::getInstance()->onKeyReleased(keyCode);
}
/**
*@desc ������
*@return true...����false...���s
*/
bool CReplay::init() {

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
	pBg->setPosition(320.0f, 240.0f);
	//���C���[�Ɏ��t��
	this->addChild(pBg);

	//�X�^�[�g�^�C�g�����x���̐����Ǝ��t��
	Label* pTitleLabel = cocos2d::Label::createWithTTF("STAGE SELECT", FONT_FILE_STARWARS, 62);
	//�����ʒu�̐ݒ�
	pTitleLabel->setPosition(320.0f, 400.0f);
	//�����F�̐ݒ�
	pTitleLabel->setColor(Color3B(0, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pTitleLabel);

	//===================================================
	//���j���[�Ɋւ���R�[�h�̒ǉ��͂�������
	//===================================================


	//===================================================
	//�^�C�g�����x���Ɋւ���R�[�h�̒ǉ��͂�������
	//===================================================
	//stage 1���x���̐����Ǝ��t��
	pStage_1 = cocos2d::Label::createWithTTF("Stage 1", FONT_FILE_STARWARS, 31);
	//�����ʒu�̐ݒ�
	pStage_1->setPosition(320.0f, 200.0f);
	//�����F�̐ݒ�
	pStage_1->setColor(Color3B(0, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pStage_1);

	//stage 2���x���̐����Ǝ��t��
	pStage_2 = cocos2d::Label::createWithTTF("Stage 2", FONT_FILE_STARWARS, 31);
	//�����ʒu�̐ݒ�
	pStage_2->setPosition(320.0f, 160.0f);
	//�����F�̐ݒ�
	pStage_2->setColor(Color3B(0, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pStage_2);

	//stage 3���x���̐����Ǝ��t��
	pStage_3 = cocos2d::Label::createWithTTF("Stage 3", FONT_FILE_STARWARS, 31);
	//�����ʒu�̐ݒ�
	pStage_3->setPosition(320.0f, 120.0f);
	//�����F�̐ݒ�
	pStage_3->setColor(Color3B(0, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pStage_3);

	//�G���h�^�C�g�����x���̐����Ǝ��t��
	pExit = cocos2d::Label::createWithTTF("EXIT", FONT_FILE_STARWARS, 31);
	//�����ʒu�̐ݒ�
	pExit->setPosition(320.0f, 80.0f);
	//�����F�̐ݒ�
	pExit->setColor(Color3B(0, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pExit);
	//�z��Ƀ��x�����i�[
	pLavelArray[3] = pStage_1;
	pLavelArray[2] = pStage_2;
	pLavelArray[1] = pStage_3;
	pLavelArray[0] = pExit;

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
	//�{�^���������菉����
	CInputJoystick::m_flg = true;
	//===================================================
	//BGM�ݒ�̃R�[�h��ǉ�
	//===================================================

	cocos2d::log("title bgm------------- %d", CTitle::TitleBgm);
	if (CTitle::TitleBgm == -1) {
		CTitle::TitleBgm = AudioEngine::play2d(SOUND_FILE_TITLE);
		//���[�v�̐ݒ�(true...���[�v����@false...���[�v���Ȃ�)
		AudioEngine::setLoop(this->m_bgmid, true);
		AudioEngine::setVolume(CTitle::TitleBgm, BGM_VOLUME / 100.0f);
	}

	//===================================================
	//�����܂ŏ������A�����ݒ�̃R�[�h��ǉ�
	//===================================================
	return true;
}


/**
*@desc �X�V����
*@param �o�ߎ���
*/
void CReplay::update(float deltaTime) {

	//===================================================
	//�����ɍX�V�����̃R�[�h��ǉ����Ă���
	//===================================================
	inputFunc();
	moveFunc();
	animetionFunc();
	applyFunc();
}


void CReplay::onEnterTransitionDidFinish() {
	cocos2d::log("senni finish");
	//�I���L����
	SCENE_END = false;
}


/**
*@desc �Q�[���I��
*@param �^�C�g�����C���[�̃C���X�^���X
@tips �Q�[���I���{�^���������ꂽ�Ƃ��ɌĂяo�����
*/
void CReplay::callbackEndGame(cocos2d::Ref* pSender) {
	OutputDebugString(L"�Q�[���̏I���{�^���������ꂽ��\n");
	Director::getInstance()->end();
}
//�L�[����
void CReplay::inputFunc() {

	//�V�[���؂�ւ��t���O
	if (p_scene || SCENE_END)
		return;
	//�J�[�\���̓��͏���
	m_pCursor->inputFunc();
	if (!pExit || CInputJoystick::m_flg == true)
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
void CReplay::moveFunc() {
	if (!m_pCursor)
		return;

	m_pCursor->moveFunc();
}

//�A�j���[�V����
void CReplay::animetionFunc() {

	if (!m_pCursor)
		return;

	m_pCursor->animationFunc();
}

//�ړ��l���f
void CReplay::applyFunc() {
	if (!m_pCursor)
		return;

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
			flashing = 0;

			//��ʑJ��
			switch (m_pCursor->p_y) {
			case 0:
			{
				//��ʑJ��

				//�Q�[�����C����
				//���y�G���W���I�����
				audioFlug = false;

				//�J�ڒ��I�����
				SCENE_END = true;

				this->unscheduleUpdate();
				Scene* pScene = CReplaySelect::createScene();
				Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));

			}
				break;
			case 1:
				if (REPLAY_DATA[1 + (2) * 4] != 0) {

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
					CGameMain::m_stageNo = 3;
					
					this->unscheduleUpdate();
					pScene = CStageTitle::createScene();
					Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
				}
				else {
					p_scene = false;
					m_frameCounter = 0;

				}
			break;
			case 2:
				if (REPLAY_DATA[1 + (1) * 4] != 0) {

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
					CGameMain::m_stageNo = 2;

					this->unscheduleUpdate();
					pScene = CStageTitle::createScene();
					Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
				}
				else {
					p_scene = false;
					m_frameCounter = 0;

				}
			break;
			case 3:
				if (REPLAY_DATA[1 + (0) * 4] != 0) {
					//�v���C���[�X�e�[�^�X������
					CGameMain::m_hp = 200;
					CGameMain::m_maxHp = 200;
					CGameMain::m_attackPt = 1;
					CGameMain::m_score = 0;
					CGameMain::m_speed = 4;
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

					this->unscheduleUpdate();
					pScene = CStageTitle::createScene();
					Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
				}
				else {
					p_scene = false;
					m_frameCounter = 0;

				}
			break;
			}

		}

	}
}

