#ifndef RANDOM_GAUSSIAN_DIST_H
#define RANDOM_GAUSSIAN_DIST_H

#include "I_Random.h"
#include <cmath>

namespace RNG {

//
// Returns random values with Gaussian Dist
// 
class GaussianDist
{
public:
    // RNG not owned by this class
    GaussianDist(I_Random* pRNG) : m_pRNG(pRNG), m_gotNext(false) { }

    virtual ~GaussianDist() { }

    virtual float getFloat()
    {
        // Two numbers are generated each call so save one of them
        // to return in the next call
        if (m_gotNext)
        {
            m_gotNext = false;
            return m_next;
        }
        else
        {
            // Thanks to http://www.taygeta.com/random/gaussian.html
            float x1, x2, w, y1, y2;

            do {
                x1 = 2.0 * m_pRNG->getFloat() - 1.0;
                x2 = 2.0 * m_pRNG->getFloat() - 1.0;
                w = x1 * x1 + x2 * x2;
            } while ( w >= 1.0 );

            w = sqrt( (-2.0 * log( w ) ) / w );
            y1 = x1 * w;
            y2 = x2 * w;

            m_gotNext = true;
            m_next = y2;
            return y1;
        }
    }
private:
    I_Random* m_pRNG;
    bool m_gotNext;
    float m_next;
};

} // namespace

#endif
