#include "stdafx.h"
#include "CObject.h"
#include "CMesh.h"
#include "CRenderManager.h"
#include "CShader.h"
#include "CGameManager.h"

CObject::CObject()
{
}

CObject::~CObject()
{
}

HRESULT CObject::Initialize(string strMesh, glm::vec3 vPos, glm::vec4 vCol)
{
	CObj::Initialize();

	m_pObject = CMesh::Create(strMesh, vCol);
	m_pObject->GetPos() = vPos;

	return NOERROR;
}

GLint CObject::Update(const GLfloat fTimeDelta)
{
	CObject::Get_BB() = {m_pObject->GetPos().x - 0.5f, m_pObject->GetPos().x + 0.5f, m_pObject->GetPos().y + 0.5f, m_pObject->GetPos().y - 0.5f};
	m_pRender->Add_RenderObj(REDER_NONAL, this);
	return GLint();
}

GLvoid CObject::Render()
{
	m_pShaderLoader->Use_Shader("Default");
	m_pGameMgr->Render_Camera();
	m_pObject->Render();
	return GLvoid();
}
GLvoid CObject::Set_Rotate(glm::vec3 vec)
{ m_pObject->GetRotate() = vec; }

GLvoid CObject::Release()
{
	return GLvoid();
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
