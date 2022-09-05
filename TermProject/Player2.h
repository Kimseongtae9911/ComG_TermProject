#pragma once
#include "CObj.h"

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

	CMesh* Get_Mesh() { return m_Player; }
	//int& GetC_Dir() { return m_iCollideDir; }
	bool& GetJump() { return m_bJump; }
	CMesh* GetP() { return m_Player; }
	bool& Get_Portal() { return m_bPortal; }
	bool& Get_Die() { return m_bDie; }

private:
	void KeyboardInput(const GLfloat fTimeDelta);
	void JumpProcess(const GLfloat fTimeDelta);
	void PortalInteract();
	void CollideCheck();
	bool Collide_Monster();
	bool Collide_OBJ();
	GLvoid Release();
	GLvoid UpdateBB();

private:
	CMesh* m_Player = nullptr;
	CObj* m_pCollideObj = nullptr;
	GLfloat m_fJumpSpeed{};

	GLfloat m_fAlpha{ 1.0f };
	bool m_bJump{ false };
	int m_iJumpdir{ -1 };
	GLfloat m_fJumpStart{ 0.f };
	//int m_iCollideDir{ 0 }; // 1:Left, 2:Right, 3:Up, 4:Down
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

#define SPEED_2D 6.0f
#define JUMP_SPEED 11.0f
#define GRAVITY JUMP_SPEED / 30.f