#include "Shader.h"
#include "ShaderProgram.h"

#include "Window.h"
#include "Rectangle.h"
#include "Camera.h"

#include <iostream>

class Rectangle;

void initGLAD();

int main()
{
	Window::instance().initializeGLFWVersion();
	Window::instance().create(Window::Size(1280, 720), "Hello");
	Window::instance().makeContextCurrent();

	initGLAD();

	Shader vertexShader("assets//main.vert", Gl::Shader::Type::VERTEX);
	Shader fragmentShader("assets//main.frag", Gl::Shader::Type::FRAGMENT);
	ShaderProgram shaderProgram(vertexShader.getShader(), fragmentShader.getShader());
	shaderProgram.use();

	GLint windowWidth = 0, windowHeight = 0;
	glfwGetFramebufferSize(Window::instance().getWinTarget(), &windowWidth, &windowHeight);

	sn::Rectangle rect;
	rect.setPosition(glm::vec3(0, 0, 0));

	Camera camera(glm::vec3(0.f, 0.f, 0.f), true);

	GLfloat deltaTime = 0.f, lastFrame = 0.f, currentFrame = 0.f;

	while(!Window::instance().shouldClose())
	{
		Window::instance().pollEvents();

		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		Window::instance().clear(GL_COLOR_BUFFER_BIT);
		Window::instance().clearColor(0.1f, 0.2f, 0.3f, 1.f);

		rect.draw("main", &shaderProgram, camera);

		camera.control(deltaTime);

		shaderProgram.uniform("view", 1, GL_FALSE, camera.getViewMatrix());
		shaderProgram.uniform("projection", 1, GL_FALSE, camera.getProjectionMatrix(
			(GLfloat)Window::instance().getSize().getX(),
			(GLfloat)Window::instance().getSize().getY()));

		Window::instance().swapBuffers(Window::instance().getWinTarget());
	}
	return 0;
}

void initGLAD()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw std::runtime_error("Failed to initialize GLAD");
	}
}