#pragma once

#include "dotth.h"

struct ViewInfo {
	matrix View;
	matrix Perspective;
	vector3 Eye;
	vector3 Up;
	vector3 At;
	float Near;
	float Far;
	float Fov;
	int Width;
	int Height;
};

enum class InputKey {
	Invalid,
	Mouse_Left = VK_LBUTTON,
	Mouse_Right = VK_RBUTTON,
	Mouse_Center = VK_MBUTTON,
	Keyboard_A = 0x41,
	Keyboard_B,
	Keyboard_C,
	Keyboard_D,
	Keyboard_E,
	Keyboard_F,
	Keyboard_G,
	Keyboard_H,
	Keyboard_I,
	Keyboard_J,
	Keyboard_K,
	Keyboard_L,
	Keyboard_M,
	Keyboard_N,
	Keyboard_O,
	Keyboard_P,
	Keyboard_Q,
	Keyboard_R,
	Keyboard_S,
	Keyboard_T,
	Keyboard_U,
	Keyboard_V,
	Keyboard_W,
	Keyboard_X,
	Keyboard_Y,
	Keyboard_Z = 0x5A,
	Keyboard_0 = 0x30,
	Keyboard_1,
	Keyboard_2,
	Keyboard_3,
	Keyboard_4,
	Keyboard_5,
	Keyboard_6,
	Keyboard_7,
	Keyboard_8,
	Keyboard_9 = 0x39,
};

enum class InputState {
	Invalid,
	Press,
	Release,
	Repeat,
	DoubleClick,
};

struct InputEvent {
	InputKey key;
	InputState state;
};

struct InputBindDelegate {
	int id;
	Base* object;
	std::function<void(InputState, InputKey)> func;
};