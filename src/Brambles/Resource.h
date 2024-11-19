#include <string>
#include <iostream>
#include "rend/rend.h"


namespace Brambles
{


	namespace Brambles
	{
		class Core;
	}
	struct Resource
	{
		virtual void onLoad() = 0;
		std::string getPath() const;
	private:
		std::string m_path;
		void load();
	};

}