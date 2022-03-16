#pragma once

#include "SystemDefine.h"
#include "SingleInstance.h"

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
	static void UnbindInputDelegate(Base* object);
	static void UnbindInputDelegate(int bindID);
};