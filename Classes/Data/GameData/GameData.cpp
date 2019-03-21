#include"GameData.h"
//デストラクタ
CGameData::~CGameData() {
	delete this;
}
CGameData::CGameData() {
	
}
//ゲームBGM
int CGameData::gameBgm;
//ゲームSE
int CGameData::gameSe;

//シーン遷移中終了回避フラグ
bool CGameData::sceneEnd;