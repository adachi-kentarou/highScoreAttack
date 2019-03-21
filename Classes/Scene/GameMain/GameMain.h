
#ifndef __ShootingGame__Main__
#define __ShootingGame__Main__

#include "cocos2d.h"
#include "Constants.h"

//=========================================================================
//	追加のインクルードはここから
//=========================================================================
#include "Model/Character/Character.h"
#include "Data/EnemyLaunchData/EnemyLaunchData.h"
#include "Model/UserInterface/UserInterface.h"
#include "Model/Map/Map.h"
#include "Data/MapData/MapData.h"
#include "Scene/Title/Title.h"
#include "Scene/StageTitle/StageTitle.h"
#include "Scene/Replay/Replay.h"
#include "Scene/ReplaySelect/ReplaySelect.h"

//#include "Data/GameData/GameData.h"
//=========================================================================
//ステージに関する列挙などはここから
//=========================================================================
enum class STAGE_MODE {
	//ステージモード無し
	NONE = -1,
	//ステージ開始処理
	START,
	//ステージ更新処理中
	UPDATE,
	//ステージ終了処理
	END,
	//ステージ一時停止中
	PAUSE,
	//ゲームオーバー一時停止中
	GAME_OVER,

};

/*
 *	ゲームメインレイヤー
 *
 *		ゲームのメインとなるレイヤー
 *		初めはこの部分に全てを書いていく
 *
 */
class CGameMain : public cocos2d::Layer
{
public:
	//=========================================================================
	//	ここからは理解出来るまでは変更禁止
	//=========================================================================

	// デストラクタ
	~CGameMain() ;
	
	/**
	 *	@desc	シーンの生成
	 *	@return	CMain レイヤーを内包したシーンクラスインスタンス
	 *	@tips	静的メンバ関数
	 */
    static cocos2d::Scene* createScene() ;
	
	/*
	 *	@desc	シーン生成時に初期化関数を処理
	 *			初期化関数失敗時は NULL を返す
	 */
    CREATE_FUNC( CGameMain );
	
	/**
	 *	@desc	キーボードのキーを押した際のイベント
	 *	@param	キーコード
	 *	@param	イベント
	 */
	virtual void onKeyPressed( cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event ) override ;
	
	/**
	 *	@desc	キーボードのキーを離した際のイベント
	 *	@param	キーコード
	 *	@param	イベント
	 */
	virtual void onKeyReleased( cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event ) override ;
	
	/**
	 *	@desc	初期化
	 *	@return	true...成功	false...失敗
	 */
    virtual bool init() override ;
	
	/**
	 *	@desc	更新処理
	 *	@param	経過時間
	 */
	virtual void update( float deltaTime_ ) override ;
	
	/**
	*@desc トランジション終了処理
	*/
	void onEnterTransitionDidFinish()override;

	//=========================================================================
	//	ここまでは理解出来るまでは変更禁止
	//=========================================================================
	
public:

	//=========================================================================
	//	メンバ宣言
	//		メイン内で使用するメンバはここ以降に記述していく
	//=========================================================================
	
	// プレイヤーキャラクター
	static CPlayerCharacter* m_pPlayerChara;
	// 敵キャラクター
	static CEnemyCharacter* m_pEnemyCharas[CEnemyCharacter::MAX_ENEMY];
	// プレイヤーバレット ( プレイヤーの弾 )
	CBullet* m_pPlayerBullets[CBullet::MAX_BULLET];

	// エネミーバレット ( 敵の弾 )
	CBullet* m_pEnemyBullets[CBullet::MAX_BULLET];
	
	
	// プレイ中入力に関するメンバ関数
	void inputFunc();
	// ポーズ中入力に関するメンバ関数
	void inputFunc2();
	// 敵の出撃
	//敵出撃データ
	//CEnemyLaunchData m_enemyLaunchData[CEnemyLaunchData::MAX_LAUNCH];
	CEnemyLaunchData* m_pEnemyLaunchData;

	// 移動に関するメンバ関数
	void moveFunc();
	// プレイヤーと敵の弾の衝突
	void collisionPlayerAndEnemyBullets();
	// プレイヤーと敵の衝突
	void collisionPlayerAndEnemies();
	// 敵とプレイヤーの弾の衝突
	void collisionEnemiesAndPlayerBullets();
	// アニメーションに関するメンバ関数
	void animationFunc();
	// 画面端判定に関するメンバ関数
	void endOfScreen();
	// 値の反映に関するメンバ関数
	void applyFunc();
	
	//敵の出撃
	//敵を出撃させるかどうがのチェック
	void checkLaunchEnemy();

	//敵出現予告のチェック
	void checkEnemyAleart();

	/**
	*@desc 敵の出撃
	*@param 参照する管理データのアドレス
	*/
	CEnemyCharacter* launchEnemy(CEnemyLaunchData* pEneLaunchData);
	//CEnemyCharacter* launchEnemy(ENEMY_TYPE type, float posX, float posY);
	//取り外し処理
	void checkActiveFlagAndRemove();

	//敵の弾の発射
	void shotEnemyBullet();
	//プレイヤーの弾の発射
	/*
	*@desc	プレイヤーの弾の発射
	*@param	弾タイプ
	*/
	void shotPlayerBullet(BULLET_TYPE type);
	
	//現在何番目の出撃データを調べているのかの番号
	int m_enemyLaunchIndex;

	//現在何番目の出撃データを調べているのかの番号
	int m_enemyAleartIndex;

	//フレームカウンター
	static int m_frameCounter;

	//エフェクト配列
	CEfect* m_pEffects[CEfect::MAX_EFFECT];

	//エフェクトの出現
	/**
	*@desc エフェクトの出現
	*@param エフェクトタイプ
	*@param 出現位置X
	*@param 出現位置Y
	*@return エフェクトクラスのポインタ
	*/
	CEfect* launchEffect(EFFECT_TYPE type,float posX,float posY);

	//BGMの識別ID
	int m_bgmid;

	//HPラベル
	CHpLabel* m_pHpLabel;

	//HPゲージ
	CHpGuage* m_pHpGuage;

	//スコアラベル
	CScoreLabel* m_pScoreLabel;
	
	//ステージラベル
	CStageNoLabel* m_pStageLabel;

	//プレイヤー数ラベル
	CPlayerLabel* m_pPlayerLabel;

	//ボム数ラベル
	CBomLabel* m_pBomLabel;

	//ジグザグの行動管理
	CActionControllerZigZag m_actCtrlZigZag;
	//直進行動管理
	CActionControllerStraight m_actCtrlStraight;
	//凸行動管理
	CActionControllerConvex m_actCtrlConvex;
	//オリジナル行動管理
	CActionControllerOriginal m_actCtrlOriginal;
	CActionControllerOriginal2 m_actCtrlOriginal2;
	//ボス行動管理
	CActionControllerBoss m_actCtrlBoss;

	// 行動処理に関するメンバ関数
	void actionFunc();

	//プレイヤーとアイテムの衝突判定
	void collisionPlayerAndItems();

	//アイテム配列
	CItem* m_pItems[CItem::MAX_ITEM];

	/**
	*@desc アイテムの出現
	*@param アイテムタイプ
	*@param 出現位置X
	*@param 出現位置Y
	*@return アイテムクラスのポインタ
	*/
	CItem* launchItem(ITEM_TYPE type, float posX, float posY);

	//マップ
	CMap* m_pMap = NULL;

	STAGE_MODE m_stageMode = STAGE_MODE::NONE;

	//ステージ開始処理
	void stageStartFunc();
	/**
	*@desc ステージ更新処理
	*@param 経過時間
	*/
	void stageUpdateFunc(float deltaTime_);
	void stagePauseFunc();
	void gameOverFunc();

	//ステージ開始処理
	void stageEndFunc();

	//aキー多重判定防止フラグ(押されていたらtrue)
	bool m_aKeyDownFlag = false;
	//sキー多重判定防止フラグ(押されていたらtrue)
	bool m_sKeyDownFlag = false;
	//zキー多重判定防止フラグ(押されていたらtrue)
	bool m_zKeyDownFlag = true;
	//xキー多重判定防止フラグ(押されていたらtrue)
	bool m_xKeyDownFlag = false;
	//spaceキー多重判定防止フラグ(押されていたらtrue)
	bool m_spaceKeyDownFlag = false;

	//ステージ最大数
	static const int MAX_STAGE_COUNT = 3;

	//現在のステージ番号(ステージは１から)
	static int m_stageNo;


	//音楽エンジン終了フラグ
	bool audioFlug = true;
	//インターフェースレイヤー
	cocos2d::Layer* m_interFaceLayer;
	//キャラクターレイヤー
	cocos2d::Layer* m_characterLayer;
	//背景レイヤー
	cocos2d::Layer* m_backGroundLayer;
	//壁レイヤー
	cocos2d::Layer* m_wallLayer;

	static void call_back(bool a);

	//カーソル
	CCursor* m_pCursor;
	//カーソル用フレームカウンター
	int c_frameCounter = 0;

	//ラベル用配列
	cocos2d::Label* pLavelArray[10];

	//点滅フラグ
	bool flashingflg = false;
	//点滅回数
	int flashing = 0;

	//zボタン押しフラグ true...押されてる false...押されてない
	bool p_zFlg = false;

	//left_shiftボタン押しフラグ true...押されてる false...押されてない
	bool p_left_shiftFlg = false;

	//カーソル移動量
	int change = 0;

	//ボタン決定フラグ
	bool p_scene = false;

	//攻撃タイプ表示ラベル用配列
	cocos2d::Label* pweponLavel[6];

	//攻撃タイプレベル表示ラベル用配列
	cocos2d::Label* pweponLevelLavel[6];

	//攻撃タイプレベル用配列
	static int pweponLevel[6];

	//攻撃タイプ別レベル別攻撃力　1次配列...攻撃タイプ　2次...レベル
	float pweponPower[6][10] = {
		{ 10,10,10,10,10,10,10,10,10,10 },	//NORMAL
		{ 1,1,1,1,1,1,1,1,1,1 },	//EXPLOSION
		{ 10,10,10,10,10,10,10,10,10,10 },	//BACK
		{ 10,10,10,10,10,10,10,10,10,10 },	//LASER
		{ 10,10,10,10,10,10,10,10,10,10 },	//INDCTION
		{ 10,10,10,10,10,10,10,10,10,10 }		//MULTIPLE
	};

	//攻撃タイプ別レベル別攻撃間隔　1次配列...攻撃タイプ　2次...レベル
	int pweponInterval[6][10] = {
		{ 5,5,5,5,5,5,5,5,5,5 },	//NORMAL
		{ 10,10,10,10,10,10,10,10,10,10 },	//EXPLOSION
		{ 5,5,5,5,5,5,5,5,5,5 },	//BACK
		{ 5,5,5,5,5,5,5,5,5,5 },	//LASER
		{ 5,5,5,5,5,5,5,5,5,5 },	//INDCTION
		{ 5,5,6,6,7,7,8,8,9,9 }		//MULTIPLE
	};

	//攻撃タイプ別レベル別攻撃パラメータ　1次配列...攻撃タイプ　2次...レベル
	float pweponParam[6][10] = {
		{ 0,0,0,0,0,0,0,0,0,0 },	//NORMAL
		{ 1,1.1f,1.2f,1.3f,1.4f,1.5f,1.6f,1.7f,1.8f,1.9f },	//EXPLOSION 爆発サイズ倍率
		{ 0,0,0,0,0,0,0,0,0,0 },	//BACK
		{ 0,0,0,0,0,0,0,0,0,0 },	//LASER
		{ 2,2.25f,2.5f,2.75f,3,3.25f,3.5f,3.75f,4,4.25f },	//INDCTION 回転移動量
		{ 2,2,3,3,4,4,5,5,6,6 }		//MULTIPLE 発射方向数
	};

	//攻撃タイプ別レベル別攻撃移動量　1次配列...攻撃タイプ　2次...レベル
	float pweponVel[6][10] = {
		{ 6,6,6,6,6,6,6,6,6,6 },	//NORMAL
		{ 6,6,6,6,6,6,6,6,6,6 },	//EXPLOSION
		{ 6,6,6,6,6,6,6,6,6,6 },	//BACK
		{ 6,6,6,6,6,6,6,6,6,6 },	//LASER
		{ 6,6,6,6,6,6,6,6,6,6 },	//INDCTION
		{ 6,6,6,6,6,6,6,6,6,6 }		//MULTIPLE
	};
	//デバッグ用ラベル用配列
	cocos2d::Label* dbgLavel[6];


	//攻撃選択 0:通常 1:爆発 2:後方 3:レーザー 4:誘導 5;エネルギー
	static int weponSelect;

	//スコア計算
	void calculationScore(int j);

	//爆発エフェクト
	void createEffect(int j);

	//レーザーフラグ
	bool laserFlg = false;

	//レーザーカウンター
	int laserCounter = 0;
	//レーザーインデックス
	int laserIndex;
	//プレイヤーとアイテムの衝突判定
	void collisionPlayerAndWalls();

	//壁配列
	CWall* m_pWalls[CWall::MAX_WALL];

	/**
	*@desc 壁の出現
	*@param 壁タイプ
	*@param 出現位置X
	*@param 出現位置Y
	*@return 壁クラスのポインタ
	*/
	CWall* launchWall(WALL_TYPE type, float posX, float posY);

	//オブジェクトカウント用
	//敵キャラカウント
	static int m_pEnemyCount;
	//プレイヤー弾カウント
	static int m_pPlayerBulletCount;
	//敵弾カウント
	static int m_pEnemyBulletCount;
	//エフェクトカウント
	static int m_pEfectCount;
	//アイテムカウント
	static int m_pItemCount;
	//壁カウント
	static int m_pWallCount;

	//壁の移動スピード
	float WALL_SPEED = MapData::WALL_SPEED;
	//壁フレームカウント
	float m_wallCounter;
	//現在の壁の表示x座標
	int m_pWallXpos;
	//壁を出現させるかのチェック
	void checkLaunchWall();
	// 壁とプレイヤーの弾の衝突
	void collisionWallsAndPlayerBullets();
	// 壁と敵の弾の衝突
	void collisionWallsAndEnemyBullets();
	//壁衝突エフェクト
	void createEffect2(int j,float x,float y);

	//復活フラグ
	bool resurrection = false;
	//復帰カウント
	int resCount = 0;

	//プレイヤー数
	static int playerCount;

	//ボムカウント
	int bomCount = 0;
	//ボム数
	static int bom;
	//プレイモード 0...play 1...pause 2...replay 3...replay*2
	static int mode;

	//ゲームモード別敵の弾速度補正
	const float m_shotVel[3] = { 0.6f,0.8f,1.0f };
	//ゲームモード別敵の弾攻撃力補正
	const float m_shotAttack[3] = { 2.0f,1.0f,0.0f };

	//マップデータ作成用
	MapData m_pMapData;
	//マップ生成シード値
	int mapSeed;

	//サウンドディレイ
	int soundDeray;

	//当たり判定方向判定フラグ
	bool colDir = true;

	//ステージクリアフレーム
	int m_clearFrame = 10000;

	//プレイヤーキャラクターステータス
	static int m_hp;
	static int m_maxHp;
	static int m_attackPt;
	static int m_score;
	static int m_speed;

	//リプレイデータ取り出し用
	int playerData;

	//デモ開始までのSEフラグ
	bool se_flg = true;
	//デモプレイラベル
	cocos2d::Label* pLavelDemo;

	//背景の星を出現させるかチェック
	void checkLaunchPlanet();
	//星出現フレーム
	int m_planetFrame;



};

#endif  defined(__ShootingGame__Main__)
