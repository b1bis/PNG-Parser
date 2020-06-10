#pragma once

#include "PNG/Utils.hpp"
#include "PNG/ColorType.hpp"
#include <utility>

namespace PNG
{
	class Header
	{
	public:
		Header() = default;
		static Header ReadHeader(std::istream& is, Endian endian = Endian::BigEndian);

		unsigned GetX() const { return m_x; }
		unsigned GetY() const { return m_y; }
		std::pair<unsigned, unsigned> GetDimension() const { return std::make_pair(m_x, m_y); }

		ColorTypeFlags GetColorType() const { return m_colorType; }

	private:
		Header(unsigned x, unsigned y, ColorTypeFlags colorType);
		unsigned m_x, m_y;
		ColorTypeFlags m_colorType;
	};
}