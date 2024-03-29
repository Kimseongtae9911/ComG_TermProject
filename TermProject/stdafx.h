#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#include <list>
#include <map>
#include <vector>
#include <time.h>
#include <Windows.h>
#include <math.h>
#include <random>
#include <algorithm>
#include <deque>
#include <unordered_map>
#include <unordered_set>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>

#include <io.h>
#include "fmod.h"
#include "fmod.hpp"
#include "fmod_dsp.h"
#include "fmod_errors.h"

#define WINCX 1280
#define WINCY 640
#define MAX_VKEY 0xff
#define PI 3.141592658979f
#define EPSILON	1.0e-6f

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


static float ToRadian(float degree) { return degree * PI / 180.f; }

inline bool IsZero(float fValue) { return((fabsf(fValue) < EPSILON)); }
inline bool IsEqual(float fA, float fB) { return(::IsZero(fA - fB)); }

struct Vector2
{
	int x;
	int y;

	Vector2()
	{
		x = 0;
		y = 0;
	}

	Vector2(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};

// Include
#include "Enum.h"
#include "Struct.h"