#pragma once
#include "CObj.h"

#define SPEED_2D 5.0f
#define JUMP_SPEED 14.0f
#define GRAVITY 30.0f

class CMesh;
class CCamera;
class Player2 : public CObj
{
public:
	Player2();
	~Player2();

public:
	virtual HRESULT Initialize();
    virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

	bool Collide_DIR(const DIR dir);

	CMesh* Get_Mesh() { return m_Player; }	
	CMesh* GetP() { return m_Player; }
	bool& Get_Portal() { return m_bPortal; }
	bool& Get_Die() { return m_bDie; }

private:
	void KeyboardInput(const GLfloat fTimeDelta);
	void JumpProcess(const GLfloat fTimeDelta);
	void CollideCheck();
	bool Collide_Monster();
	void Collide_OBJ();
	GLvoid Release();
	GLvoid UpdateBB();

private:
	CMesh* m_Player = nullptr;
	CObj* m_pCollideObj = nullptr;
	GLfloat m_fJumpSpeed = JUMP_SPEED;

	GLfloat m_fAlpha{ 1.0f };
	int m_iMoveDir{ };
	bool m_bPortal{ false };
	bool m_bDie = false;

	GLfloat m_fJumpPos{ 0.f };
	bool m_bOnAir{ false };
	bool m_bFalling{ false };
	DIR m_dirCollideDir{ DIR::NONE };

public:
	static Player2* Create();
};