#include "Map.h"
//コンストラクタ
CMap::CMap() {

}
//デストラクタ
CMap::~CMap() {

}
/**
*@desc 生成
*@param tmxファイル名
*@return CMapクラスのインスタンス
*@tips CREATE_FUMCマクロの中身
*		静的メンバ関数
*/
CMap* CMap::create(std::string tmxFile) {
	//マップクラスを生成する
	CMap* pMap = new CMap();

	//TMXTiledMapの初期化処理と
	//CMapの初期化処理を行うinitWithTMXFile
	if (pMap->initWithFile(tmxFile) == true && pMap->init() == true) {
		//生成が成功したら自動deletを設定
		pMap->autorelease();
		//マップクラスのインスタンスを返す
		return pMap;
	}
	//生成が失敗していたらマップクラスのインスタンスを解放
	CC_SAFE_DELETE(pMap);
	//NULLを返す
	return NULL;
}

/**
*@desc マップクラスの初期化
*/
bool CMap::init() {
	/**
	*スクロール終了位置の計算
	*/
	//位置セット
	this->m_scrollMove.setPos(0,0);
	
	//画面サイズの取得
	cocos2d::Size winSize = cocos2d::Director::getInstance()->getWinSize();
	
	//マップの終了位置を取得
	this->m_scrollEndPos.x = (640) - winSize.width;
	

	//初期化の位置の設定と反映
	this->m_scrollMove.setPos(640.0f,240.0f);
	this->setPosition(0.0f,0.0f);
	return true;
}

//スクロール(移動)処理
void CMap::moveFunc() {
	//マップスクロールのX移動処理
	if (this->m_scrollMove.m_posX < -this->m_scrollEndPos.x) {
		if (m_isLoop == true) {
			//ループする場合はマップの位置を戻す
			this->m_scrollMove.m_posX = 640;
		}
		else {
			//ループしない場合は終了フラグを上げる
			this->m_isEnd = true;
		}
	}
	else {
		//マップをスクロール
		this->m_scrollMove.m_posX -= this->m_scrollMove.m_velX;
	}
}
//反射処理
void CMap::applyFunc() {
	//マップの値の反映処理
	this->setPosition(this->m_scrollMove.m_posX, this->m_scrollMove.m_posY);
}