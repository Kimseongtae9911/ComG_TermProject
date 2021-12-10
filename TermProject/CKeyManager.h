#pragma once
#include "stdafx.h"

constexpr DWORD KEY_UP = 0x00000001;
constexpr DWORD KEY_DOWN = 0x00000002;
constexpr DWORD KEY_LEFT = 0x00000004;
constexpr DWORD KEY_RIGHT = 0x00000008;
constexpr DWORD KEY_SPACE = 0x00000010;
constexpr DWORD KEY_ESCAPE = 0x00000020;
constexpr DWORD KEY_A = 0x00000040;
constexpr DWORD KEY_F = 0x00000080;


class CKeyManager
{
	DECLARE_SINGLETON(CKeyManager)

public:
	CKeyManager();
	~CKeyManager();

public:
	void UpdateKey();

public:
	bool KeyDown(DWORD dwCurKey);
	bool KeyUp(DWORD dwCurKey);
	bool KeyPressing(DWORD dwCurKey);
	bool KeyCombined(DWORD dwFistKey, DWORD dwSecondKey);

private:
	DWORD m_dwCurKey = 0;
	DWORD m_dwKeyUp = 0;
	DWORD m_dwKeyDown = 0;
};