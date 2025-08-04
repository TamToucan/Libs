/************************** MERSENNE.CPP ******************** AgF 2001-10-18 *
*  Random Number generator 'Mersenne Twister'                                *
*                                                                            *
*  This random number generator is described in the article by               *
*  M. Matsumoto & T. Nishimura, in:                                          *
*  ACM Transactions on Modeling and Computer Simulation,                     *
*  vol. 8, no. 1, 1998, pp. 3-30.                                            *
*  Details on the initialization scheme can be found at                      *
*  http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html                  *
*                                                                            *
*  Experts consider this an excellent random number generator.               *
*                                                                            *
*  © 2001 - 2004 A. Fog.                                                     *
*  GNU General Public License www.gnu.org/copyleft/gpl.html                  *
*****************************************************************************/

#include "RandMersenne.h"

namespace RNG {

#ifdef MERSENNE_MT11213A
    // 32 bit constants cannot be defined as enum in 16-bit compilers
    #define MERS_N   351
    #define MERS_M   175
    #define MERS_R   19
    #define MERS_U   11
    #define MERS_S   7
    #define MERS_T   15
    #define MERS_L   17
    #define MERS_A   0xE4BD75F5
    #define MERS_B   0x655E5280
    #define MERS_C   0xFFD58000
#else
    // constants for MT19937:
    #define MERS_N   624
    #define MERS_M   397
    #define MERS_R   31
    #define MERS_U   11
    #define MERS_S   7
    #define MERS_T   15
    #define MERS_L   18
    #define MERS_A   0x9908B0DF
    #define MERS_B   0x9D2C5680
    #define MERS_C   0xEFC60000
#endif

RandMersenne::RandMersenne(unsigned int seed) : I_Random()
{
    m_state = new I_Random::uint32[MERS_N];
    initialise(seed);
}

RandMersenne::~RandMersenne()
{
    delete[] m_state;
}

void RandMersenne::initialise(unsigned int seed)
{
    // re-seed generator
    m_state[0]= (seed & 0xffffffff);
    for (m_idx=1; m_idx < MERS_N; m_idx++)
    {
        m_state[m_idx] = (1812433253UL * (m_state[m_idx-1] ^ (m_state[m_idx-1] >> 30)) + m_idx);
    }
}


void RandMersenne::initialise(unsigned int seeds[], int length)
{
    // seed by more than 32 bits
    int i, j, k;
    initialise(19650218UL);
    if (length <= 0) return;
    i = 1;
    j = 0;
    k = (MERS_N > length ? MERS_N : length);
    for (; k; k--)
    {
        m_state[i] =
            (m_state[i] ^ ((m_state[i-1] ^ (m_state[i-1] >> 30)) * 1664525UL))
            + (seeds[j]&0xffffffff)
            + j;
        i++;
        j++;
        if (i >= MERS_N)
        {
            m_state[0] = m_state[MERS_N-1];
            i=1;
        }
        if (j >= length) j=0;
    }
    for (k = MERS_N-1; k; k--)
    {
        m_state[i] =
            (m_state[i] ^ ((m_state[i-1] ^ (m_state[i-1] >> 30)) *1566083941UL))
            - i;
        if (++i >= MERS_N)
        {
            m_state[0] = m_state[MERS_N-1];
            i=1;
        }
    }
    // MSB is 1; assuring non-zero initial array
    m_state[0] = 0x80000000UL;
}


I_Random::uint32 RandMersenne::get32bits()
{
    I_Random::uint32 y;

    if (m_idx >= MERS_N)
    {
        // generate MERS_N words at one time
        // lower MERS_R bits
        const I_Random::uint32 LOWER_MASK = (1LU << MERS_R) - 1;
        // upper (32 - MERS_R) bits
        const I_Random::uint32 UPPER_MASK = 0xFFFFFFFF << MERS_R;
        static const I_Random::uint32 mag01[2] = { 0, MERS_A };

        int kk;
        for (kk=0; kk < MERS_N-MERS_M; kk++)
        {
            y = (m_state[kk] & UPPER_MASK) | (m_state[kk+1] & LOWER_MASK);
            m_state[kk] = m_state[kk+MERS_M] ^ (y >> 1) ^ mag01[y & 1];
        }

        for (; kk < MERS_N-1; kk++)
        {
            y = (m_state[kk] & UPPER_MASK) | (m_state[kk+1] & LOWER_MASK);
            m_state[kk] = m_state[kk+(MERS_M-MERS_N)] ^ (y >> 1) ^ mag01[y & 1];
        }

        y = (m_state[MERS_N-1] & UPPER_MASK) | (m_state[0] & LOWER_MASK);
        m_state[MERS_N-1] = m_state[MERS_M-1] ^ (y >> 1) ^ mag01[y & 1];
        m_idx = 0;
    }

    y = m_state[m_idx++];

    // Tempering (May be omitted):
    y ^=  y >> MERS_U;
    y ^= (y << MERS_S) & MERS_B;
    y ^= (y << MERS_T) & MERS_C;
    y ^=  y >> MERS_L;
    return y;
}


double RandMersenne::getFloat()
{
    return random2double(get32bits());
}

} // namespace

