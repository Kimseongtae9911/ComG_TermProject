#include"stdafx.h"
#include "CGameManager.h"
#include "CKeyManager.h"
#include "CObj.h"
#include "CCamera.h"
#include "CKeyManager.h"
#include "Monster.h"

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
	if (!Get_View() && Get_Camera()->Get_Move()) {
		if (CKeyManager::GetInstance()->KeyDown(KEY_F)) {
			m_bView = !m_bView;
		}
	}
	else if (Get_View() && !Get_Camera()->Get_Move()) {
		if (CKeyManager::GetInstance()->KeyDown(KEY_F)) {
			m_bView = !m_bView;
		}
	}

	//Player Collide
	if (m_bView) {
		//Player Monster, Player Obj, Monster Obj
		CObj* player = m_ObjLst[OBJ_PLAYER1].front();
		BB player_BB = player->Get_BB();
		for (int i = OBJ_MONSTER1; i < OBJ_UI; ++i) 
		{
			iter_begin = m_ObjLst[i].begin();
			iter_end = m_ObjLst[i].end();
			for (; iter_begin != iter_end;)
			{
				BB OBJ_BB = (*iter_begin)->Get_BB();

				if (player_BB.left > OBJ_BB.right || player_BB.right < OBJ_BB.left || player_BB.top < OBJ_BB.bottom || player_BB.bottom > OBJ_BB.top);
				else {
					if (OBJ_BB.bottom <= player_BB.top && (OBJ_BB.bottom + OBJ_BB.top) / 2 >= player_BB.top)
					{
						if (OBJ_BB.left <= player_BB.left && player_BB.left <= OBJ_BB.right)
						{
							cout << "Top Collide" << endl;
						}
						else if (OBJ_BB.left <= player_BB.right && player_BB.right <= OBJ_BB.right)
						{
							cout << "Top Collide" << endl;
						}
						else if (OBJ_BB.left >= player_BB.left && player_BB.right >= OBJ_BB.right)
						{
							cout << "Top Collide" << endl;
						}
					}

					else if (OBJ_BB.top >= player_BB.bottom && (OBJ_BB.bottom + OBJ_BB.top) / 2 <= player_BB.bottom)
					{
						if (OBJ_BB.left <= player_BB.left && player_BB.left <= OBJ_BB.right)
						{
							cout << "Bottom Collide" << endl;
						}
						else if (OBJ_BB.left <= player_BB.right && player_BB.right <= OBJ_BB.right)
						{
							cout << "Bottom Collide" << endl;
						}
						else if (OBJ_BB.left >= player_BB.left && player_BB.right >= OBJ_BB.right)
						{
							cout << "Bottom Collide" << endl;
						}
					}

					else if (OBJ_BB.right >= player_BB.left && (OBJ_BB.left + OBJ_BB.right) / 2 <= player_BB.left)
					{
						if (OBJ_BB.bottom <= player_BB.top && player_BB.top <= OBJ_BB.top)
						{
							cout << "left Collide" << endl;
						}
						else if (OBJ_BB.bottom <= player_BB.bottom && player_BB.bottom <= OBJ_BB.top)
						{
							cout << "left Collide" << endl;
						}
						else if (player_BB.bottom <= OBJ_BB.top && OBJ_BB.top <= player_BB.top)
						{
							cout << "left Collide" << endl;
						}
						else if (player_BB.bottom <= OBJ_BB.bottom && OBJ_BB.bottom <= player_BB.top)
						{
							cout << "left Collide" << endl;
						}
					}

					else if (OBJ_BB.left <= player_BB.right && (OBJ_BB.left + OBJ_BB.right) / 2 >= player_BB.right)
					{
						if (OBJ_BB.bottom <= player_BB.top && player_BB.top <= OBJ_BB.top)
						{
							cout << "right Collide" << endl;
						}
						else if (OBJ_BB.bottom <= player_BB.bottom && player_BB.bottom <= OBJ_BB.top)
						{
							cout << "right Collide" << endl;
						}
						else if (player_BB.bottom <= OBJ_BB.top && OBJ_BB.top <= player_BB.top)
						{
							cout << "right Collide" << endl;
						}
						else if (player_BB.bottom <= OBJ_BB.bottom && OBJ_BB.bottom <= player_BB.top)
						{
							cout << "right Collide" << endl;
						}
					}
				}
				++iter_begin;
			}
		}
	}
	else {
		CObj* player = m_ObjLst[OBJ_PLAYER2].front();
		BB player_BB = player->Get_BB();
		for (int i = OBJ_MONSTER1; i < OBJ_UI; ++i) {
			iter_begin = m_ObjLst[i].begin();
			iter_end = m_ObjLst[i].end();
			for (; iter_begin != iter_end;)
			{
				BB OBJ_BB = (*iter_begin)->Get_BB();

				if (player_BB.left > OBJ_BB.right || player_BB.right < OBJ_BB.left || player_BB.top < OBJ_BB.bottom || player_BB.bottom > OBJ_BB.top);
				else {
					//cout << "Collide" << endl;
					if (OBJ_BB.bottom <= player_BB.top && (OBJ_BB.bottom + OBJ_BB.top) / 2 >= player_BB.top)
					{
						if (OBJ_BB.left <= player_BB.left && player_BB.left <= OBJ_BB.right)
						{
							cout << "Top Collide" << endl;
						}
						else if (OBJ_BB.left <= player_BB.right && player_BB.right <= OBJ_BB.right)
						{
							cout << "Top Collide" << endl;
						}
						else if (OBJ_BB.left >= player_BB.left && player_BB.right >= OBJ_BB.right)
						{
							cout << "Top Collide" << endl;
						}
					}

					else if (OBJ_BB.top >= player_BB.bottom && (OBJ_BB.bottom + OBJ_BB.top) / 2 <= player_BB.bottom)
					{
						if (OBJ_BB.left <= player_BB.left && player_BB.left <= OBJ_BB.right)
						{
							cout << "Bottom Collide" << endl;
						}
						else if (OBJ_BB.left <= player_BB.right && player_BB.right <= OBJ_BB.right)
						{
							cout << "Bottom Collide" << endl;
						}
						else if (OBJ_BB.left >= player_BB.left && player_BB.right >= OBJ_BB.right)
						{
							cout << "Bottom Collide" << endl;
						}
					}

					else if (OBJ_BB.right >= player_BB.left && (OBJ_BB.left + OBJ_BB.right) / 2 <= player_BB.left)
					{
						if (OBJ_BB.bottom <= player_BB.top && player_BB.top <= OBJ_BB.top)
						{
							cout << "left Collide" << endl;
						}
						else if (OBJ_BB.bottom <= player_BB.bottom && player_BB.bottom <= OBJ_BB.top)
						{
							cout << "left Collide" << endl;
						}
						else if (player_BB.bottom <= OBJ_BB.top && OBJ_BB.top <= player_BB.top)
						{
							cout << "left Collide" << endl;
						}
						else if (player_BB.bottom <= OBJ_BB.bottom && OBJ_BB.bottom <= player_BB.top)
						{
							cout << "left Collide" << endl;
						}
					}

					else if (OBJ_BB.left <= player_BB.right && (OBJ_BB.left + OBJ_BB.right) / 2 >= player_BB.right)
					{
						if (OBJ_BB.bottom <= player_BB.top && player_BB.top <= OBJ_BB.top)
						{
							cout << "right Collide" << endl;
						}
						else if (OBJ_BB.bottom <= player_BB.bottom && player_BB.bottom <= OBJ_BB.top)
						{
							cout << "right Collide" << endl;
						}
						else if (player_BB.bottom <= OBJ_BB.top && OBJ_BB.top <= player_BB.top)
						{
							cout << "right Collide" << endl;
						}
						else if (player_BB.bottom <= OBJ_BB.bottom && OBJ_BB.bottom <= player_BB.top)
						{
							cout << "right Collide" << endl;
						}
					}
				}
				++iter_begin;
			}
		}
	}

	//Monster Map Collide
	list<CObj*>::iterator monster_iter_begin = m_ObjLst[OBJ_MONSTER1].begin();
	list<CObj*>::iterator monster_iter_end = m_ObjLst[OBJ_MONSTER1].end();
	for (; monster_iter_begin != monster_iter_end;) {
		BB monster_BB = (*monster_iter_begin)->Get_BB();

		iter_begin = m_ObjLst[OBJ_BOX].begin();
		iter_end = m_ObjLst[OBJ_BOX].end();
		for (; iter_begin != iter_end;)
		{
			BB OBJ_BB = (*iter_begin)->Get_BB();
			if (monster_BB.left <= OBJ_BB.right && monster_BB.right >= OBJ_BB.right)
			{
				if (OBJ_BB.bottom <= monster_BB.top && monster_BB.top <= OBJ_BB.top)
				{
					dynamic_cast<Monster*>((*monster_iter_begin))->GetDir() = 1;
				}
				else if (OBJ_BB.bottom <= monster_BB.bottom && monster_BB.bottom <= OBJ_BB.top)
				{
					dynamic_cast<Monster*>((*monster_iter_begin))->GetDir() = 1;
				}
				else if (monster_BB.bottom <= OBJ_BB.top && OBJ_BB.top <= monster_BB.top)
				{
					dynamic_cast<Monster*>((*monster_iter_begin))->GetDir() = 1;
				}
				else if (monster_BB.bottom <= OBJ_BB.bottom && OBJ_BB.bottom <= monster_BB.top)
				{
					dynamic_cast<Monster*>((*monster_iter_begin))->GetDir() = 1;
				}
			}
			else if (monster_BB.right >= OBJ_BB.left && monster_BB.left <= OBJ_BB.left)
			{
				if (OBJ_BB.bottom <= monster_BB.top && monster_BB.top <= OBJ_BB.top)
				{
					dynamic_cast<Monster*>((*monster_iter_begin))->GetDir() = -1;
				}
				else if (OBJ_BB.bottom <= monster_BB.bottom && monster_BB.bottom <= OBJ_BB.top)
				{
					dynamic_cast<Monster*>((*monster_iter_begin))->GetDir() = -1;
				}
				else if (monster_BB.bottom <= OBJ_BB.top && OBJ_BB.top <= monster_BB.top)
				{
					dynamic_cast<Monster*>((*monster_iter_begin))->GetDir() = -1;
				}
				else if (monster_BB.bottom <= OBJ_BB.bottom && OBJ_BB.bottom <= monster_BB.top)
				{
					dynamic_cast<Monster*>((*monster_iter_begin))->GetDir() = -1;
				}
			}
			++iter_begin;
		}
		++monster_iter_begin;
	}

	for (list<CObj*>::iterator iter_bullet = m_ObjLst[OBJ_BULLET].begin(); iter_bullet != m_ObjLst[OBJ_BULLET].end(); ++iter_bullet)
	{
		BB Bullet_BB = (*iter_bullet)->Get_BB();
		for (list<CObj*>::iterator iter_map = m_ObjLst[OBJ_MAP].begin(); iter_map != m_ObjLst[OBJ_MAP].end(); ++iter_map)
		{
			BB Map_BB = (*iter_map)->Get_BB();
			if (Bullet_BB.left > Map_BB.right || Bullet_BB.right < Map_BB.left || Bullet_BB.top < Map_BB.bottom || Bullet_BB.bottom > Map_BB.top);
			else
			{
				SafeDelete((*iter_bullet));
				iter_bullet = m_ObjLst[OBJ_BULLET].erase(iter_bullet);
				break;
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
