#ifndef RAND_UNIVERSAL_H
#define RAND_UNIVERSAL_H

#include "I_Random.h"

namespace RNG {

class RandUniversal : public I_Random
{
public:
    // constructor
    RandUniversal(unsigned int seed) : I_Random()
    {
        initialise(seed);
    }

    // destructor
    virtual ~RandUniversal() { }

    // re-seed
    virtual void initialise(unsigned int seed);

    // seed by more than 32 bits
    virtual void initialise(unsigned int seeds[], int length);

    // output random float
    virtual double getFloat();

private:
    void initialise(int ij, int kl);

    double u[98];
    double c;
    double cd;
    double cm;
    int i97;
    int j97;
};

} // namespace

#endif

