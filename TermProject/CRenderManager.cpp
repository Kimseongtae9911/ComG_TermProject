#include "stdafx.h"
#include "CRenderManager.h"

#include"CObj.h"

IMPLEMENT_SINGLETON(CRenderManager)

CRenderManager::~CRenderManager()
{
}

GLvoid CRenderManager::Render_Object()
{
	for (int i = 0; i < RENDER_END; ++i)
	{
		// Render �ҰͿ� ���� GL_DEPTH_TEST
		for (auto pObj : m_lstRenderObj[i])
			pObj->Render();

	}

	Clear_Renderer();
	return GLvoid();
}

HRESULT CRenderManager::Add_RenderObj(RENDER_ID eID, CObj* pObj)
{
	return E_NOTIMPL;
}

GLvoid CRenderManager::Clear_Renderer()
{
	return GLvoid();
}