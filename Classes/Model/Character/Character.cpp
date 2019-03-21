
#include "Character.h"
#include "Lib/InputManager/InputManager.h"
#include "Lib/InputManager/InputJoystick.h"
#include "Scene/GameMain/GameMain.h"
#include <math.h>

//=========================================================================
//	プレイヤーキャラクタークラスのメンバ関数の定義はここから書く
//=========================================================================
// コンストラクタ
CPlayerCharacter::CPlayerCharacter() {
}



// デストラクタ
CPlayerCharacter::~CPlayerCharacter() {
}

/**
 *	@desc	初期化処理
 */
bool CPlayerCharacter::init() {

	// cocos2d のクラスを継承したらコンストラクタで
	// スーパークラスの init 関数を処理しなければならないので注意
	if ( Sprite::init() == false ) {
		CCLOG( "CPlayerCharacter() Sprite::init is false !!!" ) ;
		return false ;
	}
	
	//=========================================================================
	//
	//	ここから初期化、初期設定のコードを追加
	//
	//=========================================================================
	
	//画像の設定
	//this->setTexture(IMAGE_FILE_CHARACTER);
	this->setTexture(IMAGE_FILE_CHARACTER_2);
	//切り取る矩形
	//this->m_chip.setRect(0,0,48,32);
	this->m_chip.setRect(0, 0, 48, 20);
	//切り取る矩形の設定
	this->setTextureRect(this->m_chip);
	//初期位置の設定
	this->setPosition(320,240);
	this->m_move.setPos(320, 240);
	this->m_move.setVel(0,0);
	//アニメーションデータの初期化
	this->m_anime.set(20,3);

	//弾発射用カウンターの初期化
	this->m_shotCounter = 0;

	//弾発射間隔の初期化(1秒間に3発発射できる設定)
	this->m_shotInterval = 5;

	//弾攻撃力
	this->m_shotPower = 1;

	//弾パラメータ
	this->m_shotParam = 0;

	//衝突用データの初期化
	this->m_body.set(-15,10,15,-10);

	//ステータスの初期化
	//プレイヤーのスコアはトータルスコアとして扱う
	//this->m_status.set(20,20,1,0,2);
	//プレイヤーステータス初期化
	this->m_status.set(
		CGameMain::m_hp,
		CGameMain::m_maxHp,
		CGameMain::m_attackPt,
		CGameMain::m_score,
		CGameMain::m_speed
	);


	//有効フラグの初期化
	this->m_activeFlag = true;

	//=========================================================================
	//
	//	ここまでに初期化、初期設定のコードを追加
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
	//右端
	if (this->m_move.m_posX + 15 > WINDOW_RIGHT) {
		//プレイヤーの右端がウィンドウ幅を飛び出した(画面の右端に到達した)

		//飛び出した分を計算(プレイヤーの右端　‐　ウィンドウ幅)
		float boundary = (this->m_move.m_posX + 15) - WINDOW_RIGHT;

		//現在の位置から飛び出した分を引いた位置を計算
		this->m_move.m_posX = this->m_move.m_posX - boundary;
	}
	//左端
	if (this->m_move.m_posX - 15 < WINDOW_LEFT) {
		//プレイヤーの右端がウィンドウ幅を飛び出した(画面の右端に到達した)

		//飛び出した分を計算(プレイヤーの右端　‐　ウィンドウ幅)
		float boundary = (this->m_move.m_posX - 15) - WINDOW_LEFT;

		//現在の位置から飛び出した分を引いた位置を計算
		this->m_move.m_posX = this->m_move.m_posX - boundary;
	}
	//上端
	if (this->m_move.m_posY + 10 > WINDOW_TOP) {
		//プレイヤーの右端がウィンドウ幅を飛び出した(画面の右端に到達した)

		//飛び出した分を計算(プレイヤーの右端　‐　ウィンドウ幅)
		float boundary = (this->m_move.m_posY + 10) - WINDOW_TOP;

		//現在の位置から飛び出した分を引いた位置を計算
		this->m_move.m_posY = this->m_move.m_posY - boundary;
	}
	//下端
	if (this->m_move.m_posY - 10 < WINDOW_BOTTOM) {
		//プレイヤーの右端がウィンドウ幅を飛び出した(画面の右端に到達した)

		//飛び出した分を計算(プレイヤーの右端　‐　ウィンドウ幅)
		float boundary = (this->m_move.m_posY - 10) - WINDOW_BOTTOM;

		//現在の位置から飛び出した分を引いた位置を計算
		this->m_move.m_posY = this->m_move.m_posY - boundary;
	}
}
void CPlayerCharacter::animationFunc() {
	if (m_activeFlag == false)
		return;
	//アニメーションの更新を行う
	int frame = this->m_anime.update();
	//フレーム数から表示するべきチップデータを計算する
	this->m_chip.setRect(this->m_chip.size.width * frame,0, this->m_chip.size.width, this->m_chip.size.height);
	
}


/**
*@desc プレイヤーの弾を発射
*@param 弾タイプ
*@param 修正位置X
*@param 修正位置Y
*@param 速度X
*@param 速度Y
*/
CBullet* CPlayerCharacter::shotBullet(BULLET_TYPE type,float fixX,float fixY,float velX,float velY) {
	if (this->m_activeFlag == false)
		return NULL;
	
	//プレイヤーの弾の生成
	CBullet* pBul = CBullet::create();
	//画像の設定
	pBul->setTexture(IMAGE_FILE_BULLET);
	//切り取る矩形
	switch (type) {
		case BULLET_TYPE::PLAYER_INDUCTION:
		pBul->m_chip = CChip(0, 18, 8, 8);
		break;
	default:
		pBul->m_chip = CChip(0, 2, 8, 8);
		break;
	}
	
	pBul->setTextureRect(pBul->m_chip);
	//移動データに初期位置の設定
	pBul->m_move.setPos(this->m_move.m_posX + fixX, this->m_move.m_posY + fixY);
	//移動データに初期速度の設定(x座標に+2ずつ)；
	pBul->m_move.setVel(velX, velY);
	//初期位置を判定
	pBul->setPosition(pBul->m_move.m_posX, pBul->m_move.m_posY);
	
	//有効フラグにtrueを入れる
	pBul->m_activeFlag = true;

	//弾タイプの設定
	pBul->m_bulletType = type;

	//アニメーションデータの初期化
	pBul->m_anime.set(10,4);

	//衝突判定用データの初期化
	pBul->m_body.set(-4, 4, 4, -4);

	return pBul;
}
//=========================================================================
//	バレット ( 弾 ) のクラスのメンバ関数の定義はここから書く
//=========================================================================
//コンストラクタ
CBullet::CBullet() {
}
CBullet::~CBullet() {
}
/**
*@desc 初期化処理
*/
bool CBullet::init() {
	//cocos2dのクラスを継承したらコンストラクタで
	//スーパークラスのinit関数を処理しなければならないので注意
	if (Sprite::init() == false) {
		CCLOG("CBullet() Sprite::init is fales !!");
		return false;
	}

	//初期化ここから
	//アニメーションデータの初期化
	this->m_anime.set(20, 4);

	//this->setScale(5.0f);
	
	//初期化ここまで
	return true;
}

void CBullet::moveFunc() {
	if (this->m_activeFlag == false)
		return;

	//弾道計算
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
			//ターゲットが無い場合
			mode = true;
			this->distance = 1000000.0f;
			
		}
		if (mode) {
			target = -1;
			//索敵
			//敵は配列なので敵の１つ１つと衝突判定を取る
			for (int i = 0; i <= CGameMain::m_pEnemyCount; i++) {
				//要素がNULLなら飛ばす
				if (CGameMain::m_pEnemyCharas[i] == NULL)
					continue;

				//有効フラグがfalseのインスタンスも飛ばす
				if (CGameMain::m_pEnemyCharas[i]->m_activeFlag == false)
					continue;

				//敵キャラと弾の距離を計算
				float distanceX = m_move.m_posX - CGameMain::m_pEnemyCharas[i]->m_move.m_posX;
				float distanceY = m_move.m_posY - CGameMain::m_pEnemyCharas[i]->m_move.m_posY;
				float distance = sqrt(distanceX * distanceX + distanceY * distanceY);
				if (distance <= this->distance) {
					//ターゲットの登録
					target = i;
					this->distance = distance;
					mode = false;
					
					continue;
				}
					
			}
			
		}
		if (!mode && target != -1) {
			//弾の移動計算
			//ターゲットと弾の角度を計算 
			float rot = atan2f(CGameMain::m_pEnemyCharas[target]->m_move.m_posY - this->m_move.m_posY,
				CGameMain::m_pEnemyCharas[target]->m_move.m_posX - this->m_move.m_posX) *
				180.0f / M_PI;
			
			//ターゲットと弾の角度
			float rot2 = this->rotation - rot;
			
			//10 - 20 = -10 マイナスの場合+に移動
			//20 - 10 = 10 プラスの場合-に移動
			//10 - 350 = -340  - 340 + 360 = 20 180度を越えた場合は360から引いた数にする
			//350 - 10 = 340   340 - 360 = -20 180度を越えた場合は数から360を引いた数にする

			if (rot2 <= -180) {
				rot2 += 360;
			}
			if (rot2 >= 180) {
				rot2 -= 360;
			}

			if (rot2 >=0) {
				//角度をマイナス
				if (rot2 >= this->param) {
					this->rotation -= this->param;
				}
				else {
					//角度を敵の角度に合わせる
					this->rotation = rot;
				}
				
			}
			else {
				//角度をプラス
				if (rot2 <= this->param) {
					this->rotation += this->param;
				}
				else {
					//角度を敵の角度に合わせる
					this->rotation = rot;
				}
			}

			//角度オーバー修正
			if (this->rotation < 0) {
				this->rotation += 360;
			}
			if (this->rotation > 360) {
				this->rotation -= 360;
			}

			//X座標の移動量
			//角度分二次ベクトルを取得
			float velX = cos(this->rotation * M_PI / 180.0f) * this->vel;
			
			//Y座標の移動量
			float velY = sin(this->rotation * M_PI / 180.0f) * this->vel;

			//移動距離をセット
			this->m_move.setVel(velX,velY);
		}
		//回転処理
		setRotation(-this->rotation);

		//移動処理
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

	//弾画像の左端の座標が画面右端の座標より大きくなったら
	if (this->m_move.m_posX - this->m_chip.size.width * 0.5f > WINDOW_RIGHT + 50) {
		//有効フラグを下げる
		this->m_activeFlag = false;
	}
	//弾画像の右端の座標が画面右端の座標より大きくなったら
	if (this->m_move.m_posX + this->m_chip.size.width * 0.5f < WINDOW_LEFT - 50) {
		//有効フラグを下げる
		this->m_activeFlag = false;
	}
	//弾画像の上端の座標が画面右端の座標より大きくなったら
	if (this->m_move.m_posY - this->m_chip.size.height * 0.5f > WINDOW_TOP + 50) {
		//有効フラグを下げる
		this->m_activeFlag = false;
	}
	//弾画像の右端の座標が画面右端の座標より大きくなったら
	if (this->m_move.m_posY + this->m_chip.size.height * 0.5f < WINDOW_BOTTOM - 50) {
		//有効フラグを下げる
		this->m_activeFlag = false;
	}
}

void CBullet::animationFunc() {
	if (this->m_activeFlag == false)
		return;
	
	//自滅フラグ有効の場合
	if (this->m_delflg == true) {
		//特定フレームで有効フラグ下げる
		if(this->m_count == this->m_maxCount) {
			this->m_activeFlag = false;
		}
		else {
			m_count++;
		}
	} 

	//アニメーションの更新を行う
	int frame = this->m_anime.update();
	//フレーム数から表示するべきチップデータを計算する
	this->m_chip.setRect(
		this->m_chip.size.width * frame,
		this->m_chip.origin.y,
		this->m_chip.size.width,
		this->m_chip.size.height);
}

//=========================================================================
//	敵のクラスのメンバ関数の定義はここから書く
//=========================================================================
CEnemyCharacter::CEnemyCharacter() {

}
CEnemyCharacter::~CEnemyCharacter() {

}
bool CEnemyCharacter::init() {
	//cocos2dのクラスを継承したらコンストラクタで
	//スーパークラスのinit関数を処理しなければならないので注意
	if (Sprite::init() == false) {
		CCLOG("CEnemyCharacter() Sprite::init is false!!");
		return false;
	}
	//===========================================
	//ここから帰化、初期設定のコードを追加
	//===========================================


	//===========================================
	//ここまでに初期化、初期っ設定を追加
	//===========================================
	return true;
}

//移動に関するメンバ関数宣言
void CEnemyCharacter::moveFunc() {
	if (this->m_activeFlag == false)
		return;

	//移動処理
	this->m_move.moveByVell();

	//ターゲットと弾の角度を計算 
	if (e_enemyType == ENEMY_TYPE::TYPE_C) {
		float rot = atan2f(CGameMain::m_pPlayerChara->m_move.m_posY - this->m_move.m_posY,
			CGameMain::m_pPlayerChara->m_move.m_posX - this->m_move.m_posX) *
			180.0f / M_PI;

		this->rotation = rot + this->getRotation();

		//回転処理
		m_pChr->setRotation(-this->rotation);
	}
	
}

//アニメーションに関するメンバ関数宣言
void CEnemyCharacter::animationFunc() {
	if (this->m_activeFlag == false)
		return;

	//アニメーションの更新を行う
	int frame = this->m_anime.update();
	//フレーム数から表示するべきチップデータを計算する
	this->m_chip.setRect(
	this->m_chip.size.width * frame,
	this->m_chip.origin.y,
	this->m_chip.size.width,
	this->m_chip.size.height
	);
	
}

//画面端に関するメンバ関数宣言
void CEnemyCharacter::endOfScreen() {
	if (this->m_activeFlag == false)
		return;
	
	//弾画像の左端の座標が画面右端の座標より小さくなったら
	if (this->m_move.m_posX + this->m_chip.size.width * 0.5f < WINDOW_LEFT - 40) {
		//有効フラグを下げる
		this->m_activeFlag = false;
	}
	//弾画像の右端の座標が画面左端の座標より大きくなったら
	if (this->m_move.m_posX - this->m_chip.size.width * 0.5f > WINDOW_RIGHT + 40) {
		//有効フラグを下げる
		this->m_activeFlag = false;
	}
	//弾画像の上端の座標が画面下端の座標より小さくなったら
	if (this->m_move.m_posY + this->m_chip.size.height * 0.5f < WINDOW_BOTTOM - 40) {
		//有効フラグを下げる
		this->m_activeFlag = false;
	}
	//弾画像の右端の座標が画面左端の座標より小さくなったら
	if (this->m_move.m_posY - this->m_chip.size.height * 0.5f > WINDOW_TOP + 40) {
		//有効フラグを下げる
		this->m_activeFlag = false;
	}
}

/**
*@desc 敵の弾を生成
*@param 弾タイプ
*@param 修正値X
*@param 修正値Y
*@param 速度X
*@param 速度Y
*/
CBullet* CEnemyCharacter::shotBullet(BULLET_TYPE type, float fixX, float fixY, float velX, float velY) {
	if (this->m_activeFlag == false)
		return NULL;

	//プレイヤーの弾の生成
	CBullet* pBul = CBullet::create();
	//画像の設定
	pBul->setTexture(IMAGE_FILE_BULLET);
	//切り取る矩形
	pBul->m_chip = CChip(0, 10, 8, 8);
	pBul->setTextureRect(pBul->m_chip);

	//移動データに初期位置の設定
	pBul->m_move.setPos(this->m_move.m_posX + fixX, this->m_move.m_posY + fixY);
	//移動データに初期速度の設定(x座標に+2ずつ)；
	pBul->m_move.setVel(velX, velY);

	//アニメーションデータの初期化
	pBul->m_anime.set(5,4);
	//衝突判定用データの初期化
	pBul->m_body.set(-4,4,4,-4);

	//有効フラグにtrueを入れる
	pBul->m_activeFlag = true;

	//弾タイプの設定
	pBul->m_bulletType = type;
	return pBul;
}

//値の反映に関するメンバ関数宣言
void CEnemyCharacter::applyFunc() {
	if (this->m_activeFlag == false)
		return;

	this->setPosition(this->m_move.m_posX, this->m_move.m_posY);
	this->setTextureRect(this->m_chip);
}


//=========================================================================
//	エフェクトのクラスのメンバ関数の定義はここから書く
//=========================================================================

CEfect::CEfect() {

}
CEfect::~CEfect() {

}
bool CEfect::init() {
	//cocos2dのクラスを継承したらコンストラクタで
	//スーパークラスのinit関数を処理しなければならないので注意
	if (Sprite::init() == false) {
		CCLOG("CEnemyCharacter() Sprite::init is false!!");
		return false;
	}
	//===========================================
	//ここから帰化、初期設定のコードを追加
	//===========================================


	//===========================================
	//ここまでに初期化、初期っ設定を追加
	//===========================================
	return true;
}

//移動に関するメンバ関数宣言
void CEfect::moveFunc() {
	if (this->m_activeFlag == false)
		return;

	//移動処理
	this->m_move.moveByVell();
}

//アニメーションに関するメンバ関数宣言
void CEfect::animationFunc() {
	//アニメーション終了で有効フラグ下げる
	if (this->m_anime.m_isEnd == true) {
		this->m_activeFlag = false;
	}

	if (this->m_activeFlag == false) {
		return;
	}
	this->getParent();
	
	//アニメーションの更新を行う
	int frame = this->m_anime.update();
	//フレーム数から表示するべきチップデータを計算する
	this->m_chip.setRect(
		this->m_chip.size.width * (frame % maxX),
		this->m_chip.size.height * (frame / maxX),
		this->m_chip.size.width,
		this->m_chip.size.height
	);

}


//値の反映に関するメンバ関数宣言
void CEfect::applyFunc() {
	if (this->m_activeFlag == false)
		return;

	this->setPosition(this->m_move.m_posX, this->m_move.m_posY);
	this->setTextureRect(this->m_chip);
}

void CEfect::endOfScreen() {
	if (this->m_activeFlag == false)
		return;

	//弾画像の左端の座標が画面右端の座標より大きくなったら
	if (this->m_move.m_posX - this->m_chip.size.width * 0.5f > WINDOW_RIGHT + 200.0f) {
		//有効フラグを下げる
		this->m_activeFlag = false;
	}
	//弾画像の右端の座標が画面右端の座標より大きくなったら
	if (this->m_move.m_posX + this->m_chip.size.width * 0.5f < WINDOW_LEFT - 200.0f) {
		//有効フラグを下げる
		this->m_activeFlag = false;
	}
	//弾画像の上端の座標が画面右端の座標より大きくなったら
	if (this->m_move.m_posY - this->m_chip.size.height * 0.5f > WINDOW_TOP + 200.0f) {
		//有効フラグを下げる
		this->m_activeFlag = false;
	}
	//弾画像の右端の座標が画面右端の座標より大きくなったら
	if (this->m_move.m_posY + this->m_chip.size.height * 0.5f < WINDOW_BOTTOM - 200.0f) {
		//有効フラグを下げる
		this->m_activeFlag = false;
	}
}


/**
*@desc 相手の攻撃が自身にあたった
*@param 衝突してきた相手のステータスのアドレス
*/
void CPlayerCharacter::hits(CStatus* pStatus) {
	//HPを減少させる
	this->m_status.decreaseHp(pStatus->getAttackPt());

	//HPが0以下だった場合有効フラグを下げる
	if (this->m_status.getHp() <= 0) {
		this->m_activeFlag = false;
	}
}

/**
*@desc 相手の攻撃が自身にあたった
*@param 衝突してきた相手のステータスのアドレス
*/
void CEnemyCharacter::hits(CStatus* pStatus) {
	//HPを減少させる
	this->m_status.decreaseHp(pStatus->getAttackPt());

	//HPが0以下だった場合有効フラグを下げる
	if (this->m_status.getHp() <= 0) {
		this->m_activeFlag = false;
	}
}

//行動に関するメンバ関数の宣言
void CEnemyCharacter::actionFunc() {
	

}

//=========================================================================
//	アイテムのクラスのメンバ関数の定義はここから書く
//=========================================================================

CItem::CItem() {

}
CItem::~CItem() {

}
bool CItem::init() {
	//cocos2dのクラスを継承したらコンストラクタで
	//スーパークラスのinit関数を処理しなければならないので注意
	if (Sprite::init() == false) {
		CCLOG("CItem() Sprite::init is false!!");
		return false;
	}
	//===========================================
	//ここから帰化、初期設定のコードを追加
	//===========================================


	//===========================================
	//ここまでに初期化、初期っ設定を追加
	//===========================================
	return true;
}

//移動に関するメンバ関数宣言
void CItem::moveFunc() {
	if (this->m_activeFlag == false)
		return;

	//移動処理
	this->m_move.moveByVell();
}

//アニメーションに関するメンバ関数宣言
void CItem::animationFunc() {

	if (this->m_activeFlag == false)
		return;

	//アニメーションの更新を行う
	int frame = this->m_anime.update();
	//フレーム数から表示するべきチップデータを計算する
	this->m_chip.setRect(
		this->m_chip.size.width * frame,
		this->m_chip.origin.y,
		this->m_chip.size.width,
		this->m_chip.size.height
	);

	//アイテムタイプ切り替え
	//this->type = (ITEM_TYPE)frame;
}


//値の反映に関するメンバ関数宣言
void CItem::applyFunc() {
	if (this->m_activeFlag == false)
		return;

	this->setPosition(this->m_move.m_posX, this->m_move.m_posY);
	this->setTextureRect(this->m_chip);
}
/**
*@desc 相手の攻撃が自身にあたった
*@param 衝突してきた相手のステータスのアドレス
*/
void CItem::hits(CStatus* pStatus) {
	//アイテム取得処理
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
	
	//有効フラグを下げる
	this->m_activeFlag = false;
}
void CItem::endOfScreen() {
	if (this->m_activeFlag == false)
		return;

	//弾画像の左端の座標が画面右端の座標より大きくなったら
	if (this->m_move.m_posX - this->m_chip.size.width * 0.5f > WINDOW_RIGHT) {
		//有効フラグを下げる
		this->m_activeFlag = false;
	}
	//弾画像の右端の座標が画面右端の座標より大きくなったら
	if (this->m_move.m_posX + this->m_chip.size.width * 0.5f < WINDOW_LEFT) {
		//有効フラグを下げる
		this->m_activeFlag = false;
	}
	//弾画像の上端の座標が画面右端の座標より大きくなったら
	if (this->m_move.m_posY - this->m_chip.size.height * 0.5f > WINDOW_TOP) {
		//有効フラグを下げる
		this->m_activeFlag = false;
	}
	//弾画像の右端の座標が画面右端の座標より大きくなったら
	if (this->m_move.m_posY + this->m_chip.size.height * 0.5f < WINDOW_BOTTOM) {
		//有効フラグを下げる
		this->m_activeFlag = false;
	}
}

cocos2d::Label** CItem::pweponLevelLavel;

//=========================================================================
//	カーソルのクラスのメンバ関数の定義はここから書く
//=========================================================================

CCursor::CCursor() {

}
CCursor::~CCursor() {

}
bool CCursor::init() {
	//cocos2dのクラスを継承したらコンストラクタで
	//スーパークラスのinit関数を処理しなければならないので注意
	if (Sprite::init() == false) {
		CCLOG("CItem() Sprite::init is false!!");
		return false;
	}
	//===========================================
	//ここから帰化、初期設定のコードを追加
	//===========================================

	

	//===========================================
	//ここまでに初期化、初期っ設定を追加
	//===========================================
	return true;
}

//移動に関するメンバ関数宣言
void CCursor::moveFunc() {
	//移動処理
	this->m_move.moveByVell();
}

//アニメーションに関するメンバ関数宣言
void CCursor::animationFunc() {

	//アニメーションの更新を行う
	int frame = this->m_anime.update();
	//フレーム数から表示するべきチップデータを計算する
	this->m_chip.setRect(
		this->m_chip.size.width * frame,
		this->m_chip.origin.y,
		this->m_chip.size.width,
		this->m_chip.size.height
	);

}


//値の反映に関するメンバ関数宣言
void CCursor::applyFunc() {
	
	this->setPosition(this->m_move.m_posX, this->m_move.m_posY);
	this->setTextureRect(this->m_chip);
}

/*
*@desc カーソル初期設定
*@param カーソルのX最大
*@param カーソルのY最大
*@param カーソルのX位置
*@param カーソルのY位置
*@param カーソルのX座標
*@param カーソルのY座標
*@param X移動サイズ
*@param Y移動サイズ
*@param X移動フレーム
*@param Y移動フレーム
*@param 横ループ
*@param 縦ループ
*@param 低速待ちフレーム
*@param 低速待ちフレーム
*/
void CCursor::set(
	char* p_fileName,//ファイル名
	int p_chipPointX,//チップX座標
	int p_chipPointY,//チップY座標
	int p_chipX,	//チップXサイズ
	int p_chipY,	//チップYサイズ
	int p_animation,//アニメーション数
	int p_animeFrame,//アニメーションフレーム数
	int p_maxX,		//カーソルのX最大
	int p_maxY,		//カーソルのY最大
	int p_x,		//カーソルのX位置
	int p_y,		//カーソルのY位置
	float p_xPoint,	//カーソルのX座標
	float p_yPoint,	//カーソルのY座標
	float p_moveX,	//X移動サイズ
	float p_moveY,	//Y移動サイズ
	int p_moveFrame,//移動フレーム
	bool p_xLoop,	//横ループ
	bool p_yLoop,	//縦ループ
	int p_slowWait,	//低速待ちフレーム
	int p_fastWait	//高速待ちフレーム
) {
	//画像の設定
	this->setTexture(p_fileName);
	//切り取る矩形
	this->m_chip.setRect(p_chipPointX, p_chipPointY, p_chipX, p_chipY);
	//切り取る矩形の設定
	this->setTextureRect(this->m_chip);
	//アニメーション数設定
	this->p_animation = p_animation;
	//アニメーションフレーム数設定
	this->p_animeFrame = p_animeFrame;
	//カーソルの最大値設定
	this->p_maxX = p_maxX;
	this->p_maxY = p_maxY;
	//カーソル位置設定
	this->p_x = p_x;
	this->p_y = p_y;
	//カーソルの座標設定
	this->p_xPoint = p_xPoint;
	this->p_yPoint = p_yPoint;
	//移動サイズ設定
	this->p_moveX = p_moveX;
	this->p_moveY = p_moveY;
	//移動フレーム設定
	this->p_moveFrame = p_moveFrame;
	//ループ設定
	this->p_xLoop = p_xLoop;
	this->p_yLoop = p_yLoop;
	//待ちフレーム設定
	this->p_fastWait = p_fastWait;
	this->p_slowWait = p_slowWait;

	//初期位置の設定
	this->setPosition(p_xPoint + p_x * p_moveX, p_yPoint + p_y * p_moveY);
	this->m_move.setPos(p_xPoint + p_x * p_moveX, p_yPoint + p_y * p_moveY);
	this->m_move.setVel(0, 0);
	//アニメーションデータの初期化
	this->m_anime.set(p_animeFrame, p_animation);
}

void CCursor::inputFunc() {

	//入力フラグ設定
	CInputJoystick::inputFunc(1);

	//入力待ち
	if (this->p_input == 0) {
		//移動終了フラグチェック
		if (moveflg)
			moveflg = false;


		if (CInputJoystick::m_right || CInputJoystick::m_left || CInputJoystick::m_up || CInputJoystick::m_down) {
			OutputDebugString(L"カーソル入力検知\n");

			//カーソルキーが押されたら入力検知に変更
			this->p_input = 1;
			//フレームカウントリセット
			this->p_countFrame = 0;
			//初回入力待ち時間
			if (this->p_fastPush) {
				this->p_fastPush = false;
				OutputDebugString(L"初回入力\n");
				//待ち時間を初回入力待ち時間に設定
				this->p_wait = this->p_inputWait;
			}
			else {
				OutputDebugString(L"初回以降入力\n");
				//待ち時間を初回以降入力待ち時間に設定
				if (this->p_speed) {
					OutputDebugString(L"低速\n");
					//低速
					this->p_wait = this->p_slowWait;
					//高速に変更
					this->p_speed = false;
				}
				else {
					OutputDebugString(L"高速\n");
					//高速
					this->p_wait = this->p_fastWait;
				}
			}
		}
		else {
			//押されてなければ処理抜け
			//初回入力に変更
			this->p_fastPush = true;
			//低速に変更
			this->p_speed = true;
			return;
		}
	}



	//入力検知待ち
	if (this->p_input == 1)
	{
		if (!CInputJoystick::m_right && !CInputJoystick::m_left && !CInputJoystick::m_up && !CInputJoystick::m_down) {
			//キーボードがすべて離されたら
			//入力待ちに変更
			this->p_input = 0;
			//初回入力に戻す
			this->p_fastPush = true;
			//低速に戻す
			this->p_speed = true;
			return;
		}
		//カウントが待ち時間に達し無い場合処理抜け
		if (this->p_countFrame < this->p_wait) {
			//フレームカウントアップ
			this->p_countFrame++;
			return;
		}
		//移動中に変更
		this->p_input = 2;
		//フレームカウントリセット
		this->p_countFrame = 0;
		//移動前カーソル位置記録
		this->p_beforeX = this->p_x;
		this->p_beforeY = this->p_y;
		
		//キー入力
		if (CInputJoystick::m_right == true)
		{
			//右矢印が押された
			this->p_x++;
		} else if (CInputJoystick::m_left == true)
		{
			//右矢印が押された
			this->p_x--;
		}

		if (CInputJoystick::m_up == true)
		{
			//上矢印が押された
			this->p_y++;
		} else if (CInputJoystick::m_down == true)
		{
			//下矢印が押された
			this->p_y--;
		}

		//カーソルオーバー修正
		//横オーバー
		if (this->p_x < 0) {
			OutputDebugString(L"横←オーバー\n");
			//ループかどうかで設定を分岐
			this->p_xLoop ? this->p_x = this->p_maxX : this->p_x = 0;
		}
		else if (this->p_x > this->p_maxX) {
			OutputDebugString(L"横→オーバー\n");
			//ループかどうかで設定を分岐
			this->p_xLoop ? this->p_x = 0 : this->p_x = this->p_maxX;
		}
		//縦オーバー
		if (this->p_y < 0) {
			OutputDebugString(L"縦↓オーバー\n");
			//ループかどうかで設定を分岐
			this->p_yLoop ? this->p_y = this->p_maxY : this->p_y = 0;
		}
		else if (this->p_y > this->p_maxY) {
			OutputDebugString(L"縦↑オーバー\n");
			//ループかどうかで設定を分岐
			this->p_yLoop ? this->p_y = 0 : this->p_y = this->p_maxY;
		}
		//移動なしの場合は入力待ちにする
		if (this->p_beforeX == this->p_x && this->p_beforeY == this->p_y) {
			//入力待ちに変更
			//this->p_input == 0;
			//低速に戻す
			//this->p_speed = true;
			return;
		}
		//入力待ちに変更
		this->p_input = 2;
		//フレームカウントリセット
		this->p_countFrame = 0;
		//移動カウントリセット
		this->p_moveCount = 0;
		//移動量を設定
		this->m_move.m_velX = (this->p_x - this->p_beforeX) * this->p_moveX / (float)this->p_moveFrame;
		this->m_move.m_velY = (this->p_y - this->p_beforeY) * this->p_moveY / (float)this->p_moveFrame;

		//カーソルSE
		int seid = AudioEngine::play2d(SOUND_FILE_CURSOR_1);
		AudioEngine::setVolume(seid, SE_VOLUME / 100.0f);
	}

	//移動中
	if (this->p_input == 2) {

		//移動カウントアップ
		this->p_countFrame++;
		//移動アニメーション終了確認
		if (this->p_countFrame < this->p_moveFrame) {
			return;
		}

		//入力検知に変更
		this->p_input = 0;
		//移動量を0に
		this->m_move.m_velX = 0;
		this->m_move.m_velY = 0;

		//座標をぴったり合わせる
		this->m_move.setPos(
			this->p_xPoint + this->p_x * this->p_moveX,
			this->p_yPoint + this->p_y * this->p_moveY
		);

		//移動終了フラグ有効
		moveflg = true;
	}

}

//=========================================================================
//	壁のクラスのメンバ関数の定義はここから書く
//=========================================================================

CWall::CWall() {

}
CWall::~CWall() {

}
bool CWall::init() {
	//cocos2dのクラスを継承したらコンストラクタで
	//スーパークラスのinit関数を処理しなければならないので注意
	if (Sprite::init() == false) {
		CCLOG("CWall() Sprite::init is false!!");
		return false;
	}
	//===========================================
	//ここから帰化、初期設定のコードを追加
	//===========================================


	//===========================================
	//ここまでに初期化、初期っ設定を追加
	//===========================================
	return true;
}

//移動に関するメンバ関数宣言
void CWall::moveFunc() {
	if (this->m_activeFlag == false)
		return;

	//移動処理
	this->m_move.moveByVell();
}

//アニメーションに関するメンバ関数宣言
void CWall::animationFunc() {

	if (this->m_activeFlag == false)
		return;

	//アニメーションの更新を行う
	int frame = this->m_anime.update();
	//フレーム数から表示するべきチップデータを計算する
	this->m_chip.setRect(
		this->m_chip.size.width * frame,
		this->m_chip.origin.y,
		this->m_chip.size.width,
		this->m_chip.size.height
	);

	//アイテムタイプ切り替え
	//this->type = (ITEM_TYPE)frame;
}


//値の反映に関するメンバ関数宣言
void CWall::applyFunc() {
	if (this->m_activeFlag == false)
		return;

	this->setPosition(this->m_move.m_posX, this->m_move.m_posY);
	this->setTextureRect(this->m_chip);
}
/**
*@desc 相手の攻撃が自身にあたった
*@param 衝突してきた相手のステータスのアドレス
*/
void CWall::hits(CStatus* pStatus) {
	
}
void CWall::endOfScreen() {
	if (this->m_activeFlag == false)
		return;

	//弾画像の左端の座標が画面右端の座標より大きくなったら
	if (this->m_move.m_posX - this->m_chip.size.width * 0.5f > WINDOW_RIGHT) {
		//有効フラグを下げる
		this->m_activeFlag = false;
	}
	//弾画像の右端の座標が画面右端の座標より大きくなったら
	if (this->m_move.m_posX + this->m_chip.size.width * 0.5f < WINDOW_LEFT) {
		//有効フラグを下げる
		this->m_activeFlag = false;
	}
	//弾画像の上端の座標が画面右端の座標より大きくなったら
	if (this->m_move.m_posY - this->m_chip.size.height * 0.5f > WINDOW_TOP) {
		//有効フラグを下げる
		this->m_activeFlag = false;
	}
	//弾画像の右端の座標が画面右端の座標より大きくなったら
	if (this->m_move.m_posY + this->m_chip.size.height * 0.5f < WINDOW_BOTTOM) {
		//有効フラグを下げる
		this->m_activeFlag = false;
	}
}
