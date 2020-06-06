#pragma once

#include <iostream>
#include <array>

namespace PNG
{
	enum class Endian
	{
		LittleEndian,
		BigEndian
	};

	std::istream& Read(std::istream& is, uint8_t& i);
	std::istream& Read(std::istream& is, uint16_t& i, Endian endian = Endian::BigEndian);
	std::istream& Read(std::istream& is, uint32_t& i, Endian endian = Endian::BigEndian);
	std::istream& Read(std::istream& is, uint64_t& i, Endian endian = Endian::BigEndian);
}