#pragma once
#ifndef ShootingGame_GameData_h
#define ShootingGame_GameData_h

//#include "cocos2d.h"
//#include "Constants.h"
/*
*	�Q�[���f�[�^�N���X
*
*		�V�[�����܂����ŕK�v�ȃf�[�^�͂����ɏW�߂�
*
*
*/
class CGameData {
public:
	~CGameData();
	CGameData();
	//�Q�[��bgm
	static int gameBgm;
	//�Q�[��SE
	static int gameSe;

	//�V�[���J�ڒ��I������t���O
	static bool sceneEnd;

};

// ���̓t���O�}�N��
//#define BGM_VOLUME (CGameData::gameBgm)
//#define SE_VOLUME (CGameData::gameSe)
//#define SCENE_END (CGameData::sceneEnd)

#endif