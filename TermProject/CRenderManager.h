#pragma once

class CObj;
class CRenderManager
{
	DECLARE_SINGLETON(CRenderManager)

private:
	CRenderManager();
	~CRenderManager();

public:
	GLvoid Render_Object();

public:
	HRESULT Add_RenderObj(RENDER_ID eID, CObj* pObj);
	GLvoid Clear_Renderer();
	list<CObj*>& Get_RenderObj(RENDER_ID ID) { return m_lstRenderObj[ID]; };

private:
	list<CObj*> m_lstRenderObj[RENDER_END];
};