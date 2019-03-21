
#include "GameMain.h"
#include "Lib/InputManager/InputManager.h"
#include "Lib/InputManager/InputJoystick.h"
#include <stdlib.h>
#include <time.h>
//AudioEngine�̃C���N���[�h
#include "audio/include/AudioEngine.h"

using namespace cocos2d;

using namespace cocos2d::experimental;

/**
*	@desc	�V�[���̐���
*	@return	CMain ���C���[�������V�[���N���X�C���X�^���X
*	@tips	�ÓI�����o�֐�
*/
cocos2d::Scene* CGameMain::createScene() {

	// �V�[���̐���
	cocos2d::Scene* pScene = cocos2d::Scene::create();

	// GameMain ���C���[�̐���
	CGameMain* pLayer = CGameMain::create();

	// CMain ���C���[���V�[���Ɏ��t����
	pScene->addChild(pLayer);
	// ���������V�[����Ԃ�
	return pScene;
}

/**
*	@desc	�L�[�{�[�h�̃L�[���������ۂ̃C�x���g
*	@param	�L�[�R�[�h
*	@param	�C�x���g
*/
void CGameMain::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {

	// ���͊Ǘ��ɓ��͏������ϑ�
	CInputManager::getInstance()->onKeyPressed(keyCode);
}

/**
*	@desc	�L�[�{�[�h�̃L�[�𗣂����ۂ̃C�x���g
*	@param	�L�[�R�[�h
*	@param	�C�x���g
*/
void CGameMain::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event) {

	// ���͊Ǘ��ɓ��͏������ϑ�
	CInputManager::getInstance()->onKeyReleased(keyCode);
}



// �f�X�g���N�^
CGameMain::~CGameMain() {
	//BGM�̒�~
	if (mode != 5) {
		AudioEngine::stop(this->m_bgmid);
	}

	//���̓N���A
	CInputManager::getInstance()->clearInputFlag();
	//�o���f�[�^�̔z������
	SAFE_DELETE_ARRAY(m_pEnemyLaunchData);
}

CEnemyCharacter* CGameMain::m_pEnemyCharas[];
CPlayerCharacter* CGameMain::m_pPlayerChara;
int CGameMain::pweponLevel[];
int CGameMain::m_frameCounter;
int CGameMain::mode;
int CGameMain::m_stageNo;
//�v���C���[�L�����N�^�[�X�e�[�^�X
int CGameMain::m_hp;
int CGameMain::m_maxHp;
int CGameMain::m_attackPt;
int CGameMain::m_score;
int CGameMain::m_speed;
int CGameMain::weponSelect;
//�I�u�W�F�N�g�J�E���g�p
//�G�L�����J�E���g
int CGameMain::m_pEnemyCount;
//�v���C���[�e�J�E���g
int CGameMain::m_pPlayerBulletCount;
//�G�e�J�E���g
int CGameMain::m_pEnemyBulletCount;
//�G�t�F�N�g�J�E���g
int CGameMain::m_pEfectCount;
//�A�C�e���J�E���g
int CGameMain::m_pItemCount;
//�ǃJ�E���g
int CGameMain::m_pWallCount;

//�v���C���[��
int CGameMain::playerCount;
//�{����
int CGameMain::bom;

void CGameMain::onEnterTransitionDidFinish() {
	cocos2d::log("senni finish");
	//�I���L����
	SCENE_END = false;
}

/**
*	@desc	������
*	@return	true...����	false...���s
*/
bool CGameMain::init() {
	CInputManager::getInstance()->clearInputFlag();
	// �e���C���[�̏�����
	if (Layer::init() == false) {
		return false;
	}

	// ��������
	//srand( time( NULL ) ) ;

	// �L�[�{�[�h���̓C�x���g�󂯎��ݒ�
	this->setKeyboardEnabled(true);

	// update �֐� ( �X�V�����֐� ) �Ăяo���ݒ�
	// ���̕�������������R�����g�A�E�g����� update �֐����Ă΂�Ȃ��Ȃ�̂Œ���
	this->scheduleUpdate();




	//=========================================================================
	//
	//	�������珉�����A�����ݒ�̃R�[�h��ǉ�
	//
	//=========================================================================

	//=========================================================================
	//	���v���C�֌W
	//=========================================================================

	//�X�e�[�W���ݒ�
	if (mode == 2 || mode == 5) {
		//���v���C�̏ꍇ
		//�Q�[�����[�h�ݒ�
		GAME_MODE = REPLAY_DATA[0] & 0b11;
		playerData = REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4 + 1];
		
		CGameMain::bom = playerData & 0b1111;
		playerData >>= 4;
		CGameMain::playerCount = playerData & 0b1111;
		playerData >>= 4;
		CGameMain::m_speed = playerData & 0b1111;
		playerData >>= 4;
		CGameMain::weponSelect = playerData & 0b111;
		playerData >>= 3;
		CGameMain::m_maxHp = playerData & 0b11111111;
		playerData >>= 8;
		CGameMain::m_hp = playerData & 0b11111111;
		//data2
		CGameMain::m_score = REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4 + 2];


		playerData = REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4 + 3];
		//data3
		CGameMain::pweponLevel[5] = playerData & 0b1111;
		playerData >>= 4;
		CGameMain::pweponLevel[4] = playerData & 0b1111;
		playerData >>= 4;
		CGameMain::pweponLevel[3] = playerData & 0b1111;
		playerData >>= 4;
		CGameMain::pweponLevel[2] = playerData & 0b1111;
		playerData >>= 4;
		CGameMain::pweponLevel[1] = playerData & 0b1111;
		playerData >>= 4;
		CGameMain::pweponLevel[0] = playerData & 0b1111;

	}
	else if (CGameMain::m_stageNo == 1) {
		//���v���C�z�񏉊���
		if (mode == 0) {
			for (int i = 0; i < 12020; i++) {
				REPLAY_DATA[i] = 0;
			}
			REPLAY_DATA[0] = MapData::m_seed;
		}

		//�v���C���[�h�̏ꍇ�̓��v���C�f�[�^�ɏ����l��ݒ�
		//���X�e�[�W�Ɍ��݂̃X�e�[�^�X���L�^

		playerData = CGameMain::m_hp;
		playerData <<= 8;
		playerData += CGameMain::m_maxHp;
		playerData <<= 3;
		playerData += CGameMain::weponSelect;
		playerData <<= 4;
		playerData += CGameMain::m_speed;
		playerData <<= 4;
		playerData += CGameMain::playerCount;
		playerData <<= 4;
		playerData += CGameMain::bom;
		//data1
		REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4 + 1] = playerData;
		//data2
		REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4 + 2] = CGameMain::m_score;

		playerData = CGameMain::pweponLevel[0];
		playerData <<= 4;
		playerData += CGameMain::pweponLevel[1];
		playerData <<= 4;
		playerData += CGameMain::pweponLevel[2];
		playerData <<= 4;
		playerData += CGameMain::pweponLevel[3];
		playerData <<= 4;
		playerData += CGameMain::pweponLevel[4];
		playerData <<= 4;
		playerData += CGameMain::pweponLevel[5];
		//data3
		REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4 + 3] = playerData;
	}

	//=========================================================================
	//	���C���[�̏������Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	//�w�i���C���[
	m_backGroundLayer = cocos2d::Layer::create();
	this->addChild(m_backGroundLayer);
	//�ǃ��C���[
	m_wallLayer = cocos2d::Layer::create();
	this->addChild(m_wallLayer);
	//�L�����N�^�[���C���[
	m_characterLayer = cocos2d::Layer::create();
	this->addChild(m_characterLayer);
	//�X�e�[�^�X���C���[
	m_interFaceLayer = cocos2d::Layer::create();
	this->addChild(m_interFaceLayer);
	//=========================================================================
	//	�}�b�v�̏������Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================

	mapSeed = mode == 0 ? MapData::m_seed : REPLAY_DATA[0];
	//mapSeed = 1508591550;

	//�X�e�[�W���ɃV�[�h�l�ݒ�
	srand(mapSeed);
	for (int i = 1; i < CGameMain::m_stageNo; i++) {
		rand();
	}
	mapSeed = rand();

	m_pMapData.create(mapSeed);
	srand(mapSeed);
	cocos2d::log("seed=%d mapdata=%d", mapSeed, MapData::m_seed);
	//=========================================================================
	//	�}�b�v�̐����̐ݒ�
	//=========================================================================

	//m_pMap = CMap::create(MAP_FILE_STAGE_1);
	m_pMap = CMap::create(IMAGE_FILE_BACKGROUND);
	//�X�N���[�����x�̐ݒ�
	this->m_pMap->m_scrollMove.m_velX = 1.0f;
	//���[�v�ݒ�(���[�v����ݒ�)
	this->m_pMap->m_isLoop = true;
	//���C���[�Ɏ��t��
	m_backGroundLayer->addChild(this->m_pMap);
	//=========================================================================
	//	�v���C���[�̏������Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	m_pPlayerChara = CPlayerCharacter::create();
	
	m_characterLayer->addChild(this->m_pPlayerChara);

	bomCount = 0;

	//=========================================================================
	//	�v���C���[�o���b�g ( �v���C���[�̒e ) �̏������Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	for (int i = 0; i < CBullet::MAX_BULLET; i++)
	{
		m_pPlayerBullets[i] = NULL;
	}

	//=========================================================================
	//	�G�̏������Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	for (int i = 0; i < CEnemyCharacter::MAX_ENEMY; i++)
	{
		m_pEnemyCharas[i] = NULL;
	}
	//=========================================================================
	//	�G�̒e�̏������Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	//�G�̒e�̔z�񏉊���
	for (int i = 0; i < CBullet::MAX_BULLET; i++) {
		m_pEnemyBullets[i] = NULL;
	}

	//=========================================================================
	//	�G�o���f�[�^�̏������Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	//���ݎQ�ƒ��̏o���f�[�^�ԍ��̏�����
	this->m_enemyLaunchIndex = 0;

	//���ݎQ�ƒ��̏o���x���ԍ��̏�����
	this->m_enemyAleartIndex = 0;
	for (int i = 0; i < (int)MapData::m_pEnemyLaunchData.size(); i++) {
		if (MapData::m_pEnemyLaunchData[i].m_frame > 60) {
			this->m_enemyAleartIndex = i;
			cocos2d::log("aleartIndex = %d", i);
			break;
		}
	}

	//�t���[���J�E���^�[�̏�����
	this->m_frameCounter = 0;
	//�X�e�[�W�N���A�t���[���̏�����
	this->m_clearFrame = CLEAR_FRAME;
	//this->m_clearFrame = 600;

	//=========================================================================
	//�@�G�t�F�N�g�̏������Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	for (int i = 0; i < CEfect::MAX_EFFECT; i++)
	{
		m_pEffects[i] = NULL;
	}

	//=========================================================================
	//�@�ǂ̏������Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	for (int i = 0; i < CWall::MAX_WALL; i++)
	{
		m_pWalls[i] = NULL;
	}

	//�Ǐo��X���W
	m_pWallXpos = 0;
	//�ǃJ�E���^�[
	m_wallCounter = 0;
	//�ǈړ��X�s�[�h
	//WALL_SPEED = 0.5;

	//BGM�̍Đ�
	if (mode != 5) {
		switch (CGameMain::m_stageNo) {
		case 1:
			this->m_bgmid = AudioEngine::play2d(SOUND_FILE_BGM_1);
			break;
		case 2:
			this->m_bgmid = AudioEngine::play2d(SOUND_FILE_BGM_2);
			break;
		case 3:
			this->m_bgmid = AudioEngine::play2d(SOUND_FILE_BGM_3);
			break;
		}
	}

	AudioEngine::setVolume(this->m_bgmid, BGM_VOLUME / 100.0f);

	//���[�v�̐ݒ�(true...���[�v����@false...���[�v���Ȃ�)
	AudioEngine::setLoop(this->m_bgmid, true);
	//�Ȃ�������ŉ�����
	AudioEngine::getDuration(this->m_bgmid);
	//�T�E���h�f�B���C������
	soundDeray = 0;
	//=========================================================================
	//	���[�U�[�C���^�[�t�F�[�X�̏������Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	//HP���x���̐����Ə�����
	m_pHpLabel = CHpLabel::create();
	m_pHpLabel->setStatus(&m_pPlayerChara->m_status);

	//���C���[�ɒ���t����
	m_interFaceLayer->addChild(m_pHpLabel);

	//HP�Q�[�W�̐����Ə�����

	CCRenderTexture* pRenderTexture = CCRenderTexture::create(204, 20);
	pRenderTexture->setPosition(180.0f, 468.0f);
	pRenderTexture->beginWithClear(255, 0, 0, 255);

	//�`��I��
	pRenderTexture->end();
	//���C���[�Ɏ��t��
	m_interFaceLayer->addChild(pRenderTexture);

	m_pHpGuage = CHpGuage::create();
	//�v���C���[�̃X�e�[�^�X��ݒ�
	m_pHpGuage->setStatus(&m_pPlayerChara->m_status);
	//���C���[�ɒ���t����
	m_interFaceLayer->addChild(m_pHpGuage);


	//�X�R�A���x���̐����Ə�����
	m_pScoreLabel = CScoreLabel::create();

	m_pScoreLabel->setStatus(&m_pPlayerChara->m_status);

	//���C���[�ɒ���t����
	m_interFaceLayer->addChild(m_pScoreLabel);

	//�X�e�[�W���x���̐����Ə�����
	m_pStageLabel = CStageNoLabel::create();

	m_pStageLabel->setStage(&this->m_stageNo);

	//���C���[�ɒ���t����
	m_interFaceLayer->addChild(m_pStageLabel);

	//�v���C���[���x���̐����Ə�����
	m_pPlayerLabel = CPlayerLabel::create();

	m_pPlayerLabel->setPlayer(&this->playerCount);

	//���C���[�ɒ���t����
	m_interFaceLayer->addChild(m_pPlayerLabel);

	//�{�����x���̐����Ə�����
	m_pBomLabel = CBomLabel::create();

	m_pBomLabel->setBom(&this->bom);

	//���C���[�ɒ���t����
	m_interFaceLayer->addChild(m_pBomLabel);

	//�U����ރ��x����������
	int fsize = 17;
	//�m�[�}��
	//�^�C�g�����x���̐����Ǝ��t��
	pweponLavel[0] = cocos2d::Label::createWithTTF("NORMAL", FONT_FILE_STARWARS, fsize);
	//�����ʒu�̐ݒ�
	pweponLavel[0]->setPosition(51.0f, 10.0f);
	//�����F�̐ݒ�
	pweponLavel[0]->setColor(Color3B(200, 200, 200));
	//���C���[�Ɏ��t��
	m_interFaceLayer->addChild(pweponLavel[0]);

	//���x���\��
	pweponLevelLavel[0] = cocos2d::Label::createWithTTF(
		cocos2d::StringUtils::format("Level %d", CGameMain::pweponLevel[0] + 1),
		FONT_FILE_STARWARS, fsize);
	//�����ʒu�̐ݒ�
	pweponLevelLavel[0]->setPosition(51.0f, 30.0f);
	//�����F�̐ݒ�
	pweponLevelLavel[0]->setColor(Color3B(200, 200, 200));
	//���C���[�Ɏ��t��
	m_interFaceLayer->addChild(pweponLevelLavel[0]);

	//����
	//�^�C�g�����x���̐����Ǝ��t��
	pweponLavel[1] = cocos2d::Label::createWithTTF("EXPLOSION", FONT_FILE_STARWARS, fsize);
	//�����ʒu�̐ݒ�
	pweponLavel[1]->setPosition(157.0f, 10.0f);
	//�����F�̐ݒ�
	pweponLavel[1]->setColor(Color3B(200, 200, 200));
	//���C���[�Ɏ��t��
	m_interFaceLayer->addChild(pweponLavel[1]);

	//���x���\��
	pweponLevelLavel[1] = cocos2d::Label::createWithTTF(
		cocos2d::StringUtils::format("Level %d", CGameMain::pweponLevel[1] + 1),
		FONT_FILE_STARWARS, fsize);
	//�����ʒu�̐ݒ�
	pweponLevelLavel[1]->setPosition(157.0f, 30.0f);
	//�����F�̐ݒ�
	pweponLevelLavel[1]->setColor(Color3B(200, 200, 200));
	//���C���[�Ɏ��t��
	m_interFaceLayer->addChild(pweponLevelLavel[1]);

	//���
	//�^�C�g�����x���̐����Ǝ��t��
	pweponLavel[2] = cocos2d::Label::createWithTTF("BACK", FONT_FILE_STARWARS, fsize);
	//�����ʒu�̐ݒ�
	pweponLavel[2]->setPosition(263.0f, 10.0f);
	//�����F�̐ݒ�
	pweponLavel[2]->setColor(Color3B(200, 200, 200));
	//���C���[�Ɏ��t��
	m_interFaceLayer->addChild(pweponLavel[2]);

	//���x���\��
	pweponLevelLavel[2] = cocos2d::Label::createWithTTF(
		cocos2d::StringUtils::format("Level %d", CGameMain::pweponLevel[2] + 1),
		FONT_FILE_STARWARS, fsize);
	//�����ʒu�̐ݒ�
	pweponLevelLavel[2]->setPosition(263.0f, 30.0f);
	//�����F�̐ݒ�
	pweponLevelLavel[2]->setColor(Color3B(200, 200, 200));
	//���C���[�Ɏ��t��
	m_interFaceLayer->addChild(pweponLevelLavel[2]);

	//���[�U�[
	//�^�C�g�����x���̐����Ǝ��t��
	pweponLavel[3] = cocos2d::Label::createWithTTF("LASER", FONT_FILE_STARWARS, fsize);
	//�����ʒu�̐ݒ�
	pweponLavel[3]->setPosition(369.0f, 10.0f);
	//�����F�̐ݒ�
	pweponLavel[3]->setColor(Color3B(200, 200, 200));
	//���C���[�Ɏ��t��
	m_interFaceLayer->addChild(pweponLavel[3]);

	//���x���\��
	pweponLevelLavel[3] = cocos2d::Label::createWithTTF(
		cocos2d::StringUtils::format("Level %d", CGameMain::pweponLevel[3] + 1),
		FONT_FILE_STARWARS, fsize);
	//�����ʒu�̐ݒ�
	pweponLevelLavel[3]->setPosition(369.0f, 30.0f);
	//�����F�̐ݒ�
	pweponLevelLavel[3]->setColor(Color3B(200, 200, 200));
	//���C���[�Ɏ��t��
	m_interFaceLayer->addChild(pweponLevelLavel[3]);

	//�U��
	//�^�C�g�����x���̐����Ǝ��t��
	pweponLavel[4] = cocos2d::Label::createWithTTF("INDCTION", FONT_FILE_STARWARS, fsize);
	//�����ʒu�̐ݒ�
	pweponLavel[4]->setPosition(475.0f, 10.0f);
	//�����F�̐ݒ�
	pweponLavel[4]->setColor(Color3B(200, 200, 200));
	//���C���[�Ɏ��t��
	m_interFaceLayer->addChild(pweponLavel[4]);

	//���x���\��
	pweponLevelLavel[4] = cocos2d::Label::createWithTTF(
		cocos2d::StringUtils::format("Level %d", CGameMain::pweponLevel[4] + 1),
		FONT_FILE_STARWARS, fsize);
	//�����ʒu�̐ݒ�
	pweponLevelLavel[4]->setPosition(475.0f, 30.0f);
	//�����F�̐ݒ�
	pweponLevelLavel[4]->setColor(Color3B(200, 200, 200));
	//���C���[�Ɏ��t��
	m_interFaceLayer->addChild(pweponLevelLavel[4]);

	//�U�e
	//�^�C�g�����x���̐����Ǝ��t��
	pweponLavel[5] = cocos2d::Label::createWithTTF("MULTIPLE", FONT_FILE_STARWARS, fsize);
	//�����ʒu�̐ݒ�
	pweponLavel[5]->setPosition(581.0f, 10.0f);
	//�����F�̐ݒ�
	pweponLavel[5]->setColor(Color3B(200, 200, 200));
	//���C���[�Ɏ��t��
	m_interFaceLayer->addChild(pweponLavel[5]);

	//���x���\��
	pweponLevelLavel[5] = cocos2d::Label::createWithTTF(
		cocos2d::StringUtils::format("Level %d", CGameMain::pweponLevel[5] + 1),
		FONT_FILE_STARWARS, fsize);
	//�����ʒu�̐ݒ�
	pweponLevelLavel[5]->setPosition(581.0f, 30.0f);
	//�����F�̐ݒ�
	pweponLevelLavel[5]->setColor(Color3B(200, 200, 200));
	//���C���[�Ɏ��t��
	m_interFaceLayer->addChild(pweponLevelLavel[5]);

	//�I���U���^�C�v�̐F��ς���
	pweponLavel[weponSelect]->setColor(Color3B(200, 0, 0));
	pweponLevelLavel[weponSelect]->setColor(Color3B(200, 0, 0));

	//�A�C�e���N���X�ɍU�����x�����x����n��
	CItem::pweponLevelLavel = pweponLevelLavel;

	//�U���͐ݒ�
	m_pPlayerChara->m_shotPower = this->pweponPower[weponSelect][pweponLevel[weponSelect]];
	//�U���Ԋu�ݒ�
	m_pPlayerChara->m_shotInterval = this->pweponInterval[weponSelect][pweponLevel[weponSelect]];
	//�U���p�����[�^�ݒ�
	m_pPlayerChara->m_shotParam = this->pweponParam[weponSelect][pweponLevel[weponSelect]];
	//�U���ړ��ʐݒ�
	m_pPlayerChara->m_shotVel = this->pweponVel[weponSelect][pweponLevel[weponSelect]];


	//=========================================================================
	//	�A�C�e�� �̏������Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	for (int i = 0; i < CItem::MAX_ITEM; i++)
	{
		m_pItems[i] = NULL;
	}

	//=========================================================================
	//	�G�f�[�^�̓ǂݍ���
	//=========================================================================
	//this->loadEnemyLaunchData(this->m_enemyLaunchDataFileNameList[this->m_stageNo - 1]);

	//=========================================================================
	//	�X�e�[�W���[�h
	//=========================================================================
	this->m_stageMode = STAGE_MODE::UPDATE;

	//=========================================================================
	//	���x��
	//=========================================================================
	pLavelArray[10] = { NULL };

	//=========================================================================
	//	�I�u�W�F�N�g�J�E���g���Z�b�g
	//=========================================================================
	//�I�u�W�F�N�g�J�E���g�p
	//�G�L�����J�E���g
	m_pEnemyCount = 0;
	//�v���C���[�e�J�E���g
	m_pPlayerBulletCount = 0;
	//�e�J�E���g
	m_pEnemyBulletCount = 0;
	//�G�t�F�N�g�J�E���g
	m_pEfectCount = 0;
	//�A�C�e���J�E���g
	m_pItemCount = 0;
	//�ǃJ�E���g
	m_pWallCount = 0;

	//=========================================================================
	//	�w�i�f���\���J�E���g�t���[�����Z�b�g
	//=========================================================================
	m_planetFrame = 0;
	//=========================================================================
	//	�f���v���C�J�n�t���[������
	//=========================================================================
	if (mode == 5) {
		int buf_se_volume = SE_VOLUME;
		//���ʂ��O�ɂ���
		SE_VOLUME = 0;
		int shift_frame;
		int testaa;
		if (DEMO_FRAME > REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4]) {
			shift_frame = 0;
			m_clearFrame = REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4];
			testaa = 0;
		}
		else {
			shift_frame = CTitle::Rand % (REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4] - DEMO_FRAME + 1) * 0.9f;

			m_clearFrame = shift_frame + DEMO_FRAME;
			testaa = REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4];
		}
		se_flg = false;
		//�f���v���C���x��
		pLavelDemo = cocos2d::Label::createWithTTF("DEMO PLAY", FONT_FILE_STARWARS, 50);

		//�����ʒu�̐ݒ�
		pLavelDemo->setPosition(320.0f, 240.0f);
		pLavelDemo->setColor(Color3B(200, 200, 200));
		//���C���[�Ɏ��t��
		m_interFaceLayer->addChild(pLavelDemo);
		cocos2d::log("shift start");
		for (int i = 0; i < shift_frame; i++) {
			this->stageUpdateFunc(0);
		}
		cocos2d::log("shift end");
		se_flg = true;
		SE_VOLUME = buf_se_volume;


	}

	//=========================================================================
	//
	//	�����܂łɏ������A�����ݒ�̃R�[�h��ǉ�
	//
	//=========================================================================

	return true;
}
void CGameMain::call_back(bool a) {
	OutputDebugString(L"�R�[���o�b�N���s----------------------------------------\n");
}
/**
*	@desc	�X�V����
*	@param	�P�t���[���o�ߎ���
*/
void CGameMain::update(float deltaTime_) {
	//AudioEngine::getDuration(this->m_bgmid), this->m_frameCounter;
	//���v���C�{���Ȃ特���{���ɂ���
	if (mode == 3) {
		AudioEngine::setCurrentTimeAll(0.066666666666666666f);
	}
	if (mode == 4) {
		AudioEngine::setCurrentTimeAll(0.133333333333333333f);
	}

	// esc �L�[����������Q�[���I��
	if (inputflag.m_esc == true) {
		cocos2d::Director::getInstance()->end();
	}

	//���[�h�ɂ��؂�ւ�
	switch (this->m_stageMode) {
	case STAGE_MODE::START:
		this->stageStartFunc();
		break;
	case STAGE_MODE::UPDATE:
		for (int i = 0; i < (mode >= 3 && mode != 5 ? (mode == 3 ? 4 : 8) : 1) && m_stageMode == STAGE_MODE::UPDATE; i++) {
			this->stageUpdateFunc(deltaTime_);
		}
		break;
		//�X�e�[�W�I������
	case STAGE_MODE::END:
		this->stageEndFunc();
		break;
		//�X�e�[�W�ꎞ��~����
	case STAGE_MODE::PAUSE:
		this->stagePauseFunc();
		break;
		//�X�e�[�W�ꎞ��~����
	case STAGE_MODE::GAME_OVER:
		this->gameOverFunc();
		break;
	default:
		break;
	}

}


void CGameMain::inputFunc() {
	
	//���̓t���O�ݒ�
	CInputJoystick::inputFunc(mode);
	
	//�U���^�C�v�؂�ւ�
	if (CInputJoystick::m_change == true) {

		if (m_xKeyDownFlag == false) {
			m_xKeyDownFlag = true;

			//�ύX�O�����F�̐ݒ�
			pweponLavel[weponSelect]->setColor(Color3B(200, 200, 200));
			pweponLevelLavel[weponSelect]->setColor(Color3B(200, 200, 200));
			//�U���^�C�v�ύX
			weponSelect++;
			if (weponSelect >= 6)
				weponSelect = 0;

			//�ύX�㕶���F�̐ݒ�
			pweponLavel[weponSelect]->setColor(Color3B(200, 0, 0));
			pweponLevelLavel[weponSelect]->setColor(Color3B(200, 0, 0));

			//�U���͐ݒ�
			m_pPlayerChara->m_shotPower = this->pweponPower[weponSelect][pweponLevel[weponSelect]];
			//�U���Ԋu�ݒ�
			m_pPlayerChara->m_shotInterval = this->pweponInterval[weponSelect][pweponLevel[weponSelect]];
			//�U���p�����[�^�ݒ�
			m_pPlayerChara->m_shotParam = this->pweponParam[weponSelect][pweponLevel[weponSelect]];
			//�U���ړ��ʐݒ�
			m_pPlayerChara->m_shotVel = this->pweponVel[weponSelect][pweponLevel[weponSelect]];
			//���[�U�[�t���O�m�F
			if (laserFlg)
				laserFlg = false;
		}
	}
	else {
		if (m_xKeyDownFlag = true) {
			m_xKeyDownFlag = false;
		}
	}

	//�v���C���[������ł������΂��B
	if (m_pPlayerChara->m_activeFlag == false) {
		return;
	}
	//�����Ɩ��G����
	if (resCount != 0) {

		//�\���_��
		if (resCount % 5 == 0 && playerCount >= 0) {
			if (resCount / 5 % 2 == 0) {
				m_pPlayerChara->setVisible(true);
			}
			else {
				m_pPlayerChara->setVisible(false);
			}
		}
		resCount--;
		if (resCount == 0) {
			//���G���ԏI��
			resurrection = false;
			m_pPlayerChara->setVisible(true);
		}
		else if (resCount > 120) {
			//�������[�V������
			return;
		}

	}

	//�f����ʂ͑�����͂Ń^�C�g����ʂɑJ��
	if (mode == 5) {

		if (m_frameCounter % 30 == 0) {
			pLavelDemo->setVisible(!pLavelDemo->isVisible());
		}
		if (!SCENE_END) {

			if (CInputJoystick::m_repPause ||
				CInputJoystick::m_repSpeed ||
				CInputJoystick::m_repSpeed2 ||
				CInputJoystick::m_repLeft ||
				CInputJoystick::m_repRight ||
				CInputJoystick::m_repUp ||
				CInputJoystick::m_repDown ||
				playerCount < 0 && resCount > 0 && resCount <= 120 ||
				m_frameCounter >= m_clearFrame ||
				m_frameCounter >= REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4]
				) {
				//�J�ڒ��I�����
				SCENE_END = true;
				//�^�C�g��BGM�t���O��߂�
				//CTitle::TitleBgm = -1;
				AudioEngine::setLoop(CTitle::TitleBgm, true);
				this->unscheduleUpdate();
				Scene* pScene = CTitle::createScene();
				Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
				return;
			}
		}

	}

	if (playerCount < 0 && resCount > 0 && resCount <= 120 || m_frameCounter == (mode == 0 ? m_clearFrame : REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4])) {
		if (mode == 5) {
			return;
		}
		cocos2d::log(" clear = " + REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4]);
		//���X�e�[�W����
		if (playerCount >= 0 && mode == 0) {
			//�v���C���[�c�@������Ȃ玟�X�e�[�W��

			//�t���[���J�E���g�L�^
			REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4] = m_frameCounter;

			//���v���C����Ȃ���Ύ��X�e�[�W�ɃJ�E���g�A�b�v
			if (mode == 0) {
				++CGameMain::m_stageNo;
				//���݃X�e�[�^�X�ݒ�
				CGameMain::m_hp = m_pPlayerChara->m_status.getHp(),
					CGameMain::m_maxHp = m_pPlayerChara->m_status.getMaxHp();
				CGameMain::m_attackPt = m_pPlayerChara->m_status.getAttackPt();
				CGameMain::m_score = m_pPlayerChara->m_status.getScore();
				CGameMain::m_speed = m_pPlayerChara->m_status.getSpeed();

				if (CGameMain::m_stageNo != 4) {
					//���X�e�[�W�Ɍ��݂̃X�e�[�^�X���L�^
					playerData = CGameMain::m_hp;
					playerData <<= 8;
					playerData += CGameMain::m_maxHp;
					playerData <<= 3;
					playerData += CGameMain::weponSelect;
					playerData <<= 4;
					playerData += CGameMain::m_speed;
					playerData <<= 4;
					playerData += CGameMain::playerCount;
					playerData <<= 4;
					playerData += CGameMain::bom;
					//data1
					REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4 + 1] = playerData;
					//data2
					REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4 + 2] = CGameMain::m_score;

					playerData = CGameMain::pweponLevel[0];
					playerData <<= 4;
					playerData += CGameMain::pweponLevel[1];
					playerData <<= 4;
					playerData += CGameMain::pweponLevel[2];
					playerData <<= 4;
					playerData += CGameMain::pweponLevel[3];
					playerData <<= 4;
					playerData += CGameMain::pweponLevel[4];
					playerData <<= 4;
					playerData += CGameMain::pweponLevel[5];
					//data3
					REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4 + 3] = playerData;

				}

			}



			//�X�e�[�W�N���A
			if (mode == 0) {

				//�J�ڒ��I�����
				SCENE_END = true;

				//BGM��~
				AudioEngine::stopAll();
				this->unscheduleUpdate();

				//�^�C���A�b�v����
				if (m_frameCounter >= CLEAR_FRAME) {
					//SE
					if (se_flg) {
						int seid = AudioEngine::play2d(SOUND_FILE_TIME_UP);
						AudioEngine::setVolume(seid, SE_VOLUME / 100.0f);
					}


				}

				if (CGameMain::m_stageNo == 4) {
					//�Q�[���N���A����

					CReplaySelect::replay_flg = true;

					//�X�R�A�o�^
					if (mode == 0 && m_pPlayerChara->m_status.getScore() > SCORE) {
						cocos2d::log("score=%d", m_pPlayerChara->m_status.getScore());
						//config.dat�ɐݒ��ۑ�
						int buf[3] = { BGM_VOLUME ,SE_VOLUME,m_pPlayerChara->m_status.getScore() };
						//�t�@�C���|�C���^
						FILE *file1;
						file1 = fopen("config.dat", "wb");
						fwrite(buf, sizeof(int), 3, file1);
						fclose(file1);
						SCORE = m_pPlayerChara->m_status.getScore();
					}
					//�^�C�g��BGM�t���O��߂�
					CTitle::TitleBgm = -1;

					this->unscheduleUpdate();
					Scene* pScene = CReplaySelect::createScene();
					Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
					return;
				}
				else {
					//�X�e�[�W�N���A����
					Scene* pScene = CStageTitle::createScene();

					Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
					return;
				}

			}

		}
		//�^�C���A�b�v����
		if (m_frameCounter >= CLEAR_FRAME) {
			//SE
			if (se_flg) {
				int seid = AudioEngine::play2d(SOUND_FILE_TIME_UP);
				AudioEngine::setVolume(seid, SE_VOLUME / 100.0f);
			}


		}
		//�Q�[���I�[�o�[
		//���[�h���Q�[���I�[�o�[�ɕύX
		this->m_stageMode = STAGE_MODE::GAME_OVER;
		m_characterLayer->getParent();
		//���ꎞ��~
		AudioEngine::pauseAll();
		//���[�h�ʏ�ɕύX
		if (mode >= 3) {
			mode = 2;
		}

		if (mode == 0) {
			if (se_flg) {
				int gameoverid = AudioEngine::play2d(SOUND_FILE_GAME_OVER);
				AudioEngine::setVolume(gameoverid, SE_VOLUME / 100.0f);
			}

		}

		//�J�[�\��SE
		int seid = AudioEngine::play2d(SOUND_FILE_CURSOR_2);
		AudioEngine::setVolume(seid, SE_VOLUME / 100.0f);
		//�|�[�Y��ʍ쐬
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
			1,			//�J�[�\����Y�ő�
			0,			//�J�[�\����X�ʒu
			1,			//�J�[�\����Y�ʒu
			150,		//�J�[�\����X���W
			200,		//�J�[�\����Y���W
			0.0f,		//X�ړ��T�C�Y
			100.0f,		//Y�ړ��T�C�Y
			5,			//�ړ��A�j���[�V�����t���[��
			true,		//�����[�v
			true,		//�c���[�v
			10,			//�ᑬ�҂��t���[��
			5			//�����҂��t���[��
		);
		//�J�[�\���z�u
		m_interFaceLayer->addChild(m_pCursor);
		//�J�[�\���p�J�E���^�[������
		c_frameCounter = 0;

		//�{�^�����m�h�~
		this->m_spaceKeyDownFlag = true;

		//�{�^�������t���O
		p_scene = false;

		//PLAY���x���̐����Ǝ��t��
		pLavelArray[1] = cocos2d::Label::createWithTTF("RETURN", FONT_FILE_STARWARS, 62);
		//�����ʒu�̐ݒ�
		pLavelArray[1]->setPosition(320.0f, 300.0f);
		//�����F�̐ݒ�
		pLavelArray[1]->setColor(Color3B(0, 200, 200));
		//���C���[�Ɏ��t��
		m_interFaceLayer->addChild(pLavelArray[1]);


		//END���x���̐����Ǝ��t��
		pLavelArray[0] = cocos2d::Label::createWithTTF("END", FONT_FILE_STARWARS, 62);
		//�����ʒu�̐ݒ�
		pLavelArray[0]->setPosition(320.0f, 200.0f);
		//�����F�̐ݒ�
		pLavelArray[0]->setColor(Color3B(0, 200, 200));
		//���C���[�Ɏ��t��
		m_interFaceLayer->addChild(pLavelArray[0]);

		//�X�R�A�o�^
		if (m_pPlayerChara->m_status.getScore() > SCORE) {
			cocos2d::log("score=%d", m_pPlayerChara->m_status.getScore());
			//config.dat�ɐݒ��ۑ�
			int buf[3] = { BGM_VOLUME ,SE_VOLUME,m_pPlayerChara->m_status.getScore() };
			//�t�@�C���|�C���^
			FILE *file1;
			file1 = fopen("config.dat", "wb");
			fwrite(buf, sizeof(int), 3, file1);
			fclose(file1);
			SCORE = m_pPlayerChara->m_status.getScore();
		}
		return;
	}

	if (CInputJoystick::m_right == true)
	{
		//�E��󂪉����ꂽ
		//���x�ɒl��ݒ肷��
		m_pPlayerChara->m_move.m_velX = m_pPlayerChara->m_status.getSpeed() / 2;
	}
	if (CInputJoystick::m_right == false && CInputJoystick::m_left == false)
	{
		//���E��󂪗����ꂽ
		//���x�����Z�b�g����
		m_pPlayerChara->m_move.m_velX = 0;
	}
	if (CInputJoystick::m_left == true)
	{
		//�E��󂪉����ꂽ
		//���x�ɒl��ݒ肷��
		m_pPlayerChara->m_move.m_velX = -m_pPlayerChara->m_status.getSpeed() / 2;
	}

	if (CInputJoystick::m_up == true)
	{
		//���󂪉����ꂽ
		//���x�ɒl��ݒ肷��
		m_pPlayerChara->m_move.m_velY = m_pPlayerChara->m_status.getSpeed() / 2;
	}
	if (CInputJoystick::m_up == false && CInputJoystick::m_down == false)
	{
		//�㉺��󂪗����ꂽ
		//���x�����Z�b�g����
		m_pPlayerChara->m_move.m_velY = 0;
	}
	if (CInputJoystick::m_down == true)
	{
		//����󂪉����ꂽ
		//���x�ɒl��ݒ肷��
		m_pPlayerChara->m_move.m_velY = -m_pPlayerChara->m_status.getSpeed() / 2;
	}

	if (m_pPlayerChara->m_shotCounter > 0) {
		//�e���˗p�J�E���^�[��0����Ȃ�
		//�e���˗p�J�E���^�[���f�N�������g
		m_pPlayerChara->m_shotCounter--;
	}

	if (CInputJoystick::m_shot == true)
	{
		shotPlayerBullet((BULLET_TYPE)weponSelect);
	}
	else {
		//���[�U�[�t���O�m�F
		laserFlg = false;
	}


	//space�L�[����������
	if (!SCENE_END && (CInputJoystick::m_pause == true || (mode >= 2 && CInputJoystick::m_repPause == true))) {
		//a�L�[��������Ă�����
		if (this->m_spaceKeyDownFlag == false) {
			//a�L�[�������ꂽ
			this->m_spaceKeyDownFlag = true;
			if (m_stageMode == STAGE_MODE::PAUSE) {
				//���[�h���ꎞ��~�����ɕύX
				this->m_stageMode = STAGE_MODE::UPDATE;
				//���ꎞ��~����
				AudioEngine::resumeAll();
			}
			else {
				//���[�h���ꎞ��~�ɕύX
				this->m_stageMode = STAGE_MODE::PAUSE;
				m_characterLayer->getParent();
				//���ꎞ��~
				AudioEngine::pauseAll();
				//���[�h�ʏ�ɕύX
				if (mode >= 3) {
					mode = 2;
				}
				//�J�[�\��SE
				int seid = AudioEngine::play2d(SOUND_FILE_CURSOR_2);
				AudioEngine::setVolume(seid, SE_VOLUME / 100.0f);

				//�|�[�Y��ʍ쐬
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
					2,			//�J�[�\����Y�ő�
					0,			//�J�[�\����X�ʒu
					2,			//�J�[�\����Y�ʒu
					150,		//�J�[�\����X���W
					100,		//�J�[�\����Y���W
					0.0f,		//X�ړ��T�C�Y
					100.0f,		//Y�ړ��T�C�Y
					5,			//�ړ��A�j���[�V�����t���[��
					true,		//�����[�v
					true,		//�c���[�v
					10,			//�ᑬ�҂��t���[��
					5			//�����҂��t���[��
				);
				//�J�[�\���z�u
				m_interFaceLayer->addChild(m_pCursor);
				//�J�[�\���p�J�E���^�[������
				c_frameCounter = 0;

				//�{�^�����m�h�~
				this->m_spaceKeyDownFlag = true;

				//�{�^�������t���O
				p_scene = false;

				//PLAY���x���̐����Ǝ��t��
				pLavelArray[2] = cocos2d::Label::createWithTTF("PLAY", FONT_FILE_STARWARS, 62);
				//�����ʒu�̐ݒ�
				pLavelArray[2]->setPosition(320.0f, 300.0f);
				//�����F�̐ݒ�
				pLavelArray[2]->setColor(Color3B(0, 200, 200));
				//���C���[�Ɏ��t��
				m_interFaceLayer->addChild(pLavelArray[2]);

				//PLAY���x���̐����Ǝ��t��
				pLavelArray[1] = cocos2d::Label::createWithTTF("RETURN", FONT_FILE_STARWARS, 62);
				//�����ʒu�̐ݒ�
				pLavelArray[1]->setPosition(320.0f, 200.0f);
				//�����F�̐ݒ�
				pLavelArray[1]->setColor(Color3B(0, 200, 200));
				//���C���[�Ɏ��t��
				m_interFaceLayer->addChild(pLavelArray[1]);


				//END���x���̐����Ǝ��t��
				pLavelArray[0] = cocos2d::Label::createWithTTF("END", FONT_FILE_STARWARS, 62);
				//�����ʒu�̐ݒ�
				pLavelArray[0]->setPosition(320.0f, 100.0f);
				//�����F�̐ݒ�
				pLavelArray[0]->setColor(Color3B(0, 200, 200));
				//���C���[�Ɏ��t��
				m_interFaceLayer->addChild(pLavelArray[0]);
			}
			return;
		}

	}
	else {
		//a�L�[��������Ă�����
		if (this->m_spaceKeyDownFlag == true) {
			//a�L�[�������ꂽ
			this->m_spaceKeyDownFlag = false;
		}
	}
	//s�L�[����������
	if (CInputJoystick::m_stage == true) {
		//s�L�[��������Ă�����
		if (this->m_sKeyDownFlag == false) {
			//s�L�[�������ꂽ
			this->m_sKeyDownFlag = true;
			//���[�h���ꎞ��~�ɕύX
			//this->m_stageMode = STAGE_MODE::END;
			//�{������
			if (bomCount == 0 && bom != 0) {
				bomCount = 120;
				//���G�ݒ�
				bom--;
				//�G�t�F�N�g��\������
				int index = getFreeIndex(m_pEffects, CEfect::MAX_EFFECT);

				//�󂢂Ă���v�f�����݂��Ȃ���΃G�t�F�N�g�̏����͍s��Ȃ�
				if (index != -1) {
					//�G�t�F�N�g�C���X�^���X�̍쐬
					CEfect* pEfe = this->launchEffect(
						EFFECT_TYPE::BOM,
						320,
						240
					);

					//���C���[�ɒ���t����
					m_characterLayer->addChild(pEfe);

					//�z��ɃA�h���X�����t����
					this->m_pEffects[index] = pEfe;
					//�I�u�W�F�N�g�J�E���g�X�V
					if (index >= m_pEfectCount) {
						m_pEfectCount = index;
					}
					//�������ʉ�
					if (se_flg) {
						int m_bomBgmid = AudioEngine::play2d(SOUND_FILE_BOM);
						AudioEngine::setVolume(m_bomBgmid, SE_VOLUME / 60.0f);
					}

				}
			}
			return;
		}

	}
	else {
		//s�L�[��������Ă�����
		if (this->m_sKeyDownFlag == true) {
			//s�L�[�������ꂽ
			this->m_sKeyDownFlag = false;
		}
	}
	//�{���J�E���g�_�E��
	if (bomCount != 0) {
		bomCount--;
	}

	//���v���C���x
	if (mode != 5) {
		if (mode >= 2) {
			if (CInputJoystick::m_repSpeed2 == true) {
				//4�{��
				mode = 4;
			}
			else if (CInputJoystick::m_repSpeed == true) {
				//2�{��
				mode = 3;
			}
			else {
				//����
				mode = 2;
			}
		}
	}


}

void CGameMain::inputFunc2() {
	//�{�^�������ꂽ���΂�
	if (p_scene)
		return;

	//���̓t���O�ݒ�
	CInputJoystick::inputFunc(1);

	//z�L�[����������
	if (CInputJoystick::m_shot == true) {
		//z�L�[��������Ă�����
		if (this->m_zKeyDownFlag == false) {
			//z�L�[�������ꂽ
			this->m_zKeyDownFlag = true;
			//�J�[�\��SE
			if (!p_scene) {
				int seid = AudioEngine::play2d(SOUND_FILE_CURSOR_2);
				AudioEngine::setVolume(seid, SE_VOLUME / 100.0f);
			}
			//�{�^�������t���O�L��
			p_scene = true;

			return;
		}

	}
	else {
		//z�L�[��������Ă�����
		if (this->m_zKeyDownFlag == true) {
			//z�L�[�������ꂽ
			this->m_zKeyDownFlag = false;

		}
	}

	//�J�[�\���ړ�����
	//�J�[�\���̓��͏���
	m_pCursor->inputFunc();

}
void CGameMain::moveFunc() {
	//�}�b�v�̒l�̔��f����
	m_pMap->moveFunc();

	// �v���C���[�̈ړ�
	m_pPlayerChara->moveFunc();

	//�v���C���[�̒e�̈ړ�����
	for (int i = 0; i <= m_pPlayerBulletCount; i++) {
		//NULL���������Ă������΂�
		if (m_pPlayerBullets[i] == NULL)
			continue;

		//�ړ��������s��
		//m_pPlayerBullets[i]->m_move.moveByVell();
		m_pPlayerBullets[i]->moveFunc();
	}
	//�G�̈ړ�����
	for (int i = 0; i <= m_pEnemyCount; i++) {
		//NULL���������Ă������΂�
		if (m_pEnemyCharas[i] == NULL)
			continue;

		//�ړ��������s��
		m_pEnemyCharas[i]->moveFunc();

		//�{�X�œ|���ꂽ�ꍇ�̃G�t�F�N�g����
		if (m_pEnemyCharas[i]->bossflg && m_pEnemyCharas[i]->m_activeFlag == false) {
			
			//�����x����
			m_pEnemyCharas[i]->setOpacity(255.0f * ((float)m_pEnemyCharas[i]->bossCount / 300.0f));

			//��������
			m_pEnemyCharas[i]->m_move.m_posY -= 0.5f;

			//�G�t�F�N�g����
			if (m_pEnemyCharas[i]->bossCount % 10 == 0) {
				//�G�t�F�N�g��\������
				int index = getFreeIndex(m_pEffects, CEfect::MAX_EFFECT);

				//�󂢂Ă���v�f�����݂��Ȃ���΃G�t�F�N�g�̏����͍s��Ȃ�
				if (index != -1) {
					//�G�t�F�N�g�C���X�^���X�̍쐬
					CEfect* pEfe = this->launchEffect(
						EFFECT_TYPE::EXPLOSION,
						rand() % (int)m_pEnemyCharas[i]->m_chip.size.width -
						(m_pEnemyCharas[i]->m_chip.size.width / 2) +
						m_pEnemyCharas[i]->m_move.m_posX,
						rand() % (int)m_pEnemyCharas[i]->m_chip.size.height -
						(m_pEnemyCharas[i]->m_chip.size.height / 2) +
						m_pEnemyCharas[i]->m_move.m_posY
					);

					//���C���[�ɒ���t����
					m_characterLayer->addChild(pEfe);

					//�z��ɃA�h���X�����t����
					this->m_pEffects[index] = pEfe;
					//�I�u�W�F�N�g�J�E���g�X�V
					if (index >= m_pEfectCount) {
						m_pEfectCount = index;
					}
					//�v���C���[�������ʉ�
					if (se_flg) {
						m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_PLAYER_EXPLOSION);
						AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 120.0f);
					}

				}

			}
			//�{�X�J�E���g�_�E��
			m_pEnemyCharas[i]->bossCount--;
		}
	}

	//�G�̒e�̈ړ�����
	for (int i = 0; i <= m_pEnemyBulletCount; i++) {
		//NULL���������Ă������΂�
		if (m_pEnemyBullets[i] == NULL)
			continue;

		//�ړ��������s��
		m_pEnemyBullets[i]->moveFunc();
	}

	//�G�t�F�N�g�̈ړ�����
	for (int i = 0; i <= m_pEfectCount; i++) {
		//NULL���������Ă������΂�
		if (m_pEffects[i] == NULL)
			continue;

		//�ړ��������s��
		m_pEffects[i]->moveFunc();
	}

	//�A�C�e���̈ړ�����
	for (int i = 0; i <= m_pItemCount; i++) {
		//NULL���������Ă������΂�
		if (m_pItems[i] == NULL)
			continue;

		//�ړ��������s��
		m_pItems[i]->moveFunc();
	}

	//�ǂ̈ړ�����
	for (int i = 0; i <= m_pWallCount; i++) {
		//NULL���������Ă������΂�
		if (m_pWalls[i] == NULL)
			continue;

		//�ړ��������s��
		m_pWalls[i]->moveFunc();
	}
}
void CGameMain::applyFunc() {
	//�}�b�v�̒l�̔��f����
	m_pMap->applyFunc();

	m_pPlayerChara->applyFunc();
	//�v���C���[�̒e�̒l�̔ɉh����
	for (int i = 0; i <= m_pPlayerBulletCount; i++) {
		//NULL���������Ă������΂�
		if (m_pPlayerBullets[i] == NULL)
			continue;

		//�l�̔��f���s��
		m_pPlayerBullets[i]->applyFunc();
	}

	//�G�̔��f����
	for (int i = 0; i <= m_pEnemyCount; i++) {
		//NULL���������Ă������΂�
		if (m_pEnemyCharas[i] == NULL)
			continue;

		//�ړ��������s��
		m_pEnemyCharas[i]->applyFunc();
		//�{�X�I�����ړ�����
		if (m_pEnemyCharas[i]->bossflg && m_pEnemyCharas[i]->m_activeFlag == false) {
			m_pEnemyCharas[i]->setPosition(m_pEnemyCharas[i]->m_move.m_posX + rand() % 8 - 4,
				m_pEnemyCharas[i]->m_move.m_posY + rand() % 8 - 4);
		}
	}

	//�G�̒e�̔��f����
	for (int i = 0; i <= m_pEnemyBulletCount; i++) {
		//NULL���������Ă������΂�
		if (m_pEnemyBullets[i] == NULL)
			continue;

		//�ړ��������s��
		m_pEnemyBullets[i]->applyFunc();
	}

	//�G�t�F�N�g�̔��f����
	for (int i = 0; i <= m_pEfectCount; i++) {
		//NULL���������Ă������΂�
		if (m_pEffects[i] == NULL)
			continue;

		//�ړ��������s��
		m_pEffects[i]->applyFunc();
	}

	//�A�C�e���̔��f����
	for (int i = 0; i <= m_pItemCount; i++) {
		//NULL���������Ă������΂�
		if (m_pItems[i] == NULL)
			continue;

		//�ړ��������s��
		m_pItems[i]->applyFunc();
	}

	//�ǂ̈ړ�����
	for (int i = 0; i <= m_pWallCount; i++) {
		//NULL���������Ă������΂�
		if (m_pWalls[i] == NULL)
			continue;

		//�ړ��������s��
		m_pWalls[i]->applyFunc();
	}
}

void CGameMain::animationFunc() {
	m_pPlayerChara->animationFunc();

	//�v���C���[�e�A�j���[�V����
	for (int i = 0; i <= m_pPlayerBulletCount; i++) {
		//�v�f��NULL�Ȃ��΂�
		if (m_pPlayerBullets[i] == NULL)
			continue;

		//�v���C���[�e�̃A�j���[�V����
		m_pPlayerBullets[i]->animationFunc();

	}
	//�G�A�j���[�V����
	for (int i = 0; i <= m_pEnemyCount; i++) {
		//�v�f��NULL�Ȃ��΂�
		if (m_pEnemyCharas[i] == NULL)
			continue;

		//�G�̃A�j���[�V����
		m_pEnemyCharas[i]->animationFunc();
	}
	//�G�e�A�j���[�V����
	for (int i = 0; i <= m_pEnemyBulletCount; i++) {
		//�v�f��NULL�Ȃ��΂�
		if (m_pEnemyBullets[i] == NULL)
			continue;

		//�G�̃A�j���[�V����
		m_pEnemyBullets[i]->animationFunc();
	}

	//�G�t�F�N�g�A�j���[�V����
	for (int i = 0; i <= m_pEfectCount; i++) {
		//�v�f��NULL�Ȃ��΂�
		if (m_pEffects[i] == NULL)
			continue;

		//�G�̃A�j���[�V����
		m_pEffects[i]->animationFunc();
	}

	//�A�C�e���A�j���[�V����
	for (int i = 0; i <= m_pItemCount; i++) {
		//NULL���������Ă������΂�
		if (m_pItems[i] == NULL)
			continue;

		//�A�C�e���̃A�j���[�V����
		m_pItems[i]->animationFunc();
	}
}

void CGameMain::endOfScreen() {
	//�v���C���[�̉�ʒ[���菈��
	m_pPlayerChara->endOfScreen();

	//�v���C���[�̒e�̉�ʊO���菈��
	for (int i = 0; i <= m_pPlayerBulletCount; i++) {
		//�v�f��NULL�Ȃ��΂�
		if (m_pPlayerBullets[i] == NULL)
			continue;

		//�e�摜�̍��[�̍��W����ʉE�[�̍��W���傫���Ȃ�����
		m_pPlayerBullets[i]->endOfScreen();
	}
	//�G�̉�ʊO���菈��
	for (int i = 0; i <= m_pEnemyCount; i++) {
		//�v�f��NULL�Ȃ��΂�
		if (m_pEnemyCharas[i] == NULL)
			continue;

		//�G�^�C�v���{�X�Ȃ��΂�
		if (m_pEnemyCharas[i]->bossflg)
			continue;

		//�e�摜�̍��[�̍��W����ʉE�[�̍��W���傫���Ȃ�����
		m_pEnemyCharas[i]->endOfScreen();
	}

	//�G�̒e�̉�ʊO���菈��
	for (int i = 0; i <= m_pEnemyBulletCount; i++) {
		//�v�f��NULL�Ȃ��΂�
		if (m_pEnemyBullets[i] == NULL)
			continue;

		//�e�摜�̍��[�̍��W����ʉE�[�̍��W���傫���Ȃ�����
		m_pEnemyBullets[i]->endOfScreen();
	}

	//�A�C�e���̉�ʊO���菈��
	for (int i = 0; i <= m_pItemCount; i++) {
		//NULL���������Ă������΂�
		if (m_pItems[i] == NULL)
			continue;

		//�A�C�e���̍��[�̍��W����ʉE�[�̍��W���傫���Ȃ�����
		m_pItems[i]->endOfScreen();
	}

	//�ǂ̉�ʊO���菈��
	for (int i = 0; i <= m_pWallCount; i++) {
		//NULL���������Ă������΂�
		if (m_pWalls[i] == NULL)
			continue;

		//�ǂ̍��[�̍��W����ʉE�[�̍��W���傫���Ȃ�����
		m_pWalls[i]->endOfScreen();
	}

	//�G�t�F�N�g�̉�ʊO���菈��
	for (int i = 0; i <= m_pEfectCount; i++) {
		//NULL���������Ă������΂�
		if (m_pEffects[i] == NULL)
			continue;

		//�ǂ̍��[�̍��W����ʉE�[�̍��W���傫���Ȃ�����
		m_pEffects[i]->endOfScreen();
	}
}

/**
*@desc �G�̏o��
*@param �Q�Ƃ���G�Ǘ��f�[�^�̃A�h���X
*/
CEnemyCharacter* CGameMain::launchEnemy(CEnemyLaunchData* pEneLaunchData) {
	//�G�̐���
	CEnemyCharacter* pEne = CEnemyCharacter::create();
	switch (pEneLaunchData->m_type) {
		//�^�C�vA�̓G
	case ENEMY_TYPE::TYPE_A:
		//�G�̐ݒ�
		pEne->setTexture(IMAGE_FILE_CHARACTER_2);

		//�؂����`
		pEne->m_chip = CChip(0, 21, 40, 40);

		//�؂����`�̐ݒ�
		pEne->setTextureRect(pEne->m_chip);

		//�i�s�����̐ݒ�
		pEne->direction = pEneLaunchData->direction;

		//�i�s�������E�Ȃ�摜���]
		if (pEne->direction == false) {
			pEne->setScaleX(-1.0f);
		}

		//�ړ��f�[�^�ɏ����ʒu�̐ݒ�(�`�b�v�̕��T�C�Y�̔����������炷)
		pEne->m_move.setPos(pEneLaunchData->m_posX, pEneLaunchData->m_posY);

		//�ړ��f�[�^�ɏ������x�̐ݒ�(X���W��-4����)
		if (pEneLaunchData->action.size() != 0) {
			pEne->m_move.setVel(pEneLaunchData->action[0].x - WALL_SPEED, pEneLaunchData->action[0].y);
		}
		else {
			pEne->m_move.setVel(-WALL_SPEED, 0);
		}


		//�A�j���[�V�����f�[�^�̏�����
		pEne->m_anime.set(10, 4);

		//�Փ˔���p�f�[�^�̏�����
		pEne->m_body.set(
			-16,
			16,
			16,
			-16
		);

		//���˂���e�̃^�C�v�̐ݒ�
		//�ʏ�e
		pEne->m_bulletType = BULLET_TYPE::ENEMY_NORMAL;
		//�X�e�[�^�X�̏�����
		pEne->m_status.set(30, 30, 1, 100);

		//�s���^�C�v�̐ݒ�
		pEne->m_actionType = pEneLaunchData->m_actionType;

		break;
	case ENEMY_TYPE::TYPE_B:
		//�G�̐ݒ�
		pEne->setTexture(IMAGE_FILE_CHARACTER_2);

		//�؂����`
		pEne->m_chip = CChip(0, 61, 40, 40);

		//�؂����`�̐ݒ�
		pEne->setTextureRect(pEne->m_chip);

		//�i�s�����̐ݒ�
		pEne->direction = pEneLaunchData->direction;

		//�i�s�������E�Ȃ�摜���]
		if (pEne->direction == false) {
			pEne->setScaleX(-1.0f);
		}

		//�ړ��f�[�^�ɏ����ʒu�̐ݒ�(�`�b�v�̕��T�C�Y�̔����������炷)
		pEne->m_move.setPos(pEneLaunchData->m_posX, pEneLaunchData->m_posY);

		//�ړ��f�[�^�ɏ������x�̐ݒ�(X���W��-4����)
		if (pEneLaunchData->action.size() != 0) {
			pEne->m_move.setVel(pEneLaunchData->action[0].x - WALL_SPEED, pEneLaunchData->action[0].y);
		}
		else {
			pEne->m_move.setVel(-WALL_SPEED, 0);
		}


		//�A�j���[�V�����f�[�^�̏�����
		pEne->m_anime.set(10, 4);

		//�Փ˔���p�f�[�^�̏�����
		pEne->m_body.set(
			-16,
			16,
			16,
			-16
		);

		//���˂���e�̃^�C�v�̐ݒ�
		//�ʏ�e
		pEne->m_bulletType = BULLET_TYPE::ENEMY_FAN;

		//�X�e�[�^�X�̏�����
		pEne->m_status.set(40, 40, 1, 500);

		//�s���^�C�v�̐ݒ�
		pEne->m_actionType = pEneLaunchData->m_actionType;

		break;
	case ENEMY_TYPE::TYPE_C:
		//�G�̐ݒ�
		pEne->setTexture(IMAGE_FILE_CHARACTER_2);

		//�؂����`
		pEne->m_chip = CChip(0, 101, 40, 40);

		//�؂����`�̐ݒ�
		pEne->setTextureRect(pEne->m_chip);

		//�i�s�����̐ݒ�
		pEne->direction = pEneLaunchData->direction;

		//�i�s�������E�Ȃ�摜���]
		if (pEne->direction == false) {
			pEne->setScaleX(-1.0f);
		}

		//�ݒu����
		pEne->setRotation(pEneLaunchData->install * 90);

		//�ړ��f�[�^�ɏ����ʒu�̐ݒ�(�`�b�v�̕��T�C�Y�̔����������炷)
		pEne->m_move.setPos(pEneLaunchData->m_posX, pEneLaunchData->m_posY);

		//�ړ��f�[�^�ɏ������x�̐ݒ�(X���W��-4����)
		if (pEneLaunchData->action.size() != 0) {
			pEne->m_move.setVel(pEneLaunchData->action[0].x - WALL_SPEED, pEneLaunchData->action[0].y);
		}
		else {
			pEne->m_move.setVel(-WALL_SPEED, 0);
		}


		//�A�j���[�V�����f�[�^�̏�����
		pEne->m_anime.set(10, 1);

		//�Փ˔���p�f�[�^�̏�����
		pEne->m_body.set(
			-16,
			10,
			16,
			-16
		);

		//���˂���e�̃^�C�v�̐ݒ�
		//�ʏ�e
		pEne->m_bulletType = BULLET_TYPE::ENEMY_AIMING;
		//�X�e�[�^�X�̏�����
		pEne->m_status.set(30, 30, 1, 100);

		//�s���^�C�v�̐ݒ�
		pEne->m_actionType = pEneLaunchData->m_actionType;

		//�C�g�̐����Ǝ��t��
		pEne->m_pChr = Sprite::create(IMAGE_FILE_CHARACTER_2);
		//�����ʒu�̐ݒ�
		pEne->m_pChr->setPosition(20.0f, 20.0f);

		//�؂����`�̐ݒ�
		pEne->m_pChr->setTextureRect(CChip(40, 100, 40, 40));

		//���C���[�Ɏ��t��
		pEne->addChild(pEne->m_pChr);
		
		break;
		//�^�C�vA�̓G
	case ENEMY_TYPE::TYPE_D:
		//�G�̐ݒ�
		pEne->setTexture(IMAGE_FILE_CHARACTER_2);

		//�؂����`
		pEne->m_chip = CChip(0, 141, 40, 40);

		//�؂����`�̐ݒ�
		pEne->setTextureRect(pEne->m_chip);

		//�i�s�����̐ݒ�
		pEne->direction = pEneLaunchData->direction;

		//�i�s�������E�Ȃ�摜���]
		if (pEne->direction == false) {
			pEne->setScaleX(-1.0f);
		}

		//�ړ��f�[�^�ɏ����ʒu�̐ݒ�(�`�b�v�̕��T�C�Y�̔����������炷)
		pEne->m_move.setPos(pEneLaunchData->m_posX, pEneLaunchData->m_posY);

		//�ړ��f�[�^�ɏ������x�̐ݒ�(X���W��-4����)
		if (pEneLaunchData->action.size() != 0) {
			pEne->m_move.setVel(pEneLaunchData->action[0].x - WALL_SPEED, pEneLaunchData->action[0].y);
		}
		else {
			pEne->m_move.setVel(-WALL_SPEED, 0);
		}


		//�A�j���[�V�����f�[�^�̏�����
		pEne->m_anime.set(10, 4);

		//�Փ˔���p�f�[�^�̏�����
		pEne->m_body.set(
			-16,
			16,
			16,
			-16
		);

		//���˂���e�̃^�C�v�̐ݒ�
		//�ʏ�e
		pEne->m_bulletType = BULLET_TYPE::ENEMY_NORMAL;
		//�X�e�[�^�X�̏�����
		pEne->m_status.set(20, 20, 1, 50);

		//�s���^�C�v�̐ݒ�
		pEne->m_actionType = pEneLaunchData->m_actionType;

		break;
	case ENEMY_TYPE::TYPE_E:
		//�G�̐ݒ�
		pEne->setTexture(IMAGE_FILE_CHARACTER_2);

		//�؂����`
		pEne->m_chip = CChip(0, 181, 40, 40);

		//�؂����`�̐ݒ�
		pEne->setTextureRect(pEne->m_chip);

		//�i�s�����̐ݒ�
		pEne->direction = pEneLaunchData->direction;

		//�i�s�������E�Ȃ�摜���]
		if (pEne->direction == false) {
			pEne->setScaleX(-1.0f);
		}

		//�ړ��f�[�^�ɏ����ʒu�̐ݒ�(�`�b�v�̕��T�C�Y�̔����������炷)
		pEne->m_move.setPos(pEneLaunchData->m_posX, pEneLaunchData->m_posY);

		//�ړ��f�[�^�ɏ������x�̐ݒ�(X���W��-4����)
		if (pEneLaunchData->action.size() != 0) {
			pEne->m_move.setVel(pEneLaunchData->action[0].x - WALL_SPEED, pEneLaunchData->action[0].y);
		}
		else {
			pEne->m_move.setVel(-WALL_SPEED, 0);
		}


		//�A�j���[�V�����f�[�^�̏�����
		pEne->m_anime.set(10, 4);

		//�Փ˔���p�f�[�^�̏�����
		pEne->m_body.set(
			-16,
			16,
			16,
			-16
		);

		//���˂���e�̃^�C�v�̐ݒ�
		//�ʏ�e
		pEne->m_bulletType = BULLET_TYPE::ENEMY_2WAY;

		//�X�e�[�^�X�̏�����
		pEne->m_status.set(40, 40, 1, 500);

		//�s���^�C�v�̐ݒ�
		pEne->m_actionType = pEneLaunchData->m_actionType;

		break;
	case ENEMY_TYPE::TYPE_BOSS_1:
		//�{�X�t���O�L��
		pEne->bossflg = true;

		//�G�̐ݒ�
		pEne->setTexture(IMAGE_FILE_BOSS_1);

		//�؂����`
		pEne->m_chip = CChip(0, 0, 200, 200);

		//�؂����`�̐ݒ�
		pEne->setTextureRect(pEne->m_chip);

		//�i�s�����̐ݒ�
		pEne->direction = pEneLaunchData->direction;

		//�i�s�������E�Ȃ�摜���]
		if (pEne->direction == false) {
			pEne->setScaleX(-1.0f);
		}

		//�ړ��f�[�^�ɏ����ʒu�̐ݒ�(�`�b�v�̕��T�C�Y�̔����������炷)
		pEne->m_move.setPos(pEneLaunchData->m_posX, pEneLaunchData->m_posY);

		//�ړ��f�[�^�ɏ������x�̐ݒ�(X���W��-4����)
		if (pEneLaunchData->action.size() != 0) {
			pEne->m_move.setVel(pEneLaunchData->action[0].x - WALL_SPEED, pEneLaunchData->action[0].y);
		}
		else {
			pEne->m_move.setVel(-WALL_SPEED, 0);
		}


		//�A�j���[�V�����f�[�^�̏�����
		pEne->m_anime.set(10, 0, true);

		//�Փ˔���p�f�[�^�̏�����
		pEne->m_body.set(
			0,
			40,
			70,
			-40
		);

		//���˂���e�̃^�C�v�̐ݒ�
		//�ʏ�e
		switch (CGameMain::m_stageNo) {
		case 1:
			pEne->m_bulletType = BULLET_TYPE::ENEMY_NORMAL;
			break;
		case 2:
			pEne->m_bulletType = BULLET_TYPE::ENEMY_FAN;
			break;
		case 3:
			pEne->m_bulletType = BULLET_TYPE::ENEMY_AIMING;
			break;
		default:
			pEne->m_bulletType = BULLET_TYPE::ENEMY_NORMAL;
			break;
		}

		//�X�e�[�^�X�̏�����
		pEne->m_status.set(1000, 1000, 1, 10000);

		//�s���^�C�v�̐ݒ�
		pEne->m_actionType = pEneLaunchData->m_actionType;
		break;
	default:
		break;
	}

	//�G�̃^�C�v��ݒ�
	pEne->e_enemyType = pEneLaunchData->m_type;

	//�L���t���O��true������
	pEne->m_activeFlag = true;

	//�A�C�e���ݒ�
	pEne->m_item = pEneLaunchData->m_item;
	/*
	if (rand() % 4 == 0) {
		pEne->m_item = (ITEM_TYPE)(rand() % 11);
	}
	else {
		pEne->m_item = (ITEM_TYPE)-1;
	}
	*/
	

	//�s���f�[�^�̐ݒ�
	pEne->action = pEneLaunchData->action;
	return pEne;
}


void CGameMain::checkActiveFlagAndRemove() {

	//�I�u�W�F�N�g�J�E���g�p
	int count = 0;

	for (int i = 0; i <= m_pPlayerBulletCount; i++) {
		//�v�f��NULL�Ȃ��΂�
		if (m_pPlayerBullets[i] == NULL)
			continue;
		if (m_pPlayerBullets[i]->m_activeFlag == false) {
			//���C���[������O��
			m_pPlayerBullets[i]->removeFromParent();

			//�z�����NULL����
			m_pPlayerBullets[i] = NULL;
		}
		else {
			//�Ō�̃A�N�e�B�u�ȃC���f�b�N�X���L�^
			count = i;
		}
	}
	//�폜���ꂽ���𔽉f������
	m_pPlayerBulletCount = count;
	//�e��J�E���g���Z�b�g
	count = 0;

	//�G�̃��C���[����̎��O������
	for (int i = 0; i <= m_pEnemyCount; i++) {
		//�v�f��NULL�Ȃ��΂�
		if (m_pEnemyCharas[i] == NULL)
			continue;

		if (m_pEnemyCharas[i]->m_activeFlag == false) {
			//�{�X�̏ꍇ
			if (m_pEnemyCharas[i]->bossflg) {
				//�J�E���g0�Ŏ��O��
				if (m_pEnemyCharas[i]->bossCount == 0) {
					//���C���[������O��
					m_pEnemyCharas[i]->removeFromParent();

					//�z�����NULL����
					m_pEnemyCharas[i] = NULL;

					//�X�e�[�W�N���A����
					//�I���t���[����ݒ肷��
					m_clearFrame = m_frameCounter + 300;
					if (se_flg) {
						int m_clearBgmid = AudioEngine::play2d(SOUND_FILE_STAGE_CLEAR);
						AudioEngine::setVolume(m_clearBgmid, SE_VOLUME / 100.0f);
					}


				}
				else {
					//�Ō�̃A�N�e�B�u�ȃC���f�b�N�X���L�^
					count = i;
				}
			}
			else {
				//�ʏ�̏ꍇ
				//���C���[������O��
				m_pEnemyCharas[i]->removeFromParent();

				//�z�����NULL����
				m_pEnemyCharas[i] = NULL;
			}
		}
		else {
			//�Ō�̃A�N�e�B�u�ȃC���f�b�N�X���L�^
			count = i;
		}
	}
	//�폜���ꂽ���𔽉f������
	m_pEnemyCount = count;
	//�e��J�E���g���Z�b�g
	count = 0;

	//�G�̒e�̃��C���[����̎��O������
	for (int i = 0; i <= m_pEnemyBulletCount; i++) {
		//�v�f��NULL�Ȃ��΂�
		if (m_pEnemyBullets[i] == NULL)
			continue;

		if (m_pEnemyBullets[i]->m_activeFlag == false) {
			//���C���[������O��
			m_pEnemyBullets[i]->removeFromParent();

			//�z�����NULL����
			m_pEnemyBullets[i] = NULL;
		}
		else {
			//�Ō�̃A�N�e�B�u�ȃC���f�b�N�X���L�^
			count = i;
		}
	}
	//�폜���ꂽ���𔽉f������
	m_pEnemyBulletCount = count;
	//�e��J�E���g���Z�b�g
	count = 0;

	//�G�t�F�N�g�̃��C���[����̎��O������
	for (int i = 0; i <= m_pEfectCount; i++) {
		//�v�f��NULL�Ȃ��΂�
		if (m_pEffects[i] == NULL)
			continue;

		if (m_pEffects[i]->m_activeFlag == false) {
			//���C���[������O��
			m_pEffects[i]->removeFromParent();

			//�z�����NULL����
			m_pEffects[i] = NULL;
		}
		else {
			//�Ō�̃A�N�e�B�u�ȃC���f�b�N�X���L�^
			count = i;
		}
	}
	//�ő�C���f�b�N�X�𔽉f������
	m_pEfectCount = count;
	//�e��J�E���g���Z�b�g
	count = 0;

	//�A�C�e���̃��C���[����̎��O������
	for (int i = 0; i <= m_pItemCount; i++) {
		//�v�f��NULL�Ȃ��΂�
		if (m_pItems[i] == NULL)
			continue;

		if (m_pItems[i]->m_activeFlag == false) {
			//���C���[������O��
			m_pItems[i]->removeFromParent();

			//�z�����NULL����
			m_pItems[i] = NULL;
		}
		else {
			//�Ō�̃A�N�e�B�u�ȃC���f�b�N�X���L�^
			count = i;
		}
	}
	//�폜���ꂽ���𔽉f������
	m_pItemCount = count;
	//�e��J�E���g���Z�b�g
	count = 0;

	//�ǂ̃��C���[����̎��O������
	for (int i = 0; i <= m_pWallCount; i++) {
		//�v�f��NULL�Ȃ��΂�
		if (m_pWalls[i] == NULL)
			continue;

		if (m_pWalls[i]->m_activeFlag == false) {
			//���C���[������O��
			m_pWalls[i]->removeFromParent();

			//�z�����NULL����
			m_pWalls[i] = NULL;
		}
		else {
			//�Ō�̃A�N�e�B�u�ȃC���f�b�N�X���L�^
			count = i;
		}
	}
	//�폜���ꂽ���𔽉f������
	m_pWallCount = count;
}

void CGameMain::shotEnemyBullet() {
	for (int i = 0; i <= m_pEnemyCount; i++) {

		//NULL���������Ă������΂�
		if (m_pEnemyCharas[i] == NULL)
			continue;

		//����ł������΂�
		if (m_pEnemyCharas[i]->m_activeFlag == false)
			continue;

		//�e���˃t���O��false�Ȃ��΂�
		if (m_pEnemyCharas[i]->m_shotFlag == false) {
			continue;
		}

		//�G�������Ă���G�̒e�̃^�C�v�𔻒肵�Ēe�𔭎˂�����
		switch (m_pEnemyCharas[i]->m_bulletType) {
			//�ʏ�e
		case BULLET_TYPE::ENEMY_NORMAL:
		{
			//�z���NULL�������Ă���Y�����ԍ����擾
			int index = getFreeIndex(m_pEnemyBullets, CBullet::MAX_BULLET);

			//�󂢂Ă���v�f�����݂��Ȃ���Βe�̔��ˏ����͍s��Ȃ�
			if (index == -1) {
				return;
			}
			//�i�s�����m�F
			int direction = m_pEnemyCharas[i]->direction ? 1 : -1;
			//�v���C���[�̒e�̔���
			CBullet* pBul = m_pEnemyCharas[i]->shotBullet(BULLET_TYPE::ENEMY_NORMAL,
				(direction == 1 ? -(m_pEnemyCharas[i]->m_body.m_left) : m_pEnemyCharas[i]->m_body.m_right) * direction,
				0,
				-8 * direction * m_shotVel[GAME_MODE],
				0);
			//NULL�Ȃ��΂�
			if (pBul == NULL)
				continue;

			//�X�e�[�^�X�̏�����
			pBul->m_status.set(1, 1, 10 - m_shotAttack[GAME_MODE], 0);

			m_characterLayer->addChild(pBul);

			//�z��ɃA�h���X�����t����
			this->m_pEnemyBullets[index] = pBul;
			//�I�u�W�F�N�g�J�E���g�X�V
			if (index >= m_pEnemyBulletCount) {
				m_pEnemyBulletCount = index;
			}
		}
		break;

		//���@�_���e(�v���C���[�_���e)
		case BULLET_TYPE::ENEMY_AIMING:
		{

			//�z���NULL�������Ă���Y�����ԍ����擾
			int index = getFreeIndex(m_pEnemyBullets, CBullet::MAX_BULLET);

			//�󂢂Ă���v�f�����݂��Ȃ���Βe�̔��ˏ����͍s��Ȃ�
			if (index == -1) {
				return;
			}

			//�v���C���[�̈ʒu���擾
			float playerPosX = m_pPlayerChara->m_move.m_posX;
			float playerPosY = m_pPlayerChara->m_move.m_posY;

			//�G�̈ʒu���擾
			float enePosX = m_pEnemyCharas[i]->m_move.m_posX;
			float enePosY = m_pEnemyCharas[i]->m_move.m_posY;

			//�G����v���C���[�܂ł̃x�N�g�����v�Z
			float vecX = playerPosX - enePosX;
			float vecY = playerPosY - enePosY;

			//�x�N�g���̒��������߂�
			float len = sqrt(vecX * vecX + vecY * vecY);

			//�P�t���[���P�ʂ̃x�N�g�����v�Z����B�܂葬�x���P�̎��̑��x�����߂�
			float velX = vecX / len;
			float velY = vecY / len;

			//�������v�Z����
			float vel = m_pEnemyCharas[i]->bossflg ? 10.0f : 5.0f * m_shotVel[GAME_MODE];
			int pos = m_pEnemyCharas[i]->bossflg ? 0 : 4;
			velX = velX * vel;
			velY = velY * vel;

			//�v���C���[�̒e�̔���
			CBullet* pBul = m_pEnemyCharas[i]->shotBullet(BULLET_TYPE::ENEMY_AIMING,
				velX * pos,
				velY * pos,
				velX,
				velY);
			//NULL�Ȃ��΂�
			if (pBul == NULL)
				continue;

			//�X�e�[�^�X�̏�����
			pBul->m_status.set(1, 1, 10 - m_shotAttack[GAME_MODE], 0);

			m_characterLayer->addChild(pBul);

			//�z��ɃA�h���X�����t����
			this->m_pEnemyBullets[index] = pBul;
			//�I�u�W�F�N�g�J�E���g�X�V
			if (index >= m_pEnemyBulletCount) {
				m_pEnemyBulletCount = index;
			}
		}
		break;
		case BULLET_TYPE::ENEMY_FAN:
		{
			for (int j = 0; j < 7; j++) {
				//�z���NULL�������Ă���Y�����ԍ����擾
				int index = getFreeIndex(m_pEnemyBullets, CBullet::MAX_BULLET);

				//�󂢂Ă���v�f�����݂��Ȃ���Βe�̔��ˏ����͍s��Ȃ�
				if (index == -1) {
					return;
				}

				//�p�x
				float angle = j * 30.0f + 90.0f;

				//�p�x���񎟃x�N�g�����擾
				float velX = cos(angle * M_PI / 180.0f) * 6.0f * m_shotVel[GAME_MODE];
				float velY = sin(angle * M_PI / 180.0f) * 6.0f * m_shotVel[GAME_MODE];
				//�i�s�����m�F
				int direction = m_pEnemyCharas[i]->direction ? 1 : -1;
				CBullet* pBul = m_pEnemyCharas[i]->shotBullet(BULLET_TYPE::ENEMY_FAN,
					(direction == 1 ? -(m_pEnemyCharas[i]->m_body.m_left) : m_pEnemyCharas[i]->m_body.m_right) * direction,
					0.0f,
					velX * direction,
					velY);


				//NULL�Ȃ��΂�
				if (pBul == NULL)
					return;

				//�X�e�[�^�X�̏�����
				pBul->m_status.set(1, 1, 10 - m_shotAttack[GAME_MODE], 0);

				//���C���[�ɒ���t����
				m_characterLayer->addChild(pBul);

				//�z��ɃA�h���X�𒣂�t����
				this->m_pEnemyBullets[index] = pBul;
				//�I�u�W�F�N�g�J�E���g�X�V
				if (index >= m_pEnemyBulletCount) {
					m_pEnemyBulletCount = index;
				}
			}
		}
		break;
		//�O��e
		case BULLET_TYPE::ENEMY_2WAY:
		{
			for (int j = 0; j < 2; j++) {
				//�z���NULL�������Ă���Y�����ԍ����擾
				int index = getFreeIndex(m_pEnemyBullets, CBullet::MAX_BULLET);

				//�󂢂Ă���v�f�����݂��Ȃ���Βe�̔��ˏ����͍s��Ȃ�
				if (index == -1) {
					return;
				}

				//�i�s�����m�F
				int direction = j == 0 ? 1 : -1;
				CBullet* pBul = m_pEnemyCharas[i]->shotBullet(BULLET_TYPE::ENEMY_FAN,
					(direction == 1 ? -(m_pEnemyCharas[i]->m_body.m_left) : m_pEnemyCharas[i]->m_body.m_right) * direction,
					0.0f,
					-8 * direction * m_shotVel[GAME_MODE],
					0);


				//NULL�Ȃ��΂�
				if (pBul == NULL)
					return;

				//�X�e�[�^�X�̏�����
				pBul->m_status.set(1, 1, 10 - m_shotAttack[GAME_MODE], 0);

				//���C���[�ɒ���t����
				m_characterLayer->addChild(pBul);

				//�z��ɃA�h���X�𒣂�t����
				this->m_pEnemyBullets[index] = pBul;
				//�I�u�W�F�N�g�J�E���g�X�V
				if (index >= m_pEnemyBulletCount) {
					m_pEnemyBulletCount = index;
				}
			}

		}
		break;
		default:
			break;
		}
		//���˃t���O����艺����
		m_pEnemyCharas[i]->m_shotFlag = false;

	}
}

/*
*@desc	�v���C���[�̒e�̔���
*@param	�e�^�C�v
*/
void CGameMain::shotPlayerBullet(BULLET_TYPE type) {
	//�e���˗p�J�E���^�[��0�ȉ��Ȃ�e�̔��˂��s��
	if (m_pPlayerChara->m_shotCounter <= 0) {
		//z�������ꂽ
		switch (type) {
		case BULLET_TYPE::PLAYER_NORMAL:
		{
			//�z���NULL�������Ă���Y�����ԍ����擾
			int index = getFreeIndex(m_pPlayerBullets, CBullet::MAX_BULLET);

			//�󂢂Ă�v�f�����݂��Ȃ���Βe�̔��ˏ����͍s��Ȃ�
			if (index == -1) {
				return;
			}

			CBullet* pBul = m_pPlayerChara->shotBullet(BULLET_TYPE::PLAYER_NORMAL,
				m_pPlayerChara->m_chip.size.width * 0.5f, 0.0f, m_pPlayerChara->m_shotVel, 0.0f);

			//NULL�Ȃ��΂�
			if (pBul == NULL)
				return;

			//�X�e�[�^�X�̏�����
			pBul->m_status.set(1, 1, m_pPlayerChara->m_shotPower, 0);

			//���C���[�ɒ���t����
			m_characterLayer->addChild(pBul);

			//�z��ɃA�h���X�𒣂�t����
			this->m_pPlayerBullets[index] = pBul;
			//�I�u�W�F�N�g�J�E���g�X�V
			if (index >= m_pPlayerBulletCount) {
				m_pPlayerBulletCount = index;
			}
		}
		break;
		case BULLET_TYPE::PLAYER_EXPLOSION:
		{
			//�z���NULL�������Ă���Y�����ԍ����擾
			int index = getFreeIndex(m_pPlayerBullets, CBullet::MAX_BULLET);

			//�󂢂Ă�v�f�����݂��Ȃ���Βe�̔��ˏ����͍s��Ȃ�
			if (index == -1) {
				return;
			}

			CBullet* pBul = m_pPlayerChara->shotBullet(BULLET_TYPE::PLAYER_EXPLOSION,
				m_pPlayerChara->m_chip.size.width * 0.5f, 0.0f, m_pPlayerChara->m_shotVel, 0.0f);

			//NULL�Ȃ��΂�
			if (pBul == NULL)
				return;

			//�X�e�[�^�X�̏�����
			pBul->m_status.set(1, 1, m_pPlayerChara->m_shotPower, 0);

			//���C���[�ɒ���t����
			m_characterLayer->addChild(pBul);

			//�z��ɃA�h���X�𒣂�t����
			this->m_pPlayerBullets[index] = pBul;
			//�I�u�W�F�N�g�J�E���g�X�V
			if (index >= m_pPlayerBulletCount) {
				m_pPlayerBulletCount = index;
			}
		}
		break;
		case BULLET_TYPE::PLAYER_BACK:
		{
			for (int i = 0; i < 2; i++) {
				//�z���NULL�������Ă���Y�����ԍ����擾
				int index = getFreeIndex(m_pPlayerBullets, CBullet::MAX_BULLET);

				//�󂢂Ă�v�f�����݂��Ȃ���Βe�̔��ˏ����͍s��Ȃ�
				if (index == -1) {
					return;
				}

				float fixX = m_pPlayerChara->m_chip.size.width * 0.5f;
				fixX = (i == 0) ? fixX : fixX * -1;
				float velX = (i == 0) ? m_pPlayerChara->m_shotVel : -m_pPlayerChara->m_shotVel;

				CBullet* pBul = m_pPlayerChara->shotBullet(BULLET_TYPE::PLAYER_NORMAL, fixX, 0.0f, velX, 0.0f);

				//NULL�Ȃ��΂�
				if (pBul == NULL)
					return;

				//�X�e�[�^�X�̏�����
				pBul->m_status.set(1, 1, m_pPlayerChara->m_shotPower, 0);

				//���C���[�ɒ���t����
				m_characterLayer->addChild(pBul);

				//�z��ɃA�h���X�𒣂�t����
				this->m_pPlayerBullets[index] = pBul;
				//�I�u�W�F�N�g�J�E���g�X�V
				if (index >= m_pPlayerBulletCount) {
					m_pPlayerBulletCount = index;
				}
			}
		}
		break;
		case BULLET_TYPE::PLAYER_LASER:
		{

			//���[�U�[�t���O�������̏ꍇ���[�U�[�����J�n
			if (laserFlg == false) {
				laserFlg = true;
				laserCounter = this->m_frameCounter;
				cocos2d::log("laser on");
			}
			else {
				return;
			}

			//�z���NULL�������Ă���Y�����ԍ����擾
			int index = getFreeIndex(m_pPlayerBullets, CBullet::MAX_BULLET);

			//�󂢂Ă�v�f�����݂��Ȃ���Βe�̔��ˏ����͍s��Ȃ�
			if (index == -1) {
				return;
			}

			//�v���C���[�̒e�̐���
			CBullet* pBul = CBullet::create();
			//�摜�̐ݒ�
			pBul->setTexture(IMAGE_FILE_LASER);
			//�؂����`
			pBul->m_chip = CChip(0, 0, 640, 1);
			pBul->setTextureRect(pBul->m_chip);
			//�A���J�[�|�C���g�����ɐݒ�
			pBul->setAnchorPoint(Vec2(0, 0));
			//�ړ��f�[�^�ɏ����ʒu�̐ݒ�
			pBul->m_move.setPos(m_pPlayerChara->m_move.m_posX + 15.0f, m_pPlayerChara->m_move.m_posY);

			//�����ʒu�𔻒�
			pBul->setPosition(pBul->m_move.m_posX, pBul->m_move.m_posY);

			//�L���t���O��true������
			pBul->m_activeFlag = true;

			//�e�^�C�v�̐ݒ�
			pBul->m_bulletType = BULLET_TYPE::PLAYER_LASER;

			//�A�j���[�V�����f�[�^�̏�����
			pBul->m_anime.set(1, 1, false);

			//�Փ˔���p�f�[�^�̏�����
			pBul->m_body.set(0, 1, 640, 0);

			//�v���C���[�ړ��f�[�^���L�^
			pBul->m_pmove = &m_pPlayerChara->m_move;

			//NULL�Ȃ��΂�
			if (pBul == NULL)
				return;

			//�X�e�[�^�X�̏�����
			pBul->m_status.set(1, 1, m_pPlayerChara->m_shotPower, 0);

			//���C���[�ɒ���t����
			m_characterLayer->addChild(pBul);

			//�z��ɃA�h���X�𒣂�t����
			this->m_pPlayerBullets[index] = pBul;
			//�I�u�W�F�N�g�J�E���g�X�V
			if (index >= m_pPlayerBulletCount) {
				m_pPlayerBulletCount = index;
			}
		}
		break;
		case BULLET_TYPE::PLAYER_INDUCTION:

		{
			//�z���NULL�������Ă���Y�����ԍ����擾
			int index = getFreeIndex(m_pPlayerBullets, CBullet::MAX_BULLET);

			//�󂢂Ă�v�f�����݂��Ȃ���Βe�̔��ˏ����͍s��Ȃ�
			if (index == -1) {
				return;
			}

			//�ړ��p�x
			float rotation = 0;
			//�ړ�����
			float vel = m_pPlayerChara->m_shotVel;

			CBullet* pBul = m_pPlayerChara->shotBullet(BULLET_TYPE::PLAYER_INDUCTION,
				m_pPlayerChara->m_chip.size.width * 0.5f, 0.0f, vel, 0.0f);

			//NULL�Ȃ��΂�
			if (pBul == NULL)
				return;

			//�X�e�[�^�X�̏�����
			pBul->m_status.set(1, 1, m_pPlayerChara->m_shotPower, 0);

			//���C���[�ɒ���t����
			m_characterLayer->addChild(pBul);

			//���[�h�����G�ɂ���
			pBul->mode = true;

			//��]�p�x
			pBul->rotation = rotation;

			//��]�p�x��
			pBul->param = m_pPlayerChara->m_shotParam;

			//�ړ�����
			pBul->vel = vel;

			//�z��ɃA�h���X�𒣂�t����
			this->m_pPlayerBullets[index] = pBul;
			//�I�u�W�F�N�g�J�E���g�X�V
			if (index >= m_pPlayerBulletCount) {
				m_pPlayerBulletCount = index;
			}
		}
		break;
		case BULLET_TYPE::PLAYER_MULTIPLE:
		{
			for (int i = 0; i < this->pweponParam[weponSelect][pweponLevel[weponSelect]]; i++) {
				//�z���NULL�������Ă���Y�����ԍ����擾
				int index = getFreeIndex(m_pPlayerBullets, CBullet::MAX_BULLET);

				//�󂢂Ă�v�f�����݂��Ȃ���Βe�̔��ˏ����͍s��Ȃ�
				if (index == -1) {
					return;
				}

				//�p�x
				float angle = i * 5.0f - (5.0f * (this->pweponParam[weponSelect][pweponLevel[weponSelect]] - 1) / 2);
				//�ړ�����
				float vel = m_pPlayerChara->m_shotVel;

				//�p�x���񎟃x�N�g�����擾
				float velX = cos(angle * M_PI / 180.0f) * vel;
				float velY = sin(angle * M_PI / 180.0f) * vel;

				CBullet* pBul = m_pPlayerChara->shotBullet(BULLET_TYPE::PLAYER_NORMAL,
					m_pPlayerChara->m_chip.size.width * 0.5f, 0.0f, velX, velY);

				//NULL�Ȃ��΂�
				if (pBul == NULL)
					return;

				//�X�e�[�^�X�̏�����
				pBul->m_status.set(1, 1, m_pPlayerChara->m_shotPower, 0);

				//���C���[�ɒ���t����
				m_characterLayer->addChild(pBul);

				//�z��ɃA�h���X�𒣂�t����
				this->m_pPlayerBullets[index] = pBul;
				//�I�u�W�F�N�g�J�E���g�X�V
				if (index >= m_pPlayerBulletCount) {
					m_pPlayerBulletCount = index;
				}
			}
		}
		break;
		case BULLET_TYPE::PLAYER_2WAY:
		{
			for (int i = 0; i < 2; i++) {
				//�z���NULL�������Ă���Y�����ԍ����擾
				int index = getFreeIndex(m_pPlayerBullets, CBullet::MAX_BULLET);

				//�󂢂Ă�v�f�����݂��Ȃ���Βe�̔��ˏ����͍s��Ȃ�
				if (index == -1) {
					return;
				}

				float fixX = (i == 0) ? 24 : -24;

				float velX = (i == 0) ? 6 : -6;

				CBullet* pBul = m_pPlayerChara->shotBullet(BULLET_TYPE::PLAYER_NORMAL, fixX, 0.0f, velX, 0.0f);

				//NULL�Ȃ��΂�
				if (pBul == NULL)
					return;

				//�X�e�[�^�X�̏�����
				pBul->m_status.set(1, 1, 1, 0);

				//���C���[�ɒ���t����
				m_characterLayer->addChild(pBul);

				//�z��ɃA�h���X�𒣂�t����
				this->m_pPlayerBullets[index] = pBul;
				//�I�u�W�F�N�g�J�E���g�X�V
				if (index >= m_pPlayerBulletCount) {
					m_pPlayerBulletCount = index;
				}
			}
		}
		break;
		case BULLET_TYPE::PLAYER_3WAY:
		{
			for (int i = 0; i < 3; i++) {
				//�z���NULL�������Ă���Y�����ԍ����擾
				int index = getFreeIndex(m_pPlayerBullets, CBullet::MAX_BULLET);

				//�󂢂Ă�v�f�����݂��Ȃ���Βe�̔��ˏ����͍s��Ȃ�
				if (index == -1) {
					return;
				}

				//�p�x
				float angle = i * 25.0f - 25.0f;

				//�p�x���񎟃x�N�g�����擾
				float velX = cos(angle * M_PI / 180.0f) * 6.0f;
				float velY = sin(angle * M_PI / 180.0f) * 6.0f;

				CBullet* pBul = m_pPlayerChara->shotBullet(BULLET_TYPE::PLAYER_NORMAL, 24.0f, 0.0f, velX, velY);

				//NULL�Ȃ��΂�
				if (pBul == NULL)
					return;

				//�X�e�[�^�X�̏�����
				pBul->m_status.set(1, 1, 1, 0);

				//���C���[�ɒ���t����
				m_characterLayer->addChild(pBul);

				//�z��ɃA�h���X�𒣂�t����
				this->m_pPlayerBullets[index] = pBul;
				//�I�u�W�F�N�g�J�E���g�X�V
				if (index >= m_pPlayerBulletCount) {
					m_pPlayerBulletCount = index;
				}
			}
		}
		break;
		default:
			break;
		}

		//�e�����˂��ꂽ��J�E���^�[���C���^�[�o���Ń��Z�b�g����
		m_pPlayerChara->m_shotCounter = m_pPlayerChara->m_shotInterval;

		//�e���ˌ��ʉ��̍Đ�
		if (se_flg) {
			int sound = AudioEngine::play2d(SOUND_FILE_LAUNCH_BULLET);
			AudioEngine::setVolume(sound, SE_VOLUME / 120.0f);
		}
	}
}
/**
*@desc �v���C���[�ƒe�̏Փ˔���
*/
void CGameMain::collisionPlayerAndEnemyBullets() {
	//�v���C���[������ł������΂�
	if (m_pPlayerChara->m_activeFlag == false || resurrection)
		return;

	//�v���C���[�̏Փ˔�����s���ۂ̈ʒu���擾
	CBody playerCollisionBody = m_pPlayerChara->m_body.getApplyPositionBody(
		m_pPlayerChara->m_move.m_posX,
		m_pPlayerChara->m_move.m_posY
	);
	//�G�̒e�͔z��Ȃ̂œG�̒e�̂P�P�ƏՓ˔�������
	for (int i = 0; i <= m_pEnemyBulletCount; i++) {
		//�v�f��NULL�Ȃ��΂�
		if (m_pEnemyBullets[i] == NULL)
			continue;

		//�L���t���O��false�́v�C���X�^���X����΂�
		if (m_pEnemyBullets[i]->m_activeFlag == false)
			continue;

		//�G�̒e�̂P���̏Փ˔�����s���ۂ̈ʒu���擾
		CBody eneBulCollisionBody = m_pEnemyBullets[i]->m_body.getApplyPositionBody(
			m_pEnemyBullets[i]->m_move.m_posX,
			m_pEnemyBullets[i]->m_move.m_posY
		);

		//�Փ˔�����s��
		if (playerCollisionBody.collision(&eneBulCollisionBody) == true && bomCount == 0) {
			//�Փ˂��Ă���

			//�v���C���[�̏Փ˔���̌v�Z���s��
			m_pPlayerChara->hits(&m_pEnemyBullets[i]->m_status);

			//�G�̒e�̗L���t���O��false�ɂ���
			m_pEnemyBullets[i]->m_activeFlag = false;

			//�G�t�F�N�g��\������
			int index = getFreeIndex(m_pEffects, CEfect::MAX_EFFECT);

			//�󂢂Ă���v�f�����݂��Ȃ���΃G�t�F�N�g�̏����͍s��Ȃ�
			if (index != -1) {
				EFFECT_TYPE efect = m_pPlayerChara->m_activeFlag ? EFFECT_TYPE::EXPLOSION : EFFECT_TYPE::EXPLOSION_FINISH;
				//�G�t�F�N�g�C���X�^���X�̍쐬
				CEfect* pEfe = this->launchEffect(
					efect,
					m_pPlayerChara->m_move.m_posX,
					m_pPlayerChara->m_move.m_posY
				);

				//���C���[�ɒ���t����
				m_characterLayer->addChild(pEfe);

				//�z��ɃA�h���X�����t����
				this->m_pEffects[index] = pEfe;
				//�I�u�W�F�N�g�J�E���g�X�V
				if (index >= m_pEfectCount) {
					m_pEfectCount = index;
				}
				//�v���C���[�������ʉ�
				if (se_flg) {
					m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_PLAYER_EXPLOSION);
					AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 120.0f);
				}

			}

			//�v���C���[������Ă����烌�[�U�[�t���O��������
			if (m_pPlayerChara->m_activeFlag == false) {
				laserFlg = false;
			}


		}


	}
}
/**
*@desc �v���C���[�ƓG�̏Փ˔���
*/
void CGameMain::collisionPlayerAndEnemies() {
	//�v���C���[������ł������΂�
	if (m_pPlayerChara->m_activeFlag == false || resurrection)
		return;

	//�v���C���[�̏Փ˔�����s���ۂ̈ʒu���擾
	CBody playerCollisionBody = m_pPlayerChara->m_body.getApplyPositionBody(
		m_pPlayerChara->m_move.m_posX,
		m_pPlayerChara->m_move.m_posY
	);
	//�G�͔z��Ȃ̂œG�̂P�P�ƏՓ˔�������
	for (int i = 0; i <= m_pEnemyCount; i++) {
		//�v�f��NULL�Ȃ��΂�
		if (m_pEnemyCharas[i] == NULL)
			continue;

		//�L���t���O��false�́v�C���X�^���X����΂�
		if (m_pEnemyCharas[i]->m_activeFlag == false)
			continue;

		//�G�̒e�̂P���̏Փ˔�����s���ۂ̈ʒu���擾
		CBody eneCollisionBody = m_pEnemyCharas[i]->m_body.getApplyPositionBody(
			m_pEnemyCharas[i]->m_move.m_posX,
			m_pEnemyCharas[i]->m_move.m_posY
		);

		//�Փ˔�����s��
		if (playerCollisionBody.collision(&eneCollisionBody) == true && resCount == 0 && bomCount == 0) {
			//�Փ˂��Ă���
			//�T�t���[���Ԗ��G
			resCount = 5;
			//�G�̏Փ˔���̌v�Z���s��
			m_pEnemyCharas[i]->hits(&m_pPlayerChara->m_status);

			//�G��|���Ă�����X�R�A�̌v�Z���s��
			if (m_pEnemyCharas[i]->m_activeFlag == false) {
				m_pPlayerChara->m_status.addScore(m_pEnemyCharas[i]->m_status.getScore());

				if (m_pEnemyCharas[i]->e_enemyType == ENEMY_TYPE::TYPE_C) {
					//�A�C�e���h���b�v����
					//�^�C�vC�̏ꍇ�A�C�e���h���b�v����
					//�A�C�e����\������
					int index = getFreeIndex(m_pItems, CItem::MAX_ITEM);

					//�󂢂Ă���v�f�����݂��Ȃ���΃G�t�F�N�g�̏����͍s��Ȃ�
					if (index != -1) {
						//�A�C�e���C���X�^���X�̍쐬

						CItem* pItem = this->launchItem(
							m_pEnemyCharas[i]->m_item,
							m_pEnemyCharas[i]->m_move.m_posX,
							m_pEnemyCharas[i]->m_move.m_posY
						);

						//���C���[�ɒ���t����
						m_characterLayer->addChild(pItem);
						//�z��ɃA�h���X�����t����
						this->m_pItems[index] = pItem;
						//�I�u�W�F�N�g�J�E���g�X�V
						if (index >= m_pItemCount) {
							m_pItemCount = index;
						}

						//�A�C�e�����ʉ�
						if (se_flg) {
							m_pItems[index]->m_bgmid = AudioEngine::play2d(SOUND_FILE_ENEMY_EXPLOSION);
							AudioEngine::setVolume(m_pItems[index]->m_bgmid, SE_VOLUME / 120.0f);
						}

					}
				}
			}

			//�G�t�F�N�g��\������
			int index = getFreeIndex(m_pEffects, CEfect::MAX_EFFECT);

			//�󂢂Ă���v�f�����݂��Ȃ���΃G�t�F�N�g�̏����͍s��Ȃ�
			if (index != -1) {
				//�G�t�F�N�g�C���X�^���X�̍쐬
				CEfect* pEfe = this->launchEffect(
					EFFECT_TYPE::EXPLOSION,
					m_pEnemyCharas[i]->m_move.m_posX,
					m_pEnemyCharas[i]->m_move.m_posY
				);

				//���C���[�ɒ���t����
				m_characterLayer->addChild(pEfe);

				//�z��ɃA�h���X�����t����
				this->m_pEffects[index] = pEfe;
				//�I�u�W�F�N�g�J�E���g�X�V
				if (index >= m_pEfectCount) {
					m_pEfectCount = index;
				}

				//�G�������ʉ�
				if (se_flg) {
					m_pEnemyCharas[i]->m_bgmid = AudioEngine::play2d(SOUND_FILE_ENEMY_EXPLOSION);
					AudioEngine::setVolume(m_pEnemyCharas[i]->m_bgmid, SE_VOLUME / 120.0f);
				}

			}

			//�G�t�F�N�g��\������
			index = getFreeIndex(m_pEffects, CEfect::MAX_EFFECT);

			//�󂢂Ă���v�f�����݂��Ȃ���΃G�t�F�N�g�̏����͍s��Ȃ�
			if (index != -1) {
				//�G�t�F�N�g�C���X�^���X�̍쐬
				CEfect* pEfe = this->launchEffect(
					EFFECT_TYPE::EXPLOSION,
					m_pPlayerChara->m_move.m_posX,
					m_pPlayerChara->m_move.m_posY
				);

				//���C���[�ɒ���t����
				m_characterLayer->addChild(pEfe);

				//�z��ɃA�h���X�����t����
				this->m_pEffects[index] = pEfe;
				//�I�u�W�F�N�g�J�E���g�X�V
				if (index >= m_pEfectCount) {
					m_pEfectCount = index;
				}
				//�v���C���[�������ʉ�
				if (se_flg) {
					m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_PLAYER_EXPLOSION);
					AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 120.0f);
				}

			}


			//�v���C���[�̏Փ˔���̌v�Z���s��
			m_pPlayerChara->hits(&m_pEnemyCharas[i]->m_status);

			//�G�t�F�N�g��\������
			index = getFreeIndex(m_pEffects, CEfect::MAX_EFFECT);

			//�󂢂Ă���v�f�����݂��Ȃ���΃G�t�F�N�g�̏����͍s��Ȃ�
			if (index != -1) {
				EFFECT_TYPE efect = m_pPlayerChara->m_activeFlag ? EFFECT_TYPE::EXPLOSION : EFFECT_TYPE::EXPLOSION_FINISH;
				//�G�t�F�N�g�C���X�^���X�̍쐬
				CEfect* pEfe = this->launchEffect(
					efect,
					m_pPlayerChara->m_move.m_posX,
					m_pPlayerChara->m_move.m_posY
				);

				//���C���[�ɒ���t����
				m_characterLayer->addChild(pEfe);

				//�z��ɃA�h���X�����t����
				this->m_pEffects[index] = pEfe;
				//�I�u�W�F�N�g�J�E���g�X�V
				if (index >= m_pEfectCount) {
					m_pEfectCount = index;
				}
				//�v���C���[�������ʉ�
				if (se_flg) {
					m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_PLAYER_EXPLOSION);
					AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 120.0f);
				}

			}

			//�v���C���[������Ă����烌�[�U�[�t���O��������
			if (m_pPlayerChara->m_activeFlag == false) {
				laserFlg = false;
			}
		}

	}


}

/**
*@desc �G�ƃv���C���[�̒e�̏Փ˔���
*/
void CGameMain::collisionEnemiesAndPlayerBullets() {
	
	for (int i = 0; i <= m_pPlayerBulletCount; i++) {
		//�v�f��NULL�Ȃ��΂�
		if (m_pPlayerBullets[i] == NULL)
			continue;

		//�L���t���O��false�́v�C���X�^���X����΂�
		if (m_pPlayerBullets[i]->m_activeFlag == false)
			continue;

		//�v���C���[�̏Փ˔�����s���ۂ̈ʒu���擾
		CBody playerCollisionBody = m_pPlayerBullets[i]->m_body.getApplyPositionBody(
			m_pPlayerBullets[i]->m_move.m_posX,
			m_pPlayerBullets[i]->m_move.m_posY
		);

		//���[�U�[�p�z��Y�����ۑ��p
		int laser = -1;

		//�G�͔z��Ȃ̂œG�̒e�̂P�P�ƏՓ˔�������
		for (int j = 0; j <= m_pEnemyCount; j++) {
			//�v�f��NULL�Ȃ��΂�
			if (m_pEnemyCharas[j] == NULL)
				continue;

			//�L���t���O��false�́v�C���X�^���X����΂�
			if (m_pEnemyCharas[j]->m_activeFlag == false)
				continue;

			//�G�̂P���̏Փ˔�����s���ۂ̈ʒu���擾
			CBody eneCollisionBody = m_pEnemyCharas[j]->m_body.getApplyPositionBody(
				m_pEnemyCharas[j]->m_move.m_posX,
				m_pEnemyCharas[j]->m_move.m_posY
			);
			//�Փ˔�����s��
			if (playerCollisionBody.collision(&eneCollisionBody) == true) {
				//�Փ˂��Ă���
				//�G�̏Փ˔���̌v�Z���s��
				//m_pEnemyCharas[j]->hits(&m_pPlayerBullets[i]->m_status);

				switch (m_pPlayerBullets[i]->m_bulletType) {
				case BULLET_TYPE::PLAYER_EXPLOSION:
					//�G�̏Փ˔���̌v�Z���s��
					m_pEnemyCharas[j]->hits(&m_pPlayerBullets[i]->m_status);
					//�����^�C�v�؂�ւ�
					m_pPlayerBullets[i]->m_bulletType = BULLET_TYPE::PLAYER_EXPLOSION_2;
					//�摜�̐ݒ�
					m_pPlayerBullets[i]->setTexture(IMAGE_FILE_EXPLOSION_2);
					//�؂����`
					m_pPlayerBullets[i]->m_chip = CChip(0, 0, 120, 120);
					m_pPlayerBullets[i]->setTextureRect(m_pEnemyCharas[j]->m_chip);
					//�X�e�[�^�X�̐ݒ�
					m_pPlayerBullets[i]->m_status.set(1, 1, 1, 0);
					//�ړ��f�[�^�ɏ������x�̐ݒ�@��~���
					m_pPlayerBullets[i]->m_move.setVel(0, 0);
					//�A�j���[�V�����f�[�^�̏�����
					m_pPlayerBullets[i]->m_anime.set(10, 7, false);
					//�Փ˔���p�f�[�^�̏�����
					m_pPlayerBullets[i]->m_body.set(
						-20 * m_pPlayerChara->m_shotParam,
						20 * m_pPlayerChara->m_shotParam,
						20 * m_pPlayerChara->m_shotParam,
						-20 * m_pPlayerChara->m_shotParam
					);
					//�摜�T�C�Y�����x���␳
					m_pPlayerBullets[i]->setScale(0.5f * m_pPlayerChara->m_shotParam);

					//���O���t���O�L��
					m_pPlayerBullets[i]->m_delflg = true;
					//���O���t���[���J�E���g�ݒ�
					m_pPlayerBullets[i]->m_maxCount = 70;
					//�G��|���Ă�����X�R�A�̌v�Z���s��
					calculationScore(j);
					//�G�t�F�N�g��\������
					createEffect(j);

					break;
				case BULLET_TYPE::PLAYER_EXPLOSION_2:
					//�G�̏Փ˔���̌v�Z���s��
					m_pEnemyCharas[j]->hits(&m_pPlayerBullets[i]->m_status);
					//�G��|���Ă�����X�R�A�̌v�Z���s��
					calculationScore(j);
					//�G�t�F�N�g��\������
					if (m_pEnemyCharas[j]->m_activeFlag == false)
						createEffect(j);

					break;
				case BULLET_TYPE::PLAYER_LASER:


					if (laser == -1) {
						//�ŏ��͕K���G�̓Y��������
						laser = j;
					}
					else {
						//��Ԏ��@�ɋ߂��G�ɓY�������㏑��
						if (m_pEnemyCharas[laser]->m_move.m_posX - m_pEnemyCharas[laser]->m_body.m_left >=
							m_pEnemyCharas[j]->m_move.m_posX - m_pEnemyCharas[j]->m_body.m_left) {
							laser = j;
						}

					}
					break;
				default:
					//�G�̏Փ˔���̌v�Z���s��
					m_pEnemyCharas[j]->hits(&m_pPlayerBullets[i]->m_status);

					//�ʏ�e�A�o�b�N�e�A�U�e�A�U���e�͏���
					//�v���C���[�̒e�̗L���t���O��false�ɂ���
					m_pPlayerBullets[i]->m_activeFlag = false;
					//�G��|���Ă�����X�R�A�̌v�Z���s��
					calculationScore(j);
					//�G�t�F�N�g��\������
					createEffect(j);
					break;
				}


			}

		}
		//���[�U�[�̏ꍇ�����Ōv�Z
		//�ǔ���p�ɕۑ�����
		laserIndex = laser;
		if (m_pPlayerBullets[i]->m_bulletType == BULLET_TYPE::PLAYER_LASER) {

			if (laserFlg == false) {
				//���[�U�[�̗L���t���O��false�ɂ���
				m_pPlayerBullets[i]->m_activeFlag = false;
				cocos2d::log("laser off");
				continue;
			}

			//���[�U�[�̒����ύX �f�t�H���g640
			m_pPlayerBullets[i]->m_chip.size.width = 640;

			
		}
	}
	//�{������
	if (bomCount != 0) {
		if (bomCount <= 100 && bomCount % 10 == 0) {
			//�{���p�̃X�e�[�^�X
			CStatus m_status;
			m_status.set(0, 0, 10, 0);

			//�G�͔z��Ȃ̂œG�̒e�̂P�P�ƏՓ˔�������
			for (int j = 0; j <= m_pEnemyCount; j++) {
				//�v�f��NULL�Ȃ��΂�
				if (m_pEnemyCharas[j] == NULL)
					continue;

				//�L���t���O��false�́v�C���X�^���X����΂�
				if (m_pEnemyCharas[j]->m_activeFlag == false)
					continue;

				//�G�̏Փ˔���̌v�Z���s��
				m_pEnemyCharas[j]->hits(&m_status);

				//�G��|���Ă�����X�R�A�̌v�Z���s��
				calculationScore(j);
				//�G�t�F�N�g��\������
				createEffect(j);
			}
		}
	}

}

void CGameMain::calculationScore(int j) {
	//�G��|���Ă�����X�R�A�̌v�Z���s��
	if (m_pEnemyCharas[j]->m_activeFlag == false) {
		m_pPlayerChara->m_status.addScore(m_pEnemyCharas[j]->m_status.getScore());
		//�{�X�Ȃ�J�E���g�𑝂₷
		if (m_pEnemyCharas[j]->bossflg) {
			m_pEnemyCharas[j]->bossCount = 300;
		}
		
		if (m_pEnemyCharas[j]->m_item != ITEM_TYPE::NONE) {
			//�A�C�e�������ȊO�̏ꍇ
			//�A�C�e����\������
			int index = getFreeIndex(m_pItems, CItem::MAX_ITEM);

			//�󂢂Ă���v�f�����݂��Ȃ���΃G�t�F�N�g�̏����͍s��Ȃ�
			if (index != -1) {
				//�A�C�e���C���X�^���X�̍쐬

				CItem* pItem = this->launchItem(
					m_pEnemyCharas[j]->m_item,
					m_pEnemyCharas[j]->m_move.m_posX,
					m_pEnemyCharas[j]->m_move.m_posY
				);

				//���C���[�ɒ���t����
				m_characterLayer->addChild(pItem);
				//�z��ɃA�h���X�����t����
				this->m_pItems[index] = pItem;
				//�I�u�W�F�N�g�J�E���g�X�V
				if (index >= m_pItemCount) {
					m_pItemCount = index;
				}

				
			}
		}


	}

}

void CGameMain::createEffect(int j) {
	//�G�t�F�N�g��\������
	int index = getFreeIndex(m_pEffects, CEfect::MAX_EFFECT);
	//�󂢂Ă���v�f�����݂��Ȃ���΃G�t�F�N�g�̏����͍s��Ȃ�
	if (index != -1) {
		EFFECT_TYPE type;
		if (m_pEnemyCharas[j]->m_activeFlag == true) {
			//�G�������ʉ�
			if (!soundDeray) {
				soundDeray = 20;
				if (se_flg) {
					m_pEnemyCharas[j]->m_bgmid = AudioEngine::play2d(SOUND_FILE_ENEMY_EXPLOSION);
					AudioEngine::setVolume(m_pEnemyCharas[j]->m_bgmid, SE_VOLUME / 120.0f);
				}

			}
			type = EFFECT_TYPE::EXPLOSION;
		}
		else {
			if (se_flg) {
				m_pEnemyCharas[j]->m_bgmid = AudioEngine::play2d(SOUND_FILE_ENEMY_EXPLOSION_FINISH);
				AudioEngine::setVolume(m_pEnemyCharas[j]->m_bgmid, SE_VOLUME / 120.0f);
			}

			type = EFFECT_TYPE::EXPLOSION_FINISH;
		}

		//�G�t�F�N�g�C���X�^���X�̍쐬
		CEfect* pEfe = this->launchEffect(
			type,
			m_pEnemyCharas[j]->m_move.m_posX,
			m_pEnemyCharas[j]->m_move.m_posY
		);

		//���C���[�ɒ���t����
		m_characterLayer->addChild(pEfe);

		//�z��ɃA�h���X�����t����
		this->m_pEffects[index] = pEfe;
		//�I�u�W�F�N�g�J�E���g�X�V
		if (index >= m_pEfectCount) {
			m_pEfectCount = index;
		}
	}
}

void CGameMain::createEffect2(int j, float x, float y) {
	//�G�t�F�N�g��\������
	int index = getFreeIndex(m_pEffects, CEfect::MAX_EFFECT);
	//�󂢂Ă���v�f�����݂��Ȃ���΃G�t�F�N�g�̏����͍s��Ȃ�
	if (index != -1) {
		EFFECT_TYPE type;
		if (!soundDeray) {
			soundDeray = 20;
			//�G�������ʉ�
			if (se_flg) {
				m_pWalls[j]->m_bgmid = AudioEngine::play2d(SOUND_FILE_ENEMY_EXPLOSION);
				AudioEngine::setVolume(m_pWalls[j]->m_bgmid, SE_VOLUME / 120.0f);
			}

		}
		type = EFFECT_TYPE::EXPLOSION;
		//�G�t�F�N�g�C���X�^���X�̍쐬
		CEfect* pEfe = this->launchEffect(
			type,
			x,
			y
		);

		//���C���[�ɒ���t����
		m_characterLayer->addChild(pEfe);

		//�z��ɃA�h���X�����t����
		this->m_pEffects[index] = pEfe;
		//�I�u�W�F�N�g�J�E���g�X�V
		if (index >= m_pEfectCount) {
			m_pEfectCount = index;
		}
	}
}

/*
*@desc �G���o�������邩�ǂ����̃`�F�b�N

*/
void CGameMain::checkLaunchEnemy() {
	//�Q�Ƃ���G�o���f�[�^�̔ԍ����o���ő吔�ȏ�ɂȂ�����o��������s��Ȃ�

	if (this->m_enemyLaunchIndex >= (int)MapData::m_pEnemyLaunchData.size()) {
		return;
	}

	//�G�����J�E���g
	int enemycount = 0;

	while (this->m_frameCounter == MapData::m_pEnemyLaunchData[this->m_enemyLaunchIndex].m_frame) {
		//�z���NULL�������Ă���Y�����ԍ����擾
		int index = getFreeIndex(m_pEnemyCharas, CEnemyCharacter::MAX_ENEMY);

		//�󂢂Ă���v�f�����݂��Ȃ���ΓG�̏o�������͍s��Ȃ�
		if (index != -1) {

			CEnemyCharacter* pEne = this->launchEnemy(
				&MapData::m_pEnemyLaunchData[this->m_enemyLaunchIndex]
			);
			
			//���C���[�ɒ���t����
			m_characterLayer->addChild(pEne);
			
			//�z��ɃA�h���X�����t����
			this->m_pEnemyCharas[index] = pEne;
			//�I�u�W�F�N�g�J�E���g�X�V
			if (index >= m_pEnemyCount) {
				m_pEnemyCount = index;
			}
			if (pEne->e_enemyType == ENEMY_TYPE::TYPE_D && 
				enemycount != (int)(this->m_frameCounter / 10) % 5) {
				pEne->m_item = ITEM_TYPE::NONE;
			}
			if (pEne->e_enemyType == ENEMY_TYPE::TYPE_D && enemycount != 5) {
				//�G��A���Ŕz�u
				
				if (enemycount != 0) {
					CEnemyAction action;
					action.x = 0;
					action.y = 0;
					action.frame = 10 * enemycount;
					pEne->action.insert(pEne->action.begin(), action);
					pEne->m_move.setVel(-WALL_SPEED, 0);
					pEne->shotCount -= 10 * enemycount;
					
				}


				enemycount++;
			}
			else {
				//�o�����s���Ă�����Q�Ƃ��Ă���o���f�[�^�̔ԍ������̏o���f�[�^�ɕύX����
				this->m_enemyLaunchIndex++;
				enemycount = 0;
			}

			if (this->m_enemyLaunchIndex >= (int)MapData::m_pEnemyLaunchData.size()) {
				return;
			}
		}

	}
}

void CGameMain::checkEnemyAleart() {
	//�Q�Ƃ���G�o���f�[�^�̔ԍ����o���ő吔�ȏ�ɂȂ�����o��������s��Ȃ�

	if (this->m_enemyAleartIndex >= (int)MapData::m_pEnemyLaunchData.size()) {
		return;
	}
	while (this->m_frameCounter + 60 == MapData::m_pEnemyLaunchData[this->m_enemyAleartIndex].m_frame) {
		//�z���NULL�������Ă���Y�����ԍ����擾
		int index = getFreeIndex(m_pEffects, CEfect::MAX_EFFECT);

		//�󂢂Ă���v�f�����݂��Ȃ���΃G�t�F�N�g�����͍s��Ȃ�
		if (index != -1) {
			CEfect* pEfect = launchEffect(EFFECT_TYPE::ALEART,
				(float)MapData::m_pEnemyLaunchData[this->m_enemyAleartIndex].m_posX + 40,
				(float)MapData::m_pEnemyLaunchData[this->m_enemyAleartIndex].m_posY);

			//���C���[�ɒ���t����
			m_characterLayer->addChild(pEfect);

			//�z��ɃA�h���X�����t����
			this->m_pEffects[index] = pEfect;
			//�I�u�W�F�N�g�J�E���g�X�V
			if (index >= m_pEfectCount) {
				m_pEfectCount = index;
			}

			//�o�����s���Ă�����Q�Ƃ��Ă���o���f�[�^�̔ԍ������̏o���f�[�^�ɕύX����
			this->m_enemyAleartIndex++;

			if (this->m_enemyAleartIndex >= (int)MapData::m_pEnemyLaunchData.size()) {
				return;
			}
		}

	}
}


//�G�t�F�N�g�̏o��
/**
*@desc �G�t�F�N�g�̏o��
*@param �G�t�F�N�g�^�C�v
*@param �o���ʒuX
*@param �o���ʒuY
*@return �G�t�F�N�g�N���X�̃|�C���^
*/
CEfect* CGameMain::launchEffect(EFFECT_TYPE type, float posX, float posY) {
	//�G�t�F�N�g�̐���
	CEfect* pEfe = CEfect::create();

	switch (type) {
	case EFFECT_TYPE::EXPLOSION:
		//�摜�̐ݒ�
		pEfe->setTexture(IMAGE_FILE_EXPLOSION);
		//�؂����`
		pEfe->m_chip = CChip(0, 0, 48, 48);
		//�A�j���[�V�����f�[�^�̏�����
		pEfe->m_anime.set(5, 8, false);
		break;
	case EFFECT_TYPE::EXPLOSION_FINISH:
		//�摜�̐ݒ�
		pEfe->setTexture(IMAGE_FILE_EXPLOSION_FINISH);
		//�؂����`
		pEfe->m_chip = CChip(0, 0, 120, 120);
		//�A�j���[�V�����f�[�^�̏�����
		pEfe->m_anime.set(5, 5, false);
		break;
	case EFFECT_TYPE::BOM:
		//�摜�̐ݒ�
		pEfe->setTexture(IMAGE_FILE_BOM);
		//�؂����`
		pEfe->m_chip = CChip(0, 0, 640, 480);
		//�A�j���[�V�����f�[�^�̏�����
		pEfe->m_anime.set(5, 24, false);
		pEfe->maxX = 3;

		break;
	case EFFECT_TYPE::ALEART:
		//�摜�̐ݒ�
		pEfe->setTexture(IMAGE_FILE_ALEART);
		//�؂����`
		pEfe->m_chip = CChip(0, 0, 40, 40);
		//�A�j���[�V�����f�[�^�̏�����
		pEfe->m_anime.set(10, 6, false);
		break;
	case EFFECT_TYPE::PLANET1:
		//�摜�̐ݒ�
		pEfe->setTexture(IMAGE_FILE_PLANET_1);
		//�؂����`
		pEfe->m_chip = CChip(0, 0, 171, 171);
		//�A�j���[�V�����f�[�^�̏�����
		pEfe->m_anime.set(60, 1, true);
		break;
	case EFFECT_TYPE::PLANET2:
		//�摜�̐ݒ�
		pEfe->setTexture(IMAGE_FILE_PLANET_2);
		//�؂����`
		pEfe->m_chip = CChip(0, 0, 233, 135);
		//�A�j���[�V�����f�[�^�̏�����
		pEfe->m_anime.set(60, 1, true);
		break;
	case EFFECT_TYPE::PLANET3:
		//�摜�̐ݒ�
		pEfe->setTexture(IMAGE_FILE_PLANET_3);
		//�؂����`
		pEfe->m_chip = CChip(0, 0, 281, 162);
		//�A�j���[�V�����f�[�^�̏�����
		pEfe->m_anime.set(60, 1, true);
		break;
	case EFFECT_TYPE::PLANET4:
		//�摜�̐ݒ�
		pEfe->setTexture(IMAGE_FILE_PLANET_4);
		//�؂����`
		pEfe->m_chip = CChip(0, 0, 142, 136);
		//�A�j���[�V�����f�[�^�̏�����
		pEfe->m_anime.set(60, 1, true);
		break;
	case EFFECT_TYPE::PLANET5:
		//�摜�̐ݒ�
		pEfe->setTexture(IMAGE_FILE_PLANET_5);
		//�؂����`
		pEfe->m_chip = CChip(0, 0, 285, 164);
		//�A�j���[�V�����f�[�^�̏�����
		pEfe->m_anime.set(60, 1, true);
		break;
	case EFFECT_TYPE::PLANET6:
		//�摜�̐ݒ�
		pEfe->setTexture(IMAGE_FILE_PLANET_6);
		//�؂����`
		pEfe->m_chip = CChip(0, 0, 236, 235);
		//�A�j���[�V�����f�[�^�̏�����
		pEfe->m_anime.set(60, 1, true);
		break;
	case EFFECT_TYPE::PLANET7:
		//�摜�̐ݒ�
		pEfe->setTexture(IMAGE_FILE_PLANET_7);
		//�؂����`
		pEfe->m_chip = CChip(0, 0, 203, 203);
		//�A�j���[�V�����f�[�^�̏�����
		pEfe->m_anime.set(60, 1, true);
		break;
	case EFFECT_TYPE::PLANET8:
		//�摜�̐ݒ�
		pEfe->setTexture(IMAGE_FILE_PLANET_8);
		//�؂����`
		pEfe->m_chip = CChip(0, 0, 172, 172);
		//�A�j���[�V�����f�[�^�̏�����
		pEfe->m_anime.set(60, 1, true);
		break;
	case EFFECT_TYPE::PLANET9:
		//�摜�̐ݒ�
		pEfe->setTexture(IMAGE_FILE_PLANET_9);
		//�؂����`
		pEfe->m_chip = CChip(0, 0, 232, 217);
		//�A�j���[�V�����f�[�^�̏�����
		pEfe->m_anime.set(60, 1, true);
		break;
	default:
		break;
	}
	//�e�^�C�v�̐ݒ�
	pEfe->type = type;

	pEfe->setTextureRect(pEfe->m_chip);
	//�ړ��f�[�^�ɏ����ʒu�̐ݒ�
	pEfe->m_move.setPos(posX, posY);
	//�ړ��f�[�^�ɏ������x�̐ݒ�G
	pEfe->m_move.setVel(0, 0);

	//�����ʒu�𔻒�
	pEfe->setPosition(pEfe->m_move.m_posX, pEfe->m_move.m_posY);

	//�L���t���O��true������
	pEfe->m_activeFlag = true;



	return pEfe;
}

/**
*@desc �A�C�e���̏o��
*@param �A�C�e���^�C�v
*@param �o���ʒuX
*@param �o���ʒuY
*@return �A�C�e���N���X�̃|�C���^
*/
CItem* CGameMain::launchItem(ITEM_TYPE type, float posX, float posY) {
	//�A�C�e���̐���
	CItem* pItem = CItem::create();
	//�摜�̐ݒ�
	pItem->setTexture(IMAGE_FILE_ITEM);
	//�؂����`
	switch (type) {
	case ITEM_TYPE::SPEEDUP:
		pItem->m_chip = CChip(0, 0, 40, 40);
		break;
	case ITEM_TYPE::RECOVERY:
		pItem->m_chip = CChip(0, 40, 40, 40);
		break;
	case ITEM_TYPE::NORMAL:
		pItem->m_chip = CChip(0, 80, 40, 40);
		break;
	case ITEM_TYPE::EXPLOSION:
		pItem->m_chip = CChip(0, 120, 40, 40);
		break;
	case ITEM_TYPE::BACK:
		pItem->m_chip = CChip(0, 160, 40, 40);
		break;
	case ITEM_TYPE::LASER:
		pItem->m_chip = CChip(0, 200, 40, 40);
		break;
	case ITEM_TYPE::INDUCTION:
		pItem->m_chip = CChip(0, 240, 40, 40);
		break;
	case ITEM_TYPE::MULTIPLE:
		pItem->m_chip = CChip(0, 280, 40, 40);
		break;
	case ITEM_TYPE::BOM:
		pItem->m_chip = CChip(0, 320, 40, 40);
		break;
	case ITEM_TYPE::ONE_UP:
		pItem->m_chip = CChip(0, 360, 40, 40);
		break;
	default:
		pItem->m_chip = CChip(0, 0, 40, 40);
		break;
	}
	
	pItem->setTextureRect(pItem->m_chip);
	//�ړ��f�[�^�ɏ����ʒu�̐ݒ�
	pItem->m_move.setPos(posX, posY);
	//�ړ��f�[�^�ɏ������x�̐ݒ�G
	pItem->m_move.setVel(-WALL_SPEED, 0);
	//�����蔻��ݒ�
	pItem->m_body.set(-20, 20, 20, -20);
	//�A�j���[�V�����f�[�^�̏�����
	pItem->m_anime.set(5, 6, true);

	//�����ʒu�𔻒�
	pItem->setPosition(pItem->m_move.m_posX, pItem->m_move.m_posY);

	//�L���t���O��true������
	pItem->m_activeFlag = true;

	//�A�C�e���^�C�v�̐ݒ�
	pItem->type = type;

	return pItem;
}

/**
*@desc �ǂ̏o��
*@param �ǃ^�C�v
*@param �o���ʒuX
*@param �o���ʒuY
*@return �ǃN���X�̃|�C���^
*/
CWall* CGameMain::launchWall(WALL_TYPE type, float posX, float posY) {
	//�ǂ̐���
	CWall* pWall = CWall::create();
	//�摜�̐ݒ�
	switch (type) {
	case WALL_TYPE::STAGE_1_1:
		pWall->setTexture(IMAGE_FILE_WALL);
		break;
	case WALL_TYPE::STAGE_1_2:
		pWall->setTexture(IMAGE_FILE_WALL_2);
		break;
	case WALL_TYPE::STAGE_2_1:
		pWall->setTexture(IMAGE_FILE_WALL_3);
		break;
	case WALL_TYPE::STAGE_2_2:
		pWall->setTexture(IMAGE_FILE_WALL_4);
		break;
	case WALL_TYPE::STAGE_3_1:
		pWall->setTexture(IMAGE_FILE_WALL_5);
		break;
	case WALL_TYPE::STAGE_3_2:
		pWall->setTexture(IMAGE_FILE_WALL_6);
		break;
	}

	//�؂����`
	pWall->m_chip = CChip(0, 0, 40, 40);
	

	pWall->setTextureRect(pWall->m_chip);
	//�ړ��f�[�^�ɏ����ʒu�̐ݒ�
	pWall->m_move.setPos(posX, posY);
	//�ړ��f�[�^�ɏ������x�̐ݒ�G
	pWall->m_move.setVel(-MapData::WALL_SPEED, 0);
	//�����蔻��ݒ�
	pWall->m_body.set(-20, 20, 20, -20);
	//�A�j���[�V�����f�[�^�̏�����
	pWall->m_anime.set(1, 1, false);
	//�X�e�[�^�X�̐ݒ�
	pWall->m_status.set(1, 1, 1, 0);
	//�����ʒu�𔻒�
	pWall->setPosition(pWall->m_move.m_posX, pWall->m_move.m_posY);

	//�L���t���O��true������
	pWall->m_activeFlag = true;

	//�A�C�e���^�C�v�̐ݒ�
	pWall->type = type;

	return pWall;
}

/*
*@desc �ǂ��o�������邩�ǂ����̃`�F�b�N
*/
void CGameMain::checkLaunchWall() {
	//�}�b�v�̒[�Ȃ��΂�
	if (m_pWallXpos == 100) {
		return;
	}
	if ((int)this->m_wallCounter / 40 == m_pWallXpos) {
		//�[�����擾�擾
		//�ǂ̏o���ʒu�␳
		float wallRemainder = m_wallCounter - ((int)m_wallCounter / 40 * 40);
		//�}�b�v�f�[�^����Ǐ��𒲂ׂ�
		for (int i = 1; i < 13; i++) {
			if (MapData::m_pMapData[m_pWallXpos][i].m_mapChipPatern >= 1) {
				//�ǂ�z�u
				//�z���NULL�������Ă���Y�����ԍ����擾
				int index = getFreeIndex(m_pWalls, CWall::MAX_WALL);
				//�󂢂Ă���v�f�����݂��Ȃ���Εǂ̏o�������͍s��Ȃ�
				if (index != -1) {
					float xPos = 660 - wallRemainder;
					float yPos = 20 + (i - 1) * 40;
					CWall* pWall = this->launchWall(
						(WALL_TYPE)(MapData::m_pMapData[m_pWallXpos][i].m_mapChipPatern - 1),
						xPos,
						yPos
					);
					//�ǂ̉����쐬
					char* img;
					switch (CGameMain::m_stageNo) {
					case 1:
						img = IMAGE_FILE_WALL_BORDER_1;
						break;
					case 2:
						img = IMAGE_FILE_WALL_BORDER_2;
						break;
					case 3:
						img = IMAGE_FILE_WALL_BORDER_3;
						break;
					}
					//��
					if (m_pWallXpos == 0 || !MapData::m_pMapData[m_pWallXpos - 1][i].m_mapChipPatern) {
						pWall->m_pWall_left = Sprite::create();
						pWall->m_pWall_left->setTexture(img);

						pWall->m_pWall_left->setTextureRect(CChip(0, 8 * (rand() % 3), 48, 8));
						pWall->m_pWall_left->setRotation(90);
						pWall->m_pWall_left->setPosition(0.0f, 20.0f);
						pWall->addChild(pWall->m_pWall_left);
					}
					
					//�E
					if (m_pWallXpos == MapData::MAX_MAP_DATA_X - 1 || !MapData::m_pMapData[m_pWallXpos + 1][i].m_mapChipPatern) {
						pWall->m_pWall_right = Sprite::create();
						pWall->m_pWall_right->setTexture(img);

						pWall->m_pWall_right->setTextureRect(CChip(0, 8 * (rand() % 3), 48, 8));
						pWall->m_pWall_right->setRotation(270);
						pWall->m_pWall_right->setPosition(40.0f, 20.0f);
						pWall->addChild(pWall->m_pWall_right);
					}
					
					//��
					if (i != MapData::MAX_MAP_DATA_Y - 2 && !MapData::m_pMapData[m_pWallXpos][i + 1].m_mapChipPatern) {
						pWall->m_pWall_top = Sprite::create();
						pWall->m_pWall_top->setTexture(img);

						pWall->m_pWall_top->setTextureRect(CChip(0, 8 * (rand() % 3), 48, 8));
						pWall->m_pWall_top->setRotation(0);
						pWall->m_pWall_top->setPosition(20.0f, 40.0f);
						pWall->addChild(pWall->m_pWall_top);
					}
					
					//��
					if (i != 1 && !MapData::m_pMapData[m_pWallXpos][i - 1].m_mapChipPatern) {
						pWall->m_pWall_bottom = Sprite::create();
						pWall->m_pWall_bottom->setTexture(img);

						pWall->m_pWall_bottom->setTextureRect(CChip(0, 8 * (rand() % 3), 48, 8));
						pWall->m_pWall_bottom->setRotation(180);
						pWall->m_pWall_bottom->setPosition(20.0f, 0.0f);
						pWall->addChild(pWall->m_pWall_bottom);
					}
					

					//���C���[�ɒ���t����
					m_wallLayer->addChild(pWall);

					//�z��ɃA�h���X�����t����
					this->m_pWalls[index] = pWall;
					//�I�u�W�F�N�g�J�E���g�X�V
					if (index >= m_pWallCount) {
						m_pWallCount = index;
					}
				}
			}
		}
		
		//����x�|�W�V�����ɂ���
		m_pWallXpos++;



	}

}

/*
*@desc �ǂ��o�������邩�ǂ����̃`�F�b�N
*/
void CGameMain::checkLaunchPlanet() {
	//�}�b�v�̒[�Ȃ��΂�
	if (m_planetFrame > 0) {
		m_planetFrame--;
		return;
	}
	m_planetFrame = rand() % 300;
	//�G�t�F�N�g��\������
	int index = getFreeIndex(m_pEffects, CEfect::MAX_EFFECT);

	//�󂢂Ă���v�f�����݂��Ȃ���΃G�t�F�N�g�̏����͍s��Ȃ�
	if (index != -1) {
		bool dir = (bool)(rand() % 2);
		float x = dir ? -190.0f : 830.0f;
		float y = rand() % 480;
		float vel_x = (dir ? 1 : -1) * ((float)(rand() % 200 / 100.0) + 1.0f);
		float vel_y = (y < 240 ? 1 : -1) * (float)(rand() % 100 / 100.0);
		//�G�t�F�N�g�C���X�^���X�̍쐬
		CEfect* pEfe = this->launchEffect(
			(EFFECT_TYPE)(rand() % 9 + 4),
			x,
			y
		);

		//�T�C�Y�ύX
		pEfe->setScale((float)((rand() % 100 + 20) / 100.0f));
		
		pEfe->m_move.setVel(vel_x, vel_y);
		//���C���[�ɒ���t����
		m_backGroundLayer->addChild(pEfe);

		//�z��ɃA�h���X�����t����
		this->m_pEffects[index] = pEfe;
		//�I�u�W�F�N�g�J�E���g�X�V
		if (index >= m_pEfectCount) {
			m_pEfectCount = index;
		}

	}


}

/**
*@desc �s���Ǘ��֐�
*/
void CGameMain::actionFunc() {
	for (int i = 0; i <= m_pEnemyCount; i++) {
		//NULL�`�F�b�N
		if (m_pEnemyCharas[i] == NULL) {
			continue;
		}
		//�L���t���O�`�F�b�N
		if (m_pEnemyCharas[i]->m_activeFlag == false) {
			continue;
		}

		switch (m_pEnemyCharas[i]->m_actionType) {
		case ACTION_TYPE::ZIGZAG:
			//�W�O�U�O�̍s�����s��
			m_actCtrlZigZag.actionFunc(m_pEnemyCharas[i]);
			break;
		case ACTION_TYPE::STRAIGHT:
			//�W�O�U�O�̍s�����s��
			m_actCtrlStraight.actionFunc(m_pEnemyCharas[i]);
			break;
		case ACTION_TYPE::CONVEX:
			//�ʍs�����s��
			m_actCtrlConvex.actionFunc(m_pEnemyCharas[i]);
			break;
		case ACTION_TYPE::ORIGINAL:
			//�I���W�i���s�����s��
			m_actCtrlOriginal.actionFunc(m_pEnemyCharas[i]);
			break;
		case ACTION_TYPE::ORIGINAL2:
			//�I���W�i���s�����s��
			m_actCtrlOriginal2.actionFunc(m_pEnemyCharas[i]);
			break;
		case ACTION_TYPE::BOSS_1:
			//�{�X�s�����s��
			m_actCtrlBoss.actionFunc(m_pEnemyCharas[i]);
			break;
		default:
			break;
		}

	}
}

/**
*@desc �v���C���[�ƃA�C�e���̏Փ˔���
*/
void CGameMain::collisionPlayerAndItems() {
	//�v���C���[������ł������΂�
	if (m_pPlayerChara->m_activeFlag == false)
		return;

	//�v���C���[�̏Փ˔�����s���ۂ̈ʒu���擾
	CBody playerCollisionBody = m_pPlayerChara->m_body.getApplyPositionBody(
		m_pPlayerChara->m_move.m_posX,
		m_pPlayerChara->m_move.m_posY
	);
	//�A�C�e���͔z��Ȃ̂œG�̂P�P�ƏՓ˔�������
	for (int i = 0; i <= m_pItemCount; i++) {
		//�v�f��NULL�Ȃ��΂�
		if (m_pItems[i] == NULL)
			continue;

		//�L���t���O��false�́v�C���X�^���X����΂�
		if (m_pItems[i]->m_activeFlag == false)
			continue;

		//�A�C�e���̂P���̏Փ˔�����s���ۂ̈ʒu���擾
		CBody itemCollisionBody = m_pItems[i]->m_body.getApplyPositionBody(
			m_pItems[i]->m_move.m_posX,
			m_pItems[i]->m_move.m_posY
		);

		//�Փ˔�����s��
		if (playerCollisionBody.collision(&itemCollisionBody) == true) {
			//�Փ˂��Ă���
			m_pItems[i]->hits(&m_pPlayerChara->m_status);

			//�U���͐ݒ�
			m_pPlayerChara->m_shotPower = this->pweponPower[weponSelect][pweponLevel[weponSelect]];
			//�U���Ԋu�ݒ�
			m_pPlayerChara->m_shotInterval = this->pweponInterval[weponSelect][pweponLevel[weponSelect]];
			//�U���p�����[�^�ݒ�
			m_pPlayerChara->m_shotParam = this->pweponParam[weponSelect][pweponLevel[weponSelect]];
			//�U���ړ��ʐݒ�
			m_pPlayerChara->m_shotVel = this->pweponVel[weponSelect][pweponLevel[weponSelect]];

			//�L���t���O��false
			m_pItems[i]->m_activeFlag = false;

			//�A�C�e�����ʉ�
			if (se_flg) {
				switch (m_pItems[i]->type) {
				case ITEM_TYPE::SPEEDUP:
					m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_ITEM_SPEED_UP);
					AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 100.0f);
					break;
				case ITEM_TYPE::RECOVERY:
					m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_ITEM_RECEVERY);
					AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 100.0f);
					break;
				case ITEM_TYPE::NORMAL:
					m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_ITEM_NORMAL);
					AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 100.0f);
					break;
				case ITEM_TYPE::BACK:
					m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_ITEM_BACK);
					AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 100.0f);
					break;
				case ITEM_TYPE::EXPLOSION:
					m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_ITEM_EXPLOSION);
					AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 100.0f);
					break;
				case ITEM_TYPE::LASER:
					m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_ITEM_LASER);
					AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 100.0f);
					break;
				case ITEM_TYPE::INDUCTION:
					m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_ITEM_INDUCTION);
					AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 100.0f);
					break;
				case ITEM_TYPE::MULTIPLE:
					m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_ITEM_MULTIPLE);
					AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 100.0f);
					break;
				case ITEM_TYPE::BOM:
					m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_ITEM_BOM);
					AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 100.0f);
					break;
				case ITEM_TYPE::ONE_UP:
					m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_ITEM_ONE_UP);
					AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 100.0f);
					break;
				default:
					break;
				}
				//�A�C�e���擾�ʉ�
				m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_ITEM_GET);
				AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 100.0f);
			}


		}

	}


}

/**
*@desc �v���C���[�ƕǂ̏Փ˔���
*/
void CGameMain::collisionPlayerAndWalls() {
	//�v���C���[������ł������΂�
	if (m_pPlayerChara->m_activeFlag == false || resurrection)
		return;


	//�ǂ͔z��Ȃ̂œG�̂P�P�ƏՓ˔�������
	for (int i = 0; i <= m_pWallCount; i++) {

		//�v�f��NULL�Ȃ��΂�
		if (m_pWalls[i] == NULL)
			continue;

		//�L���t���O��false�́v�C���X�^���X����΂�
		if (m_pWalls[i]->m_activeFlag == false)
			continue;

		//�v���C���[�̏Փ˔�����s���ۂ̈ʒu���擾
		CBody playerCollisionBody = m_pPlayerChara->m_body.getApplyPositionBody(
			m_pPlayerChara->m_move.m_posX,
			m_pPlayerChara->m_move.m_posY
		);

		//�A�C�e���̂P���̏Փ˔�����s���ۂ̈ʒu���擾
		CBody wallCollisionBody = m_pWalls[i]->m_body.getApplyPositionBody(
			m_pWalls[i]->m_move.m_posX,
			m_pWalls[i]->m_move.m_posY
		);

		//�Փ˔�����s��

		if (playerCollisionBody.collision(&wallCollisionBody) == true) {
			//�ǈړ��L�����N�^�[���W�␳
			if (colDir) {
				//������D��
				if (m_pPlayerChara->m_body.getApplyPositionBody(
					m_pPlayerChara->m_move.m_posX - WALL_SPEED - m_pPlayerChara->m_move.m_velX,
					m_pPlayerChara->m_move.m_posY
				).collision(&wallCollisionBody) == false) {
					m_pPlayerChara->m_move.m_posX -= m_pPlayerChara->m_move.m_velX + WALL_SPEED;

					colDir = true;
				}
				else if (m_pPlayerChara->m_body.getApplyPositionBody(
					m_pPlayerChara->m_move.m_posX,
					m_pPlayerChara->m_move.m_posY - m_pPlayerChara->m_move.m_velY
				).collision(&wallCollisionBody) == false) {
					m_pPlayerChara->m_move.m_posY -= m_pPlayerChara->m_move.m_velY;

					colDir = false;
				}
				else if (m_pPlayerChara->m_body.getApplyPositionBody(
					m_pPlayerChara->m_move.m_posX - WALL_SPEED - m_pPlayerChara->m_move.m_velX,
					m_pPlayerChara->m_move.m_posY - m_pPlayerChara->m_move.m_velY
				).collision(&wallCollisionBody) == false) {
					m_pPlayerChara->m_move.m_posX -= m_pPlayerChara->m_move.m_velX + WALL_SPEED;
					m_pPlayerChara->m_move.m_posY -= m_pPlayerChara->m_move.m_velY;

				}
			}
			else {
				//�c����D��
				if (m_pPlayerChara->m_body.getApplyPositionBody(
					m_pPlayerChara->m_move.m_posX,
					m_pPlayerChara->m_move.m_posY - m_pPlayerChara->m_move.m_velY
				).collision(&wallCollisionBody) == false) {
					m_pPlayerChara->m_move.m_posY -= m_pPlayerChara->m_move.m_velY;

					colDir = false;
				}
				else if (m_pPlayerChara->m_body.getApplyPositionBody(
					m_pPlayerChara->m_move.m_posX - WALL_SPEED - m_pPlayerChara->m_move.m_velX,
					m_pPlayerChara->m_move.m_posY
				).collision(&wallCollisionBody) == false) {
					m_pPlayerChara->m_move.m_posX -= m_pPlayerChara->m_move.m_velX + WALL_SPEED;

					colDir = true;
				}
				else if (m_pPlayerChara->m_body.getApplyPositionBody(
					m_pPlayerChara->m_move.m_posX - WALL_SPEED - m_pPlayerChara->m_move.m_velX,
					m_pPlayerChara->m_move.m_posY - m_pPlayerChara->m_move.m_velY
				).collision(&wallCollisionBody) == false) {
					m_pPlayerChara->m_move.m_posX -= m_pPlayerChara->m_move.m_velX + WALL_SPEED;
					m_pPlayerChara->m_move.m_posY -= m_pPlayerChara->m_move.m_velY;

				}
			}



			//���[�͂ݏo���m�F �ǂ߂荞�݊m�F
			if (m_pPlayerChara->m_move.m_posX - m_pPlayerChara->m_body.m_left < WINDOW_LEFT ||
				m_pPlayerChara->m_body.getApplyPositionBody(
					m_pPlayerChara->m_move.m_posX,
					m_pPlayerChara->m_move.m_posY
				).collision(&wallCollisionBody) == true
				) {
				//�͂ݏo������A�N�e�B�u������
				m_pPlayerChara->m_activeFlag = false;
				//�G�t�F�N�g��\������
				int index = getFreeIndex(m_pEffects, CEfect::MAX_EFFECT);

				//�󂢂Ă���v�f�����݂��Ȃ���΃G�t�F�N�g�̏����͍s��Ȃ�
				if (index != -1) {
					EFFECT_TYPE efect = m_pPlayerChara->m_activeFlag ? EFFECT_TYPE::EXPLOSION : EFFECT_TYPE::EXPLOSION_FINISH;
					//�G�t�F�N�g�C���X�^���X�̍쐬
					CEfect* pEfe = this->launchEffect(
						efect,
						m_pPlayerChara->m_move.m_posX,
						m_pPlayerChara->m_move.m_posY
					);

					//���C���[�ɒ���t����
					m_characterLayer->addChild(pEfe);

					//�z��ɃA�h���X�����t����
					this->m_pEffects[index] = pEfe;
					//�I�u�W�F�N�g�J�E���g�X�V
					if (index >= m_pEfectCount) {
						m_pEfectCount = index;
					}
					//�v���C���[�������ʉ�
					if (se_flg) {
						m_pPlayerChara->m_bgmid = AudioEngine::play2d(SOUND_FILE_PLAYER_EXPLOSION);
						AudioEngine::setVolume(m_pPlayerChara->m_bgmid, SE_VOLUME / 120.0f);
					}

				}
				return;
			}

			
		}

	}


}
// �ǂƃv���C���[�̒e�̏Փ�
void CGameMain::collisionWallsAndPlayerBullets() {
	//�v���C���[������ł������΂�
	//if (m_pPlayerChara->m_activeFlag == false)
	//return;

	for (int i = 0; i <= m_pPlayerBulletCount; i++) {
		//�v�f��NULL�Ȃ��΂�
		if (m_pPlayerBullets[i] == NULL)
			continue;

		//�L���t���O��false�́v�C���X�^���X����΂�
		if (m_pPlayerBullets[i]->m_activeFlag == false)
			continue;

		//�v���C���[�̏Փ˔�����s���ۂ̈ʒu���擾
		CBody playerCollisionBody = m_pPlayerBullets[i]->m_body.getApplyPositionBody(
			m_pPlayerBullets[i]->m_move.m_posX,
			m_pPlayerBullets[i]->m_move.m_posY
		);

		//���[�U�[�p�z��Y�����ۑ��p
		int laser = -1;

		//�ǂ͔z��Ȃ̂œG�̒e�̂P�P�ƏՓ˔�������
		for (int j = 0; j <= m_pWallCount; j++) {
			//�v�f��NULL�Ȃ��΂�
			if (m_pWalls[j] == NULL)
				continue;

			//�L���t���O��false�́v�C���X�^���X����΂�
			if (m_pWalls[j]->m_activeFlag == false)
				continue;

			//�ǂ̂P���̏Փ˔�����s���ۂ̈ʒu���擾
			CBody wallCollisionBody = m_pWalls[j]->m_body.getApplyPositionBody(
				m_pWalls[j]->m_move.m_posX,
				m_pWalls[j]->m_move.m_posY
			);
			//�Փ˔�����s��
			if (playerCollisionBody.collision(&wallCollisionBody) == true) {
				//�Փ˂��Ă���
				//�ǂ̏Փ˔���̌v�Z���s��
				
				switch (m_pPlayerBullets[i]->m_bulletType) {
				case BULLET_TYPE::PLAYER_EXPLOSION:
					
					//�����^�C�v�؂�ւ�
					m_pPlayerBullets[i]->m_bulletType = BULLET_TYPE::PLAYER_EXPLOSION_2;
					//�摜�̐ݒ�
					m_pPlayerBullets[i]->setTexture(IMAGE_FILE_EXPLOSION_2);
					//�؂����`
					m_pPlayerBullets[i]->m_chip = CChip(0, 0, 120, 120);
					m_pPlayerBullets[i]->setTextureRect(m_pWalls[j]->m_chip);
					//�X�e�[�^�X�̐ݒ�
					m_pPlayerBullets[i]->m_status.set(1, 1, 1, 0);
					//�ړ��f�[�^�ɏ������x�̐ݒ�@��~���
					m_pPlayerBullets[i]->m_move.setVel(0, 0);
					//�A�j���[�V�����f�[�^�̏�����
					m_pPlayerBullets[i]->m_anime.set(10, 7, false);
					//�Փ˔���p�f�[�^�̏�����
					m_pPlayerBullets[i]->m_body.set(
						-20 * m_pPlayerChara->m_shotParam,
						20 * m_pPlayerChara->m_shotParam,
						20 * m_pPlayerChara->m_shotParam,
						-20 * m_pPlayerChara->m_shotParam
					);
					//�摜�T�C�Y�����x���␳
					m_pPlayerBullets[i]->setScale(0.5f * m_pPlayerChara->m_shotParam);

					//���O���t���O�L��
					m_pPlayerBullets[i]->m_delflg = true;
					//���O���t���[���J�E���g�ݒ�
					m_pPlayerBullets[i]->m_maxCount = 70;
					//�G�t�F�N�g��\������
					createEffect2(j, m_pPlayerBullets[i]->m_move.m_posX, m_pPlayerBullets[i]->m_move.m_posY);

					break;
				case BULLET_TYPE::PLAYER_EXPLOSION_2:
					
					break;
				case BULLET_TYPE::PLAYER_LASER:


					if (laser == -1) {
						//�ŏ��͕K���G�̓Y��������
						laser = j;
					}
					else {
						//��Ԏ��@�ɋ߂��G�ɓY�������㏑��
						if (m_pWalls[laser]->m_move.m_posX - m_pWalls[laser]->m_chip.size.width * 0.5f >=
							m_pWalls[j]->m_move.m_posX - m_pWalls[j]->m_chip.size.width * 0.5f) {
							laser = j;
						}
					}
					break;
				default:
					//�ʏ�e�A�o�b�N�e�A�U�e�A�U���e�͏���
					//�v���C���[�̒e�̗L���t���O��false�ɂ���
					m_pPlayerBullets[i]->m_activeFlag = false;
					//�G�t�F�N�g��\������
					createEffect2(j, m_pPlayerBullets[i]->m_move.m_posX, m_pPlayerBullets[i]->m_move.m_posY);
					break;
				}


			}

		}
		//���[�U�[�̏ꍇ�����Ōv�Z
		if (m_pPlayerBullets[i]->m_bulletType == BULLET_TYPE::PLAYER_LASER) {

			if (laserFlg == false) {
				//���[�U�[�̗L���t���O��false�ɂ���
				m_pPlayerBullets[i]->m_activeFlag = false;
				cocos2d::log("laser off");
				continue;
			}

			//�G���ǂ̂����W���Ⴂ�ꍇ �������͕ǂ̔��肪�݂�G�̔��肪�����ꍇ
			if (laser != -1 && laserIndex == -1 ||
				laser != -1 && laserIndex != -1 && m_pEnemyCharas[laserIndex]->m_move.m_posX > m_pWalls[laser]->m_move.m_posX) {
				//�G���ǂ̂����W���Ⴂ�ꍇ �������͕ǂ̔��肪�݂�G�̔��肪�����ꍇ

				//���[�U�[�̒����ύX �ǂ̍��[ - �v���C���[�̉E�[
				m_pPlayerBullets[i]->m_chip.size.width = (m_pWalls[laser]->m_move.m_posX - m_pWalls[laser]->m_chip.size.width / 2) -
					(m_pPlayerChara->m_move.m_posX + m_pPlayerChara->m_chip.size.width / 2);

				if (m_pPlayerBullets[i]->m_activeFlag == true &&
					laserCounter <= this->m_frameCounter
					) {
					//���[�U�[�_���[�W�C���^�[�o���X�V
					laserCounter = this->m_frameCounter + 5;

					//�G�t�F�N�g��\������	
					createEffect2(laser, (m_pWalls[laser]->m_move.m_posX - m_pWalls[laser]->m_chip.size.width / 2), m_pPlayerBullets[i]->m_move.m_posY);
				}
			}
			else if (laser == -1 && laserIndex != -1 ||
				laser != -1 && laserIndex != -1 && m_pEnemyCharas[laserIndex]->m_move.m_posX < m_pWalls[laser]->m_move.m_posX) {
				//�ǂ��G�̂����W���Ⴂ�ꍇ �������͓G�̔��肪�݂�ǂ̔��肪�����ꍇ

				//���[�U�[�̒����ύX �G�̍��[ - �v���C���[�̉E�[
				m_pPlayerBullets[i]->m_chip.size.width = (m_pEnemyCharas[laserIndex]->m_move.m_posX - m_pEnemyCharas[laserIndex]->m_body.m_left) -
					(m_pPlayerChara->m_move.m_posX + m_pPlayerChara->m_chip.size.width / 2);

				if (m_pPlayerBullets[i]->m_activeFlag == true &&
					laserCounter <= this->m_frameCounter
					) {
					//���[�U�[�_���[�W�C���^�[�o���X�V
					laserCounter = this->m_frameCounter + 5;


					//�G�̏Փ˔���̌v�Z���s��
					m_pEnemyCharas[laserIndex]->hits(&m_pPlayerBullets[i]->m_status);

					//�G��|���Ă�����X�R�A�̌v�Z���s��
					calculationScore(laserIndex);

					//�G�t�F�N�g��\������	
					createEffect(laserIndex);
				}
			}
		}
	}
}
// �ǂƓG�̒e�̏Փ�
void CGameMain::collisionWallsAndEnemyBullets() {
	

	for (int i = 0; i <= m_pEnemyBulletCount; i++) {
		//�v�f��NULL�Ȃ��΂�
		if (m_pEnemyBullets[i] == NULL)
			continue;

		//�L���t���O��false�́v�C���X�^���X����΂�
		if (m_pEnemyBullets[i]->m_activeFlag == false)
			continue;

		//�v���C���[�̏Փ˔�����s���ۂ̈ʒu���擾
		CBody playerCollisionBody = m_pEnemyBullets[i]->m_body.getApplyPositionBody(
			m_pEnemyBullets[i]->m_move.m_posX,
			m_pEnemyBullets[i]->m_move.m_posY
		);

		//�ǂ͔z��Ȃ̂œG�̒e�̂P�P�ƏՓ˔�������
		for (int j = 0; j <= m_pWallCount; j++) {
			//�v�f��NULL�Ȃ��΂�
			if (m_pWalls[j] == NULL)
				continue;

			//�L���t���O��false�́v�C���X�^���X����΂�
			if (m_pWalls[j]->m_activeFlag == false)
				continue;

			//�ǂ̂P���̏Փ˔�����s���ۂ̈ʒu���擾
			CBody wallCollisionBody = m_pWalls[j]->m_body.getApplyPositionBody(
				m_pWalls[j]->m_move.m_posX,
				m_pWalls[j]->m_move.m_posY
			);
			//�Փ˔�����s��
			if (playerCollisionBody.collision(&wallCollisionBody) == true) {
				//�Փ˂��Ă���
				m_pEnemyBullets[i]->m_activeFlag = false;
				//�G�t�F�N�g��\������
				createEffect2(j, m_pEnemyBullets[i]->m_move.m_posX, m_pEnemyBullets[i]->m_move.m_posY);

			}

		}
	}
}


void CGameMain::stageStartFunc() {
	//=========================================================================
	//�T�E���h�t�@�C���̃X�e�[�W�؂�ւ����̓ǂݍ���
	//=========================================================================
	//���̃X�e�[�W�̃T�E���h�̓ǂݍ���
	switch (CGameMain::m_stageNo) {
	case 1:
		this->m_bgmid = AudioEngine::play2d(SOUND_FILE_BGM_1);
		break;
	case 2:
		this->m_bgmid = AudioEngine::play2d(SOUND_FILE_BGM_2);
		break;
	case 3:
		this->m_bgmid = AudioEngine::play2d(SOUND_FILE_BGM_3);
		break;
	}
	AudioEngine::setVolume(this->m_bgmid, BGM_VOLUME / 100.0f);
	//���[�h���X�e�[�W�X�V�����ɐ؂�ւ���
	this->m_stageMode = STAGE_MODE::UPDATE;
	
	//=========================================================================
	//�}�b�v�̃X�e�[�W�؂�ւ����Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	//���̃X�e�[�W�}�b�v�̐���
	//�}�b�v�̐���
	
	m_pMap = CMap::create(IMAGE_FILE_BACKGROUND);
	//�X�N���[�����x�̐ݒ�
	this->m_pMap->m_scrollMove.m_velX = 1.0f;
	//���[�v�ݒ�(���[�v����ݒ�)
	this->m_pMap->m_isLoop = true;
	//���C���[�Ɏ��t��
	m_backGroundLayer->addChild(this->m_pMap);
	//=========================================================================
	//�ǂ̃X�e�[�W�؂�ւ����Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	m_pWallXpos = 0;
	//=========================================================================
	//�v���C���[�̃X�e�[�W�؂�ւ����Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	//�v���C���[�̗L���t���O���グ��
	m_pPlayerChara->m_activeFlag = true;
	//�v���C���[��\������
	m_pPlayerChara->setVisible(true);
	//�v���C���[�̏����ʒu�̐ݒ�
	m_pPlayerChara->m_move.setPos(320.0f, 240.0f);
	//�����ʒu�̔��f
	m_pPlayerChara->setPosition(m_pPlayerChara->m_move.m_posX, m_pPlayerChara->m_move.m_posY);
	//=========================================================================
	//���[�U�[�C���^�[�t�F�[�X�̃X�e�[�W�؂�ւ����Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	//HP���x���̕\��
	m_pHpLabel->setVisible(true);
	//HP�Q�[�W�̕\��
	m_pHpGuage->setVisible(true);
	//�X�R�A���x���̕\��
	m_pScoreLabel->setVisible(true);
	//�X�e�[�W���x���̕\��
	m_pStageLabel->setVisible(true);
	//�v���C���[�����x���̕\��
	m_pPlayerLabel->setVisible(true);
	//�{�������x���̕\��
	m_pBomLabel->setVisible(true);

	//�T�E���h�̍Đ�
	AudioEngine::setLoop(m_bgmid, true);

}

/**
*@desc �X�e�[�W�X�V����
*@param �o�ߎ���
*/
void CGameMain::stageUpdateFunc(float deltaTime_) {

	//=========================================================================
	//
	//	�����ɍX�V�����̃R�[�h��ǉ����Ă���
	//
	//=========================================================================
	//�v���C��
	this->inputFunc();

	//=========================================================================
	//	���͏����Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================


	//=========================================================================
	//	�ǂ̏o���Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	checkLaunchWall();

	//=========================================================================
	//	�w�i�f���̏o���Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	checkLaunchPlanet();

	//=========================================================================
	//	�G�̏o���Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	
	checkLaunchEnemy();
	checkEnemyAleart();

	//=========================================================================
	//	�s�������Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	actionFunc();

	//=========================================================================
	//	�ړ������Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	//���x����ʒu���v�Z
	moveFunc();






	//=========================================================================
	//	��ʒ[���菈���Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================

	//��ʒ[�֐�
	endOfScreen();


	//=========================================================================
	//	�Փ˔���Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	//�v���C���[�ƓG�̒e
	this->collisionPlayerAndEnemyBullets();
	//�v���C���[�ƓG
	this->collisionPlayerAndEnemies();
	//�G�ƃv���C���[�̒e�̏Փ�
	this->collisionEnemiesAndPlayerBullets();
	//�v���C���[�ƃA�C�e���̏Փ�
	this->collisionPlayerAndItems();
	//�v���C���[�ƕ�
	this->collisionPlayerAndWalls();
	//�ǂƃv���C���[�̒e
	this->collisionWallsAndPlayerBullets();
	//�ǂƓG�̒e
	this->collisionWallsAndEnemyBullets();
	//=========================================================================
	//	�G�̒e�̔��˂Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	shotEnemyBullet();


	//=========================================================================
	//	�A�j���[�V���������Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	//�v���C���[�L�����̃A�j���[�V����

	//�A�j���[�V�����֐�
	animationFunc();

	//=========================================================================
	//	��\���Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================

	if (m_pPlayerChara->m_activeFlag == false) {
		//���ɔ�\���̏ꍇ�͔�\�������͍s��Ȃ�
		if (m_pPlayerChara->isVisible() == true) {
			//��\���ɂ���
			m_pPlayerChara->setVisible(false);
		}
	}
	//=========================================================================
	//�v���C���[�����Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	if (m_pPlayerChara->m_activeFlag == false) {
		playerCount--;

		m_pPlayerChara->m_activeFlag = true;

		if (playerCount >= 0) {
			//�v���C���[�c�@������ꍇ
			m_pPlayerChara->m_status.set(200, 200, 10, m_pPlayerChara->m_status.getScore());
			m_pPlayerChara->setVisible(true);
			m_pPlayerChara->m_move.setPos(-20, 240);
			m_pPlayerChara->setPosition(-20, 240);
			m_pPlayerChara->m_move.setVel(1, 0);
		}
		else {
			//�v���C���[�c�@���Ȃ��ꍇ
			m_pPlayerChara->m_move.setVel(0, 0);
		}

		m_pPlayerChara->m_move.setVel(1, 0);
		resurrection = true;
		resCount = 180;
	}


	//=========================================================================
	//	���O�������Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	//�v���C���[�̒e�̃��C���[����̎��O������
	checkActiveFlagAndRemove();


	//=========================================================================
	//	�v�Z�p�f�[�^�𔽉f�Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	this->applyFunc();


	//=========================================================================
	//	���[�U�[�C���^�[�t�F�[�X�̏������Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================


	//�t���[���J�E���^�[�̍X�V
	this->m_frameCounter++;
	//�ǃJ�E���^�[�̍X�V
	this->m_wallCounter += MapData::WALL_SPEED;
	//�T�E���h�f�B���C�J�E���g�_�E��
	if (soundDeray)
		soundDeray--;
}

void CGameMain::stagePauseFunc() {
	//��~��
	this->inputFunc2();
	//�J�[�\��NULL�`�F�b�N
	if (m_pCursor) {
		m_pCursor->moveFunc();
		m_pCursor->animationFunc();
		m_pCursor->applyFunc();

		//�摜�_��
		//�{�^����������Ă����烉�x���_�ŊJ�n
		if (p_scene && !SCENE_END) {

			c_frameCounter++;

			if (c_frameCounter > 5) {
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
				c_frameCounter = 0;
			}
			//�_�ŏI��
			if (flashing > 5) {
				flashingflg = false;
				p_scene = false;
				flashing = 0;

				//��ʑJ��

				Scene* pScene;
				switch (m_pCursor->p_y) {
				case 0:
					//EXIT
					//�Q�[�����C����
					//���y�G���W���I�����
					audioFlug = false;

					//�J�ڒ��I�����
					SCENE_END = true;
					//�^�C�g��BGM�t���O��߂�
					CTitle::TitleBgm = -1;

					//�ʏ�v���C�Ȃ烊�v���C�ۑ�
					if (mode == 0) {
						//���v���C�ۑ�
						REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4] = m_frameCounter;
						
						CReplaySelect::replay_flg = true;

					}

					//�X�R�A�o�^
					if (mode == 0 && m_pPlayerChara->m_status.getScore() > SCORE) {
						cocos2d::log("score=%d", m_pPlayerChara->m_status.getScore());
						//config.dat�ɐݒ��ۑ�
						int buf[3] = { BGM_VOLUME ,SE_VOLUME,m_pPlayerChara->m_status.getScore() };
						//�t�@�C���|�C���^
						FILE *file1;
						file1 = fopen("config.dat", "wb");
						fwrite(buf, sizeof(int), 3, file1);
						fclose(file1);
						SCORE = m_pPlayerChara->m_status.getScore();
					}
					//�^�C�g��BGM�t���O��߂�
					CTitle::TitleBgm = -1;

					this->unscheduleUpdate();
					if (mode == 0) {
						//�^�C�g����ʂ�
						pScene = CReplaySelect::createScene();
					}
					else {
						//���v���C��ʂ�
						pScene = CReplay::createScene();
					}
					Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
					break;
				case 1:
					//REDO

					
					CGameMain::mode = mode >= 3 ? 2 : mode;
					if (mode == 0) {
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
					}


					//�J�ڒ��I�����
					SCENE_END = true;

					//BGM��~
					AudioEngine::stopAll();
					this->unscheduleUpdate();
					pScene = CStageTitle::createScene();
					Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
					break;
				case 2:
					//PLAY
					//���[�h���ꎞ��~�����ɕύX
					this->m_stageMode = STAGE_MODE::UPDATE;
					//���ꎞ��~����
					AudioEngine::resumeAll();
					break;
				}

				//�|�[�Y��ʎ��O��
				pLavelArray[0]->removeFromParent();
				pLavelArray[1]->removeFromParent();
				pLavelArray[2]->removeFromParent();
				m_pCursor->removeFromParent();
				pLavelArray[0] = NULL;
				pLavelArray[1] = NULL;
				pLavelArray[2] = NULL;
				m_pCursor = NULL;
				

			}

		}
	}

}

void CGameMain::gameOverFunc() {
	//��~��
	this->inputFunc2();
	//�J�[�\��NULL�`�F�b�N
	if (m_pCursor) {
		m_pCursor->moveFunc();
		m_pCursor->animationFunc();
		m_pCursor->applyFunc();

		//�摜�_��
		//�{�^����������Ă����烉�x���_�ŊJ�n
		if (p_scene && !SCENE_END) {

			c_frameCounter++;

			if (c_frameCounter > 5) {
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
				c_frameCounter = 0;
			}
			//�_�ŏI��
			if (flashing > 5) {
				flashingflg = false;
				p_scene = false;
				flashing = 0;

				//��ʑJ��

				Scene* pScene;
				switch (m_pCursor->p_y) {
				case 0:
					//EXIT
					//�Q�[�����C����
					//���y�G���W���I�����
					audioFlug = false;

					//�J�ڒ��I�����
					SCENE_END = true;
					//�^�C�g��BGM�t���O��߂�
					CTitle::TitleBgm = -1;

					//�ʏ�v���C�Ȃ烊�v���C�ۑ�
					if (mode == 0) {
						//���v���C�ۑ�
						//REPLAY_DATA[1] = m_frameCounter;
						//���v���C�ۑ�
						REPLAY_DATA[1 + (CGameMain::m_stageNo - 1) * 4] = m_frameCounter;
						
						CReplaySelect::replay_flg = true;
					}
					//�X�R�A�o�^
					if (mode == 0 && m_pPlayerChara->m_status.getScore() > SCORE) {
						cocos2d::log("score=%d", m_pPlayerChara->m_status.getScore());
						//config.dat�ɐݒ��ۑ�
						int buf[3] = { BGM_VOLUME ,SE_VOLUME,m_pPlayerChara->m_status.getScore() };
						//�t�@�C���|�C���^
						FILE *file1;
						file1 = fopen("config.dat", "wb");
						fwrite(buf, sizeof(int), 3, file1);
						fclose(file1);
						SCORE = m_pPlayerChara->m_status.getScore();
					}
					this->unscheduleUpdate();
					if (mode == 0) {
						//�^�C�g����ʂ�
						pScene = CReplaySelect::createScene();
					}
					else {
						//���v���C��ʂ�
						pScene = CReplay::createScene();
					}

					Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
					break;
				case 1:
					//REDO

					
					//���y�G���W���I�����
					audioFlug = false;

					//�J�ڒ��I�����
					SCENE_END = true;

					CGameMain::mode = mode >= 3 ? 2 : mode;
					if (mode == 0) {
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
					}

					//BGM��~
					AudioEngine::stopAll();
					//�^�C�g��BGM�t���O�߂�
					CTitle::TitleBgm = -1;
					this->unscheduleUpdate();
					pScene = CStageTitle::createScene();
					Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
					break;
				}

				//�|�[�Y��ʎ��O��
				pLavelArray[0]->removeFromParent();
				pLavelArray[1]->removeFromParent();
				m_pCursor->removeFromParent();
				pLavelArray[0] = NULL;
				pLavelArray[1] = NULL;
				m_pCursor = NULL;
				

			}

		}
	}

}


void CGameMain::stageEndFunc() {
	//=======================================================
	//�T�E���h�Ɋւ���R�[�h�̒ǉ��͂�������
	//=======================================================
	//�w�i�̒�~
	AudioEngine::stop(this->m_bgmid);
	//�S�Ă̌��ʉ��̒�~
	AudioEngine::stopAll();
	//=======================================================
	//�v���C���[�L�����N�^�[�Ɋւ���R�[�h�̒ǉ��͂�������
	//=======================================================
	//�v���C���[�̗L���t���O�������ĉ�ʂ����\��
	if (m_pPlayerChara != NULL) {
		//�L���t���O���Q�[���̍��ɂ���Ă͉�����K�v���Ȃ�
		m_pPlayerChara->m_activeFlag = false;

		//�v���C���[�͎g���܂킷�̂ł��������폜������\���ɂ��邾��
		m_pPlayerChara->setVisible(false);

	}
	//�����t���O������
	resurrection = false;
	//�����J�E���g������
	resCount = 0;
	//�v���C���[��������
	playerCount = 2;
	//�{���J�E���g������
	bomCount = 0;
	//�{����������
	bom = 3;
	//�X�e�[�^�X������
	m_pPlayerChara->m_status.set(20, 20, 10, 0, 2);
	//�U�����x���ݒ�
	pweponLevel[0] = 0;		//NORMAL
	pweponLevel[1] = 0;		//EXPLOSION
	pweponLevel[2] = 0;		//BACK
	pweponLevel[3] = 0;		//LASER
	pweponLevel[4] = 0;		//INDCTION
	pweponLevel[5] = 0;		//MULTIPLE
	pweponLevelLavel[0]->setString(cocos2d::StringUtils::format("Level %d", 1));
	pweponLevelLavel[1]->setString(cocos2d::StringUtils::format("Level %d", 1));
	pweponLevelLavel[2]->setString(cocos2d::StringUtils::format("Level %d", 1));
	pweponLevelLavel[3]->setString(cocos2d::StringUtils::format("Level %d", 1));
	pweponLevelLavel[4]->setString(cocos2d::StringUtils::format("Level %d", 1));
	pweponLevelLavel[5]->setString(cocos2d::StringUtils::format("Level %d", 1));
	//=======================================================
	//�v���C���[�o���b�g�Ɋւ���R�[�h�̒ǉ��͂�������
	//=======================================================
	//�v���C���[�o���b�g�����C���[������O����NULL����
	for (int i = 0; i < CBullet::MAX_BULLET; i++) {
		if (m_pPlayerBullets[i] == NULL) {
			continue;
		}

		m_pPlayerBullets[i]->removeFromParent();
		m_pPlayerBullets[i] = NULL;
	}
	//�J�E���g���Z�b�g
	m_pPlayerBulletCount = 0;
	//=======================================================
	//�G�L�����N�^�[�Ɋւ���R�[�h�̒ǉ��͂�������
	//=======================================================
	//�G�L�����N�^�[�����C���[������O����NULL����
	for (int i = 0; i < CEnemyCharacter::MAX_ENEMY; i++) {
		if (m_pEnemyCharas[i] == NULL) {
			continue;
		}

		m_pEnemyCharas[i]->removeFromParent();
		m_pEnemyCharas[i] = NULL;
	}
	//�J�E���g���Z�b�g
	m_pEnemyCount = 0;
	//=======================================================
	//�G�l�~�[�o���b�g�Ɋւ���R�[�h�̒ǉ��͂�������
	//=======================================================
	//�G�l�~�[�o���b�g�[�����C���[������O����NULL����
	for (int i = 0; i < CBullet::MAX_BULLET; i++) {
		if (m_pEnemyBullets[i] == NULL) {
			continue;
		}

		m_pEnemyBullets[i]->removeFromParent();
		m_pEnemyBullets[i] = NULL;
	}
	//�J�E���g���Z�b�g
	m_pEnemyBulletCount = 0;
	//=======================================================
	//�G�t�F�N�g�Ɋւ���R�[�h�̒ǉ��͂�������
	//=======================================================
	//�G�t�F�N�g�����C���[������O����NULL����
	for (int i = 0; i < CEfect::MAX_EFFECT; i++) {
		if (m_pEffects[i] == NULL) {
			continue;
		}

		m_pEffects[i]->removeFromParent();
		m_pEffects[i] = NULL;
	}
	//�J�E���g���Z�b�g
	m_pEfectCount = 0;
	//=======================================================
	//�A�C�e���Ɋւ���R�[�h�̒ǉ��͂�������
	//=======================================================
	//�A�C�e�������C���[������O����NULL����
	for (int i = 0; i < CItem::MAX_ITEM; i++) {
		if (m_pItems[i] == NULL) {
			continue;
		}

		m_pItems[i]->removeFromParent();
		m_pItems[i] = NULL;
	}
	//�J�E���g���Z�b�g
	m_pItemCount = 0;
	//=======================================================
	//�ǂɊւ���R�[�h�̒ǉ��͂�������
	//=======================================================
	//�ǂ����C���[������O����NULL����
	for (int i = 0; i < CWall::MAX_WALL; i++) {
		if (m_pWalls[i] == NULL) {
			continue;
		}

		m_pWalls[i]->removeFromParent();
		m_pWalls[i] = NULL;
	}
	//�J�E���g���Z�b�g
	m_pItemCount = 0;
	//=======================================================
	//�G�o���f�[�^�Ɋւ���R�[�h�̒ǉ��͂�������
	//=======================================================
	//�G�o���f�[�^�̉��
	SAFE_DELETE_ARRAY(m_pEnemyLaunchData);

	//�G�o���C���f�b�N�X�̃��Z�b�g
	m_enemyLaunchIndex = 0;

	//�t���[���J�E���^�[�̃��Z�b�g
	m_frameCounter = 0;
	//=======================================================
	//�}�b�v�Ɋւ���R�[�h�̒ǉ��͂�������
	//=======================================================
	//�}�b�v�����C���[������O����NULL����
	if (m_pMap != NULL) {
		m_pMap->removeFromParent();
		m_pMap = NULL;
	}
	//=======================================================
	//�ǂɊւ���R�[�h�̒ǉ��͂�������
	//=======================================================
	//�ǃC���f�b�N�X�̃��Z�b�g
	m_pWallXpos = 0;

	//�ǃJ�E���^�[�̃��Z�b�g
	m_wallCounter = 0;
	//=======================================================
	//UI�Ɋւ���R�[�h�̒ǉ��͂�������
	//=======================================================
	//�S�Ă�UI�����������\���ɂ���
	m_pHpLabel->setVisible(false);
	m_pHpGuage->setVisible(false);
	m_pScoreLabel->setVisible(false);
	m_pStageLabel->setVisible(false);
	m_pPlayerLabel->setVisible(false);
	m_pBomLabel->setVisible(false);

	//=======================================================
	//���v���C�Ɋւ���R�[�h�̒ǉ��͂�������
	//=======================================================
	//���v���C�z�񏉊���
	if (mode == 0) {
		for (int i = 0; i < 4010; i++) {
			REPLAY_DATA[i] = 0;
		}
		REPLAY_DATA[0] = MapData::m_seed;
	}

	//�X�e�[�W���ɃV�[�h�l�ݒ�
	srand(MapData::m_seed);
	for (int i = 0; i < CGameMain::m_stageNo; i++) {
		rand();
	}
	srand(rand());

	//=======================================================
	//�X�e�[�W�̐؂�ւ��Ɋւ���R�[�h�̒ǉ��͂�������
	//=======================================================
	if (this->m_stageNo >= CGameMain::MAX_STAGE_COUNT) {
		//TODO:�����ŃG���f�B���O�V�[���ɐi��
	}
	else {
		//�X�e�[�W���X�V(�C���N�������g���邾��)
		this->m_stageNo++;

		//���[�h���X�e�[�W�J�n�ɐ؂�ւ���
		this->m_stageMode = STAGE_MODE::START;
	}

}