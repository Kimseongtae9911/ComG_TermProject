#include"stdafx.h"
#include "CGameManager.h"
#include "CKeyManager.h"
#include "CObj.h"
#include "CCamera.h"
#include "CKeyManager.h"

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
	
	if (CKeyManager::GetInstance()->KeyDown(KEY_F)) {
		m_bView = !m_bView;
	}

	if (m_bView) {
		//Player Monster, Player Obj, Monster Obj
		CObj* player = m_ObjLst[OBJ_PLAYER1].front();
		BB player_BB = player->Get_BB();
		for (int i = OBJ_MONSTER; i < OBJ_UI; ++i) 
		{
			iter_begin = m_ObjLst[i].begin();
			iter_end = m_ObjLst[i].end();
			for (; iter_begin != iter_end;)
			{
				BB OBJ_BB = (*iter_begin)->Get_BB();

				if (player_BB.left > OBJ_BB.right || player_BB.right < OBJ_BB.left || player_BB.top < OBJ_BB.bottom || player_BB.bottom > OBJ_BB.top) {

				}
				else {
					cout << "Collide" << endl;
				}
				++iter_begin;
			}
		}
	}
	else {
		CObj* player = m_ObjLst[OBJ_PLAYER2].front();
		BB player_BB = player->Get_BB();
		for (int i = OBJ_MONSTER; i < OBJ_UI; ++i) {
			iter_begin = m_ObjLst[i].begin();
			iter_end = m_ObjLst[i].end();
			for (; iter_begin != iter_end;)
			{
				BB OBJ_BB = (*iter_begin)->Get_BB();

				if (player_BB.left > OBJ_BB.right || player_BB.right < OBJ_BB.left || player_BB.top < OBJ_BB.bottom || player_BB.bottom > OBJ_BB.top) {

				}
				else {
					cout << "Collide" << endl;
				}
				++iter_begin;
			}
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
