#include "ActionController.h"
#include "Model/Character/Character.h"
#include "Data/MapData/MapData.h"

//コンストラクタ
CActionControllerZigZag::CActionControllerZigZag():m_actionType(ACTION_TYPE::ZIGZAG){

}
void CActionControllerZigZag::actionFunc(CEnemyCharacter* pEne) {
	//X座標が320以下になったら
	if (pEne->m_actionStep == 0 && pEne->m_move.m_posX <= 320.0f) {
		//上に移動
		pEne->m_move.m_velX = 0.0f;
		pEne->m_move.m_velY = 5.0f;
		pEne->m_shotFlag = false;
		//ステップを1にする
		pEne->m_actionStep = 1;
	}
	//Y座標が240以上になったら
	if (pEne->m_actionStep == 1 && pEne->m_move.m_posY >= 240.0f) {
		//弾を発射
		pEne->m_move.m_velX = 0.0f;
		pEne->m_move.m_velY = 5.0f;
		pEne->m_shotFlag = true;
		//ステップを2にする
		pEne->m_actionStep = 2;
	}
	//Y座標が380以上になったら
	if (pEne->m_actionStep == 2 && pEne->m_move.m_posY >= 380.0f) {
		//左に移動
		pEne->m_move.m_velX = -5.0f;
		pEne->m_move.m_velY = 0.0f;
		pEne->m_shotFlag = false;
		//ステップを3にする
		pEne->m_actionStep = 3;
	}
}

//コンストラクタ
CActionControllerStraight::CActionControllerStraight() :m_actionType(ACTION_TYPE::STRAIGHT) {

}
void CActionControllerStraight::actionFunc(CEnemyCharacter* pEne) {
	//X座標が３分の２ぐらいにきたら弾を発射
	if (pEne->m_actionStep == 0 && pEne->m_move.m_posX <= WINDOW_RIGHT * 0.6666f) {
		//上に移動
		pEne->m_move.m_velX = -5.0f;
		pEne->m_move.m_velY = 0.0f;
		pEne->m_shotFlag = true;
		//ステップを1にする
		pEne->m_actionStep = 1;
	}
	//X座標が３分の1ぐらいにきたら弾を発射
	if (pEne->m_actionStep == 1 && pEne->m_move.m_posX <= WINDOW_RIGHT * 0.3333f) {
		//弾を発射
		pEne->m_move.m_velX = -5.0f;
		pEne->m_move.m_velY = 0.0f;
		pEne->m_shotFlag = true;
		//ステップを2にする
		pEne->m_actionStep = 2;
	}
}

//コンストラクタ
CActionControllerConvex::CActionControllerConvex() :m_actionType(ACTION_TYPE::CONVEX) {

}
void CActionControllerConvex::actionFunc(CEnemyCharacter* pEne) {
	//X座標が３分の２ぐらいにきたら下に移動
	if (pEne->m_actionStep == 0 && pEne->m_move.m_posX <= WINDOW_RIGHT * 0.6666f) {
		//上に移動
		pEne->m_move.m_velX = 0.0f;
		pEne->m_move.m_velY = -5.0f;
		pEne->m_shotFlag = false;
		//ステップを1にする
		pEne->m_actionStep = 1;
	}
	//Y座標が100以下にきたら左に移動し弾を発射
	if (pEne->m_actionStep == 1 && pEne->m_move.m_posY <= 100.0) {
		//弾を発射
		pEne->m_move.m_velX = -5.0f;
		pEne->m_move.m_velY = 0.0f;
		pEne->m_shotFlag = true;
		//ステップを2にする
		pEne->m_actionStep = 2;
	}
	//X座標が３分の２ぐらいにきたら上に移動
	if (pEne->m_actionStep == 2 && pEne->m_move.m_posX <= WINDOW_RIGHT * 0.3333f) {
		//弾を発射
		pEne->m_move.m_velX = 0.0f;
		pEne->m_move.m_velY = 5.0f;
		pEne->m_shotFlag = false;
		//ステップを2にする
		pEne->m_actionStep = 3;
	}
	//Y座標が380にきたら左に移動
	if (pEne->m_actionStep == 3 && pEne->m_move.m_posY >= 380.0) {
		//弾を発射
		pEne->m_move.m_velX = -5.0f;
		pEne->m_move.m_velY = 0.0f;
		pEne->m_shotFlag = true;
		//ステップを2にする
		pEne->m_actionStep = 4;
	}
}

//コンストラクタ
CActionControllerOriginal::CActionControllerOriginal() :m_actionType(ACTION_TYPE::ORIGINAL) {

}
void CActionControllerOriginal::actionFunc(CEnemyCharacter* pEne) {
	
	pEne->shotCount++;
	//弾発射
	if (pEne->shotCount % 120 == 0 || pEne->shotCount % 120 == 5) {
		pEne->m_shotFlag = true;
	}
	//アクションが上限に達していた場合は行動無し
	if (pEne->m_actionStep == pEne->action.size()) {
		pEne->m_move.m_velX = - MapData::WALL_SPEED;
		pEne->m_move.m_velY = 0;
		return;
	}

	
	//カウントアップ
	pEne->actionCount++;
	//フレームカウントが次の移動カウントに達していた場合
	if (pEne->actionCount ==  pEne->action[pEne->m_actionStep].frame ) {
		pEne->actionCount = 0;
		pEne->m_actionStep++;
		//行動上限に達しているか確認
		if (pEne->m_actionStep != pEne->action.size()) {
			//移動量変更
			pEne->m_move.m_velX = pEne->action[pEne->m_actionStep].x - MapData::WALL_SPEED;
			pEne->m_move.m_velY = pEne->action[pEne->m_actionStep].y;
		}
		
	}
	

}
//コンストラクタ
CActionControllerOriginal2::CActionControllerOriginal2() :m_actionType(ACTION_TYPE::ORIGINAL2) {

}
void CActionControllerOriginal2::actionFunc(CEnemyCharacter* pEne) {

	pEne->shotCount++;
	//弾発射
	if (pEne->shotCount % 120 == 0) {
		pEne->m_shotFlag = true;
	}
	//アクションが上限に達していた場合は行動無し
	if (pEne->m_actionStep == pEne->action.size()) {
		pEne->m_move.m_velX = -MapData::WALL_SPEED;
		pEne->m_move.m_velY = 0;
		return;
	}


	//カウントアップ
	pEne->actionCount++;
	//フレームカウントが次の移動カウントに達していた場合
	if (pEne->actionCount == pEne->action[pEne->m_actionStep].frame) {
		pEne->actionCount = 0;
		pEne->m_actionStep++;
		//行動上限に達しているか確認
		if (pEne->m_actionStep != pEne->action.size()) {
			//移動量変更
			pEne->m_move.m_velX = pEne->action[pEne->m_actionStep].x - MapData::WALL_SPEED;
			pEne->m_move.m_velY = pEne->action[pEne->m_actionStep].y;
		}

	}


}


//コンストラクタ
CActionControllerBoss::CActionControllerBoss(){

}
void CActionControllerBoss::actionFunc(CEnemyCharacter* pEne) {

	pEne->shotCount++;
	//弾発射
	if (pEne->shotCount % 120 >= 0 && pEne->shotCount % 120 <= 40 && pEne->shotCount % 4 == 0) {
		pEne->m_shotFlag = true;
	}

	//カウントアップ
	pEne->actionCount++;
	//フレームカウントが次の移動カウントに達していた場合
	if (pEne->actionCount == pEne->action[pEne->m_actionStep].frame) {
		pEne->actionCount = 0;
		pEne->m_actionStep++;
		//アクションが上限に達していた場合は最初に戻す
		if (pEne->m_actionStep == pEne->action.size()) {
			pEne->m_actionStep = 1;
		}
		//行動上限に達しているか確認
		if (pEne->m_actionStep != pEne->action.size()) {
			//移動量変更
			pEne->m_move.m_velX = pEne->action[pEne->m_actionStep].x;
			pEne->m_move.m_velY = pEne->action[pEne->m_actionStep].y;
		}

	}


}