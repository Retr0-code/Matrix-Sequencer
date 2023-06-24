#ifndef SEQUENCE_ALGORITHM
#define SEQUENCE_ALGORITHM

#include <cstdint>
#include <iostream>

struct sequence_t
{
    uint8_t x;
    uint8_t y;
    uint8_t round;
    sequence_t(uint8_t _x, uint8_t _y, uint8_t _round) : x(_x), y(_y), round(_round) {}
};


struct SequnceAlgorithm_base : public sequence_t
{
    SequnceAlgorithm_base(sequence_t current_step) : sequence_t(current_step)
    {
        callback();
    }

    SequnceAlgorithm_base() = delete;

    SequnceAlgorithm_base(const SequnceAlgorithm_base&) = delete;

    SequnceAlgorithm_base(SequnceAlgorithm_base&&) = delete;


private:
    /*  Default algorithm
        Override this function to implement own algorithm
    */
    virtual void callback();
};

#endif
