#include "PNG/ColorType.hpp"

namespace PNG
{

	ColorTypeFlags ColorTypeFlags::Parse(std::uint8_t raw)
	{
		ColorTypeFlags flags;

		if (raw & 0b001)
			flags |= ColorType::Indexed;
		if (raw & 0b010)
			flags |= ColorType::Colored;
		if (raw & 0b100)
			flags |= ColorType::Alphaed;

		return flags;
	}

	ColorTypeFlags ColorTypeFlags::operator&(ColorTypeFlags mask)
	{
		return m_flags & mask.m_flags;
	}

	ColorTypeFlags ColorTypeFlags::operator|(ColorTypeFlags mask)
	{
		return m_flags | mask.m_flags;
	}

	ColorTypeFlags ColorTypeFlags::operator^(ColorTypeFlags mask)
	{
		return m_flags ^ mask.m_flags;
	}

	ColorTypeFlags ColorTypeFlags::operator&(ColorType mask)
	{
		return m_flags & static_cast<uint8_t>(mask);
	}

	ColorTypeFlags ColorTypeFlags::operator|(ColorType mask)
	{
		return m_flags | static_cast<uint8_t>(mask);
	}

	ColorTypeFlags ColorTypeFlags::operator^(ColorType mask)
	{
		return m_flags ^ static_cast<uint8_t>(mask);
	}

	ColorTypeFlags& ColorTypeFlags::operator&=(ColorTypeFlags mask)
	{
		m_flags &= mask.m_flags;
		return *this;
	}

	ColorTypeFlags& ColorTypeFlags::operator|=(ColorTypeFlags mask)
	{
		m_flags |= mask.m_flags;
		return *this;
	}

	ColorTypeFlags& ColorTypeFlags::operator^=(ColorTypeFlags mask)
	{
		m_flags ^= mask.m_flags;
		return *this;
	}

	ColorTypeFlags ColorTypeFlags::operator~()
	{
		return ~m_flags;
	}
}