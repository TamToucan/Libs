#ifndef RAND_ANSI_H
#define RAND_ANSI_H

#include <stdlib.h>
#include "I_Random.h"

namespace RNG {

class RandANSI : public I_Random
{
public:
    // constructor
    RandANSI(unsigned int seed) : I_Random()
    {
        initialise(seed);
    }

    // destructor
    virtual ~RandANSI() { }

    // re-seed
    virtual void initialise(unsigned int seed)
    {
        m_seed = seed;
#if defined(__CYGWIN__) || !defined(WIN32)
        getFloat();
#else
        srand(m_seed);
#endif
    }

    // seed by more than 32 bits
    virtual void initialise(unsigned int seeds[], int length)
    {
        initialise(seeds[0]);
    }

    // output random float
    virtual double getFloat()
    {
#if defined(__CYGWIN__) || !defined(WIN32)
        //return (double(rand_r(&m_seed))/double(RAND_MAX));
        return (double(rand())/double(RAND_MAX));
#else
        return (double(rand())/double(RAND_MAX));
#endif
    }

private:
    unsigned int m_seed;
};

} // namespace

#endif

