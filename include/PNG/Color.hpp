#pragma once

#include "PNG/Utils.hpp"
#include <iostream>
#include <iomanip>

namespace PNG 
{
	// Hold any PNG-8 color
	class Color
	{
	public:
		friend std::ostream& operator<<(std::ostream&, Color);
		Color() = default;
		Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 0xFF) : 
			m_r { r }, m_g { g }, m_b { b }, m_a { a } {}
		Color(std::uint8_t grayscale, std::uint8_t a = 0xFF) :
			m_r{ grayscale }, m_g{ grayscale }, m_b{ grayscale }, m_a{ a } {}

		std::uint8_t GetR() const { return m_r; }
		std::uint8_t GetG() const { return m_g; }
		std::uint8_t GetB() const { return m_b; }
		std::uint8_t GetA() const { return m_a; }

	private:
		std::uint8_t m_r, m_g, m_b, m_a;
	};
}