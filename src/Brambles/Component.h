
#pragma once
#include <glm/glm.hpp>
#include <memory>

namespace Brambles
{
    struct Transform;
    struct Entity;
    struct Gui;


	/**
	 * @brief Defines the base class for components attached to entities.
	 */
    struct Component
    {
        virtual void onInitialize() {}
        virtual void onTick() {}
        virtual void onRender() {}
        virtual void onGui() {}

        /**
         * @brief Gets the entity this component is attached to.
         * @return A shared pointer to the entity.
         */
        std::shared_ptr<Entity> getEntity();

        /**
         * @brief Gets the transform of the entity.
         * @return A shared pointer to the transform.
         */
        std::shared_ptr<Transform> getTransform();

        /**
         * @brief Gets the GUI associated with this component.
         * @return A shared pointer to the GUI.
         */
        std::shared_ptr<Gui> getGui();

        glm::vec3 getPosition();
        glm::vec3 getRotation();
        glm::vec3 getScale();

        void setPosition(glm::vec3 position);
        void setRotation(glm::vec3 rotation);
        void setScale(glm::vec3 scale);

        /**
         * @brief Moves the component by the given vector.
         * @param move The vector by which to move the component.
         */
        void move(glm::vec3 move);

        /**
         * @brief Rotates the component by the given vector.
         * @param rotate The vector by which to rotate the component.
         */
        void rotate(glm::vec3 rotate);

        /**
         * @brief Scales the component by the given vector.
         * @param scale The vector by which to scale the component.
         */
        void scale(glm::vec3 scale);

    private:
        friend struct Brambles::Entity;

        std::weak_ptr<Entity> m_entity;

        void gui();
        void tick();
        void render();
    };
}
