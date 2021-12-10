#include"stdafx.h"
#include "CGameManager.h"
#include "CObj.h"
#include "CCamera.h"

IMPLEMENT_SINGLETON(CGameManager)

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
}

HRESULT CGameManager::Add_GameObj(OBJID eID, CObj* pObj)
{
	if (!pObj)
		return E_FAIL;

	m_ObjLst[eID].emplace_back(pObj);

	return NOERROR;
}

GLvoid CGameManager::Update(const GLfloat fTimeDelta)
{
	list<CObj*>::iterator iter_begin;
	list<CObj*>::iterator iter_end;
	for (int i = 0; i < OBJ_END; ++i)
	{
		iter_begin = m_ObjLst[i].begin();
		iter_end = m_ObjLst[i].end();
		for (; iter_begin != iter_end;)
		{
			if (OBJ_END == (*iter_begin)->Update(fTimeDelta))
			{
				SafeDelete(*iter_begin);
				iter_begin = m_ObjLst[i].erase(iter_begin);
			}
			else
				++iter_begin;
		}
	}

	if (m_pCamera)
		m_pCamera->Update(fTimeDelta);
	return GLvoid();
}

HRESULT CGameManager::Clear_ObjList()
{
	for (int i = 0; i < OBJ_END; ++i)
		Clear_Obj((OBJID)i);
	//

	return NOERROR;
}

HRESULT CGameManager::Clear_Obj(OBJID eID)
{
	for (auto pObj : m_ObjLst[eID])
		SafeDelete(pObj);
	m_ObjLst[eID].clear();

	return NOERROR;
}

HRESULT CGameManager::Add_Camera(CCamera* pCamera)
{
	if (!pCamera)
		return E_FAIL;

	if (m_pCamera)
		SafeDelete(m_pCamera);
	m_pCamera = pCamera;

	return NOERROR;
}

GLvoid CGameManager::Render_Camera()
{
	if (m_pCamera)
		m_pCamera->Render();
	return GLvoid();
}
