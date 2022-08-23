#include "stdafx.h"
#include "CObject.h"
#include "CMesh.h"
#include "CRenderManager.h"
#include "CShader.h"
#include "CGameManager.h"

CObject::CObject()
{
}

CObject::CObject(const CObject& other)
{
	m_pObject = new CMesh;
	memcpy(m_pObject, other.m_pObject, sizeof(other.m_pObject));
	std::cout << "복사생성" << std::endl;
}

CObject::~CObject()
{
	Release();
}

HRESULT CObject::Initialize(string strMesh, glm::vec3 vPos, glm::vec4 vCol)
{
	CObj::Initialize();

	m_pObject = CMesh::Create(strMesh, vCol);
	m_pObject->GetPos() = vPos;

	return NOERROR;
}

HRESULT CObject::Initialize(CObject* pObj, string strMesh, glm::vec3 vPos, glm::vec4 vCol)
{
	return E_NOTIMPL;
}

GLint CObject::Update(const GLfloat fTimeDelta)
{
	CObj::UpdateAABB(m_pObject->Get_Matrix());
	m_pRender->Add_RenderObj(RENDER_ID::REDER_NONAL, this);
	return GLint();
}

GLvoid CObject::Render()
{
	m_pShaderLoader->Use_Shader("Default");
	m_pGameMgr->Render_Camera();
	m_pObject->Render();

	CObj::Render();

	return GLvoid();
}

GLvoid CObject::Set_Rotate(glm::vec3 vec)
{ 
	m_pObject->GetRotate() = vec; 
}

GLvoid CObject::Release()
{
	SafeDelete(m_pObject);
	return GLvoid();
}

void CObject::Change_position(glm::vec3 vPos)
{
	m_pObject->GetPos() = vPos;
}

CObject* CObject::Create(string strMesh, glm::vec3 vPos, glm::vec4 vCol)
{
	CObject* pInstance = new CObject;

	if (FAILED(pInstance->Initialize(strMesh, vPos, vCol)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

CObject* CObject::Create(CObject* pObj, string strMesh, glm::vec3 vPos, glm::vec4 vCol)
{
	CObject* pInstance(pObj);
	pInstance->Change_position(vPos);
	return pInstance;
}


