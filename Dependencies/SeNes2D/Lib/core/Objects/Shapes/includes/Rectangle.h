#pragma once

#include "SceneObject.h"

namespace sn
{
	class Rectangle : public SceneObject // TODO: It is a square
	{
	public:
		Rectangle();
		~Rectangle() = default;

		void setSize(GLfloat size);
		[[nodiscard]] GLfloat getSize() const;

		void setPosition(const glm::vec3& position) override;

		void draw(const std::string& programName, ShaderManager& shaderManager, Camera& camera) override
		{
		};
		void draw(const std::string& programName,
			ShaderProgram* program, Camera& camera) override;
		void processKeyboard(Movement direction, GLfloat deltaTime) override
		{
		};
		void processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch) override
		{
		}

	private:
		void setupVertices();

	private:
		GLfloat _size = 100.f;
	};

}