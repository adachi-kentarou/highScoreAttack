
#ifndef ShootingGame_ActionController_h
#define ShootingGame_ActionController_h
//アクションタイプ
enum class ACTION_TYPE {
	NONE = -1,	//行動無し
	ZIGZAG,		//ジグザグ
	STRAIGHT,	//直進行動
	CONVEX,		//凸行動
	ORIGINAL,	//オリジナル
	ORIGINAL2,	//オリジナル
	BOSS_1,		//ボス１
};
//CEnemyCharacterクラスを前方宣言
class CEnemyCharacter;

//=========================================================================
//　行動管理のクラスはここから書く
//=========================================================================
/**
*ジグザグ行動
*/
class CActionControllerZigZag {
public:
	//アクションタイプ
	ACTION_TYPE m_actionType;

	//コンストラクタ
	CActionControllerZigZag();

	/*
	*@desc 行動処理
	*@param この行動を行う敵キャラのアドレス
	*/
	void actionFunc(CEnemyCharacter* pEne);
};

/**
*直進行動
*直進行動中に弾を2発発射
*/
class CActionControllerStraight {
public:
	//アクションタイプ
	ACTION_TYPE m_actionType;

	//コンストラクタ
	CActionControllerStraight();

	/*
	*@desc 行動処理
	*@param この行動を行う敵キャラのアドレス
	*/
	void actionFunc(CEnemyCharacter* pEne);
};

/**
*凸行動
*/
class CActionControllerConvex {
public:
	//アクションタイプ
	ACTION_TYPE m_actionType;

	//コンストラクタ
	CActionControllerConvex();

	/*
	*@desc 行動処理
	*@param この行動を行う敵キャラのアドレス
	*/
	void actionFunc(CEnemyCharacter* pEne);
};

/**
*オリジナル
*/
class CActionControllerOriginal {
public:
	//アクションタイプ
	ACTION_TYPE m_actionType;

	//コンストラクタ
	CActionControllerOriginal();

	/*
	*@desc 行動処理
	*@param この行動を行う敵キャラのアドレス
	*/
	void actionFunc(CEnemyCharacter* pEne);
};
class CActionControllerOriginal2 {
public:
	//アクションタイプ
	ACTION_TYPE m_actionType;

	//コンストラクタ
	CActionControllerOriginal2();

	/*
	*@desc 行動処理
	*@param この行動を行う敵キャラのアドレス
	*/
	void actionFunc(CEnemyCharacter* pEne);
};

/**
*ボス
*/
class CActionControllerBoss {
public:
	//アクションタイプ
	ACTION_TYPE m_actionType;

	//コンストラクタ
	CActionControllerBoss();

	/*
	*@desc 行動処理
	*@param この行動を行う敵キャラのアドレス
	*/
	void actionFunc(CEnemyCharacter* pEne);
};
#endif