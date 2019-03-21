#include "Scene/Replay/Replay.h"
#include "Constants.h"
#include "Scene/GameMain/GameMain.h"
#include "Lib/InputManager/InputManager.h"
#include "Lib/InputManager/InputJoystick.h"
#include "Scene/Replay/Replay.h"
#include "Scene/Title/Title.h"
#include "Scene/StageTitle/StageTitle.h"
#include "Scene/StageTitle/StageTitle.h"
#include "Scene/ReplaySelect/ReplaySelect.h"
//cocos2d::�̏ȗ�
using namespace cocos2d;

//AudioEngine�̃C���N���[�h
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

int CReplaySelect::replay_no = 0;
bool CReplaySelect::replay_flg = true;
//�f�X�g���N�^
CReplaySelect::~CReplaySelect() {
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
cocos2d::Scene* CReplaySelect::createScene() {
	//�V�[���̐���
	cocos2d::Scene* pScene = cocos2d::Scene::create();

	//CTitle���C���[�̐���
	CReplaySelect* pLayer = CReplaySelect::create();

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
void CReplaySelect::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {

	// ���͊Ǘ��ɓ��͏������ϑ�
	CInputManager::getInstance()->onKeyPressed(keyCode);
}

/**
*	@desc	�L�[�{�[�h�̃L�[�𗣂����ۂ̃C�x���g
*	@param	�L�[�R�[�h
*	@param	�C�x���g
*/
void CReplaySelect::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event) {

	// ���͊Ǘ��ɓ��͏������ϑ�
	CInputManager::getInstance()->onKeyReleased(keyCode);
}
/**
*@desc ������
*@return true...����false...���s
*/
bool CReplaySelect::init() {

	//update�֐�(�X�V�����֐�)�Ăяo���ݒ�
	this->scheduleUpdate();
	// �L�[�{�[�h���̓C�x���g�󂯎��ݒ�
	this->setKeyboardEnabled(true);
	
	//===================================================
	//�������珉�����A�����ݒ�̃R�[�h��ǉ�
	//===================================================
	//�^�C�g���w�i�̐����Ǝ��t��
	Sprite* pBg = Sprite::create(IMAGE_FILE_REPLAY);
	//�����ʒu�̐ݒ�
	pBg->setPosition(320.0f, 240.0f);
	//���C���[�Ɏ��t��
	this->addChild(pBg);

	//�X�^�[�g�^�C�g�����x���̐����Ǝ��t��
	Label* pTitleLabel = cocos2d::Label::createWithTTF("REPLAY SELECT", FONT_FILE_STARWARS, 30);
	//�����ʒu�̐ݒ�
	pTitleLabel->setPosition(320.0f, 450.0f);
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
	struct stat st;
	const char* file;
	std::string labelstr = "";
	//stage 1���x���̐����Ǝ��t��
	
	file = "replay_1.dat";
	if (stat(file, &st) == 0) {
		labelstr = asctime(localtime(&st.st_mtime));
	}
	else {
		labelstr = "NO SAVE DATA";
	}
	
	pReplay_1 = cocos2d::Label::createWithTTF(labelstr, FONT_FILE_STARWARS, 30);
	//�����ʒu�̐ݒ�
	pReplay_1->setPosition(320.0f, 405.0f);
	//�����F�̐ݒ�
	pReplay_1->setColor(Color3B(0, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pReplay_1);
	
	//stage 2���x���̐����Ǝ��t��
	
	file = "replay_2.dat";
	if (stat(file, &st) == 0) {
		labelstr = asctime(localtime(&st.st_mtime));
	}
	else {
		labelstr = "NO SAVE DATA";
	}

	pReplay_2 = cocos2d::Label::createWithTTF(labelstr, FONT_FILE_STARWARS, 30);
	//�����ʒu�̐ݒ�
	pReplay_2->setPosition(320.0f, 365.0f);
	//�����F�̐ݒ�
	pReplay_2->setColor(Color3B(0, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pReplay_2);

	//stage 3���x���̐����Ǝ��t��

	file = "replay_3.dat";
	if (stat(file, &st) == 0) {
		labelstr = asctime(localtime(&st.st_mtime));
	}
	else {
		labelstr = "NO SAVE DATA";
	}

	pReplay_3 = cocos2d::Label::createWithTTF(labelstr, FONT_FILE_STARWARS, 30);
	//�����ʒu�̐ݒ�
	pReplay_3->setPosition(320.0f, 325.0f);
	//�����F�̐ݒ�
	pReplay_3->setColor(Color3B(0, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pReplay_3);

	//stage 4���x���̐����Ǝ��t��

	file = "replay_4.dat";
	if (stat(file, &st) == 0) {
		labelstr = asctime(localtime(&st.st_mtime));
	}
	else {
		labelstr = "NO SAVE DATA";
	}

	pReplay_4 = cocos2d::Label::createWithTTF(labelstr, FONT_FILE_STARWARS, 30);
	//�����ʒu�̐ݒ�
	pReplay_4->setPosition(320.0f, 285.0f);
	//�����F�̐ݒ�
	pReplay_4->setColor(Color3B(0, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pReplay_4);

	//stage 5���x���̐����Ǝ��t��

	file = "replay_5.dat";
	if (stat(file, &st) == 0) {
		labelstr = asctime(localtime(&st.st_mtime));
	}
	else {
		labelstr = "NO SAVE DATA";
	}

	pReplay_5 = cocos2d::Label::createWithTTF(labelstr, FONT_FILE_STARWARS, 30);
	//�����ʒu�̐ݒ�
	pReplay_5->setPosition(320.0f, 245.0f);
	//�����F�̐ݒ�
	pReplay_5->setColor(Color3B(0, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pReplay_5);

	//stage 6���x���̐����Ǝ��t��

	file = "replay_6.dat";
	if (stat(file, &st) == 0) {
		labelstr = asctime(localtime(&st.st_mtime));
	}
	else {
		labelstr = "NO SAVE DATA";
	}

	pReplay_6 = cocos2d::Label::createWithTTF(labelstr, FONT_FILE_STARWARS, 30);
	//�����ʒu�̐ݒ�
	pReplay_6->setPosition(320.0f, 205.0f);
	//�����F�̐ݒ�
	pReplay_6->setColor(Color3B(0, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pReplay_6);

	//stage 7���x���̐����Ǝ��t��

	file = "replay_7.dat";
	if (stat(file, &st) == 0) {
		labelstr = asctime(localtime(&st.st_mtime));
	}
	else {
		labelstr = "NO SAVE DATA";
	}

	pReplay_7 = cocos2d::Label::createWithTTF(labelstr, FONT_FILE_STARWARS, 30);
	//�����ʒu�̐ݒ�
	pReplay_7->setPosition(320.0f, 165.0f);
	//�����F�̐ݒ�
	pReplay_7->setColor(Color3B(0, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pReplay_7);

	//stage 8���x���̐����Ǝ��t��

	file = "replay_8.dat";
	if (stat(file, &st) == 0) {
		labelstr = asctime(localtime(&st.st_mtime));
	}
	else {
		labelstr = "NO SAVE DATA";
	}

	pReplay_8 = cocos2d::Label::createWithTTF(labelstr, FONT_FILE_STARWARS, 30);
	//�����ʒu�̐ݒ�
	pReplay_8->setPosition(320.0f, 125.0f);
	//�����F�̐ݒ�
	pReplay_8->setColor(Color3B(0, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pReplay_8);

	//stage 9���x���̐����Ǝ��t��

	file = "replay_9.dat";
	if (stat(file, &st) == 0) {
		labelstr = asctime(localtime(&st.st_mtime));
	}
	else {
		labelstr = "NO SAVE DATA";
	}

	pReplay_9 = cocos2d::Label::createWithTTF(labelstr, FONT_FILE_STARWARS, 30);
	//�����ʒu�̐ݒ�
	pReplay_9->setPosition(320.0f, 85.0f);
	//�����F�̐ݒ�
	pReplay_9->setColor(Color3B(0, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pReplay_9);

	//stage 10���x���̐����Ǝ��t��

	file = "replay_10.dat";
	if (stat(file, &st) == 0) {
		labelstr = asctime(localtime(&st.st_mtime));
	}
	else {
		labelstr = "NO SAVE DATA";
	}
	
	pReplay_10 = cocos2d::Label::createWithTTF(labelstr, FONT_FILE_STARWARS, 30);
	//�����ʒu�̐ݒ�
	pReplay_10->setPosition(320.0f, 45.0f);
	//�����F�̐ݒ�
	pReplay_10->setColor(Color3B(0, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pReplay_10);


	//�G���h�^�C�g�����x���̐����Ǝ��t��
	pExit = cocos2d::Label::createWithTTF("EXIT", FONT_FILE_STARWARS, 30);
	//�����ʒu�̐ݒ�
	pExit->setPosition(320.0f, 15.0f);
	//�����F�̐ݒ�
	pExit->setColor(Color3B(0, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pExit);
	//�z��Ƀ��x�����i�[
	pLavelArray[10] = pReplay_1;
	pLavelArray[9] = pReplay_2;
	pLavelArray[8] = pReplay_3;
	pLavelArray[7] = pReplay_4;
	pLavelArray[6] = pReplay_5;
	pLavelArray[5] = pReplay_6;
	pLavelArray[4] = pReplay_7;
	pLavelArray[3] = pReplay_8;
	pLavelArray[2] = pReplay_9;
	pLavelArray[1] = pReplay_10;
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
		10,			//�J�[�\����Y�ő�
		0,			//�J�[�\����X�ʒu
		10,			//�J�[�\����Y�ʒu
		100,		//�J�[�\����X���W
		20,			//�J�[�\����Y���W
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
void CReplaySelect::update(float deltaTime) {

	//===================================================
	//�����ɍX�V�����̃R�[�h��ǉ����Ă���
	//===================================================
	inputFunc();
	moveFunc();
	animetionFunc();
	applyFunc();
}


void CReplaySelect::onEnterTransitionDidFinish() {
	cocos2d::log("senni finish");
	//�I���L����
	SCENE_END = false;
}


/**
*@desc �Q�[���I��
*@param �^�C�g�����C���[�̃C���X�^���X
@tips �Q�[���I���{�^���������ꂽ�Ƃ��ɌĂяo�����
*/
void CReplaySelect::callbackEndGame(cocos2d::Ref* pSender) {
	OutputDebugString(L"�Q�[���̏I���{�^���������ꂽ��\n");
	Director::getInstance()->end();
}
//�L�[����
void CReplaySelect::inputFunc() {

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
void CReplaySelect::moveFunc() {
	if (!m_pCursor)
		return;

	m_pCursor->moveFunc();
}

//�A�j���[�V����
void CReplaySelect::animetionFunc() {

	if (!m_pCursor)
		return;

	m_pCursor->animationFunc();
}

//�ړ��l���f
void CReplaySelect::applyFunc() {
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
			//p_scene = false;
			flashing = 0;

			//���v���C�ǉ�
			struct stat st;
			char* rep[11] = {
				"",
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
			const char* file;
			std::string labelstr = "";
			//stage 1���x���̐����Ǝ��t��

			if (m_pCursor->p_y > 0) {
				p_scene = false;
				m_frameCounter = 0;

				//�ǂݏ���
				if (replay_flg) {
					//��������
					FILE *file1;
					file1 = fopen(rep[m_pCursor->p_y], "wb");
					fwrite(REPLAY_DATA, sizeof(int), 12020, file1);
					fclose(file1);
					if (stat(rep[m_pCursor->p_y], &st) == 0) {
						pLavelArray[m_pCursor->p_y]->setString(cocos2d::StringUtils::format(asctime(localtime(&st.st_mtime))));
					}
				}
				else {
					//�ǂݍ���
					file = rep[m_pCursor->p_y];
					if (stat(file, &st) == 0) {
						//labelstr = asctime(localtime(&st.st_mtime));
						
						//�t�@�C������ǂݍ���
						//�t�@�C���|�C���^
						FILE *file1;
						file1 = fopen(file, "rb");
						fread(REPLAY_DATA, sizeof(int), 12020, file1);
						fclose(file1);

						//�Q�[�����C����
						//���y�G���W���I�����
						audioFlug = false;

						//���v���C�i���o�[�L�^
						replay_no = m_pCursor->p_y;

						//�J�ڒ��I�����
						SCENE_END = true;
						this->unscheduleUpdate();
						pScene = CReplay::createScene();
						Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
					}
					else {
						

					}
				}
				
				
			}
			else {
				//exit
				//�Q�[�����C����
				//���y�G���W���I�����
				audioFlug = false;

				//�J�ڒ��I�����
				SCENE_END = true;
				this->unscheduleUpdate();
				pScene = CTitle::createScene();
				Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
			}
			

		}

	}
}

