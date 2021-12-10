#pragma once
#include "CObj.h"
//#include "CMesh.h"
//#include "CObject.h"

class CMesh;
class Player : public CObj
{
public:
	Player();
	~Player();

public:
	virtual HRESULT Initialize();
    virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

private:
	CMesh* m_player;

private:
	GLfloat m_fAlpha{ 1.0f };
	bool m_bView{ true };

public:
	static Player* Create();
};

