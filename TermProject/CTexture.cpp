#include "stdafx.h"
#include "CTexture.h"
#include"CShader.h"

#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"

CTexture::CTexture()
{
}

CTexture::~CTexture()
{
}

HRESULT CTexture::Initialize(string strTag, string strPath, bool bAl)
{
	if (strPath == "")
		return E_FAIL;

	bAlpha = bAl;

	glGenTextures(1, &m_iID);
	glBindTexture(GL_TEXTURE_2D, m_iID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data = stbi_load(strPath.c_str(), &m_iWidth, &m_iHeight, &m_iChannels, 0);

	if (data == nullptr)
	{
		cout << "ERROR : Failed to load texture" << endl;
		return E_FAIL;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_iWidth, m_iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	//glActiveTexture(GL_TEXTURE0); //

	return NOERROR;
}

GLvoid CTexture::Render()
{
	GLuint iLocation = glGetUniformLocation(CShader::GetInstance()->Get_CurrProgram(), "outTexture");  
	glUniform1i(iLocation, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_iID);	

	return GLvoid();
}

GLvoid CTexture::Release()
{
	return GLvoid();
}

CTexture* CTexture::Create(string strTag, string strPath, bool bAlpha)
{
	CTexture* pInstance = new CTexture;

	if (FAILED(pInstance->Initialize(strTag, strPath, bAlpha)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
