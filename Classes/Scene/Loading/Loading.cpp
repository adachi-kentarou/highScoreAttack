#include "Constants.h"
#include "Loading.h"
#include "Scene/GameMain/GameMain.h"
#include<string>
//cocos2d::の省略
using namespace cocos2d;

using namespace cocos2d::experimental;

//デストラクタ
CLoading::~CLoading() {
	
}
/**
*@desc シーンの生成
*@return CTitleレイヤーを内包したシーンクラスインスタンス
*@tips 静的メンバ関数
*/
cocos2d::Scene* CLoading::createScene() {
	//シーンの生成
	cocos2d::Scene* pScene = cocos2d::Scene::create();

	//CTitleレイヤーの生成
	CLoading* pLayer = CLoading::create();

	//Ctitleレイヤーをシーンに取り付ける
	pScene->addChild(pLayer);

	//生成したシーンを返す
	return pScene;
}

//読み込みファイル数初期化
int CLoading::m_pRoadFiles = 0;
bool CLoading::flg = true;
/**
*@desc 初期化
*@return true...成功false...失敗
*/
bool CLoading::init() {

	//update関数(更新処理関数)呼び出し設定
	this->scheduleUpdate();
	//===================================================
	//ここから初期化、初期設定のコードを追加
	//===================================================
	//タイトル背景の生成と取り付け
	Sprite* pBg = Sprite::create(IMAGE_FILE_TITLE_BG);
	//初期位置の設定
	pBg->setPosition(320.0f, 240.0f);
	//レイヤーに取り付け
	this->addChild(pBg);

	//===================================================
	//タイトルラベルに関するコードの追加はここから
	//===================================================
	//タイトルラベルの生成と取り付け
	pTitleLabel = cocos2d::Label::createWithTTF("ShootingGame", FONT_FILE_STARWARS, 62);
	//初期位置の設定
	pTitleLabel->setPosition(320.0f, 360.0f);
	//文字色の設定
	pTitleLabel->setColor(Color3B(0, 200, 200));
	//レイヤーに取り付け
	this->addChild(pTitleLabel);
	pTitleLabel->setString("0");
	//===================================================
	//ゲージに関するコードの追加はここから
	//===================================================
	//ゲージの生成と初期化
	m_pLoadingGuage = CLoadingGuage::create();
	this->addChild(m_pLoadingGuage);
	
	//===================================================
	//ここまで初期化、初期設定のコードを追加
	//===================================================
	
	return true;
}

//音楽コールバック
void CLoading::audioCallBack(bool isSucces) {
	CLoading::m_pRoadFiles++;
	cocos2d::log("audioload %d", CLoading::m_pRoadFiles);
}

//画像コールバック
void CLoading::textureCallBack(cocos2d::Texture2D* texture) {
	CLoading::m_pRoadFiles++;
	cocos2d::log("textureload %d", CLoading::m_pRoadFiles);
}


/**
*@desc ゲームメインに遷移
@param タイトルレイヤーのインスタンス
*@tips スタートボタンが押されたときに呼び出される
*/
void CLoading::callbackChangeTitle() {
	OutputDebugString(L"ロードが終わったよ\n");
	//オーディオ削除フラグ下げ
	audioFlug = false;
	//遷移中終了回避
	SCENE_END = true;
	this->unscheduleUpdate();
	Scene* pScene = CTitle::createScene();
	Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, pScene));
	
}

/**
*@desc 更新処理
*@param 経過時間
*/
void CLoading::update(float deltaTime) {
	if (CLoading::flg) {
		CLoading::flg = false;
		//===================================================
		//ここからファイル読み込みのコードを追加
		//===================================================
		//非同期処理開始
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
		//ここまでファイル読み込みのコードを追加
		//===================================================

	}
	//===================================================
	//ここに更新処理のコードを追加していく
	//===================================================
	if (!this->m_pLoadingGuage) {
		return;
	}
	//ゲージ更新
	float percentage = CLoading::m_pRoadFiles / (float)this->MAX_FILES * 100;
	this->m_pLoadingGuage->setPercentage( percentage );
	this->pTitleLabel->setString(cocos2d::StringUtils::format("%d %",(int)percentage));
	
	countFrame++;
	//100%ならタイトルシーンへ移動
	if (percentage == 100.0f && countFrame >= 60) {
		callbackChangeTitle();
	}
}

//=========================================================================
//　ゲージのクラスの関数の定義はここから書く
//=========================================================================
//コンストラクタ
CLoadingGuage::CLoadingGuage() {
	
	auto th = std::thread([&] {
		//configファイル確認
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
			//ファイルから読み込む
			//ファイルポインタ
			
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
			//ファイル作成
			//初期設定　BGM10 SE10
			buf[0] = 10;
			buf[1] = 10;
			buf[2] = 0;
			buf[3] = 1;

			//ファイルポインタ
			
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
		//読み込みカウントアップ
		CLoading::m_pRoadFiles++;
		cocos2d::log("bgm%d se%d", BGM_VOLUME, SE_VOLUME);
	});
	th.detach();
}
//デストラクタ
CLoadingGuage::~CLoadingGuage() {

}
//初期化処理
bool CLoadingGuage::init() {
	//ゲージで使用する画像を生成
	cocos2d::Sprite* pSprite = cocos2d::Sprite::create(IMAGE_FILE_HP_GUAGE);
	
	//生成したスプライトを使って基底クラスの初期化を行う
	if (cocos2d::ProgressTimer::initWithSprite(pSprite) == false) {
		CCLOG("CLoagingGuage() ProgressTimer::initWithSprite is false!!");
		return false;
	}

	//プログレスタイマーの初期の長さを設定　バーはパーセンテージで表示
	this->setPercentage(99.9f);
	//プログレスタイマーのタイプを設定(バーに設定)
	this->setType(cocos2d::ProgressTimer::Type::BAR);
	//プログレスバーの伸びる方向(X方向に設定)
	this->setBarChangeRate(cocos2d::Point(1, 0));
	//プログレスタイマーバーの基準点(左側に設定)
	this->setMidpoint(cocos2d::Point(0, 0));
	//プログレスタイマーバーの位置を設定
	//
	this->setPosition(WINDOW_RIGHT * 0.5f, WINDOW_TOP * 0.5f);
	
	return true;
}

