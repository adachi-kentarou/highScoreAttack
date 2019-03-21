//
//  Constants_h
//  ShootingGame
//
//  Created by vantan-303-t on 2014/11/20.
//
//	�ėp�E�萔��`�t�@�C��
//

#ifndef ShootingGame_Constants_h
#define ShootingGame_Constants_h


//=========================================================================
//	�ėp�I�Ɏg����C���N���[�h�͂������珑��
//=========================================================================

#include "cocos2d.h"
//#include "Lib/InputManager/InputManager.h"


//=========================================================================
//	�萔��}�N���͂������珑��
//=========================================================================

// ���������
#define SAFE_DELETE( p_ ) if ( p_ ) { delete p_ ; p_ = NULL ; }
// �z�񃁃������
#define SAFE_DELETE_ARRAY( p_ ) if ( p_ ) { delete [] p_ ; p_ = NULL ; }





// CGameMain �̃^�O
#define TAG_GAME_MAIN (1000)


// ���ݎ��t����Ă��郌�C���[�̎擾
#define getCurrentLayer( tag_ ) cocos2d::Director::getInstance()->getRunningScene()->getChildByTag( tag_ )




// �E�B���h�E�T�C�Y
#define WINDOW_LEFT			(0)
#define WINDOW_TOP			(480)
#define WINDOW_RIGHT		(640)
#define WINDOW_BOTTOM		(0)

#define CLEAR_FRAME			(13600)
#define DEMO_FRAME			(3000)

//=========================================================================
//	�摜�t�@�C���̃}�N���͂������珑��
//=========================================================================

// �w�i
#define IMAGE_FILE_NAME_BG			"Images/bg.png"
#define IMAGE_FILE_CHARACTER		"Images/hStgChrTest.png"
#define IMAGE_FILE_BULLET			"Images/bullet.png"
#define IMAGE_FILE_EXPLOSION		"Images/explosion.png"
#define IMAGE_FILE_EXPLOSION_2		"Images/explosion2.png"
#define IMAGE_FILE_BACKGROUND		"Images/background.png"
#define IMAGE_FILE_CHARACTER_2		"Images/char.png"
#define IMAGE_FILE_BOSS_1			"Images/boss1.png"
#define IMAGE_FILE_PLANET_1			"Images/planet1.png"
#define IMAGE_FILE_PLANET_2			"Images/planet2.png"
#define IMAGE_FILE_PLANET_3			"Images/planet3.png"
#define IMAGE_FILE_PLANET_4			"Images/planet4.png"
#define IMAGE_FILE_PLANET_5			"Images/planet5.png"
#define IMAGE_FILE_PLANET_6			"Images/planet6.png"
#define IMAGE_FILE_PLANET_7			"Images/planet7.png"
#define IMAGE_FILE_PLANET_8			"Images/planet8.png"
#define IMAGE_FILE_PLANET_9			"Images/planet9.png"

//HP�Q�[�W
#define IMAGE_FILE_HP_GUAGE			"Images/hpGuage.png"
#define IMAGE_FILE_ITEM				"Images/Items.png"
//�^�C�g���w�i
#define IMAGE_FILE_TITLE_BG			"Images/title.png"
//�X�^�[�g�{�^��
#define IMAGE_FILE_START_BUTTON		"Images/startButton.png"
//�X�^�[�g�{�^���I����
#define IMAGE_FILE_START_BUTTON_SELECTED				"Images/startButtonSelected.png"
//�I���{�^��
#define IMAGE_FILE_END_BUTTON		"Images/endButton.png"
//�I���{�^���I����
#define IMAGE_FILE_END_BUTTON_SELECTED				"Images/endButtonSelected.png"
//�J�[�\��
#define IMAGE_FILE_CURSOR			"Images/cursor.png"
//���[�U�[
#define IMAGE_FILE_LASER			"Images/laser.png"

//�^�C�g���w�i
#define IMAGE_FILE_TITLE_BACKGROUND "Images/starburst_640x480.png"
#define IMAGE_FILE_EXPLOSION_FINISH	"Images/pipo-btleffect003.png"

//��
#define IMAGE_FILE_WALL				"Images/wall.png"
#define IMAGE_FILE_WALL_2			"Images/wall2.png"
#define IMAGE_FILE_WALL_3			"Images/wall3.png"
#define IMAGE_FILE_WALL_4			"Images/wall4.png"
#define IMAGE_FILE_WALL_5			"Images/wall5.png"
#define IMAGE_FILE_WALL_6			"Images/wall6.png"
#define IMAGE_FILE_WALL_BORDER_1	"Images/wall_border1.png"
#define IMAGE_FILE_WALL_BORDER_2	"Images/wall_border2.png"
#define IMAGE_FILE_WALL_BORDER_3	"Images/wall_border3.png"

//�{��
#define IMAGE_FILE_BOM				"Images/bom.png"

//�A���[�g
#define IMAGE_FILE_ALEART			"Images/aleart.png"

//���v���C�w�i
#define IMAGE_FILE_REPLAY			"Images/UnknownPlanet.png"

//=========================================================================
//	�T�E���h�t�@�C���̃}�N���͂������珑��
//=========================================================================
//BGM
#define SOUND_FILE_BGM_2				"Sounds/nc29206.mp3"
#define SOUND_FILE_BGM_1				"Sounds/nc115484.mp3"
#define SOUND_FILE_BGM_3				"Sounds/nc98330.mp3"

//TITLE
#define SOUND_FILE_TITLE			"Sounds/nc95751.mp3"

//�e���ˌ��ʉ�
#define SOUND_FILE_LAUNCH_BULLET	"Sounds/Se01.mp3"

//�������ʉ�
#define SOUND_FILE_ENEMY_EXPLOSION	"Sounds/enemy_Se01.mp3"
//�������ʉ�
#define SOUND_FILE_PLAYER_EXPLOSION	"Sounds/player_Se02.mp3"

//����HP0���ʉ�
#define SOUND_FILE_ENEMY_EXPLOSION_FINISH	"Sounds/bom21.mp3"

//�J�[�\��1
#define SOUND_FILE_CURSOR_1	"Sounds/cursor05.mp3"

//�J�[�\��2
#define SOUND_FILE_CURSOR_2	"Sounds/cursor09.mp3"

//�A�C�e���擾
#define SOUND_FILE_ITEM_GET			"Sounds/power23.mp3"

//speed up
#define SOUND_FILE_ITEM_SPEED_UP			"Sounds/speedup.mp3"

//recevery
#define SOUND_FILE_ITEM_RECEVERY			"Sounds/recevery.mp3"

//normal
#define SOUND_FILE_ITEM_NORMAL			"Sounds/normal.mp3"

//back
#define SOUND_FILE_ITEM_BACK			"Sounds/back.mp3"

//explosion
#define SOUND_FILE_ITEM_EXPLOSION			"Sounds/explosion.mp3"

//laser
#define SOUND_FILE_ITEM_LASER			"Sounds/laser.mp3"

//induction
#define SOUND_FILE_ITEM_INDUCTION			"Sounds/induction.mp3"

//multiple
#define SOUND_FILE_ITEM_MULTIPLE			"Sounds/multiple.mp3"

//multiple
#define SOUND_FILE_ITEM_BOM				"Sounds/bom.mp3"

//multiple
#define SOUND_FILE_ITEM_ONE_UP			"Sounds/oneup.mp3"

//bom
#define SOUND_FILE_BOM					"Sounds/alarm00.mp3"

//stage clear
#define SOUND_FILE_STAGE_CLEAR					"Sounds/stage_clear.mp3"

//game over
#define SOUND_FILE_GAME_OVER					"Sounds/game_over.mp3"

//time up
#define SOUND_FILE_TIME_UP					"Sounds/time_up.mp3"

//=========================================================================
//	�t�H���g�̃}�N���͂������珑��
//=========================================================================
#define FONT_FILE_STARWARS			"fonts/STARWARS.ttf"
#define FONT_FILE_ARIAL			"fonts/arial.ttf"


//=========================================================================
//	���̑��̊O���t�@�C���̃}�N���͂������珑��
//=========================================================================
//�o���f�[�^
#define ENEMY_LAUNCH_DATA_FILE_1	"EnemyLaunchData1.txt"
#define ENEMY_LAUNCH_DATA_FILE_2	"EnemyLaunchData2.txt"
#define ENEMY_LAUNCH_DATA_FILE_3	"EnemyLaunchData3.txt"

//�}�b�v
#define MAP_FILE_STAGE_1			"Stage1.tmx"
#define MAP_FILE_STAGE_2			"Stage2.tmx"
#define MAP_FILE_STAGE_3			"Stage3.tmx"

//=========================================================================
//	�ėp�I�Ɏg�p�����e���v���[�g�͂������珑��
//=========================================================================
/**
 *	@desc	�z��� NULL �������Ă���Y���ԍ����擾
 *	@param	��������z��
 *	@return	NULL �������Ă���Y���ԍ�
 */
template<typename Ty>
int getFreeIndex( Ty** array, int size ) {
	
	for ( int i = 0 ; i < size ; i++ ) {
		if ( array[ i ] == NULL ) {
			return i ;
		}
	}
	return -1 ;
}



#endif // ShootingGame_Constants_h
