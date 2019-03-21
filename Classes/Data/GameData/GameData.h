#pragma once
#ifndef ShootingGame_GameData_h
#define ShootingGame_GameData_h

//#include "cocos2d.h"
//#include "Constants.h"
/*
*	ゲームデータクラス
*
*		シーンをまたいで必要なデータはここに集める
*
*
*/
class CGameData {
public:
	~CGameData();
	CGameData();
	//ゲームbgm
	static int gameBgm;
	//ゲームSE
	static int gameSe;

	//シーン遷移中終了回避フラグ
	static bool sceneEnd;

};

// 入力フラグマクロ
//#define BGM_VOLUME (CGameData::gameBgm)
//#define SE_VOLUME (CGameData::gameSe)
//#define SCENE_END (CGameData::sceneEnd)

#endif