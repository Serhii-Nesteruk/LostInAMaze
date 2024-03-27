#include "Rectangle.h"

void sn::Rectangle::draw(const std::string& programName, ShaderProgram* program, Camera& camera)
{
	updateMatrices();

	program->uniform("model", 1, GL_FALSE, _modelMatrix);
	program->uniform("uDefaultColor", _rgb);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void sn::Rectangle::setupVertices()
{
	float halfSize = _size / 2.0f;

	std::vector<float> vertices = {
		// left bottom triangle
		-halfSize, -halfSize, 0.0f,
		halfSize,  halfSize, 0.0f,
		-halfSize,  halfSize, 0.0f,

		// right triangle
		-halfSize, -halfSize, 0.0f,
		halfSize, -halfSize, 0.0f,
		halfSize,  halfSize, 0.0f
	};


	setVertices(vertices);

	_vbo.generate();
	_vao.generate();

	_vbo.bind();
	_vao.bind();

	_vbo.setData(_vertices);
	_vao.vertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

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

sn::Rectangle::Rectangle(bool isSetupVertices /*= false*/)
{
	if (isSetupVertices)
	{
		setupVertices();
	}
}

sn::Rectangle::Rectangle(sn::Rectangle&& other) noexcept
	: SceneObject(std::move(other))
{
	if (this != &other)
	{
		_size = other._size;
	}
}

sn::Rectangle& sn::Rectangle::operator=(sn::Rectangle&& other) noexcept
{
	if (this != &other)
	{
		SceneObject::operator=(std::move(other));
		_size = std::move(other._size);

		other._size = { };
	}

	return *this;
}
void sn::Rectangle::setColor(const Color3& rgb)
{
	_rgb = rgb;
}
Color3 sn::Rectangle::getColor() const
{
	return _rgb;
};


