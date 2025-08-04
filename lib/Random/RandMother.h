#ifndef RAND_MOTHER_H
#define RAND_MOTHER_H

#include "I_Random.h"

namespace RNG {

class RandMother : public I_Random
{
public:
    // constructor
    RandMother(unsigned int seed);

    // destructor
    virtual ~RandMother();

    // re-seed
    virtual void initialise(unsigned int seed);

    // seed by more than 32 bits
    virtual void initialise(unsigned int seeds[], int length);

    // output random float
    virtual double getFloat();

private:
    double x[5];                         // history buffer
};

} // namespace

#endif

