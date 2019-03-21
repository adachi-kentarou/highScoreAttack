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
	*�W���C�X�e�B�b�N�̃A�i���O���͑��uID
	*@note XBOX360�R���g���[���[�
	*/
	enum GLFWAXESID {
		GLFWAXESID_LeftX,//���X�e�B�b�N��X��
		GLFWAXESID_LeftY,//���X�e�B�b�N��Y��
		GLFWAXESID_BackX,//�A�i���O�g���K�[
		GLFWAXESID_RightY,//�E�X�e�B�b�N��Y��
		GLFWAXESID_RightX,//�E�X�e�B�b�N��X��
	};

	/**
	*�W���C�X�e�B�b�N�̃f�W�^�����͑��uID
	*@note XBOX360�R���g���[���[�
	*/
	enum GLFWBUTTONID {
		GLFWBUTTONID_A,//A�{�^��
		GLFWBUTTONID_B,//B�{�^��
		GLFWBUTTONID_X,//X�{�^��
		GLFWBUTTONID_Y,//Y�{�^��
		GLFWBUTTONID_L,//L�{�^��
		GLFWBUTTONID_R,//R�{�^��
		GLFWBUTTONID_Back,//Back�{�^��
		GLFWBUTTONID_Start,//Start�{�^��
		GLFWBUTTONID_LThumb,//���X�e�B�b�N�{�^��
		GLFWBUTTONID_RThumb,//�E�X�e�B�b�N�{�^��
		GLFWBUTTONID_Up,//��L�[
		GLFWBUTTONID_Right,//�E�L�[
		GLFWBUTTONID_Down,//���L�[
		GLFWBUTTONID_Left,//���L�[
	};

	
	/**
	*	@desc	�L�[�{�[�h�̃L�[���������ۂ̃C�x���g
	*	@param	�L�[�R�[�h
	*	@param	�C�x���g
	*/
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	/**
	*	@desc	�L�[�{�[�h�̃L�[�𗣂����ۂ̃C�x���g
	*	@param	�L�[�R�[�h
	*	@param	�C�x���g
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