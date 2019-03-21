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
	//�Q�[��bgm
	static int gameBgm;
	//�Q�[��SE
	static int gameSe;
	//�X�R�A
	static int score;
	//�X�R�A
	static int gamePad;

	//���v���C�f�[�^
	static int replayData[];

	//�V�[���J�ڒ��I������t���O
	static bool sceneEnd;

	//�Q�[����Փx 0...easy 1...normal 2...hard
	static int gameMode;
};

// ���̓t���O�}�N��
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