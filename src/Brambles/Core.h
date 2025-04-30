#pragma once
#include "Entity.h"
#include "LightManager.h"

#include <iostream>
#include <memory>
#include <vector>

namespace Brambles
{
    struct Entity;
    struct Window;
    struct Input;
    struct Camera;
    struct Physics;
	struct Shader;
    struct Audio;
    struct Timer;
    struct Screen;
    struct Gui;
    struct Resources;


	/**
	 * @brief Core engine class handling entities, input, and main loop.
	 */
    struct Core
    {
    public:
        static std::shared_ptr<Core> initialize(int winsizeX, int winsizeY);

        void run();
		void runSingleFrame();
        void stop();


		std::shared_ptr<Shader> setShader(std::string _path);
        /**
         * @brief Adds a new entity to the core.
         * @return A shared pointer to the newly added entity.
         */
        std::shared_ptr<Entity> addEntity();

        /**
         * @brief Gets the window associated with the core system.
         * @return A shared pointer to the window.
         */
        std::shared_ptr<Window> getWindow() { return m_window; }

        /**
         * @brief Gets the resources manager.
         * @return A shared pointer to the resources manager.
         */
        std::shared_ptr<Resources> getResources() { return m_resources; }

        /**
         * @brief Gets the input handler.
         * @return A shared pointer to the input handler.
         */
        std::shared_ptr<Input> getInput() { return m_input; }

        /**
         * @brief Gets the GUI manager.
         * @return A shared pointer to the GUI manager.
         */
        std::shared_ptr<Gui> getGui() { return m_gui; }

        std::vector<std::shared_ptr<Entity>> getEntities() { return m_entities; }


        /**
         * @brief Gets the camera.
         * @return A shared pointer to the camera.
         */
        std::shared_ptr<Camera> getCamera();

        /**
         * @brief Gets the timer associated with the core.
         * @return A shared pointer to the timer.
         */
        std::shared_ptr<Timer> getTimer();



		std::shared_ptr<Physics> getPhysics() { return m_physics; }



        std::shared_ptr<LightManager> getLightManager()  { return m_lightManager; }
        /**
         * @brief Seeks for components of a specific type in all entities.
         * @param _out The output vector to store found components.
         */
        template <typename T>
        void seekComponents(std::vector<std::shared_ptr<T>>& _out) {
            for (size_t ei = 0; ei < m_entities.size(); ++ei) {
                std::shared_ptr<Entity> e = m_entities.at(ei);
                for (size_t ci = 0; ci < e->m_components.size(); ++ci) {
                    std::shared_ptr<Component> c = e->m_components.at(ci);
                    std::shared_ptr<T> t = std::dynamic_pointer_cast<T>(c);

                    if (t) {
                        _out.push_back(t);
                    }
                }
            }
        }

    private:
        std::shared_ptr<Window> m_window;
        std::shared_ptr<Audio> m_audio;
        std::shared_ptr<Resources> m_resources;
        std::shared_ptr<Gui> m_gui;
        std::shared_ptr<Input> m_input;
        std::shared_ptr<Camera> m_camera;
        std::shared_ptr<Timer> m_timer;
        std::shared_ptr<Shader> m_shader;
        std::shared_ptr<LightManager> m_lightManager;
		std::shared_ptr<Physics> m_physics;
        std::vector<std::shared_ptr<Entity>> m_entities;

        std::weak_ptr<Core> m_self;
    };
}
