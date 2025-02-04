#pragma once

#include "Gl.h"
#include "Window.h"
#include "SceneObject.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace sn
{
	class Camera : public SceneObject
	{
	public:
		Camera() = default;
		Camera(const glm::vec3& position, bool setCursorMousePosCallback = false,
			GLfloat speed = 35.f, GLfloat sensitivity = 0.1f);
		Camera(const Camera&) = default;
		Camera& operator=(const Camera&) = default;
		Camera(Camera&&) = default;
		Camera& operator=(Camera&&) = default;
		~Camera() = default;

		[[nodiscard]] glm::mat4 getViewMatrix();
		void processKeyboard(Movement direction, GLfloat deltaTime) override;
		void processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch) override;

		void setTexture(const Texture& texture) override
		{
		};
		void setSpeed(GLfloat speed);
		[[nodiscard]] GLfloat getSpeed() const;
		void setSensitivity(GLfloat sensitivity);
		[[nodiscard]] GLfloat getSensitivity() const;
		[[nodiscard]] glm::mat4 getProjectionMatrix(GLfloat windowWidth, GLfloat windowHeight) const;
		void updateViewMatrix();

		static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
		void setCursorPosCallback();
		void control(GLfloat deltaTime);

		[[nodiscard]] bool is2DCameraMode() const;
		void set2DCameraMode(bool is2DCameraMode);

	private:
		glm::mat4 _projection{ }, _viewMatrix{ };
		bool _is2DCamera = false;

		GLfloat _movementSpeed = 25.f, _mouseSensitivity = 0.1f;
		inline static GLfloat _xMouseOffset = 0.f, _yMouseOffset = 0.f;
	};
}