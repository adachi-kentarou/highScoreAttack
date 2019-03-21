#ifndef __ShootingGame__UserInterface__
#define __ShootingGame__UserInterface__

#include "cocos2d.h"
#include "Data/Status/Status.h"

//=========================================================================
//�@HP�\���p�̃��x���N���X�͂������珑��
//=========================================================================
class CHpLabel :public cocos2d::Label {
public:
	CHpLabel();
	~CHpLabel();
	
	CREATE_FUNC(CHpLabel);

	//����������
	virtual bool init();
	/**
	*@desc �X�V����
	*@param �o�ߎ���
	*/
	virtual void update(float deltaTime_) override;

private:
	//���̃N���X�ŊĎ�����X�e�[�^�X�N���X�̃A�h���X��⊮����|�C���^
	CStatus* m_pStatus;
	
public:
	//�X�e�[�^�X�̐ݒ�
	void setStatus(CStatus* pStatus){
		this->m_pStatus = pStatus;
	}
};


//=========================================================================
//�@HP�Q�[�W�̃N���X�͂������珑��
//=========================================================================
class CHpGuage :public cocos2d::ProgressTimer {
public:
	CHpGuage();
	~CHpGuage();
	CREATE_FUNC(CHpGuage);
	
	//����������
	virtual bool init();
	/**
	*@desc �X�V����
	*@param �o�ߎ���
	*/
	virtual void update(float deltaTimer_)override;
private:
	//�Q�Ƃ���X�e�[�^�X
	CStatus* m_pStatus;
public:
	//�Q�Ƃ���X�e�[�^�X�̐ݒ�
	void setStatus(CStatus* pStatus) {
		this->m_pStatus = pStatus;
	}

};

//=========================================================================
//�@�X�R�A�\���p�̃��x���N���X�͂������珑��
//=========================================================================
class CScoreLabel :public cocos2d::Label {
public:
	CScoreLabel();
	~CScoreLabel();

	CREATE_FUNC(CScoreLabel);

	//����������
	virtual bool init();
	/**
	*@desc �X�V����
	*@param �o�ߎ���
	*/
	virtual void update(float deltaTime_) override;
private:
	//�Q�Ƃ���X�e�[�^�X
	CStatus* m_pStatus;
public:
	//�Q�Ƃ���X�e�[�^�X�̐ݒ�
	void setStatus(CStatus* pStatus) {
		this->m_pStatus = pStatus;
	}
};
//=========================================================================
//�@�X�e�[�W�\���p�̃��x���N���X�͂������珑��
//=========================================================================
class CStageNoLabel :public cocos2d::Label {
public:
	CStageNoLabel();
	~CStageNoLabel();

	CREATE_FUNC(CStageNoLabel);

	//����������
	virtual bool init();
	/**
	*@desc �X�V����
	*@param �o�ߎ���
	*/
	virtual void update(float deltaTime_) override;

private:
	//���̃N���X�ŊĎ�����X�e�[�^�X�N���X�̃A�h���X��⊮����|�C���^
	int* m_pStage;

public:
	//�X�e�[�^�X�̐ݒ�
	void setStage(int* pStage) {
		this->m_pStage = pStage;
	}
};

//=========================================================================
//�@�v���C���[���\���p�̃��x���N���X�͂������珑��
//=========================================================================
class CPlayerLabel :public cocos2d::Label {
public:
	CPlayerLabel();
	~CPlayerLabel();

	CREATE_FUNC(CPlayerLabel);

	//����������
	virtual bool init();
	/**
	*@desc �X�V����
	*@param �o�ߎ���
	*/
	virtual void update(float deltaTime_) override;

private:
	//���̃N���X�ŊĎ�����X�e�[�^�X�N���X�̃A�h���X��⊮����|�C���^
	int* m_pPlayer;

public:
	//�X�e�[�^�X�̐ݒ�
	void setPlayer(int* pPlayer) {
		this->m_pPlayer = pPlayer;
	}
};

//=========================================================================
//�@�{�����\���p�̃��x���N���X�͂������珑��
//=========================================================================
class CBomLabel :public cocos2d::Label {
public:
	CBomLabel();
	~CBomLabel();

	CREATE_FUNC(CBomLabel);

	//����������
	virtual bool init();
	/**
	*@desc �X�V����
	*@param �o�ߎ���
	*/
	virtual void update(float deltaTime_) override;

private:
	//���̃N���X�ŊĎ�����X�e�[�^�X�N���X�̃A�h���X��⊮����|�C���^
	int* m_pBom;

public:
	//�X�e�[�^�X�̐ݒ�
	void setBom(int* pBom) {
		this->m_pBom = pBom;
	}
};
#endif