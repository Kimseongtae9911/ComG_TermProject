#pragma once
#include "CObj.h"

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

public:
	CMesh* Get_Rotate() { return m_pObject; };
	GLvoid Set_Rotate(glm::vec3 vec) /*{ m_pObject->GetRotate() = vec; }*/;

private:
	CMesh* m_pObject;

private:
	GLvoid Release();

public:
	static CObject* Create(string strMesh, glm::vec3 vPos, glm::vec4 vCol);
};

