#include "PNG/Chunk.hpp"

namespace PNG
{
	ChunkInfo::Type ParseType(std::istream& is, Endian endian)
	{
		std::uint32_t raw;
		Read(is, raw, endian);


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

	ChunkInfo ChunkInfo::Parse(std::istream& is, Endian endian)
	{
		std::uint32_t lenght = 0, crt = 0;
		Read(is, lenght, endian);
		Type type = ParseType(is, endian);

		std::streampos pos = is.tellg();
		is.seekg(lenght, std::ios::cur);
		Read(is, crt, endian);

		is.seekg(pos);

		return ChunkInfo(lenght, type, crt, is.tellg());
	}
}
