#pragma once
#include "CObj.h"

class CMesh;
class CObject : public CObj
{
public:
	CObject();
	CObject(const CObject& other);
	~CObject();

public:
	virtual HRESULT Initialize(string strMesh, glm::vec3 vPos, glm::vec4 vCol);
	virtual HRESULT Initialize(CObject* pObj, string strMesh, glm::vec3 vPos, glm::vec4 vCol);
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

public:
	CMesh* Get_Rotate() { return m_pObject; };
	GLvoid Set_Rotate(glm::vec3 vec) /*{ m_pObject->GetRotate() = vec; }*/;
	CMesh* Get_Mesh() { return m_pObject; };

	void Change_position(glm::vec3 vPos);

private:
	CMesh* m_pObject;

private:
	GLvoid Release();

public:
	static CObject* Create(string strMesh, glm::vec3 vPos, glm::vec4 vCol);
	static CObject* Create(CObject* pObj, string strMesh, glm::vec3 vPos, glm::vec4 vCol);

};

