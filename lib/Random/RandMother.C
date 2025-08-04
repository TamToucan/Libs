/************************** MOTHER.CPP ****************** AgF 1999-03-03 *
*  'Mother-of-All' random number generator                               *
*                                                                        *
*  This is a multiply-with-carry type of random number generator         *
*  invented by George Marsaglia.  The algorithm is:                      *
*  S = 2111111111*X[n-4] + 1492*X[n-3] + 1776*X[n-2] + 5115*X[n-1] + C   *
*  X[n] = S modulo 2^32                                                  *
*  C = floor(S / 2^32)                                                   *
*                                                                        *
*  IMPORTANT:
*  This implementation uses a long double for C. Note that not all       *
*  computers and compilers support the long double (80-bit) floating     *
*  point format. It is recommended to use a Borland or Gnu compiler on   *
*  a PC. The Microsoft compiler doesn't support the long double format.  *
*  You will get an error message if your system doesn't support this.    *
*                                                                        *
* © 2002 A. Fog. GNU General Public License www.gnu.org/copyleft/gpl.html*
*************************************************************************/

#include <assert.h>
#include <math.h>
#include "RandMother.h"

namespace RNG {

RandMother::RandMother(unsigned int seed) : I_Random()
{
    // Check that compiler supports 80-bit long double:
    assert(sizeof(long double)>9);
    initialise(seed);
}

RandMother::~RandMother()
{
}

void RandMother::initialise(unsigned int seed)
{
    I_Random::uint32 s = seed&0xffffffff;
    // make random numbers and put them into the buffer
    for (unsigned int i=0; i < (sizeof(x)/sizeof(x[0])); i++)
    {
        s = s * 29943829 - 1;
        x[i] = s * (1./(65536.*65536.));
    }
    // randomize some more
    for (int i=0; i<19; i++) getFloat();
}

void RandMother::initialise(unsigned int seeds[], int length)
{
    initialise(seeds[0]);
}

double RandMother::getFloat()
{
    long double c;
    // This is
    c = (long double)2111111111.0 * x[3]
        + 1492.0 * x[2]
        + 1776.0 * x[1]
        + 5115.0 * x[0]
        + x[4];
    x[4] = floor(double(c));
    x[3] = x[2];
    x[2] = x[1];
    x[1] = x[0];
    x[0] = c - x[4];
    x[4] = x[4] * (1./(65536.*65536.));
    return x[0];
}

} // namespace

