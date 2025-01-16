
#include "Component.h"

namespace Brambles
{

	/**
	 * @brief Defines a BoxCollider component for handling collisions in 3D space.
	 */
    struct BoxCollider : Component
    {
    public:
        void renderDebug();

        void onRender();

        /**
         * @brief Checks if this collider is colliding with another box collider.
         * @param _other Another BoxCollider to check collision with.
         * @return True if colliding, false otherwise.
         */
        bool isColliding(std::shared_ptr<BoxCollider> _other);

        /**
         * @brief Gets the size of the box collider.
         * @return The size of the collider.
         */
        glm::vec3 getSize() { return m_size; }

        /**
         * @brief Sets the size of the box collider.
         * @param _size The new size to set.
         */
        void setSize(glm::vec3 _size) { m_size = _size; }

        /**
         * @brief Gets the offset of the box collider.
         * @return The offset of the collider.
         */
        glm::vec3 getOffset() { return m_offset; }

        /**
         * @brief Sets the offset of the box collider.
         * @param _offset The new offset to set.
         */
        void setOffset(const glm::vec3& _offset) { m_offset = _offset; }

        /**
         * @brief Enables or disables debug rendering for this collider.
         * @param _debugRenderer True to enable, false to disable.
         */
        void setDebugRenderer(bool _debugRenderer) { debugRenderer = _debugRenderer; }

        /**
         * @brief Gets the current debug rendering status.
         * @return True if debug rendering is enabled, false otherwise.
         */
        bool getDebugRenderer() { return debugRenderer; }

    private:
        glm::vec3 m_size{ 1 , 1 , 1 }; ///< The size of the collider.
        glm::vec3 m_offset{ 0, 0, 0 }; ///< The offset from the collider's position.

        float m_mass{ 1.0f }; ///< The mass of the collider.

        bool debugRenderer; ///< Flag to enable/disable debug rendering.
    };

};
