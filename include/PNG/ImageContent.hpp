#pragma once

#include "PNG/Utils.hpp"
#include "PNG/Scanline.hpp"
#include "PNG/Color.hpp"

#include <vector>
#include <cassert>

namespace PNG
{
	class ImageContent
	{
	public:
		ImageContent() = default;
		ImageContent(const ImageContent&) = default;
		ImageContent(ImageContent&&) noexcept = default;
		ImageContent& operator=(const ImageContent&) = default;
		ImageContent& operator=(ImageContent&&) noexcept = default;

		Color At(size_t x, size_t y);
		
		void AddScanline(const Scanline& scanline);
	private:
		std::vector<std::vector<Color>> m_content;
	};
}