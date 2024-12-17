#include <vector>

namespace Brambles
{
	struct Input
	{
	public:
		void isKeyPressed(int key);

		void isKeyReleased(int key);

		bool isKey(int key);


		std::vector<int> keys;
		std::vector<int> keysPressed;
		std::vector<int> keysReleased;
	};

}