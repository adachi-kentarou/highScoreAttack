#include "Lib/InputManager/InputJoystick.h"
#include "Lib/InputManager/InputManager.h"
#include "Scene/GameMain/GameMain.h"
using namespace cocos2d;
bool CInputJoystick::m_up;
bool CInputJoystick::m_down;
bool CInputJoystick::m_left;
bool CInputJoystick::m_right;
bool CInputJoystick::m_shot;
bool CInputJoystick::m_change;
bool CInputJoystick::m_pause;
bool CInputJoystick::m_stage;
bool CInputJoystick::m_repPause;
bool CInputJoystick::m_repSpeed;
bool CInputJoystick::m_repSpeed2;
bool CInputJoystick::m_repUp;
bool CInputJoystick::m_repDown;
bool CInputJoystick::m_repLeft;
bool CInputJoystick::m_repRight;
bool CInputJoystick::m_flg = false;
CInputJoystick::GamePad CInputJoystick::gamepad;

void CInputJoystick::inputFunc(int mode) {
	//フラグ初期化
	m_up = inputflag.m_up;
	m_down = inputflag.m_down;
	m_left = inputflag.m_left;
	m_right = inputflag.m_right;
	m_shot = inputflag.m_z;
	m_change = inputflag.m_x;
	m_pause = inputflag.m_space;
	m_stage = inputflag.m_s;
	//リプレイ用
	m_repPause = inputflag.m_space;
	m_repSpeed = inputflag.m_z;
	m_repSpeed2 = inputflag.m_x;
	m_repUp = inputflag.m_up;
	m_repDown = inputflag.m_down;
	m_repLeft = inputflag.m_left;
	m_repRight = inputflag.m_right;
	if (GAME_PAD) {
		//DirectInput

		for (int i = 0; i <= GLFW_JOYSTICK_LAST; i++) {

			if (glfwJoystickPresent(i)) {
				int buttonNum;
				int axisNum;
				const unsigned char* buttons;
				const float* axes;
				buttons = glfwGetJoystickButtons(i, &buttonNum);
				axes = glfwGetJoystickAxes(i, &axisNum);

				if ((int)buttons[0] == 1) {
					m_shot = true;
					m_repSpeed = true;
				}
				if ((int)buttons[2] == 1) {
					m_change = true;
					m_repSpeed2 = true;
				}
				if ((int)buttons[1] == 1) {
					m_pause = true;
					m_repPause = true;
				}
				if ((int)buttons[3] == 1) {
					m_stage = true;
				}
				if ((int)axes[0] == 1 || (int)buttons[14] == 1) {
					m_right = true;
					m_repRight = true;
				}
				if ((int)axes[0] == -1 || (int)buttons[16] == 1) {
					m_left = true;
					m_repLeft = true;
				}
				if ((int)axes[1] == 1 || (int)buttons[15] == 1) {
					m_down = true;
					m_repDown = true;
				}
				if ((int)axes[1] == -1 || (int)buttons[13] == 1) {
					m_up = true;
					m_repUp = true;
				}
			}
		}
		
	}
	else {
		//XInput

		uint32_t prevButtons = gamepad.buttons;//前フレームのボタン状態を保存
													 //ジョイスティック入力kを取得し、取得した要素が足りていればそれを使う
		int axesCount, buttonCount;
		const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
		const uint8_t* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
		if (axes && buttons && axesCount >= 2 && buttonCount >= 8) {
			//ジョイスティックの左スティック入力をゲームパッド入力に変換する
			gamepad.buttons &= ~(GamePad::DPAD_UP | GamePad::DPAD_DOWN
				| GamePad::DPAD_LEFT | GamePad::DPAD_RIGHT);
			
			//ジョイスティックのボタン入力をゲームパッドに変換する
			static const struct {
				int glfwCode;
				uint32_t gamepadCode;
			} keyMap[] = {
				{ GLFWBUTTONID_A,GamePad::A },
				{ GLFWBUTTONID_B,GamePad::B },
				{ GLFWBUTTONID_X,GamePad::X },
				{ GLFWBUTTONID_Y,GamePad::Y },
				{ GLFWBUTTONID_Start,GamePad::START },
				{ GLFWBUTTONID_Up,GamePad::DPAD_UP },
				{ GLFWBUTTONID_Right,GamePad::DPAD_RIGHT },
				{ GLFWBUTTONID_Down,GamePad::DPAD_DOWN },
				{ GLFWBUTTONID_Left,GamePad::DPAD_LEFT }
			};
			for (const auto& e : keyMap) {
				if (buttons[e.glfwCode] == GLFW_PRESS) {
					gamepad.buttons |= e.gamepadCode;
				}
				else if (buttons[e.glfwCode] == GLFW_RELEASE) {
					gamepad.buttons &= ~e.gamepadCode;
				}
			}
			static const float threshould = 0.3f;
			//cocos2d::log("%f", axes[GLFWAXESID_LeftY]);
			if (axes[GLFWAXESID_LeftY] >= threshould) {
				gamepad.buttons |= GamePad::DPAD_UP;
			}
			if (axes[GLFWAXESID_LeftY] <= -threshould) {
				gamepad.buttons |= GamePad::DPAD_DOWN;
			}
			if (axes[GLFWAXESID_LeftX] >= threshould) {
				gamepad.buttons |= GamePad::DPAD_RIGHT;
			}
			if (axes[GLFWAXESID_LeftX] <= -threshould) {
				gamepad.buttons |= GamePad::DPAD_LEFT;
			}
		}
		gamepad.buttonDown = gamepad.buttons & ~prevButtons;

		if (gamepad.buttons & GamePad::X) {
			m_shot = true;
			m_repSpeed = true;
		}
		if (gamepad.buttons & GamePad::A) {
			m_change = true;
			m_repSpeed2 = true;
		}
		if (gamepad.buttons & GamePad::Y) {
			m_pause = true;
			m_repPause = true;
		}
		if (gamepad.buttons & GamePad::B) {
			m_stage = true;
		}
		if (gamepad.buttons & GamePad::DPAD_RIGHT) {
			m_right = true;
			m_repRight = true;
		}
		if (gamepad.buttons & GamePad::DPAD_LEFT) {
			m_left = true;
			m_repLeft = true;
		}
		if (gamepad.buttons & GamePad::DPAD_DOWN) {
			m_down = true;
			m_repDown = true;
		}
		if (gamepad.buttons & GamePad::DPAD_UP) {
			m_up = true;
			m_repUp = true;
		}
	}
	

	//ボタン押し解除判定
	if (m_flg) {
		m_flg = m_change || m_down || m_left || m_right || m_up || m_shot || m_pause || m_stage;
	}
	//リプレイ記録
	if (mode == 0) {
		int repData;
		int order = CGameMain::m_frameCounter % 4 * 7;

		repData = ((int)m_up << order) + ((int)m_down << (order + 1)) +
			((int)m_left << (order + 2)) + ((int)m_right << (order + 3)) +
			((int)m_shot << (order + 4)) + ((int)m_change << (order + 5)) + ((int)m_stage << (order + 6));
		REPLAY_DATA[CGameMain::m_frameCounter / 4 + 13 + ((CGameMain::m_stageNo - 1) * 4000)] += repData;
		
	}
	//リプレイ再生
	if (mode >= 2) {
		int repData;
		int order = CGameMain::m_frameCounter % 4 * 7;
		repData = REPLAY_DATA[CGameMain::m_frameCounter / 4 + 13 + ((CGameMain::m_stageNo - 1) * 4000)];
		
		repData >>= order;
		
		m_up = (bool)(repData & 1);
		repData >>= 1;
		m_down = (bool)(repData & 1);
		repData >>= 1;
		m_left = (bool)(repData & 1);
		repData >>= 1;
		m_right = (bool)(repData & 1);
		repData >>= 1;
		m_shot = (bool)(repData & 1);
		repData >>= 1;
		m_change = (bool)(repData & 1);
		repData >>= 1;
		m_stage = (bool)(repData & 1);
		}
	
}
/**
*	@desc	キーボードのキーを押した際のイベント
*	@param	キーコード
*	@param	イベント
*/
void CInputJoystick::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
	// 入力管理に入力処理を委託
	CInputManager::getInstance()->onKeyPressed(keyCode);
}

/**
*	@desc	キーボードのキーを離した際のイベント
*	@param	キーコード
*	@param	イベント
*/
void CInputJoystick::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event) {

	// 入力管理に入力処理を委託
	CInputManager::getInstance()->onKeyReleased(keyCode);
}