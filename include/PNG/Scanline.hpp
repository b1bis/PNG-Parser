#pragma once

#include <vector>
#include "PNG/Utils.hpp"

namespace PNG 
{
	struct Scanline
	{
		Scanline(std::vector<std::vector<std::uint8_t>> d, FilteringType ft) :
			data(std::move(d)), filteringType(ft) {}

		Scanline() = default;
		Scanline(const Scanline&) = default;
		Scanline(Scanline&&) = default;

		static std::vector<Scanline> ParseScanlines(const std::vector<std::uint8_t>& rawData, size_t lenght, size_t channelNumber)
		{
			std::vector<Scanline> scanlines{};

			for (auto it = rawData.begin(); it != rawData.end(); it += lenght * channelNumber)
			{
				FilteringType type = ParseFilteringType(*it++);
				std::vector<std::vector<std::uint8_t>> channels(channelNumber);


				for (auto& channel : channels)
				{
					channel.reserve(lenght);
				}

				for (auto rawChannelIt = it; rawChannelIt != (it + (lenght * channelNumber)); rawChannelIt += channelNumber)
				{
					for (auto cIt = channels.begin(); cIt != channels.end(); cIt++)
						cIt->push_back(*(rawChannelIt + std::distance(channels.begin(), cIt)));
				}
				scanlines.emplace_back(std::move(channels), type);
			}
			return scanlines;
		}

		std::vector<std::vector<std::uint8_t>> data;
		FilteringType filteringType = FilteringType::None;
	};
}