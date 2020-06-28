#include "PNG/Image.hpp"

namespace PNG
{
	Image::Image(std::filesystem::path path, bool loadContent)
	{
		Load(path, loadContent);
	}

	void Image::Load(std::filesystem::path path, bool loadContent)
	{
		m_is = std::make_unique<std::ifstream>(path.string(), std::ios::binary);

		m_is->seekg(0, std::ios::end);
		std::streampos end{ m_is->tellg() };

		m_is->seekg(8); // TODO : Verify PNG signature

		while (m_is->tellg() < end) 
		{
			ChunkInfo chunk = ChunkInfo::ReadChunk(*m_is);
			m_is->seekg(chunk.NextChunkPos());
			m_chunks.push_back(std::move(chunk));
		}

		LoadHeader();
		if (loadContent)
			LoadImageContent();
	}

	void Image::LoadHeader()
	{
		auto headerChunkIt = std::find_if(m_chunks.begin(), m_chunks.end(), [](ChunkInfo c) 
		{
			return (c.GetType()) == ChunkInfo::Type::IDRH;
		});
		m_is->seekg(headerChunkIt->begin());
		m_header = Header::ReadHeader(*m_is);
	}

	void Image::LoadImageContent()
	{
		std::vector<std::uint8_t> data;
		for (const ChunkInfo& chunk : m_chunks)
		{
			if (chunk.GetType() == ChunkInfo::IDAT)
			{
				std::vector<std::uint8_t> tmp{ chunk.Load(*m_is) };
				data.insert(data.end(), tmp.begin(), tmp.end());
			}
			else if (chunk.GetType() == ChunkInfo::IEND)
				break;
		}
		m_content = ImageContentLoader().Load(std::move(data), GetDimension(), m_header.GetColorType());
	}
}