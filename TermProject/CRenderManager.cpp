#include "stdafx.h"
#include "CRenderManager.h"
#include"CObj.h"

IMPLEMENT_SINGLETON(CRenderManager)

CRenderManager::CRenderManager()
{

}

CRenderManager::~CRenderManager()
{
}

GLvoid CRenderManager::Render_Object()
{
	for (int i = 0; i < static_cast<int>(RENDER_ID::RENDER_END); ++i)
	{
		// Render 할것에 따라 GL_DEPTH_TEST
		glEnable(GL_DEPTH_TEST);

		for (auto& pObj : m_lstRenderObj[i])
			pObj->Render();
	}

	Clear_Renderer();
	return GLvoid();
}

HRESULT CRenderManager::Add_RenderObj(RENDER_ID eID, CObj* pObj)
{
	if (!pObj)
		return E_FAIL;

	m_lstRenderObj[static_cast<int>(eID)].emplace_back(pObj);
	return E_NOTIMPL;
}

GLvoid CRenderManager::Clear_Renderer()
{
	for (int i = 0; i < static_cast<int>(RENDER_ID::RENDER_END); ++i)
		m_lstRenderObj[i].clear();
}
