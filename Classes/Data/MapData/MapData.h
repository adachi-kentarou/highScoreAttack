#pragma once
#ifndef __ShootingGame__MapData__
#define __ShootingGame__MapData__
#include <stdlib.h>
#include <time.h>
#include "Data/EnemyLaunchData/EnemyLaunchData.h"


class MapData {
public:
	//�S�̃}�b�v�T�C�Y
	static const int MAX_MAP_DATA_X = 100;
	static const int MAX_MAP_DATA_Y = 14;

	static float WALL_SPEED;

	/*
	* @desk �}�b�v�`�b�v�f�[�^
	*/
	struct chipData {
		//�}�b�v�`�b�v�p�^�[��
		int m_mapChipPatern = 0;
		//�G���A
		int m_area;
		//�O�ړ��揇��
		int m_frontRank = 0;
		//��ړ��揇��
		int m_backRank = 0;
		//test
		int m_test = 0;
	};
	/*
	* @desk �`�b�v�|�W�V�����f�[�^
	*/
	struct chipPos {
		//x���W
		int x;
		//y���W
		int y;
	};

	/*
	*@desc �`�b�v�쐬
	@param x���W
	@param y���W
	*/
	chipPos createChip(int x,int y);
	
	//�`�b�v�|�W�V�����v�f��
	int indexChipPos;
	//�`�b�v�|�W�V�����z��
	chipPos m_pchipPos[100];
	
	//�}�b�v�f�[�^�i�[
	static chipData m_pMapData[MAX_MAP_DATA_X][MAX_MAP_DATA_Y];
	

	//�}�b�v�쐻�σt���O true...�쐬�ς݁@false...���쐬
	bool m_pCreateFlg = false;
	
	//�}�b�v�쐻�p���W
	int m_posX;
	int m_posY;
	
	//�}�b�v�ړ�����
	int m_move;

	/**
	* @desc �}�b�v�쐻
	* @param �V�[�h�l�A�����l�̓����_��
	* @return ����
	*/
	void create(int seed);
	
	/*
	* @desk �}�b�v�G���A�f�[�^
	*/
	struct areaData {
		//���̃G���A�܂ł̋���
		int m_next = 1;
		
		//�ʘHY���������p�����[�^
		//��b�l
		int m_default = 0;
		//�����l
		int m_random = MAX_MAP_DATA_Y;
		int m_enemyCount = 0;
		//�V��݂�t���O
		bool m_top = false;
		//���݂�t���O
		bool m_bottom = false;
		//�㏬�R
		bool m_topSmallHill = false;
		//�����R
		bool m_bottomSmallHill = false;
		//�㒆�R
		bool m_topMiddleHill = false;
		//�����R
		bool m_bottomMiddleHill = false;
		//���R
		bool m_topLargeHill = false;
		//����R
		bool m_bottomLargeHill = false;
		//������
		bool m_middleSmallRock = false;
		//������
		bool m_middleMiddleRock = false;
		//�G1
		bool m_enemy1 = false;
		//�G2
		bool m_enemy2 = false;
		//�G3
		bool m_enemy3 = false;
		//�G4
		bool m_enemy4 = false;
		//�G5
		bool m_enemy5 = false;
		//�G6
		bool m_enemy6 = false;
		//�G7
		bool m_enemy7 = false;

	};
	//�G���A�f�[�^�z��
	areaData m_pAreaData[10];
	//std::vector<areaData> m_pAreaData;
	//�G���A�f�[�^�J�E���g
	static int m_areaDataCount;
	void setAreaData(
		int next,//���̃G���A�܂ł̋���
		int default,//y����b�l
		int random,//y�������l
		int enemyCount,//�G�̐�
		bool top,//�V��݂�t���O
		bool bottom,//���݂�t���O
		bool topSmallHill,//�㏬�R
		bool bottomSmallHill,//�����R
		bool topMiddleHill,//�㒆�R
		bool bottomMiddleHill,//�����R
		bool topLargeHill,//���R
		bool bottomLargeHill,//����R
		bool middleSmallRock,//������
		bool middleMiddleRock,//������
		bool enemy1,
		bool enemy2,
		bool enemy3,
		bool enemy4,
		bool enemy5,
		bool enemy6,
		bool enemy7
	);
	/*
	*@desc �}�b�v�G���A�O�`�F�b�N
	*@param x���W
	*@param y���W
	*/
	bool areaCheck(int x,int y);
	/*
	*@desc �}�b�v��R�쐬
	*@param �^�񒆍���
	*@param �����␳
	*@param �G���A�n��
	*@param �G���A�I���
	*/
	void createTopHill(int height,int random,int start,int next);
	
	/*
	*@desc �}�b�v��R�쐬
	*@param �^�񒆍���
	*@param �����␳
	*@param �G���A�n��
	*@param �G���A�I���
	*/
	void createBottomHill(int height, int random, int start, int next);

	/*
	*@desc ��쐬
	*@param ��T�C�Y
	*@param �G���A�n��
	*@param �G���A�I���
	*/
	void createRock(int size, int start, int next);

	static std::vector<CEnemyLaunchData> m_pEnemyLaunchData;
	/*
	*@desc �G�̓���
	*@param x���W
	*@param y���W
	*@param �ړ����� true...�E false...��
	*@param �o���ꏊ 0�E 1�� 2�� 3��
	*@param �ړ��p�^�[��
	*/
	std::vector<CEnemyAction> enemyMove(int x,int y,bool direction, int position, int patern);
	
	/**
	*@desc ���͂𒲍����Ĉړ��\�����𒲂ׂ�
	*@param x���W
	*@param y���W
	*@param �����@true...�E false...��
	*/
	chipPos checkMove(int x,int y,bool direction,int stdDir);

	//�����L�^�p
	int m_saveDirection;

	//���͍��W�␳�p
	int m_dataX[9] = { -1,-1,0,1,1,1,0,-1,0 };
	int m_dataY[9] = { 0,1,1,1,0,-1,-1,-1,0 };

	//�����
	int checkDir(int x, int y, int direction, int patern, int position);
	//�����쐬�p�J�E���^�[
	int m_dirCount = 0;
	//int dirMaxCount;
	//�����쐬�p����
	int m_dirHeight;

	//�V�[�h�l
	static int m_seed;
	
	/*
	*@desc �{�X�ړ��쐬
	*@param �{�X�����N
	*@return �ړ��f�[�^�z��
	*/
	std::vector<CEnemyAction> bossEnemyMove(int rank);

};
#endif __ShootingGame__MapData__