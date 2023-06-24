#include "sequence_algorithm.hpp"

void SequnceAlgorithm_base::callback()
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
