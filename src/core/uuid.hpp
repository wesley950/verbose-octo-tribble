#pragma once

#include <cstdint>

class UUID {
public:
    UUID();

    int64_t get() { return m_ID; }

private:
    int64_t m_ID = 0;
};
