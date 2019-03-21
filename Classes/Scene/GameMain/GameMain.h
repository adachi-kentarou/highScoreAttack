
#ifndef __ShootingGame__Main__
#define __ShootingGame__Main__

#include "cocos2d.h"
#include "Constants.h"

//=========================================================================
//	�ǉ��̃C���N���[�h�͂�������
//=========================================================================
#include "Model/Character/Character.h"
#include "Data/EnemyLaunchData/EnemyLaunchData.h"
#include "Model/UserInterface/UserInterface.h"
#include "Model/Map/Map.h"
#include "Data/MapData/MapData.h"
#include "Scene/Title/Title.h"
#include "Scene/StageTitle/StageTitle.h"
#include "Scene/Replay/Replay.h"
#include "Scene/ReplaySelect/ReplaySelect.h"

//#include "Data/GameData/GameData.h"
//=========================================================================
//�X�e�[�W�Ɋւ���񋓂Ȃǂ͂�������
//=========================================================================
enum class STAGE_MODE {
	//�X�e�[�W���[�h����
	NONE = -1,
	//�X�e�[�W�J�n����
	START,
	//�X�e�[�W�X�V������
	UPDATE,
	//�X�e�[�W�I������
	END,
	//�X�e�[�W�ꎞ��~��
	PAUSE,
	//�Q�[���I�[�o�[�ꎞ��~��
	GAME_OVER,

};

/*
 *	�Q�[�����C�����C���[
 *
 *		�Q�[���̃��C���ƂȂ郌�C���[
 *		���߂͂��̕����ɑS�Ă������Ă���
 *
 */
class CGameMain : public cocos2d::Layer
{
public:
	//=========================================================================
	//	��������͗����o����܂ł͕ύX�֎~
	//=========================================================================

	// �f�X�g���N�^
	~CGameMain() ;
	
	/**
	 *	@desc	�V�[���̐���
	 *	@return	CMain ���C���[�������V�[���N���X�C���X�^���X
	 *	@tips	�ÓI�����o�֐�
	 */
    static cocos2d::Scene* createScene() ;
	
	/*
	 *	@desc	�V�[���������ɏ������֐�������
	 *			�������֐����s���� NULL ��Ԃ�
	 */
    CREATE_FUNC( CGameMain );
	
	/**
	 *	@desc	�L�[�{�[�h�̃L�[���������ۂ̃C�x���g
	 *	@param	�L�[�R�[�h
	 *	@param	�C�x���g
	 */
	virtual void onKeyPressed( cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event ) override ;
	
	/**
	 *	@desc	�L�[�{�[�h�̃L�[�𗣂����ۂ̃C�x���g
	 *	@param	�L�[�R�[�h
	 *	@param	�C�x���g
	 */
	virtual void onKeyReleased( cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event ) override ;
	
	/**
	 *	@desc	������
	 *	@return	true...����	false...���s
	 */
    virtual bool init() override ;
	
	/**
	 *	@desc	�X�V����
	 *	@param	�o�ߎ���
	 */
	virtual void update( float deltaTime_ ) override ;
	
	/**
	*@desc �g�����W�V�����I������
	*/
	void onEnterTransitionDidFinish()override;

	//=========================================================================
	//	�����܂ł͗����o����܂ł͕ύX�֎~
	//=========================================================================
	
public:

	//=========================================================================
	//	�����o�錾
	//		���C�����Ŏg�p���郁���o�͂����ȍ~�ɋL�q���Ă���
	//=========================================================================
	
	// �v���C���[�L�����N�^�[
	static CPlayerCharacter* m_pPlayerChara;
	// �G�L�����N�^�[
	static CEnemyCharacter* m_pEnemyCharas[CEnemyCharacter::MAX_ENEMY];
	// �v���C���[�o���b�g ( �v���C���[�̒e )
	CBullet* m_pPlayerBullets[CBullet::MAX_BULLET];

	// �G�l�~�[�o���b�g ( �G�̒e )
	CBullet* m_pEnemyBullets[CBullet::MAX_BULLET];
	
	
	// �v���C�����͂Ɋւ��郁���o�֐�
	void inputFunc();
	// �|�[�Y�����͂Ɋւ��郁���o�֐�
	void inputFunc2();
	// �G�̏o��
	//�G�o���f�[�^
	//CEnemyLaunchData m_enemyLaunchData[CEnemyLaunchData::MAX_LAUNCH];
	CEnemyLaunchData* m_pEnemyLaunchData;

	// �ړ��Ɋւ��郁���o�֐�
	void moveFunc();
	// �v���C���[�ƓG�̒e�̏Փ�
	void collisionPlayerAndEnemyBullets();
	// �v���C���[�ƓG�̏Փ�
	void collisionPlayerAndEnemies();
	// �G�ƃv���C���[�̒e�̏Փ�
	void collisionEnemiesAndPlayerBullets();
	// �A�j���[�V�����Ɋւ��郁���o�֐�
	void animationFunc();
	// ��ʒ[����Ɋւ��郁���o�֐�
	void endOfScreen();
	// �l�̔��f�Ɋւ��郁���o�֐�
	void applyFunc();
	
	//�G�̏o��
	//�G���o�������邩�ǂ����̃`�F�b�N
	void checkLaunchEnemy();

	//�G�o���\���̃`�F�b�N
	void checkEnemyAleart();

	/**
	*@desc �G�̏o��
	*@param �Q�Ƃ���Ǘ��f�[�^�̃A�h���X
	*/
	CEnemyCharacter* launchEnemy(CEnemyLaunchData* pEneLaunchData);
	//CEnemyCharacter* launchEnemy(ENEMY_TYPE type, float posX, float posY);
	//���O������
	void checkActiveFlagAndRemove();

	//�G�̒e�̔���
	void shotEnemyBullet();
	//�v���C���[�̒e�̔���
	/*
	*@desc	�v���C���[�̒e�̔���
	*@param	�e�^�C�v
	*/
	void shotPlayerBullet(BULLET_TYPE type);
	
	//���݉��Ԗڂ̏o���f�[�^�𒲂ׂĂ���̂��̔ԍ�
	int m_enemyLaunchIndex;

	//���݉��Ԗڂ̏o���f�[�^�𒲂ׂĂ���̂��̔ԍ�
	int m_enemyAleartIndex;

	//�t���[���J�E���^�[
	static int m_frameCounter;

	//�G�t�F�N�g�z��
	CEfect* m_pEffects[CEfect::MAX_EFFECT];

	//�G�t�F�N�g�̏o��
	/**
	*@desc �G�t�F�N�g�̏o��
	*@param �G�t�F�N�g�^�C�v
	*@param �o���ʒuX
	*@param �o���ʒuY
	*@return �G�t�F�N�g�N���X�̃|�C���^
	*/
	CEfect* launchEffect(EFFECT_TYPE type,float posX,float posY);

	//BGM�̎���ID
	int m_bgmid;

	//HP���x��
	CHpLabel* m_pHpLabel;

	//HP�Q�[�W
	CHpGuage* m_pHpGuage;

	//�X�R�A���x��
	CScoreLabel* m_pScoreLabel;
	
	//�X�e�[�W���x��
	CStageNoLabel* m_pStageLabel;

	//�v���C���[�����x��
	CPlayerLabel* m_pPlayerLabel;

	//�{�������x��
	CBomLabel* m_pBomLabel;

	//�W�O�U�O�̍s���Ǘ�
	CActionControllerZigZag m_actCtrlZigZag;
	//���i�s���Ǘ�
	CActionControllerStraight m_actCtrlStraight;
	//�ʍs���Ǘ�
	CActionControllerConvex m_actCtrlConvex;
	//�I���W�i���s���Ǘ�
	CActionControllerOriginal m_actCtrlOriginal;
	CActionControllerOriginal2 m_actCtrlOriginal2;
	//�{�X�s���Ǘ�
	CActionControllerBoss m_actCtrlBoss;

	// �s�������Ɋւ��郁���o�֐�
	void actionFunc();

	//�v���C���[�ƃA�C�e���̏Փ˔���
	void collisionPlayerAndItems();

	//�A�C�e���z��
	CItem* m_pItems[CItem::MAX_ITEM];

	/**
	*@desc �A�C�e���̏o��
	*@param �A�C�e���^�C�v
	*@param �o���ʒuX
	*@param �o���ʒuY
	*@return �A�C�e���N���X�̃|�C���^
	*/
	CItem* launchItem(ITEM_TYPE type, float posX, float posY);

	//�}�b�v
	CMap* m_pMap = NULL;

	STAGE_MODE m_stageMode = STAGE_MODE::NONE;

	//�X�e�[�W�J�n����
	void stageStartFunc();
	/**
	*@desc �X�e�[�W�X�V����
	*@param �o�ߎ���
	*/
	void stageUpdateFunc(float deltaTime_);
	void stagePauseFunc();
	void gameOverFunc();

	//�X�e�[�W�J�n����
	void stageEndFunc();

	//a�L�[���d����h�~�t���O(������Ă�����true)
	bool m_aKeyDownFlag = false;
	//s�L�[���d����h�~�t���O(������Ă�����true)
	bool m_sKeyDownFlag = false;
	//z�L�[���d����h�~�t���O(������Ă�����true)
	bool m_zKeyDownFlag = true;
	//x�L�[���d����h�~�t���O(������Ă�����true)
	bool m_xKeyDownFlag = false;
	//space�L�[���d����h�~�t���O(������Ă�����true)
	bool m_spaceKeyDownFlag = false;

	//�X�e�[�W�ő吔
	static const int MAX_STAGE_COUNT = 3;

	//���݂̃X�e�[�W�ԍ�(�X�e�[�W�͂P����)
	static int m_stageNo;


	//���y�G���W���I���t���O
	bool audioFlug = true;
	//�C���^�[�t�F�[�X���C���[
	cocos2d::Layer* m_interFaceLayer;
	//�L�����N�^�[���C���[
	cocos2d::Layer* m_characterLayer;
	//�w�i���C���[
	cocos2d::Layer* m_backGroundLayer;
	//�ǃ��C���[
	cocos2d::Layer* m_wallLayer;

	static void call_back(bool a);

	//�J�[�\��
	CCursor* m_pCursor;
	//�J�[�\���p�t���[���J�E���^�[
	int c_frameCounter = 0;

	//���x���p�z��
	cocos2d::Label* pLavelArray[10];

	//�_�Ńt���O
	bool flashingflg = false;
	//�_�ŉ�
	int flashing = 0;

	//z�{�^�������t���O true...������Ă� false...������ĂȂ�
	bool p_zFlg = false;

	//left_shift�{�^�������t���O true...������Ă� false...������ĂȂ�
	bool p_left_shiftFlg = false;

	//�J�[�\���ړ���
	int change = 0;

	//�{�^������t���O
	bool p_scene = false;

	//�U���^�C�v�\�����x���p�z��
	cocos2d::Label* pweponLavel[6];

	//�U���^�C�v���x���\�����x���p�z��
	cocos2d::Label* pweponLevelLavel[6];

	//�U���^�C�v���x���p�z��
	static int pweponLevel[6];

	//�U���^�C�v�ʃ��x���ʍU���́@1���z��...�U���^�C�v�@2��...���x��
	float pweponPower[6][10] = {
		{ 10,10,10,10,10,10,10,10,10,10 },	//NORMAL
		{ 1,1,1,1,1,1,1,1,1,1 },	//EXPLOSION
		{ 10,10,10,10,10,10,10,10,10,10 },	//BACK
		{ 10,10,10,10,10,10,10,10,10,10 },	//LASER
		{ 10,10,10,10,10,10,10,10,10,10 },	//INDCTION
		{ 10,10,10,10,10,10,10,10,10,10 }		//MULTIPLE
	};

	//�U���^�C�v�ʃ��x���ʍU���Ԋu�@1���z��...�U���^�C�v�@2��...���x��
	int pweponInterval[6][10] = {
		{ 5,5,5,5,5,5,5,5,5,5 },	//NORMAL
		{ 10,10,10,10,10,10,10,10,10,10 },	//EXPLOSION
		{ 5,5,5,5,5,5,5,5,5,5 },	//BACK
		{ 5,5,5,5,5,5,5,5,5,5 },	//LASER
		{ 5,5,5,5,5,5,5,5,5,5 },	//INDCTION
		{ 5,5,6,6,7,7,8,8,9,9 }		//MULTIPLE
	};

	//�U���^�C�v�ʃ��x���ʍU���p�����[�^�@1���z��...�U���^�C�v�@2��...���x��
	float pweponParam[6][10] = {
		{ 0,0,0,0,0,0,0,0,0,0 },	//NORMAL
		{ 1,1.1f,1.2f,1.3f,1.4f,1.5f,1.6f,1.7f,1.8f,1.9f },	//EXPLOSION �����T�C�Y�{��
		{ 0,0,0,0,0,0,0,0,0,0 },	//BACK
		{ 0,0,0,0,0,0,0,0,0,0 },	//LASER
		{ 2,2.25f,2.5f,2.75f,3,3.25f,3.5f,3.75f,4,4.25f },	//INDCTION ��]�ړ���
		{ 2,2,3,3,4,4,5,5,6,6 }		//MULTIPLE ���˕�����
	};

	//�U���^�C�v�ʃ��x���ʍU���ړ��ʁ@1���z��...�U���^�C�v�@2��...���x��
	float pweponVel[6][10] = {
		{ 6,6,6,6,6,6,6,6,6,6 },	//NORMAL
		{ 6,6,6,6,6,6,6,6,6,6 },	//EXPLOSION
		{ 6,6,6,6,6,6,6,6,6,6 },	//BACK
		{ 6,6,6,6,6,6,6,6,6,6 },	//LASER
		{ 6,6,6,6,6,6,6,6,6,6 },	//INDCTION
		{ 6,6,6,6,6,6,6,6,6,6 }		//MULTIPLE
	};
	//�f�o�b�O�p���x���p�z��
	cocos2d::Label* dbgLavel[6];


	//�U���I�� 0:�ʏ� 1:���� 2:��� 3:���[�U�[ 4:�U�� 5;�G�l���M�[
	static int weponSelect;

	//�X�R�A�v�Z
	void calculationScore(int j);

	//�����G�t�F�N�g
	void createEffect(int j);

	//���[�U�[�t���O
	bool laserFlg = false;

	//���[�U�[�J�E���^�[
	int laserCounter = 0;
	//���[�U�[�C���f�b�N�X
	int laserIndex;
	//�v���C���[�ƃA�C�e���̏Փ˔���
	void collisionPlayerAndWalls();

	//�ǔz��
	CWall* m_pWalls[CWall::MAX_WALL];

	/**
	*@desc �ǂ̏o��
	*@param �ǃ^�C�v
	*@param �o���ʒuX
	*@param �o���ʒuY
	*@return �ǃN���X�̃|�C���^
	*/
	CWall* launchWall(WALL_TYPE type, float posX, float posY);

	//�I�u�W�F�N�g�J�E���g�p
	//�G�L�����J�E���g
	static int m_pEnemyCount;
	//�v���C���[�e�J�E���g
	static int m_pPlayerBulletCount;
	//�G�e�J�E���g
	static int m_pEnemyBulletCount;
	//�G�t�F�N�g�J�E���g
	static int m_pEfectCount;
	//�A�C�e���J�E���g
	static int m_pItemCount;
	//�ǃJ�E���g
	static int m_pWallCount;

	//�ǂ̈ړ��X�s�[�h
	float WALL_SPEED = MapData::WALL_SPEED;
	//�ǃt���[���J�E���g
	float m_wallCounter;
	//���݂̕ǂ̕\��x���W
	int m_pWallXpos;
	//�ǂ��o�������邩�̃`�F�b�N
	void checkLaunchWall();
	// �ǂƃv���C���[�̒e�̏Փ�
	void collisionWallsAndPlayerBullets();
	// �ǂƓG�̒e�̏Փ�
	void collisionWallsAndEnemyBullets();
	//�ǏՓ˃G�t�F�N�g
	void createEffect2(int j,float x,float y);

	//�����t���O
	bool resurrection = false;
	//���A�J�E���g
	int resCount = 0;

	//�v���C���[��
	static int playerCount;

	//�{���J�E���g
	int bomCount = 0;
	//�{����
	static int bom;
	//�v���C���[�h 0...play 1...pause 2...replay 3...replay*2
	static int mode;

	//�Q�[�����[�h�ʓG�̒e���x�␳
	const float m_shotVel[3] = { 0.6f,0.8f,1.0f };
	//�Q�[�����[�h�ʓG�̒e�U���͕␳
	const float m_shotAttack[3] = { 2.0f,1.0f,0.0f };

	//�}�b�v�f�[�^�쐬�p
	MapData m_pMapData;
	//�}�b�v�����V�[�h�l
	int mapSeed;

	//�T�E���h�f�B���C
	int soundDeray;

	//�����蔻���������t���O
	bool colDir = true;

	//�X�e�[�W�N���A�t���[��
	int m_clearFrame = 10000;

	//�v���C���[�L�����N�^�[�X�e�[�^�X
	static int m_hp;
	static int m_maxHp;
	static int m_attackPt;
	static int m_score;
	static int m_speed;

	//���v���C�f�[�^���o���p
	int playerData;

	//�f���J�n�܂ł�SE�t���O
	bool se_flg = true;
	//�f���v���C���x��
	cocos2d::Label* pLavelDemo;

	//�w�i�̐����o�������邩�`�F�b�N
	void checkLaunchPlanet();
	//���o���t���[��
	int m_planetFrame;



};

#endif  defined(__ShootingGame__Main__)
