#pragma once

#include <iostream>
#include <cstdint>
#include <array>

namespace PNG
{
	enum class Endian
	{
		LittleEndian,
		BigEndian
	};

	std::istream& Read(std::istream& is, std::uint8_t& i);
	std::istream& Read(std::istream& is, std::uint16_t& i, Endian endian = Endian::BigEndian);
	std::istream& Read(std::istream& is, std::uint32_t& i, Endian endian = Endian::BigEndian);
	std::istream& Read(std::istream& is, std::uint64_t& i, Endian endian = Endian::BigEndian);

	template<unsigned bitN> constexpr unsigned EnumBit()
	{
		return (1 << bitN);
	}
}