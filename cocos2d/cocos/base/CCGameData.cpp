#include "base/CCGameData.h"

NS_CC_BEGIN
//デストラクタ
GameData::~GameData() {
	delete this;
}
GameData::GameData() {

}
//ゲームBGM
int GameData::gameBgm;
//ゲームSE
int GameData::gameSe;
//スコア
int GameData::score;
//ゲームパッド
int GameData::gamePad;
//リプレイデータ
int GameData::replayData[12020];
//シーン遷移中終了回避フラグ
bool GameData::sceneEnd;
//ゲーム難易度 0...easy 1...normal 2...hard
int GameData::gameMode;
NS_CC_END
