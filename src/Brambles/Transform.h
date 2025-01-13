#pragma once

#include "Component.h"
#include <glm/glm.hpp>

namespace Brambles
{
    class Transform : public Component
    {
    public:
        Transform()
            : m_position(0.0f), m_rotation(0.0f), m_scale(1.0f) {}


        void setPosition(const glm::vec3& position) { m_position = position; }
        glm::vec3 getPosition() const { return m_position; }
        void move(const glm::vec3& delta) { m_position += delta; }


        void setRotation(const glm::vec3& rotation) { m_rotation = rotation; }
        glm::vec3 getRotation() const { return m_rotation; }
        void rotate(const glm::vec3& delta) { m_rotation += delta; }


        void setScale(const glm::vec3& scale) { m_scale = scale; }
        glm::vec3 getScale() const { return m_scale; }


        glm::vec3 getForward() const;
        glm::vec3 getRight() const;
        glm::vec3 getUp() const;


        glm::mat4 getModelMatrix() const;

    private:
        glm::vec3 m_position;
        glm::vec3 m_rotation; 
        glm::vec3 m_scale;
    };
}
