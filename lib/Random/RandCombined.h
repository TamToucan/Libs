#ifndef RAND_COMBINED_H
#define RAND_COMBINED_H

#include "I_Random.h"

namespace RNG {

template<class RG1, class RG2>
class RandCombined : public I_Random
{
public:
    RandCombined(unsigned int seed) : I_Random()
    {
        m_pRG1 = new RG1(seed);
        m_pRG2 = new RG2(seed+1);
    }

    virtual ~RandCombined()
    {
        delete m_pRG1;
        delete m_pRG2;
    }

    virtual void initialise(unsigned int seed)
    {
        m_pRG1->initialise(seed);
        m_pRG2->initialise(seed+1);
    }
    virtual void initialise(unsigned int seeds[], int length)
    {
        m_pRG1->initialise(seeds, length);
        for (int i=0; i < length; ++i) ++seeds[i];
        m_pRG2->initialise(seeds, length);
    }

    virtual double getFloat()
    {
        long double r = m_pRG1->getFloat() + m_pRG2->getFloat();
        if (r >= 1.) r -= 1.;
        return r;
    }
private:
    RG1* m_pRG1;
    RG2* m_pRG2;
};

} // namespace

#endif

