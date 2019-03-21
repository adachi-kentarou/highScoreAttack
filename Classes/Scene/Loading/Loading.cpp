#include "Constants.h"
#include "Loading.h"
#include "Scene/GameMain/GameMain.h"
#include<string>
//cocos2d::�̏ȗ�
using namespace cocos2d;

using namespace cocos2d::experimental;

//�f�X�g���N�^
CLoading::~CLoading() {
	
}
/**
*@desc �V�[���̐���
*@return CTitle���C���[�������V�[���N���X�C���X�^���X
*@tips �ÓI�����o�֐�
*/
cocos2d::Scene* CLoading::createScene() {
	//�V�[���̐���
	cocos2d::Scene* pScene = cocos2d::Scene::create();

	//CTitle���C���[�̐���
	CLoading* pLayer = CLoading::create();

	//Ctitle���C���[���V�[���Ɏ��t����
	pScene->addChild(pLayer);

	//���������V�[����Ԃ�
	return pScene;
}

//�ǂݍ��݃t�@�C����������
int CLoading::m_pRoadFiles = 0;
bool CLoading::flg = true;
/**
*@desc ������
*@return true...����false...���s
*/
bool CLoading::init() {

	//update�֐�(�X�V�����֐�)�Ăяo���ݒ�
	this->scheduleUpdate();
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
	//�^�C�g�����x���̐����Ǝ��t��
	pTitleLabel = cocos2d::Label::createWithTTF("ShootingGame", FONT_FILE_STARWARS, 62);
	//�����ʒu�̐ݒ�
	pTitleLabel->setPosition(320.0f, 360.0f);
	//�����F�̐ݒ�
	pTitleLabel->setColor(Color3B(0, 200, 200));
	//���C���[�Ɏ��t��
	this->addChild(pTitleLabel);
	pTitleLabel->setString("0");
	//===================================================
	//�Q�[�W�Ɋւ���R�[�h�̒ǉ��͂�������
	//===================================================
	//�Q�[�W�̐����Ə�����
	m_pLoadingGuage = CLoadingGuage::create();
	this->addChild(m_pLoadingGuage);
	
	//===================================================
	//�����܂ŏ������A�����ݒ�̃R�[�h��ǉ�
	//===================================================
	
	return true;
}

//���y�R�[���o�b�N
void CLoading::audioCallBack(bool isSucces) {
	CLoading::m_pRoadFiles++;
	cocos2d::log("audioload %d", CLoading::m_pRoadFiles);
}

//�摜�R�[���o�b�N
void CLoading::textureCallBack(cocos2d::Texture2D* texture) {
	CLoading::m_pRoadFiles++;
	cocos2d::log("textureload %d", CLoading::m_pRoadFiles);
}


/**
*@desc �Q�[�����C���ɑJ��
@param �^�C�g�����C���[�̃C���X�^���X
*@tips �X�^�[�g�{�^���������ꂽ�Ƃ��ɌĂяo�����
*/
void CLoading::callbackChangeTitle() {
	OutputDebugString(L"���[�h���I�������\n");
	//�I�[�f�B�I�폜�t���O����
	audioFlug = false;
	//�J�ڒ��I�����
	SCENE_END = true;
	this->unscheduleUpdate();
	Scene* pScene = CTitle::createScene();
	Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
	
}

/**
*@desc �X�V����
*@param �o�ߎ���
*/
void CLoading::update(float deltaTime) {
	if (CLoading::flg) {
		CLoading::flg = false;
		//===================================================
		//��������t�@�C���ǂݍ��݂̃R�[�h��ǉ�
		//===================================================
		//�񓯊������J�n
		audioFlug = true;
		
		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_NAME_BG, CLoading::textureCallBack);

		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_CHARACTER, CLoading::textureCallBack);

		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_BULLET, CLoading::textureCallBack);

		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_EXPLOSION, CLoading::textureCallBack);

		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_HP_GUAGE, CLoading::textureCallBack);

		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_ITEM, CLoading::textureCallBack);

		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_TITLE_BG, CLoading::textureCallBack);

		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_START_BUTTON, CLoading::textureCallBack);

		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_START_BUTTON_SELECTED, CLoading::textureCallBack);

		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_END_BUTTON, CLoading::textureCallBack);

		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_END_BUTTON_SELECTED, CLoading::textureCallBack);

		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_CURSOR, CLoading::textureCallBack);

		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_TITLE_BACKGROUND, CLoading::textureCallBack);

		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_EXPLOSION_FINISH, CLoading::textureCallBack);

		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_EXPLOSION_2, CLoading::textureCallBack);

		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_BACKGROUND, CLoading::textureCallBack);

		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_CHARACTER_2, CLoading::textureCallBack);
		
		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_BOM, CLoading::textureCallBack);
		
		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_WALL, CLoading::textureCallBack);
		
		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_WALL_2, CLoading::textureCallBack);
		
		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_WALL_3, CLoading::textureCallBack);

		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_WALL_4, CLoading::textureCallBack);
		
		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_WALL_5, CLoading::textureCallBack);

		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_WALL_6, CLoading::textureCallBack);

		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_WALL_BORDER_1, CLoading::textureCallBack);

		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_WALL_BORDER_2, CLoading::textureCallBack);

		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_WALL_BORDER_3, CLoading::textureCallBack);

		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_BOSS_1, CLoading::textureCallBack);

		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_REPLAY, CLoading::textureCallBack);

		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_PLANET_1, CLoading::textureCallBack);
		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_PLANET_2, CLoading::textureCallBack);
		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_PLANET_3, CLoading::textureCallBack);
		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_PLANET_4, CLoading::textureCallBack);
		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_PLANET_5, CLoading::textureCallBack);
		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_PLANET_6, CLoading::textureCallBack);
		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_PLANET_7, CLoading::textureCallBack);
		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_PLANET_8, CLoading::textureCallBack);
		cocos2d::TextureCache::sharedTextureCache()->addImageAsync(IMAGE_FILE_PLANET_9, CLoading::textureCallBack);


		AudioEngine::preload(SOUND_FILE_BGM_1, CLoading::audioCallBack);

		AudioEngine::preload(SOUND_FILE_BGM_2, CLoading::audioCallBack);

		AudioEngine::preload(SOUND_FILE_BGM_3, CLoading::audioCallBack);

		AudioEngine::preload(SOUND_FILE_TITLE, CLoading::audioCallBack);

		AudioEngine::preload(SOUND_FILE_CURSOR_1, CLoading::audioCallBack);

		AudioEngine::preload(SOUND_FILE_CURSOR_2, CLoading::audioCallBack);

		AudioEngine::preload(SOUND_FILE_LAUNCH_BULLET, CLoading::audioCallBack);

		AudioEngine::preload(SOUND_FILE_ENEMY_EXPLOSION, CLoading::audioCallBack);

		AudioEngine::preload(SOUND_FILE_PLAYER_EXPLOSION, CLoading::audioCallBack);
		
		AudioEngine::preload(SOUND_FILE_ENEMY_EXPLOSION_FINISH, CLoading::audioCallBack);

		AudioEngine::preload(SOUND_FILE_ITEM_GET, CLoading::audioCallBack);

		AudioEngine::preload(SOUND_FILE_ITEM_SPEED_UP, CLoading::audioCallBack);
		
		AudioEngine::preload(SOUND_FILE_ITEM_NORMAL, CLoading::audioCallBack);

		AudioEngine::preload(SOUND_FILE_ITEM_RECEVERY, CLoading::audioCallBack);

		AudioEngine::preload(SOUND_FILE_ITEM_EXPLOSION, CLoading::audioCallBack);

		AudioEngine::preload(SOUND_FILE_ITEM_BACK, CLoading::audioCallBack);

		AudioEngine::preload(SOUND_FILE_ITEM_LASER, CLoading::audioCallBack);

		AudioEngine::preload(SOUND_FILE_ITEM_INDUCTION, CLoading::audioCallBack);

		AudioEngine::preload(SOUND_FILE_ITEM_MULTIPLE, CLoading::audioCallBack);

		AudioEngine::preload(SOUND_FILE_ITEM_BOM, CLoading::audioCallBack);

		AudioEngine::preload(SOUND_FILE_ITEM_ONE_UP, CLoading::audioCallBack);

		AudioEngine::preload(SOUND_FILE_BOM, CLoading::audioCallBack);

		AudioEngine::preload(SOUND_FILE_STAGE_CLEAR, CLoading::audioCallBack);

		AudioEngine::preload(SOUND_FILE_GAME_OVER, CLoading::audioCallBack);

		AudioEngine::preload(SOUND_FILE_TIME_UP, CLoading::audioCallBack);
		//===================================================
		//�����܂Ńt�@�C���ǂݍ��݂̃R�[�h��ǉ�
		//===================================================

	}
	//===================================================
	//�����ɍX�V�����̃R�[�h��ǉ����Ă���
	//===================================================
	if (!this->m_pLoadingGuage) {
		return;
	}
	//�Q�[�W�X�V
	float percentage = CLoading::m_pRoadFiles / (float)this->MAX_FILES * 100;
	this->m_pLoadingGuage->setPercentage( percentage );
	this->pTitleLabel->setString(cocos2d::StringUtils::format("%d %",(int)percentage));
	
	countFrame++;
	//100%�Ȃ�^�C�g���V�[���ֈړ�
	if (percentage == 100.0f && countFrame >= 60) {
		callbackChangeTitle();
	}
}

//=========================================================================
//�@�Q�[�W�̃N���X�̊֐��̒�`�͂������珑��
//=========================================================================
//�R���X�g���N�^
CLoadingGuage::CLoadingGuage() {
	
	auto th = std::thread([&] {
		//config�t�@�C���m�F
		struct stat st;
		const char* file = "config.dat";
		int buf[4];
		/*
		HANDLE hFile;
		//char *lpFileName = "test.txt";
		//char szBuff[1024];
		DWORD dwNumberOfReadBytes;
		DWORD dwNumberOfBytesWritten;
		BOOL bRet;
		*/
		if (stat(file, &st) == 0) {
		//if(true){
			cocos2d::log("config.dat find");
			//�t�@�C������ǂݍ���
			//�t�@�C���|�C���^
			
			FILE *file;
			file = fopen("config.dat", "rb");
			fread(buf, sizeof(int), 4, file);
			fclose(file);
			
			
			/*
			hFile = CreateFile((LPCWSTR)file,
				GENERIC_READ,
				FILE_SHARE_READ,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL
			);

			bRet = ReadFile(hFile,
				buf,
				sizeof(int),
				&dwNumberOfReadBytes,
				NULL);
			CloseHandle(hFile);
			*/
			

			BGM_VOLUME = buf[0];
			SE_VOLUME = buf[1];
			SCORE = buf[2];
			GAME_PAD = buf[3];
		}
		else {
			cocos2d::log("config.dat not find");
			//�t�@�C���쐬
			//�����ݒ�@BGM10 SE10
			buf[0] = 10;
			buf[1] = 10;
			buf[2] = 0;
			buf[3] = 1;

			//�t�@�C���|�C���^
			
			FILE *file1;
			file1 = fopen("config.dat", "wb");
			fwrite(buf, sizeof(int), 4, file1);
			fclose(file1);
			/*
			hFile = CreateFile((LPCWSTR)file,
				GENERIC_WRITE,
				FILE_SHARE_WRITE,
				NULL,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL
			);
			WriteFile(GetStdHandle(STD_OUTPUT_HANDLE),
				buf,
				dwNumberOfReadBytes,
				&dwNumberOfBytesWritten,
				NULL);
			*/
			

			BGM_VOLUME = buf[0];
			SE_VOLUME = buf[1];
			SCORE = buf[2];
			GAME_PAD = buf[3];
		}
		//�ǂݍ��݃J�E���g�A�b�v
		CLoading::m_pRoadFiles++;
		cocos2d::log("bgm%d se%d", BGM_VOLUME, SE_VOLUME);
	});
	th.detach();
}
//�f�X�g���N�^
CLoadingGuage::~CLoadingGuage() {

}
//����������
bool CLoadingGuage::init() {
	//�Q�[�W�Ŏg�p����摜�𐶐�
	cocos2d::Sprite* pSprite = cocos2d::Sprite::create(IMAGE_FILE_HP_GUAGE);
	
	//���������X�v���C�g���g���Ċ��N���X�̏��������s��
	if (cocos2d::ProgressTimer::initWithSprite(pSprite) == false) {
		CCLOG("CLoagingGuage() ProgressTimer::initWithSprite is false!!");
		return false;
	}

	//�v���O���X�^�C�}�[�̏����̒�����ݒ�@�o�[�̓p�[�Z���e�[�W�ŕ\��
	this->setPercentage(99.9f);
	//�v���O���X�^�C�}�[�̃^�C�v��ݒ�(�o�[�ɐݒ�)
	this->setType(cocos2d::ProgressTimer::Type::BAR);
	//�v���O���X�o�[�̐L�т����(X�����ɐݒ�)
	this->setBarChangeRate(cocos2d::Point(1, 0));
	//�v���O���X�^�C�}�[�o�[�̊�_(�����ɐݒ�)
	this->setMidpoint(cocos2d::Point(0, 0));
	//�v���O���X�^�C�}�[�o�[�̈ʒu��ݒ�
	//
	this->setPosition(WINDOW_RIGHT * 0.5f, WINDOW_TOP * 0.5f);
	
	return true;
}

