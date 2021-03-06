#include "catch.hh"
#include "lib/crc_factories.h"
#include "test_crc_support.h"

namespace
{
    CRC::Value getTestChecksum(size_t numBytes)
    {
        return 0xDECEA5ED & (0xFFFFFFFFUL >> (32 - (numBytes << 3)));
    }
}

TEST_CASE("CRC computing works", "[crc]")
{
    for (auto &crc : createAllCRC())
        SECTION(crc->getSpecs().name)
            testComputing(*crc, crc->getSpecs().test);
}

TEST_CASE("CRC patch appending works", "[crc]")
{
    for (auto &crc : createAllCRC())
        SECTION(crc->getSpecs().name)
            testAppending(*crc, getTestChecksum(crc->getSpecs().numBytes));
}

TEST_CASE("CRC patch inserting works", "[crc]")
{
    for (auto &crc : createAllCRC())
        SECTION(crc->getSpecs().name)
            testInserting(*crc, getTestChecksum(crc->getSpecs().numBytes));
}

TEST_CASE("CRC patch overwriting works", "[crc]")
{
    for (auto &crc : createAllCRC())
        SECTION(crc->getSpecs().name)
            testOverwriting(*crc, getTestChecksum(crc->getSpecs().numBytes));
}
