#ifndef __ShootingGame__Status__
#define __ShootingGame__Status__

//=========================================================================
//　ステータスクラスはここから書く
//=========================================================================
class CStatus {
public:
	CStatus(){}
	~CStatus(){}

private:
	//HP
	int m_hp = 0;

	//最大HP
	int m_maxHp = 0;

	//攻撃力
	int m_attackPt = 0;

	//得点
	int m_score = 0;

	//移動速度
	int m_speed = 0;
public:
	/*
	*@des 設定
	*@param HP
	*@param 最大HP
	*@param 攻撃力
	*@param スコア
	*/
	void set(int hp,int maxHp,int attackPt,int score) {
		this->m_hp = hp;
		this->m_maxHp = maxHp;
		this->m_attackPt = attackPt;
		this->m_score = score;
	}

	/*
	*@des 設定 オーバーロード
	*@param HP
	*@param 最大HP
	*@param 攻撃力
	*@param スコア
	*@param 移動速度
	*/
	void set(int hp, int maxHp, int attackPt, int score,float speed) {
		this->m_hp = hp;
		this->m_maxHp = maxHp;
		this->m_attackPt = attackPt;
		this->m_score = score;
		this->m_speed = speed;
	}

	//HPの取得
	int getHp() {
		return this->m_hp;
	}

	//最大HPの取得
	int getMaxHp() {
		return this->m_maxHp;
	}

	//攻撃力の取得
	int getAttackPt() {
		return this->m_attackPt;
	}

	//スコアの取得
	int getScore() {
		return this->m_score;
	}

	//移動速度の取得
	float getSpeed() {
		return this->m_speed;
	}

	/**
	*@desc HPの減少
	*@param 減少する値(相手の攻撃力)
	*/
	void decreaseHp(int attackPt) {
		this->m_hp -= attackPt;
		if (this->m_hp < 0) {
			this->m_hp = 0;
		}
	}

	/**
	*@desc HPの回復
	*/
	void recoveryHp() {
		this->m_hp = this->m_maxHp;
	}

	/**
	*@desc スコアの加点
	*@param 追加するスコア
	*/
	void addScore(int score) {
		this->m_score += score;
	}

	/**
	*@desc 移動速度の上昇
	*/
	void speedUp( float speed ) {
		if (this->m_speed < 16) {
			this->m_speed += speed;
		}
		

	}

	/**
	*@desc HPの回復少量
	*/
	void hpUp( int hp ) {
		this->m_hp += hp;
		
		if (this->m_hp > this->m_maxHp)
			this->m_hp = this->m_maxHp;

	}
};
#endif