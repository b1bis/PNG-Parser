#pragma once

#include "PNG/Utils.hpp"
#include "PNG/ImageContent.hpp"
#include "PNG/Chunk.hpp"
#include "PNG/ColorType.hpp"
#include <algorithm>
#include <vector>
#include <functional>
#include <cmath>
#include <utility>

namespace PNG
{
	namespace FilteringFunction
	{
		std::uint8_t Sub(std::uint8_t, std::uint8_t);
		std::uint8_t Up(std::uint8_t, std::uint8_t);
		std::uint8_t Average(std::uint8_t, std::uint8_t, std::uint8_t);
		std::uint8_t Paeth(std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t);
	}

	class ImageContentLoader
	{
	public:
		ImageContentLoader();
		ImageContent Load(std::vector<std::uint8_t>,
			std::pair<std::uint32_t, std::uint32_t> dimension, ColorTypeFlags ct) const;
	private:

		std::vector<std::uint8_t> Uncompress(std::vector<std::uint8_t> deflate, size_t readBufferSize) const;
		void Filter(std::vector<Scanline>& filtered) const;

		std::function<std::uint8_t(std::uint8_t, std::uint8_t)> m_subFunction;
		std::function<std::uint8_t(std::uint8_t, std::uint8_t)> m_upFunction;
		std::function<std::uint8_t(std::uint8_t, std::uint8_t, std::uint8_t)> m_averageFunction;
		std::function<std::uint8_t(std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t)> m_paethFunction;
	};
}