#include "PNG/Color.hpp"

namespace PNG
{
	std::ostream& operator<<(std::ostream& out, Color color)
	{
		out << "(R:" << std::setw(3) << static_cast<int>(color.m_r)
			<< "; G:" << std::setw(3) << static_cast<int>(color.m_g)
			<< "; B:" << std::setw(3) << static_cast<int>(color.m_b)
			<< "; A:" << std::setw(3) << static_cast<int>(color.m_a) << ")";
		return out;
	}
}


