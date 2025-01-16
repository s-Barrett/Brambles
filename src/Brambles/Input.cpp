#include "Input.h"


namespace Brambles
{

	void Input::isKeyPressed(int key)//Adds keys to array
	{
		keys.push_back(key);
	}

	void Input::isKeyReleased(int key)//Removes keys from array
	{
		for (int i = 0; i < keys.size(); i++)
		{
			if (keys[i] == key)
			{
				keys.erase(keys.begin() + i);
			}
		}
	}

	bool Input::isKey(int key)//Checks if key is in array
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

	void Input::onMouseMove(float x, float y)//Checks mouse position
	{
		if (firstMouse)
		{
			lastMouseX = x;
			lastMouseY = y;
			firstMouse = false;
		}

		mouseX = x;
		mouseY = y;
	}

	void Input::setMousePosition(float& x, float& y)//Sets mouse position
	{
		x = mouseX;
		y = mouseY;
	}

	void Input::getMousePosition(float& dx, float& dy)//Gets mouse position
	{
		dx = mouseX;
		dy = mouseY;

		// Reset deltas after reading
		mouseX = 0.0f;
		mouseY = 0.0f;
	}

}