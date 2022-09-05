#pragma once

class CRenderManager;
class CKeyManager;
class CGameManager;
class CSceneManager;
class CShader;
class CSoundManager;

class CObj
{
public:
	CObj();
	~CObj();

public:
	virtual HRESULT Initialize();
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid UpdateAABB(const glm::mat4& mat);
	virtual GLvoid UpdateAABB(const glm::mat4& mat, const glm::vec3& Scale, const glm::vec3& Rotate, const glm::vec3& Translation);
	virtual GLvoid Render();
	BoundingBox& Get_AABB() { return m_AABB; }
	GLvoid Set_OBJID(OBJ_ID id) { m_idObj = id; }

private:
	GLuint m_iVao, m_iVbo[2];
	vector<glm::vec3> m_vecAABBColor;
	

protected:
	CRenderManager* m_pRender = nullptr;
	CKeyManager* m_pKeyMgr = nullptr;
	CGameManager* m_pGameMgr = nullptr;
	CSceneManager* m_pSceneMgr = nullptr;
	CShader* m_pShaderLoader = nullptr;
	CSoundManager* m_pSoundMgr = nullptr;
	OBJ_ID m_idObj;

	vector<glm::vec3> m_vecMAABBColor;
	GLuint m_Vao[4], m_Vbo[4][2];
	BoundingBox m_AABB_M[4]{};
	BoundingBox m_AABB{};

protected:
	GLvoid Release();
};

