
#include "Character.h"
#include "Lib/InputManager/InputManager.h"
#include "Lib/InputManager/InputJoystick.h"
#include "Scene/GameMain/GameMain.h"
#include <math.h>

//=========================================================================
//	�v���C���[�L�����N�^�[�N���X�̃����o�֐��̒�`�͂������珑��
//=========================================================================
// �R���X�g���N�^
CPlayerCharacter::CPlayerCharacter() {
}



// �f�X�g���N�^
CPlayerCharacter::~CPlayerCharacter() {
}

/**
 *	@desc	����������
 */
bool CPlayerCharacter::init() {

	// cocos2d �̃N���X���p��������R���X�g���N�^��
	// �X�[�p�[�N���X�� init �֐����������Ȃ���΂Ȃ�Ȃ��̂Œ���
	if ( Sprite::init() == false ) {
		CCLOG( "CPlayerCharacter() Sprite::init is false !!!" ) ;
		return false ;
	}
	
	//=========================================================================
	//
	//	�������珉�����A�����ݒ�̃R�[�h��ǉ�
	//
	//=========================================================================
	
	//�摜�̐ݒ�
	//this->setTexture(IMAGE_FILE_CHARACTER);
	this->setTexture(IMAGE_FILE_CHARACTER_2);
	//�؂����`
	//this->m_chip.setRect(0,0,48,32);
	this->m_chip.setRect(0, 0, 48, 20);
	//�؂����`�̐ݒ�
	this->setTextureRect(this->m_chip);
	//�����ʒu�̐ݒ�
	this->setPosition(320,240);
	this->m_move.setPos(320, 240);
	this->m_move.setVel(0,0);
	//�A�j���[�V�����f�[�^�̏�����
	this->m_anime.set(20,3);

	//�e���˗p�J�E���^�[�̏�����
	this->m_shotCounter = 0;

	//�e���ˊԊu�̏�����(1�b�Ԃ�3�����˂ł���ݒ�)
	this->m_shotInterval = 5;

	//�e�U����
	this->m_shotPower = 1;

	//�e�p�����[�^
	this->m_shotParam = 0;

	//�Փ˗p�f�[�^�̏�����
	this->m_body.set(-15,10,15,-10);

	//�X�e�[�^�X�̏�����
	//�v���C���[�̃X�R�A�̓g�[�^���X�R�A�Ƃ��Ĉ���
	//this->m_status.set(20,20,1,0,2);
	//�v���C���[�X�e�[�^�X������
	this->m_status.set(
		CGameMain::m_hp,
		CGameMain::m_maxHp,
		CGameMain::m_attackPt,
		CGameMain::m_score,
		CGameMain::m_speed
	);


	//�L���t���O�̏�����
	this->m_activeFlag = true;

	//=========================================================================
	//
	//	�����܂łɏ������A�����ݒ�̃R�[�h��ǉ�
	//
	//=========================================================================


	return true ;
}

void CPlayerCharacter::moveFunc() {
	if (m_activeFlag == false)
		return;
	this->m_move.moveByVell();
}
void CPlayerCharacter::applyFunc() {
	if (m_activeFlag == false)
		return;
	this->setPosition(this->m_move.m_posX, this->m_move.m_posY);
	this->setTextureRect(this->m_chip);
}
void CPlayerCharacter::endOfScreen() {
	if (m_activeFlag == false)
		return;
	//�E�[
	if (this->m_move.m_posX + 15 > WINDOW_RIGHT) {
		//�v���C���[�̉E�[���E�B���h�E�����яo����(��ʂ̉E�[�ɓ��B����)

		//��яo���������v�Z(�v���C���[�̉E�[�@�]�@�E�B���h�E��)
		float boundary = (this->m_move.m_posX + 15) - WINDOW_RIGHT;

		//���݂̈ʒu�����яo���������������ʒu���v�Z
		this->m_move.m_posX = this->m_move.m_posX - boundary;
	}
	//���[
	if (this->m_move.m_posX - 15 < WINDOW_LEFT) {
		//�v���C���[�̉E�[���E�B���h�E�����яo����(��ʂ̉E�[�ɓ��B����)

		//��яo���������v�Z(�v���C���[�̉E�[�@�]�@�E�B���h�E��)
		float boundary = (this->m_move.m_posX - 15) - WINDOW_LEFT;

		//���݂̈ʒu�����яo���������������ʒu���v�Z
		this->m_move.m_posX = this->m_move.m_posX - boundary;
	}
	//��[
	if (this->m_move.m_posY + 10 > WINDOW_TOP) {
		//�v���C���[�̉E�[���E�B���h�E�����яo����(��ʂ̉E�[�ɓ��B����)

		//��яo���������v�Z(�v���C���[�̉E�[�@�]�@�E�B���h�E��)
		float boundary = (this->m_move.m_posY + 10) - WINDOW_TOP;

		//���݂̈ʒu�����яo���������������ʒu���v�Z
		this->m_move.m_posY = this->m_move.m_posY - boundary;
	}
	//���[
	if (this->m_move.m_posY - 10 < WINDOW_BOTTOM) {
		//�v���C���[�̉E�[���E�B���h�E�����яo����(��ʂ̉E�[�ɓ��B����)

		//��яo���������v�Z(�v���C���[�̉E�[�@�]�@�E�B���h�E��)
		float boundary = (this->m_move.m_posY - 10) - WINDOW_BOTTOM;

		//���݂̈ʒu�����яo���������������ʒu���v�Z
		this->m_move.m_posY = this->m_move.m_posY - boundary;
	}
}
void CPlayerCharacter::animationFunc() {
	if (m_activeFlag == false)
		return;
	//�A�j���[�V�����̍X�V���s��
	int frame = this->m_anime.update();
	//�t���[��������\������ׂ��`�b�v�f�[�^���v�Z����
	this->m_chip.setRect(this->m_chip.size.width * frame,0, this->m_chip.size.width, this->m_chip.size.height);
	
}


/**
*@desc �v���C���[�̒e�𔭎�
*@param �e�^�C�v
*@param �C���ʒuX
*@param �C���ʒuY
*@param ���xX
*@param ���xY
*/
CBullet* CPlayerCharacter::shotBullet(BULLET_TYPE type,float fixX,float fixY,float velX,float velY) {
	if (this->m_activeFlag == false)
		return NULL;
	
	//�v���C���[�̒e�̐���
	CBullet* pBul = CBullet::create();
	//�摜�̐ݒ�
	pBul->setTexture(IMAGE_FILE_BULLET);
	//�؂����`
	switch (type) {
		case BULLET_TYPE::PLAYER_INDUCTION:
		pBul->m_chip = CChip(0, 18, 8, 8);
		break;
	default:
		pBul->m_chip = CChip(0, 2, 8, 8);
		break;
	}
	
	pBul->setTextureRect(pBul->m_chip);
	//�ړ��f�[�^�ɏ����ʒu�̐ݒ�
	pBul->m_move.setPos(this->m_move.m_posX + fixX, this->m_move.m_posY + fixY);
	//�ړ��f�[�^�ɏ������x�̐ݒ�(x���W��+2����)�G
	pBul->m_move.setVel(velX, velY);
	//�����ʒu�𔻒�
	pBul->setPosition(pBul->m_move.m_posX, pBul->m_move.m_posY);
	
	//�L���t���O��true������
	pBul->m_activeFlag = true;

	//�e�^�C�v�̐ݒ�
	pBul->m_bulletType = type;

	//�A�j���[�V�����f�[�^�̏�����
	pBul->m_anime.set(10,4);

	//�Փ˔���p�f�[�^�̏�����
	pBul->m_body.set(-4, 4, 4, -4);

	return pBul;
}
//=========================================================================
//	�o���b�g ( �e ) �̃N���X�̃����o�֐��̒�`�͂������珑��
//=========================================================================
//�R���X�g���N�^
CBullet::CBullet() {
}
CBullet::~CBullet() {
}
/**
*@desc ����������
*/
bool CBullet::init() {
	//cocos2d�̃N���X���p��������R���X�g���N�^��
	//�X�[�p�[�N���X��init�֐����������Ȃ���΂Ȃ�Ȃ��̂Œ���
	if (Sprite::init() == false) {
		CCLOG("CBullet() Sprite::init is fales !!");
		return false;
	}

	//��������������
	//�A�j���[�V�����f�[�^�̏�����
	this->m_anime.set(20, 4);

	//this->setScale(5.0f);
	
	//�����������܂�
	return true;
}

void CBullet::moveFunc() {
	if (this->m_activeFlag == false)
		return;

	//�e���v�Z
	switch (m_bulletType) {
	case BULLET_TYPE::PLAYER_NORMAL:
		this->m_move.moveByVell();
		break;
	case BULLET_TYPE::PLAYER_EXPLOSION:
		this->m_move.moveByVell();
		break;
	case BULLET_TYPE::PLAYER_BACK:
		this->m_move.moveByVell();
		break;
	case BULLET_TYPE::PLAYER_LASER:
		this->m_move.m_posX = m_pmove->m_posX + 15;
		this->m_move.m_posY = m_pmove->m_posY;
		break;
	case BULLET_TYPE::PLAYER_INDUCTION:
	{
		if (target == -1 || CGameMain::m_pEnemyCharas[target] == NULL || CGameMain::m_pEnemyCharas[target]->m_activeFlag == false) {
			//�^�[�Q�b�g�������ꍇ
			mode = true;
			this->distance = 1000000.0f;
			
		}
		if (mode) {
			target = -1;
			//���G
			//�G�͔z��Ȃ̂œG�̂P�P�ƏՓ˔�������
			for (int i = 0; i <= CGameMain::m_pEnemyCount; i++) {
				//�v�f��NULL�Ȃ��΂�
				if (CGameMain::m_pEnemyCharas[i] == NULL)
					continue;

				//�L���t���O��false�̃C���X�^���X����΂�
				if (CGameMain::m_pEnemyCharas[i]->m_activeFlag == false)
					continue;

				//�G�L�����ƒe�̋������v�Z
				float distanceX = m_move.m_posX - CGameMain::m_pEnemyCharas[i]->m_move.m_posX;
				float distanceY = m_move.m_posY - CGameMain::m_pEnemyCharas[i]->m_move.m_posY;
				float distance = sqrt(distanceX * distanceX + distanceY * distanceY);
				if (distance <= this->distance) {
					//�^�[�Q�b�g�̓o�^
					target = i;
					this->distance = distance;
					mode = false;
					
					continue;
				}
					
			}
			
		}
		if (!mode && target != -1) {
			//�e�̈ړ��v�Z
			//�^�[�Q�b�g�ƒe�̊p�x���v�Z 
			float rot = atan2f(CGameMain::m_pEnemyCharas[target]->m_move.m_posY - this->m_move.m_posY,
				CGameMain::m_pEnemyCharas[target]->m_move.m_posX - this->m_move.m_posX) *
				180.0f / M_PI;
			
			//�^�[�Q�b�g�ƒe�̊p�x
			float rot2 = this->rotation - rot;
			
			//10 - 20 = -10 �}�C�i�X�̏ꍇ+�Ɉړ�
			//20 - 10 = 10 �v���X�̏ꍇ-�Ɉړ�
			//10 - 350 = -340  - 340 + 360 = 20 180�x���z�����ꍇ��360������������ɂ���
			//350 - 10 = 340   340 - 360 = -20 180�x���z�����ꍇ�͐�����360�����������ɂ���

			if (rot2 <= -180) {
				rot2 += 360;
			}
			if (rot2 >= 180) {
				rot2 -= 360;
			}

			if (rot2 >=0) {
				//�p�x���}�C�i�X
				if (rot2 >= this->param) {
					this->rotation -= this->param;
				}
				else {
					//�p�x��G�̊p�x�ɍ��킹��
					this->rotation = rot;
				}
				
			}
			else {
				//�p�x���v���X
				if (rot2 <= this->param) {
					this->rotation += this->param;
				}
				else {
					//�p�x��G�̊p�x�ɍ��킹��
					this->rotation = rot;
				}
			}

			//�p�x�I�[�o�[�C��
			if (this->rotation < 0) {
				this->rotation += 360;
			}
			if (this->rotation > 360) {
				this->rotation -= 360;
			}

			//X���W�̈ړ���
			//�p�x���񎟃x�N�g�����擾
			float velX = cos(this->rotation * M_PI / 180.0f) * this->vel;
			
			//Y���W�̈ړ���
			float velY = sin(this->rotation * M_PI / 180.0f) * this->vel;

			//�ړ��������Z�b�g
			this->m_move.setVel(velX,velY);
		}
		//��]����
		setRotation(-this->rotation);

		//�ړ�����
		this->m_move.moveByVell();
	}
		

		break;
	case BULLET_TYPE::PLAYER_MULTIPLE:
		this->m_move.moveByVell();
		break;
	case BULLET_TYPE::ENEMY_NORMAL:
		this->m_move.moveByVell();
		break;
	case BULLET_TYPE::ENEMY_FAN:
		this->m_move.moveByVell();
		break;
	case BULLET_TYPE::ENEMY_AIMING:
		this->m_move.moveByVell();
		break;
	case BULLET_TYPE::ENEMY_2WAY:
		this->m_move.moveByVell();
		break;
	}


	
}
void CBullet::applyFunc() {
	if (this->m_activeFlag == false)
		return;

	this->setPosition(
		this->m_move.m_posX,
		this->m_move.m_posY
	);
	this->setTextureRect(this->m_chip);
}
void CBullet::endOfScreen() {
	if (this->m_activeFlag == false)
		return;

	//�e�摜�̍��[�̍��W����ʉE�[�̍��W���傫���Ȃ�����
	if (this->m_move.m_posX - this->m_chip.size.width * 0.5f > WINDOW_RIGHT + 50) {
		//�L���t���O��������
		this->m_activeFlag = false;
	}
	//�e�摜�̉E�[�̍��W����ʉE�[�̍��W���傫���Ȃ�����
	if (this->m_move.m_posX + this->m_chip.size.width * 0.5f < WINDOW_LEFT - 50) {
		//�L���t���O��������
		this->m_activeFlag = false;
	}
	//�e�摜�̏�[�̍��W����ʉE�[�̍��W���傫���Ȃ�����
	if (this->m_move.m_posY - this->m_chip.size.height * 0.5f > WINDOW_TOP + 50) {
		//�L���t���O��������
		this->m_activeFlag = false;
	}
	//�e�摜�̉E�[�̍��W����ʉE�[�̍��W���傫���Ȃ�����
	if (this->m_move.m_posY + this->m_chip.size.height * 0.5f < WINDOW_BOTTOM - 50) {
		//�L���t���O��������
		this->m_activeFlag = false;
	}
}

void CBullet::animationFunc() {
	if (this->m_activeFlag == false)
		return;
	
	//���Ńt���O�L���̏ꍇ
	if (this->m_delflg == true) {
		//����t���[���ŗL���t���O������
		if(this->m_count == this->m_maxCount) {
			this->m_activeFlag = false;
		}
		else {
			m_count++;
		}
	} 

	//�A�j���[�V�����̍X�V���s��
	int frame = this->m_anime.update();
	//�t���[��������\������ׂ��`�b�v�f�[�^���v�Z����
	this->m_chip.setRect(
		this->m_chip.size.width * frame,
		this->m_chip.origin.y,
		this->m_chip.size.width,
		this->m_chip.size.height);
}

//=========================================================================
//	�G�̃N���X�̃����o�֐��̒�`�͂������珑��
//=========================================================================
CEnemyCharacter::CEnemyCharacter() {

}
CEnemyCharacter::~CEnemyCharacter() {

}
bool CEnemyCharacter::init() {
	//cocos2d�̃N���X���p��������R���X�g���N�^��
	//�X�[�p�[�N���X��init�֐����������Ȃ���΂Ȃ�Ȃ��̂Œ���
	if (Sprite::init() == false) {
		CCLOG("CEnemyCharacter() Sprite::init is false!!");
		return false;
	}
	//===========================================
	//��������A���A�����ݒ�̃R�[�h��ǉ�
	//===========================================


	//===========================================
	//�����܂łɏ������A�������ݒ��ǉ�
	//===========================================
	return true;
}

//�ړ��Ɋւ��郁���o�֐��錾
void CEnemyCharacter::moveFunc() {
	if (this->m_activeFlag == false)
		return;

	//�ړ�����
	this->m_move.moveByVell();

	//�^�[�Q�b�g�ƒe�̊p�x���v�Z 
	if (e_enemyType == ENEMY_TYPE::TYPE_C) {
		float rot = atan2f(CGameMain::m_pPlayerChara->m_move.m_posY - this->m_move.m_posY,
			CGameMain::m_pPlayerChara->m_move.m_posX - this->m_move.m_posX) *
			180.0f / M_PI;

		this->rotation = rot + this->getRotation();

		//��]����
		m_pChr->setRotation(-this->rotation);
	}
	
}

//�A�j���[�V�����Ɋւ��郁���o�֐��錾
void CEnemyCharacter::animationFunc() {
	if (this->m_activeFlag == false)
		return;

	//�A�j���[�V�����̍X�V���s��
	int frame = this->m_anime.update();
	//�t���[��������\������ׂ��`�b�v�f�[�^���v�Z����
	this->m_chip.setRect(
	this->m_chip.size.width * frame,
	this->m_chip.origin.y,
	this->m_chip.size.width,
	this->m_chip.size.height
	);
	
}

//��ʒ[�Ɋւ��郁���o�֐��錾
void CEnemyCharacter::endOfScreen() {
	if (this->m_activeFlag == false)
		return;
	
	//�e�摜�̍��[�̍��W����ʉE�[�̍��W��菬�����Ȃ�����
	if (this->m_move.m_posX + this->m_chip.size.width * 0.5f < WINDOW_LEFT - 40) {
		//�L���t���O��������
		this->m_activeFlag = false;
	}
	//�e�摜�̉E�[�̍��W����ʍ��[�̍��W���傫���Ȃ�����
	if (this->m_move.m_posX - this->m_chip.size.width * 0.5f > WINDOW_RIGHT + 40) {
		//�L���t���O��������
		this->m_activeFlag = false;
	}
	//�e�摜�̏�[�̍��W����ʉ��[�̍��W��菬�����Ȃ�����
	if (this->m_move.m_posY + this->m_chip.size.height * 0.5f < WINDOW_BOTTOM - 40) {
		//�L���t���O��������
		this->m_activeFlag = false;
	}
	//�e�摜�̉E�[�̍��W����ʍ��[�̍��W��菬�����Ȃ�����
	if (this->m_move.m_posY - this->m_chip.size.height * 0.5f > WINDOW_TOP + 40) {
		//�L���t���O��������
		this->m_activeFlag = false;
	}
}

/**
*@desc �G�̒e�𐶐�
*@param �e�^�C�v
*@param �C���lX
*@param �C���lY
*@param ���xX
*@param ���xY
*/
CBullet* CEnemyCharacter::shotBullet(BULLET_TYPE type, float fixX, float fixY, float velX, float velY) {
	if (this->m_activeFlag == false)
		return NULL;

	//�v���C���[�̒e�̐���
	CBullet* pBul = CBullet::create();
	//�摜�̐ݒ�
	pBul->setTexture(IMAGE_FILE_BULLET);
	//�؂����`
	pBul->m_chip = CChip(0, 10, 8, 8);
	pBul->setTextureRect(pBul->m_chip);

	//�ړ��f�[�^�ɏ����ʒu�̐ݒ�
	pBul->m_move.setPos(this->m_move.m_posX + fixX, this->m_move.m_posY + fixY);
	//�ړ��f�[�^�ɏ������x�̐ݒ�(x���W��+2����)�G
	pBul->m_move.setVel(velX, velY);

	//�A�j���[�V�����f�[�^�̏�����
	pBul->m_anime.set(5,4);
	//�Փ˔���p�f�[�^�̏�����
	pBul->m_body.set(-4,4,4,-4);

	//�L���t���O��true������
	pBul->m_activeFlag = true;

	//�e�^�C�v�̐ݒ�
	pBul->m_bulletType = type;
	return pBul;
}

//�l�̔��f�Ɋւ��郁���o�֐��錾
void CEnemyCharacter::applyFunc() {
	if (this->m_activeFlag == false)
		return;

	this->setPosition(this->m_move.m_posX, this->m_move.m_posY);
	this->setTextureRect(this->m_chip);
}


//=========================================================================
//	�G�t�F�N�g�̃N���X�̃����o�֐��̒�`�͂������珑��
//=========================================================================

CEfect::CEfect() {

}
CEfect::~CEfect() {

}
bool CEfect::init() {
	//cocos2d�̃N���X���p��������R���X�g���N�^��
	//�X�[�p�[�N���X��init�֐����������Ȃ���΂Ȃ�Ȃ��̂Œ���
	if (Sprite::init() == false) {
		CCLOG("CEnemyCharacter() Sprite::init is false!!");
		return false;
	}
	//===========================================
	//��������A���A�����ݒ�̃R�[�h��ǉ�
	//===========================================


	//===========================================
	//�����܂łɏ������A�������ݒ��ǉ�
	//===========================================
	return true;
}

//�ړ��Ɋւ��郁���o�֐��錾
void CEfect::moveFunc() {
	if (this->m_activeFlag == false)
		return;

	//�ړ�����
	this->m_move.moveByVell();
}

//�A�j���[�V�����Ɋւ��郁���o�֐��錾
void CEfect::animationFunc() {
	//�A�j���[�V�����I���ŗL���t���O������
	if (this->m_anime.m_isEnd == true) {
		this->m_activeFlag = false;
	}

	if (this->m_activeFlag == false) {
		return;
	}
	this->getParent();
	
	//�A�j���[�V�����̍X�V���s��
	int frame = this->m_anime.update();
	//�t���[��������\������ׂ��`�b�v�f�[�^���v�Z����
	this->m_chip.setRect(
		this->m_chip.size.width * (frame % maxX),
		this->m_chip.size.height * (frame / maxX),
		this->m_chip.size.width,
		this->m_chip.size.height
	);

}


//�l�̔��f�Ɋւ��郁���o�֐��錾
void CEfect::applyFunc() {
	if (this->m_activeFlag == false)
		return;

	this->setPosition(this->m_move.m_posX, this->m_move.m_posY);
	this->setTextureRect(this->m_chip);
}

void CEfect::endOfScreen() {
	if (this->m_activeFlag == false)
		return;

	//�e�摜�̍��[�̍��W����ʉE�[�̍��W���傫���Ȃ�����
	if (this->m_move.m_posX - this->m_chip.size.width * 0.5f > WINDOW_RIGHT + 200.0f) {
		//�L���t���O��������
		this->m_activeFlag = false;
	}
	//�e�摜�̉E�[�̍��W����ʉE�[�̍��W���傫���Ȃ�����
	if (this->m_move.m_posX + this->m_chip.size.width * 0.5f < WINDOW_LEFT - 200.0f) {
		//�L���t���O��������
		this->m_activeFlag = false;
	}
	//�e�摜�̏�[�̍��W����ʉE�[�̍��W���傫���Ȃ�����
	if (this->m_move.m_posY - this->m_chip.size.height * 0.5f > WINDOW_TOP + 200.0f) {
		//�L���t���O��������
		this->m_activeFlag = false;
	}
	//�e�摜�̉E�[�̍��W����ʉE�[�̍��W���傫���Ȃ�����
	if (this->m_move.m_posY + this->m_chip.size.height * 0.5f < WINDOW_BOTTOM - 200.0f) {
		//�L���t���O��������
		this->m_activeFlag = false;
	}
}


/**
*@desc ����̍U�������g�ɂ�������
*@param �Փ˂��Ă�������̃X�e�[�^�X�̃A�h���X
*/
void CPlayerCharacter::hits(CStatus* pStatus) {
	//HP������������
	this->m_status.decreaseHp(pStatus->getAttackPt());

	//HP��0�ȉ��������ꍇ�L���t���O��������
	if (this->m_status.getHp() <= 0) {
		this->m_activeFlag = false;
	}
}

/**
*@desc ����̍U�������g�ɂ�������
*@param �Փ˂��Ă�������̃X�e�[�^�X�̃A�h���X
*/
void CEnemyCharacter::hits(CStatus* pStatus) {
	//HP������������
	this->m_status.decreaseHp(pStatus->getAttackPt());

	//HP��0�ȉ��������ꍇ�L���t���O��������
	if (this->m_status.getHp() <= 0) {
		this->m_activeFlag = false;
	}
}

//�s���Ɋւ��郁���o�֐��̐錾
void CEnemyCharacter::actionFunc() {
	

}

//=========================================================================
//	�A�C�e���̃N���X�̃����o�֐��̒�`�͂������珑��
//=========================================================================

CItem::CItem() {

}
CItem::~CItem() {

}
bool CItem::init() {
	//cocos2d�̃N���X���p��������R���X�g���N�^��
	//�X�[�p�[�N���X��init�֐����������Ȃ���΂Ȃ�Ȃ��̂Œ���
	if (Sprite::init() == false) {
		CCLOG("CItem() Sprite::init is false!!");
		return false;
	}
	//===========================================
	//��������A���A�����ݒ�̃R�[�h��ǉ�
	//===========================================


	//===========================================
	//�����܂łɏ������A�������ݒ��ǉ�
	//===========================================
	return true;
}

//�ړ��Ɋւ��郁���o�֐��錾
void CItem::moveFunc() {
	if (this->m_activeFlag == false)
		return;

	//�ړ�����
	this->m_move.moveByVell();
}

//�A�j���[�V�����Ɋւ��郁���o�֐��錾
void CItem::animationFunc() {

	if (this->m_activeFlag == false)
		return;

	//�A�j���[�V�����̍X�V���s��
	int frame = this->m_anime.update();
	//�t���[��������\������ׂ��`�b�v�f�[�^���v�Z����
	this->m_chip.setRect(
		this->m_chip.size.width * frame,
		this->m_chip.origin.y,
		this->m_chip.size.width,
		this->m_chip.size.height
	);

	//�A�C�e���^�C�v�؂�ւ�
	//this->type = (ITEM_TYPE)frame;
}


//�l�̔��f�Ɋւ��郁���o�֐��錾
void CItem::applyFunc() {
	if (this->m_activeFlag == false)
		return;

	this->setPosition(this->m_move.m_posX, this->m_move.m_posY);
	this->setTextureRect(this->m_chip);
}
/**
*@desc ����̍U�������g�ɂ�������
*@param �Փ˂��Ă�������̃X�e�[�^�X�̃A�h���X
*/
void CItem::hits(CStatus* pStatus) {
	//�A�C�e���擾����
	switch (this->type) {
	case ITEM_TYPE::RECOVERY:
		pStatus->hpUp(50);
		break;
	case ITEM_TYPE::SPEEDUP:
		pStatus->speedUp(1);
		break;
	case ITEM_TYPE::NORMAL:
		if (CGameMain::pweponLevel[0] < 9) {
			CGameMain::pweponLevel[0] += 1;
			pweponLevelLavel[0]->setString(cocos2d::StringUtils::format("Level %d", CGameMain::pweponLevel[0] + 1));
		}
			
		
		break;
	case ITEM_TYPE::EXPLOSION:
		if (CGameMain::pweponLevel[1] < 9) {
			CGameMain::pweponLevel[1] += 1;
			pweponLevelLavel[1]->setString(cocos2d::StringUtils::format("Level %d", CGameMain::pweponLevel[1] + 1));
		}

		break;
	case ITEM_TYPE::BACK:
		if (CGameMain::pweponLevel[2] < 9) {
			CGameMain::pweponLevel[2] += 1;
			pweponLevelLavel[2]->setString(cocos2d::StringUtils::format("Level %d", CGameMain::pweponLevel[2] + 1));
		}

		break;
	case ITEM_TYPE::LASER:
		if (CGameMain::pweponLevel[3] < 9) {
			CGameMain::pweponLevel[3] += 1;
			pweponLevelLavel[3]->setString(cocos2d::StringUtils::format("Level %d", CGameMain::pweponLevel[3] + 1));
		}

		break;
	case ITEM_TYPE::INDUCTION:
		if (CGameMain::pweponLevel[4] < 9) {
			CGameMain::pweponLevel[4] += 1;
			pweponLevelLavel[4]->setString(cocos2d::StringUtils::format("Level %d", CGameMain::pweponLevel[4] + 1));
		}

		break;
	case ITEM_TYPE::MULTIPLE:
		if (CGameMain::pweponLevel[5] < 9) {
			CGameMain::pweponLevel[5] += 1;
			pweponLevelLavel[5]->setString(cocos2d::StringUtils::format("Level %d", CGameMain::pweponLevel[5] + 1));
		}

		break;
	case ITEM_TYPE::BOM:
		if (CGameMain::bom < 16) {
			CGameMain::bom += 1;
		}
		
		break;
	case ITEM_TYPE::ONE_UP:
		if (CGameMain::playerCount < 16) {
			CGameMain::playerCount += 1;
		}
		
		break;
	default:
		break;
	}
	
	//�L���t���O��������
	this->m_activeFlag = false;
}
void CItem::endOfScreen() {
	if (this->m_activeFlag == false)
		return;

	//�e�摜�̍��[�̍��W����ʉE�[�̍��W���傫���Ȃ�����
	if (this->m_move.m_posX - this->m_chip.size.width * 0.5f > WINDOW_RIGHT) {
		//�L���t���O��������
		this->m_activeFlag = false;
	}
	//�e�摜�̉E�[�̍��W����ʉE�[�̍��W���傫���Ȃ�����
	if (this->m_move.m_posX + this->m_chip.size.width * 0.5f < WINDOW_LEFT) {
		//�L���t���O��������
		this->m_activeFlag = false;
	}
	//�e�摜�̏�[�̍��W����ʉE�[�̍��W���傫���Ȃ�����
	if (this->m_move.m_posY - this->m_chip.size.height * 0.5f > WINDOW_TOP) {
		//�L���t���O��������
		this->m_activeFlag = false;
	}
	//�e�摜�̉E�[�̍��W����ʉE�[�̍��W���傫���Ȃ�����
	if (this->m_move.m_posY + this->m_chip.size.height * 0.5f < WINDOW_BOTTOM) {
		//�L���t���O��������
		this->m_activeFlag = false;
	}
}

cocos2d::Label** CItem::pweponLevelLavel;

//=========================================================================
//	�J�[�\���̃N���X�̃����o�֐��̒�`�͂������珑��
//=========================================================================

CCursor::CCursor() {

}
CCursor::~CCursor() {

}
bool CCursor::init() {
	//cocos2d�̃N���X���p��������R���X�g���N�^��
	//�X�[�p�[�N���X��init�֐����������Ȃ���΂Ȃ�Ȃ��̂Œ���
	if (Sprite::init() == false) {
		CCLOG("CItem() Sprite::init is false!!");
		return false;
	}
	//===========================================
	//��������A���A�����ݒ�̃R�[�h��ǉ�
	//===========================================

	

	//===========================================
	//�����܂łɏ������A�������ݒ��ǉ�
	//===========================================
	return true;
}

//�ړ��Ɋւ��郁���o�֐��錾
void CCursor::moveFunc() {
	//�ړ�����
	this->m_move.moveByVell();
}

//�A�j���[�V�����Ɋւ��郁���o�֐��錾
void CCursor::animationFunc() {

	//�A�j���[�V�����̍X�V���s��
	int frame = this->m_anime.update();
	//�t���[��������\������ׂ��`�b�v�f�[�^���v�Z����
	this->m_chip.setRect(
		this->m_chip.size.width * frame,
		this->m_chip.origin.y,
		this->m_chip.size.width,
		this->m_chip.size.height
	);

}


//�l�̔��f�Ɋւ��郁���o�֐��錾
void CCursor::applyFunc() {
	
	this->setPosition(this->m_move.m_posX, this->m_move.m_posY);
	this->setTextureRect(this->m_chip);
}

/*
*@desc �J�[�\�������ݒ�
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
void CCursor::set(
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
) {
	//�摜�̐ݒ�
	this->setTexture(p_fileName);
	//�؂����`
	this->m_chip.setRect(p_chipPointX, p_chipPointY, p_chipX, p_chipY);
	//�؂����`�̐ݒ�
	this->setTextureRect(this->m_chip);
	//�A�j���[�V�������ݒ�
	this->p_animation = p_animation;
	//�A�j���[�V�����t���[�����ݒ�
	this->p_animeFrame = p_animeFrame;
	//�J�[�\���̍ő�l�ݒ�
	this->p_maxX = p_maxX;
	this->p_maxY = p_maxY;
	//�J�[�\���ʒu�ݒ�
	this->p_x = p_x;
	this->p_y = p_y;
	//�J�[�\���̍��W�ݒ�
	this->p_xPoint = p_xPoint;
	this->p_yPoint = p_yPoint;
	//�ړ��T�C�Y�ݒ�
	this->p_moveX = p_moveX;
	this->p_moveY = p_moveY;
	//�ړ��t���[���ݒ�
	this->p_moveFrame = p_moveFrame;
	//���[�v�ݒ�
	this->p_xLoop = p_xLoop;
	this->p_yLoop = p_yLoop;
	//�҂��t���[���ݒ�
	this->p_fastWait = p_fastWait;
	this->p_slowWait = p_slowWait;

	//�����ʒu�̐ݒ�
	this->setPosition(p_xPoint + p_x * p_moveX, p_yPoint + p_y * p_moveY);
	this->m_move.setPos(p_xPoint + p_x * p_moveX, p_yPoint + p_y * p_moveY);
	this->m_move.setVel(0, 0);
	//�A�j���[�V�����f�[�^�̏�����
	this->m_anime.set(p_animeFrame, p_animation);
}

void CCursor::inputFunc() {

	//���̓t���O�ݒ�
	CInputJoystick::inputFunc(1);

	//���͑҂�
	if (this->p_input == 0) {
		//�ړ��I���t���O�`�F�b�N
		if (moveflg)
			moveflg = false;


		if (CInputJoystick::m_right || CInputJoystick::m_left || CInputJoystick::m_up || CInputJoystick::m_down) {
			OutputDebugString(L"�J�[�\�����͌��m\n");

			//�J�[�\���L�[�������ꂽ����͌��m�ɕύX
			this->p_input = 1;
			//�t���[���J�E���g���Z�b�g
			this->p_countFrame = 0;
			//������͑҂�����
			if (this->p_fastPush) {
				this->p_fastPush = false;
				OutputDebugString(L"�������\n");
				//�҂����Ԃ�������͑҂����Ԃɐݒ�
				this->p_wait = this->p_inputWait;
			}
			else {
				OutputDebugString(L"����ȍ~����\n");
				//�҂����Ԃ�����ȍ~���͑҂����Ԃɐݒ�
				if (this->p_speed) {
					OutputDebugString(L"�ᑬ\n");
					//�ᑬ
					this->p_wait = this->p_slowWait;
					//�����ɕύX
					this->p_speed = false;
				}
				else {
					OutputDebugString(L"����\n");
					//����
					this->p_wait = this->p_fastWait;
				}
			}
		}
		else {
			//������ĂȂ���Ώ�������
			//������͂ɕύX
			this->p_fastPush = true;
			//�ᑬ�ɕύX
			this->p_speed = true;
			return;
		}
	}



	//���͌��m�҂�
	if (this->p_input == 1)
	{
		if (!CInputJoystick::m_right && !CInputJoystick::m_left && !CInputJoystick::m_up && !CInputJoystick::m_down) {
			//�L�[�{�[�h�����ׂė����ꂽ��
			//���͑҂��ɕύX
			this->p_input = 0;
			//������͂ɖ߂�
			this->p_fastPush = true;
			//�ᑬ�ɖ߂�
			this->p_speed = true;
			return;
		}
		//�J�E���g���҂����ԂɒB�������ꍇ��������
		if (this->p_countFrame < this->p_wait) {
			//�t���[���J�E���g�A�b�v
			this->p_countFrame++;
			return;
		}
		//�ړ����ɕύX
		this->p_input = 2;
		//�t���[���J�E���g���Z�b�g
		this->p_countFrame = 0;
		//�ړ��O�J�[�\���ʒu�L�^
		this->p_beforeX = this->p_x;
		this->p_beforeY = this->p_y;
		
		//�L�[����
		if (CInputJoystick::m_right == true)
		{
			//�E��󂪉����ꂽ
			this->p_x++;
		} else if (CInputJoystick::m_left == true)
		{
			//�E��󂪉����ꂽ
			this->p_x--;
		}

		if (CInputJoystick::m_up == true)
		{
			//���󂪉����ꂽ
			this->p_y++;
		} else if (CInputJoystick::m_down == true)
		{
			//����󂪉����ꂽ
			this->p_y--;
		}

		//�J�[�\���I�[�o�[�C��
		//���I�[�o�[
		if (this->p_x < 0) {
			OutputDebugString(L"�����I�[�o�[\n");
			//���[�v���ǂ����Őݒ�𕪊�
			this->p_xLoop ? this->p_x = this->p_maxX : this->p_x = 0;
		}
		else if (this->p_x > this->p_maxX) {
			OutputDebugString(L"�����I�[�o�[\n");
			//���[�v���ǂ����Őݒ�𕪊�
			this->p_xLoop ? this->p_x = 0 : this->p_x = this->p_maxX;
		}
		//�c�I�[�o�[
		if (this->p_y < 0) {
			OutputDebugString(L"�c���I�[�o�[\n");
			//���[�v���ǂ����Őݒ�𕪊�
			this->p_yLoop ? this->p_y = this->p_maxY : this->p_y = 0;
		}
		else if (this->p_y > this->p_maxY) {
			OutputDebugString(L"�c���I�[�o�[\n");
			//���[�v���ǂ����Őݒ�𕪊�
			this->p_yLoop ? this->p_y = 0 : this->p_y = this->p_maxY;
		}
		//�ړ��Ȃ��̏ꍇ�͓��͑҂��ɂ���
		if (this->p_beforeX == this->p_x && this->p_beforeY == this->p_y) {
			//���͑҂��ɕύX
			//this->p_input == 0;
			//�ᑬ�ɖ߂�
			//this->p_speed = true;
			return;
		}
		//���͑҂��ɕύX
		this->p_input = 2;
		//�t���[���J�E���g���Z�b�g
		this->p_countFrame = 0;
		//�ړ��J�E���g���Z�b�g
		this->p_moveCount = 0;
		//�ړ��ʂ�ݒ�
		this->m_move.m_velX = (this->p_x - this->p_beforeX) * this->p_moveX / (float)this->p_moveFrame;
		this->m_move.m_velY = (this->p_y - this->p_beforeY) * this->p_moveY / (float)this->p_moveFrame;

		//�J�[�\��SE
		int seid = AudioEngine::play2d(SOUND_FILE_CURSOR_1);
		AudioEngine::setVolume(seid, SE_VOLUME / 100.0f);
	}

	//�ړ���
	if (this->p_input == 2) {

		//�ړ��J�E���g�A�b�v
		this->p_countFrame++;
		//�ړ��A�j���[�V�����I���m�F
		if (this->p_countFrame < this->p_moveFrame) {
			return;
		}

		//���͌��m�ɕύX
		this->p_input = 0;
		//�ړ��ʂ�0��
		this->m_move.m_velX = 0;
		this->m_move.m_velY = 0;

		//���W���҂����荇�킹��
		this->m_move.setPos(
			this->p_xPoint + this->p_x * this->p_moveX,
			this->p_yPoint + this->p_y * this->p_moveY
		);

		//�ړ��I���t���O�L��
		moveflg = true;
	}

}

//=========================================================================
//	�ǂ̃N���X�̃����o�֐��̒�`�͂������珑��
//=========================================================================

CWall::CWall() {

}
CWall::~CWall() {

}
bool CWall::init() {
	//cocos2d�̃N���X���p��������R���X�g���N�^��
	//�X�[�p�[�N���X��init�֐����������Ȃ���΂Ȃ�Ȃ��̂Œ���
	if (Sprite::init() == false) {
		CCLOG("CWall() Sprite::init is false!!");
		return false;
	}
	//===========================================
	//��������A���A�����ݒ�̃R�[�h��ǉ�
	//===========================================


	//===========================================
	//�����܂łɏ������A�������ݒ��ǉ�
	//===========================================
	return true;
}

//�ړ��Ɋւ��郁���o�֐��錾
void CWall::moveFunc() {
	if (this->m_activeFlag == false)
		return;

	//�ړ�����
	this->m_move.moveByVell();
}

//�A�j���[�V�����Ɋւ��郁���o�֐��錾
void CWall::animationFunc() {

	if (this->m_activeFlag == false)
		return;

	//�A�j���[�V�����̍X�V���s��
	int frame = this->m_anime.update();
	//�t���[��������\������ׂ��`�b�v�f�[�^���v�Z����
	this->m_chip.setRect(
		this->m_chip.size.width * frame,
		this->m_chip.origin.y,
		this->m_chip.size.width,
		this->m_chip.size.height
	);

	//�A�C�e���^�C�v�؂�ւ�
	//this->type = (ITEM_TYPE)frame;
}


//�l�̔��f�Ɋւ��郁���o�֐��錾
void CWall::applyFunc() {
	if (this->m_activeFlag == false)
		return;

	this->setPosition(this->m_move.m_posX, this->m_move.m_posY);
	this->setTextureRect(this->m_chip);
}
/**
*@desc ����̍U�������g�ɂ�������
*@param �Փ˂��Ă�������̃X�e�[�^�X�̃A�h���X
*/
void CWall::hits(CStatus* pStatus) {
	
}
void CWall::endOfScreen() {
	if (this->m_activeFlag == false)
		return;

	//�e�摜�̍��[�̍��W����ʉE�[�̍��W���傫���Ȃ�����
	if (this->m_move.m_posX - this->m_chip.size.width * 0.5f > WINDOW_RIGHT) {
		//�L���t���O��������
		this->m_activeFlag = false;
	}
	//�e�摜�̉E�[�̍��W����ʉE�[�̍��W���傫���Ȃ�����
	if (this->m_move.m_posX + this->m_chip.size.width * 0.5f < WINDOW_LEFT) {
		//�L���t���O��������
		this->m_activeFlag = false;
	}
	//�e�摜�̏�[�̍��W����ʉE�[�̍��W���傫���Ȃ�����
	if (this->m_move.m_posY - this->m_chip.size.height * 0.5f > WINDOW_TOP) {
		//�L���t���O��������
		this->m_activeFlag = false;
	}
	//�e�摜�̉E�[�̍��W����ʉE�[�̍��W���傫���Ȃ�����
	if (this->m_move.m_posY + this->m_chip.size.height * 0.5f < WINDOW_BOTTOM) {
		//�L���t���O��������
		this->m_activeFlag = false;
	}
}
