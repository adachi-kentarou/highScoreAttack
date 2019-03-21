#ifndef __ShootingGame__Character__
#define __ShootingGame__Character__

#include "cocos2d.h"
#include "Constants.h"
#include "Data/Status/Status.h"
#include "Data/ActionController/ActionController.h"
using namespace cocos2d;
using namespace cocos2d::experimental;
//AudioEngineのインクルード
#include "audio/include/AudioEngine.h"

//=========================================================================
//	キャラクターに関するタイプなどの列挙はここから書いていく
//=========================================================================
//敵のタイプ
enum class ENEMY_TYPE :int {
	TYPE_A = 0,
	TYPE_B = 1,
	TYPE_C = 2,
	TYPE_D = 3,
	TYPE_E = 4,
	TYPE_BOSS_1 = 10,
};

//弾のタイプ
enum class BULLET_TYPE {
	//プレイヤーの弾タイプ
	//通常弾
	PLAYER_NORMAL = 0,
	//爆発
	PLAYER_EXPLOSION = 1,
	//後方弾
	PLAYER_BACK = 2,
	//レーザー弾
	PLAYER_LASER = 3,
	//誘導弾
	PLAYER_INDUCTION = 4,
	//散弾
	PLAYER_MULTIPLE = 5,
	//爆発エフェクト
	PLAYER_EXPLOSION_2 = 6,
	
	//通常弾
	//PLAYER_NORMAL = 1000,

	//2way弾
	PLAYER_2WAY,

	//3way弾
	PLAYER_3WAY,

	//敵の弾のタイプ
	//通常弾
	ENEMY_NORMAL = 2000,

	//敵の弾のタイプ
	//自機狙い弾(プレイヤー狙い弾)
	ENEMY_AIMING,

	//扇形弾(7way弾)
	ENEMY_FAN,

	//前後ショット
	ENEMY_2WAY,
};


//爆発エフェクトタイプ
enum class EFFECT_TYPE {
	EXPLOSION = 0,//爆発
	EXPLOSION_FINISH = 1,//HP0爆発
	BOM = 2,//ボム
	ALEART = 3,//アラート
	PLANET1 = 4,//惑星1
	PLANET2 = 5,//惑星2
	PLANET3 = 6,//惑星3
	PLANET4 = 7,//惑星4
	PLANET5 = 8,//惑星5
	PLANET6 = 9,//惑星6
	PLANET7 = 10,//惑星7
	PLANET8 = 11,//惑星8
	PLANET9 = 12,//惑星9
};

//アイテムタイプ
enum class ITEM_TYPE :int{
	NONE = -1,//無し
	RECOVERY = 0,//HP回復
	SPEEDUP = 1,//速度アップ
	NORMAL = 2,//ノーマル攻撃レベルアップ
	EXPLOSION = 3,//爆発攻撃レベルアップ
	BACK = 4,//後方攻撃レベルアップ
	LASER = 5,//レーザー攻撃レベルアップ
	INDUCTION = 6,//誘導攻撃レベルアップ
	MULTIPLE = 7,//散弾攻撃レベルアップ
	BOM = 8,//ボム
	ONE_UP = 9,//プレイヤー数
};

//壁タイプ
enum class WALL_TYPE :int {
	STAGE_1_1 = 0,//ステージ１
	STAGE_1_2 = 1,//ステージ２
	STAGE_2_1 = 2,//ステージ１
	STAGE_2_2 = 3,//ステージ２
	STAGE_3_1 = 4,//ステージ１
	STAGE_3_2 = 5,//ステージ２
};

/*
 *	チップクラス
 *	cocos2d::Rect を typedef して使用する
 *	typedef とは「型」を「別名の型」でも使用出来るようにする指定子
 *
 *	構文
 *		typedef 型 別名の型 ;
 *
 *	今まで通りの型でも宣言できるし、別名の型でも宣言する事ができる。
 *
 *		typedef cocos2d::Rect CRect ;
 *
 *	とすれば、
 *
 *		cocos2d::Rect body ;
 *		CRect body ;
 *
 *	の２通りで宣言する事ができる。
 */
typedef cocos2d::Rect CChip ;



//=========================================================================
//	移動用クラスのコードはここから書く
//=========================================================================
/*
移動用データクラス
*/
class CMove
{
	public:
		float m_posX;	//位置X座標
		float m_posY;	//位置Y座標
		float m_velX;	//速度X
		float m_velY;	//速度Y
		/*
		*@desc	位置の設定
		*@param	X座標
		*@param	Y座標
		*/
		void setPos(float posX,float posY)
		{
			m_posX = posX;
			m_posY = posY;
		}
		/*
		*@desc	速度の設定
		*@param	速度X
		*@param	速度Y
		*/
		void setVel(float velX,float velY)
		{
			m_velX = velX;
			m_velY = velY;
		}
		/*
		*@desc	速度による移動
		*/
		void moveByVell()
		{
			//次の位置　＝　現在の位置　＋　移動する量
			m_posX = m_posX + m_velX;
			m_posY = m_posY + m_velY;
		}

};

//=========================================================================
//	アニメーション用クラスのコードはここから書く
//=========================================================================
class CAnimation {
public:
	int m_counter;//カウンター
	int m_interval;//切り替え間隔
	int m_number;//アニメーション枚数
	
	//アニメーションが終了したかどうかのフラグ
	//true...終了した
	bool m_isEnd;

	//ループするかどうかのフラグ
	//true...ループする
	bool m_isLoop;

	CAnimation() {
		//アニメーションが終了したかどうかのフラグの初期化
		this->m_isEnd = false;
	}
	/**
	*@desc 設定用
	*@param 切り替え間隔
	*@param アニメーション枚数
	*@param true...ループする false...ループしない
	*/
	void set(int interval,int number,bool isLoop = true) {
		this->m_counter = 0;
		this->m_interval = interval;
		this->m_number = number;
		this->m_isLoop = isLoop;
	}

	/**
	*@desc アニメーションの更新処理
	*@return 表示するフレーム数
	*/
	int update() {
		if (this->m_isEnd == false) {
			this->m_counter++;
			//カウンターの数がアニメーションさせる枚数以上になったらカウンターをリセットする
			if (this->m_counter >= this->m_interval * this->m_number) {
				if (this->m_isLoop == true) {
					//ループするアニメーションはカウンターをリセットする
					this->m_counter = 0;
				}
				else {
					//アニメーションが終了したかどうかのフラグに対してtrueを入れる
					this->m_isEnd = true;

					//ループしないアニメーションに対しては飛び出たカウンターをデクリメントする
					this->m_counter--;
				}

			}

			//表示するフレーム数
			int frame = this->m_counter / this->m_interval;
			return frame;
		}
	}
};


//=========================================================================
//	衝突判定用クラスのコードはここから書く
//=========================================================================
class CBody {
public:
	float m_left;//左の位置
	float m_top;//上の位置
	float m_right;;//右の位置
	float m_bottom;//下の位置
	  //コンストラクタ
	CBody() {}
	/**
	*desc 設定用
	*@param 左の設定
	*@param 上の設定
	*@param 右の設定
	:@param 下の設定
	*/
	void set(float left,float top,float right,float bottom) {
		this->m_left = left;
		this->m_top = top;
		this->m_right = right;
		this->m_bottom = bottom;
	}

	/**
	*@desc 衝突判定
	*@param 衝突をしてくる対象のデータ
	*@return true 衝突している　false 衝突していない
	*@tips 自分thisというのが衝突される対象
	/*引数の対象pBodyというのが衝突してくる対象
	*/

	bool collision(CBody* pBody) {
		//自分の右側と対象の左側と自分の左側と対象の右側
		if (this->m_right > pBody->m_left && this->m_left < pBody->m_right) {
			//自分の上側と対象の下側と自分の下側と対象の上側
			if (this->m_top > pBody->m_bottom && this->m_bottom < pBody->m_top){
				//重なった(衝突している)
				return true;
			}
		}
		//衝突していない
		return false;
	}

	/**
	*@desc 位置を反映した衝突判定のデータを取得
	*@param 位置X
	*@param 位置Y
	*@return 位置を反映した衝突判定用データ
	*/
	CBody getApplyPositionBody(float posX,float posY) {
		//新しく衝突判定用データを生成
		CBody body;

		//衝突判定を行う大きさに位置を反映
		body.set(
			posX + this->m_left,
			posY + this->m_top,
			posX + this->m_right,
			posY + this->m_bottom
			);
		return body;
	}
};



class CBullet;

/*
 *
 *	プレイヤーキャラクタークラス
 *
 *		cocos2d::Sprite クラスを継承して使用している
 *		インスタンスを生成する際は 静的メンバ関数 create を使用できるが
 *		引数無しの create しか用意されていないので注意
 *
 */
class CPlayerCharacter : public cocos2d::Sprite {
public:

	//=========================================================================
	//	ここからは理解出来るまでは変更禁止
	//=========================================================================
	
	// コンストラクタの宣言
	CPlayerCharacter() ;
	// デストラクタの宣言
	~CPlayerCharacter() ;
	
	CREATE_FUNC( CPlayerCharacter ) ;
	
	/**
	 *	@desc	初期化処理
	 */
	virtual bool init() override ;
	
	/**
	*@desc プレイヤーの弾を発射
	*@param 弾タイプ
	*@param 修正位置X
	*@param 修正位置Y
	*@param 速度X
	*@param 速度Y
	*/
	CBullet* shotBullet(BULLET_TYPE type, float fixX, float fixY, float velX, float velY);

	//=========================================================================
	//	ここまでは理解出来るまでは変更禁止
	//=========================================================================
	
public:

	//=========================================================================
	//	メンバ宣言
	//		メイン内で使用するメンバはここ以降に記述していく
	//=========================================================================
	
	// 移動用データ
	CMove m_move;
	// チップデータ
	CChip m_chip;
	// アニメーションデータ
	CAnimation m_anime;

	// 衝突判定用データ
	CBody m_body;

	// 有効フラグ
	bool m_activeFlag;
	//弾発射用カウンター
	int m_shotCounter;

	//弾発射間隔
	int m_shotInterval;

	//弾攻撃力
	float m_shotPower;

	//弾移動量
	float m_shotVel;

	//弾パラメータ
	float m_shotParam;
	
	// 移動に関するメンバ関数宣言
	void moveFunc();
	// アニメーションに関するメンバ関数宣言
	void animationFunc();
	// 画面端判定に関するメンバ関数宣言
	void endOfScreen();
	// 値の反映に関するメンバ関数宣言
	void applyFunc();
	
	//プレイヤー効果音
	int m_bgmid;

	//ステータス
	CStatus m_status;

	/**
	*@desc 相手の攻撃が自身にあたった
	*@param 衝突してきた相手のステータスのアドレス
	*/
	void hits(CStatus* pStatus);
};



//=========================================================================
//	バレット ( 弾 ) のクラスはここから書く
//=========================================================================
class CBullet : public cocos2d::Sprite {
public:
	//=====================================================================
	//ここからは理解できるまでは変更禁止
	//=====================================================================

	//コンストラクタの宣言
	CBullet();

	//デストラクタの宣言
	~CBullet();

	CREATE_FUNC(CBullet);
	/*
	*@desc 初期化処理
	*/
	virtual bool init() override;
	//=====================================================================
	//ここまで理解できるまでは変更禁止
	//=====================================================================

public:
	//=====================================================================
	//メンバ宣言　メイン内で使用するメンバはここ以降に記述していく
	//=====================================================================

	//移動用データ
	CMove m_move;

	//プレイヤーキャラクター移動データ
	CMove* m_pmove;

	//チップデータ
	CChip m_chip;

	//アニメーションデータ
	CAnimation m_anime;

	//プレイヤーの弾の発射できる最大数
	static const int MAX_BULLET = 200;

	//有効フラグ(falseでレイヤーから取り外される)
	bool m_activeFlag;
	
	// 移動に関するメンバ関数宣言
	void moveFunc();
	// 画面端判定に関するメンバ関数宣言
	void endOfScreen();
	// 値の反映に関するメンバ関数宣言
	void applyFunc();
	//アニメーションに関するメンバ関数
	void CBullet::animationFunc();
	//弾タイプ
	BULLET_TYPE m_bulletType;
	//衝突判定用データ
	CBody m_body;

	//ステータス
	CStatus m_status;

	//削除在りフラグ
	bool m_delflg = false;

	//カウント
	int m_count = 0;
	//最大カウント
	int m_maxCount = 0;

	//誘導弾モード true...ターゲット選択 false...追尾
	bool mode = true;

	//ターゲット
	int target = -1;

	//弾とターゲットの距離 初回必ず登録するために初期値は巨大
	float distance = 1000000.0f;

	//回転角度
	float rotation = 0;

	//パラメータ
	float param = 0;

	//移動距離
	float vel = 0;

};

//=========================================================================
//	敵のクラスはここから書く
//=========================================================================
class CEnemyAction {
public:
	float x = 0;
	float y = 0;
	int frame = 0;
};
class CEnemyCharacter :public cocos2d::Sprite {
public:
	//===========================================
	//ここからは理解できるまでは変更禁止
	//===========================================
	//コンストラクタの宣言
	CEnemyCharacter();
	//デストラクタの宣言
	~CEnemyCharacter();

	CREATE_FUNC(CEnemyCharacter);
	/*
	*@desc 初期化処理
	*/
	virtual bool init() override;
	//===========================================
	//ここまで理解できるまでは変更禁止
	//===========================================
	
public:
	//===========================================
	//メンバ宣言
	//メイン内で使用するメンバはここ以降に記述していく
	//===========================================
	static const int MAX_ENEMY = 100;

	//移動用データ
	CMove m_move;

	//チップデータ
	CChip m_chip;

	//アニメーションデータ
	CAnimation m_anime;

	//有効フラグ(false...レイヤーから取り外される)
	bool m_activeFlag;

	//移動に関するメンバ関数宣言
	void moveFunc();

	//アニメーションに関するメンバ関数宣言
	void animationFunc();

	//画面端判定に関するメンバ関数宣言
	void endOfScreen();

	//値の繁栄に関するメンバ関数宣言
	void applyFunc();

	//敵のタイプ
	ENEMY_TYPE e_enemyType;

	/**
	*@desc プレイヤーの弾を発射
	*@param 弾タイプ
	*@param 修正値X
	*@param 修正値Y
	*@param 速度X
	*@param 速度Y
	*/
	CBullet* shotBullet(BULLET_TYPE type,float fixX,float fixY,float velX,float velY);

	//衝突判定用データ
	CBody m_body;

	//発射する弾のタイプ
	BULLET_TYPE m_bulletType;

	//敵効果音
	int m_bgmid;

	//ステータス
	CStatus m_status;

	/**
	*@desc 相手の攻撃が自身にあたった
	*@param 衝突してきた相手のステータスのアドレス
	*/
	void hits(CStatus* pStatus);

	//行動に関するメンバ関数の宣言
	void actionFunc();

	//行動タイプ
	ACTION_TYPE m_actionType;

	//発射フラグ
	bool m_shotFlag = false;

	//現在の行動ステップ
	int m_actionStep = 0;

	//所持アイテム
	ITEM_TYPE m_item = ITEM_TYPE::NONE;

	//移動データ
	std::vector<CEnemyAction> action;

	//アクションフレームカウント
	int actionCount = -1;

	//ショットカウント
	int shotCount = 0;

	//進行方向　true...左　false...右
	bool direction;

	//砲身
	Sprite* m_pChr;

	//回転角度
	float rotation = 0;

	//弾ｘ座標補正
	float fixX = 0;

	//弾ｙ座標補正
	float fixY = 0;

	//弾半径補正
	float fixR = 0;

	//ボスフラグ
	bool bossflg = false;

	//ボスカウント用
	int bossCount = 0;
	
};


//=========================================================================
//	エフェクトのクラスはここから書く
//=========================================================================
class CEfect : public cocos2d::Sprite {
public:
	static const int MAX_EFFECT = 100;

	// コンストラクタの宣言
	CEfect();
	// デストラクタの宣言
	~CEfect();

	CREATE_FUNC(CEfect);

	/**
	*	@desc	初期化処理
	*/
	virtual bool init() override;

public:
	//=====================================================================
	//メンバ宣言　メイン内で使用するメンバはここ以降に記述していく
	//=====================================================================

	//移動用データ
	CMove m_move;

	//チップデータ
	CChip m_chip;

	//アニメーションデータ
	CAnimation m_anime;

	//有効フラグ(falseでレイヤーから取り外される)
	bool m_activeFlag;

	//エフェクトタイプ
	EFFECT_TYPE type;

	// 移動に関するメンバ関数宣言
	void moveFunc();
	// アニメーションに関するメンバ関数宣言
	void animationFunc();
	// 値の反映に関するメンバ関数宣言
	void applyFunc();
	//画面端判定に関するメンバ関数宣言
	void endOfScreen();
	//集合のX最大数
	int maxX = 10000;

};

//=========================================================================
//	アイテムのクラスはここから書く
//=========================================================================
class CItem : public cocos2d::Sprite {
public:
	static const int MAX_ITEM = 100;

	// コンストラクタの宣言
	CItem();
	// デストラクタの宣言
	~CItem();

	CREATE_FUNC(CItem);

	/**
	*	@desc	初期化処理
	*/
	virtual bool init() override;

public:
	//=====================================================================
	//メンバ宣言　メイン内で使用するメンバはここ以降に記述していく
	//=====================================================================

	//移動用データ
	CMove m_move;

	//チップデータ
	CChip m_chip;

	//アニメーションデータ
	CAnimation m_anime;

	//有効フラグ(falseでレイヤーから取り外される)
	bool m_activeFlag;

	//アイテムタイプ
	ITEM_TYPE type;

	// 移動に関するメンバ関数宣言
	void moveFunc();
	// アニメーションに関するメンバ関数宣言
	void animationFunc();
	// 値の反映に関するメンバ関数宣言
	void applyFunc();
	//画面端判定に関するメンバ関数宣言
	void endOfScreen();



	//衝突判定用データ
	CBody m_body;
	/**
	*@desc 相手の攻撃が自身にあたった
	*@param 衝突してきた相手のステータスのアドレス
	*/
	void hits(CStatus* pStatus);

	//アイテム取得効果音
	int m_bgmid;

	//メインの攻撃レベルラベル取得用
	static cocos2d::Label** pweponLevelLavel;
};

//=========================================================================
//	カーソルのクラスはここから書く
//=========================================================================
class CCursor : public cocos2d::Sprite {
public:
	// コンストラクタの宣言
	CCursor();
	// デストラクタの宣言
	~CCursor();

	CREATE_FUNC(CCursor);

	/**
	*	@desc	初期化処理
	*/
	virtual bool init() override;

public:
	//=====================================================================
	//メンバ宣言　メイン内で使用するメンバはここ以降に記述していく
	//=====================================================================

	//移動用データ
	CMove m_move;

	//チップデータ
	CChip m_chip;

	//アニメーションデータ
	CAnimation m_anime;

	// 移動に関するメンバ関数宣言
	void moveFunc();
	// アニメーションに関するメンバ関数宣言
	void animationFunc();
	// 値の反映に関するメンバ関数宣言
	void applyFunc();
	
	//カーソルのX最大
	int p_maxX;
	//カーソルのY最大
	int p_maxY;
	//カーソルのX位置
	int p_x;
	//カーソルのY位置
	int p_y;
	//カーソルのX座標
	float p_xPoint;
	//カーソルのY座標
	float p_yPoint;
	//アニメーション数
	int p_animation;
	//アニメーションフレーム数
	int p_animeFrame;
	//X移動サイズ
	float p_moveX;
	//Y移動サイズ
	float p_moveY;
	//移動フレーム
	int p_moveFrame;
	//横ループ
	bool p_xLoop;
	//縦ループ
	bool p_yLoop;
	//低速待ちフレーム
	int p_slowWait;
	//高速待ちフレーム
	int p_fastWait;
	//初回入力待ちフレーム
	int p_inputWait = 10;

	//カウントフレーム
	int p_countFrame = 0;
	//待ちフレーム
	int p_wait;

	//初回プッシュフラグ　true...初回 false...初回以降
	bool p_fastPush = true;
	//移動速度フラグ　true...低速 false...高速
	bool p_speed = true;
	//処理分岐　0...入力待ち 1...入力検知待ち 2...移動中
	int p_input = 0;

	//移動前カーソル位置
	//移動前カーソルのX位置
	int p_beforeX;
	//移動前カーソルのY位置
	int p_beforeY;
	//移動カウント
	int p_moveCount;
	//移動終了フラグ
	bool moveflg = false;

	/*
	*@desc カーソル初期設定
	*@param ファイル名
	*@param チップX座標
	*@param チップY座標
	*@param チップXサイズ
	*@param チップYサイズ
	*@param アニメーション数
	*@param アニメーションフレーム数
	*@param カーソルのX最大
	*@param カーソルのY最大
	*@param カーソルのX位置
	*@param カーソルのY位置
	*@param カーソルのX座標
	*@param カーソルのY座標
	*@param X移動サイズ
	*@param Y移動サイズ
	*@param X移動フレーム
	*@param Y移動フレーム
	*@param 横ループ
	*@param 縦ループ
	*@param 低速待ちフレーム
	*@param 低速待ちフレーム
	*/
	void set(
		char* p_fileName,//ファイル名
		int p_chipPointX,//チップX座標
		int p_chipPointY,//チップY座標
		int p_chipX,	//チップXサイズ
		int p_chipY,	//チップYサイズ
		int p_animation,//アニメーション数
		int p_animeFrame,//アニメーションフレーム数
		int p_maxX,		//カーソルのX最大
		int p_maxY,		//カーソルのY最大
		int p_x,		//カーソルのX位置
		int p_y,		//カーソルのY位置
		float p_xPoint,	//カーソルのX座標
		float p_yPoint,	//カーソルのY座標
		float p_moveX,	//X移動サイズ
		float p_moveY,	//Y移動サイズ
		int p_moveFrame,//移動フレーム
		bool p_xLoop,	//横ループ
		bool p_yLoop,	//縦ループ
		int p_slowWait,	//低速待ちフレーム
		int p_fastWait	//高速待ちフレーム
	);

	void inputFunc();
};

//=========================================================================
//	壁のクラスはここから書く
//=========================================================================
class CWall : public cocos2d::Sprite {
public:
	static const int MAX_WALL = 200;

	// コンストラクタの宣言
	CWall();
	// デストラクタの宣言
	~CWall();

	CREATE_FUNC(CWall);

	/**
	*	@desc	初期化処理
	*/
	virtual bool init() override;

public:
	//=====================================================================
	//メンバ宣言　メイン内で使用するメンバはここ以降に記述していく
	//=====================================================================

	//移動用データ
	CMove m_move;

	//チップデータ
	CChip m_chip;

	//アニメーションデータ
	CAnimation m_anime;

	//有効フラグ(falseでレイヤーから取り外される)
	bool m_activeFlag;

	//アイテムタイプ
	WALL_TYPE type;

	//ステータス
	CStatus m_status;

	// 移動に関するメンバ関数宣言
	void moveFunc();
	// アニメーションに関するメンバ関数宣言
	void animationFunc();
	// 値の反映に関するメンバ関数宣言
	void applyFunc();
	//画面端判定に関するメンバ関数宣言
	void endOfScreen();

	//効果音
	int m_bgmid;

	//衝突判定用データ
	CBody m_body;
	/**
	*@desc 相手の攻撃が自身にあたった
	*@param 衝突してきた相手のステータスのアドレス
	*/
	void hits(CStatus* pStatus);

	//壁の縁
	Sprite* m_pWall_left;
	Sprite* m_pWall_right;
	Sprite* m_pWall_top;
	Sprite* m_pWall_bottom;

};
#endif  defined(__ShootingGame__Character__) 
