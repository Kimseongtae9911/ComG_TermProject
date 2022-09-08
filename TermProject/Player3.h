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
	bool& Get_Portal() { return m_bPortal; }
	bool& Get_HoldingB() { return m_bHoldingB; }
	bool& Get_CollideB() { return m_bCollideB; }

private:
	CMesh* m_Player;
	CObj* m_pCollideObj = nullptr;
	GLfloat m_fAlpha{ 0.3f };
	bool m_bPortal{ false };
	bool m_bHoldingB{ false };
	bool m_bCollideB{ false };

private:
	void KeyboardInput(const GLfloat fTimeDelta);
	void CollideCheck();
	bool Collide_Monster();
	bool Collide_OBJ();

private:
	GLvoid Release();
	GLvoid UpdateBB();

public:
	static Player3* Create();
};

