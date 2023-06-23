#ifndef SEQUENCE_ALGORITHM
#define SEQUENCE_ALGORITHM

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
    virtual void callback()
    {
        uint8_t* direction = reinterpret_cast<uint8_t*>((&this->x) + (round & 1));
        uint8_t* shift = reinterpret_cast<uint8_t*>((&this->y) - (round & 1));

        (*direction)++;

        if ((*direction) > 3)
        {
            (*direction) = 0;
            (*shift)++ ;
        }
            
        if ((*shift) > 3)
        {
            (*shift) = 0;
            this->round++ ;
        }
    };
};

#endif
