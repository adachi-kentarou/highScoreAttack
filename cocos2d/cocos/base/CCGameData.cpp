#include "base/CCGameData.h"

NS_CC_BEGIN
//�f�X�g���N�^
GameData::~GameData() {
	delete this;
}
GameData::GameData() {

}
//�Q�[��BGM
int GameData::gameBgm;
//�Q�[��SE
int GameData::gameSe;
//�X�R�A
int GameData::score;
//�Q�[���p�b�h
int GameData::gamePad;
//���v���C�f�[�^
int GameData::replayData[12020];
//�V�[���J�ڒ��I������t���O
bool GameData::sceneEnd;
//�Q�[����Փx 0...easy 1...normal 2...hard
int GameData::gameMode;
NS_CC_END
