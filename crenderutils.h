#include <GL\glew.h>
#include <GL\wglew.h>
#include <GLFW\glfw3.h>

#include <cassert>
#include <fstream>
#include <string>
#include <sstream>


union vec4 { float v[4]; struct  { float x, y, z, w; }; };
union mat4 { float m[16]; float mm[4][4]; vec4 v[4]; };

mat4 mul(mat4 a, mat4 b);
//mat4 mul(mat4 a, vec4 b);

struct Vertex { vec4 position; vec4 color; }; //

struct Triangle { unsigned v[3]; }; // 12 bytes

struct RenderObject
{
	unsigned VBO, IBO, VAO, size;
};


RenderObject loadMesh(Vertex *verts, unsigned nverts,
					  Triangle *tris, unsigned ntris);

void drawRenderObject(RenderObject ro, unsigned shader);





/*

*/

GLuint CreateProgram(const char *a_vertex, const char *a_frag);

mat4 getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar);



