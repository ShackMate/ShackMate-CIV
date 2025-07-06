#pragma once

// -------------------------------------------------------------------------
// Project Configuration (defer to civ_config.h for CI-V specific settings)
// -------------------------------------------------------------------------

// Include CI-V specific configuration
#include "civ_config.h"

// Memory Constants
static constexpr uint32_t CRITICAL_HEAP_THRESHOLD = 30000;

// Helper function to check valid FROM address using list from civ_config.h
inline bool isValidFromAddress(uint8_t fromAddr)
{
    for (auto addr : VALID_FROM_ADDRS)
    {
        if (fromAddr == addr)
            return true;
    }
    return false;
}

// Helper function to check full CI-V frame validity (start, end, length, FROM address)
inline bool isValidCIVFrame(const uint8_t *data, size_t len)
{
    if (len < 7)
        return false; // Too short for a valid CI-V frame
    if (data[0] != 0xFE || data[1] != 0xFE)
        return false; // Must start with FE FE
    if (data[len - 1] != 0xFD)
        return false; // Must end with FD
    return isValidFromAddress(data[3]);
}

// Helper function to extract and process all valid CI-V frames from a buffer
inline void extractAndProcessCIVFrames(const uint8_t *buf, size_t len, std::function<void(const uint8_t *, size_t)> processFrame)
{
    size_t i = 0;
    while (i + 6 < len)
    { // Minimum frame length
        // Look for frame start
        if (buf[i] == 0xFE && buf[i + 1] == 0xFE)
        {
            // Look for frame end
            size_t end = i + 2;
            while (end < len && buf[end] != 0xFD)
                end++;
            if (end < len && buf[end] == 0xFD)
            {
                size_t frameLen = end - i + 1;
                if (isValidCIVFrame(buf + i, frameLen))
                {
                    processFrame(buf + i, frameLen); // Call user-supplied handler for valid frame
                }
                i = end + 1; // Move to next possible frame
            }
            else
            {
                // No end found, break and wait for more data
                break;
            }
        }
        else
        {
            i++; // Not a frame start, move forward
        }
    }
}
