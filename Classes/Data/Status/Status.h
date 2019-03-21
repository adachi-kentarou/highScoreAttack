#ifndef __ShootingGame__Status__
#define __ShootingGame__Status__

//=========================================================================
//�@�X�e�[�^�X�N���X�͂������珑��
//=========================================================================
class CStatus {
public:
	CStatus(){}
	~CStatus(){}

private:
	//HP
	int m_hp = 0;

	//�ő�HP
	int m_maxHp = 0;

	//�U����
	int m_attackPt = 0;

	//���_
	int m_score = 0;

	//�ړ����x
	int m_speed = 0;
public:
	/*
	*@des �ݒ�
	*@param HP
	*@param �ő�HP
	*@param �U����
	*@param �X�R�A
	*/
	void set(int hp,int maxHp,int attackPt,int score) {
		this->m_hp = hp;
		this->m_maxHp = maxHp;
		this->m_attackPt = attackPt;
		this->m_score = score;
	}

	/*
	*@des �ݒ� �I�[�o�[���[�h
	*@param HP
	*@param �ő�HP
	*@param �U����
	*@param �X�R�A
	*@param �ړ����x
	*/
	void set(int hp, int maxHp, int attackPt, int score,float speed) {
		this->m_hp = hp;
		this->m_maxHp = maxHp;
		this->m_attackPt = attackPt;
		this->m_score = score;
		this->m_speed = speed;
	}

	//HP�̎擾
	int getHp() {
		return this->m_hp;
	}

	//�ő�HP�̎擾
	int getMaxHp() {
		return this->m_maxHp;
	}

	//�U���͂̎擾
	int getAttackPt() {
		return this->m_attackPt;
	}

	//�X�R�A�̎擾
	int getScore() {
		return this->m_score;
	}

	//�ړ����x�̎擾
	float getSpeed() {
		return this->m_speed;
	}

	/**
	*@desc HP�̌���
	*@param ��������l(����̍U����)
	*/
	void decreaseHp(int attackPt) {
		this->m_hp -= attackPt;
		if (this->m_hp < 0) {
			this->m_hp = 0;
		}
	}

	/**
	*@desc HP�̉�
	*/
	void recoveryHp() {
		this->m_hp = this->m_maxHp;
	}

	/**
	*@desc �X�R�A�̉��_
	*@param �ǉ�����X�R�A
	*/
	void addScore(int score) {
		this->m_score += score;
	}

	/**
	*@desc �ړ����x�̏㏸
	*/
	void speedUp( float speed ) {
		if (this->m_speed < 16) {
			this->m_speed += speed;
		}
		

	}

	/**
	*@desc HP�̉񕜏���
	*/
	void hpUp( int hp ) {
		this->m_hp += hp;
		
		if (this->m_hp > this->m_maxHp)
			this->m_hp = this->m_maxHp;

	}
};
#endif