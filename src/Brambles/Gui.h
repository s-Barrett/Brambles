
#include "rend/Shader.h"
#include "rend/Mesh.h"
#include "Component.h"

namespace Brambles
{
    struct Texture;
    struct Core;



	/**
	* @brief GUI component for rendering and handling GUI elements like buttons and shapes. 
	*/
    struct Gui : public Component
    {
    public:
        Gui();
        ~Gui();

        /**
         * @brief Creates a button in the GUI.
         * @return A unique identifier for the button.
         */
        int button(glm::vec2 _position, glm::vec2 _size, std::shared_ptr<Brambles::Texture> _texture, std::shared_ptr<rend::Mesh> _shape);

        /**
         * @brief Sets the GUI shader.
         * @return The previously set shader.
         */
        std::shared_ptr<rend::Shader> setGuiShader(std::shared_ptr<rend::Shader> _shader) { return guiShader = _shader; }

        /**
         * @brief Creates a cube mesh for the GUI.
         * @return A shared pointer to a cube mesh.
         */
        std::shared_ptr<rend::Mesh> meshCube();

        /**
         * @brief Creates a circle mesh for the GUI.
         * @return A shared pointer to a circle mesh.
         */
        std::shared_ptr<rend::Mesh> meshCircle();

        /**
         * @brief Creates a triangle mesh for the GUI.
         * @return A shared pointer to a triangle mesh.
         */
        std::shared_ptr<rend::Mesh> meshTriangle();

        /**
         * @brief Creates a star mesh for the GUI.
         * @return A shared pointer to a star mesh.
         */
        std::shared_ptr<rend::Mesh> meshStar();

        // Uncomment if text rendering functionality is added
        // void text(glm::vec2 _position, float _size, glm::vec3 _colour, std::string _text, std::shared_ptr<Font> _font);

    private:
        glm::vec2 mousePosition; ///< The position of the mouse on the screen.

        std::shared_ptr<rend::Shader> guiShader; ///< The shader to be used for GUI rendering.
        std::weak_ptr<Core> m_core; ///< A weak pointer to the core of the system.
    };
}
