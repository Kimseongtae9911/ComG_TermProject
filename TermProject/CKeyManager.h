#pragma once

const DWORD KEY_UP = 0x00000001;
const DWORD KEY_DOWN = 0x00000002;
const DWORD KEY_LEFT = 0x00000004;
const DWORD KEY_RIGHT = 0x00000008;
const DWORD KEY_SPACE = 0x00000016;
const DWORD KEY_A = 0x00000032;
const DWORD KEY_F = 0x00000064;


class CKeyManager
{
	DECLARE_SINGLETON(CKeyManager)

private:
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

