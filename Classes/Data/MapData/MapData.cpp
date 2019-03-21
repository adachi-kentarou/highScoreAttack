#include "MapData.h"
#include "Constants.h"
#include "Scene/GameMain/GameMain.h"

/**
* @desc �}�b�v�쐻
* @param �V�[�h�l�A�����l�̓����_��
* @return ����
*/
MapData::chipData MapData::m_pMapData[MapData::MAX_MAP_DATA_X][MapData::MAX_MAP_DATA_Y];
std::vector<CEnemyLaunchData> MapData::m_pEnemyLaunchData;
int MapData::m_areaDataCount = 0;
float MapData::WALL_SPEED = 0.5f;
int MapData::m_seed;
void MapData::create(int m_seed) {
	//this->m_seed = m_seed;
	//�V�[�h�l�ݒ�
	srand(m_seed);
	int m_indexNum = 0;

	//�o���f�[�^�̉��
	m_pEnemyLaunchData.clear();
	//������
	m_areaDataCount = 0;
	WALL_SPEED = 0.5f;
	
	std::vector<chipPos> m_pchipVector;
	std::vector<chipPos>::iterator itr;
	//�}�b�v�̏�����
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

	//�X�e�[�W�f�[�^
	int stage_data[17][3] ={
		{ 5,4,3},	//�V��	
		{ 5,4,3 },	//��		
		{ 2,3,4 },	//�㏬�R	
		{ 2,3,4 },	//�����R	
		{ 2,3,3 },	//�㒆�R	
		{ 2,3,3 },	//�����R	
		{ 1,3,3 },	//���R	
		{ 1,3,3 },	//����R	
		{ 3,3,4 },	//������	
		{ 2,3,4 },	//������	
		{ 8,7,7 },	//�G1		
		{ 7,8,8 },	//�G2		
		{ 6,7,7 },	//�G3		
		{ 6,7,8 },	//�G4
		{ -1,-1,8 },//�G5
		{ -1,6,7 },	//�G6
		{ -1,6,7 }	//�G7
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
			10,		//������
			0,		//y��b	
			11,		//y����	
			5 + i / 2 + rand() % 5,//�G�̐�	
			m_data[0],	//�V��	
			m_data[1],	//��		
			m_data[2],	//�㏬�R	
			m_data[3],	//�����R	
			m_data[4],	//�㒆�R	
			m_data[5],	//�����R	
			m_data[6],	//���R	
			m_data[7],	//����R	
			m_data[8],	//������	
			m_data[9],	//������	
			m_data[10],	//�G1		
			m_data[11],	//�G2		
			m_data[12],	//�G3		
			m_data[13],	//�G4
			m_data[14],	//�G5
			m_data[15],	//�G6
			m_data[16]	//�G7
		);
	}

	//�G���A�f�[�^�J�E���g
	int m_count = 0;
	//���̃G���A�܂ł̃J�E���g
	int nextAreaCount = m_pAreaData[m_count].m_next - 1;
	

	//�ړ��������Z�b�g
	m_move = 0;

	//�G���A�J�E���g���Z�b�g
	m_areaDataCount = 0;

	//x���W�ݒ�
	m_posX = 0;
	//y���W�ݒ�
	m_posY = rand() % m_pAreaData[m_count].m_random + m_pAreaData[m_count].m_default + 1;

	//�ړ�����
	int moveX = rand() % 5 + 1;
	int moveY = rand() % m_pAreaData[m_count].m_random + m_pAreaData[m_count].m_default + 1 - m_posY;
	
	//�ŏ��̓}�b�v�����f���铹�����@���ɕǂ�z�u���Ȃ��悤�ɂ���̂Ń}�b�v�𔲂����邱�Ƃ��ۏ؂����
	//�[����[�܂Ń��[�v���ă}�b�v�ɓ�����������
	while (m_move < MAX_MAP_DATA_X) {
		//����ݒ�
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
		//�G���A��ݒ�
		for (int i = 1; i < 13;i++) {
			m_pMapData[m_move][i].m_area = m_count;
		}

		//���̈ړ��ݒ���s��
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
				//�ʘH�z�u
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
			//����y���ړ�������ݒ�
			moveY = rand() % m_pAreaData[m_count].m_random + m_pAreaData[m_count].m_default + 1 - m_posY;
		}
		//x�ړ������𑝂₷
		m_move++;
		//x���W�𑝂₷
		m_posX++;
	}

	//�G���A�̍ő�J�E���g���L�^
	int maxCount = m_count;
	m_count = 0;
	//�G���A�̎n�܂�̍��W
	int m_start = 0;
	//�G���A���[�v
	while (m_count < maxCount) {
		//��������e��ǔz�u����

		//�V��
		if (m_pAreaData[m_count].m_top) {
			//�G���A�̒[����[�܂Ń��[�v����
			for (int i = m_start; i <= m_start + m_pAreaData[m_count].m_next; i++) {
				//���������_���ݒ�
				int maxLength = rand() % 3 + 2;
				//x������y���ǐݒ�\�����𒲂ׂ�
				for (int j = 2; j <= maxLength; j++) {
					if (areaCheck(i, MAX_MAP_DATA_Y - j) || m_pMapData[i][MAX_MAP_DATA_Y - j].m_frontRank == -1) {
						//�ʘH���}�b�v�̒[�ɐڐG�����̂Œ��������܂�
						break;
					}
					//�ǂ�ݒ�
					m_pMapData[i][MAX_MAP_DATA_Y - j].m_mapChipPatern = 1;
				}
			}
		}

		//��
		if (m_pAreaData[m_count].m_bottom) {
			//�G���A�̒[����[�܂Ń��[�v����
			for (int i = m_start; i < m_start + m_pAreaData[m_count].m_next; i++) {
				//���������_���ݒ�
				int maxLength = rand() % 3 + 1;
				//x������y���ǐݒ�\�����𒲂ׂ�
				for (int j = 1; j <= maxLength; j++) {
					if (areaCheck(i,j) || m_pMapData[i][j].m_frontRank == -1) {
						//�ʘH���}�b�v�̒[�ɐڐG�����̂Œ��������܂�
						break;
					}
					//�ǂ�ݒ�
					m_pMapData[i][j].m_mapChipPatern = 1;
				}
			}
		}

		//�㏬�R
		if (m_pAreaData[m_count].m_topSmallHill) {
			createTopHill(3, 3, m_start, m_pAreaData[m_count].m_next);
		}

		//�����R
		if (m_pAreaData[m_count].m_bottomSmallHill) {
			createBottomHill(3,3,m_start, m_pAreaData[m_count].m_next);
		}

		//�㒆�R
		if (m_pAreaData[m_count].m_topMiddleHill) {
			createTopHill(6, 3, m_start, m_pAreaData[m_count].m_next);
		}

		//�����R
		if (m_pAreaData[m_count].m_bottomMiddleHill) {
			createBottomHill(6, 3, m_start, m_pAreaData[m_count].m_next);
		}

		//���R
		if (m_pAreaData[m_count].m_topLargeHill) {
			createTopHill(9, 3, m_start, m_pAreaData[m_count].m_next);
		}

		//���R
		if (m_pAreaData[m_count].m_bottomLargeHill) {
			createBottomHill(9, 3, m_start, m_pAreaData[m_count].m_next);
		}
		
		//���̃G���A�̎n�܂�̍��W��ݒ�
		m_start += m_pAreaData[m_count].m_next;
		m_count++;

	}

	m_count = 0;
	//�G���A�̎n�܂�̍��W
	m_start = 0;
	//�G���A���[�v
	while (m_count <= maxCount) {
		//������
		if (m_pAreaData[m_count].m_middleSmallRock) {
			createRock(5, m_start, m_pAreaData[m_count].m_next);
		}
		//������
		if (m_pAreaData[m_count].m_middleMiddleRock) {
			createRock(10, m_start, m_pAreaData[m_count].m_next);
		}
		//���̃G���A�̎n�܂�̍��W��ݒ�
		m_start += m_pAreaData[m_count].m_next;
		m_count++;
	}

	//j=0 �O j=1 ���
	for (int j = 0; j < 2;j++) {
		//���W�z������Z�b�g����
		m_pchipVector.clear();
		
		//�`�b�v���W�z��
		//�O�ړ����ʐݒ�
		//�ړ��惉���N
		int rank = 1;
		//�X�^�[�g�n�_��ݒ�
		for (int i = 1; i < 13; i++) {
			if (m_pMapData[j ? MAX_MAP_DATA_X : 0][i].m_mapChipPatern == 0) {
				j ? m_pMapData[j ? MAX_MAP_DATA_X - 1 : 0][i].m_backRank = rank : m_pMapData[j ? MAX_MAP_DATA_X - 1 : 0][i].m_frontRank = rank;
				//�`�b�v�ݒ�
				m_pchipVector.push_back(createChip(j ? MAX_MAP_DATA_X - 1: 0, i));
			}
		}

		while (m_pchipVector.size() != 0) {
			//�ړ����ʂ��グ��
			rank++;
			
			std::vector<chipPos> m_pchipVector2 = m_pchipVector;
			//���W�z������Z�b�g����
			m_pchipVector.clear();
			
			itr = m_pchipVector2.begin();
			while (itr != m_pchipVector2.end()) {
				//���͂Ɉړ��ł��邩�m�F���Ă���
				//��
				bool left = !areaCheck(itr->x - 1, itr->y) &&
					m_pMapData[itr->x - 1][itr->y].m_mapChipPatern == 0 &&
					(j ? m_pMapData[itr->x - 1][itr->y].m_backRank <= 0 :
						m_pMapData[itr->x - 1][itr->y].m_frontRank <= 0);
				//�E
				bool right = !areaCheck(itr->x + 1, itr->y) &&
					m_pMapData[itr->x + 1][itr->y].m_mapChipPatern == 0 &&
					(j ? m_pMapData[itr->x + 1][itr->y].m_backRank <= 0 :
						m_pMapData[itr->x + 1][itr->y].m_frontRank <= 0);
				//��
				bool top = !areaCheck(itr->x, itr->y + 1) &&
					m_pMapData[itr->x][itr->y + 1].m_mapChipPatern == 0 &&
					(j ? m_pMapData[itr->x][itr->y + 1].m_backRank <= 0 :
						m_pMapData[itr->x][itr->y + 1].m_frontRank <= 0);
				//��
				bool bottom = !areaCheck(itr->x, itr->y - 1) &&
					m_pMapData[itr->x][itr->y - 1].m_mapChipPatern == 0 &&
					(j ? m_pMapData[itr->x][itr->y - 1].m_backRank <= 0 :
						m_pMapData[itr->x][itr->y - 1].m_frontRank <= 0);
				//����
				bool leftTop = !areaCheck(itr->x - 1, itr->y + 1) &&
					m_pMapData[itr->x - 1][itr->y + 1].m_mapChipPatern == 0 &&
					(j ? m_pMapData[itr->x - 1][itr->y + 1].m_backRank <= 0 :
						m_pMapData[itr->x - 1][itr->y + 1].m_frontRank <= 0);
				//����
				bool leftBottom = !areaCheck(itr->x - 1, itr->y - 1) &&
					m_pMapData[itr->x - 1][itr->y - 1].m_mapChipPatern == 0 &&
					(j ? m_pMapData[itr->x - 1][itr->y - 1].m_backRank <= 0 :
						m_pMapData[itr->x - 1][itr->y - 1].m_frontRank <= 0);
				//�E��
				bool rightTop = !areaCheck(itr->x + 1, itr->y + 1) &&
					m_pMapData[itr->x + 1][itr->y + 1].m_mapChipPatern == 0 &&
					(j ? m_pMapData[itr->x + 1][itr->y + 1].m_backRank <= 0 :
						m_pMapData[itr->x + 1][itr->y + 1].m_frontRank <= 0);
				//�E��
				bool rightBottom = !areaCheck(itr->x + 1, itr->y - 1) &&
					m_pMapData[itr->x + 1][itr->y - 1].m_mapChipPatern == 0 &&
					(j ? m_pMapData[itr->x + 1][itr->y - 1].m_backRank <= 0 :
						m_pMapData[itr->x + 1][itr->y - 1].m_frontRank <= 0);

				//��
				if (left) {
					m_pchipVector.push_back(createChip(itr->x - 1, itr->y));
				}
				//�E
				if (right) {
					m_pchipVector.push_back(createChip(itr->x + 1, itr->y));
				}
				//��
				if (top) {
					m_pchipVector.push_back(createChip(itr->x, itr->y + 1));
				}
				//��
				if (bottom) {
					m_pchipVector.push_back(createChip(itr->x, itr->y - 1));
				}
				//����
				if (left && top && leftTop) {
					m_pchipVector.push_back(createChip(itr->x - 1, itr->y + 1));
				}
				//����
				if (left && bottom && leftBottom) {
					m_pchipVector.push_back(createChip(itr->x - 1, itr->y - 1));
				}
				//�E��
				if (right && top && rightTop) {
					m_pchipVector.push_back(createChip(itr->x + 1, itr->y + 1));
				}
				//�E��
				if (right && bottom && rightBottom) {
					m_pchipVector.push_back(createChip(itr->x + 1, itr->y - 1));
				}

				itr++;
			}
			//rank�K�p
			for (chipPos pos: m_pchipVector) {
				j ? m_pMapData[pos.x][pos.y].m_backRank = rank :
					m_pMapData[pos.x][pos.y].m_frontRank = rank;
			}

		}

	}

	//////////////////////////////////
	//��������G�̔z�u�ƈړ��o�H�ݒ�//
	//////////////////////////////////

	//�ړ��J�E���g
	int m_moveCounter = 0;
	//�ǈړ��X�s�[�h
	//int WALL_SPEED = 0.5;
	m_count = 0;
	//�G���A�̎n�܂�̍��W
	m_start = 0;
	//�G���A���[�v
	while (m_count <= maxCount) {
		
		//�G���z��
		std::vector<int> m_enemy;
		//�G�P�ǉ�
		if (m_pAreaData[m_count].m_enemy1) {
			m_enemy.push_back(1);
		}
		//�G�Q�ǉ�
		if (m_pAreaData[m_count].m_enemy2) {
			m_enemy.push_back(2);
		}
		//�G�R�ǉ�
		if (m_pAreaData[m_count].m_enemy3) {
			m_enemy.push_back(3);
		}
		//�G�S�ǉ�
		if (m_pAreaData[m_count].m_enemy4) {
			m_enemy.push_back(4);
		}
		//�G�T�ǉ�
		if (m_pAreaData[m_count].m_enemy5) {
			m_enemy.push_back(5);
		}
		//�G�U�ǉ�
		if (m_pAreaData[m_count].m_enemy6) {
			m_enemy.push_back(6);
		}
		//�G�V�ǉ�
		if (m_pAreaData[m_count].m_enemy7) {
			m_enemy.push_back(7);
		}

		//�o���G��₪�S�ĂȂ������ꍇ�͏����𔲂���
		if (m_enemy.size() == 0) {
			//���̃G���A�̎n�܂�̍��W��ݒ�
			m_start += m_pAreaData[m_count].m_next;
			m_count++;
			continue;
		}

		//�o���ʒu��⌟��
		//�S��
		std::vector<chipPos> allPos;
		//�ǎ���
		std::vector<chipPos> aroundPos;
		//�V��
		std::vector<chipPos> topPos;
		//��
		std::vector<chipPos> bottomPos;
		//�o���ʒu��⌟��
		//�G���A�̒[����[�܂Ń��[�v����
		for (int i = m_start; i < m_start + m_pAreaData[m_count].m_next;i++) {
			for (int j = 1; j < MAX_MAP_DATA_Y - 1; j++) {
				if (areaCheck(i, j)) {
					//�G���A�O�Ȃ��΂�
					continue;
				}

				chipPos pos;
				pos.x = i;
				pos.y = j;
				//�G���A��������
				if (m_pMapData[i][j].m_mapChipPatern == 0 && (m_pMapData[i][j].m_frontRank > 0 || m_pMapData[i][j].m_backRank > 0)) {
					//�S��
					allPos.push_back(pos);
					//����
					if (m_pMapData[i][j].m_mapChipPatern == 0 && (!areaCheck(i - 1, j) && m_pMapData[i - 1][j].m_mapChipPatern != 0 ||
						!areaCheck(i + 1, j) && m_pMapData[i + 1][j].m_mapChipPatern != 0 ||
						!areaCheck(i, j - 1) && m_pMapData[i][j - 1].m_mapChipPatern != 0 ||
						!areaCheck(i, j + 1) && m_pMapData[i][j + 1].m_mapChipPatern != 0
						)) {
						aroundPos.push_back(pos);
					}
					//�V��
					if (m_pMapData[i][j].m_mapChipPatern == 0 && j == MAX_MAP_DATA_Y - 2 &&
						(m_pMapData[i][j].m_frontRank > 0 || m_pMapData[i][j].m_backRank > 0)) {
						topPos.push_back(pos);
					}
					//��
					if (m_pMapData[i][j].m_mapChipPatern == 0 && j == 1 &&
						(m_pMapData[i][j].m_frontRank > 0 || m_pMapData[i][j].m_backRank > 0)) {
						bottomPos.push_back(pos);
					}
				}
			}
		}

		//�o���ʒu��₪�S�ĂȂ������ꍇ�͏����𔲂���
		if (allPos.size() == 0 && aroundPos.size() == 0 && topPos.size() == 0 && bottomPos.size() == 0) {
			//���̃G���A�̎n�܂�̍��W��ݒ�
			m_start += m_pAreaData[m_count].m_next;
			m_count++;
			continue;
		}

		cocos2d::log("--**--%d", m_pAreaData[m_count].m_enemyCount);
		//�G�̐��������[�v
		for (int i = 0; i < m_pAreaData[m_count].m_enemyCount;i++) {
			//�o���f�[�^
			CEnemyLaunchData enemyData;
			//�o���G�^�C�v
			int enemyType;
			//�o���^�C�v�z��
			std::vector<int> enemyTypeArray;
			//�o���G����z��ɓ����
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
			//���0�Ȃ�o�������I��
			if (!enemyTypeArray.size()) {
				break;
			}

			//�o���G����
			enemyType = enemyTypeArray[rand() % enemyTypeArray.size()];
			//enemyType = 4;
			//���W
			chipPos pos;
			//�o���^�C�~���O
			int timing;
			//�o���ʒu�␳
			float remainder;
			//�o���������
			std::vector<int> directionArray;
			//�o������
			int direction;
			bool bdirection = true;
			int position;
			//�z��Y�����L���p
			int index;
			//�ړ��p�^�[��
			int m_mapChipPatern = 0;
			//�G�P
			//���W�ݒ�
			//�o���������
			//�O��
			if ((enemyType == 1 || enemyType == 5) && allPos.size() != 0) {
				directionArray.push_back(1);
				directionArray.push_back(2);
			}
			//��
			if ((enemyType == 2 || enemyType == 6) && topPos.size() != 0) {
				directionArray.push_back(3);
			}
			//��
			if ((enemyType == 3 || enemyType == 7) && bottomPos.size() != 0) {
				directionArray.push_back(4);
			}
			//����
			if (enemyType == 4 && aroundPos.size() != 0) {
				directionArray.push_back(5);
				m_mapChipPatern = 2;
			}

			//�o����������
			direction = directionArray[rand() % directionArray.size()];
			//direction = 5;
			//x���o���ʒu���炷
			int shift = 0;
			//�ݒu����
			int install = 0;
			//���W�ݒ�
			switch (direction) {
			case 1://�E�[
				index = rand() % allPos.size();
				pos = allPos[index];
				bdirection = true;
				position = 0;
				//�z�񂩂�폜
				allPos.erase(allPos.begin() + index);
				break;
			case 2://���[
				index = rand() % allPos.size();
				pos = allPos[index];
				bdirection = false;
				position = 1;
				//�z�񂩂�폜
				allPos.erase(allPos.begin() + index); 
				shift = 17;
				break;
			case 3://��
				index = rand() % topPos.size();
				pos = topPos[index];
				bdirection = rand() % 2 ? true : false;
				position = 2;
				//�z�񂩂�폜
				topPos.erase(topPos.begin() + index);
				//��ʊO�ɐݒ�
				pos.y += 1;
				shift = bdirection ? (rand() % 5) : (rand() % 5 + 11);
				//shift = 5;
				break;
			case 4://��
				index = rand() % bottomPos.size();
				pos = bottomPos[index];
				bdirection = rand() % 2 ? true : false;
				position = 3;
				//�z�񂩂�폜
				bottomPos.erase(bottomPos.begin() + index);
				//��ʊO�ɐݒ�
				pos.y -= 1;
				shift = bdirection ? (rand() % 5) : (rand() % 5 + 11);
				break;
			case 5://����
				index = rand() % aroundPos.size();
				pos = aroundPos[index];
				bdirection = true;
				position = 4;
				//�z�񂩂�폜
				aroundPos.erase(aroundPos.begin() + index);

				//�ݒu����
				std::vector<int> ins;
				//��
				if(!areaCheck(pos.x,pos.y - 1) && m_pMapData[pos.x][pos.y - 1].m_mapChipPatern != 0){
					ins.push_back(0);
				}
				//��
				if (!areaCheck(pos.x - 1, pos.y) && m_pMapData[pos.x - 1][pos.y].m_mapChipPatern != 0) {
					ins.push_back(1);
				}
				//��
				if (!areaCheck(pos.x, pos.y + 1) && m_pMapData[pos.x][pos.y + 1].m_mapChipPatern != 0) {
					ins.push_back(2);
				}
				//�E
				if (!areaCheck(pos.x + 1, pos.y) && m_pMapData[pos.x + 1][pos.y].m_mapChipPatern != 0) {
					ins.push_back(3);
				}
				//�ݒu����
				if (ins.size()) {
					install = ins[rand() % ins.size()];
					cocos2d::log("size= %d install = %d", ins.size(),install);
				}

				break;

			}

			//�E�[
			m_pMapData[pos.x][pos.y].m_test = -1;
			cocos2d::log("%d - %d", pos.x, pos.y);
			

			timing = (pos.x + shift) * 40 / WALL_SPEED;
			remainder = ((pos.x + shift) * 40) - (timing * WALL_SPEED);
			//�o���f�[�^
			enemyData.m_frame = timing;
			enemyData.m_posX = 660 - remainder - (shift * 40);
			enemyData.m_posY = 40 * (pos.y - 1) + 20;
			

			//�G�^�C�v
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
			
			//�i�s����
			enemyData.direction = bdirection;
			enemyData.install = install;
			//�s��
			enemyData.action = enemyMove(pos.x, pos.y, bdirection, position, m_mapChipPatern);
			//�A�C�e���ݒ�
			if (rand() % 4 == 0) {
				enemyData.m_item = (ITEM_TYPE)(rand() % 11);
			}
			else {
				enemyData.m_item = (ITEM_TYPE)-1;
			}
			//�o���z��Ɋi�[
			m_pEnemyLaunchData.push_back(enemyData);
			

			switch (enemyType) {
			case 1:
				
				switch (direction) {
				case 1:
					
					break;

				}
				break;
			case 2:
				//�G�Q
				break;
			case 3:
				//�G�R
				break;
			case 4:
				//�G�S
				break;
			case 5:
				//�G�T
				break;
			case 6:
				//�G�U
				break;
			case 7:
				//�G�V
				break;
			default:
				break;
			}
			//�o���ʒu�ݒ�
			
			
		}
		//���̃G���A�̎n�܂�̍��W��ݒ�
		m_start += m_pAreaData[m_count].m_next;
		m_count++;
	}
	//�{�X�o���f�[�^

	//�{�X�o��x���W
	int bossX = 118;

				  //�{�X�o��y���W
	int bossY = 6;
	//�V�t�g
	int shift = 0;

	CEnemyLaunchData enemyData;
	int timing = (bossX + shift) * 40 / WALL_SPEED;
	int remainder = ((bossX + shift) * 40) - (timing * WALL_SPEED);
	//�o���f�[�^
	enemyData.m_frame = timing;
	enemyData.m_posX = 660 - remainder - (shift * 40) + 100;
	enemyData.m_posY = 40 * (bossY - 1) + 20;

	//�G�^�C�v
	enemyData.m_type = ENEMY_TYPE::TYPE_BOSS_1;

	//�i�s����
	enemyData.direction = true;
	enemyData.install = 1;

	enemyData.m_actionType = ACTION_TYPE::BOSS_1;
	enemyData.action = bossEnemyMove(CGameMain::m_stageNo - 1);
	m_pEnemyLaunchData.push_back(enemyData);





	//�o���f�[�^���t���[���Ń\�[�g����
	// name���L�[�ɏ����Ń\�[�g
	sort(m_pEnemyLaunchData.begin(), m_pEnemyLaunchData.end(),
		[](const CEnemyLaunchData& x, const CEnemyLaunchData& y) { return x.m_frame < y.m_frame; });
	cocos2d::log("------sort-------");
	for (CEnemyLaunchData a : m_pEnemyLaunchData) {
		cocos2d::log("frame=%d", a.m_frame);
	}

	//�ǎ�ސݒ�
	for (int i = 0; i < MAX_MAP_DATA_X; i++) {
		for (int j = 0; j < MAX_MAP_DATA_Y; j++) {
			if (m_pMapData[i][j].m_mapChipPatern == 1) {
				m_pMapData[i][j].m_mapChipPatern = (int)(rand() % 2) + 1 + (CGameMain::m_stageNo -1) * 2;
			}
		}
	}
}

/*
*@desc �`�b�v�쐬
@param x���W
@param y���W
*/
MapData::chipPos MapData::createChip(int x, int y) {
	MapData::chipPos chip;
	chip.x = x;
	chip.y = y;
	return chip;
}

/*
*@desc �}�b�v��R�쐬
*@param �^�񒆍���
*@param �����_��
*@param �G���A�n��
*@param �G���A�I���
*/
void MapData::createTopHill(int hight,int random,int start,int next) {
	//�G���A�͈͂̍�����������
	int m_indexNum = 0;
	//�ŏ�����1�ݒ�
	int m_maxHight = 1;

	int m_xIndex[100];

	int m_randx;

	int m_vMaxX;
	//�G���A�̒[����[�܂Ń��[�v����
	for (int i = start; i < start + next; i++) {
		//�ŏ�����4�ō쐬�\�ꏊ���G���A���Ō���

		int j;

		for (j = 2; j < m_maxHight + 2; j++) {
			if (m_pMapData[i][MAX_MAP_DATA_Y - j].m_frontRank == -1) {
				break;
			}
		}
		if (j == m_maxHight + 2) {
			//����OK			
			m_xIndex[m_indexNum] = i;
			//�v�f�����₷
			m_indexNum++;
		}

	}

	//�z�u��₪����ꍇ
	if (m_indexNum != 0) {
		//�z�u�ꏊ�I��
		m_randx = rand() % m_indexNum;
		//�����ύX 4+�����_��
		m_maxHight = rand() % random + hight;
		//�R�����z�u
		for (int j = 2; j < m_maxHight + 2; j++) {
			//�i�H�ɂԂ���Ȃ璆�f
			if (m_pMapData[m_xIndex[m_randx]][MAX_MAP_DATA_Y - j].m_frontRank == -1) {
				break;
			}
			m_pMapData[m_xIndex[m_randx]][MAX_MAP_DATA_Y - j].m_mapChipPatern = 1;
		}
		//������������
		m_vMaxX = m_maxHight + 2 - (rand() % random);
		//�i�s�����ɎR�z�u
		for (int i = m_xIndex[m_randx] + 1; i < start + next; i++) {
			int j;
			for (j = 2; j < m_vMaxX; j++) {
				//�i�H�ɂԂ���Ȃ璆�f
				if (m_pMapData[i][MAX_MAP_DATA_Y - j].m_frontRank == -1) {
					break;
				}

				m_pMapData[i][MAX_MAP_DATA_Y - j].m_mapChipPatern = 1;
			}
			//�I�����̍������炳��Ƀ����_���ō�����Ⴍ����
			m_vMaxX = j - (rand() % 3);
			//����0�Ȃ璆�f
			if (m_vMaxX <= 2) {
				break;
			}

		}

		//������������
		m_vMaxX = m_maxHight + 2 - (rand() % random);
		//��ޕ����ɎR�z�u
		for (int i = m_xIndex[m_randx] - 1; i >= start; i--) {
			int j;
			for (j = 2; j < m_vMaxX; j++) {
				//�i�H�ɂԂ���Ȃ璆�f
				if (m_pMapData[i][MAX_MAP_DATA_Y - j].m_frontRank == -1) {
					break;
				}

				m_pMapData[i][MAX_MAP_DATA_Y - j].m_mapChipPatern = 1;
			}
			//�I�����̍������炳��Ƀ����_���ō�����Ⴍ����
			m_vMaxX = j - (rand() % 3);
			//����0�Ȃ璆�f
			if (m_vMaxX <= 2) {
				break;
			}

		}

	}
	else {
		//�z�u�s��;
		cocos2d::log("no topSmallHill");
	}
}

/*
*@desc �}�b�v���R�쐬
*@param �^�񒆍���
*@param �����_��
*@param �G���A�n��
*@param �G���A�I���
*/
void MapData::createBottomHill(int hight, int random, int start, int next) {
	//�G���A�͈͂̍�����������
	int indexNum = 0;
	//�ŏ�����1�ݒ�
	int m_maxHight = 1;

	int m_xIndex[100];

	int m_randx;

	int vMaxX;
	//�G���A�̒[����[�܂Ń��[�v����
	for (int i = start; i < start + next; i++) {
		//�ŏ�����4�ō쐬�\�ꏊ���G���A���Ō���

		int j;

		for (j = 1; j < m_maxHight + 1; j++) {
			if (m_pMapData[i][j].m_frontRank == -1) {
				break;
			}
		}
		if (j == m_maxHight + 1) {
			//����OK			
			m_xIndex[indexNum] = i;
			//�v�f�����₷
			indexNum++;
		}

	}

	//�z�u��₪����ꍇ
	if (indexNum != 0) {
		//�z�u�ꏊ�I��
		m_randx = rand() % indexNum;
		//�����ύX 4+�����_��
		m_maxHight = rand() % random + hight;
		//�R�����z�u
		for (int j = 1; j < m_maxHight + 1; j++) {
			//�i�H�ɂԂ���Ȃ璆�f
			if (m_pMapData[m_xIndex[m_randx]][j].m_frontRank == -1) {
				break;
			}
			m_pMapData[m_xIndex[m_randx]][j].m_mapChipPatern = 1;
		}
		//������������
		vMaxX = m_maxHight + 1 - (rand() % 3);
		//�i�s�����ɎR�z�u
		for (int i = m_xIndex[m_randx] + 1; i < start + next; i++) {
			int j;
			for (j = 1; j < vMaxX; j++) {
				//�i�H�ɂԂ���Ȃ璆�f
				if (m_pMapData[i][j].m_frontRank == -1) {
					break;
				}

				m_pMapData[i][j].m_mapChipPatern = 1;
			}
			//�I�����̍������炳��Ƀ����_���ō�����Ⴍ����
			vMaxX = j - (rand() % 3);
			//����0�Ȃ璆�f
			if (vMaxX <= 1) {
				break;
			}

		}

		//������������
		vMaxX = m_maxHight + 1 - (rand() % hight);
		//��ޕ����ɎR�z�u
		for (int i = m_xIndex[m_randx] - 1; i >= start; i--) {
			int j;
			for (j = 1; j < vMaxX; j++) {
				//�i�H�ɂԂ���Ȃ璆�f
				if (m_pMapData[i][j].m_frontRank == -1) {
					break;
				}

				m_pMapData[i][j].m_mapChipPatern = 1;
			}
			//�I�����̍������炳��Ƀ����_���ō�����Ⴍ����
			vMaxX = j - (rand() % hight);
			//����0�Ȃ璆�f
			if (vMaxX <= 1) {
				break;
			}

		}

	}
	else {
		//�z�u�s��;
		cocos2d::log("no bottomSmallHill");
	}
}

/*
*@desc ��쐬
*@param ��T�C�Y
*@param ��
*@param �G���A�n��
*@param �G���A�I���
*/
void MapData::createRock(int size, int start, int next) {
	
	std::vector<chipPos> m_pchipVector;
	std::vector<chipPos> m_pchipVector2;
	std::vector<chipPos> m_pchipVector3;
	std::vector<chipPos>::iterator itr;
	int rockSize;
	int chipCount = 0;
	int rockcount;

	//�ǈȊO�̃`�b�v�̐��𐔂���
	//�G���A�̒[����[�܂Ń��[�v����
	for (int i = start; i < start + next; i++) {

		//x������y���ǐݒ�\�����𒲂ׂ�
		for (int j = 1; j < MAX_MAP_DATA_Y - 1; j++) {
			if (m_pMapData[i][j].m_mapChipPatern == 0) {
				chipCount++;
			}
		}
	}
	//�`�b�v�̐��ɍ��킹�Ċ�̌��ύX
	rockcount = rand() % (chipCount / (size * 4) + 1) + 1;
	
	//��̌������[�v����
	while (rockcount != 0) {
		//��̃T�C�Y��ݒ肷��
		rockSize = rand() % size;

		//�}�b�v�`�b�v�z�����ɂ���
		m_pchipVector.clear();

		//�G���A�̒[����[�܂Ń��[�v����
		for (int i = start; i < start + next; i++) {

			//x������y���ǐݒ�\�����𒲂ׂ�
			for (int j = 1; j < MAX_MAP_DATA_Y - 1; j++) {

				bool m_check = true;
				//���͂̍��W���`�F�b�N
				for (int k = -1; k < 2; k++) {
					for (int l = -1; l < 2; l++) {
						if (areaCheck(i + k, j + l)) {
							continue;
						}

						if (m_pMapData[i + k][j + l].m_mapChipPatern == 1) {
							//��ʊO���ʘH���ǂɗאڂ���̂ŃA�E�g
							m_check = false;
						}
					}
				}
				if (m_check && m_pMapData[i][j].m_frontRank != -1) {
					//���Ȃ���Δz��ɍ��W��o�^
					m_pchipVector.push_back(createChip(i, j));

					//���ǂ�ݒ�
					m_pMapData[i][j].m_mapChipPatern = -1;
				}

			}
		}
		
		//�z�u��₪�����ꍇ�͏I��
		if (m_pchipVector.size() == 0) {
			return;
		}

		chipPos m_prandPoint;
		//��̑傫��
		//��̃T�C�Y�J�E���g
		int rockSizeCount = 0;
		//�����_���l
		int random;

		//�}�b�v�`�b�v�z�����ɂ���
		m_pchipVector2.clear();

		//�C�e���[�^�[�̐ݒ�
		itr = m_pchipVector.begin();
		//���_���W�������_���Ŏw��
		if (m_pchipVector.size() != 0) {
			random = rand() % m_pchipVector.size();
			m_prandPoint = m_pchipVector[random];
			m_pMapData[m_prandPoint.x][m_prandPoint.y].m_mapChipPatern = 1;
			//�z�u�`�b�v�z��ɒǉ�
			m_pchipVector2.push_back(m_pchipVector[random]);
			//���W��z�񂩂�폜
			m_pchipVector.erase(itr + random);

		}

		//�w�肵�����W���烉���_���Ɋg������
		//�w�肵���T�C�Y�ɂȂ�����g���I��
		while (rockSizeCount != rockSize) {

			//�}�b�v�`�b�v�z�����ɂ���
			m_pchipVector3.clear();

			//�㉺���E�̔z�u�ł���`�b�v��T��
			//�z�u�`�b�v�z�񂩂�T��
			itr = m_pchipVector2.begin();
			while (itr != m_pchipVector2.end()) {
				//���W���G���A���ŉ��ǔ͈͓��ł���Ό��ɒǉ�����
				if (!areaCheck(itr->x + 1, itr->y) && m_pMapData[itr->x + 1][itr->y].m_mapChipPatern == -1) {
					m_pchipVector3.push_back(createChip(itr->x + 1, itr->y));
					//�d���ǉ���h�����߂Ƀp�^�[���l��ύX
					m_pMapData[itr->x + 1][itr->y].m_mapChipPatern = -2;
				}
				if (!areaCheck(itr->x - 1, itr->y) && m_pMapData[itr->x - 1][itr->y].m_mapChipPatern == -1) {
					m_pchipVector3.push_back(createChip(itr->x - 1, itr->y));
					//�d���ǉ���h�����߂Ƀp�^�[���l��ύX
					m_pMapData[itr->x - 1][itr->y].m_mapChipPatern = -2;
				}
				if (!areaCheck(itr->x, itr->y + 1) && m_pMapData[itr->x][itr->y + 1].m_mapChipPatern == -1) {
					m_pchipVector3.push_back(createChip(itr->x, itr->y + 1));
					//�d���ǉ���h�����߂Ƀp�^�[���l��ύX
					m_pMapData[itr->x][itr->y + 1].m_mapChipPatern = -2;
				}
				if (!areaCheck(itr->x, itr->y - 1) && m_pMapData[itr->x][itr->y - 1].m_mapChipPatern == -1) {
					m_pchipVector3.push_back(createChip(itr->x, itr->y - 1));
					//�d���ǉ���h�����߂Ƀp�^�[���l��ύX
					m_pMapData[itr->x][itr->y - 1].m_mapChipPatern = -2;
				}

				itr++;
			}
			//�d���ǉ��ύX�����ɖ߂�
			itr = m_pchipVector.begin();
			while (itr != m_pchipVector.end()) {
				if (m_pMapData[itr->x][itr->y].m_mapChipPatern == -2) {
					m_pMapData[itr->x][itr->y].m_mapChipPatern = -1;
				}
				itr++;
			}

			//�z�u��₪�����ꍇ�͊�g���I��
			if (m_pchipVector3.size() == 0) {
				break;
			}

			//�����_���Ɋg������
			random = rand() % m_pchipVector3.size();
			m_pMapData[m_pchipVector3[random].x][m_pchipVector3[random].y].m_mapChipPatern = 1;
			//�z�u�`�b�v�z��ɍ��W��ǉ�
			m_pchipVector2.push_back(createChip(m_pchipVector3[random].x, m_pchipVector3[random].y));
			//�z�u�J�E���g�𑝂₷
			rockSizeCount++;

		}
		//�������ɖ߂�
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
	int next = 1,//���̃G���A�܂ł̋���
	int default = 0,//y����b�l
	int random = MAX_MAP_DATA_Y,//y�������l
	int enemyCount = 0,//�G�̐�
	bool top = false,//�V��݂�t���O
	bool bottom = false,//���݂�t���O
	bool topSmallHill = false,//�㏬�R
	bool bottomSmallHill = false,//�����R
	bool topMiddleHill = false,//�㒆�R
	bool bottomMiddleHill = false,//�����R
	bool topLargeHill = false,//���R
	bool bottomLargeHill = false,//����R
	bool middleSmallRock = false,//������
	bool middleMiddleRock = false,//������
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
*@desc �}�b�v�G���A�O�`�F�b�N
*@param x���W
*@param y���W
*@return true...�G���A�O false...�G���A��
*/
bool MapData::areaCheck(int x, int y) {
	if (x < 0 || x>= MAX_MAP_DATA_X || y < 1 || y >= MAX_MAP_DATA_Y - 1) {
		return true;
	}
	return false;
}

/*
*@desc �G�̓���
*@param x���W
*@param y���W
*@param �ړ����� true...�E false...��
*@param �o���ꏊ 0�E 1�� 2�� 3��
*@param �ړ��p�^�[�� 0���i 1�W�O�U�O 2�ړ�����
*/
std::vector<CEnemyAction> MapData::enemyMove(int x, int y, bool direction,int position, int m_mapChipPatern) {
	std::vector<CEnemyAction> enemyAction;
	//�ړ����� 1�� 2���� 3�� 4�E�� 5�E 6�E�� 7�� 8���� 0�ړ��Ȃ�
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
	//�ړ������Ȃ�Α��I��
	if (m_mapChipPatern == 2) {
		return enemyAction;
	}
	//�������W�L�^
	xDefoltPos = x;
	yDefoltPos = y;

	//�ړ��������Z�b�g
	this->m_saveDirection = 0;
	cocos2d::log("dire= %d ---------------", position);
	if (position == 0) {
		//�o���ʒu���E�̏ꍇ
		pos = checkMove(x,y,direction,1);
		
	}
	else if (position == 1) {
		//�o���ʒu�����̏ꍇ
		pos = checkMove(x, y, direction, 5);

	}
	else if (position == 2) {
		//�o���ʒu����̏ꍇ
		//pos = checkMove(x, y, direction, 7);
		pos.x = x;
		pos.y = y - 1;
		this->m_saveDirection = 7;
		//moveCount = 0;
	}
	else if (position == 3) {
		//�o���ʒu�����̏ꍇ
		//pos = checkMove(x, y, direction, 3);
		pos.x = x;
		pos.y = y + 1;
		this->m_saveDirection = 3;
		//moveCount = 0;
	}
	moveDirection = this->m_saveDirection;

	//�ړ��X�s�[�h(1�Z���ړ��ɉ���s�����邩)
	int speed = 20;
	//�����J�E���g���Z�b�g
	this->m_dirCount = 0;


	//�}�b�v�[�܂ŗ����璼���ړ�
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


	//�ړ������Ȃ�I��
	if (moveDirection == 0) {
		
		return enemyAction;
	}
	x = pos.x;
	y = pos.y;
	m_pMapData[x][y].m_test = -1;
	cocos2d::log("%d ** %d",pos.x,pos.y);
	cocos2d::log("position = %d,m_mapChipPatern = %d  direction = %d",position,m_mapChipPatern,moveDirection);
	
	//�E���獶�Ɉړ�
		
	if (m_mapChipPatern == 0) {
		//���i
		
		for (int i = 0; i < 30;i++) {
			int stdDir = checkDir(x, y, direction, m_mapChipPatern, position);
			pos = checkMove(x, y, direction, stdDir);
			x = pos.x;
			y = pos.y;
			//m_test
			m_pMapData[x][y].m_test = -1;
			cocos2d::log("%d -- %d dire = %d stdDir=%d",x,y, this->m_saveDirection,stdDir);

			//�ړ��������ύX�ɂȂ�����
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
		//�ړ�������Ȃ�ǉ�
		if (moveCount && moveDirection != 0) {
			CEnemyAction action;
			action.x = m_dataX[moveDirection - 1] * (40 / speed);
			action.y = m_dataY[moveDirection - 1] * (40 / speed);
			action.frame = speed * moveCount;
			
			moveDirection = this->m_saveDirection;
			enemyAction.push_back(action);
		}
		//�}�b�v�[�܂ŗ����璼���ړ�
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
		//�W�O�U�O
	}
	else if (m_mapChipPatern == 2) {
		//�ړ�����
	}
	if (direction) {
		
			

		
	}
	else if(direction == 1){
		//������E�Ɉړ�

	}
	return enemyAction;
}

/**
*@desc ���͂𒲍����Ĉړ��\�����𒲂ׂ�
*@param x���W
*@param y���W
*@param �����@true...�E false...��
*@param //��{�ړ����� 1�� 2���� 3�� 4�E�� 5�E 6�E�� 7�� 8���� 0�ړ��Ȃ�
*/
MapData::chipPos MapData::checkMove(int x, int y, bool direction,int stdDir) {
	//�����w��Ȃ��Ȃ�ړ�������Ԃ�
	if (!(stdDir > 0 && stdDir < 9)) {
		this->m_saveDirection = 0;
		return createChip(x,y);
	}
	else {
		//�z��p�Ƀ}�C�i�X����
		stdDir--;
	}

	//�������1
	bool m_dire1[8] = { false,false,false,false,false,false,false,false };
	//�������2
	bool m_dire2[8] = { false,false,false,false,false,false,false,false };

	//x�����␳�p [stdDir][����]
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
	//y�����␳�p [stdDir][����]
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
	//�����L�^�p
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

	//�D�揇��
	int rank;
	//����p
	bool flg;

	//���^�[���pchipPos
	chipPos pos;

	//�S������������
	for (int k = 0; k < 8; k++) {
		//�G���A�O���ǂɓ����邩�`�F�b�N
		if (areaCheck(x + m_dataX[k], y + m_dataY[k]) ||
			m_pMapData[x + m_dataX[k]][y + m_dataY[k]].m_mapChipPatern != 0) {
			//�ړ��s�Ȃ̂Ŕ�΂�
			continue;
		}

		//�΂߈ړ��̎��Ɋp�����\���`�F�b�N
		if ((k + 1) % 2 == 0 &&
				(
					areaCheck(x + m_stdX[k][1], y + m_stdY[k][1]) ||
					m_pMapData[x + m_stdX[k][1]][y + m_stdY[k][1]].m_mapChipPatern != 0 ||
					areaCheck(x + m_stdX[k][7], y + m_stdY[k][7]) ||
					m_pMapData[x + m_stdX[k][7]][y + m_stdY[k][7]].m_mapChipPatern != 0
				)
			) {
			//�p�����s�Ȃ̂Ŕ�΂�
			continue;
		}
		
		rank = direction ? m_pMapData[x][y].m_frontRank : m_pMapData[x][y].m_backRank;
		
		if ((direction ? m_pMapData[x + m_dataX[k]][y + m_dataY[k]].m_frontRank < rank :
		m_pMapData[x + m_dataX[k]][y + m_dataY[k]].m_backRank < rank)) {
			//���݂̏��ʂ����������ʂɈړ��ł���
			m_dire1[k] = true;
		}
		
		if ((direction ? m_pMapData[x + m_dataX[k]][y + m_dataY[k]].m_frontRank == rank :
			m_pMapData[x + m_dataX[k]][y + m_dataY[k]].m_backRank == rank)) {
			//���݂̏��ʂƓ����������͂Ɍ��݂̏��ʂ�荂���}�X������
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

	//�ړ��\����
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
	//�ړ��\����
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

	if (m_stdBool1[stdDir][0]) {//�P�ʗD��
		pos = createChip(x + m_stdX[stdDir][0] , y + m_stdY[stdDir][0]);
		this->m_saveDirection = m_saveDirection[stdDir][0];
	}
	else if (m_stdBool1[stdDir][1] && m_stdBool1[stdDir][7]) {//�Q�ʗD��
		pos = createChip(x + m_stdX[stdDir][1], y + (m_random ? m_stdY[stdDir][1] : m_stdY[stdDir][7]));
		this->m_saveDirection = m_random ? m_saveDirection[stdDir][1] : m_saveDirection[stdDir][7];
	}
	else if (m_stdBool1[stdDir][1]) {//�Q�ʗD��
		pos = createChip(x + m_stdX[stdDir][1], y + m_stdY[stdDir][1]);
		this->m_saveDirection = m_saveDirection[stdDir][1];
	}
	else if (m_stdBool1[stdDir][7]) {//�Q�ʗD��
		pos = createChip(x + m_stdX[stdDir][7], y + m_stdY[stdDir][7]);
		this->m_saveDirection = m_saveDirection[stdDir][7];
	}
	else if (m_stdBool1[stdDir][2] && m_stdBool1[stdDir][6]) {//�R�ʗD��
		pos = createChip(x + m_stdX[stdDir][2], y + (m_random ? +m_stdY[stdDir][2] : +m_stdY[stdDir][6]));
		this->m_saveDirection = m_random ? m_saveDirection[stdDir][2] : m_saveDirection[stdDir][6];
	}
	else if (m_stdBool1[stdDir][2]) {//�R�ʗD��
		pos = createChip(x + m_stdX[stdDir][2], y + m_stdY[stdDir][2]);
		this->m_saveDirection = m_saveDirection[stdDir][2];
	}
	else if (m_stdBool1[stdDir][6]) {//�R�ʗD��
		pos = createChip(x + m_stdX[stdDir][6], y + m_stdY[stdDir][6]);
		this->m_saveDirection = m_saveDirection[stdDir][6];
	}
	else if (m_stdBool1[stdDir][3] && m_stdBool1[stdDir][5]) {//�S�ʗD��
		pos = createChip(x + m_stdX[stdDir][3], y + (m_random ? +m_stdY[stdDir][3] : +m_stdY[stdDir][5]));
		this->m_saveDirection = m_random ? m_saveDirection[stdDir][3] : m_saveDirection[stdDir][5];
	}
	else if (m_stdBool1[stdDir][3]) {//�S�ʗD��
		pos = createChip(x + m_stdX[stdDir][3], y + m_stdY[stdDir][3]);
		this->m_saveDirection = m_saveDirection[stdDir][3];
	}
	else if (m_stdBool1[stdDir][5]) {//�S�ʗD��
		pos = createChip(x + m_stdX[stdDir][5], y + m_stdY[stdDir][5]);
		this->m_saveDirection = m_saveDirection[stdDir][5];
	}
	else if (m_stdBool1[stdDir][4]) {//�T�ʗD��
		pos = createChip(x + m_stdX[stdDir][4], y + m_stdY[stdDir][4]);
		this->m_saveDirection = m_saveDirection[stdDir][4];
	}
	else if (m_stdBool2[stdDir][0]) {//�P�ʗ\��
		pos = createChip(x + m_stdX[stdDir][0], y + m_stdY[stdDir][0]);
		this->m_saveDirection = m_saveDirection[stdDir][0];
	}
	else if (m_stdBool2[stdDir][1] && m_stdBool2[stdDir][7]) {//�Q�ʗ\��
		pos = createChip(x + m_stdX[stdDir][1], y + (m_random ? m_stdY[stdDir][1] : m_stdY[stdDir][7]));
		this->m_saveDirection = m_random ? m_saveDirection[stdDir][1] : m_saveDirection[stdDir][7];
	}
	else if (m_stdBool2[stdDir][1]) {//�Q�ʗ\��
		pos = createChip(x + m_stdX[stdDir][1], y + m_stdY[stdDir][1]);
		this->m_saveDirection = m_saveDirection[stdDir][1];
	}
	else if (m_stdBool2[stdDir][7]) {//�Q�ʗ\��
		pos = createChip(x + m_stdX[stdDir][7], y + m_stdY[stdDir][7]);
		this->m_saveDirection = m_saveDirection[stdDir][7];
	}
	else if (m_stdBool2[stdDir][2] && m_stdBool2[stdDir][6]) {//�R�ʗ\��
		pos = createChip(x + m_stdX[stdDir][2], y + (m_random ? +m_stdY[stdDir][2] : +m_stdY[stdDir][6]));
		this->m_saveDirection = m_random ? m_saveDirection[stdDir][2] : m_saveDirection[stdDir][6];
	}
	else if (m_stdBool2[stdDir][2]) {//�R�ʗ\��
		pos = createChip(x + m_stdX[stdDir][2], y + m_stdY[stdDir][2]);
		this->m_saveDirection = m_saveDirection[stdDir][2];
	}
	else if (m_stdBool2[stdDir][6]) {//�R�ʗ\��
		pos = createChip(x + m_stdX[stdDir][6], y + m_stdY[stdDir][6]);
		this->m_saveDirection = m_saveDirection[stdDir][6];
	}
	else if (m_stdBool1[stdDir][3] && m_stdBool1[stdDir][5]) {//�S�ʗ\��
		pos = createChip(x + m_stdX[stdDir][3], y + (m_random ? +m_stdY[stdDir][3] : +m_stdY[stdDir][5]));
		this->m_saveDirection = m_random ? m_saveDirection[stdDir][3] : m_saveDirection[stdDir][5];
	}
	else if (m_stdBool1[stdDir][3]) {//�S�ʗ\��
		pos = createChip(x + m_stdX[stdDir][3], y + m_stdY[stdDir][3]);
		this->m_saveDirection = m_saveDirection[stdDir][3];
	}
	else if (m_stdBool1[stdDir][5]) {//�S�ʗ\��
		pos = createChip(x + m_stdX[stdDir][5], y + m_stdY[stdDir][5]);
		this->m_saveDirection = m_saveDirection[stdDir][5];
	}
	else if (m_stdBool2[stdDir][4]) {//�T�ʗ\��
		pos = createChip(x + m_stdX[stdDir][4], y + m_stdY[stdDir][4]);
		this->m_saveDirection = m_saveDirection[stdDir][4];
	}
	else {//�ړ�����
		pos = createChip(x,y);
		this->m_saveDirection = 0;
		cocos2d::log("no move");
	}
	return pos;
}

/*
*@desc ������Ԃ�
*@param x���W
*@param y���W
*@param ���� true...�� false...�E
*@param �ړ��p�^�[��
*@param �o������ 0...�E 1...�� 2...�� 3...��
*@return �����
*/
int MapData::checkDir(int x, int y, int direction, int m_mapChipPatern, int position) {
	//�����
	int stdDir;
	//�J�E���g��0�Ȃ�ڕW�����ݒ�
	if (this->m_dirCount == 0) {
		this->m_dirHeight = rand() % 10 + 2;
		//���̃J�E���g��ݒ�
		this->m_dirCount = rand() % 5 + 2;
	}

	if (y == this->m_dirHeight) {
		//�����������Ȃ�
		stdDir = direction ? 1 : 5;
	}
	else if (y < this->m_dirHeight) {
		//�������Ⴂ�Ȃ�
		stdDir = direction ? 2 : 4;
	}
	else if (y > this->m_dirHeight) {
		//�����������Ȃ�
		stdDir = direction ? 8 : 6;
	}

	//�J�E���g�_�E��
	this->m_dirCount--;

	return stdDir;
}

/*
*@desc �{�X�ړ��쐬
*@param �{�X�����N
*@return �ړ��f�[�^�z��
*/
std::vector<CEnemyAction> MapData::bossEnemyMove(int rank) {
	std::vector<CEnemyAction> enemyAction;
	
	//�ړ��X�s�[�h
	//int speed = 20;
	int m_speed[3][10] = {
		{20,20,10,10,20,10, 10,20,20, 10},
		{ 10,10,10,10,10,0, 0,0,0, 0 },
		{ 20,20,20,20,0,0, 0,0,0, 0 }
	};
	
	//�ړ��z��
	int m_move[3][10] = {
		{ 2,6,0,4,2,0,4,6,2,0 },
		{ 2,8,6,8,2,0,4,6,2,0 },
		{ 1,7,5,3,0,0,0,0,0,0 }
	};
	//�ړ����Ԕz��
	int m_moveCount[3][10] = {
		{ 4,7,12,12,7,12,12,7,3,0 },
		{ 4,2,7,2,3,0,0,0,0,0 },
		{ 5,5,5,5,0,0,0,0,0,0 }
	};

	//�����N�ʈړ�����
	int m_rankArray[3] = {9,5,4};
	
	//��ʊO����ړ�
	CEnemyAction action;
	action.x = m_dataX[0] * (40 / 20);
	action.y = m_dataY[0] * (40 / 20);
	action.frame = 20 * 5;
	enemyAction.push_back(action);

	//���[�v����
	for (int i = 0; i < m_rankArray[rank];i++) {
		CEnemyAction action;
		action.x = m_dataX[m_move[rank][i]] * (40 / m_speed[rank][i]);
		action.y = m_dataY[m_move[rank][i]] * (40 / m_speed[rank][i]);
		action.frame = m_speed[rank][i] * m_moveCount[rank][i];

		enemyAction.push_back(action);
	}
	return enemyAction;
}