#include"GameData.h"
//�f�X�g���N�^
CGameData::~CGameData() {
	delete this;
}
CGameData::CGameData() {
	
}
//�Q�[��BGM
int CGameData::gameBgm;
//�Q�[��SE
int CGameData::gameSe;

//�V�[���J�ڒ��I������t���O
bool CGameData::sceneEnd;