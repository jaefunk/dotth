#include "InputSystem.h"


void InputSystem::Initialize(void)
{
	InputBuffers.resize(128);
	InputEvents.resize(128);
	for (auto i = 0; i < 128; i++)
	{
		InputBuffers[i] = new InputBuffer(0, 0, 0);
		InputEvents[i] = new InputEvent();
	}
}

void InputSystem::UpdateMouseCursorPosition(int x, int y)
{
	cureentMouseCursorPosition.x = x;
	cureentMouseCursorPosition.y = y;
}

void InputSystem::PushBuffer(unsigned int msg, unsigned __int64 wParam, __int64 lParam)
{
	if (InputBuffers.empty())
		return;

	InputBuffer* ib = InputBuffers[lastBufferIndex];
	ib->msg = msg;
	ib->wParam = wParam;
	ib->lParam = lParam;
	lastBufferIndex++;
}

void InputSystem::ArrangeBuffer(void)
{
	lastEventIndex = 0;
	for (unsigned int bufferIndex = 0; bufferIndex < lastBufferIndex; ++bufferIndex)
	{
		InputBuffer* ib = InputBuffers[bufferIndex];

		InputState is = ConvertInputState(ib->msg);
		if (is == InputState::Invalid)
			continue;

		InputKey ik = ConvertInputKey(ib->msg, ib->wParam, ib->lParam);
		if (ik == InputKey::Invalid)
			continue;

		if (is == InputState::DoubleClick)
		{
			InputEvent* ie = InputEvents[lastEventIndex];
			ie->state = InputState::Press;
			ie->key = ik;
			lastEventIndex++;
		}

		InputEvent* ie = InputEvents[lastEventIndex];
		ie->state = is;
		ie->key = ik;
		lastEventIndex++;
	}
}

void InputSystem::BroadcastEvent(void)
{
	for (auto& action : inputBinds)
	{
		for (unsigned int eventIndex = 0; eventIndex < lastEventIndex; ++eventIndex)
		{
			InputEvent* ie = InputEvents[eventIndex];
			action.func(ie->state, ie->key);
		}
	}
}

void InputSystem::ReleaseBuffer(void)
{
	lastBufferIndex = 0;
}

InputState InputSystem::ConvertInputState(unsigned int msg)
{
	switch (msg)
	{
	case WM_KEYDOWN:
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
		return InputState::Press;
	case WM_KEYUP:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
		return InputState::Release;
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDBLCLK:
		return InputState::DoubleClick;
	}
	return InputState::Invalid;
}

InputKey InputSystem::ConvertInputKey(unsigned int msg, unsigned __int64 wParam, __int64 lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
		return InputKey::Mouse_Left;
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
		return InputKey::Mouse_Right;
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
		return InputKey::Mouse_Center;
	case WM_KEYDOWN:
	case WM_KEYUP:
		// alphabet
		if (wParam >= 0x30 && wParam <= 0x39)
			return static_cast<InputKey>(wParam);
		// number
		else if (wParam >= 0x41 && wParam <= 0x5A)
			return static_cast<InputKey>(wParam);
	}
	return InputKey::Invalid;
}


const vector2i& InputSystem::GetMousePosition(void)
{
	return InputSystem::Instance()->cureentMouseCursorPosition;
}

int InputSystem::BindInputDelegate(Base* object, std::function<void(InputState, InputKey)> func)
{
	static int bindID = 0;
	InputBindDelegate ibd;
	ibd.id = bindID;
	ibd.func = func;
	ibd.object = object;
	InputSystem::Instance()->inputBinds.push_back(ibd);
	return bindID++;
}

