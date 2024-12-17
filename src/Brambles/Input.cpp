#include "Input.h"


namespace Brambles
{

	void Input::isKeyPressed(int key)
	{
		keys.push_back(key);
	}

	void Input::isKeyReleased(int key)
	{
		for (int i = 0; i < keys.size(); i++)
		{
			if (keys[i] == key)
			{
				keys.erase(keys.begin() + i);
			}
		}
	}

	bool Input::isKey(int key)
	{
		for (int i = 0; i < keys.size(); i++)
		{
			if (keys[i] == key)
			{
				return true;
			}
		}
		return false;
	}

}