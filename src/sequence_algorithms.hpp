#ifndef SEQUENCE_ALGORITHM
#define SEQUENCE_ALGORITHM

#include <cstdint>
#include <iostream>
#include <memory>

struct sequence_t
{
    uint8_t x;
    uint8_t y;
    uint8_t round;

    sequence_t(uint8_t _x, uint8_t _y, uint8_t _round) : x(_x), y(_y), round(_round) {}
    sequence_t() {x = 0, y = 0, round = 0;}
};


struct SequenceAlgorithm_base
{
    // Override this function to implement own algorithm
    virtual void callback(sequence_t &current_step);
};

struct StraightSequence : public SequenceAlgorithm_base
{
    StraightSequence() = default;

    void callback(sequence_t &current_step) override;
};

struct LeftRight_UpDown : public SequenceAlgorithm_base
{
    LeftRight_UpDown() = default;

    void callback(sequence_t &current_step) override;
};

struct SpiralSequence : public SequenceAlgorithm_base
{
    SpiralSequence() = default;

    void callback(sequence_t &current_step) override;

private:
    uint8_t furthest = 3, nearest = 0;
};

#endif
