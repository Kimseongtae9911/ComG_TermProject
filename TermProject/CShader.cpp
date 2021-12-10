#include "stdafx.h"
#include "CShader.h"

IMPLEMENT_SINGLETON(CShader)

CShader::CShader()
{
}


CShader::~CShader()
{
}

HRESULT CShader::Add_Shader(string strTag, string strVertex, string strPixel)
{
	SHADER* pShader = new SHADER;

	if (FAILED(Create_VertexShader(pShader, strVertex)))
	{
		SafeDelete(pShader);
		return E_FAIL;
	}

	if (FAILED(Create_FragmentShader(pShader, strPixel)))
	{
		SafeDelete(pShader);
		return E_FAIL;
	}

	pShader->program = glCreateProgram();
	glAttachShader(pShader->program, pShader->vertexshader);
	glAttachShader(pShader->program, pShader->fragmentshader);
	glLinkProgram(pShader->program);

	glDeleteShader(pShader->vertexshader);
	glDeleteShader(pShader->fragmentshader);

	glUseProgram(pShader->program);

	m_mapShader.insert({ strTag, pShader });

	return NOERROR;
}

GLuint CShader::Use_Shader(string strTag)
{
	auto iter_find = m_mapShader.find(strTag);

	if (iter_find == m_mapShader.end())
	{
		m_iCurrProgram = -1;
		cout << "ERROR : failed to find shader" << endl;
		return E_FAIL;
	}

	m_iCurrProgram = iter_find->second->program;
	glUseProgram(m_iCurrProgram);

	return m_iCurrProgram;
}

GLuint CShader::Get_CurrProgram()
{
	return m_iCurrProgram;
}


char* CShader::FileToBuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fopen_s(&fptr, file, "rb"); // Open file for reading
	if (!fptr) // Return NULL on failure
		return NULL;
	fseek(fptr, 0, SEEK_END); // Seek to the end of the file
	length = ftell(fptr); // Find out how many bytes into the file we are
	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator
	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file
	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer
	fclose(fptr); // Close the file
	buf[length] = 0; // Null terminator
	return buf; // Return the buffer
}

HRESULT CShader::Create_VertexShader(SHADER* pShader, string strVertexShader)
{
	if (pShader == nullptr)
		return E_FAIL;

	pShader->vertexsource = FileToBuf(strVertexShader.c_str());
	//--- 버텍스 세이더 객체 만들기
	pShader->vertexshader = glCreateShader(GL_VERTEX_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(pShader->vertexshader, 1, (const GLchar**)&pShader->vertexsource, 0);
	//--- 버텍스 세이더 컴파일하기
	glCompileShader(pShader->vertexshader);
	//--- 컴파일이 제대로 되지 않은 경우: 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(pShader->vertexshader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(pShader->vertexshader, 512, NULL, errorLog);
		cerr << "ERROR : vertex shader compile failed\n" << errorLog << endl;
		return E_FAIL;
	}

	return NOERROR;
}

HRESULT CShader::Create_FragmentShader(SHADER* pShader, string strfragmentShader)
{
	if (pShader == nullptr)
		return E_FAIL;

	pShader->fragmentsource = FileToBuf(strfragmentShader.c_str());
	//--- 프래그먼트 세이더 객체 만들기
	pShader->fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(pShader->fragmentshader, 1, (const GLchar**)&pShader->fragmentsource, 0);
	//--- 프래그먼트 세이더 컴파일
	glCompileShader(pShader->fragmentshader);
	//--- 컴파일이 제대로 되지 않은 경우: 컴파일 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(pShader->fragmentshader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(pShader->fragmentshader, 512, NULL, errorLog);
		cerr << "ERROR: fragment shader compile failed\n" << errorLog << endl;
		return E_FAIL;
	}

	return NOERROR;
}
