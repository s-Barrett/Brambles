#include <vector>
#include <glm/glm.hpp>

namespace Brambles
{
	struct Input
	{
	public:

		void onMouseMove(float x, float y);
		
		void setMousePosition(float& x, float& y);

		void getMousePosition(float& dx, float& dy);

		void isKeyPressed(int key);

		void isKeyReleased(int key);

		bool isKey(int key);


		std::vector<int> keys;
		std::vector<int> keysPressed;
		std::vector<int> keysReleased;
		
		float lastMouseX = 0;
		float lastMouseY = 0;
		float mouseX = 0;
		float mouseY = 0;
		bool firstMouse = true;

	private:

	};

}