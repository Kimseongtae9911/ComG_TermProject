#include "CKeyManager.h"

IMPLEMENT_SINGLETON(CKeyManager)

CKeyManager::CKeyManager()
{

}

CKeyManager::~CKeyManager()
{
}

void CKeyManager::UpdateKey()
{
	m_dwCurKey = 0;

	for (int i = 0; i < MAX_VKEY; ++i)
	{
		if (m_dwCurKey && !(GetAsyncKeyState(i) & 0x8000))
			m_dwCurKey = !m_dwCurKey;
		if (!m_dwCurKey && (GetAsyncKeyState(i) & 0x8000))
			m_dwCurKey = !m_dwCurKey;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)		
		m_dwCurKey |= KEY_UP;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		m_dwCurKey |= KEY_DOWN;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_dwCurKey |= KEY_LEFT;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_dwCurKey |= KEY_RIGHT;
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		m_dwCurKey |= KEY_SPACE;
	if (GetAsyncKeyState(0x41) & 0x8000)
		m_dwCurKey |= KEY_A;
	if (GetAsyncKeyState(0x46) & 0x8000)
		m_dwCurKey |= KEY_F;
}

bool CKeyManager::KeyDown(DWORD dwCurKey)
{
	// ���� ������ ���� ���� ������ �� true
	if (!(m_dwKeyDown & dwCurKey) && (m_dwCurKey & dwCurKey))
	{
		m_dwKeyDown |= dwCurKey;
		return true;
	}

	// m_dwKeyDown�� ����
	// ���� ������ �ְ� ���� ������ �ʾ��� ��
	else if ((m_dwKeyDown & dwCurKey) && !(m_dwCurKey & dwCurKey))
	{
		m_dwKeyDown ^= dwCurKey;
		return false;
	}

	return false;
}

bool CKeyManager::KeyUp(DWORD dwCurKey)
{
	// ���� ������ �ְ� ���� ������ �ʾ��� �� true
	if ((m_dwKeyUp & dwCurKey) && !(m_dwCurKey & dwCurKey))
	{
		// m_dwKeyUp�� ����
		m_dwKeyUp ^= dwCurKey;
		return true;
	}

	// ���� ������ ���� ���� ������ �� 
	else if (!(m_dwKeyUp & dwCurKey) && (m_dwCurKey & dwCurKey))
	{
		m_dwKeyUp |= dwCurKey;
		return false;
	}

	return false;
}

bool CKeyManager::KeyPressing(DWORD dwCurKey)
{
	if (m_dwCurKey & dwCurKey)
		return true;

	return false;
}


bool CKeyManager::KeyCombined(DWORD dwFistKey, DWORD dwSecondKey)
{
	if (KeyDown(dwSecondKey) && KeyPressing(dwFistKey))
		return true;

	return false;
}
