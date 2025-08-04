#ifndef RAND_MERSENNE_H
#define RAND_MERSENNE_H

#include "I_Random.h"

namespace RNG {

class RandMersenne : public I_Random
{
public:
    // constructor
    RandMersenne(unsigned int seed);

    // destructor
    virtual ~RandMersenne();

    // re-seed
    virtual void initialise(unsigned int seed);

    // seed by more than 32 bits
    virtual void initialise(unsigned int seeds[], int length);

    // output random float
    virtual double getFloat();

private:
    I_Random::uint32 get32bits();

    // state vector
    I_Random::uint32* m_state;
    // index into state
    int m_idx;
};

} // namespace

#endif

