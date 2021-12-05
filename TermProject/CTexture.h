#pragma once

class CTexture 
{
public:
	CTexture();
	~CTexture();

public:
	const GLint Get_Width() { return m_iWidth; }
	const GLint Get_Height() { return m_iHeight; }
	bool& Get_bAlpha() { return bAlpha; }


public:
	virtual HRESULT Initialize(string strTag, string strPath, bool bAlpha);
	virtual GLvoid Render();

private:
	GLuint m_iID;
	GLint m_iWidth;
	GLint m_iHeight;
	GLint m_iChannels;
	bool bAlpha;



private:
	GLvoid Release();

public:
	static CTexture* Create(string strTag, string strPath, bool bAlpha = true);
};

