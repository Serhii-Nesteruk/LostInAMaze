#include "Rectangle.h"

void sn::Rectangle::draw(const std::string& programName, ShaderProgram* program, Camera& camera)
{
	updateMatrices();

	program->uniform("model", 1, GL_FALSE, _modelMatrix);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void sn::Rectangle::setupVertices()
{
	std::vector<GLfloat> vertices = {
		_position.x, _position.y,
		_position.x + _size, _position.y,
		_position.x + _size, _position.y + _size,

		_position.x, _position.y,
		_position.x, _position.y + _size,
		_position.x + _size, _position.y + _size,
	};

	setVertices(vertices);

	_vbo.generate();
	_vao.generate();

	_vbo.bind();
	_vao.bind();

	_vbo.setData(_vertices);
	_vao.vertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);

	_vao.bind();
	_vbo.bind();
}

void sn::Rectangle::setSize(GLfloat size)
{
	_size = size;
	setupVertices();
}

GLfloat sn::Rectangle::getSize() const
{
	return _size;
}

void sn::Rectangle::setPosition(const glm::vec3& position)
{
	SceneObject::setPosition(position);
	setupVertices();
}

sn::Rectangle::Rectangle()
{
	setupVertices();
}
