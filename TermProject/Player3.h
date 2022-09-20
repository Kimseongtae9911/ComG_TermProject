#pragma once
#include "CObj.h"

#define SPEED_3D 5.0f
#define SPEED_3D_DI 4.0f

class CMesh;
class CCamera;
class Player3 : public CObj
{
public:
	Player3();
	~Player3();

public:
	virtual HRESULT Initialize();
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();
	
public:
	CMesh* Get_pMesh() { return m_Player; };
	bool Get_Portal() { return m_bPortal; }
	bool Get_HoldingB() { return m_bHoldingB; }
	bool Get_CollideB() { return m_bCollideB; }
	CObj* GetHoldingBox() { return m_pHoldingBox; }

	GLvoid SetHoldingB(bool bHoldingB) { m_bHoldingB = bHoldingB; }
	GLvoid SetCollideB(bool bCollideB) { m_bCollideB = bCollideB; }
	GLvoid ResetHoldingB() { m_pHoldingBox = nullptr; }

private:
	CMesh* m_Player;
	CObj* m_pCollideObj = nullptr;
	CObj* m_pHoldingBox = nullptr;
	GLfloat m_fAlpha{ 0.3f };
	bool m_bPortal{ false };
	bool m_bHoldingB{ false };
	bool m_bCollideB{ false };

private:
	void KeyboardInput(const GLfloat fTimeDelta);
	void Box_Move(const GLfloat fTimeDelta);
	void CollideCheck();
	bool Collide_Monster();
	bool Collide_OBJ();
	bool Check_BoxDown();

private:
	GLvoid Release();
	GLvoid UpdateBB();

public:
	static Player3* Create();
};

