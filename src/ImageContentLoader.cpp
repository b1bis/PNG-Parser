#include "PNG/ImageContentLoader.hpp"

namespace PNG
{
	std::uint8_t FilteringFunction::Sub(std::uint8_t x, std::uint8_t left)
	{
		return static_cast<std::uint8_t>((x + left) % 256);
	}
	std::uint8_t FilteringFunction::Up(std::uint8_t x, std::uint8_t above)
	{
		return static_cast<std::uint8_t>((x + above) % 256);
	}
	std::uint8_t FilteringFunction::Average(std::uint8_t x, std::uint8_t left, std::uint8_t above)
	{
		return static_cast<std::uint8_t>(static_cast<std::uint8_t>(x + std::floor((left + above) / 2)) %  256);
	}
	std::uint8_t FilteringFunction::Paeth(std::uint8_t x, std::uint8_t left, std::uint8_t above, std::uint8_t upperLeft)
	{
		int pLeft = above - upperLeft;
		int pAbove = left - upperLeft;
		int pUpperLeft = std::abs(pLeft + pAbove);
		pLeft = std::abs(pLeft);
		pAbove = std::abs(pAbove);
		std::uint8_t nearest;

		if (pLeft <= pAbove && pLeft <= pUpperLeft) nearest = left;
		else if (pAbove <= pUpperLeft) nearest = above;
		else nearest = upperLeft;

		return static_cast<std::uint8_t>((x + nearest) % 256);
	}

	ImageContentLoader::ImageContentLoader() :
		m_subFunction { FilteringFunction::Sub },
		m_upFunction { FilteringFunction::Up },
		m_averageFunction { FilteringFunction::Average },
		m_paethFunction { FilteringFunction::Paeth }
	{
	}

	ImageContent ImageContentLoader::Load(std::vector<std::uint8_t> rawData, 
		std::pair<std::uint32_t, std::uint32_t> dimension, ColorTypeFlags ct) const
	{
		size_t channelNumber = ct.ChannelsNumber();
		std::vector<Scanline> scanlines;
		{
			std::vector<std::uint8_t> uncompressedData{ Uncompress(rawData,
				static_cast<size_t>(dimension.first) * static_cast<size_t>(dimension.second) * channelNumber
				+ static_cast<size_t>(dimension.second)) };
			scanlines = Scanline::ParseScanlines(uncompressedData, dimension.first, channelNumber);
		}
		Filter(scanlines);

		ImageContent imageContent;

		for (const Scanline& scanline : scanlines)
		{
			imageContent.AddScanline(scanline);
		}

		return imageContent;
	}

	std::vector<std::uint8_t> ImageContentLoader::Uncompress(std::vector<std::uint8_t> deflate, size_t readBufferSize) const
	{
		return Inflate(deflate, readBufferSize);
	}

	void ImageContentLoader::Filter (std::vector<Scanline>& filtered) const
	{
		for (auto slIt = filtered.begin(); slIt != filtered.end(); ++slIt)
		{
			for (auto channelIt = slIt->data.begin(); channelIt != slIt->data.end(); ++channelIt)
			{
				std::vector<std::uint8_t>::iterator leftIt{ channelIt->begin() }, aboveIt;
				std::uint8_t left = 0, upperLeft = 0;

				if (slIt->filteringType == FilteringType::Average 
					|| slIt->filteringType == FilteringType::Paeth || slIt->filteringType == FilteringType::Up)
				{
					aboveIt =
						((slIt - 1)->data.begin() + std::distance(slIt->data.begin(), channelIt))->begin();
				}

				switch (slIt->filteringType)
				{
				case FilteringType::None:
					break;
				case FilteringType::Sub:
					std::transform(channelIt->begin() + 1, channelIt->end(), channelIt->begin(), channelIt->begin() + 1, m_subFunction);
					break;
				case FilteringType::Up:
					std::transform(channelIt->begin(), channelIt->end(), aboveIt, channelIt->begin(), m_upFunction);
					break;
				case FilteringType::Average:

					for (auto xIt = channelIt->begin(); xIt != channelIt->end(); xIt++)
					{
						*xIt = m_averageFunction(*xIt, left, *aboveIt);
						left = *leftIt;
						leftIt++, aboveIt++;
					}
					break;
				case FilteringType::Paeth:
					for (auto xIt = channelIt->begin(); xIt != channelIt->end(); xIt++)
					{
						*xIt = m_paethFunction(*xIt, left, *aboveIt, upperLeft);
						left = *leftIt;
						upperLeft = *aboveIt;
						leftIt++, aboveIt++;
					}
					break;
				default:
					return;
				}
			}
		}
	}
}