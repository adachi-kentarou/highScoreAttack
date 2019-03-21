#include "UserInterface.h"
#include "Constants.h"

//=========================================================================
//�@HP�\���p�̃��x���N���X�͂������珑��
//=========================================================================
//�R���X�g���N�^
CHpLabel::CHpLabel() {
	//�S�~����
	this->m_pStatus = NULL;
}
//�f�X�g���N�^
CHpLabel::~CHpLabel() {

}
bool CHpLabel::init() {

	//=========================================================================
	//	���[�U�[�C���^�[�t�F�[�X�̏������Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	//������̃t�H���g�^�C�v
	this->setSystemFontName("Arial");
	//������̃t�H���g�T�C�Y
	this->setSystemFontSize(24);
	//�A���J�[�|�C���g�ݒ�
	this->setAnchorPoint(cocos2d::Point(0.0f, 0.5f));

	//����
	this->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
	//�ʒu�̐ݒ�
	this->setPosition(cocos2d::Point(WINDOW_RIGHT * 0.0f, WINDOW_TOP * 0.97f));
	
	//�����čX�V�������Ăяo��
	this->scheduleUpdate();
	return true;
}

void CHpLabel::update(float deltaTime_)
{
	if (this->m_pStatus == NULL)
		return;

	//�\������HP�𕶎���ɕϊ�
	std::string hpStr = cocos2d::StringUtils::format("HP:%d", this->m_pStatus->getHp());

	this->setString(hpStr);

}

//=========================================================================
//�@HP�Q�[�W�̃N���X�̊֐��̒�`�͂������珑��
//=========================================================================
//�R���X�g���N�^
CHpGuage::CHpGuage() {
	//�S�~����
	this->m_pStatus = NULL;
}
//�f�X�g���N�^
CHpGuage::~CHpGuage() {

}
//����������
bool CHpGuage::init() {


	//HP�Q�[�W�Ŏg�p����摜�𐶐�
	cocos2d::Sprite* pSprite = cocos2d::Sprite::create(IMAGE_FILE_HP_GUAGE);

	//���������X�v���C�g���g���Ċ��N���X�̏��������s��
	if (cocos2d::ProgressTimer::initWithSprite(pSprite) == false) {
		CCLOG("CHpGuage() ProgressTimer::initWithSprite is false!!");
		return false;
	}

	//�v���O���X�^�C�}�[�̏����̒�����ݒ�@�o�[�̓p�[�Z���e�[�W�ŕ\��
	this->setPercentage(0.0f);
	//�v���O���X�^�C�}�[�̃^�C�v��ݒ�(�o�[�ɐݒ�)
	this->setType(cocos2d::ProgressTimer::Type::BAR);
	//�v���O���X�o�[�̐L�т����(X�����ɐݒ�)
	this->setBarChangeRate(cocos2d::Point(1,0));
	//�v���O���X�^�C�}�[�o�[�̊�_(�����ɐݒ�)
	this->setMidpoint(cocos2d::Point(0,0));
	//�v���O���X�^�C�}�[�o�[�̈ʒu��ݒ�
	this->setPosition(180.0f,468.0f);
	//�T�C�Y�ύX
	this->setScale(0.5f);

	//�X�V�����̐ݒ�
	this->scheduleUpdate();
	return true;
}

/**
*@desc �X�V����
*@param �o�ߎ���
*/
void CHpGuage::update(float deltaTimer_) {
	if (this->m_pStatus == NULL)
		return;
	
	//�v���C���[��HP�o�[���x���̐ݒ�
	if (0 <= this->m_pStatus->getHp()) {
		//���݂̃��C�t���ő僉�C�t�Ɣ�r���ăp�[�Z���e�[�W�ɕϊ�
		//int�^�Ōv�Z�����0�ɂȂ��Ă��܂��̂�float�^�ɃL���X�g���Čv�Z����
		float hp = ((float)this->m_pStatus->getHp() / (float)this->m_pStatus->getMaxHp() ) * 100.0f;
		
		//�\������摜�̊�����ݒ�
		this->setPercentage(hp);
	}
}

//=========================================================================
//�@�X�R�A�\���p�̃��x���N���X�͂������珑��
//=========================================================================
//�R���X�g���N�^
CScoreLabel::CScoreLabel() {
	//�S�~����
	this->m_pStatus = NULL;
}
//�f�X�g���N�^
CScoreLabel::~CScoreLabel() {

}
bool CScoreLabel::init() {

	//=========================================================================
	//	���[�U�[�C���^�[�t�F�[�X�̏������Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	//������̃t�H���g�^�C�v
	this->setSystemFontName("Arial");
	//������̃t�H���g�T�C�Y
	this->setSystemFontSize(24);

	//�A���J�[�|�C���g�ݒ�
	this->setAnchorPoint(cocos2d::Point(0.0f,0.5f));

	//����
	this->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
	//�ʒu�̐ݒ�
	this->setPosition(cocos2d::Point(WINDOW_RIGHT * 0.0f, WINDOW_TOP * 0.92f));

	//�����čX�V�������Ăяo��
	this->scheduleUpdate();
	return true;
}

void CScoreLabel::update(float deltaTime_)
{
	if (this->m_pStatus == NULL)
		return;

	//�\������X�R�A�𕶎���ɕϊ�
	std::string scoreStr = cocos2d::StringUtils::format("TOTAL SCORE:%d", this->m_pStatus->getScore());

	this->setString(scoreStr);

}
//=========================================================================
//�@�X�e�[�W�\���p�̃��x���N���X�͂������珑��
//=========================================================================
//�R���X�g���N�^
CStageNoLabel::CStageNoLabel() {
	//�S�~����
	this->m_pStage = NULL;
}
//�f�X�g���N�^
CStageNoLabel::~CStageNoLabel() {

}
bool CStageNoLabel::init() {

	//=========================================================================
	//	���[�U�[�C���^�[�t�F�[�X�̏������Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	//������̃t�H���g�^�C�v
	this->setSystemFontName("Arial");
	//������̃t�H���g�T�C�Y
	this->setSystemFontSize(24);
	//�A���J�[�|�C���g�ݒ�
	this->setAnchorPoint(cocos2d::Point(0.0f, 0.5f));

	//����
	this->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
	//�ʒu�̐ݒ�
	this->setPosition(cocos2d::Point(WINDOW_RIGHT * 0.8f, WINDOW_TOP * 0.97f));

	//�����čX�V�������Ăяo��
	this->scheduleUpdate();
	return true;
}

void CStageNoLabel::update(float deltaTime_)
{
	if (this->m_pStage == NULL)
		return;

	//�\������HP�𕶎���ɕϊ�
	std::string stageStr = cocos2d::StringUtils::format("STAGE:%d", *this->m_pStage);

	this->setString(stageStr);

}

//=========================================================================
//�@�v���C���[���\���p�̃��x���N���X�͂������珑��
//=========================================================================
//�R���X�g���N�^
CPlayerLabel::CPlayerLabel() {
	//�S�~����
	this->m_pPlayer = NULL;
}
//�f�X�g���N�^
CPlayerLabel::~CPlayerLabel() {

}
bool CPlayerLabel::init() {

	//=========================================================================
	//	���[�U�[�C���^�[�t�F�[�X�̏������Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	//������̃t�H���g�^�C�v
	this->setSystemFontName("Arial");
	//������̃t�H���g�T�C�Y
	this->setSystemFontSize(24);
	//�A���J�[�|�C���g�ݒ�
	this->setAnchorPoint(cocos2d::Point(0.0f, 0.5f));

	//����
	this->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
	//�ʒu�̐ݒ�
	this->setPosition(cocos2d::Point(WINDOW_RIGHT * 0.45f, WINDOW_TOP * 0.97f));

	//�����čX�V�������Ăяo��
	this->scheduleUpdate();
	return true;
}

void CPlayerLabel::update(float deltaTime_)
{
	if (this->m_pPlayer == NULL)
		return;

	int player = *this->m_pPlayer;
	//�\������HP�𕶎���ɕϊ�
	player = *this->m_pPlayer == -1 ? 0 : *this->m_pPlayer;
	std::string playerStr = cocos2d::StringUtils::format("PLAYER:%d", player);

	this->setString(playerStr);

}

//=========================================================================
//�@�{�����\���p�̃��x���N���X�͂������珑��
//=========================================================================
//�R���X�g���N�^
CBomLabel::CBomLabel() {
	//�S�~����
	this->m_pBom = NULL;
}
//�f�X�g���N�^
CBomLabel::~CBomLabel() {

}
bool CBomLabel::init() {

	//=========================================================================
	//	���[�U�[�C���^�[�t�F�[�X�̏������Ɋւ���R�[�h�̒ǉ��͂�������
	//=========================================================================
	//������̃t�H���g�^�C�v
	this->setSystemFontName("Arial");
	//������̃t�H���g�T�C�Y
	this->setSystemFontSize(24);
	//�A���J�[�|�C���g�ݒ�
	this->setAnchorPoint(cocos2d::Point(0.0f, 0.5f));

	//����
	this->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
	//�ʒu�̐ݒ�
	this->setPosition(cocos2d::Point(WINDOW_RIGHT * 0.65f, WINDOW_TOP * 0.97f));

	//�����čX�V�������Ăяo��
	this->scheduleUpdate();
	return true;
}

void CBomLabel::update(float deltaTime_)
{
	if (this->m_pBom == NULL)
		return;

	//�\������HP�𕶎���ɕϊ�
	std::string bomStr = cocos2d::StringUtils::format("BOM:%d", *this->m_pBom);

	this->setString(bomStr);
}