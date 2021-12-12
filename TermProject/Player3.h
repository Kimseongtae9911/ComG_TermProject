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
	virtual int& GetC_Dir() { return m_iCollideDir; }
	bool& Get_Portal() { return m_bPortal; }
	bool& Get_InPortal() { return m_bIn_Portal; }

public:
	CMesh* Get_pMesh() { return m_Player; };

private:
	CMesh* m_Player;

private:
	GLfloat m_fAlpha{ 1.0f };
	int m_iCollideDir{ 0 }; // 1:Left, 2:Right, 3:Up, 4:Down
	int m_iMoveDir{ 0 };
	bool m_bPortal{ false };
	bool m_bIn_Portal{ false };

public:
	static Player3* Create();
};

