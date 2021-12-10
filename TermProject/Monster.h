#pragma once
#include "stdafx.h"
#include "CMesh.h"
#include "CObj.h"

class Monster : public CObj
{
public:
	Monster();
	~Monster();

public:
	virtual HRESULT Initialize();
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

private:
	

private:
	bool m_bView{ true }; // true ->2D, false ->3D
};

