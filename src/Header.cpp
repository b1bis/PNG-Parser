#include "PNG/Header.hpp"

namespace PNG
{
	Header::Header(unsigned x, unsigned y, ColorTypeFlags colorType) : 
		m_x{x}, m_y{y}, m_colorType{colorType}
	{}

	Header Header::ReadHeader(std::istream& is, Endian endian)
	{
		std::uint32_t x, y;
		Read(is, x, endian);
		Read(is, y, endian);
		std::uint8_t rawBitDepth, rawColorType, rawCompressionMethod, rawFilteringMethod, rawInterlacingMethod;

		Read(is, rawBitDepth);
		//TODO : Support different bit depth

		Read(is, rawColorType);
		ColorTypeFlags colorType { ColorTypeFlags::Parse(rawColorType) };

		Read(is, rawCompressionMethod); // There is only one compression method, so just ignore it

		Read(is, rawFilteringMethod);
		//TODO : Support filtering

		Read(is, rawInterlacingMethod); // I'll not implement interlacing

		return Header {x, y, colorType};
	}
}