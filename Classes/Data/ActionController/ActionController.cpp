#include "ActionController.h"
#include "Model/Character/Character.h"
#include "Data/MapData/MapData.h"

//�R���X�g���N�^
CActionControllerZigZag::CActionControllerZigZag():m_actionType(ACTION_TYPE::ZIGZAG){

}
void CActionControllerZigZag::actionFunc(CEnemyCharacter* pEne) {
	//X���W��320�ȉ��ɂȂ�����
	if (pEne->m_actionStep == 0 && pEne->m_move.m_posX <= 320.0f) {
		//��Ɉړ�
		pEne->m_move.m_velX = 0.0f;
		pEne->m_move.m_velY = 5.0f;
		pEne->m_shotFlag = false;
		//�X�e�b�v��1�ɂ���
		pEne->m_actionStep = 1;
	}
	//Y���W��240�ȏ�ɂȂ�����
	if (pEne->m_actionStep == 1 && pEne->m_move.m_posY >= 240.0f) {
		//�e�𔭎�
		pEne->m_move.m_velX = 0.0f;
		pEne->m_move.m_velY = 5.0f;
		pEne->m_shotFlag = true;
		//�X�e�b�v��2�ɂ���
		pEne->m_actionStep = 2;
	}
	//Y���W��380�ȏ�ɂȂ�����
	if (pEne->m_actionStep == 2 && pEne->m_move.m_posY >= 380.0f) {
		//���Ɉړ�
		pEne->m_move.m_velX = -5.0f;
		pEne->m_move.m_velY = 0.0f;
		pEne->m_shotFlag = false;
		//�X�e�b�v��3�ɂ���
		pEne->m_actionStep = 3;
	}
}

//�R���X�g���N�^
CActionControllerStraight::CActionControllerStraight() :m_actionType(ACTION_TYPE::STRAIGHT) {

}
void CActionControllerStraight::actionFunc(CEnemyCharacter* pEne) {
	//X���W���R���̂Q���炢�ɂ�����e�𔭎�
	if (pEne->m_actionStep == 0 && pEne->m_move.m_posX <= WINDOW_RIGHT * 0.6666f) {
		//��Ɉړ�
		pEne->m_move.m_velX = -5.0f;
		pEne->m_move.m_velY = 0.0f;
		pEne->m_shotFlag = true;
		//�X�e�b�v��1�ɂ���
		pEne->m_actionStep = 1;
	}
	//X���W���R����1���炢�ɂ�����e�𔭎�
	if (pEne->m_actionStep == 1 && pEne->m_move.m_posX <= WINDOW_RIGHT * 0.3333f) {
		//�e�𔭎�
		pEne->m_move.m_velX = -5.0f;
		pEne->m_move.m_velY = 0.0f;
		pEne->m_shotFlag = true;
		//�X�e�b�v��2�ɂ���
		pEne->m_actionStep = 2;
	}
}

//�R���X�g���N�^
CActionControllerConvex::CActionControllerConvex() :m_actionType(ACTION_TYPE::CONVEX) {

}
void CActionControllerConvex::actionFunc(CEnemyCharacter* pEne) {
	//X���W���R���̂Q���炢�ɂ����牺�Ɉړ�
	if (pEne->m_actionStep == 0 && pEne->m_move.m_posX <= WINDOW_RIGHT * 0.6666f) {
		//��Ɉړ�
		pEne->m_move.m_velX = 0.0f;
		pEne->m_move.m_velY = -5.0f;
		pEne->m_shotFlag = false;
		//�X�e�b�v��1�ɂ���
		pEne->m_actionStep = 1;
	}
	//Y���W��100�ȉ��ɂ����獶�Ɉړ����e�𔭎�
	if (pEne->m_actionStep == 1 && pEne->m_move.m_posY <= 100.0) {
		//�e�𔭎�
		pEne->m_move.m_velX = -5.0f;
		pEne->m_move.m_velY = 0.0f;
		pEne->m_shotFlag = true;
		//�X�e�b�v��2�ɂ���
		pEne->m_actionStep = 2;
	}
	//X���W���R���̂Q���炢�ɂ������Ɉړ�
	if (pEne->m_actionStep == 2 && pEne->m_move.m_posX <= WINDOW_RIGHT * 0.3333f) {
		//�e�𔭎�
		pEne->m_move.m_velX = 0.0f;
		pEne->m_move.m_velY = 5.0f;
		pEne->m_shotFlag = false;
		//�X�e�b�v��2�ɂ���
		pEne->m_actionStep = 3;
	}
	//Y���W��380�ɂ����獶�Ɉړ�
	if (pEne->m_actionStep == 3 && pEne->m_move.m_posY >= 380.0) {
		//�e�𔭎�
		pEne->m_move.m_velX = -5.0f;
		pEne->m_move.m_velY = 0.0f;
		pEne->m_shotFlag = true;
		//�X�e�b�v��2�ɂ���
		pEne->m_actionStep = 4;
	}
}

//�R���X�g���N�^
CActionControllerOriginal::CActionControllerOriginal() :m_actionType(ACTION_TYPE::ORIGINAL) {

}
void CActionControllerOriginal::actionFunc(CEnemyCharacter* pEne) {
	
	pEne->shotCount++;
	//�e����
	if (pEne->shotCount % 120 == 0 || pEne->shotCount % 120 == 5) {
		pEne->m_shotFlag = true;
	}
	//�A�N�V����������ɒB���Ă����ꍇ�͍s������
	if (pEne->m_actionStep == pEne->action.size()) {
		pEne->m_move.m_velX = - MapData::WALL_SPEED;
		pEne->m_move.m_velY = 0;
		return;
	}

	
	//�J�E���g�A�b�v
	pEne->actionCount++;
	//�t���[���J�E���g�����̈ړ��J�E���g�ɒB���Ă����ꍇ
	if (pEne->actionCount ==  pEne->action[pEne->m_actionStep].frame ) {
		pEne->actionCount = 0;
		pEne->m_actionStep++;
		//�s������ɒB���Ă��邩�m�F
		if (pEne->m_actionStep != pEne->action.size()) {
			//�ړ��ʕύX
			pEne->m_move.m_velX = pEne->action[pEne->m_actionStep].x - MapData::WALL_SPEED;
			pEne->m_move.m_velY = pEne->action[pEne->m_actionStep].y;
		}
		
	}
	

}
//�R���X�g���N�^
CActionControllerOriginal2::CActionControllerOriginal2() :m_actionType(ACTION_TYPE::ORIGINAL2) {

}
void CActionControllerOriginal2::actionFunc(CEnemyCharacter* pEne) {

	pEne->shotCount++;
	//�e����
	if (pEne->shotCount % 120 == 0) {
		pEne->m_shotFlag = true;
	}
	//�A�N�V����������ɒB���Ă����ꍇ�͍s������
	if (pEne->m_actionStep == pEne->action.size()) {
		pEne->m_move.m_velX = -MapData::WALL_SPEED;
		pEne->m_move.m_velY = 0;
		return;
	}


	//�J�E���g�A�b�v
	pEne->actionCount++;
	//�t���[���J�E���g�����̈ړ��J�E���g�ɒB���Ă����ꍇ
	if (pEne->actionCount == pEne->action[pEne->m_actionStep].frame) {
		pEne->actionCount = 0;
		pEne->m_actionStep++;
		//�s������ɒB���Ă��邩�m�F
		if (pEne->m_actionStep != pEne->action.size()) {
			//�ړ��ʕύX
			pEne->m_move.m_velX = pEne->action[pEne->m_actionStep].x - MapData::WALL_SPEED;
			pEne->m_move.m_velY = pEne->action[pEne->m_actionStep].y;
		}

	}


}


//�R���X�g���N�^
CActionControllerBoss::CActionControllerBoss(){

}
void CActionControllerBoss::actionFunc(CEnemyCharacter* pEne) {

	pEne->shotCount++;
	//�e����
	if (pEne->shotCount % 120 >= 0 && pEne->shotCount % 120 <= 40 && pEne->shotCount % 4 == 0) {
		pEne->m_shotFlag = true;
	}

	//�J�E���g�A�b�v
	pEne->actionCount++;
	//�t���[���J�E���g�����̈ړ��J�E���g�ɒB���Ă����ꍇ
	if (pEne->actionCount == pEne->action[pEne->m_actionStep].frame) {
		pEne->actionCount = 0;
		pEne->m_actionStep++;
		//�A�N�V����������ɒB���Ă����ꍇ�͍ŏ��ɖ߂�
		if (pEne->m_actionStep == pEne->action.size()) {
			pEne->m_actionStep = 1;
		}
		//�s������ɒB���Ă��邩�m�F
		if (pEne->m_actionStep != pEne->action.size()) {
			//�ړ��ʕύX
			pEne->m_move.m_velX = pEne->action[pEne->m_actionStep].x;
			pEne->m_move.m_velY = pEne->action[pEne->m_actionStep].y;
		}

	}


}