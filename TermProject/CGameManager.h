#pragma once
class CObj;
class CCamera;
class CKeyManager;

class CGameManager
{
	DECLARE_SINGLETON(CGameManager)

private:
	CGameManager();
	~CGameManager();

public:
	HRESULT Add_GameObj(OBJ_ID eID, CObj* pObj);
	GLvoid Update(const GLfloat fTimeDelta);
	HRESULT Clear_ObjList();
	HRESULT Clear_Obj(OBJ_ID eID);

public:
	VIEW Get_View() { return m_View; }
	list<CObj*>& Get_Obj(OBJ_ID ID) { return m_ObjLst[static_cast<int>(ID)]; }

	bool Get_PlayerDie() { return m_bPlayerDie; }
	void Set_PlayerDie(bool die) { m_bPlayerDie = die; }

public:
	HRESULT Add_Camera(CCamera* pCamera);
	HRESULT Delete_Camera();
	GLvoid Render_Camera();
	GLvoid init();
	CCamera* Get_Camera() { return m_pCamera; }

	GLvoid Set_DebugMode(bool mode) { m_bDebug = mode; }
	bool Get_DebugMode() { return m_bDebug; }

	bool Collide(DIR dir);		// using in Player.cpp
	bool JumpCollide(int num);

private:
	GLvoid CheckViewChange();
	GLvoid ChangeView();
	GLvoid CheckCollide();		// Collide Check
	GLvoid MonMapCollide();		// Monster - Map Collide Check
	GLvoid MonBulletCollide();	// Monster - Bullet Collide Check	

private:
	CCamera* m_pCamera = nullptr;
	list<CObj*> m_ObjLst[static_cast<int>(OBJ_ID::OBJ_END)];

private:
	VIEW m_View = VIEW::VIEW_2D;
	bool m_bDebug = false;
	bool m_bPlayerDie = false;
};

