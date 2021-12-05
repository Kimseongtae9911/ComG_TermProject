#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>

#include <list>
#include <map>
#include <vector>
#include <time.h>
#include <Windows.h>
#include <math.h>
#include <random>


// Include
#include "Enum.h"

using namespace std;





#define WINCX 1280
#define WINCY 720
#define MAX_VKEY 0xff


typedef struct tagShader
{
public:
	tagShader() { memset(this, 0, sizeof(tagShader)); }
	GLuint program;
	GLchar* vertexsource;
	GLchar* fragmentsource;
	GLuint vertexshader;
	GLuint fragmentshader;
}SHADER;

typedef struct tagTexture
{
public:
	tagTexture() { memset(this, 0, sizeof(tagTexture)); }
	GLuint id;
	GLint width;
	GLint height;
	GLint nrChannels;
}TEXTURE;

class CTexture;
typedef struct tagMaterial
{
	GLchar name[256] = "";
	GLint illum;
	string map_Kd = "";
	GLfloat Ns;
	GLfloat Ni;
	GLfloat d;
	GLfloat Ka[3];
	GLfloat Kd[3];
	GLfloat Ks[3];
	GLfloat Tf[3];
	CTexture* texture;
}MATERIAL;

typedef struct tagSubMesh
{
	GLchar name[256] = "";
	GLchar matname[256] = "";
	GLuint vao = 0;
	GLuint vbo[4] = {};
	vector<GLint> indices[4];
	vector<glm::vec3> vertex;
	vector<glm::vec2> texcoord;
	vector<glm::vec3> normal;
	vector<glm::vec4> color;
	MATERIAL* material;
}SUBMESH;


template <typename T>
void SafeDelete(T& ptr)
{
	if (ptr != nullptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}

template <typename T>
void SafeDelete_Array(T& ptr)
{
	if (ptr)
	{
		delete[] ptr;
		ptr = nullptr;
	}
}

#define NO_COPY(ClassName)						\
private:										\
	ClassName(const ClassName& Obj);			\
	ClassName& operator=(const ClassName& Obj);

#define DECLARE_SINGLETON(ClassName)		\
		NO_COPY(ClassName)					\
public:										\
	static ClassName* GetInstance()			\
	{										\
		if(nullptr == m_pInstance)			\
		{									\
			m_pInstance = new ClassName;	\
		}									\
		return m_pInstance;					\
	}										\
	void DestroyInstance()					\
	{										\
		if(m_pInstance)						\
		{									\
			delete m_pInstance;				\
			m_pInstance = nullptr;			\
		}									\
	}										\
private:									\
	static ClassName*	m_pInstance;

#define IMPLEMENT_SINGLETON(ClassName)		\
ClassName* ClassName::m_pInstance = nullptr;


