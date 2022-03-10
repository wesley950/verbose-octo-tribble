#include "uuid.hpp"

#include <random>

UUID::UUID()
{
    static std::random_device rd {};
    static std::mt19937_64 rng { rd() };
    static std::uniform_int_distribution<int64_t> ud;

    m_ID = ud(rng);
}
