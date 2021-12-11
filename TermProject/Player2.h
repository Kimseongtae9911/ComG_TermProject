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

private:
	CMesh* m_Player;
	BB m_Box;

private:
	GLfloat m_fAlpha{ 1.0f };
	bool m_bJump{ false };
	int m_iJumpdir{ -1 };
	GLfloat m_fJumpPos{ 0.f };
	GLfloat m_fJumpStart{ 0.f };

public:
	static Player2* Create();
	BB Get_BB() { return m_Box; }
};

