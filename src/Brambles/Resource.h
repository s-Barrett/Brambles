#include <string>
#include <iostream>
#include "rend/rend.h"


namespace Brambles
{

	class Core;
	struct Resources;
	struct Resource
	{
		virtual void onLoad() = 0;
		std::string getPath() const;
	private:
		friend struct Brambles::Resources;
		std::string m_path;
		void load();
	};

}