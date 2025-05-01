// #pragma once
//
// #include "Resource.h"
// #include "rend/Font.h"
//
// #include <memory>
//
// namespace Brambles
// {
//
// 	class Renderer;
//
// 	class Font : public Resource
// 	{
// 	public:
// 		void onLoad() { m_font = std::make_shared<rend::Font>(getPath() + ".ttf"); }
//
// 	private:
// 		friend class Renderer;
// 		friend class Gui;
//
// 		std::shared_ptr<rend::Font> m_font;
// 	};
//
// }