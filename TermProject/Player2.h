#pragma once
#include "CObj.h"
//#include "CMesh.h"
//#include "CObject.h"

class CMesh;
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
	CMesh* m_player;

private:
	GLfloat m_fAlpha{ 1.0f };
	//bool m_bView{ true };

public:
	static Player2* Create();
};

