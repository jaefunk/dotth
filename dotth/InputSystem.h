#pragma once

#include "SingleInstance.h"

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

class InputSystem : public SingleInstance<InputSystem>
{
	friend class Application;

private:
	struct InputBuffer {
		InputBuffer(unsigned int _msg, unsigned __int64 _wParam, __int64 _lParam)
			: msg(_msg), wParam(_wParam), lParam(_lParam) {}
		unsigned int msg;
		unsigned __int64 wParam;
		__int64 lParam;
	};
	unsigned int lastBufferIndex = 0;
	std::vector<InputBuffer*> InputBuffers;
	unsigned int lastEventIndex = 0;
	std::vector<InputEvent*> InputEvents;
	std::vector<InputBindDelegate> inputBinds;

	vector2i cureentMouseCursorPosition;

private:
	void Initialize(void);
	void UpdateMouseCursorPosition(int x, int y);
	void PushBuffer(unsigned int msg, unsigned __int64 wParam, __int64 lParam);
	void ArrangeBuffer(void);
	void BroadcastEvent(void);
	void ReleaseBuffer(void);
	InputState ConvertInputState(unsigned int msg);
	InputKey ConvertInputKey(unsigned int msg, unsigned __int64 wParam, __int64 lParam);

public:
	static const vector2i& GetMousePosition(void);
	static int BindInputDelegate(Base* object, std::function<void(InputState, InputKey)> func);
};