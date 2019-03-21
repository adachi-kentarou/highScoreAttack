
#ifndef ShootingGame_ActionController_h
#define ShootingGame_ActionController_h
//�A�N�V�����^�C�v
enum class ACTION_TYPE {
	NONE = -1,	//�s������
	ZIGZAG,		//�W�O�U�O
	STRAIGHT,	//���i�s��
	CONVEX,		//�ʍs��
	ORIGINAL,	//�I���W�i��
	ORIGINAL2,	//�I���W�i��
	BOSS_1,		//�{�X�P
};
//CEnemyCharacter�N���X��O���錾
class CEnemyCharacter;

//=========================================================================
//�@�s���Ǘ��̃N���X�͂������珑��
//=========================================================================
/**
*�W�O�U�O�s��
*/
class CActionControllerZigZag {
public:
	//�A�N�V�����^�C�v
	ACTION_TYPE m_actionType;

	//�R���X�g���N�^
	CActionControllerZigZag();

	/*
	*@desc �s������
	*@param ���̍s�����s���G�L�����̃A�h���X
	*/
	void actionFunc(CEnemyCharacter* pEne);
};

/**
*���i�s��
*���i�s�����ɒe��2������
*/
class CActionControllerStraight {
public:
	//�A�N�V�����^�C�v
	ACTION_TYPE m_actionType;

	//�R���X�g���N�^
	CActionControllerStraight();

	/*
	*@desc �s������
	*@param ���̍s�����s���G�L�����̃A�h���X
	*/
	void actionFunc(CEnemyCharacter* pEne);
};

/**
*�ʍs��
*/
class CActionControllerConvex {
public:
	//�A�N�V�����^�C�v
	ACTION_TYPE m_actionType;

	//�R���X�g���N�^
	CActionControllerConvex();

	/*
	*@desc �s������
	*@param ���̍s�����s���G�L�����̃A�h���X
	*/
	void actionFunc(CEnemyCharacter* pEne);
};

/**
*�I���W�i��
*/
class CActionControllerOriginal {
public:
	//�A�N�V�����^�C�v
	ACTION_TYPE m_actionType;

	//�R���X�g���N�^
	CActionControllerOriginal();

	/*
	*@desc �s������
	*@param ���̍s�����s���G�L�����̃A�h���X
	*/
	void actionFunc(CEnemyCharacter* pEne);
};
class CActionControllerOriginal2 {
public:
	//�A�N�V�����^�C�v
	ACTION_TYPE m_actionType;

	//�R���X�g���N�^
	CActionControllerOriginal2();

	/*
	*@desc �s������
	*@param ���̍s�����s���G�L�����̃A�h���X
	*/
	void actionFunc(CEnemyCharacter* pEne);
};

/**
*�{�X
*/
class CActionControllerBoss {
public:
	//�A�N�V�����^�C�v
	ACTION_TYPE m_actionType;

	//�R���X�g���N�^
	CActionControllerBoss();

	/*
	*@desc �s������
	*@param ���̍s�����s���G�L�����̃A�h���X
	*/
	void actionFunc(CEnemyCharacter* pEne);
};
#endif