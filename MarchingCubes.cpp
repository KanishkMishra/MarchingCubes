// Kanishk Mishra
// Assignment 5: Marcging Cubes
// 251173609

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <fstream>

#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <iostream>
#include <vector>

#include "TriTable.hpp"

#define F_TOP_LEFT     128
#define F_TOP_RIGHT    64
#define F_BOTTOM_RIGHT 4
#define F_BOTTOM_LEFT  8
#define H_TOP_LEFT     16
#define H_TOP_RIGHT    32
#define H_BOTTOM_RIGHT 2
#define H_BOTTOM_LEFT  1


typedef float (*scalar_field_3d)(float, float, float);


float hills(float x, float y, float z)
{
	return y - sin(x)*cos(z);
}

float cone(float x, float y, float z)
{
	return x*x - y*y - z*z - z;
}

float sphere(float x, float y, float z)
{
	return x*x + y*y + z*z;
}

// marching cubes algorithm
std::vector<float> marching_cubes(scalar_field_3d f, float isovalue, float min, float max, float stepsize)
{
	std::vector<float> vertices;

	float ftl, ftr, fbr, fbl, htl, htr, hbr, hbl;
	int which = 0;
	int* verts;

	// check all notable x, y, z valus between min and max
	for (float z = min; z < max; z += stepsize)
	{
		for (float y = min; y < max; y += stepsize)
		{
			for (float x = min; x < max; x += stepsize)
			{
				// test the cube
				ftl = (*f)(x, y+stepsize, z+stepsize);
				ftr = (*f)(x+stepsize, y+stepsize, z+stepsize);
				fbr = (*f)(x+stepsize, y, z+stepsize);
				fbl = (*f)(x, y, z+stepsize);
				htl = (*f)(x, y+stepsize, z);
				htr = (*f)(x+stepsize, y+stepsize, z);
				hbr = (*f)(x+stepsize, y, z);
				hbl = (*f)(x, y, z);

				which = 0;
				if (htl < isovalue)
					which |= H_TOP_LEFT;
				if (htr < isovalue)
					which |= H_TOP_RIGHT;
				if (hbr < isovalue)
					which |= H_BOTTOM_RIGHT;
				if (hbl < isovalue)
					which |= H_BOTTOM_LEFT;
				if (ftl < isovalue)
					which |= F_TOP_LEFT;
				if (ftr < isovalue)
					which |= F_TOP_RIGHT;
				if (fbr < isovalue)
					which |= F_BOTTOM_RIGHT;
				if (fbl < isovalue)
					which |= F_BOTTOM_LEFT;

				// store vertices
				verts = marching_cubes_lut[which];

				if (verts[0] >= 0) 
				{
					//printf("%i %f %f %f\n", which, x, y, z);
					vertices.emplace_back(x+stepsize*vertTable[verts[0]][0]);
					vertices.emplace_back(y+stepsize*vertTable[verts[0]][1]);
					vertices.emplace_back(z+stepsize*vertTable[verts[0]][2]);

					vertices.emplace_back(x+stepsize*vertTable[verts[1]][0]);
					vertices.emplace_back(y+stepsize*vertTable[verts[1]][1]);
					vertices.emplace_back(z+stepsize*vertTable[verts[1]][2]);

					vertices.emplace_back(x+stepsize*vertTable[verts[2]][0]);
					vertices.emplace_back(y+stepsize*vertTable[verts[2]][1]);
					vertices.emplace_back(z+stepsize*vertTable[verts[2]][2]);
				}

				if (verts[3] >= 0) 
				{
					vertices.emplace_back(x+stepsize*vertTable[verts[3]][0]);
					vertices.emplace_back(y+stepsize*vertTable[verts[3]][1]);
					vertices.emplace_back(z+stepsize*vertTable[verts[3]][2]);

					vertices.emplace_back(x+stepsize*vertTable[verts[4]][0]);
					vertices.emplace_back(y+stepsize*vertTable[verts[4]][1]);
					vertices.emplace_back(z+stepsize*vertTable[verts[4]][2]);
					
					vertices.emplace_back(x+stepsize*vertTable[verts[5]][0]);
					vertices.emplace_back(y+stepsize*vertTable[verts[5]][1]);
					vertices.emplace_back(z+stepsize*vertTable[verts[5]][2]);
				}

				if (verts[6] >= 0) 
				{
					vertices.emplace_back(x+stepsize*vertTable[verts[6]][0]);
					vertices.emplace_back(y+stepsize*vertTable[verts[6]][1]);
					vertices.emplace_back(z+stepsize*vertTable[verts[6]][2]);
					
					vertices.emplace_back(x+stepsize*vertTable[verts[7]][0]);
					vertices.emplace_back(y+stepsize*vertTable[verts[7]][1]);
					vertices.emplace_back(z+stepsize*vertTable[verts[7]][2]);

					vertices.emplace_back(x+stepsize*vertTable[verts[8]][0]);
					vertices.emplace_back(y+stepsize*vertTable[verts[8]][1]);
					vertices.emplace_back(z+stepsize*vertTable[verts[8]][2]);
				}

				if (verts[9] >= 0) 
				{
					vertices.emplace_back(x+stepsize*vertTable[verts[9]][0]);
					vertices.emplace_back(y+stepsize*vertTable[verts[9]][1]);
					vertices.emplace_back(z+stepsize*vertTable[verts[9]][2]);

					vertices.emplace_back(x+stepsize*vertTable[verts[10]][0]);
					vertices.emplace_back(y+stepsize*vertTable[verts[10]][1]);
					vertices.emplace_back(z+stepsize*vertTable[verts[10]][2]);
					
					vertices.emplace_back(x+stepsize*vertTable[verts[11]][0]);
					vertices.emplace_back(y+stepsize*vertTable[verts[11]][1]);
					vertices.emplace_back(z+stepsize*vertTable[verts[11]][2]);
				}

				if (verts[12] >= 0) 
				{
					vertices.emplace_back(x+stepsize*vertTable[verts[12]][0]);
					vertices.emplace_back(y+stepsize*vertTable[verts[12]][1]);
					vertices.emplace_back(z+stepsize*vertTable[verts[12]][2]);
					
					vertices.emplace_back(x+stepsize*vertTable[verts[13]][0]);
					vertices.emplace_back(y+stepsize*vertTable[verts[13]][1]);
					vertices.emplace_back(z+stepsize*vertTable[verts[13]][2]);

					vertices.emplace_back(x+stepsize*vertTable[verts[14]][0]);
					vertices.emplace_back(y+stepsize*vertTable[verts[14]][1]);
					vertices.emplace_back(z+stepsize*vertTable[verts[14]][2]);
				}
			}
		}
	}

	return vertices;
}

// determine the normals of all vertices
std::vector<float> compute_normals(std::vector<float> vertices)
{
	std::vector<float> normals;

	for (int i = 0; i < vertices.size(); i += 9)
	{
		// find vectors
		glm::vec3 v1, v2;

		v1.x = vertices[3*1 + i] - vertices[i];
		v1.y = vertices[3*1 + (i+1)] - vertices[i+1]; 
		v1.z = vertices[3*1 + (i+2)] - vertices[i+2]; 

		v2.x = vertices[3*2 + i] - vertices[i];
		v2.y = vertices[3*2 + (i+1)] - vertices[i+1]; 
		v2.z = vertices[3*2 + (i+2)] - vertices[i+2]; 

		// find normalized normal
		glm::vec3 v3 = normalize(cross(v1, v2));

		// store normals (once for each vertex)
		for (int j = 0; j < 3; j++)
		{
			normals.emplace_back(v3.x);
			normals.emplace_back(v3.y);
			normals.emplace_back(v3.z);
		}
	}

	return normals;
}

// Create valid .ply file containing all information
void writePly(std::vector<float> vertices, std::vector<float> normals, std::string fileName)
{
	// write simple header
	std::ofstream PLYfile(fileName+".ply");
	PLYfile << "ply\n";
	PLYfile << "element vertex " << vertices.size()/3 <<"\n";
	PLYfile << "property float x\n";
	PLYfile << "property float y\n";
	PLYfile << "property float z\n";
	PLYfile << "property float nx\n";
	PLYfile << "property float ny\n";
	PLYfile << "property float nz\n";
	PLYfile << "element faces " << vertices.size()/9 <<"\n";
	PLYfile << "end_header\n";

	// write in vertices
	for (int i = 0; i < vertices.size(); i += 3)
	{
		PLYfile << vertices[i] << " " << vertices[i+1] << " " << vertices[i+2] << " " << normals[i] << " " << normals[i+1] << " " << normals[i+2] << "\n";
	}

	// write in faces
	for (int i = 0; (i+2) < vertices.size()/3; i += 3)
	{
		PLYfile << "3 " << i << " " << i+1 << " " << i+2 << "\n";
	}
}

// move camera back and forth using arrow keys and mouse
void cameraControls(glm::vec3& eye, float& yaw, float& pitch, float& r, bool& hold, float& lastX, float& lastY)
{
	// fixed values
	const float speed = 0.03f;
	double xPos = 0, yPos = 0;
	glfwGetCursorPos(window, &xPos, &yPos);

	// determine input
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && r >= 0)
        r -= speed * r;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        r += speed * r;
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// check if click and hold
		if (hold)
		{
			const float sensitivity = glm::radians(0.5f);

			float xOffset = lastX - (float)xPos;
			float yOffset = lastY - (float)yPos;

			xOffset *= sensitivity;
			yOffset *= sensitivity;

			yaw -= yOffset;
			pitch += xOffset;
		}

		// update last mouse position
		lastX = xPos;
		lastY = yPos;

		hold = true;
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		hold = false;

	
	// set new position
	eye.x = r*cos(yaw)*sin(pitch);
	eye.y = r*sin(yaw)*sin(pitch);
	eye.z = r*cos(pitch);
}

//////////////////////////////////////////////////////////////////////////////
// Main
//////////////////////////////////////////////////////////////////////////////

int main( int argc, char* argv[])
{

	///////////////////////////////////////////////////////
	float screenW = 800;
	float screenH = 800;
	float stepsize = 0.1f;

	float min = -5.0f;
	float max = 5.0f;
	float isoval = 1;

	std::string fileName = "marching";

	if (argc > 1 ) {
		screenW = atoi(argv[1]);
	}
	if (argc > 2) {
		screenH = atoi(argv[2]);
	}
	if (argc > 3) {
		stepsize = atof(argv[3]);
	}
	if (argc > 4) {
		min = atof(argv[4]);
	}
	if (argc > 5) {
		max = atof(argv[5]);
	}
	if (argc > 6) {
		isoval = atof(argv[6]);
	}
	if (argc > 7) {
		fileName = argv[7];
	}

	///////////////////////////////////////////////////////

	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( screenW, screenH, "Marching Cubes", NULL, NULL);
	if( window == NULL ){
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}


	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_CURSOR, GL_TRUE);
	glfwPollEvents();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Dark blue background
	glClearColor(0.2f, 0.2f, 0.3f, 0.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(min, max, min, max, -1, 1);

	// Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    std::string VertexShaderCode = "\
    	#version 400\n\
		layout(location = 0) in vec3 vertexPos;\n\
		layout(location = 1) in vec3 normal;\n\
		out vec3 normal_out;\n\
		out vec3 eye_direction;\n\
		out vec3 light_direction;\n\
		uniform mat4 MVP;\n\
		uniform mat4 V;\n\
		uniform vec3 LightDir;\n\
		void main(){\n\
			gl_Position = MVP * vec4(vertexPos, 1);\n\
			eye_direction = vec3(5.0,5.0,5.0);\n\
			normal_out = normal;\n\
			light_direction = LightDir;\n\
		}\n";

    std::string FragmentShaderCode = "\
		#version 400\n\
		in vec3 normal_out;\n\
		in vec3 eye_direction;\n\
		in vec3 light_direction;\n\
		uniform vec4 modelColor;\n\
		out vec4 fragColor;\n\
		void main() {\n\
			vec4 ambient = vec4(0.2, 0.2, 0.2, 1.0);\n\
			vec4 specular = vec4(1.0, 1.0, 1.0, 1.0);\n\
			vec3 n = normalize(normal_out);\n\
			vec3 l = normalize(light_direction);\n\
			float cosTheta = clamp(dot(n, l), 0, 1);\n\
			vec3 E = normalize(eye_direction);\n\
			vec3 R = reflect(-l, n);\n\
			float cosAlpha = clamp(dot(E, R), 0, 1);\n\
			float alpha = 64;\n\
			fragColor = ambient + modelColor*cosTheta + specular*pow(cosAlpha, alpha);\n\
		}\n";

	// Compile Vertex Shader
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

	GLint success = 0;
	GLchar infoLog[512];
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(VertexShaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

    // Compile Fragment Shader
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);

	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(FragmentShaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	// Link Program
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

	glGetProgramiv(ProgramID, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(ProgramID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

	//std::vector<float> marchingVerts = marching_squares(f1, isoval, min, max, min, max, stepsize);

	// access and process vertex information
	std::vector<float> vertices = marching_cubes(cone, isoval, min, max, stepsize);
	std::vector<float> normals = compute_normals(vertices);
	writePly(vertices, normals, fileName);

	// create buffers
	GLuint VAO;
	GLuint vertexID;
	GLuint normalID;

	// start VAO
	glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

	// 1st attribute : vertices
    glGenBuffers(1, &vertexID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                               // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                               // size
		GL_FLOAT,                        // type
		GL_FALSE,                        // normalized?
		0,             					 // stride
		(void*)0                         // data
	);

	/*
	glBindBuffer(GL_ARRAY_BUFFER, vertexID);
	int size = vertices.size();
	GLfloat array[size];
	glGetBufferSubData(GL_ARRAY_BUFFER, 0, size* sizeof(GLfloat), array);
	for (int i = 0; i < size; i += 3)
		printf("%f %f %f\n", array[i], array[i+1], array[i+2]);
	*/

	// 2nd attribute : normals
    glGenBuffers(1, &normalID);
	glBindBuffer(GL_ARRAY_BUFFER, normalID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*normals.size(), normals.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,                               // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                               // size
		GL_FLOAT,                        // type
		GL_FALSE,                        // normalized?
		0,             					 // stride
		(void*)0                         // data
	);

	glBindVertexArray(0);

	// get MVP
	glm::mat4 MVP;
	glm::vec3 LightDir = {1.0f, 1.0f, 1.0f};
	glm::vec4 modelColor = {0.0f, 1.0f, 1.0f, 1.0f};

    // starting camera position
    glm::vec3 eye = {5.0f, 5.0f, 5.0f};
    glm::vec3 up = {0.0f, 1.0f, 0.0f};
    glm::vec3 point = {0.0f, 0.0f, 0.0f};

	float r = sqrt(3*(5.0f*5.0f));
	float pitch = glm::radians(90.0f) - asin(5.0f/r);
	float yaw = asin(5.0f/(r*sin(pitch)));

	// mouse info
	bool hold = false;
	float lastX = 0;
	float lastY = 0;

	// render part by part
	int i = 0;
	int increment = 100*(max - min)/stepsize;

	do{
		i += increment;
		if (i > vertices.size())
			i = vertices.size();

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// create projection matrix
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glm::mat4 Projection = glm::perspective(glm::radians(45.0f), screenW/screenH, 0.001f, 1000.0f);

		glLoadMatrixf(glm::value_ptr(Projection));

		glMatrixMode( GL_MODELVIEW );
		glPushMatrix();

		// allow camera to move
		cameraControls(eye, yaw, pitch, r, hold, lastX, lastY); 

		glm::mat4 V = glm::lookAt(eye, point, up); 

		glm::mat4 M = glm::mat4(1.0f);

		glm::mat4 MV = V * M;
		glLoadMatrixf(glm::value_ptr(V));

		MVP = Projection * V * M;

		// Draw the box around the marching volume
		glLineWidth(1.0f);
		glColor3f(0.7f, 0.7f, 0.7f);
		glBegin(GL_LINES);
			glVertex3f(min, min, min);
			glVertex3f(max, min, min);
			
			glVertex3f(min, min, min);
			glVertex3f(min, max, min);

			glVertex3f(min, min, min);
			glVertex3f(min, min, max);

			glVertex3f(max, max, max);
			glVertex3f(min, max, max);
			
			glVertex3f(max, max, max);
			glVertex3f(max, min, max);

			glVertex3f(max, max, max);
			glVertex3f(max, max, min);

			glVertex3f(min, min, max);
			glVertex3f(max, min, max);

			glVertex3f(max, min, min);
			glVertex3f(max, min, max);

			glVertex3f(min, max, min);
			glVertex3f(max, max, min);

			glVertex3f(min, max, min);
			glVertex3f(min, max, max);

			glVertex3f(min, min, max);
			glVertex3f(min, max, max);

			glVertex3f(max, min, min);
			glVertex3f(max, max, min);
		glEnd();

		// Draw the Axis
		glLineWidth(1.5f);
		glBegin(GL_LINES);

			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(min, min, min);
			glVertex3f(max, min, min);
			
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(min, min, min);
			glVertex3f(min, max, min);

			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(min, min, min);
			glVertex3f(min, min, max);
		glEnd();

		// draw triangles
		glUseProgram(ProgramID);

		glUniformMatrix4fv(glGetUniformLocation(ProgramID, "MVP"), 1, false, glm::value_ptr(MVP));
		glUniformMatrix4fv(glGetUniformLocation(ProgramID, "V"), 1, false, glm::value_ptr(V));
		glUniform3fv(glGetUniformLocation(ProgramID, "LightDir"), 1, glm::value_ptr(LightDir));
		glUniform4fv(glGetUniformLocation(ProgramID, "modelColor"), 1, glm::value_ptr(modelColor));

        glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, i);
		glBindVertexArray(0);

		glUseProgram(0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();


	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	return 0;
}

