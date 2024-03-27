#pragma once

#include "Window.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Rectangle.h"

#include <string>

class Game
{
public:
	Game(const Window::Size& windowSize, const std::string& windowName);
	~Game();

	void start();
	void setup();
private:
	void createMap();
	void setupWorldObjects();

private:
	Shader vertexShader{}, fragmentShader{};
	ShaderProgram shaderProgram{};
	sn::Camera camera;
	sn::Rectangle player{}; // TODO: replace it to the Player class
	std::vector<sn::Rectangle> rects{}; //TODO: Replace the Rectangle class to the Wall class
	GLfloat deltaTime = 0.f, lastFrame = 0.f, currentFrame = 0.f;
	float playerPosX = 0.f, playerPosY = 0.f;
	float rectPosX = 0.f, rectPosY = 0.f;
	const float rectPosZ = 0.f;

};