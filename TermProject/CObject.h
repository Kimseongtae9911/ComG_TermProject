#pragma once
#include "CObj.h"
//#include "CMesh.h"
class CMesh;

class CObject : public CObj
{
public:
	CObject();
	~CObject();

public:
	virtual HRESULT Initialize(string strMesh, glm::vec3 vPos, glm::vec4 vCol);
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

private:
	CMesh* m_pObject;

private:
	GLvoid Release();

public:
	static CObject* Create(string strMesh, glm::vec3 vPos, glm::vec4 vCol);
};

