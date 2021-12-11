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

private:
	CMesh* m_Player;

private:
	GLfloat m_fAlpha{ 1.0f };

public:
	static Player3* Create();
};

