#pragma once

class CShader
{
	DECLARE_SINGLETON(CShader)

private:
	CShader();
	~CShader();

public:
	HRESULT Add_Shader(string strTag, string strVertex, string strPixel);
	GLuint Use_Shader(string strTag);
	GLuint Get_CurrProgram();
	

private:
	GLuint m_iCurrProgram = -1;

private:
	char* FileToBuf(const char* file);
	HRESULT Create_VertexShader(SHADER* pShader, string strVertexShader);
	HRESULT Create_FragmentShader(SHADER* pShader, string strfragmentShader);

private:
	map<string, SHADER*> m_mapShader;





};
