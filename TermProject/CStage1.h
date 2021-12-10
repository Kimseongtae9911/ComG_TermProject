#pragma once
#include "CScene.h"
//#include "Player3.h"
//#include "Player.h"
//#include "CObject.h"
//#include "CCamera.h"
//
class CStage1 : public CScene
{
public:
	CStage1();
	~CStage1();

public:
	virtual HRESULT Initialize();
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

private:
	GLvoid Release();

public:
	static CStage1* Create();


};

