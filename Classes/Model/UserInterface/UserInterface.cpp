#include "UserInterface.h"
#include "Constants.h"

//=========================================================================
//　HP表示用のラベルクラスはここから書く
//=========================================================================
//コンストラクタ
CHpLabel::CHpLabel() {
	//ゴミ処理
	this->m_pStatus = NULL;
}
//デストラクタ
CHpLabel::~CHpLabel() {

}
bool CHpLabel::init() {

	//=========================================================================
	//	ユーザーインターフェースの初期化に関するコードの追加はここから
	//=========================================================================
	//文字列のフォントタイプ
	this->setSystemFontName("Arial");
	//文字列のフォントサイズ
	this->setSystemFontSize(24);
	//アンカーポイント設定
	this->setAnchorPoint(cocos2d::Point(0.0f, 0.5f));

	//左寄せ
	this->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
	//位置の設定
	this->setPosition(cocos2d::Point(WINDOW_RIGHT * 0.0f, WINDOW_TOP * 0.97f));
	
	//自動て更新処理を呼び出す
	this->scheduleUpdate();
	return true;
}

void CHpLabel::update(float deltaTime_)
{
	if (this->m_pStatus == NULL)
		return;

	//表示するHPを文字列に変換
	std::string hpStr = cocos2d::StringUtils::format("HP:%d", this->m_pStatus->getHp());

	this->setString(hpStr);

}

//=========================================================================
//　HPゲージのクラスの関数の定義はここから書く
//=========================================================================
//コンストラクタ
CHpGuage::CHpGuage() {
	//ゴミ処理
	this->m_pStatus = NULL;
}
//デストラクタ
CHpGuage::~CHpGuage() {

}
//初期化処理
bool CHpGuage::init() {


	//HPゲージで使用する画像を生成
	cocos2d::Sprite* pSprite = cocos2d::Sprite::create(IMAGE_FILE_HP_GUAGE);

	//生成したスプライトを使って基底クラスの初期化を行う
	if (cocos2d::ProgressTimer::initWithSprite(pSprite) == false) {
		CCLOG("CHpGuage() ProgressTimer::initWithSprite is false!!");
		return false;
	}

	//プログレスタイマーの初期の長さを設定　バーはパーセンテージで表示
	this->setPercentage(0.0f);
	//プログレスタイマーのタイプを設定(バーに設定)
	this->setType(cocos2d::ProgressTimer::Type::BAR);
	//プログレスバーの伸びる方向(X方向に設定)
	this->setBarChangeRate(cocos2d::Point(1,0));
	//プログレスタイマーバーの基準点(左側に設定)
	this->setMidpoint(cocos2d::Point(0,0));
	//プログレスタイマーバーの位置を設定
	this->setPosition(180.0f,468.0f);
	//サイズ変更
	this->setScale(0.5f);

	//更新処理の設定
	this->scheduleUpdate();
	return true;
}

/**
*@desc 更新処理
*@param 経過時間
*/
void CHpGuage::update(float deltaTimer_) {
	if (this->m_pStatus == NULL)
		return;
	
	//プレイヤーのHPバーラベルの設定
	if (0 <= this->m_pStatus->getHp()) {
		//現在のライフを最大ライフと比較してパーセンテージに変換
		//int型で計算すると0になってしまうのでfloat型にキャストして計算する
		float hp = ((float)this->m_pStatus->getHp() / (float)this->m_pStatus->getMaxHp() ) * 100.0f;
		
		//表示する画像の割合を設定
		this->setPercentage(hp);
	}
}

//=========================================================================
//　スコア表示用のラベルクラスはここから書く
//=========================================================================
//コンストラクタ
CScoreLabel::CScoreLabel() {
	//ゴミ処理
	this->m_pStatus = NULL;
}
//デストラクタ
CScoreLabel::~CScoreLabel() {

}
bool CScoreLabel::init() {

	//=========================================================================
	//	ユーザーインターフェースの初期化に関するコードの追加はここから
	//=========================================================================
	//文字列のフォントタイプ
	this->setSystemFontName("Arial");
	//文字列のフォントサイズ
	this->setSystemFontSize(24);

	//アンカーポイント設定
	this->setAnchorPoint(cocos2d::Point(0.0f,0.5f));

	//左寄せ
	this->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
	//位置の設定
	this->setPosition(cocos2d::Point(WINDOW_RIGHT * 0.0f, WINDOW_TOP * 0.92f));

	//自動て更新処理を呼び出す
	this->scheduleUpdate();
	return true;
}

void CScoreLabel::update(float deltaTime_)
{
	if (this->m_pStatus == NULL)
		return;

	//表示するスコアを文字列に変換
	std::string scoreStr = cocos2d::StringUtils::format("TOTAL SCORE:%d", this->m_pStatus->getScore());

	this->setString(scoreStr);

}
//=========================================================================
//　ステージ表示用のラベルクラスはここから書く
//=========================================================================
//コンストラクタ
CStageNoLabel::CStageNoLabel() {
	//ゴミ処理
	this->m_pStage = NULL;
}
//デストラクタ
CStageNoLabel::~CStageNoLabel() {

}
bool CStageNoLabel::init() {

	//=========================================================================
	//	ユーザーインターフェースの初期化に関するコードの追加はここから
	//=========================================================================
	//文字列のフォントタイプ
	this->setSystemFontName("Arial");
	//文字列のフォントサイズ
	this->setSystemFontSize(24);
	//アンカーポイント設定
	this->setAnchorPoint(cocos2d::Point(0.0f, 0.5f));

	//左寄せ
	this->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
	//位置の設定
	this->setPosition(cocos2d::Point(WINDOW_RIGHT * 0.8f, WINDOW_TOP * 0.97f));

	//自動て更新処理を呼び出す
	this->scheduleUpdate();
	return true;
}

void CStageNoLabel::update(float deltaTime_)
{
	if (this->m_pStage == NULL)
		return;

	//表示するHPを文字列に変換
	std::string stageStr = cocos2d::StringUtils::format("STAGE:%d", *this->m_pStage);

	this->setString(stageStr);

}

//=========================================================================
//　プレイヤー数表示用のラベルクラスはここから書く
//=========================================================================
//コンストラクタ
CPlayerLabel::CPlayerLabel() {
	//ゴミ処理
	this->m_pPlayer = NULL;
}
//デストラクタ
CPlayerLabel::~CPlayerLabel() {

}
bool CPlayerLabel::init() {

	//=========================================================================
	//	ユーザーインターフェースの初期化に関するコードの追加はここから
	//=========================================================================
	//文字列のフォントタイプ
	this->setSystemFontName("Arial");
	//文字列のフォントサイズ
	this->setSystemFontSize(24);
	//アンカーポイント設定
	this->setAnchorPoint(cocos2d::Point(0.0f, 0.5f));

	//左寄せ
	this->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
	//位置の設定
	this->setPosition(cocos2d::Point(WINDOW_RIGHT * 0.45f, WINDOW_TOP * 0.97f));

	//自動て更新処理を呼び出す
	this->scheduleUpdate();
	return true;
}

void CPlayerLabel::update(float deltaTime_)
{
	if (this->m_pPlayer == NULL)
		return;

	int player = *this->m_pPlayer;
	//表示するHPを文字列に変換
	player = *this->m_pPlayer == -1 ? 0 : *this->m_pPlayer;
	std::string playerStr = cocos2d::StringUtils::format("PLAYER:%d", player);

	this->setString(playerStr);

}

//=========================================================================
//　ボム数表示用のラベルクラスはここから書く
//=========================================================================
//コンストラクタ
CBomLabel::CBomLabel() {
	//ゴミ処理
	this->m_pBom = NULL;
}
//デストラクタ
CBomLabel::~CBomLabel() {

}
bool CBomLabel::init() {

	//=========================================================================
	//	ユーザーインターフェースの初期化に関するコードの追加はここから
	//=========================================================================
	//文字列のフォントタイプ
	this->setSystemFontName("Arial");
	//文字列のフォントサイズ
	this->setSystemFontSize(24);
	//アンカーポイント設定
	this->setAnchorPoint(cocos2d::Point(0.0f, 0.5f));

	//左寄せ
	this->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
	//位置の設定
	this->setPosition(cocos2d::Point(WINDOW_RIGHT * 0.65f, WINDOW_TOP * 0.97f));

	//自動て更新処理を呼び出す
	this->scheduleUpdate();
	return true;
}

void CBomLabel::update(float deltaTime_)
{
	if (this->m_pBom == NULL)
		return;

	//表示するHPを文字列に変換
	std::string bomStr = cocos2d::StringUtils::format("BOM:%d", *this->m_pBom);

	this->setString(bomStr);
}