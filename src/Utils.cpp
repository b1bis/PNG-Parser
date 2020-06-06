#include "PNG/Utils.hpp"

/* Unsigned */

std::istream& PNG::Read(std::istream& is, uint8_t& i)
{
	is.read(reinterpret_cast<char*>(&i), 1);
	return is;
}	

std::istream& PNG::Read(std::istream& is, uint16_t& i, Endian endian)
{
	i = 0;
	std::array<uint8_t, 2> data{};
	if (endian == Endian::LittleEndian)
	{
		for (auto it = data.rbegin(); it != data.rend(); ++it)
			is.read(reinterpret_cast<char*>(&(*it)), 1);
	}
	else if (endian == Endian::BigEndian)
	{
		for (auto it = data.begin(); it != data.end(); ++it)
			is.read(reinterpret_cast<char*>(&(*it)), 1);
	}

	i |= (0xFF00 & static_cast<uint16_t>(data[0] << 8));
	i |= (0x00FF & data[1]);
	return is;
}

std::istream& PNG::Read(std::istream& is, uint32_t& i, Endian endian)
{
	i = 0;
	std::array<uint8_t, 4> data{};
	if (endian == Endian::LittleEndian)
	{
		for (auto it = data.rbegin(); it != data.rend(); ++it)
			is.read(reinterpret_cast<char*>(&(*it)), 1);
	}
	else if (endian == Endian::BigEndian)
	{
		for (auto it = data.begin(); it != data.end(); ++it)
			is.read(reinterpret_cast<char*>(&(*it)), 1);
	}

	i |= (0xFF000000 & (static_cast<uint32_t>(data[0]) << 24));
	i |= (0x00FF0000 & (static_cast<uint32_t>(data[1]) << 16));
	i |= (0x0000FF00 & (static_cast<uint32_t>(data[2]) << 8));
	i |= (0x000000FF & data[3]);
	return is;
}

std::istream& PNG::Read(std::istream& is, uint64_t& i, Endian endian)
{
	i = 0;
	std::array<uint8_t, 8> data{};
	if (endian == Endian::LittleEndian)
	{
		for (auto it = data.rbegin(); it != data.rend(); ++it)
			is.read(reinterpret_cast<char*>(&(*it)), 1);
	}
	else if (endian == Endian::BigEndian)
	{
		for (auto it = data.begin(); it != data.end(); ++it)
			is.read(reinterpret_cast<char*>(&(*it)), 1);
	}

	i |= (0xFF00000000000000 & (static_cast<uint64_t>(data[0]) << 56));
	i |= (0x00FF000000000000 & (static_cast<uint64_t>(data[1]) << 48));
	i |= (0x0000FF0000000000 & (static_cast<uint64_t>(data[2]) << 40));
	i |= (0x000000FF00000000 & (static_cast<uint64_t>(data[3]) << 32));
	i |= (0x00000000FF000000 & (static_cast<uint64_t>(data[4]) << 24));
	i |= (0x0000000000FF0000 & (static_cast<uint64_t>(data[5]) << 16));
	i |= (0x000000000000FF00 & (static_cast<uint64_t>(data[6]) <<  8));
	i |= (0x00000000000000FF & data[7]);
	return is;
}