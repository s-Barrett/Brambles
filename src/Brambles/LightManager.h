#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

#include <iostream>
#include <string>
#include <vector>
#include <memory>

struct Light
{
	std::string name;
	glm::vec3 position;
	glm::vec3 colour;
	float strength;
};

class LightManager
{
public:
	std::vector<std::shared_ptr<Light>> getLights() { return m_lights; }

	void addLight(std::string _name, glm::vec3 _position, glm::vec3 _colour, float _strength)
	{
		std::shared_ptr<Light> l = std::make_shared<Light>();
		l->position = _position;
		l->colour = _colour;
		l->strength = _strength;
		m_lights.push_back(l);
	}

	void removeLight(std::string _name)
	{
		for (size_t i = 0; i < m_lights.size(); ++i)
		{
			if (m_lights.at(i)->name == _name)
			{
				m_lights.erase(m_lights.begin() + i);
				return;
			}
		}
	}

	void setAmbient(glm::vec3 _ambient) { m_ambient = _ambient; }

	glm::vec3 getAmbient() { return m_ambient; }

private:
	std::vector<std::shared_ptr<Light>> m_lights;
	glm::vec3 m_ambient = glm::vec3(0.1f, 0.1f, 0.1f);
};