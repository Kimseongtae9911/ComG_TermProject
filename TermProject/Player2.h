#pragma once
#include "CObj.h"
//#include "CMesh.h"
//#include "CObject.h"

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

	int& GetC_Dir() { return m_iCollideDir; }
	DIR& GetM_Dir() { return m_iMoveDir; }
	bool& GetJump() { return m_bJump; }
	CMesh* GetP() { return m_Player; }
	bool& Get_Die() { return m_iDie; }
	bool& Get_Portal() { return m_bPortal; }
	

private:
	bool Collide_Spike();
	bool Collide_Monster();
	GLvoid Release();

private:
	CMesh* m_Player = nullptr;

private:
	GLfloat m_fAlpha{ 1.0f };
	bool m_bJump{ false };
	int m_iJumpdir{ -1 };
	GLfloat m_fJumpPos{ 0.f };
	GLfloat m_fJumpStart{ 0.f };
	int m_iCollideDir{ 0 }; // 1:Left, 2:Right, 3:Up, 4:Down
	DIR m_iMoveDir{};
	bool m_bPortal{ false };
	bool m_iDie{ false };

public:
	static Player2* Create();
};

