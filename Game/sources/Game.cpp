#include "../includes/Game.h"

Game::Game(const Window::Size& windowSize, const std::string& windowName)
{
	Window::instance().initializeGLFWVersion();
	Window::instance().create(Window::Size(1280, 720), "Lost In A Maze");
	Window::instance().makeContextCurrent();

	Window::instance().initGLAD();
}

Game::~Game()
{

}

void Game::setup()
{
	vertexShader.create(Gl::Shader::Type::VERTEX);
	vertexShader.loadFromFile("D://LostInAMaze//assets//main.vert");
	vertexShader.compile();

	fragmentShader.create(Gl::Shader::Type::FRAGMENT);
	fragmentShader.loadFromFile("D://LostInAMaze//assets//main.frag");
	fragmentShader.compile();

	shaderProgram.create();
	shaderProgram.attachShader(vertexShader.getShader());
	shaderProgram.attachShader(fragmentShader.getShader());
	shaderProgram.link();
	shaderProgram.use();

	setupWorldObjects();
}

void Game::start()
{
	while (!Window::instance().shouldClose())
	{
		Window::instance().pollEvents();

		player.setPosition({ playerPosX, playerPosY, rectPosZ });

		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		Window::instance().clear(GL_COLOR_BUFFER_BIT);
		Window::instance().clearColor(0.1f, 0.2f, 0.3f, 1.f);

		for (auto& rect : rects)
		{
			rect.draw("main", &shaderProgram, camera);
		}
		player.draw("main", &shaderProgram, camera);
		camera.control(deltaTime);

		if (GetAsyncKeyState('D') & 0x8000)
		{
			playerPosX += 250.f * deltaTime;
		}
		if (GetAsyncKeyState('A') & 0x8000)
		{
			playerPosX -= 250.f * deltaTime;
		}

		shaderProgram.uniform("view", 1, GL_FALSE, camera.getViewMatrix());
		shaderProgram.uniform("projection", 1, GL_FALSE, camera.getProjectionMatrix(
			(GLfloat)Window::instance().getSize().getX(),
			(GLfloat)Window::instance().getSize().getY()));

		Window::instance().swapBuffers(Window::instance().getWinTarget());
	}

}

void Game::setupWorldObjects()
{
	createMap();

	player.setupVertices();

	playerPosX = rectPosX + 400.f/*xOffset*/;
	playerPosY = rectPosY + 100.f/*yOffset*/;

	player.setColor({ 255, 0, 0 });

	camera.setPosition({0.f, 0.f, 500.f});
	camera.set2DCameraMode(true);
	camera.setSpeed(250.f);
}

void Game::createMap()
{
	rectPosX = -(GLfloat)Window::instance().getSize().getX() / 2;
	rectPosY = -(GLfloat)Window::instance().getSize().getY() / 2;

	static const int countOfRects = 20;
	rects.resize(countOfRects);

	for (auto& rect: rects)
		rect.setupVertices();

	float xOffset = 0.f;
	for (size_t i = 0; i < countOfRects; ++i)
	{
		xOffset += 100.f;
		sn::Rectangle rect;
		rect.setPosition({ rectPosX + xOffset, rectPosY, rectPosZ });
		rect.setColor({ 0, 255, 255 }); // something went wrong
		rects.at(i) = std::move(rect);
	}
}
