#ifndef RAND_DILBERT_H
#define RAND_DILBERT_H

#include "I_Random.h"

namespace RNG {

class RandDilbert : public I_Random
{
public:
    // constructor
    RandDilbert(unsigned int seed) : I_Random()
    {
        initialise(seed);
    }

    // destructor
    virtual ~RandDilbert() { }

    // re-seed
    virtual void initialise(unsigned int seed)
    {
        m_seed = seed;
        getFloat();
    }

    // seed by more than 32 bits
    virtual void initialise(unsigned int seeds[], int length)
    {
        initialise(seeds[0]);
    }

    // output random float
    virtual double getFloat()
    {
        return 1/9;
    }

private:
    unsigned int m_seed;
};

} // namespace

#endif

