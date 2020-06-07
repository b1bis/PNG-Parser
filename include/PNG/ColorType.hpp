#pragma once

#include "PNG/Utils.hpp"

#include <iostream>

namespace PNG
{
	enum class ColorType : uint8_t
	{
		Indexed = EnumBit<0>(),
		Colored = EnumBit<1>(),
		Alphaed = EnumBit<2>(),

		GrayScale      = 0,
		AlphaGrayScale = Alphaed,
		ColorPalette   = Colored | Indexed,
		ColorAlpha     = Colored | Alphaed
	};

	class ColorTypeFlags
	{
	public:
		ColorTypeFlags() = default;

		ColorTypeFlags(ColorType colorType) : 
			m_flags { static_cast<uint8_t>(std::move(colorType)) } {}

		ColorTypeFlags(uint8_t colorType) :
			m_flags{ std::move(colorType) } {}

		void SetFlags(ColorType colorType) { m_flags = static_cast<uint8_t>(colorType); }

		bool TestFlags(ColorTypeFlags mask) { return static_cast<bool>(*this & mask); }

		operator bool() { return m_flags; }
		operator uint8_t() { return m_flags; }

		ColorTypeFlags operator&(ColorTypeFlags mask);
		ColorTypeFlags operator|(ColorTypeFlags mask);
		ColorTypeFlags operator^(ColorTypeFlags mask);
		ColorTypeFlags operator&(ColorType mask);
		ColorTypeFlags operator|(ColorType mask);
		ColorTypeFlags operator^(ColorType mask);
		ColorTypeFlags operator~();

		ColorTypeFlags& operator&=(ColorTypeFlags mask);
		ColorTypeFlags& operator|=(ColorTypeFlags mask);
		ColorTypeFlags& operator^=(ColorTypeFlags mask);
	private:
		uint8_t m_flags;
	};
}