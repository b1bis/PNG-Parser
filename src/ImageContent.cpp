#include "PNG/ImageContent.hpp"

namespace PNG
{
    void ImageContent::AddScanline(const Scanline& scanline)
    {
        std::vector<Color> line;
        if (scanline.data.size() == 1)
        {
            for (auto gIt = scanline.data[0].begin(); gIt != scanline.data[0].end(); ++gIt)
            {
                line.emplace_back(*gIt);
            }
        }
        else if (scanline.data.size() == 2)
        {
            for (auto gIt = scanline.data[0].begin(), aIt = scanline.data[1].begin(); 
                gIt != scanline.data[0].end(); ++gIt, ++aIt)
            {
                line.emplace_back(*gIt, *aIt);
            }
        }

        else if (scanline.data.size() == 3)
        {
            for (auto rIt = scanline.data[0].begin(), gIt = scanline.data[1].begin(),
                bIt = scanline.data[2].begin();
                rIt != scanline.data[0].end(); ++rIt, ++gIt, ++bIt)
            {
                line.emplace_back(*rIt, *gIt, *bIt);
            }
        }

        else if (scanline.data.size() == 4)
        {
            for (auto rIt = scanline.data[0].begin(), gIt = scanline.data[1].begin(),
                bIt = scanline.data[2].begin(), aIt = scanline.data[3].begin();
                rIt != scanline.data[0].end(); ++rIt, ++gIt, ++bIt, aIt++)
            {
                line.emplace_back(*rIt, *gIt, *bIt, *aIt);
            }
        }
        m_content.push_back(std::move(line));
    }

    Color ImageContent::At(size_t x, size_t y) const
    {
        return m_content.at(y).at(x);
    }
}