#include "sequence_algorithms.hpp"

void SequenceAlgorithm_base::callback(sequence_t &current_step)
{
    throw std::runtime_error("Call of pure virtual function\n");
}

void LeftRight_UpDown::callback(sequence_t &current_step)
{
    uint8_t* direction = reinterpret_cast<uint8_t*>((&current_step.x) + (current_step.round & 1));
    uint8_t* shift = reinterpret_cast<uint8_t*>((&current_step.y) - (current_step.round & 1));

    (*direction)++;
    if ((*direction) > 3)
    {
        (*direction) = 0;
        (*shift)++ ;
    }
        
    if ((*shift) > 3)
    {
        (*shift) = 0;
        current_step.round++ ;
    }
};


void SpiralSequence::callback(sequence_t &current_step)
{
    current_step.x++;
    if (current_step.x > 3)
    {
        current_step.x = 0;
        current_step.y++ ;
    }
        
    if (current_step.y > 3)
    {
        current_step.y = 0;
        current_step.round++ ;
    }
}
