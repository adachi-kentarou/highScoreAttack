#ifndef __ShootingGame__Character__
#define __ShootingGame__Character__

#include "cocos2d.h"
#include "Constants.h"
#include "Data/Status/Status.h"
#include "Data/ActionController/ActionController.h"
using namespace cocos2d;
using namespace cocos2d::experimental;
//AudioEngine�̃C���N���[�h
#include "audio/include/AudioEngine.h"

//=========================================================================
//	�L�����N�^�[�Ɋւ���^�C�v�Ȃǂ̗񋓂͂������珑���Ă���
//=========================================================================
//�G�̃^�C�v
enum class ENEMY_TYPE :int {
	TYPE_A = 0,
	TYPE_B = 1,
	TYPE_C = 2,
	TYPE_D = 3,
	TYPE_E = 4,
	TYPE_BOSS_1 = 10,
};

//�e�̃^�C�v
enum class BULLET_TYPE {
	//�v���C���[�̒e�^�C�v
	//�ʏ�e
	PLAYER_NORMAL = 0,
	//����
	PLAYER_EXPLOSION = 1,
	//����e
	PLAYER_BACK = 2,
	//���[�U�[�e
	PLAYER_LASER = 3,
	//�U���e
	PLAYER_INDUCTION = 4,
	//�U�e
	PLAYER_MULTIPLE = 5,
	//�����G�t�F�N�g
	PLAYER_EXPLOSION_2 = 6,
	
	//�ʏ�e
	//PLAYER_NORMAL = 1000,

	//2way�e
	PLAYER_2WAY,

	//3way�e
	PLAYER_3WAY,

	//�G�̒e�̃^�C�v
	//�ʏ�e
	ENEMY_NORMAL = 2000,

	//�G�̒e�̃^�C�v
	//���@�_���e(�v���C���[�_���e)
	ENEMY_AIMING,

	//��`�e(7way�e)
	ENEMY_FAN,

	//�O��V���b�g
	ENEMY_2WAY,
};


//�����G�t�F�N�g�^�C�v
enum class EFFECT_TYPE {
	EXPLOSION = 0,//����
	EXPLOSION_FINISH = 1,//HP0����
	BOM = 2,//�{��
	ALEART = 3,//�A���[�g
	PLANET1 = 4,//�f��1
	PLANET2 = 5,//�f��2
	PLANET3 = 6,//�f��3
	PLANET4 = 7,//�f��4
	PLANET5 = 8,//�f��5
	PLANET6 = 9,//�f��6
	PLANET7 = 10,//�f��7
	PLANET8 = 11,//�f��8
	PLANET9 = 12,//�f��9
};

//�A�C�e���^�C�v
enum class ITEM_TYPE :int{
	NONE = -1,//����
	RECOVERY = 0,//HP��
	SPEEDUP = 1,//���x�A�b�v
	NORMAL = 2,//�m�[�}���U�����x���A�b�v
	EXPLOSION = 3,//�����U�����x���A�b�v
	BACK = 4,//����U�����x���A�b�v
	LASER = 5,//���[�U�[�U�����x���A�b�v
	INDUCTION = 6,//�U���U�����x���A�b�v
	MULTIPLE = 7,//�U�e�U�����x���A�b�v
	BOM = 8,//�{��
	ONE_UP = 9,//�v���C���[��
};

//�ǃ^�C�v
enum class WALL_TYPE :int {
	STAGE_1_1 = 0,//�X�e�[�W�P
	STAGE_1_2 = 1,//�X�e�[�W�Q
	STAGE_2_1 = 2,//�X�e�[�W�P
	STAGE_2_2 = 3,//�X�e�[�W�Q
	STAGE_3_1 = 4,//�X�e�[�W�P
	STAGE_3_2 = 5,//�X�e�[�W�Q
};

/*
 *	�`�b�v�N���X
 *	cocos2d::Rect �� typedef ���Ďg�p����
 *	typedef �Ƃ́u�^�v���u�ʖ��̌^�v�ł��g�p�o����悤�ɂ���w��q
 *
 *	�\��
 *		typedef �^ �ʖ��̌^ ;
 *
 *	���܂Œʂ�̌^�ł��錾�ł��邵�A�ʖ��̌^�ł��錾���鎖���ł���B
 *
 *		typedef cocos2d::Rect CRect ;
 *
 *	�Ƃ���΁A
 *
 *		cocos2d::Rect body ;
 *		CRect body ;
 *
 *	�̂Q�ʂ�Ő錾���鎖���ł���B
 */
typedef cocos2d::Rect CChip ;



//=========================================================================
//	�ړ��p�N���X�̃R�[�h�͂������珑��
//=========================================================================
/*
�ړ��p�f�[�^�N���X
*/
class CMove
{
	public:
		float m_posX;	//�ʒuX���W
		float m_posY;	//�ʒuY���W
		float m_velX;	//���xX
		float m_velY;	//���xY
		/*
		*@desc	�ʒu�̐ݒ�
		*@param	X���W
		*@param	Y���W
		*/
		void setPos(float posX,float posY)
		{
			m_posX = posX;
			m_posY = posY;
		}
		/*
		*@desc	���x�̐ݒ�
		*@param	���xX
		*@param	���xY
		*/
		void setVel(float velX,float velY)
		{
			m_velX = velX;
			m_velY = velY;
		}
		/*
		*@desc	���x�ɂ��ړ�
		*/
		void moveByVell()
		{
			//���̈ʒu�@���@���݂̈ʒu�@�{�@�ړ������
			m_posX = m_posX + m_velX;
			m_posY = m_posY + m_velY;
		}

};

//=========================================================================
//	�A�j���[�V�����p�N���X�̃R�[�h�͂������珑��
//=========================================================================
class CAnimation {
public:
	int m_counter;//�J�E���^�[
	int m_interval;//�؂�ւ��Ԋu
	int m_number;//�A�j���[�V��������
	
	//�A�j���[�V�������I���������ǂ����̃t���O
	//true...�I������
	bool m_isEnd;

	//���[�v���邩�ǂ����̃t���O
	//true...���[�v����
	bool m_isLoop;

	CAnimation() {
		//�A�j���[�V�������I���������ǂ����̃t���O�̏�����
		this->m_isEnd = false;
	}
	/**
	*@desc �ݒ�p
	*@param �؂�ւ��Ԋu
	*@param �A�j���[�V��������
	*@param true...���[�v���� false...���[�v���Ȃ�
	*/
	void set(int interval,int number,bool isLoop = true) {
		this->m_counter = 0;
		this->m_interval = interval;
		this->m_number = number;
		this->m_isLoop = isLoop;
	}

	/**
	*@desc �A�j���[�V�����̍X�V����
	*@return �\������t���[����
	*/
	int update() {
		if (this->m_isEnd == false) {
			this->m_counter++;
			//�J�E���^�[�̐����A�j���[�V���������閇���ȏ�ɂȂ�����J�E���^�[�����Z�b�g����
			if (this->m_counter >= this->m_interval * this->m_number) {
				if (this->m_isLoop == true) {
					//���[�v����A�j���[�V�����̓J�E���^�[�����Z�b�g����
					this->m_counter = 0;
				}
				else {
					//�A�j���[�V�������I���������ǂ����̃t���O�ɑ΂���true������
					this->m_isEnd = true;

					//���[�v���Ȃ��A�j���[�V�����ɑ΂��Ă͔�яo���J�E���^�[���f�N�������g����
					this->m_counter--;
				}

			}

			//�\������t���[����
			int frame = this->m_counter / this->m_interval;
			return frame;
		}
	}
};


//=========================================================================
//	�Փ˔���p�N���X�̃R�[�h�͂������珑��
//=========================================================================
class CBody {
public:
	float m_left;//���̈ʒu
	float m_top;//��̈ʒu
	float m_right;;//�E�̈ʒu
	float m_bottom;//���̈ʒu
	  //�R���X�g���N�^
	CBody() {}
	/**
	*desc �ݒ�p
	*@param ���̐ݒ�
	*@param ��̐ݒ�
	*@param �E�̐ݒ�
	:@param ���̐ݒ�
	*/
	void set(float left,float top,float right,float bottom) {
		this->m_left = left;
		this->m_top = top;
		this->m_right = right;
		this->m_bottom = bottom;
	}

	/**
	*@desc �Փ˔���
	*@param �Փ˂����Ă���Ώۂ̃f�[�^
	*@return true �Փ˂��Ă���@false �Փ˂��Ă��Ȃ�
	*@tips ����this�Ƃ����̂��Փ˂����Ώ�
	/*�����̑Ώ�pBody�Ƃ����̂��Փ˂��Ă���Ώ�
	*/

	bool collision(CBody* pBody) {
		//�����̉E���ƑΏۂ̍����Ǝ����̍����ƑΏۂ̉E��
		if (this->m_right > pBody->m_left && this->m_left < pBody->m_right) {
			//�����̏㑤�ƑΏۂ̉����Ǝ����̉����ƑΏۂ̏㑤
			if (this->m_top > pBody->m_bottom && this->m_bottom < pBody->m_top){
				//�d�Ȃ���(�Փ˂��Ă���)
				return true;
			}
		}
		//�Փ˂��Ă��Ȃ�
		return false;
	}

	/**
	*@desc �ʒu�𔽉f�����Փ˔���̃f�[�^���擾
	*@param �ʒuX
	*@param �ʒuY
	*@return �ʒu�𔽉f�����Փ˔���p�f�[�^
	*/
	CBody getApplyPositionBody(float posX,float posY) {
		//�V�����Փ˔���p�f�[�^�𐶐�
		CBody body;

		//�Փ˔�����s���傫���Ɉʒu�𔽉f
		body.set(
			posX + this->m_left,
			posY + this->m_top,
			posX + this->m_right,
			posY + this->m_bottom
			);
		return body;
	}
};



class CBullet;

/*
 *
 *	�v���C���[�L�����N�^�[�N���X
 *
 *		cocos2d::Sprite �N���X���p�����Ďg�p���Ă���
 *		�C���X�^���X�𐶐�����ۂ� �ÓI�����o�֐� create ���g�p�ł��邪
 *		���������� create �����p�ӂ���Ă��Ȃ��̂Œ���
 *
 */
class CPlayerCharacter : public cocos2d::Sprite {
public:

	//=========================================================================
	//	��������͗����o����܂ł͕ύX�֎~
	//=========================================================================
	
	// �R���X�g���N�^�̐錾
	CPlayerCharacter() ;
	// �f�X�g���N�^�̐錾
	~CPlayerCharacter() ;
	
	CREATE_FUNC( CPlayerCharacter ) ;
	
	/**
	 *	@desc	����������
	 */
	virtual bool init() override ;
	
	/**
	*@desc �v���C���[�̒e�𔭎�
	*@param �e�^�C�v
	*@param �C���ʒuX
	*@param �C���ʒuY
	*@param ���xX
	*@param ���xY
	*/
	CBullet* shotBullet(BULLET_TYPE type, float fixX, float fixY, float velX, float velY);

	//=========================================================================
	//	�����܂ł͗����o����܂ł͕ύX�֎~
	//=========================================================================
	
public:

	//=========================================================================
	//	�����o�錾
	//		���C�����Ŏg�p���郁���o�͂����ȍ~�ɋL�q���Ă���
	//=========================================================================
	
	// �ړ��p�f�[�^
	CMove m_move;
	// �`�b�v�f�[�^
	CChip m_chip;
	// �A�j���[�V�����f�[�^
	CAnimation m_anime;

	// �Փ˔���p�f�[�^
	CBody m_body;

	// �L���t���O
	bool m_activeFlag;
	//�e���˗p�J�E���^�[
	int m_shotCounter;

	//�e���ˊԊu
	int m_shotInterval;

	//�e�U����
	float m_shotPower;

	//�e�ړ���
	float m_shotVel;

	//�e�p�����[�^
	float m_shotParam;
	
	// �ړ��Ɋւ��郁���o�֐��錾
	void moveFunc();
	// �A�j���[�V�����Ɋւ��郁���o�֐��錾
	void animationFunc();
	// ��ʒ[����Ɋւ��郁���o�֐��錾
	void endOfScreen();
	// �l�̔��f�Ɋւ��郁���o�֐��錾
	void applyFunc();
	
	//�v���C���[���ʉ�
	int m_bgmid;

	//�X�e�[�^�X
	CStatus m_status;

	/**
	*@desc ����̍U�������g�ɂ�������
	*@param �Փ˂��Ă�������̃X�e�[�^�X�̃A�h���X
	*/
	void hits(CStatus* pStatus);
};



//=========================================================================
//	�o���b�g ( �e ) �̃N���X�͂������珑��
//=========================================================================
class CBullet : public cocos2d::Sprite {
public:
	//=====================================================================
	//��������͗����ł���܂ł͕ύX�֎~
	//=====================================================================

	//�R���X�g���N�^�̐錾
	CBullet();

	//�f�X�g���N�^�̐錾
	~CBullet();

	CREATE_FUNC(CBullet);
	/*
	*@desc ����������
	*/
	virtual bool init() override;
	//=====================================================================
	//�����܂ŗ����ł���܂ł͕ύX�֎~
	//=====================================================================

public:
	//=====================================================================
	//�����o�錾�@���C�����Ŏg�p���郁���o�͂����ȍ~�ɋL�q���Ă���
	//=====================================================================

	//�ړ��p�f�[�^
	CMove m_move;

	//�v���C���[�L�����N�^�[�ړ��f�[�^
	CMove* m_pmove;

	//�`�b�v�f�[�^
	CChip m_chip;

	//�A�j���[�V�����f�[�^
	CAnimation m_anime;

	//�v���C���[�̒e�̔��˂ł���ő吔
	static const int MAX_BULLET = 200;

	//�L���t���O(false�Ń��C���[������O�����)
	bool m_activeFlag;
	
	// �ړ��Ɋւ��郁���o�֐��錾
	void moveFunc();
	// ��ʒ[����Ɋւ��郁���o�֐��錾
	void endOfScreen();
	// �l�̔��f�Ɋւ��郁���o�֐��錾
	void applyFunc();
	//�A�j���[�V�����Ɋւ��郁���o�֐�
	void CBullet::animationFunc();
	//�e�^�C�v
	BULLET_TYPE m_bulletType;
	//�Փ˔���p�f�[�^
	CBody m_body;

	//�X�e�[�^�X
	CStatus m_status;

	//�폜�݂�t���O
	bool m_delflg = false;

	//�J�E���g
	int m_count = 0;
	//�ő�J�E���g
	int m_maxCount = 0;

	//�U���e���[�h true...�^�[�Q�b�g�I�� false...�ǔ�
	bool mode = true;

	//�^�[�Q�b�g
	int target = -1;

	//�e�ƃ^�[�Q�b�g�̋��� ����K���o�^���邽�߂ɏ����l�͋���
	float distance = 1000000.0f;

	//��]�p�x
	float rotation = 0;

	//�p�����[�^
	float param = 0;

	//�ړ�����
	float vel = 0;

};

//=========================================================================
//	�G�̃N���X�͂������珑��
//=========================================================================
class CEnemyAction {
public:
	float x = 0;
	float y = 0;
	int frame = 0;
};
class CEnemyCharacter :public cocos2d::Sprite {
public:
	//===========================================
	//��������͗����ł���܂ł͕ύX�֎~
	//===========================================
	//�R���X�g���N�^�̐錾
	CEnemyCharacter();
	//�f�X�g���N�^�̐錾
	~CEnemyCharacter();

	CREATE_FUNC(CEnemyCharacter);
	/*
	*@desc ����������
	*/
	virtual bool init() override;
	//===========================================
	//�����܂ŗ����ł���܂ł͕ύX�֎~
	//===========================================
	
public:
	//===========================================
	//�����o�錾
	//���C�����Ŏg�p���郁���o�͂����ȍ~�ɋL�q���Ă���
	//===========================================
	static const int MAX_ENEMY = 100;

	//�ړ��p�f�[�^
	CMove m_move;

	//�`�b�v�f�[�^
	CChip m_chip;

	//�A�j���[�V�����f�[�^
	CAnimation m_anime;

	//�L���t���O(false...���C���[������O�����)
	bool m_activeFlag;

	//�ړ��Ɋւ��郁���o�֐��錾
	void moveFunc();

	//�A�j���[�V�����Ɋւ��郁���o�֐��錾
	void animationFunc();

	//��ʒ[����Ɋւ��郁���o�֐��錾
	void endOfScreen();

	//�l�̔ɉh�Ɋւ��郁���o�֐��錾
	void applyFunc();

	//�G�̃^�C�v
	ENEMY_TYPE e_enemyType;

	/**
	*@desc �v���C���[�̒e�𔭎�
	*@param �e�^�C�v
	*@param �C���lX
	*@param �C���lY
	*@param ���xX
	*@param ���xY
	*/
	CBullet* shotBullet(BULLET_TYPE type,float fixX,float fixY,float velX,float velY);

	//�Փ˔���p�f�[�^
	CBody m_body;

	//���˂���e�̃^�C�v
	BULLET_TYPE m_bulletType;

	//�G���ʉ�
	int m_bgmid;

	//�X�e�[�^�X
	CStatus m_status;

	/**
	*@desc ����̍U�������g�ɂ�������
	*@param �Փ˂��Ă�������̃X�e�[�^�X�̃A�h���X
	*/
	void hits(CStatus* pStatus);

	//�s���Ɋւ��郁���o�֐��̐錾
	void actionFunc();

	//�s���^�C�v
	ACTION_TYPE m_actionType;

	//���˃t���O
	bool m_shotFlag = false;

	//���݂̍s���X�e�b�v
	int m_actionStep = 0;

	//�����A�C�e��
	ITEM_TYPE m_item = ITEM_TYPE::NONE;

	//�ړ��f�[�^
	std::vector<CEnemyAction> action;

	//�A�N�V�����t���[���J�E���g
	int actionCount = -1;

	//�V���b�g�J�E���g
	int shotCount = 0;

	//�i�s�����@true...���@false...�E
	bool direction;

	//�C�g
	Sprite* m_pChr;

	//��]�p�x
	float rotation = 0;

	//�e�����W�␳
	float fixX = 0;

	//�e�����W�␳
	float fixY = 0;

	//�e���a�␳
	float fixR = 0;

	//�{�X�t���O
	bool bossflg = false;

	//�{�X�J�E���g�p
	int bossCount = 0;
	
};


//=========================================================================
//	�G�t�F�N�g�̃N���X�͂������珑��
//=========================================================================
class CEfect : public cocos2d::Sprite {
public:
	static const int MAX_EFFECT = 100;

	// �R���X�g���N�^�̐錾
	CEfect();
	// �f�X�g���N�^�̐錾
	~CEfect();

	CREATE_FUNC(CEfect);

	/**
	*	@desc	����������
	*/
	virtual bool init() override;

public:
	//=====================================================================
	//�����o�錾�@���C�����Ŏg�p���郁���o�͂����ȍ~�ɋL�q���Ă���
	//=====================================================================

	//�ړ��p�f�[�^
	CMove m_move;

	//�`�b�v�f�[�^
	CChip m_chip;

	//�A�j���[�V�����f�[�^
	CAnimation m_anime;

	//�L���t���O(false�Ń��C���[������O�����)
	bool m_activeFlag;

	//�G�t�F�N�g�^�C�v
	EFFECT_TYPE type;

	// �ړ��Ɋւ��郁���o�֐��錾
	void moveFunc();
	// �A�j���[�V�����Ɋւ��郁���o�֐��錾
	void animationFunc();
	// �l�̔��f�Ɋւ��郁���o�֐��錾
	void applyFunc();
	//��ʒ[����Ɋւ��郁���o�֐��錾
	void endOfScreen();
	//�W����X�ő吔
	int maxX = 10000;

};

//=========================================================================
//	�A�C�e���̃N���X�͂������珑��
//=========================================================================
class CItem : public cocos2d::Sprite {
public:
	static const int MAX_ITEM = 100;

	// �R���X�g���N�^�̐錾
	CItem();
	// �f�X�g���N�^�̐錾
	~CItem();

	CREATE_FUNC(CItem);

	/**
	*	@desc	����������
	*/
	virtual bool init() override;

public:
	//=====================================================================
	//�����o�錾�@���C�����Ŏg�p���郁���o�͂����ȍ~�ɋL�q���Ă���
	//=====================================================================

	//�ړ��p�f�[�^
	CMove m_move;

	//�`�b�v�f�[�^
	CChip m_chip;

	//�A�j���[�V�����f�[�^
	CAnimation m_anime;

	//�L���t���O(false�Ń��C���[������O�����)
	bool m_activeFlag;

	//�A�C�e���^�C�v
	ITEM_TYPE type;

	// �ړ��Ɋւ��郁���o�֐��錾
	void moveFunc();
	// �A�j���[�V�����Ɋւ��郁���o�֐��錾
	void animationFunc();
	// �l�̔��f�Ɋւ��郁���o�֐��錾
	void applyFunc();
	//��ʒ[����Ɋւ��郁���o�֐��錾
	void endOfScreen();



	//�Փ˔���p�f�[�^
	CBody m_body;
	/**
	*@desc ����̍U�������g�ɂ�������
	*@param �Փ˂��Ă�������̃X�e�[�^�X�̃A�h���X
	*/
	void hits(CStatus* pStatus);

	//�A�C�e���擾���ʉ�
	int m_bgmid;

	//���C���̍U�����x�����x���擾�p
	static cocos2d::Label** pweponLevelLavel;
};

//=========================================================================
//	�J�[�\���̃N���X�͂������珑��
//=========================================================================
class CCursor : public cocos2d::Sprite {
public:
	// �R���X�g���N�^�̐錾
	CCursor();
	// �f�X�g���N�^�̐錾
	~CCursor();

	CREATE_FUNC(CCursor);

	/**
	*	@desc	����������
	*/
	virtual bool init() override;

public:
	//=====================================================================
	//�����o�錾�@���C�����Ŏg�p���郁���o�͂����ȍ~�ɋL�q���Ă���
	//=====================================================================

	//�ړ��p�f�[�^
	CMove m_move;

	//�`�b�v�f�[�^
	CChip m_chip;

	//�A�j���[�V�����f�[�^
	CAnimation m_anime;

	// �ړ��Ɋւ��郁���o�֐��錾
	void moveFunc();
	// �A�j���[�V�����Ɋւ��郁���o�֐��錾
	void animationFunc();
	// �l�̔��f�Ɋւ��郁���o�֐��錾
	void applyFunc();
	
	//�J�[�\����X�ő�
	int p_maxX;
	//�J�[�\����Y�ő�
	int p_maxY;
	//�J�[�\����X�ʒu
	int p_x;
	//�J�[�\����Y�ʒu
	int p_y;
	//�J�[�\����X���W
	float p_xPoint;
	//�J�[�\����Y���W
	float p_yPoint;
	//�A�j���[�V������
	int p_animation;
	//�A�j���[�V�����t���[����
	int p_animeFrame;
	//X�ړ��T�C�Y
	float p_moveX;
	//Y�ړ��T�C�Y
	float p_moveY;
	//�ړ��t���[��
	int p_moveFrame;
	//�����[�v
	bool p_xLoop;
	//�c���[�v
	bool p_yLoop;
	//�ᑬ�҂��t���[��
	int p_slowWait;
	//�����҂��t���[��
	int p_fastWait;
	//������͑҂��t���[��
	int p_inputWait = 10;

	//�J�E���g�t���[��
	int p_countFrame = 0;
	//�҂��t���[��
	int p_wait;

	//����v�b�V���t���O�@true...���� false...����ȍ~
	bool p_fastPush = true;
	//�ړ����x�t���O�@true...�ᑬ false...����
	bool p_speed = true;
	//��������@0...���͑҂� 1...���͌��m�҂� 2...�ړ���
	int p_input = 0;

	//�ړ��O�J�[�\���ʒu
	//�ړ��O�J�[�\����X�ʒu
	int p_beforeX;
	//�ړ��O�J�[�\����Y�ʒu
	int p_beforeY;
	//�ړ��J�E���g
	int p_moveCount;
	//�ړ��I���t���O
	bool moveflg = false;

	/*
	*@desc �J�[�\�������ݒ�
	*@param �t�@�C����
	*@param �`�b�vX���W
	*@param �`�b�vY���W
	*@param �`�b�vX�T�C�Y
	*@param �`�b�vY�T�C�Y
	*@param �A�j���[�V������
	*@param �A�j���[�V�����t���[����
	*@param �J�[�\����X�ő�
	*@param �J�[�\����Y�ő�
	*@param �J�[�\����X�ʒu
	*@param �J�[�\����Y�ʒu
	*@param �J�[�\����X���W
	*@param �J�[�\����Y���W
	*@param X�ړ��T�C�Y
	*@param Y�ړ��T�C�Y
	*@param X�ړ��t���[��
	*@param Y�ړ��t���[��
	*@param �����[�v
	*@param �c���[�v
	*@param �ᑬ�҂��t���[��
	*@param �ᑬ�҂��t���[��
	*/
	void set(
		char* p_fileName,//�t�@�C����
		int p_chipPointX,//�`�b�vX���W
		int p_chipPointY,//�`�b�vY���W
		int p_chipX,	//�`�b�vX�T�C�Y
		int p_chipY,	//�`�b�vY�T�C�Y
		int p_animation,//�A�j���[�V������
		int p_animeFrame,//�A�j���[�V�����t���[����
		int p_maxX,		//�J�[�\����X�ő�
		int p_maxY,		//�J�[�\����Y�ő�
		int p_x,		//�J�[�\����X�ʒu
		int p_y,		//�J�[�\����Y�ʒu
		float p_xPoint,	//�J�[�\����X���W
		float p_yPoint,	//�J�[�\����Y���W
		float p_moveX,	//X�ړ��T�C�Y
		float p_moveY,	//Y�ړ��T�C�Y
		int p_moveFrame,//�ړ��t���[��
		bool p_xLoop,	//�����[�v
		bool p_yLoop,	//�c���[�v
		int p_slowWait,	//�ᑬ�҂��t���[��
		int p_fastWait	//�����҂��t���[��
	);

	void inputFunc();
};

//=========================================================================
//	�ǂ̃N���X�͂������珑��
//=========================================================================
class CWall : public cocos2d::Sprite {
public:
	static const int MAX_WALL = 200;

	// �R���X�g���N�^�̐錾
	CWall();
	// �f�X�g���N�^�̐錾
	~CWall();

	CREATE_FUNC(CWall);

	/**
	*	@desc	����������
	*/
	virtual bool init() override;

public:
	//=====================================================================
	//�����o�錾�@���C�����Ŏg�p���郁���o�͂����ȍ~�ɋL�q���Ă���
	//=====================================================================

	//�ړ��p�f�[�^
	CMove m_move;

	//�`�b�v�f�[�^
	CChip m_chip;

	//�A�j���[�V�����f�[�^
	CAnimation m_anime;

	//�L���t���O(false�Ń��C���[������O�����)
	bool m_activeFlag;

	//�A�C�e���^�C�v
	WALL_TYPE type;

	//�X�e�[�^�X
	CStatus m_status;

	// �ړ��Ɋւ��郁���o�֐��錾
	void moveFunc();
	// �A�j���[�V�����Ɋւ��郁���o�֐��錾
	void animationFunc();
	// �l�̔��f�Ɋւ��郁���o�֐��錾
	void applyFunc();
	//��ʒ[����Ɋւ��郁���o�֐��錾
	void endOfScreen();

	//���ʉ�
	int m_bgmid;

	//�Փ˔���p�f�[�^
	CBody m_body;
	/**
	*@desc ����̍U�������g�ɂ�������
	*@param �Փ˂��Ă�������̃X�e�[�^�X�̃A�h���X
	*/
	void hits(CStatus* pStatus);

	//�ǂ̉�
	Sprite* m_pWall_left;
	Sprite* m_pWall_right;
	Sprite* m_pWall_top;
	Sprite* m_pWall_bottom;

};
#endif  defined(__ShootingGame__Character__) 
