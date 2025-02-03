#pragma once

#include "Component.h"
#include <glm/glm.hpp>

namespace Brambles
{
	/**
	 * @brief Represents the position, rotation, and scale of an entity.
	 */
    class Transform : public Component
    {
    public:
        /**
         * @brief Default constructor initializing position, rotation, and scale.
         */
        Transform() : m_position(0.0f), m_rotation(0.0f), m_scale(1.0f) {}

        /**
         * @brief Sets the position of the entity.
         * @param position The new position in 3D space.
         */
        void setPosition(const glm::vec3& position) { m_position = position; }

        /**
         * @brief Gets the current position of the entity.
         * @return The position in 3D space.
         */
        glm::vec3 getPosition() const { return m_position; }

        /**
         * @brief Moves the entity by a specified amount.
         * @param pos The amount to move the entity by.
         */
        void move(const glm::vec3& pos) { m_position += pos; }

        /**
         * @brief Sets the rotation of the entity.
         * @param rotation The new rotation (Euler angles).
         */
        void setRotation(const glm::vec3& rotation) { m_rotation = rotation; }

        /**
         * @brief Gets the current rotation of the entity.
         * @return The rotation in Euler angles.
         */
        glm::vec3 getRotation() const { return m_rotation; }

        /**
         * @brief Rotates the entity by a specified amount.
         * @param pos The rotation to apply to the entity.
         */
        void rotate(const glm::vec3& pos) { m_rotation += pos; }

        /**
         * @brief Sets the scale of the entity.
         * @param scale The new scale factor.
         */
        void scale(const glm::vec3& scale) { m_scale = scale; }

        /**
         * @brief Gets the current scale of the entity.
         * @return The scale factor.
         */
        glm::vec3 getScale() const { return m_scale; }

        /**
         * @brief Gets the forward direction of the entity.
         * @return The forward vector.
         */
        glm::vec3 getForward() const;

        /**
         * @brief Gets the right direction of the entity.
         * @return The right vector.
         */
        glm::vec3 getRight() const;

        /**
         * @brief Gets the up direction of the entity.
         * @return The up vector.
         */
        glm::vec3 getUp() const;

        /**
         * @brief Calculates the model matrix based on position, rotation, and scale.
         * @return The model matrix.
         */
        glm::mat4 getModelMatrix() const;

    private:
        glm::vec3 m_position;  /**< Position of the entity in 3D space. */
        glm::vec3 m_rotation;  /**< Rotation of the entity (Euler angles). */
        glm::vec3 m_scale;     /**< Scale factor of the entity. */
    };
}
