#include "stdafx.h"
#include "CObj.h"

#include "CGameManager.h"
#include "CKeyManager.h"
#include "CRenderManager.h"
#include "CSceneManager.h"
#include "CShader.h"
#include "CFrameManager.h"
#include "CSoundManager.h"
#include "CCamera.h"

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

	for (size_t i = 0; i < m_AABB.GetCornersBox().size(); ++i) {
		m_vecAABBColor.push_back(glm::vec3(1.f, 0.f, 0.f));
	}

	glGenVertexArrays(1, &m_iVao);
	glGenBuffers(2, m_iVbo);

	glBindVertexArray(m_iVao);

	glBindBuffer(GL_ARRAY_BUFFER, m_iVbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_AABB.GetCornersBox().size(), &m_AABB.GetCornersBox().front(), GL_STATIC_DRAW);

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

	m_AABB.Update(m_AABB.GetCorners()[0], m_AABB.GetCorners()[7]);

	return GLvoid();
}

GLvoid CObj::UpdateAABB(const glm::mat4& mat, const glm::vec3& Scale, const glm::vec3& Rotate, const glm::vec3& Translation)
{
	m_AABB.Transform(mat, Scale, Rotate, Translation);

	m_AABB.Update(m_AABB.GetCorners()[5], m_AABB.GetCorners()[3]);

	return GLvoid();
}

GLvoid CObj::Render()
{
	if (m_pGameMgr->Get_DebugMode()) {
		GLuint program = CShader::GetInstance()->Use_Shader("BoundingBox");

		int viewLoc = glGetUniformLocation(program, "viewTransform");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(m_pGameMgr->Get_Camera()->Get_View()));

		if (m_pGameMgr->Get_View() == true && !m_pGameMgr->Get_Camera()->Get_MovingCam())
		{
			int ProjLoc = glGetUniformLocation(program, "projectionTransform");// 직각
			glUniformMatrix4fv(ProjLoc, 1, GL_FALSE, value_ptr(m_pGameMgr->Get_Camera()->Get_Ortho()));
		}
		else
		{
			int ProjLoc = glGetUniformLocation(program, "projectionTransform"); //원근
			glUniformMatrix4fv(ProjLoc, 1, GL_FALSE, value_ptr(m_pGameMgr->Get_Camera()->Get_Perspective()));
		}

		GLuint iLocation = glGetUniformLocation(program, "modelTransform");
		glUniformMatrix4fv(iLocation, 1, GL_FALSE, value_ptr(m_AABB.TransMatrix));

		for (int i = 0; i < 2; ++i)
		{
			glEnableVertexAttribArray(i);
			glBindBuffer(GL_ARRAY_BUFFER, m_iVbo[i]);
			glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		}

		glLineWidth(3.0f);

		glDrawArrays(GL_LINE_LOOP, 0, 4);
		glDrawArrays(GL_LINE_LOOP, 4, 4);
		glDrawArrays(GL_LINE_LOOP, 8, 4);
		glDrawArrays(GL_LINE_LOOP, 16, 4);
		glDrawArrays(GL_LINE_LOOP, 20, 4);
		glDrawArrays(GL_LINE_LOOP, 24, 4);


		for (int i = 0; i < 2; ++i)
			glDisableVertexAttribArray(i);

	}

	return GLvoid();
}

GLvoid CObj::Release()
{
	return GLvoid();
}
