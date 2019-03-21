#pragma once
#ifndef __ShootingGame__InputJoystick__
#define __ShootingGame__InputJoystick__
#include "Lib/InputManager/InputManager.h"
#include "cocos2d.h"



class CInputJoystick {
public:
	struct GamePad {
		enum {
			DPAD_UP = 0x0001,
			DPAD_DOWN = 0x0002,
			DPAD_LEFT = 0x0004,
			DPAD_RIGHT = 0x0008,
			START = 0x0010,
			A = 0x0020,
			B = 0x0040,
			X = 0x0080,
			Y = 0x0100,
			L = 0x0200,
			R = 0x0400
		};
		uint32_t buttons = 0;
		uint32_t buttonDown = 0;
	};
	static GamePad gamepad;
	/**
	*ジョイスティックのアナログ入力装置ID
	*@note XBOX360コントローラー基準
	*/
	enum GLFWAXESID {
		GLFWAXESID_LeftX,//左スティックのX軸
		GLFWAXESID_LeftY,//左スティックのY軸
		GLFWAXESID_BackX,//アナログトリガー
		GLFWAXESID_RightY,//右スティックのY軸
		GLFWAXESID_RightX,//右スティックのX軸
	};

	/**
	*ジョイスティックのデジタル入力装置ID
	*@note XBOX360コントローラー基準
	*/
	enum GLFWBUTTONID {
		GLFWBUTTONID_A,//Aボタン
		GLFWBUTTONID_B,//Bボタン
		GLFWBUTTONID_X,//Xボタン
		GLFWBUTTONID_Y,//Yボタン
		GLFWBUTTONID_L,//Lボタン
		GLFWBUTTONID_R,//Rボタン
		GLFWBUTTONID_Back,//Backボタン
		GLFWBUTTONID_Start,//Startボタン
		GLFWBUTTONID_LThumb,//左スティックボタン
		GLFWBUTTONID_RThumb,//右スティックボタン
		GLFWBUTTONID_Up,//上キー
		GLFWBUTTONID_Right,//右キー
		GLFWBUTTONID_Down,//下キー
		GLFWBUTTONID_Left,//左キー
	};

	
	/**
	*	@desc	キーボードのキーを押した際のイベント
	*	@param	キーコード
	*	@param	イベント
	*/
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	/**
	*	@desc	キーボードのキーを離した際のイベント
	*	@param	キーコード
	*	@param	イベント
	*/
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event);
	static bool m_up;
	static bool m_down;
	static bool m_left;
	static bool m_right;
	static bool m_shot;
	static bool m_change;
	static bool m_pause;
	static bool m_stage;

	static bool m_repPause;
	static bool m_repSpeed;
	static bool m_repSpeed2;
	static bool m_repUp;
	static bool m_repDown;
	static bool m_repLeft;
	static bool m_repRight;

	static bool m_flg;

	static void inputFunc(int mode);
};

#endif __ShootingGame__InputJoystick__