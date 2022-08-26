#pragma once
#include "CObj.h"
//#include "CMesh.h"
//#include "Player.h"
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
	int& GetC_Dir() { return m_iCollideDir; }
	bool& Get_Portal() { return m_bPortal; }
	bool& Get_HoldingB() { return m_bHoldingB; }
	bool& Get_CollideB() { return m_bCollideB; }

private:
	CMesh* m_Player;
	GLfloat m_fAlpha{ 1.0f };
	int m_iCollideDir{ 0 }; // 1:Left, 2:Right, 3:Up, 4:Down
	DIR m_iMoveDir{};
	bool m_bPortal{ false };
	bool m_bHoldingB{ false };
	bool m_bCollideB{ false };

private:
	void KeyboardInput(const GLfloat fTimeDelta);
	void PortalInteract();
	void CollideCheck();
	bool Collide_Monster();
	bool Collide_OBJ();

private:
	GLvoid Release();
	

public:
	static Player3* Create();
};

