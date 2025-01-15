#include "rend/Shader.h"
#include "rend/Mesh.h"
#include "Component.h"


namespace Brambles
{
	struct Texture;
	struct Core;
	struct Gui
	{

	public:

		Gui();
		~Gui();


		int button(glm::vec2 _position, glm::vec2 _size, std::shared_ptr<Brambles::Texture> _texture, std::shared_ptr<rend::Mesh> _shape);

		bool isMouseOverButton(glm::vec2 mousePos, glm::vec2 buttonPos, glm::vec2 buttonSize);

		std::shared_ptr<rend::Mesh> meshCube();
		std::shared_ptr<rend::Mesh> meshCircle();


		//void text(glm::vec2 _position, float _size, glm::vec3 _colour, std::string _text, std::shared_ptr<Font> _font);


	private:

		glm::vec2 mousePosition; 
		std::shared_ptr<rend::Shader> guiShader = std::make_shared<rend::Shader>("../assets/shaders/funortho.vert", "../assets/shaders/funortho.frag");


		std::weak_ptr<Core> m_core;


	};
}

