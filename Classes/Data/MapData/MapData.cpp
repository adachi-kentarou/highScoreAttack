#include "MapData.h"
#include "Constants.h"
#include "Scene/GameMain/GameMain.h"

/**
* @desc マップ作製
* @param シード値、初期値はランダム
* @return 無し
*/
MapData::chipData MapData::m_pMapData[MapData::MAX_MAP_DATA_X][MapData::MAX_MAP_DATA_Y];
std::vector<CEnemyLaunchData> MapData::m_pEnemyLaunchData;
int MapData::m_areaDataCount = 0;
float MapData::WALL_SPEED = 0.5f;
int MapData::m_seed;
void MapData::create(int m_seed) {
	//this->m_seed = m_seed;
	//シード値設定
	srand(m_seed);
	int m_indexNum = 0;

	//出撃データの解放
	m_pEnemyLaunchData.clear();
	//初期化
	m_areaDataCount = 0;
	WALL_SPEED = 0.5f;
	
	std::vector<chipPos> m_pchipVector;
	std::vector<chipPos>::iterator itr;
	//マップの初期化
	for (int i = 0; i < MAX_MAP_DATA_X;i++) {
		for (int j = 0; j < MAX_MAP_DATA_Y; j++) {
			if (j == 0 || j == MAX_MAP_DATA_Y - 1) {
				m_pMapData[i][j].m_frontRank = 999999999;
				m_pMapData[i][j].m_backRank = 999999999;
			}
			else {
				m_pMapData[i][j].m_frontRank = 0;
				m_pMapData[i][j].m_backRank = 0;
			}
			m_pMapData[i][j].m_mapChipPatern = 0;
			m_pMapData[i][j].m_area = 0;
		}
	}

	//ステージデータ
	int stage_data[17][3] ={
		{ 5,4,3},	//天井	
		{ 5,4,3 },	//床		
		{ 2,3,4 },	//上小山	
		{ 2,3,4 },	//下小山	
		{ 2,3,3 },	//上中山	
		{ 2,3,3 },	//下中山	
		{ 1,3,3 },	//上大山	
		{ 1,3,3 },	//下大山	
		{ 3,3,4 },	//中小岩	
		{ 2,3,4 },	//中中岩	
		{ 8,7,7 },	//敵1		
		{ 7,8,8 },	//敵2		
		{ 6,7,7 },	//敵3		
		{ 6,7,8 },	//敵4
		{ -1,-1,8 },//敵5
		{ -1,6,7 },	//敵6
		{ -1,6,7 }	//敵7
	};
	bool m_data[17];
	
	for (int i = 0; i < 10;i++) {
		for (int i = 0; i < 17; i++) {
			if ((rand() % 10) <= (stage_data[i][CGameMain::m_stageNo - 1])) {
				m_data[i] = true;
			}
			else {
				m_data[i] = false;
			}
		}
		setAreaData(
			10,		//次距離
			0,		//y基礎	
			11,		//y乱数	
			5 + i / 2 + rand() % 5,//敵の数	
			m_data[0],	//天井	
			m_data[1],	//床		
			m_data[2],	//上小山	
			m_data[3],	//下小山	
			m_data[4],	//上中山	
			m_data[5],	//下中山	
			m_data[6],	//上大山	
			m_data[7],	//下大山	
			m_data[8],	//中小岩	
			m_data[9],	//中中岩	
			m_data[10],	//敵1		
			m_data[11],	//敵2		
			m_data[12],	//敵3		
			m_data[13],	//敵4
			m_data[14],	//敵5
			m_data[15],	//敵6
			m_data[16]	//敵7
		);
	}

	//エリアデータカウント
	int m_count = 0;
	//次のエリアまでのカウント
	int nextAreaCount = m_pAreaData[m_count].m_next - 1;
	

	//移動距離リセット
	m_move = 0;

	//エリアカウントリセット
	m_areaDataCount = 0;

	//x座標設定
	m_posX = 0;
	//y座標設定
	m_posY = rand() % m_pAreaData[m_count].m_random + m_pAreaData[m_count].m_default + 1;

	//移動距離
	int moveX = rand() % 5 + 1;
	int moveY = rand() % m_pAreaData[m_count].m_random + m_pAreaData[m_count].m_default + 1 - m_posY;
	
	//最初はマップを横断する道を作る　道に壁を配置しないようにするのでマップを抜けきることが保証される
	//端から端までループしてマップに道を書き込む
	while (m_move < MAX_MAP_DATA_X) {
		//道を設定
		m_pMapData[m_posX][m_posY].m_frontRank = -1;
		m_pMapData[m_posX][m_posY].m_backRank = -1;
		if (m_posX < MAX_MAP_DATA_X - 1) {
			m_pMapData[m_posX + 1][m_posY].m_frontRank = -1;
			m_pMapData[m_posX + 1][m_posY].m_backRank = -1;
		}
		m_pMapData[m_posX][m_posY + 1].m_frontRank = -1;
		m_pMapData[m_posX][m_posY + 1].m_backRank = -1;
		if (m_posX < MAX_MAP_DATA_X - 1) {
			m_pMapData[m_posX + 1][m_posY + 1].m_frontRank = -1;
			m_pMapData[m_posX + 1][m_posY + 1].m_backRank = -1;
		}
		//エリアを設定
		for (int i = 1; i < 13;i++) {
			m_pMapData[m_move][i].m_area = m_count;
		}

		//次の移動設定を行う
		if (m_move == moveX || m_move == nextAreaCount) {
			if (m_move == nextAreaCount) {
				m_count++;
				nextAreaCount += m_pAreaData[m_count].m_next;
			}
			
			moveX += rand() % 10 + 1;

			while (moveY != 0) {
				
				if (moveY > 0) {
					moveY--;
					m_posY++;
					m_pMapData[m_posX - 1][m_posY + 1].m_frontRank = -1;
					m_pMapData[m_posX - 1][m_posY + 1].m_backRank = -1;
					if (m_posX < MAX_MAP_DATA_X - 1) {
						m_pMapData[m_posX][m_posY + 1].m_frontRank = -1;
						m_pMapData[m_posX][m_posY + 1].m_backRank = -1;
					}
				}
				else {
					moveY++;
					m_posY--;
					m_pMapData[m_posX - 1][m_posY].m_frontRank = -1;
					m_pMapData[m_posX - 1][m_posY].m_backRank = -1;
					if (m_posX < MAX_MAP_DATA_X - 1) {
						m_pMapData[m_posX][m_posY].m_frontRank = -1;
						m_pMapData[m_posX][m_posY].m_backRank = -1;
					}
				}
				//通路配置
				m_pMapData[m_posX][m_posY].m_frontRank = -1;
				m_pMapData[m_posX][m_posY].m_backRank = -1;
				if (m_posX < MAX_MAP_DATA_X - 1) {
					m_pMapData[m_posX + 1][m_posY].m_frontRank = -1;
					m_pMapData[m_posX + 1][m_posY].m_backRank = -1;
				}
				m_pMapData[m_posX][m_posY + 1].m_frontRank = -1;
				m_pMapData[m_posX][m_posY + 1].m_backRank = -1;
				if (m_posX < MAX_MAP_DATA_X - 1) {
					m_pMapData[m_posX + 1][m_posY + 1].m_frontRank = -1;
					m_pMapData[m_posX + 1][m_posY + 1].m_backRank = -1;
				}
				
			}
			//次のy軸移動距離を設定
			moveY = rand() % m_pAreaData[m_count].m_random + m_pAreaData[m_count].m_default + 1 - m_posY;
		}
		//x移動距離を増やす
		m_move++;
		//x座標を増やす
		m_posX++;
	}

	//エリアの最大カウントを記録
	int maxCount = m_count;
	m_count = 0;
	//エリアの始まりの座標
	int m_start = 0;
	//エリアループ
	while (m_count < maxCount) {
		//ここから各種壁配置処理

		//天井
		if (m_pAreaData[m_count].m_top) {
			//エリアの端から端までループ処理
			for (int i = m_start; i <= m_start + m_pAreaData[m_count].m_next; i++) {
				//高さランダム設定
				int maxLength = rand() % 3 + 2;
				//x軸毎のy軸壁設定可能距離を調べる
				for (int j = 2; j <= maxLength; j++) {
					if (areaCheck(i, MAX_MAP_DATA_Y - j) || m_pMapData[i][MAX_MAP_DATA_Y - j].m_frontRank == -1) {
						//通路かマップの端に接触したので長さここまで
						break;
					}
					//壁を設定
					m_pMapData[i][MAX_MAP_DATA_Y - j].m_mapChipPatern = 1;
				}
			}
		}

		//床
		if (m_pAreaData[m_count].m_bottom) {
			//エリアの端から端までループ処理
			for (int i = m_start; i < m_start + m_pAreaData[m_count].m_next; i++) {
				//高さランダム設定
				int maxLength = rand() % 3 + 1;
				//x軸毎のy軸壁設定可能距離を調べる
				for (int j = 1; j <= maxLength; j++) {
					if (areaCheck(i,j) || m_pMapData[i][j].m_frontRank == -1) {
						//通路かマップの端に接触したので長さここまで
						break;
					}
					//壁を設定
					m_pMapData[i][j].m_mapChipPatern = 1;
				}
			}
		}

		//上小山
		if (m_pAreaData[m_count].m_topSmallHill) {
			createTopHill(3, 3, m_start, m_pAreaData[m_count].m_next);
		}

		//下小山
		if (m_pAreaData[m_count].m_bottomSmallHill) {
			createBottomHill(3,3,m_start, m_pAreaData[m_count].m_next);
		}

		//上中山
		if (m_pAreaData[m_count].m_topMiddleHill) {
			createTopHill(6, 3, m_start, m_pAreaData[m_count].m_next);
		}

		//下中山
		if (m_pAreaData[m_count].m_bottomMiddleHill) {
			createBottomHill(6, 3, m_start, m_pAreaData[m_count].m_next);
		}

		//上大山
		if (m_pAreaData[m_count].m_topLargeHill) {
			createTopHill(9, 3, m_start, m_pAreaData[m_count].m_next);
		}

		//上大山
		if (m_pAreaData[m_count].m_bottomLargeHill) {
			createBottomHill(9, 3, m_start, m_pAreaData[m_count].m_next);
		}
		
		//次のエリアの始まりの座標を設定
		m_start += m_pAreaData[m_count].m_next;
		m_count++;

	}

	m_count = 0;
	//エリアの始まりの座標
	m_start = 0;
	//エリアループ
	while (m_count <= maxCount) {
		//中小岩
		if (m_pAreaData[m_count].m_middleSmallRock) {
			createRock(5, m_start, m_pAreaData[m_count].m_next);
		}
		//中中岩
		if (m_pAreaData[m_count].m_middleMiddleRock) {
			createRock(10, m_start, m_pAreaData[m_count].m_next);
		}
		//次のエリアの始まりの座標を設定
		m_start += m_pAreaData[m_count].m_next;
		m_count++;
	}

	//j=0 前 j=1 後ろ
	for (int j = 0; j < 2;j++) {
		//座標配列をリセットする
		m_pchipVector.clear();
		
		//チップ座標配列
		//前移動順位設定
		//移動先ランク
		int rank = 1;
		//スタート地点を設定
		for (int i = 1; i < 13; i++) {
			if (m_pMapData[j ? MAX_MAP_DATA_X : 0][i].m_mapChipPatern == 0) {
				j ? m_pMapData[j ? MAX_MAP_DATA_X - 1 : 0][i].m_backRank = rank : m_pMapData[j ? MAX_MAP_DATA_X - 1 : 0][i].m_frontRank = rank;
				//チップ設定
				m_pchipVector.push_back(createChip(j ? MAX_MAP_DATA_X - 1: 0, i));
			}
		}

		while (m_pchipVector.size() != 0) {
			//移動順位を上げる
			rank++;
			
			std::vector<chipPos> m_pchipVector2 = m_pchipVector;
			//座標配列をリセットする
			m_pchipVector.clear();
			
			itr = m_pchipVector2.begin();
			while (itr != m_pchipVector2.end()) {
				//周囲に移動できるか確認していく
				//左
				bool left = !areaCheck(itr->x - 1, itr->y) &&
					m_pMapData[itr->x - 1][itr->y].m_mapChipPatern == 0 &&
					(j ? m_pMapData[itr->x - 1][itr->y].m_backRank <= 0 :
						m_pMapData[itr->x - 1][itr->y].m_frontRank <= 0);
				//右
				bool right = !areaCheck(itr->x + 1, itr->y) &&
					m_pMapData[itr->x + 1][itr->y].m_mapChipPatern == 0 &&
					(j ? m_pMapData[itr->x + 1][itr->y].m_backRank <= 0 :
						m_pMapData[itr->x + 1][itr->y].m_frontRank <= 0);
				//上
				bool top = !areaCheck(itr->x, itr->y + 1) &&
					m_pMapData[itr->x][itr->y + 1].m_mapChipPatern == 0 &&
					(j ? m_pMapData[itr->x][itr->y + 1].m_backRank <= 0 :
						m_pMapData[itr->x][itr->y + 1].m_frontRank <= 0);
				//下
				bool bottom = !areaCheck(itr->x, itr->y - 1) &&
					m_pMapData[itr->x][itr->y - 1].m_mapChipPatern == 0 &&
					(j ? m_pMapData[itr->x][itr->y - 1].m_backRank <= 0 :
						m_pMapData[itr->x][itr->y - 1].m_frontRank <= 0);
				//左上
				bool leftTop = !areaCheck(itr->x - 1, itr->y + 1) &&
					m_pMapData[itr->x - 1][itr->y + 1].m_mapChipPatern == 0 &&
					(j ? m_pMapData[itr->x - 1][itr->y + 1].m_backRank <= 0 :
						m_pMapData[itr->x - 1][itr->y + 1].m_frontRank <= 0);
				//左下
				bool leftBottom = !areaCheck(itr->x - 1, itr->y - 1) &&
					m_pMapData[itr->x - 1][itr->y - 1].m_mapChipPatern == 0 &&
					(j ? m_pMapData[itr->x - 1][itr->y - 1].m_backRank <= 0 :
						m_pMapData[itr->x - 1][itr->y - 1].m_frontRank <= 0);
				//右上
				bool rightTop = !areaCheck(itr->x + 1, itr->y + 1) &&
					m_pMapData[itr->x + 1][itr->y + 1].m_mapChipPatern == 0 &&
					(j ? m_pMapData[itr->x + 1][itr->y + 1].m_backRank <= 0 :
						m_pMapData[itr->x + 1][itr->y + 1].m_frontRank <= 0);
				//右下
				bool rightBottom = !areaCheck(itr->x + 1, itr->y - 1) &&
					m_pMapData[itr->x + 1][itr->y - 1].m_mapChipPatern == 0 &&
					(j ? m_pMapData[itr->x + 1][itr->y - 1].m_backRank <= 0 :
						m_pMapData[itr->x + 1][itr->y - 1].m_frontRank <= 0);

				//左
				if (left) {
					m_pchipVector.push_back(createChip(itr->x - 1, itr->y));
				}
				//右
				if (right) {
					m_pchipVector.push_back(createChip(itr->x + 1, itr->y));
				}
				//上
				if (top) {
					m_pchipVector.push_back(createChip(itr->x, itr->y + 1));
				}
				//下
				if (bottom) {
					m_pchipVector.push_back(createChip(itr->x, itr->y - 1));
				}
				//左上
				if (left && top && leftTop) {
					m_pchipVector.push_back(createChip(itr->x - 1, itr->y + 1));
				}
				//左下
				if (left && bottom && leftBottom) {
					m_pchipVector.push_back(createChip(itr->x - 1, itr->y - 1));
				}
				//右上
				if (right && top && rightTop) {
					m_pchipVector.push_back(createChip(itr->x + 1, itr->y + 1));
				}
				//右下
				if (right && bottom && rightBottom) {
					m_pchipVector.push_back(createChip(itr->x + 1, itr->y - 1));
				}

				itr++;
			}
			//rank適用
			for (chipPos pos: m_pchipVector) {
				j ? m_pMapData[pos.x][pos.y].m_backRank = rank :
					m_pMapData[pos.x][pos.y].m_frontRank = rank;
			}

		}

	}

	//////////////////////////////////
	//ここから敵の配置と移動経路設定//
	//////////////////////////////////

	//移動カウント
	int m_moveCounter = 0;
	//壁移動スピード
	//int WALL_SPEED = 0.5;
	m_count = 0;
	//エリアの始まりの座標
	m_start = 0;
	//エリアループ
	while (m_count <= maxCount) {
		
		//敵候補配列
		std::vector<int> m_enemy;
		//敵１追加
		if (m_pAreaData[m_count].m_enemy1) {
			m_enemy.push_back(1);
		}
		//敵２追加
		if (m_pAreaData[m_count].m_enemy2) {
			m_enemy.push_back(2);
		}
		//敵３追加
		if (m_pAreaData[m_count].m_enemy3) {
			m_enemy.push_back(3);
		}
		//敵４追加
		if (m_pAreaData[m_count].m_enemy4) {
			m_enemy.push_back(4);
		}
		//敵５追加
		if (m_pAreaData[m_count].m_enemy5) {
			m_enemy.push_back(5);
		}
		//敵６追加
		if (m_pAreaData[m_count].m_enemy6) {
			m_enemy.push_back(6);
		}
		//敵７追加
		if (m_pAreaData[m_count].m_enemy7) {
			m_enemy.push_back(7);
		}

		//出現敵候補が全てなかった場合は処理を抜ける
		if (m_enemy.size() == 0) {
			//次のエリアの始まりの座標を設定
			m_start += m_pAreaData[m_count].m_next;
			m_count++;
			continue;
		}

		//出撃位置候補検索
		//全て
		std::vector<chipPos> allPos;
		//壁周囲
		std::vector<chipPos> aroundPos;
		//天井
		std::vector<chipPos> topPos;
		//床
		std::vector<chipPos> bottomPos;
		//出現位置候補検索
		//エリアの端から端までループ処理
		for (int i = m_start; i < m_start + m_pAreaData[m_count].m_next;i++) {
			for (int j = 1; j < MAX_MAP_DATA_Y - 1; j++) {
				if (areaCheck(i, j)) {
					//エリア外なら飛ばす
					continue;
				}

				chipPos pos;
				pos.x = i;
				pos.y = j;
				//エリア内を検索
				if (m_pMapData[i][j].m_mapChipPatern == 0 && (m_pMapData[i][j].m_frontRank > 0 || m_pMapData[i][j].m_backRank > 0)) {
					//全て
					allPos.push_back(pos);
					//周囲
					if (m_pMapData[i][j].m_mapChipPatern == 0 && (!areaCheck(i - 1, j) && m_pMapData[i - 1][j].m_mapChipPatern != 0 ||
						!areaCheck(i + 1, j) && m_pMapData[i + 1][j].m_mapChipPatern != 0 ||
						!areaCheck(i, j - 1) && m_pMapData[i][j - 1].m_mapChipPatern != 0 ||
						!areaCheck(i, j + 1) && m_pMapData[i][j + 1].m_mapChipPatern != 0
						)) {
						aroundPos.push_back(pos);
					}
					//天井
					if (m_pMapData[i][j].m_mapChipPatern == 0 && j == MAX_MAP_DATA_Y - 2 &&
						(m_pMapData[i][j].m_frontRank > 0 || m_pMapData[i][j].m_backRank > 0)) {
						topPos.push_back(pos);
					}
					//床
					if (m_pMapData[i][j].m_mapChipPatern == 0 && j == 1 &&
						(m_pMapData[i][j].m_frontRank > 0 || m_pMapData[i][j].m_backRank > 0)) {
						bottomPos.push_back(pos);
					}
				}
			}
		}

		//出現位置候補が全てなかった場合は処理を抜ける
		if (allPos.size() == 0 && aroundPos.size() == 0 && topPos.size() == 0 && bottomPos.size() == 0) {
			//次のエリアの始まりの座標を設定
			m_start += m_pAreaData[m_count].m_next;
			m_count++;
			continue;
		}

		cocos2d::log("--**--%d", m_pAreaData[m_count].m_enemyCount);
		//敵の数だけループ
		for (int i = 0; i < m_pAreaData[m_count].m_enemyCount;i++) {
			//出撃データ
			CEnemyLaunchData enemyData;
			//出撃敵タイプ
			int enemyType;
			//出撃タイプ配列
			std::vector<int> enemyTypeArray;
			//出現敵候補を配列に入れる
			for (int i = 0; i < (int)m_enemy.size();i++) {
				switch (m_enemy[i]) {
				case 1:
					if (allPos.size()) {
						enemyTypeArray.push_back(1);
					}
					break;
				case 2:
					if (topPos.size()) {
						enemyTypeArray.push_back(2);
					}
					break;
				case 3:
					if (bottomPos.size()) {
						enemyTypeArray.push_back(3);
					}
					break;
				case 4:
					if (aroundPos.size()) {
						enemyTypeArray.push_back(4);
					}
					break;
				case 5:
					if (allPos.size()) {
						enemyTypeArray.push_back(5);
					}
					break;
				case 6:
					if (topPos.size()) {
						enemyTypeArray.push_back(6);
					}
					break;
				case 7:
					if (bottomPos.size()) {
						enemyTypeArray.push_back(7);
					}
					break;
				}
			}
			//候補0なら出現処理終了
			if (!enemyTypeArray.size()) {
				break;
			}

			//出現敵決定
			enemyType = enemyTypeArray[rand() % enemyTypeArray.size()];
			//enemyType = 4;
			//座標
			chipPos pos;
			//出現タイミング
			int timing;
			//出現位置補正
			float remainder;
			//出撃方向候補
			std::vector<int> directionArray;
			//出撃方向
			int direction;
			bool bdirection = true;
			int position;
			//配列添え字記憶用
			int index;
			//移動パターン
			int m_mapChipPatern = 0;
			//敵１
			//座標設定
			//出撃方向候補
			//前後
			if ((enemyType == 1 || enemyType == 5) && allPos.size() != 0) {
				directionArray.push_back(1);
				directionArray.push_back(2);
			}
			//上
			if ((enemyType == 2 || enemyType == 6) && topPos.size() != 0) {
				directionArray.push_back(3);
			}
			//下
			if ((enemyType == 3 || enemyType == 7) && bottomPos.size() != 0) {
				directionArray.push_back(4);
			}
			//周囲
			if (enemyType == 4 && aroundPos.size() != 0) {
				directionArray.push_back(5);
				m_mapChipPatern = 2;
			}

			//出撃方向決定
			direction = directionArray[rand() % directionArray.size()];
			//direction = 5;
			//x軸出現位置ずらす
			int shift = 0;
			//設置方向
			int install = 0;
			//座標設定
			switch (direction) {
			case 1://右端
				index = rand() % allPos.size();
				pos = allPos[index];
				bdirection = true;
				position = 0;
				//配列から削除
				allPos.erase(allPos.begin() + index);
				break;
			case 2://左端
				index = rand() % allPos.size();
				pos = allPos[index];
				bdirection = false;
				position = 1;
				//配列から削除
				allPos.erase(allPos.begin() + index); 
				shift = 17;
				break;
			case 3://上
				index = rand() % topPos.size();
				pos = topPos[index];
				bdirection = rand() % 2 ? true : false;
				position = 2;
				//配列から削除
				topPos.erase(topPos.begin() + index);
				//画面外に設定
				pos.y += 1;
				shift = bdirection ? (rand() % 5) : (rand() % 5 + 11);
				//shift = 5;
				break;
			case 4://下
				index = rand() % bottomPos.size();
				pos = bottomPos[index];
				bdirection = rand() % 2 ? true : false;
				position = 3;
				//配列から削除
				bottomPos.erase(bottomPos.begin() + index);
				//画面外に設定
				pos.y -= 1;
				shift = bdirection ? (rand() % 5) : (rand() % 5 + 11);
				break;
			case 5://周囲
				index = rand() % aroundPos.size();
				pos = aroundPos[index];
				bdirection = true;
				position = 4;
				//配列から削除
				aroundPos.erase(aroundPos.begin() + index);

				//設置方向
				std::vector<int> ins;
				//下
				if(!areaCheck(pos.x,pos.y - 1) && m_pMapData[pos.x][pos.y - 1].m_mapChipPatern != 0){
					ins.push_back(0);
				}
				//左
				if (!areaCheck(pos.x - 1, pos.y) && m_pMapData[pos.x - 1][pos.y].m_mapChipPatern != 0) {
					ins.push_back(1);
				}
				//上
				if (!areaCheck(pos.x, pos.y + 1) && m_pMapData[pos.x][pos.y + 1].m_mapChipPatern != 0) {
					ins.push_back(2);
				}
				//右
				if (!areaCheck(pos.x + 1, pos.y) && m_pMapData[pos.x + 1][pos.y].m_mapChipPatern != 0) {
					ins.push_back(3);
				}
				//設置方向
				if (ins.size()) {
					install = ins[rand() % ins.size()];
					cocos2d::log("size= %d install = %d", ins.size(),install);
				}

				break;

			}

			//右端
			m_pMapData[pos.x][pos.y].m_test = -1;
			cocos2d::log("%d - %d", pos.x, pos.y);
			

			timing = (pos.x + shift) * 40 / WALL_SPEED;
			remainder = ((pos.x + shift) * 40) - (timing * WALL_SPEED);
			//出撃データ
			enemyData.m_frame = timing;
			enemyData.m_posX = 660 - remainder - (shift * 40);
			enemyData.m_posY = 40 * (pos.y - 1) + 20;
			

			//敵タイプ
			switch (enemyType) {
			case 1:enemyData.m_type = ENEMY_TYPE::TYPE_A;
				enemyData.m_actionType = ACTION_TYPE::ORIGINAL;
				break;
			case 2:enemyData.m_type = ENEMY_TYPE::TYPE_B;
				enemyData.m_actionType = ACTION_TYPE::ORIGINAL;
				break;
			case 3:enemyData.m_type = ENEMY_TYPE::TYPE_B;
				enemyData.m_actionType = ACTION_TYPE::ORIGINAL;
				break;
			case 4:enemyData.m_type = ENEMY_TYPE::TYPE_C;
				enemyData.m_actionType = ACTION_TYPE::ORIGINAL;
				break;
			case 5:enemyData.m_type = ENEMY_TYPE::TYPE_D;
				enemyData.m_actionType = ACTION_TYPE::ORIGINAL2;
				break;
			case 6:enemyData.m_type = ENEMY_TYPE::TYPE_E;
				enemyData.m_actionType = ACTION_TYPE::ORIGINAL;
				break;
			case 7:enemyData.m_type = ENEMY_TYPE::TYPE_E;
				enemyData.m_actionType = ACTION_TYPE::ORIGINAL;
				break;
			}
			
			//進行方向
			enemyData.direction = bdirection;
			enemyData.install = install;
			//行動
			enemyData.action = enemyMove(pos.x, pos.y, bdirection, position, m_mapChipPatern);
			//アイテム設定
			if (rand() % 4 == 0) {
				enemyData.m_item = (ITEM_TYPE)(rand() % 11);
			}
			else {
				enemyData.m_item = (ITEM_TYPE)-1;
			}
			//出撃配列に格納
			m_pEnemyLaunchData.push_back(enemyData);
			

			switch (enemyType) {
			case 1:
				
				switch (direction) {
				case 1:
					
					break;

				}
				break;
			case 2:
				//敵２
				break;
			case 3:
				//敵３
				break;
			case 4:
				//敵４
				break;
			case 5:
				//敵５
				break;
			case 6:
				//敵６
				break;
			case 7:
				//敵７
				break;
			default:
				break;
			}
			//出撃位置設定
			
			
		}
		//次のエリアの始まりの座標を設定
		m_start += m_pAreaData[m_count].m_next;
		m_count++;
	}
	//ボス出撃データ

	//ボス出撃x座標
	int bossX = 118;

				  //ボス出撃y座標
	int bossY = 6;
	//シフト
	int shift = 0;

	CEnemyLaunchData enemyData;
	int timing = (bossX + shift) * 40 / WALL_SPEED;
	int remainder = ((bossX + shift) * 40) - (timing * WALL_SPEED);
	//出撃データ
	enemyData.m_frame = timing;
	enemyData.m_posX = 660 - remainder - (shift * 40) + 100;
	enemyData.m_posY = 40 * (bossY - 1) + 20;

	//敵タイプ
	enemyData.m_type = ENEMY_TYPE::TYPE_BOSS_1;

	//進行方向
	enemyData.direction = true;
	enemyData.install = 1;

	enemyData.m_actionType = ACTION_TYPE::BOSS_1;
	enemyData.action = bossEnemyMove(CGameMain::m_stageNo - 1);
	m_pEnemyLaunchData.push_back(enemyData);





	//出撃データをフレームでソートする
	// nameをキーに昇順でソート
	sort(m_pEnemyLaunchData.begin(), m_pEnemyLaunchData.end(),
		[](const CEnemyLaunchData& x, const CEnemyLaunchData& y) { return x.m_frame < y.m_frame; });
	cocos2d::log("------sort-------");
	for (CEnemyLaunchData a : m_pEnemyLaunchData) {
		cocos2d::log("frame=%d", a.m_frame);
	}

	//壁種類設定
	for (int i = 0; i < MAX_MAP_DATA_X; i++) {
		for (int j = 0; j < MAX_MAP_DATA_Y; j++) {
			if (m_pMapData[i][j].m_mapChipPatern == 1) {
				m_pMapData[i][j].m_mapChipPatern = (int)(rand() % 2) + 1 + (CGameMain::m_stageNo -1) * 2;
			}
		}
	}
}

/*
*@desc チップ作成
@param x座標
@param y座標
*/
MapData::chipPos MapData::createChip(int x, int y) {
	MapData::chipPos chip;
	chip.x = x;
	chip.y = y;
	return chip;
}

/*
*@desc マップ上山作成
*@param 真ん中高さ
*@param ランダム
*@param エリア始め
*@param エリア終わり
*/
void MapData::createTopHill(int hight,int random,int start,int next) {
	//エリア範囲の高さ条件判定
	int m_indexNum = 0;
	//最小高さ1設定
	int m_maxHight = 1;

	int m_xIndex[100];

	int m_randx;

	int m_vMaxX;
	//エリアの端から端までループ処理
	for (int i = start; i < start + next; i++) {
		//最小高さ4で作成可能場所をエリア内で検索

		int j;

		for (j = 2; j < m_maxHight + 2; j++) {
			if (m_pMapData[i][MAX_MAP_DATA_Y - j].m_frontRank == -1) {
				break;
			}
		}
		if (j == m_maxHight + 2) {
			//高さOK			
			m_xIndex[m_indexNum] = i;
			//要素数増やす
			m_indexNum++;
		}

	}

	//配置候補がある場合
	if (m_indexNum != 0) {
		//配置場所選択
		m_randx = rand() % m_indexNum;
		//高さ変更 4+ランダム
		m_maxHight = rand() % random + hight;
		//山中央配置
		for (int j = 2; j < m_maxHight + 2; j++) {
			//進路にぶつかるなら中断
			if (m_pMapData[m_xIndex[m_randx]][MAX_MAP_DATA_Y - j].m_frontRank == -1) {
				break;
			}
			m_pMapData[m_xIndex[m_randx]][MAX_MAP_DATA_Y - j].m_mapChipPatern = 1;
		}
		//高さを下げる
		m_vMaxX = m_maxHight + 2 - (rand() % random);
		//進行方向に山配置
		for (int i = m_xIndex[m_randx] + 1; i < start + next; i++) {
			int j;
			for (j = 2; j < m_vMaxX; j++) {
				//進路にぶつかるなら中断
				if (m_pMapData[i][MAX_MAP_DATA_Y - j].m_frontRank == -1) {
					break;
				}

				m_pMapData[i][MAX_MAP_DATA_Y - j].m_mapChipPatern = 1;
			}
			//終了時の高さからさらにランダムで高さを低くする
			m_vMaxX = j - (rand() % 3);
			//高さ0なら中断
			if (m_vMaxX <= 2) {
				break;
			}

		}

		//高さを下げる
		m_vMaxX = m_maxHight + 2 - (rand() % random);
		//後退方向に山配置
		for (int i = m_xIndex[m_randx] - 1; i >= start; i--) {
			int j;
			for (j = 2; j < m_vMaxX; j++) {
				//進路にぶつかるなら中断
				if (m_pMapData[i][MAX_MAP_DATA_Y - j].m_frontRank == -1) {
					break;
				}

				m_pMapData[i][MAX_MAP_DATA_Y - j].m_mapChipPatern = 1;
			}
			//終了時の高さからさらにランダムで高さを低くする
			m_vMaxX = j - (rand() % 3);
			//高さ0なら中断
			if (m_vMaxX <= 2) {
				break;
			}

		}

	}
	else {
		//配置不可;
		cocos2d::log("no topSmallHill");
	}
}

/*
*@desc マップ下山作成
*@param 真ん中高さ
*@param ランダム
*@param エリア始め
*@param エリア終わり
*/
void MapData::createBottomHill(int hight, int random, int start, int next) {
	//エリア範囲の高さ条件判定
	int indexNum = 0;
	//最小高さ1設定
	int m_maxHight = 1;

	int m_xIndex[100];

	int m_randx;

	int vMaxX;
	//エリアの端から端までループ処理
	for (int i = start; i < start + next; i++) {
		//最小高さ4で作成可能場所をエリア内で検索

		int j;

		for (j = 1; j < m_maxHight + 1; j++) {
			if (m_pMapData[i][j].m_frontRank == -1) {
				break;
			}
		}
		if (j == m_maxHight + 1) {
			//高さOK			
			m_xIndex[indexNum] = i;
			//要素数増やす
			indexNum++;
		}

	}

	//配置候補がある場合
	if (indexNum != 0) {
		//配置場所選択
		m_randx = rand() % indexNum;
		//高さ変更 4+ランダム
		m_maxHight = rand() % random + hight;
		//山中央配置
		for (int j = 1; j < m_maxHight + 1; j++) {
			//進路にぶつかるなら中断
			if (m_pMapData[m_xIndex[m_randx]][j].m_frontRank == -1) {
				break;
			}
			m_pMapData[m_xIndex[m_randx]][j].m_mapChipPatern = 1;
		}
		//高さを下げる
		vMaxX = m_maxHight + 1 - (rand() % 3);
		//進行方向に山配置
		for (int i = m_xIndex[m_randx] + 1; i < start + next; i++) {
			int j;
			for (j = 1; j < vMaxX; j++) {
				//進路にぶつかるなら中断
				if (m_pMapData[i][j].m_frontRank == -1) {
					break;
				}

				m_pMapData[i][j].m_mapChipPatern = 1;
			}
			//終了時の高さからさらにランダムで高さを低くする
			vMaxX = j - (rand() % 3);
			//高さ0なら中断
			if (vMaxX <= 1) {
				break;
			}

		}

		//高さを下げる
		vMaxX = m_maxHight + 1 - (rand() % hight);
		//後退方向に山配置
		for (int i = m_xIndex[m_randx] - 1; i >= start; i--) {
			int j;
			for (j = 1; j < vMaxX; j++) {
				//進路にぶつかるなら中断
				if (m_pMapData[i][j].m_frontRank == -1) {
					break;
				}

				m_pMapData[i][j].m_mapChipPatern = 1;
			}
			//終了時の高さからさらにランダムで高さを低くする
			vMaxX = j - (rand() % hight);
			//高さ0なら中断
			if (vMaxX <= 1) {
				break;
			}

		}

	}
	else {
		//配置不可;
		cocos2d::log("no bottomSmallHill");
	}
}

/*
*@desc 岩作成
*@param 岩サイズ
*@param 個数
*@param エリア始め
*@param エリア終わり
*/
void MapData::createRock(int size, int start, int next) {
	
	std::vector<chipPos> m_pchipVector;
	std::vector<chipPos> m_pchipVector2;
	std::vector<chipPos> m_pchipVector3;
	std::vector<chipPos>::iterator itr;
	int rockSize;
	int chipCount = 0;
	int rockcount;

	//壁以外のチップの数を数える
	//エリアの端から端までループ処理
	for (int i = start; i < start + next; i++) {

		//x軸毎のy軸壁設定可能距離を調べる
		for (int j = 1; j < MAX_MAP_DATA_Y - 1; j++) {
			if (m_pMapData[i][j].m_mapChipPatern == 0) {
				chipCount++;
			}
		}
	}
	//チップの数に合わせて岩の個数変更
	rockcount = rand() % (chipCount / (size * 4) + 1) + 1;
	
	//岩の個数分ループする
	while (rockcount != 0) {
		//岩のサイズを設定する
		rockSize = rand() % size;

		//マップチップ配列を空にする
		m_pchipVector.clear();

		//エリアの端から端までループ処理
		for (int i = start; i < start + next; i++) {

			//x軸毎のy軸壁設定可能距離を調べる
			for (int j = 1; j < MAX_MAP_DATA_Y - 1; j++) {

				bool m_check = true;
				//周囲の座標をチェック
				for (int k = -1; k < 2; k++) {
					for (int l = -1; l < 2; l++) {
						if (areaCheck(i + k, j + l)) {
							continue;
						}

						if (m_pMapData[i + k][j + l].m_mapChipPatern == 1) {
							//画面外か通路か壁に隣接するのでアウト
							m_check = false;
						}
					}
				}
				if (m_check && m_pMapData[i][j].m_frontRank != -1) {
					//問題なければ配列に座標を登録
					m_pchipVector.push_back(createChip(i, j));

					//仮壁を設定
					m_pMapData[i][j].m_mapChipPatern = -1;
				}

			}
		}
		
		//配置候補が無い場合は終了
		if (m_pchipVector.size() == 0) {
			return;
		}

		chipPos m_prandPoint;
		//岩の大きさ
		//岩のサイズカウント
		int rockSizeCount = 0;
		//ランダム値
		int random;

		//マップチップ配列を空にする
		m_pchipVector2.clear();

		//イテレーターの設定
		itr = m_pchipVector.begin();
		//原点座標をランダムで指定
		if (m_pchipVector.size() != 0) {
			random = rand() % m_pchipVector.size();
			m_prandPoint = m_pchipVector[random];
			m_pMapData[m_prandPoint.x][m_prandPoint.y].m_mapChipPatern = 1;
			//配置チップ配列に追加
			m_pchipVector2.push_back(m_pchipVector[random]);
			//座標を配列から削除
			m_pchipVector.erase(itr + random);

		}

		//指定した座標からランダムに拡張する
		//指定したサイズになったら拡張終了
		while (rockSizeCount != rockSize) {

			//マップチップ配列を空にする
			m_pchipVector3.clear();

			//上下左右の配置できるチップを探す
			//配置チップ配列から探す
			itr = m_pchipVector2.begin();
			while (itr != m_pchipVector2.end()) {
				//座標がエリア内で仮壁範囲内であれば候補に追加する
				if (!areaCheck(itr->x + 1, itr->y) && m_pMapData[itr->x + 1][itr->y].m_mapChipPatern == -1) {
					m_pchipVector3.push_back(createChip(itr->x + 1, itr->y));
					//重複追加を防ぐためにパターン値を変更
					m_pMapData[itr->x + 1][itr->y].m_mapChipPatern = -2;
				}
				if (!areaCheck(itr->x - 1, itr->y) && m_pMapData[itr->x - 1][itr->y].m_mapChipPatern == -1) {
					m_pchipVector3.push_back(createChip(itr->x - 1, itr->y));
					//重複追加を防ぐためにパターン値を変更
					m_pMapData[itr->x - 1][itr->y].m_mapChipPatern = -2;
				}
				if (!areaCheck(itr->x, itr->y + 1) && m_pMapData[itr->x][itr->y + 1].m_mapChipPatern == -1) {
					m_pchipVector3.push_back(createChip(itr->x, itr->y + 1));
					//重複追加を防ぐためにパターン値を変更
					m_pMapData[itr->x][itr->y + 1].m_mapChipPatern = -2;
				}
				if (!areaCheck(itr->x, itr->y - 1) && m_pMapData[itr->x][itr->y - 1].m_mapChipPatern == -1) {
					m_pchipVector3.push_back(createChip(itr->x, itr->y - 1));
					//重複追加を防ぐためにパターン値を変更
					m_pMapData[itr->x][itr->y - 1].m_mapChipPatern = -2;
				}

				itr++;
			}
			//重複追加変更を元に戻す
			itr = m_pchipVector.begin();
			while (itr != m_pchipVector.end()) {
				if (m_pMapData[itr->x][itr->y].m_mapChipPatern == -2) {
					m_pMapData[itr->x][itr->y].m_mapChipPatern = -1;
				}
				itr++;
			}

			//配置候補が無い場合は岩拡張終了
			if (m_pchipVector3.size() == 0) {
				break;
			}

			//ランダムに拡張する
			random = rand() % m_pchipVector3.size();
			m_pMapData[m_pchipVector3[random].x][m_pchipVector3[random].y].m_mapChipPatern = 1;
			//配置チップ配列に座標を追加
			m_pchipVector2.push_back(createChip(m_pchipVector3[random].x, m_pchipVector3[random].y));
			//配置カウントを増やす
			rockSizeCount++;

		}
		//仮を元に戻す
		itr = m_pchipVector.begin();
		while (itr != m_pchipVector.end()) {
			if (m_pMapData[itr->x][itr->y].m_mapChipPatern == -1) {
				m_pMapData[itr->x][itr->y].m_mapChipPatern = 0;
			}
			itr++;
		}

		rockcount--;
	}
	
	
	
}

void MapData::setAreaData(
	int next = 1,//次のエリアまでの距離
	int default = 0,//y軸基礎値
	int random = MAX_MAP_DATA_Y,//y軸乱数値
	int enemyCount = 0,//敵の数
	bool top = false,//天井在りフラグ
	bool bottom = false,//床在りフラグ
	bool topSmallHill = false,//上小山
	bool bottomSmallHill = false,//下小山
	bool topMiddleHill = false,//上中山
	bool bottomMiddleHill = false,//下中山
	bool topLargeHill = false,//上大山
	bool bottomLargeHill = false,//下大山
	bool middleSmallRock = false,//中小岩
	bool middleMiddleRock = false,//中中岩
	bool enemy1 = false,
	bool enemy2 = false,
	bool enemy3 = false,
	bool enemy4 = false,
	bool enemy5 = false,
	bool enemy6 = false,
	bool enemy7 = false
) {
	if (m_areaDataCount == 100) {
		return;
	}
	
	m_pAreaData[m_areaDataCount].m_next = next;
	m_pAreaData[m_areaDataCount].m_default = default;
	m_pAreaData[m_areaDataCount].m_random = random;
	m_pAreaData[m_areaDataCount].m_enemyCount = enemyCount;
	m_pAreaData[m_areaDataCount].m_top = top;
	m_pAreaData[m_areaDataCount].m_bottom = bottom;
	m_pAreaData[m_areaDataCount].m_topSmallHill = topSmallHill;
	m_pAreaData[m_areaDataCount].m_bottomSmallHill = bottomSmallHill;
	m_pAreaData[m_areaDataCount].m_topMiddleHill = topMiddleHill;
	m_pAreaData[m_areaDataCount].m_bottomMiddleHill = bottomMiddleHill;
	m_pAreaData[m_areaDataCount].m_topLargeHill = topLargeHill;
	m_pAreaData[m_areaDataCount].m_bottomLargeHill = bottomLargeHill;
	m_pAreaData[m_areaDataCount].m_middleSmallRock = middleSmallRock;
	m_pAreaData[m_areaDataCount].m_middleMiddleRock = middleMiddleRock;
	m_pAreaData[m_areaDataCount].m_enemy1 = enemy1;
	m_pAreaData[m_areaDataCount].m_enemy2 = enemy2;
	m_pAreaData[m_areaDataCount].m_enemy3 = enemy3;
	m_pAreaData[m_areaDataCount].m_enemy4 = enemy4;
	m_pAreaData[m_areaDataCount].m_enemy5 = enemy5;
	m_pAreaData[m_areaDataCount].m_enemy6 = enemy6;
	m_pAreaData[m_areaDataCount].m_enemy7 = enemy7;

	m_areaDataCount++;
}

/*
*@desc マップエリア外チェック
*@param x座標
*@param y座標
*@return true...エリア外 false...エリア内
*/
bool MapData::areaCheck(int x, int y) {
	if (x < 0 || x>= MAX_MAP_DATA_X || y < 1 || y >= MAX_MAP_DATA_Y - 1) {
		return true;
	}
	return false;
}

/*
*@desc 敵の動き
*@param x座標
*@param y座標
*@param 移動方向 true...右 false...左
*@param 出現場所 0右 1左 2上 3下
*@param 移動パターン 0直進 1ジグザグ 2移動無し
*/
std::vector<CEnemyAction> MapData::enemyMove(int x, int y, bool direction,int position, int m_mapChipPatern) {
	std::vector<CEnemyAction> enemyAction;
	//移動方向 1左 2左上 3上 4右上 5右 6右下 7下 8左下 0移動なし
	int moveDirection;
	float xDefoltPos;
	float yDefoltPos;
	chipPos pos;
	pos.x = x;
	pos.y = y;

	int zigFront[] = { 1,2,3,2,1,8,7,8 };
	int zigBack[] = { 5,4,3,4,5,6,7,6 };
	int zigIndex = 0;
	int indexCount = 0;
	int moveCount = 1;
	//移動無しならば即終了
	if (m_mapChipPatern == 2) {
		return enemyAction;
	}
	//初期座標記録
	xDefoltPos = x;
	yDefoltPos = y;

	//移動方向リセット
	this->m_saveDirection = 0;
	cocos2d::log("dire= %d ---------------", position);
	if (position == 0) {
		//出現位置が右の場合
		pos = checkMove(x,y,direction,1);
		
	}
	else if (position == 1) {
		//出現位置が左の場合
		pos = checkMove(x, y, direction, 5);

	}
	else if (position == 2) {
		//出現位置が上の場合
		//pos = checkMove(x, y, direction, 7);
		pos.x = x;
		pos.y = y - 1;
		this->m_saveDirection = 7;
		//moveCount = 0;
	}
	else if (position == 3) {
		//出現位置が下の場合
		//pos = checkMove(x, y, direction, 3);
		pos.x = x;
		pos.y = y + 1;
		this->m_saveDirection = 3;
		//moveCount = 0;
	}
	moveDirection = this->m_saveDirection;

	//移動スピード(1セル移動に何回行動するか)
	int speed = 20;
	//方向カウントリセット
	this->m_dirCount = 0;


	//マップ端まで来たら直線移動
	if (!direction && pos.x == MAX_MAP_DATA_X - 1) {
		CEnemyAction action;
		action.x = 40 / speed;
		action.y = 0;
		action.frame = 10000;// +(moveDirection == 0 ? speed : 0);

		enemyAction.push_back(action);
		return enemyAction;
	}
	if (direction && pos.x == 0) {
		CEnemyAction action;
		action.x = -40 / speed;
		action.y = 0;
		action.frame = 10000;// +(moveDirection == 0 ? speed : 0);

		enemyAction.push_back(action);
		return enemyAction;
	}


	//移動無しなら終了
	if (moveDirection == 0) {
		
		return enemyAction;
	}
	x = pos.x;
	y = pos.y;
	m_pMapData[x][y].m_test = -1;
	cocos2d::log("%d ** %d",pos.x,pos.y);
	cocos2d::log("position = %d,m_mapChipPatern = %d  direction = %d",position,m_mapChipPatern,moveDirection);
	
	//右から左に移動
		
	if (m_mapChipPatern == 0) {
		//直進
		
		for (int i = 0; i < 30;i++) {
			int stdDir = checkDir(x, y, direction, m_mapChipPatern, position);
			pos = checkMove(x, y, direction, stdDir);
			x = pos.x;
			y = pos.y;
			//m_test
			m_pMapData[x][y].m_test = -1;
			cocos2d::log("%d -- %d dire = %d stdDir=%d",x,y, this->m_saveDirection,stdDir);

			//移動方向が変更になったら
			if (this->m_saveDirection != moveDirection) {
				CEnemyAction action;
				action.x = m_dataX[moveDirection - 1] * (40 / speed);
				action.y = m_dataY[moveDirection - 1] * (40 / speed);
				action.frame = speed * moveCount;
				cocos2d::log("dire=%d x=%d y=%d frame=%d", moveDirection,m_dataX[moveDirection - 1], m_dataY[moveDirection - 1], action.frame);

				moveDirection = this->m_saveDirection;
				
				enemyAction.push_back(action);
				if (moveDirection == 0) {
					break;
				}
				moveCount = 1;
			}
			else {
				moveCount++;
			}
		}
		//移動があるなら追加
		if (moveCount && moveDirection != 0) {
			CEnemyAction action;
			action.x = m_dataX[moveDirection - 1] * (40 / speed);
			action.y = m_dataY[moveDirection - 1] * (40 / speed);
			action.frame = speed * moveCount;
			
			moveDirection = this->m_saveDirection;
			enemyAction.push_back(action);
		}
		//マップ端まで来たら直線移動
		if (!direction && pos.x == MAX_MAP_DATA_X - 1) {
			CEnemyAction action;
			action.x = 40 / speed;
			action.y = 0;
			action.frame = 10000;

			enemyAction.push_back(action);
			return enemyAction;
		}
		if (direction && pos.x == 0) {
			CEnemyAction action;
			action.x = -40 / speed;
			action.y = 0;
			action.frame = 10000;

			enemyAction.push_back(action);
			return enemyAction;
		}
		

	}else if(m_mapChipPatern == 1) {
		//ジグザグ
	}
	else if (m_mapChipPatern == 2) {
		//移動無し
	}
	if (direction) {
		
			

		
	}
	else if(direction == 1){
		//左から右に移動

	}
	return enemyAction;
}

/**
*@desc 周囲を調査して移動可能方向を調べる
*@param x座標
*@param y座標
*@param 方向　true...右 false...左
*@param //基本移動方向 1左 2左上 3上 4右上 5右 6右下 7下 8左下 0移動なし
*/
MapData::chipPos MapData::checkMove(int x, int y, bool direction,int stdDir) {
	//方向指定なしなら移動無しを返す
	if (!(stdDir > 0 && stdDir < 9)) {
		this->m_saveDirection = 0;
		return createChip(x,y);
	}
	else {
		//配列用にマイナスする
		stdDir--;
	}

	//方向候補1
	bool m_dire1[8] = { false,false,false,false,false,false,false,false };
	//方向候補2
	bool m_dire2[8] = { false,false,false,false,false,false,false,false };

	//x方向補正用 [stdDir][方向]
	int m_stdX[8][8] = {
		{ -1,-1,0,1,1,1,0,-1 },
		{ -1,0,1,1,1,0,-1,-1 },
		{ 0,1,1,1,0,-1,-1,-1 },
		{ 1,1,1,0,-1,-1,-1,0 },
		{ 1,1,0,-1,-1,-1,0,1 },
		{ 1,0,-1,-1,-1,0,1,1 },
		{ 0,-1,-1,-1,0,1,1,1 },
		{ -1,-1,-1,0,1,1,1,0 }
	};
	//y方向補正用 [stdDir][方向]
	int m_stdY[8][8] = {
		{ 0,1,1,1,0,-1,-1,-1 },
		{ 1,1,1,0,-1,-1,-1,0 },
		{ 1,1,0,-1,-1,-1,0,1 },
		{ 1,0,-1,-1,-1,0,1,1 },
		{ 0,-1,-1,-1,0,1,1,1 },
		{ -1,-1,-1,0,1,1,1,0 },
		{ -1,-1,0,1,1,1,0,-1 },
		{ -1,0,1,1,1,0,-1,-1 }
	};
	//方向記録用
	int m_saveDirection[8][8] = {
		{ 1,2,3,4,5,6,7,8 },
		{ 2,3,4,5,6,7,8,1 },
		{ 3,4,5,6,7,8,1,2 },
		{ 4,5,6,7,8,1,2,3 },
		{ 5,6,7,8,1,2,3,4 },
		{ 6,7,8,1,2,3,4,5 },
		{ 7,8,1,2,3,4,5,6 },
		{ 8,1,2,3,4,5,6,7 }
	};

	//優先順位
	int rank;
	//判定用
	bool flg;

	//リターン用chipPos
	chipPos pos;

	//全方向調査する
	for (int k = 0; k < 8; k++) {
		//エリア外か壁に当たるかチェック
		if (areaCheck(x + m_dataX[k], y + m_dataY[k]) ||
			m_pMapData[x + m_dataX[k]][y + m_dataY[k]].m_mapChipPatern != 0) {
			//移動不可なので飛ばす
			continue;
		}

		//斜め移動の時に角抜け可能かチェック
		if ((k + 1) % 2 == 0 &&
				(
					areaCheck(x + m_stdX[k][1], y + m_stdY[k][1]) ||
					m_pMapData[x + m_stdX[k][1]][y + m_stdY[k][1]].m_mapChipPatern != 0 ||
					areaCheck(x + m_stdX[k][7], y + m_stdY[k][7]) ||
					m_pMapData[x + m_stdX[k][7]][y + m_stdY[k][7]].m_mapChipPatern != 0
				)
			) {
			//角抜け不可なので飛ばす
			continue;
		}
		
		rank = direction ? m_pMapData[x][y].m_frontRank : m_pMapData[x][y].m_backRank;
		
		if ((direction ? m_pMapData[x + m_dataX[k]][y + m_dataY[k]].m_frontRank < rank :
		m_pMapData[x + m_dataX[k]][y + m_dataY[k]].m_backRank < rank)) {
			//現在の順位よりも高い順位に移動できる
			m_dire1[k] = true;
		}
		
		if ((direction ? m_pMapData[x + m_dataX[k]][y + m_dataY[k]].m_frontRank == rank :
			m_pMapData[x + m_dataX[k]][y + m_dataY[k]].m_backRank == rank)) {
			//現在の順位と同じだが周囲に現在の順位より高いマスがある
			flg = false;
			for (int i = -1; i < 2 && !flg; i++) {
				for (int j = -1; j < 2 && !flg; j++) {
					
					if (!areaCheck(x + i + m_dataX[k], y + j + m_dataY[k]) &&
						m_pMapData[x + i + m_dataX[k]][y + j + m_dataY[k]].m_mapChipPatern == 0 &&
						(direction ? m_pMapData[x + i + m_dataX[k]][y + j + m_dataY[k]].m_frontRank < rank :
					m_pMapData[x + i + m_dataX[k]][y + j + m_dataY[k]].m_backRank < rank)) {
						
						flg = true;
						m_dire2[k] = true;
						cocos2d::log("ok");
					}
				}
			}
			
		}
	}
	cocos2d::log("%d,%d,%d,%d,%d,%d,%d,%d",
		(int)m_dire1[0], (int)m_dire1[1], (int)m_dire1[2], (int)m_dire1[3], (int)m_dire1[4], (int)m_dire1[5], (int)m_dire1[6], (int)m_dire1[7] );
	cocos2d::log("%d,%d,%d,%d,%d,%d,%d,%d",
		(int)m_dire2[0], (int)m_dire2[1], (int)m_dire2[2], (int)m_dire2[3], (int)m_dire2[4], (int)m_dire2[5], (int)m_dire2[6], (int)m_dire2[7]);

	//移動可能判定
	bool m_stdBool1[8][8]{
		{ m_dire1[0],m_dire1[1],m_dire1[2],m_dire1[3],m_dire1[4],m_dire1[5],m_dire1[6],m_dire1[7] },
		{ m_dire1[1],m_dire1[2],m_dire1[3],m_dire1[4],m_dire1[5],m_dire1[6],m_dire1[7],m_dire1[0] },
		{ m_dire1[2],m_dire1[3],m_dire1[4],m_dire1[5],m_dire1[6],m_dire1[7],m_dire1[0],m_dire1[1] },
		{ m_dire1[3],m_dire1[4],m_dire1[5],m_dire1[6],m_dire1[7],m_dire1[0],m_dire1[1],m_dire1[2] },
		{ m_dire1[4],m_dire1[5],m_dire1[6],m_dire1[7],m_dire1[0],m_dire1[1],m_dire1[2],m_dire1[3] },
		{ m_dire1[5],m_dire1[6],m_dire1[7],m_dire1[0],m_dire1[1],m_dire1[2],m_dire1[3],m_dire1[4] },
		{ m_dire1[6],m_dire1[7],m_dire1[0],m_dire1[1],m_dire1[2],m_dire1[3],m_dire1[4],m_dire1[5] },
		{ m_dire1[7],m_dire1[0],m_dire1[1],m_dire1[2],m_dire1[3],m_dire1[4],m_dire1[5],m_dire1[6] },
	};
	//移動可能判定
	bool m_stdBool2[8][8]{
		{ m_dire2[0],m_dire2[1],m_dire2[2],m_dire2[3],m_dire2[4],m_dire2[5],m_dire2[6],m_dire2[7] },
		{ m_dire2[1],m_dire2[2],m_dire2[3],m_dire2[4],m_dire2[5],m_dire2[6],m_dire2[7],m_dire2[0] },
		{ m_dire2[2],m_dire2[3],m_dire2[4],m_dire2[5],m_dire2[6],m_dire2[7],m_dire2[0],m_dire2[1] },
		{ m_dire2[3],m_dire2[4],m_dire2[5],m_dire2[6],m_dire2[7],m_dire2[0],m_dire2[1],m_dire2[2] },
		{ m_dire2[4],m_dire2[5],m_dire2[6],m_dire2[7],m_dire2[0],m_dire2[1],m_dire2[2],m_dire2[3] },
		{ m_dire2[5],m_dire2[6],m_dire2[7],m_dire2[0],m_dire2[1],m_dire2[2],m_dire2[3],m_dire2[4] },
		{ m_dire2[6],m_dire2[7],m_dire2[0],m_dire2[1],m_dire2[2],m_dire2[3],m_dire2[4],m_dire2[5] },
		{ m_dire2[7],m_dire2[0],m_dire2[1],m_dire2[2],m_dire2[3],m_dire2[4],m_dire2[5],m_dire2[6] },
	};

	int m_random = rand() % 2;

	if (m_stdBool1[stdDir][0]) {//１位優先
		pos = createChip(x + m_stdX[stdDir][0] , y + m_stdY[stdDir][0]);
		this->m_saveDirection = m_saveDirection[stdDir][0];
	}
	else if (m_stdBool1[stdDir][1] && m_stdBool1[stdDir][7]) {//２位優先
		pos = createChip(x + m_stdX[stdDir][1], y + (m_random ? m_stdY[stdDir][1] : m_stdY[stdDir][7]));
		this->m_saveDirection = m_random ? m_saveDirection[stdDir][1] : m_saveDirection[stdDir][7];
	}
	else if (m_stdBool1[stdDir][1]) {//２位優先
		pos = createChip(x + m_stdX[stdDir][1], y + m_stdY[stdDir][1]);
		this->m_saveDirection = m_saveDirection[stdDir][1];
	}
	else if (m_stdBool1[stdDir][7]) {//２位優先
		pos = createChip(x + m_stdX[stdDir][7], y + m_stdY[stdDir][7]);
		this->m_saveDirection = m_saveDirection[stdDir][7];
	}
	else if (m_stdBool1[stdDir][2] && m_stdBool1[stdDir][6]) {//３位優先
		pos = createChip(x + m_stdX[stdDir][2], y + (m_random ? +m_stdY[stdDir][2] : +m_stdY[stdDir][6]));
		this->m_saveDirection = m_random ? m_saveDirection[stdDir][2] : m_saveDirection[stdDir][6];
	}
	else if (m_stdBool1[stdDir][2]) {//３位優先
		pos = createChip(x + m_stdX[stdDir][2], y + m_stdY[stdDir][2]);
		this->m_saveDirection = m_saveDirection[stdDir][2];
	}
	else if (m_stdBool1[stdDir][6]) {//３位優先
		pos = createChip(x + m_stdX[stdDir][6], y + m_stdY[stdDir][6]);
		this->m_saveDirection = m_saveDirection[stdDir][6];
	}
	else if (m_stdBool1[stdDir][3] && m_stdBool1[stdDir][5]) {//４位優先
		pos = createChip(x + m_stdX[stdDir][3], y + (m_random ? +m_stdY[stdDir][3] : +m_stdY[stdDir][5]));
		this->m_saveDirection = m_random ? m_saveDirection[stdDir][3] : m_saveDirection[stdDir][5];
	}
	else if (m_stdBool1[stdDir][3]) {//４位優先
		pos = createChip(x + m_stdX[stdDir][3], y + m_stdY[stdDir][3]);
		this->m_saveDirection = m_saveDirection[stdDir][3];
	}
	else if (m_stdBool1[stdDir][5]) {//４位優先
		pos = createChip(x + m_stdX[stdDir][5], y + m_stdY[stdDir][5]);
		this->m_saveDirection = m_saveDirection[stdDir][5];
	}
	else if (m_stdBool1[stdDir][4]) {//５位優先
		pos = createChip(x + m_stdX[stdDir][4], y + m_stdY[stdDir][4]);
		this->m_saveDirection = m_saveDirection[stdDir][4];
	}
	else if (m_stdBool2[stdDir][0]) {//１位予備
		pos = createChip(x + m_stdX[stdDir][0], y + m_stdY[stdDir][0]);
		this->m_saveDirection = m_saveDirection[stdDir][0];
	}
	else if (m_stdBool2[stdDir][1] && m_stdBool2[stdDir][7]) {//２位予備
		pos = createChip(x + m_stdX[stdDir][1], y + (m_random ? m_stdY[stdDir][1] : m_stdY[stdDir][7]));
		this->m_saveDirection = m_random ? m_saveDirection[stdDir][1] : m_saveDirection[stdDir][7];
	}
	else if (m_stdBool2[stdDir][1]) {//２位予備
		pos = createChip(x + m_stdX[stdDir][1], y + m_stdY[stdDir][1]);
		this->m_saveDirection = m_saveDirection[stdDir][1];
	}
	else if (m_stdBool2[stdDir][7]) {//２位予備
		pos = createChip(x + m_stdX[stdDir][7], y + m_stdY[stdDir][7]);
		this->m_saveDirection = m_saveDirection[stdDir][7];
	}
	else if (m_stdBool2[stdDir][2] && m_stdBool2[stdDir][6]) {//３位予備
		pos = createChip(x + m_stdX[stdDir][2], y + (m_random ? +m_stdY[stdDir][2] : +m_stdY[stdDir][6]));
		this->m_saveDirection = m_random ? m_saveDirection[stdDir][2] : m_saveDirection[stdDir][6];
	}
	else if (m_stdBool2[stdDir][2]) {//３位予備
		pos = createChip(x + m_stdX[stdDir][2], y + m_stdY[stdDir][2]);
		this->m_saveDirection = m_saveDirection[stdDir][2];
	}
	else if (m_stdBool2[stdDir][6]) {//３位予備
		pos = createChip(x + m_stdX[stdDir][6], y + m_stdY[stdDir][6]);
		this->m_saveDirection = m_saveDirection[stdDir][6];
	}
	else if (m_stdBool1[stdDir][3] && m_stdBool1[stdDir][5]) {//４位予備
		pos = createChip(x + m_stdX[stdDir][3], y + (m_random ? +m_stdY[stdDir][3] : +m_stdY[stdDir][5]));
		this->m_saveDirection = m_random ? m_saveDirection[stdDir][3] : m_saveDirection[stdDir][5];
	}
	else if (m_stdBool1[stdDir][3]) {//４位予備
		pos = createChip(x + m_stdX[stdDir][3], y + m_stdY[stdDir][3]);
		this->m_saveDirection = m_saveDirection[stdDir][3];
	}
	else if (m_stdBool1[stdDir][5]) {//４位予備
		pos = createChip(x + m_stdX[stdDir][5], y + m_stdY[stdDir][5]);
		this->m_saveDirection = m_saveDirection[stdDir][5];
	}
	else if (m_stdBool2[stdDir][4]) {//５位予備
		pos = createChip(x + m_stdX[stdDir][4], y + m_stdY[stdDir][4]);
		this->m_saveDirection = m_saveDirection[stdDir][4];
	}
	else {//移動無し
		pos = createChip(x,y);
		this->m_saveDirection = 0;
		cocos2d::log("no move");
	}
	return pos;
}

/*
*@desc 方向を返す
*@param x座標
*@param y座標
*@param 方向 true...左 false...右
*@param 移動パターン
*@param 出現方向 0...右 1...左 2...上 3...下
*@return 基準方向
*/
int MapData::checkDir(int x, int y, int direction, int m_mapChipPatern, int position) {
	//基準方向
	int stdDir;
	//カウントが0なら目標高さ設定
	if (this->m_dirCount == 0) {
		this->m_dirHeight = rand() % 10 + 2;
		//次のカウントを設定
		this->m_dirCount = rand() % 5 + 2;
	}

	if (y == this->m_dirHeight) {
		//高さが同じなら
		stdDir = direction ? 1 : 5;
	}
	else if (y < this->m_dirHeight) {
		//高さが低いなら
		stdDir = direction ? 2 : 4;
	}
	else if (y > this->m_dirHeight) {
		//高さが高いなら
		stdDir = direction ? 8 : 6;
	}

	//カウントダウン
	this->m_dirCount--;

	return stdDir;
}

/*
*@desc ボス移動作成
*@param ボスランク
*@return 移動データ配列
*/
std::vector<CEnemyAction> MapData::bossEnemyMove(int rank) {
	std::vector<CEnemyAction> enemyAction;
	
	//移動スピード
	//int speed = 20;
	int m_speed[3][10] = {
		{20,20,10,10,20,10, 10,20,20, 10},
		{ 10,10,10,10,10,0, 0,0,0, 0 },
		{ 20,20,20,20,0,0, 0,0,0, 0 }
	};
	
	//移動配列
	int m_move[3][10] = {
		{ 2,6,0,4,2,0,4,6,2,0 },
		{ 2,8,6,8,2,0,4,6,2,0 },
		{ 1,7,5,3,0,0,0,0,0,0 }
	};
	//移動時間配列
	int m_moveCount[3][10] = {
		{ 4,7,12,12,7,12,12,7,3,0 },
		{ 4,2,7,2,3,0,0,0,0,0 },
		{ 5,5,5,5,0,0,0,0,0,0 }
	};

	//ランク別移動長さ
	int m_rankArray[3] = {9,5,4};
	
	//画面外から移動
	CEnemyAction action;
	action.x = m_dataX[0] * (40 / 20);
	action.y = m_dataY[0] * (40 / 20);
	action.frame = 20 * 5;
	enemyAction.push_back(action);

	//ループ処理
	for (int i = 0; i < m_rankArray[rank];i++) {
		CEnemyAction action;
		action.x = m_dataX[m_move[rank][i]] * (40 / m_speed[rank][i]);
		action.y = m_dataY[m_move[rank][i]] * (40 / m_speed[rank][i]);
		action.frame = m_speed[rank][i] * m_moveCount[rank][i];

		enemyAction.push_back(action);
	}
	return enemyAction;
}