#pragma once

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

typedef struct BoundingBox
{
	GLfloat left;
	GLfloat right;
	GLfloat top;
	GLfloat down;
	GLfloat front;
	GLfloat back;
}BB;
