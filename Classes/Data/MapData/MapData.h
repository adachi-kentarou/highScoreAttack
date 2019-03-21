#pragma once
#ifndef __ShootingGame__MapData__
#define __ShootingGame__MapData__
#include <stdlib.h>
#include <time.h>
#include "Data/EnemyLaunchData/EnemyLaunchData.h"


class MapData {
public:
	//全体マップサイズ
	static const int MAX_MAP_DATA_X = 100;
	static const int MAX_MAP_DATA_Y = 14;

	static float WALL_SPEED;

	/*
	* @desk マップチップデータ
	*/
	struct chipData {
		//マップチップパターン
		int m_mapChipPatern = 0;
		//エリア
		int m_area;
		//前移動先順位
		int m_frontRank = 0;
		//後移動先順位
		int m_backRank = 0;
		//test
		int m_test = 0;
	};
	/*
	* @desk チップポジションデータ
	*/
	struct chipPos {
		//x座標
		int x;
		//y座標
		int y;
	};

	/*
	*@desc チップ作成
	@param x座標
	@param y座標
	*/
	chipPos createChip(int x,int y);
	
	//チップポジション要素数
	int indexChipPos;
	//チップポジション配列
	chipPos m_pchipPos[100];
	
	//マップデータ格納
	static chipData m_pMapData[MAX_MAP_DATA_X][MAX_MAP_DATA_Y];
	

	//マップ作製済フラグ true...作成済み　false...未作成
	bool m_pCreateFlg = false;
	
	//マップ作製用座標
	int m_posX;
	int m_posY;
	
	//マップ移動距離
	int m_move;

	/**
	* @desc マップ作製
	* @param シード値、初期値はランダム
	* @return 無し
	*/
	void create(int seed);
	
	/*
	* @desk マップエリアデータ
	*/
	struct areaData {
		//次のエリアまでの距離
		int m_next = 1;
		
		//通路Y軸高さ式パラメータ
		//基礎値
		int m_default = 0;
		//乱数値
		int m_random = MAX_MAP_DATA_Y;
		int m_enemyCount = 0;
		//天井在りフラグ
		bool m_top = false;
		//床在りフラグ
		bool m_bottom = false;
		//上小山
		bool m_topSmallHill = false;
		//下小山
		bool m_bottomSmallHill = false;
		//上中山
		bool m_topMiddleHill = false;
		//下中山
		bool m_bottomMiddleHill = false;
		//上大山
		bool m_topLargeHill = false;
		//下大山
		bool m_bottomLargeHill = false;
		//中小岩
		bool m_middleSmallRock = false;
		//中中岩
		bool m_middleMiddleRock = false;
		//敵1
		bool m_enemy1 = false;
		//敵2
		bool m_enemy2 = false;
		//敵3
		bool m_enemy3 = false;
		//敵4
		bool m_enemy4 = false;
		//敵5
		bool m_enemy5 = false;
		//敵6
		bool m_enemy6 = false;
		//敵7
		bool m_enemy7 = false;

	};
	//エリアデータ配列
	areaData m_pAreaData[10];
	//std::vector<areaData> m_pAreaData;
	//エリアデータカウント
	static int m_areaDataCount;
	void setAreaData(
		int next,//次のエリアまでの距離
		int default,//y軸基礎値
		int random,//y軸乱数値
		int enemyCount,//敵の数
		bool top,//天井在りフラグ
		bool bottom,//床在りフラグ
		bool topSmallHill,//上小山
		bool bottomSmallHill,//下小山
		bool topMiddleHill,//上中山
		bool bottomMiddleHill,//下中山
		bool topLargeHill,//上大山
		bool bottomLargeHill,//下大山
		bool middleSmallRock,//中小岩
		bool middleMiddleRock,//中中岩
		bool enemy1,
		bool enemy2,
		bool enemy3,
		bool enemy4,
		bool enemy5,
		bool enemy6,
		bool enemy7
	);
	/*
	*@desc マップエリア外チェック
	*@param x座標
	*@param y座標
	*/
	bool areaCheck(int x,int y);
	/*
	*@desc マップ上山作成
	*@param 真ん中高さ
	*@param 乱数補正
	*@param エリア始め
	*@param エリア終わり
	*/
	void createTopHill(int height,int random,int start,int next);
	
	/*
	*@desc マップ上山作成
	*@param 真ん中高さ
	*@param 乱数補正
	*@param エリア始め
	*@param エリア終わり
	*/
	void createBottomHill(int height, int random, int start, int next);

	/*
	*@desc 岩作成
	*@param 岩サイズ
	*@param エリア始め
	*@param エリア終わり
	*/
	void createRock(int size, int start, int next);

	static std::vector<CEnemyLaunchData> m_pEnemyLaunchData;
	/*
	*@desc 敵の動き
	*@param x座標
	*@param y座標
	*@param 移動方向 true...右 false...左
	*@param 出現場所 0右 1左 2上 3下
	*@param 移動パターン
	*/
	std::vector<CEnemyAction> enemyMove(int x,int y,bool direction, int position, int patern);
	
	/**
	*@desc 周囲を調査して移動可能方向を調べる
	*@param x座標
	*@param y座標
	*@param 方向　true...右 false...左
	*/
	chipPos checkMove(int x,int y,bool direction,int stdDir);

	//方向記録用
	int m_saveDirection;

	//周囲座標補正用
	int m_dataX[9] = { -1,-1,0,1,1,1,0,-1,0 };
	int m_dataY[9] = { 0,1,1,1,0,-1,-1,-1,0 };

	//基準方向
	int checkDir(int x, int y, int direction, int patern, int position);
	//方向作成用カウンター
	int m_dirCount = 0;
	//int dirMaxCount;
	//方向作成用高さ
	int m_dirHeight;

	//シード値
	static int m_seed;
	
	/*
	*@desc ボス移動作成
	*@param ボスランク
	*@return 移動データ配列
	*/
	std::vector<CEnemyAction> bossEnemyMove(int rank);

};
#endif __ShootingGame__MapData__