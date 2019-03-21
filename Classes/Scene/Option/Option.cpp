#include "Option.h"
#include "Constants.h"
#include "Scene/GameMain/GameMain.h"
#include "Lib/InputManager/InputManager.h"
#include "Lib/InputManager/InputJoystick.h"
#include "Scene/Title/Title.h"
//cocos2d::�̏ȗ�
using namespace cocos2d;

//AudioEngine�̃C���N���[�h
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

//�f�X�g���N�^
COption::~COption() {
	cocos2d::log("config end");
	//config.dat�ɐݒ��ۑ�
	int buf[4] = { BGM_VOLUME ,SE_VOLUME,SCORE,GAME_PAD };
	//�t�@�C���|�C���^
	FILE *file1;
	file1 = fopen("config.dat", "wb");
	fwrite(buf, sizeof(int), 4, file1);
	fclose(file1);
	
}
/**
*@desc �V�[���̐���
*@return CTitle���C���[�������V�[���N���X�C���X�^���X
*@tips �ÓI�����o�֐�
*/
cocos2d::Scene* COption::createScene() {
	//�V�[���̐���
	cocos2d::Scene* pScene = cocos2d::Scene::create();

	//COption���C���[�̐���
	COption* pLayer = COption::create();

	//COption���C���[���V�[���Ɏ��t����
	pScene->addChild(pLayer);

	//���������V�[����Ԃ�
	return pScene;
}

/**
*	@desc	�L�[�{�[�h�̃L�[���������ۂ̃C�x���g
*	@param	�L�[�R�[�h
*	@param	�C�x���g
*/
void COption::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {

	// ���͊Ǘ��ɓ��͏������ϑ�
	CInputManager::getInstance()->onKeyPressed(keyCode);
}

/**
*	@desc	�L�[�{�[�h�̃L�[�𗣂����ۂ̃C�x���g
*	@param	�L�[�R�[�h
*	@param	�C�x���g
*/
void COption::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event) {

	// ���͊Ǘ��ɓ��͏������ϑ�
	CInputManager::getInstance()->onKeyReleased(keyCode);
}

void COption::onEnterTransitionDidFinish() {
	cocos2d::log("senni finish");
	//�I���L����
	SCENE_END = false;
}

/**
*@desc ������
*@return true...����false...���s
*/
bool COption::init() {
	
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
	
	
	//===================================================
	//�^�C�g�����x���Ɋւ���R�[�h�̒ǉ��͂�������
	//===================================================
	//�X�^�[�g�^�C�g�����x���̐����Ǝ��t��
	pBgmLabel = cocos2d::Label::createWithTTF("BGM", FONT_FILE_STARWARS, 62);
	//�����ʒu�̐ݒ�
	pBgmLabel->setPosition(320.0f, 450.0f);
	//�����F�̐ݒ�
	pBgmLabel->setColor(Color3B(0, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pBgmLabel);

	//BGM�{�����[��
	pBgmVolLabel = cocos2d::Label::createWithTTF(std::to_string(BGM_VOLUME), FONT_FILE_STARWARS, 62);
	//�����ʒu�̐ݒ�
	pBgmVolLabel->setPosition(320.0f, 400.0f);
	//�����F�̐ݒ�
	pBgmVolLabel->setColor(Color3B(0, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pBgmVolLabel);


	//�I�v�V�����^�C�g�����x���̐����Ǝ��t��
	pSeLabel = cocos2d::Label::createWithTTF("SE", FONT_FILE_STARWARS, 62);
	//�����ʒu�̐ݒ�
	pSeLabel->setPosition(320.0f, 330.0f);
	//�����F�̐ݒ�
	pSeLabel->setColor(Color3B(0, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pSeLabel);

	//SE�{�����[��
	pSeVolLabel = cocos2d::Label::createWithTTF(std::to_string(SE_VOLUME), FONT_FILE_STARWARS, 62);
	//�����ʒu�̐ݒ�
	pSeVolLabel->setPosition(320.0f, 280.0f);
	//�����F�̐ݒ�
	pSeVolLabel->setColor(Color3B(0, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pSeVolLabel);

	//�I�v�V�����^�C�g�����x���̐����Ǝ��t��
	pGamePadLabel = cocos2d::Label::createWithTTF("GAME PAD", FONT_FILE_STARWARS, 62);
	//�����ʒu�̐ݒ�
	pGamePadLabel->setPosition(320.0f, 210.0f);
	//�����F�̐ݒ�
	pGamePadLabel->setColor(Color3B(0, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pGamePadLabel);

	//�Q�[���p�b�h�^�C�v
	pPadTypeLabel = cocos2d::Label::createWithTTF(GAME_PAD ? "DirectInput" : "XInput", FONT_FILE_STARWARS, 62);
	//�����ʒu�̐ݒ�
	pPadTypeLabel->setPosition(320.0f, 160.0f);
	//�����F�̐ݒ�
	pPadTypeLabel->setColor(Color3B(0, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pPadTypeLabel);

	//�G���h�^�C�g�����x���̐����Ǝ��t��
	pExitLabel = cocos2d::Label::createWithTTF("EXIT", FONT_FILE_STARWARS, 62);
	//�����ʒu�̐ݒ�
	pExitLabel->setPosition(320.0f, 40.0f);
	//�����F�̐ݒ�
	pExitLabel->setColor(Color3B(0, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pExitLabel);
	

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
		90,		//�J�[�\����X���W
		70,		//�J�[�\����Y���W
		0.0f,		//X�ړ��T�C�Y
		120.0f,		//Y�ړ��T�C�Y
		5,			//�ړ��A�j���[�V�����t���[��
		true,		//�����[�v
		true,		//�c���[�v
		30,			//�ᑬ�҂��t���[��
		0			//�����҂��t���[��
	);

	this->addChild(m_pCursor);

	//�t���[���J�E���^�[������
	m_frameCounter = 0;
	//�{�^���������菉����
	CInputJoystick::m_flg = true;

	cocos2d::log("bgm%d se%d", BGM_VOLUME, SE_VOLUME);

	//===================================================
	//�����܂ŏ������A�����ݒ�̃R�[�h��ǉ�
	//===================================================
	return true;
}

/**
*@desc �X�V����
*@param �o�ߎ���
*/
void COption::update(float deltaTime) {
	//===================================================
	//�����ɍX�V�����̃R�[�h��ǉ����Ă���
	//===================================================
	inputFunc();
	moveFunc();
	animetionFunc();
	applyFunc();

}

//�L�[����
void COption::inputFunc() {
	

	//�V�[���؂�ւ��t���O
	if (p_scene || SCENE_END)
		return;


	//�J�[�\���̓��͏���
	m_pCursor->inputFunc();
	if (CInputJoystick::m_flg == true)
		return;

	//�ړ��I���t���O���L���Ȃ�΃{�����[���ύX���� �㉺�J�[�\���������ĂȂ�����
	if (m_pCursor->moveflg && !CInputJoystick::m_up && !CInputJoystick::m_down &&
		(CInputJoystick::m_left || CInputJoystick::m_right)) {
		//�{�����[���ύX
		if (CInputJoystick::m_left == true) {
			changeVolume = -1;
		} else if (CInputJoystick::m_right == true) {
			changeVolume = 1;
		} else if (CInputJoystick::m_left == false && CInputJoystick::m_right == false) {
			changeVolume = 0;
		}
		switch (m_pCursor->p_y) {
		case 3:
			//BGM
			BGM_VOLUME += changeVolume;
			if(BGM_VOLUME > 100 )
				BGM_VOLUME = 100;
		
			if (BGM_VOLUME < 0)
				BGM_VOLUME = 0;

			pBgmVolLabel->setString(std::to_string(BGM_VOLUME));
			//���ʕύX
			AudioEngine::setVolume(CTitle::TitleBgm, BGM_VOLUME / 100.0f);
			{
				int seid = AudioEngine::play2d(SOUND_FILE_CURSOR_1);
				AudioEngine::setVolume(seid, SE_VOLUME / 100.0f);
			}
			return;
			break;
		case 2:
			//SE
			SE_VOLUME += changeVolume;
			if (SE_VOLUME > 100)
				SE_VOLUME = 100;

			if (SE_VOLUME < 0)
				SE_VOLUME = 0;

			pSeVolLabel->setString(std::to_string(SE_VOLUME));
			{
				int seid = AudioEngine::play2d(SOUND_FILE_CURSOR_1);
				AudioEngine::setVolume(seid, SE_VOLUME / 100.0f);
			}
			return;
			break;
		case 1:
			//SE
			//GAME_PAD += changeVolume;
			if (GAME_PAD == 1) {
				GAME_PAD = 0;
			}
			else {
				GAME_PAD = 1;
			}
			pPadTypeLabel->setString(GAME_PAD == 1 ? "DirectInput" : "XInput");
			{
				int seid = AudioEngine::play2d(SOUND_FILE_CURSOR_1);
				AudioEngine::setVolume(seid, SE_VOLUME / 100.0f);
			}
			return;
			break;
		case 0:
			//EXIT
			break;

		}
	}

	

	if (CInputJoystick::m_shot == true) {
		if (p_zFlg == false) {
			p_zFlg = true;
		}
	}
	else {
		if (p_zFlg == true) {
			//�{�^������������Ԃ��痣������
			p_zFlg = false;

			//�J�[�\�����͑҂��̎��Ƀ{�^����������
			if (m_pCursor->p_input == 0 && m_pCursor->p_y == 0) {
				//�J�[�\��SE
				if (!p_scene) {
					int seid = AudioEngine::play2d(SOUND_FILE_CURSOR_2);
					AudioEngine::setVolume(seid, SE_VOLUME / 100.0f);
				}
				//�V�[���؂�ւ��t���O�L��
				p_scene = true;
			}

		}

	}

}

//�ړ�
void COption::moveFunc() {
	if (!m_pCursor)
		return;

	m_pCursor->moveFunc();
}

//�A�j���[�V����
void COption::animetionFunc() {
	if (!m_pCursor)
		return;

	m_pCursor->animationFunc();
}

//�ړ��l���f
void COption::applyFunc() {
	if (!m_pCursor)
		return;

	m_pCursor->applyFunc();

	//�{�^����������Ă����烉�x���_�ŊJ�n
	if (p_scene) {

		m_frameCounter++;

		if (m_frameCounter > 5) {
			//�_�Ŋm�F
			if (flashingflg) {
				pExitLabel->setColor(Color3B(0, 200, 200));
				flashingflg = false;
			}
			else {
				pExitLabel->setColor(Color3B(200, 200, 0));
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
			p_scene = false;
			flashing = 0;

			//��ʑJ��

			//�Q�[�����C����
			//���y�G���W���I�����
			audioFlug = false;

			//�J�ڒ��I�����
			SCENE_END = true;

			this->unscheduleUpdate();
			Scene* pScene = CTitle::createScene();
			Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));


		}

	}
}

