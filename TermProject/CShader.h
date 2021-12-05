#pragma once


class CShader
{
	DECLARE_SINGLETON(CShader)

public:
	static CShader* GetInstance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CShader;
		}
		return m_pInstance;
	}
	void DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static CShader* m_pInstance;

public:
	HRESULT Initialize_Shader(string strVertex, string strFragment);

private:
	char* FileToBuf(const char* file);
	HRESULT Create_VertexShader(string strVertexShader);
	HRESULT Create_FragmentShader(string strfragmentShader);

public:
	GLuint s_program;	
	GLchar* vertexsource, * fragmentsource; // 소스코드 저장 변수
	GLuint vertexshader, fragmentshader; // 세이더 객체

private:
	CShader();
	~CShader();



};
