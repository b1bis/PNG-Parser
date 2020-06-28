#pragma once

#include "PNG/Utils.hpp"
#include "PNG/Header.hpp"
#include "PNG/ImageContent.hpp"
#include "PNG/ImageContentLoader.hpp"
#include <filesystem>
#include <fstream>
#include <memory>
#include <algorithm>

namespace PNG 
{
	class Image
	{
	public:
		Image() = default;

		Image(std::filesystem::path path, bool loadImage = true);

		Image(const Image&) = default;
		Image(Image&&) = default;
		Image& operator= (const Image&) = default;
		Image& operator= (Image&&) = default;

		unsigned GetLenght() { return m_header.GetX(); }
		unsigned GetHeight() { return m_header.GetY(); }
		std::pair<unsigned, unsigned> GetDimension() { return m_header.GetDimension(); }

		const ImageContent& GetContent() { return m_content; }

		void LoadImageContent();

	private:
		void Load(std::filesystem::path path, bool loadContent);
		void LoadHeader();

		std::unique_ptr<std::istream> m_is;
		std::vector<ChunkInfo> m_chunks;
		Header m_header;
		ImageContent m_content;
	};
}