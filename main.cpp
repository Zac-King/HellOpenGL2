#include <GL\glew.h>
#include <GL\wglew.h>
#include <GLFW\glfw3.h>
//#include "Vector3.h"
#include "crenderutils.h"

#define S_W 1280
#define S_H 720

int main()
{
	if (!glfwInit()) return -1;
	GLFWwindow* window;

	window = glfwCreateWindow(S_W, S_H, "Hello World", NULL, NULL);
	if (!window) { glfwTerminate(); return -1; }
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) { glfwTerminate(); return -1; }
	////////////////////////////////////////////////////////////////////////
	auto major = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR);
	auto minor = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR);
	auto revision = glfwGetWindowAttrib(window, GLFW_CONTEXT_REVISION);
	printf("GL %i.%i.%i\n", major, minor, revision);
	////////////////////////////////////////////////////////////////////////


	Vertex verts[3] = { { { 0, 30, 0, 1},
						  { 0, 1, 1, 1 } },
					    { { -30, -30, 0, 1 }, 
						  { 1, 1, 0, 1 } },					   
						{ { 30, -30, 0, 1 },
						  { 1, 0, 1, 1 } } };

	Triangle tris[1] = { 0, 1, 2 };
	


	RenderObject ro = loadMesh(verts, 3, tris, 1);
	//create shader program
	GLuint shader = CreateProgram("./shaders/simpleShader.vert",
								  "./shaders/simpleShader.frag");

	mat4 model = {1,0,0,0,
	              0,1,0,0,
				  0,0,1,0,
	              0,0,0,1};

	mat4 model2 = { 1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1 };



	mat4 view  = { 1, 0, 0, 0,
				   0, 1, 0, 0,
				   0, 0, 1, 0,
				   0, 0, 0, 1 };

	model.v[3].x = S_W / 2;
	model.v[3].y = S_H / 2;
	model.v[3].z = 0;
	model.v[3].w = 1;

	model2.v[3].x = 0;
	model2.v[3].y = 60;
	model2.v[3].z = 0;
	model2.v[3].w = 1;

	mat4 ortho = getOrtho(0, S_W, 0, S_H, 0, 100);

	glUseProgram(shader);
	GLuint ul_proj  = glGetUniformLocation(shader, "Projection");
	GLuint ul_view  = glGetUniformLocation(shader, "View");
	GLuint ul_model = glGetUniformLocation(shader, "Model");
		
	glUniformMatrix4fv(ul_proj, 1, GL_FALSE, ortho.m);
	glUniformMatrix4fv(ul_view, 1, GL_FALSE, view.m);
	glUniformMatrix4fv(ul_model, 1, GL_FALSE, model.m);

	float a = 0.707;
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (glfwGetKey(window, GLFW_KEY_W))
			model.v[3].y += 3;
		if (glfwGetKey(window, GLFW_KEY_S))
			model.v[3].y -= 3;
		if (glfwGetKey(window, GLFW_KEY_A))
			model.v[3].x -= 3;
		if (glfwGetKey(window, GLFW_KEY_D))
			model.v[3].x += 3;
		
		if (glfwGetKey(window, GLFW_KEY_Q))
			a += 0.20f;
		if (glfwGetKey(window, GLFW_KEY_E))
			a -= 0.20f;
		// Model2 is being used as a translation matrix
		// rotation is recreated each loop		
		mat4 rotation = { cos(a), sin(a), 0, 0,
						 -sin(a), cos(a), 0, 0,
							   0,	   0, 1, 0,
							   0,	   0, 0, 1 };


		mat4 orbitor = mul(model2,mul(rotation, model));

		glUseProgram(shader);
		glUniformMatrix4fv(ul_model, 1, GL_FALSE, model.m);
		drawRenderObject(ro,shader);				

		glUseProgram(shader);
		glUniformMatrix4fv(ul_model, 1, GL_FALSE, orbitor.m);
		drawRenderObject(ro, shader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}