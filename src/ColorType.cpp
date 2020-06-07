#include "PNG/ColorType.hpp"

namespace PNG
{
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