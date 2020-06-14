#include "PNG/Chunk.hpp"

namespace PNG
{
	ChunkInfo::Type ChunkInfo::ParseType(std::uint32_t raw)
	{
		switch (raw)
		{
		case 0x49484452: //Header
			return ChunkInfo::IDRH;
		case 0x504C5445: //Palette
			return ChunkInfo::PLTE;
		case 0x49444154: //Image begin
			return ChunkInfo::IDAT;
		case 0x49454E44: //Image end
			return ChunkInfo::IEND;
		default:
			return ChunkInfo::Unsupported;
		}
	}

	std::vector<std::uint8_t> ChunkInfo::Load(std::istream& is)
	{
		std::vector<std::uint8_t> data;
		is.seekg(begin());
		while (is.tellg() != end())
		{
			std::uint8_t i;
			Read(is, i);
			data.push_back(std::move(i));
		}

		return data;
	}

	ChunkInfo ChunkInfo::ReadChunk(std::istream& is, Endian endian)
	{
		std::uint32_t lenght = 0, rawType = 0, crt = 0;
		Read(is, lenght, endian);

		Read(is, rawType, endian);
		Type type = ParseType(rawType);

		std::streampos pos = is.tellg();
		is.seekg(lenght, std::ios::cur);
		Read(is, crt, endian);

		is.seekg(pos);

		return ChunkInfo(lenght, type, crt, is.tellg());
	}
}