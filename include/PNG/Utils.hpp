#pragma once

#include <iostream>
#include <cstdint>
#include <array>
#include <vector>
#include <zlib.h>

namespace PNG
{
	enum class Endian
	{
		LittleEndian,
		BigEndian
	};

	std::uint16_t Read(std::array<std::uint8_t, 2> data);
	std::uint32_t Read(std::array<std::uint8_t, 4> data);
	std::uint64_t Read(std::array<std::uint8_t, 8> data);

	std::istream& Read(std::istream& is, std::uint8_t& i);
	std::istream& Read(std::istream& is, std::uint16_t& i, Endian endian = Endian::BigEndian);
	std::istream& Read(std::istream& is, std::uint32_t& i, Endian endian = Endian::BigEndian);
	std::istream& Read(std::istream& is, std::uint64_t& i, Endian endian = Endian::BigEndian);

	std::vector<std::uint8_t> Inflate(std::vector<std::uint8_t> deflatedData, size_t readBufferSize);

	template<unsigned bitN> constexpr unsigned EnumBit()
	{
		return (1 << bitN);
	}

	enum class FilteringType : std::uint8_t
	{
		None,
		Sub,
		Up,
		Average,
		Paeth
	};

	inline FilteringType ParseFilteringType(std::uint8_t rawFilteringType)
	{
		return static_cast<FilteringType>(rawFilteringType);
	}
}