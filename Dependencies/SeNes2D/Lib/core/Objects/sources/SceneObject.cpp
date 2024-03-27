#include "SceneObject.h"

void sn::SceneObject::setPosition(const glm::vec3& position)
{
	_position = position;
	updateMatrices();
}

glm::vec3 sn::SceneObject::getPosition() const
{
	return _position;
}

void sn::SceneObject::setScale(const glm::vec3& scale)
{
	_scale = scale;
	updateMatrices();
}

glm::vec3 sn::SceneObject::getScaleVec() const
{
	return _scale;
}

void sn::SceneObject::setTexture(const Texture& texture)
{
	*_texture = texture;
}

const Texture* sn::SceneObject::getTexture() const
{
	return _texture;
}

void sn::SceneObject::draw(const std::string& programName, ShaderManager& shaderManager, Camera& camera)
{

}

void sn::SceneObject::updateMatrices()
{
	_modelMatrix = glm::mat4(1.f);

	if (_isReverseMatrixCalculating)
	{
		_modelMatrix = glm::translate(_modelMatrix, _position - _origin);
		_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.x), glm::vec3(1.f, 0.f, 0.f));
		_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.y), glm::vec3(0.f, 1.f, 0.f));
		_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.z), glm::vec3(0.f, 0.f, 1.f));
		_modelMatrix = glm::translate(_modelMatrix, _origin - _position);

		_modelMatrix = glm::scale(_modelMatrix, _scale);
	}
	else
	{
		_modelMatrix = glm::scale(_modelMatrix, _scale);
		_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.x), glm::vec3(1.f, 0.f, 0.f));
		_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.y), glm::vec3(0.f, 1.f, 0.f));
		_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.z), glm::vec3(0.f, 0.f, 1.f));

		_modelMatrix = glm::translate(_modelMatrix, _position);
	}
}

void sn::SceneObject::setOrigin(const glm::vec3& origin)
{
	_origin = origin;
	updateMatrices();
}

void sn::SceneObject::setReverseMatrixCalculating(bool value)
{
	_isReverseMatrixCalculating = value;
}

bool sn::SceneObject::getReverseMatrixCalculating() const
{
	return _isReverseMatrixCalculating;
}

glm::mat4 sn::SceneObject::getModelMatrix() const
{
	return _modelMatrix;
}

void sn::SceneObject::setRotate(const glm::vec3& rotate)
{
	_rotation = rotate;
	updateMatrices();
}

glm::vec3 sn::SceneObject::getRotate() const
{
	return _rotation;
}

void sn::SceneObject::setVao(VAO&& vao)
{
	_vao = std::move(vao);
}

void sn::SceneObject::setVbo(VBO&& vbo)
{
	_vbo = std::move(vbo);
}

void sn::SceneObject::setVertices(const std::vector<GLfloat>& vertices)
{
	_vertices = vertices;
}

std::vector<GLfloat> sn::SceneObject::getVertices() const
{
	return _vertices;
}
glm::vec3 sn::SceneObject::getForwardVector() const //*
{
	auto r = glm::vec2(glm::radians(_rotation.x), glm::radians(_rotation.y));

	// clang-format off
	return glm::normalize(glm::vec3{
		cos(r.x) * -sin(r.y),
		sin(r.x),
		cos(r.x) * cos(r.y)
	});
	// clang-format on
}

glm::vec3 sn::SceneObject::getUpVector() const //*
{
	auto r = glm::vec2(glm::radians(_rotation.x), glm::radians(_rotation.y));
	r.x += glm::radians(-90.f);

	// clang-format off
	return glm::normalize(glm::vec3{
		cos(r.x) * -sin(r.y),
		sin(r.x),
		cos(r.x) * cos(r.y)
	});
	// clang-format on
}

glm::vec3 sn::SceneObject::getRightVector() const //*
{
	return glm::normalize(glm::cross(getForwardVector(), getUpVector()));
}

sn::SceneObject::SceneObject(sn::SceneObject&& other) noexcept
{
	operator=(std::move(other));
}

sn::SceneObject& sn::SceneObject::operator=(sn::SceneObject&& other) noexcept
{
	if (this != &other)
	{
		_isReverseMatrixCalculating = std::move(other._isReverseMatrixCalculating);
		_modelMatrix = std::move(other._modelMatrix);
		_rotation = std::move(other._rotation);
		_origin = std::move(other._origin);
		_position = std::move(other._position);
		_scale = std::move(other._scale);
		_texture = other._texture;
		_vao = std::move(other._vao);
		_vbo = std::move(other._vbo);
		_vertices = other._vertices;

		other._texture = nullptr;
		other._isReverseMatrixCalculating = { };
		other._modelMatrix = { };
		other._rotation = { };
		other._origin = { };
		other._position = { };
		other._scale = { };
		other._vao = { };
		other._vbo = { };
		other._vertices = { };
	}

	return *this;
};