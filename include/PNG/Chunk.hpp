#pragma once

#include "PNG/Utils.hpp"
#include <vector>

namespace PNG
{
	class ChunkInfo
	{
	public:

		enum Type
		{
			Unsupported,
			IDRH, //Header
			PLTE, //Palette
			IDAT, //Begin of an image section
			IEND  //End of an image section
		};

		ChunkInfo() = default;

		std::streampos begin() const { return m_dataBegin; }
		std::streampos end() const { return m_dataEnd; }

		std::uint32_t GetLenght() const { return m_lenght; }
		std::uint32_t GetCRT() const { return m_crt; }
		Type GetType() const { return m_type; }

		std::streampos NextChunkPos() const { return m_dataEnd + static_cast<std::streampos>(4); }

		std::vector<std::uint8_t> Load(std::istream&) const;

		static ChunkInfo ReadChunk(std::istream& is, Endian endian = Endian::BigEndian);
		static ChunkInfo::Type ParseType(std::uint32_t raw);
	private:
		ChunkInfo(std::uint32_t lenght, Type type, std::uint32_t crt, std::streampos dataBegin) : 
			m_lenght{ lenght }, m_type{ type }, m_crt{ crt }, m_dataBegin{ dataBegin }, 
			m_dataEnd { dataBegin + static_cast<std::streampos>(lenght) }
			{}
		std::uint32_t m_crt = 0;
		std::uint32_t m_lenght = 0;
		Type m_type = Unsupported;

		std::streampos m_dataBegin;
		std::streampos m_dataEnd;
	};
}