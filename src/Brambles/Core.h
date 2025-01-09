#pragma once
#include <iostream>
#include<memory>
#include<vector>


namespace Brambles
{
	struct Entity;
	struct Window;
	struct Input;
	struct Camera;
	struct Audio;
	struct Screen;
	struct Gui;
	struct Resources;
	struct Core
	{
	public:
		static std::shared_ptr<Core> initialize();
		
		void run();
		void stop();

		std::shared_ptr<Entity> addEntity();

		std::shared_ptr<Window> getWindow() { return m_window; }

		std::shared_ptr<Resources> getResources() { return m_resources; }

		std::shared_ptr<Input> getInput() { return m_input; }

		std::shared_ptr<Camera> getCamera() { return m_camera; }


	private:

		std::shared_ptr<Window> m_window;
		std::shared_ptr<Audio> m_audio;
		std::shared_ptr<Resources> m_resources;
		std::shared_ptr<Gui> m_gui;
		std::shared_ptr<Input> m_input;
		std::shared_ptr<Camera> m_camera;


		std::vector<std::shared_ptr<Entity>> m_entities;

		std::weak_ptr<Core> m_self;
		
	};
}

