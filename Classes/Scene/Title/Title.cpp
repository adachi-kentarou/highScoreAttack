#include "Title.h"
#include "Constants.h"
#include "Scene/GameMain/GameMain.h"
#include "Lib/InputManager/InputManager.h"
#include "Lib/InputManager/InputJoystick.h"
#include "Scene/Option/Option.h"
#include "Scene/Loading/Loading.h"
#include "Data/MapData/MapData.h"
#include "Scene/StageTitle/StageTitle.h"
#include "Scene/Replay/Replay.h"
#include "Scene/ReplaySelect/ReplaySelect.h"
#include <time.h>
//cocos2d::�̏ȗ�
using namespace cocos2d;

//AudioEngine�̃C���N���[�h
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

//�f�X�g���N�^
CTitle::~CTitle() {

	cocos2d::log("load end");
	//Director::getInstance()->pushScene(SCENE);
}
/**
*@desc �V�[���̐���
*@return CTitle���C���[�������V�[���N���X�C���X�^���X
*@tips �ÓI�����o�֐�
*/
cocos2d::Scene* CTitle::createScene() {
	//�V�[���̐���
	cocos2d::Scene* pScene = cocos2d::Scene::create();

	//CTitle���C���[�̐���
	CTitle* pLayer = CTitle::create();

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
void CTitle::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {

	// ���͊Ǘ��ɓ��͏������ϑ�
	CInputManager::getInstance()->onKeyPressed(keyCode);
}

/**
*	@desc	�L�[�{�[�h�̃L�[�𗣂����ۂ̃C�x���g
*	@param	�L�[�R�[�h
*	@param	�C�x���g
*/
void CTitle::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event) {

	// ���͊Ǘ��ɓ��͏������ϑ�
	CInputManager::getInstance()->onKeyReleased(keyCode);
}
/*
void CTitle::onEnter(){
cocos2d::log("enter");
}
*/

//�^�C�g��BGM
int CTitle::TitleBgm = -1;
//�f���p�V�[�h�l
int CTitle::Rand = 0;
/**
*@desc ������
*@return true...����false...���s
*/
bool CTitle::init() {

	//update�֐�(�X�V�����֐�)�Ăяo���ݒ�
	this->scheduleUpdate();
	// �L�[�{�[�h���̓C�x���g�󂯎��ݒ�
	this->setKeyboardEnabled(true);

	//===================================================
	//�������珉�����A�����ݒ�̃R�[�h��ǉ�
	//===================================================
	//�^�C�g���w�i�̐����Ǝ��t��

	//CCRenderTexture���쐬
	CCRenderTexture* pRenderTexture = CCRenderTexture::create(640, 480);
	pRenderTexture->setPosition(320, 240);
	pRenderTexture->beginWithClear(0, 0, 0, 255);

	//�`��I��
	pRenderTexture->end();
	//���C���[�Ɏ��t��
	this->addChild(pRenderTexture);


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
	pStartLabel = cocos2d::Label::createWithTTF(m_gameModeArray[0], FONT_FILE_STARWARS, 31);
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

	//�{�^���������菉����
	CInputJoystick::m_flg = true;


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

	AudioEngine::setMaxAudioInstance(32);

	//===================================================
	//�Q�[�����[�h������
	//===================================================
	GAME_MODE = 0;

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
void CTitle::callbackChangeGameMain(cocos2d::Ref* pSender) {
	OutputDebugString(L"�X�^�[�g�{�^���������ꂽ��\n");

	//���y�G���W���I�����
	audioFlug = false;

	//�J�ڒ��I�����
	SCENE_END = true;

	//BGM��~
	AudioEngine::stopAll();

	Scene* pScene = CGameMain::createScene();
	Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));

}

/**
*@desc �X�V����
*@param �o�ߎ���
*/
void CTitle::update(float deltaTime) {

	//===================================================
	//�����ɍX�V�����̃R�[�h��ǉ����Ă���
	//===================================================
	inputFunc();
	moveFunc();
	animetionFunc();
	applyFunc();

}


void CTitle::onEnterTransitionDidFinish() {
	cocos2d::log("senni finish");
	//�I���L����
	SCENE_END = false;
}


/**
*@desc �Q�[���I��
*@param �^�C�g�����C���[�̃C���X�^���X
@tips �Q�[���I���{�^���������ꂽ�Ƃ��ɌĂяo�����
*/
void CTitle::callbackEndGame(cocos2d::Ref* pSender) {
	OutputDebugString(L"�Q�[���̏I���{�^���������ꂽ��\n");
	Director::getInstance()->end();
}
//�L�[����
void CTitle::inputFunc() {

	//�V�[���؂�ւ��t���O
	if (p_scene || SCENE_END)
		return;

	//�J�[�\���̓��͏���
	m_pCursor->inputFunc();
	if (!pEndLabel || CInputJoystick::m_flg)
		return;
	
	//�ړ��I���t���O���L���Ȃ�Γ�Փx�ύX���� �㉺�J�[�\���������ĂȂ�����
	if (m_pCursor->moveflg && !CInputJoystick::m_up && !CInputJoystick::m_down &&
		m_pCursor->p_y == 3 && (CInputJoystick::m_left || CInputJoystick::m_right)) {
		int m_change = 0;
		//�{�����[���ύX
		if (CInputJoystick::m_left == true) {
			m_change = -1;
		}
		else if (CInputJoystick::m_right == true) {
			m_change = 1;
		}
		else if (CInputJoystick::m_left == false && CInputJoystick::m_right == false) {
			m_change = 0;
		}
		GAME_MODE += m_change;

		if (GAME_MODE < 0) {
			GAME_MODE = m_gameModeArray.size() - 1;
		}
		else if (GAME_MODE >= m_gameModeArray.size()) {
			GAME_MODE = 0;
		}

		pStartLabel->setString(cocos2d::StringUtils::format(m_gameModeArray[GAME_MODE]));

		int seid = AudioEngine::play2d(SOUND_FILE_CURSOR_1);
		AudioEngine::setVolume(seid, SE_VOLUME / 100.0f);
		
	}


	//�f����ʈړ�
	if (m_demoCount == 900) {
		

		char* m_pStr[10] = {
			"replay_10.dat",
			"replay_9.dat",
			"replay_8.dat",
			"replay_7.dat",
			"replay_6.dat",
			"replay_5.dat",
			"replay_4.dat",
			"replay_3.dat",
			"replay_2.dat",
			"replay_1.dat"
		};
		std::vector<char*>m_pStr2;
		struct stat st;
		FILE *file1;
		for (int i = 0; i < 10; i++) {
			if (stat(m_pStr[i], &st) == 0) {
				m_pStr2.push_back(m_pStr[i]);
			}
		}
		if (m_pStr2.size() == 0) {
			//�f�[�^��������΃J�E���g���Z�b�g
			m_demoCount = 0;
		}
		else {

			//�f�[�^������΃����_���ɑI��
			audioFlug = false;

			//�J�ڒ��I�����
			SCENE_END = true;


			srand(time(NULL));
			file1 = fopen(m_pStr2[rand() % m_pStr2.size()], "rb");
			fread(REPLAY_DATA, sizeof(int), 12020, file1);
			fclose(file1);
			int stage = 0;
			if (REPLAY_DATA[1 + (0) * 4] != 0) {
				stage++;
			}
			if (REPLAY_DATA[1 + (1) * 4] != 0) {
				stage++;
			}
			if (REPLAY_DATA[1 + (2) * 4] != 0) {
				stage++;
			}

			//����
			Rand = rand();

			//���[�h���v���C
			CGameMain::mode = 5;
			//�X�e�[�W�i���o�[�ݒ�
			CGameMain::m_stageNo = rand() % stage + 1;

			this->unscheduleUpdate();
			pScene = CStageTitle::createScene();
			Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));

		}

		
	}
	else {
		m_demoCount++;
	}
	//���͂���������J�E���g���Z�b�g
	if (CInputJoystick::m_change ||
		CInputJoystick::m_down ||
		CInputJoystick::m_left ||
		CInputJoystick::m_pause ||
		CInputJoystick::m_shot ||
		CInputJoystick::m_right ||
		CInputJoystick::m_stage ||
		CInputJoystick::m_up
		) {
		m_demoCount = 0;
	}


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
void CTitle::moveFunc() {
	if (!m_pCursor || !background)
		return;

	background->moveFunc();
	m_pCursor->moveFunc();
}

//�A�j���[�V����
void CTitle::animetionFunc() {

	if (!m_pCursor || !background)
		return;

	background->animationFunc();

	m_pCursor->animationFunc();
}

//�ړ��l���f
void CTitle::applyFunc() {
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

			{

				{

					//�Q�[�����C����
					//���y�G���W���I�����
					audioFlug = false;

					//�J�ڒ��I�����
					SCENE_END = true;

					//�t�@�C���ǂݍ��݃t���O�ݒ�
					CReplaySelect::replay_flg = false;

					this->unscheduleUpdate();
					//pScene = CReplay::createScene();
					pScene = CReplaySelect::createScene();
					Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));

				}

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
				//�����V�[�h�ݒ�
				MapData::m_seed = time(NULL);
				MapData::m_seed >>= 2;
				MapData::m_seed <<= 2;
				MapData::m_seed += GAME_MODE;
				cocos2d::log("game mode = %d", MapData::m_seed & 3);

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

