#include "Map.h"
//�R���X�g���N�^
CMap::CMap() {

}
//�f�X�g���N�^
CMap::~CMap() {

}
/**
*@desc ����
*@param tmx�t�@�C����
*@return CMap�N���X�̃C���X�^���X
*@tips CREATE_FUMC�}�N���̒��g
*		�ÓI�����o�֐�
*/
CMap* CMap::create(std::string tmxFile) {
	//�}�b�v�N���X�𐶐�����
	CMap* pMap = new CMap();

	//TMXTiledMap�̏�����������
	//CMap�̏������������s��initWithTMXFile
	if (pMap->initWithFile(tmxFile) == true && pMap->init() == true) {
		//���������������玩��delet��ݒ�
		pMap->autorelease();
		//�}�b�v�N���X�̃C���X�^���X��Ԃ�
		return pMap;
	}
	//���������s���Ă�����}�b�v�N���X�̃C���X�^���X�����
	CC_SAFE_DELETE(pMap);
	//NULL��Ԃ�
	return NULL;
}

/**
*@desc �}�b�v�N���X�̏�����
*/
bool CMap::init() {
	/**
	*�X�N���[���I���ʒu�̌v�Z
	*/
	//�ʒu�Z�b�g
	this->m_scrollMove.setPos(0,0);
	
	//��ʃT�C�Y�̎擾
	cocos2d::Size winSize = cocos2d::Director::getInstance()->getWinSize();
	
	//�}�b�v�̏I���ʒu���擾
	this->m_scrollEndPos.x = (640) - winSize.width;
	

	//�������̈ʒu�̐ݒ�Ɣ��f
	this->m_scrollMove.setPos(640.0f,240.0f);
	this->setPosition(0.0f,0.0f);
	return true;
}

//�X�N���[��(�ړ�)����
void CMap::moveFunc() {
	//�}�b�v�X�N���[����X�ړ�����
	if (this->m_scrollMove.m_posX < -this->m_scrollEndPos.x) {
		if (m_isLoop == true) {
			//���[�v����ꍇ�̓}�b�v�̈ʒu��߂�
			this->m_scrollMove.m_posX = 640;
		}
		else {
			//���[�v���Ȃ��ꍇ�͏I���t���O���グ��
			this->m_isEnd = true;
		}
	}
	else {
		//�}�b�v���X�N���[��
		this->m_scrollMove.m_posX -= this->m_scrollMove.m_velX;
	}
}
//���ˏ���
void CMap::applyFunc() {
	//�}�b�v�̒l�̔��f����
	this->setPosition(this->m_scrollMove.m_posX, this->m_scrollMove.m_posY);
}