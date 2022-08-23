#include "stdafx.h"
#include "CObj.h"

#include "CGameManager.h"
#include "CKeyManager.h"
#include "CRenderManager.h"
#include "CSceneManager.h"
#include "CShader.h"
#include "CFrameManager.h"
#include "CSoundManager.h"

CObj::CObj()
{
}

CObj::~CObj()
{
}

HRESULT CObj::Initialize()
{
	m_pGameMgr = CGameManager::GetInstance();
	m_pRender = CRenderManager::GetInstance();
	m_pSceneMgr = CSceneManager::GetInstance();
	m_pKeyMgr = CKeyManager::GetInstance();
	m_pShaderLoader = CShader::GetInstance();
	m_pSoundMgr = CSoundManager::GetInstance();

	for (int i = 0; i < m_AABB.GetCorners().size(); ++i) {
		m_vecAABBColor.push_back(glm::vec3(255.f, 0.f, 0.f));
	}

	glGenVertexArrays(1, &m_iVao);
	glGenBuffers(2, m_iVbo);

	glBindVertexArray(m_iVao);

	glBindBuffer(GL_ARRAY_BUFFER, m_iVbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_AABB.GetCorners().size(), &m_AABB.GetCorners().front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_iVbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_vecAABBColor.size(), &m_vecAABBColor.front(), GL_STATIC_DRAW);

	return NOERROR;
}

GLint CObj::Update(const GLfloat fTimeDelta)
{
	return GLint();
}

GLvoid CObj::UpdateAABB(const glm::mat4& mat)
{
	m_AABB.Transform(mat);

	return GLvoid();
}

GLvoid CObj::Render()
{
	GLuint program = CShader::GetInstance()->Use_Shader("BoundingBox");

	GLuint iLocation = glGetUniformLocation(program, "modelTransform");
	glUniformMatrix4fv(iLocation, 1, GL_FALSE, value_ptr(m_AABB.TransMatrix));

	for (int i = 0; i < 2; ++i)
	{
		glEnableVertexAttribArray(i);
		glBindBuffer(GL_ARRAY_BUFFER, m_iVbo[i]);
		glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

	glDrawArrays(GL_TRIANGLES, 0, m_AABB.GetCorners().size());

	for (int i = 0; i < 2; ++i)
		glDisableVertexAttribArray(i);
	

	return GLvoid();
}

GLvoid CObj::Release()
{
	return GLvoid();
}
