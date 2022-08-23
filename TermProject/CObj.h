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
	virtual GLvoid Render();
	BB& Get_BB() { return m_Box; }
	BoundingBox& Get_AABB() { return m_AABB; }

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
	BB m_Box;
	BoundingBox m_AABB {};

protected:
	GLvoid Release();
};

