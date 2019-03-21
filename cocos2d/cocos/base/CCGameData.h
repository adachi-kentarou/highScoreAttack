#ifndef __CCGAMEDATA_H__
#define __CCGAMEDATA__

#include "platform/CCPlatformMacros.h"

/**
* @addtogroup base
* @js NA
* @lua NA
*/
NS_CC_BEGIN



class CC_DLL GameData {
public:
	~GameData();
	GameData();
	//ゲームbgm
	static int gameBgm;
	//ゲームSE
	static int gameSe;
	//スコア
	static int score;
	//スコア
	static int gamePad;

	//リプレイデータ
	static int replayData[];

	//シーン遷移中終了回避フラグ
	static bool sceneEnd;

	//ゲーム難易度 0...easy 1...normal 2...hard
	static int gameMode;
};

// 入力フラグマクロ
#define BGM_VOLUME (GameData::gameBgm)
#define SE_VOLUME (GameData::gameSe)
#define SCORE (GameData::score)
#define GAME_PAD (GameData::gamePad)
#define REPLAY_DATA (GameData::replayData)
#define SCENE_END (GameData::sceneEnd)
#define GAME_MODE (GameData::gameMode)
NS_CC_END

/** @} */
#endif // __CCGAMEDATA_H__