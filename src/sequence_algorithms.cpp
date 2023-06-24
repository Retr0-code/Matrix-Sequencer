#include "sequence_algorithms.hpp"

void SequenceAlgorithm_base::callback(sequence_t &current_step)
{
    throw std::runtime_error("Call of pure virtual function\n");
}


void StraightSequence::callback(sequence_t &current_step)
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
    // Change to inner spiral
    if ((current_step.y == (nearest + 1)) && (current_step.x == nearest))
    {
        furthest--;
        nearest++;
    }
	
    // Down
    if ((current_step.x == furthest) && (current_step.y < furthest))
    {
        current_step.y++;
        return;
    }

    // Right
	if ((current_step.x < furthest) && (current_step.y == nearest))
    {
        current_step.x++;
        return;
    }

    // Left
	if ((current_step.y == furthest) && (current_step.x > nearest))
    {
        current_step.x--;
        return;
    }

    // Up
	if ((current_step.x == nearest) && (current_step.y > nearest))
    {
        current_step.y--;
        return;
    }

    // Reset
    else 
    {
        current_step = {0, 0, 0};
        furthest = 3;
        nearest = 0;
    }
}
