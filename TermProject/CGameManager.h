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
	bool& Get_boolPortal() { return bPortalCollide; };
	bool& Get_CollideMTP() { return bMonsterPlayerCollide; };
	bool Get_View() { return m_bView; };
	list<CObj*>& Get_Obj(OBJ_ID ID) { return m_ObjLst[static_cast<int>(ID)]; };

public:
	HRESULT Add_Camera(CCamera* pCamera);
	HRESULT Delete_Camera();
	GLvoid Render_Camera();
	GLvoid init();
	CCamera* Get_Camera() { return m_pCamera; };
	
	
	bool Collide(DIR dir);		// using in Player.cpp
	bool JumpCollide(int num);
	bool bPortalCollide = false;
	bool bMonsterPlayerCollide = false;

private:
	GLvoid CheckViewChange();
	GLvoid ChangeView();
	GLvoid CheckCollide();		// Collide Check
	GLvoid MonMapCollide();		// Monster - Map Collide Check
	GLvoid MonBulletCollide();	// Monster - Bullet Collide Check
	GLvoid MonPlayerCollide();	// Monster - Player Collide Check
	GLvoid PortalInteract();	// Portal - Player Interact

private:
	CCamera* m_pCamera = nullptr;
	list<CObj*> m_ObjLst[static_cast<int>(OBJ_ID::OBJ_END)];

private:
	bool m_bView = true;

};

