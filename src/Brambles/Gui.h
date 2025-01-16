#include "rend/Shader.h"
#include "rend/Mesh.h"
#include "Component.h"


namespace Brambles
{
	struct Texture;
	struct Core;
	struct Input;
	struct Gui : public Component
	{

	public:

		Gui();
		~Gui();


		int button(glm::vec2 _position, glm::vec2 _size, std::shared_ptr<Brambles::Texture> _texture, std::shared_ptr<rend::Mesh> _shape);

		std::shared_ptr<rend::Shader> setGuiShader(std::shared_ptr<rend::Shader> _shader) { return guiShader = _shader; }


		std::shared_ptr<rend::Mesh> meshCube();
		std::shared_ptr<rend::Mesh> meshCircle();
		std::shared_ptr<rend::Mesh> meshTriangle();
		std::shared_ptr<rend::Mesh> meshStar();


		//void text(glm::vec2 _position, float _size, glm::vec3 _colour, std::string _text, std::shared_ptr<Font> _font);


	private:

		glm::vec2 mousePosition; 
	
		std::shared_ptr<rend::Shader> guiShader;
		std::weak_ptr<Core> m_core;


	};
}

