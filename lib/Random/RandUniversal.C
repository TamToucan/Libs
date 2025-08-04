/*
         Notes on the C Language Version

The C code was derived from PD1:<MSDOS.FORTRAN>RANDOM.ARC, and has
been linted with PC-Lint version 4.00a and tested using Microsoft C
version 5.10.  In doing the translation, I tried to change as little
as possible; in fact, all of the variable names and function
(subroutine) names are the same in the C and FORTRAN versions.  Some
of the comment blocks from the FORTRAN version were copied verbatim
into the C version.

The C language version as distributed will compile and execute as a
stand-alone program, allowing you to verify that the random number
generator is working correctly with your compiler (if your compiler
does not support full ANSI function prototypes, minor changes may be
required).  When executed, the program should display the following
(after a delay of several seconds or more):

  6533892.0  14220222.0   7275067.0   6172232.0   8354498.0  10633180.0

Use function main() as an example of how to call the random number
generator from your program.

The remainder of this file was copied from RANDOM.DOC from
PD1:<MSDOS.FORTRAN>RANDOM.ARC.  Thanks to David LaSalle for posting it.

-------------------------------------------------------------------------

When I posted the code for George Marsaglia's universal random number
generator, I forgot to mention that the seed variables can only have
certain values:

i, j, and k  must be between 1 and 178 (not all of them 1)
l must be in the range 0 to 168

I am posting a slightly modified version of the code that requires only two
seed variables which basically have the range 0 to 30000. One nice feature
of this version is that each subsequence of numbers specified by the two
seeds has a length of approximately 10^30. If different parts of a large
calculation is being worked on by several people, each person could be
given his own IJ seed. That would leave 30000 more seeds for the individual
to use -- without fear that any part of the overall calculation would
experience correlations in the random numbers.

Finally, it should also be noted that to save the state of the random number
generator at any point in time, you have to save the entire contents of the
common block
*/

/*
 *========================================================================
 * This passes ALL of the tests for random number generators and has a period
 * of 2^144, is completely portable (gives bit identical results on all
 * machines with at least 24-bit mantissas in the floating point
 * representation).
 *
 * The algorithm is a combination of a Fibonacci sequence (with lags of 97
 * and 33, and operation "subtraction plus one, modulo one") and an
 * "arithmetic sequence" (using subtraction).
 *========================================================================
*/

#include "RandUniversal.h"

namespace RNG {

const int SEED_IJ_MAX = 31328;
const int SEED_KL_MAX = 30081;

/*
 * This is the initialization routine for the random number generator
 * NOTE: The seed variables can have values between:
 *    0 <= IJ <= 31328
 *    0 <= KL <= 30081
 * The random number sequences created by these two seeds are of sufficient
 * length to complete an entire calculation with. For example, if sveral
 * different groups are working on different parts of the same calculation,
 * each group could be assigned its own IJ seed. This would leave each
 * group with 30000 choices for the second seed. That is to say, this
 * random number generator can create 900 million different subsequences --
 * with each subsequence having a length of approximately 10^30.
 *
 * Use IJ = 1802 & KL = 9373 to test the random number generator. The
 * subroutine RANMAR should be used to generate 20000 random numbers.  Then
 * display the next six random numbers generated multiplied by 4096*4096 If
 * the random number generator is working properly, the random numbers
 * should be:
 *     6533892.0  14220222.0  7275067.0 6172232.0  8354498.0 10633180.0
 */
void RandUniversal::initialise(int ij, int kl)
{
    int i, j, k, l, ii, jj, m;
    double s, t;

    i = (ij/177)%177 + 2;
    j = ij%177 + 2;
    k = (kl/169)%178 + 1;
    l = kl%169;

    for (ii=1; ii<=97; ii++)
    {
        s = 0.0;
        t = 0.5;
        for (jj=1; jj<=24; jj++)
        {
            m = (((i*j)%179)*k) % 179;
            i = j;
            j = k;
            k = m;
            l = (53*l + 1) % 169;
            if ((l*m)%64 >= 32) s += t;
            t *= 0.5;
        }
        u[ii] = s;
    }

    c = 362436.0 / 16777216.0;
    cd = 7654321.0 / 16777216.0;
    cm = 16777213.0 / 16777216.0;

    i97 = 97;
    j97 = 33;
}

void RandUniversal::initialise(unsigned int seed)
{
    initialise(seed%(SEED_IJ_MAX+1), ((seed>>13)^seed)%(SEED_IJ_MAX+1));
}

// Function to rotate an unsigned int left by r
inline
static unsigned int rotateLeft(unsigned int x, int r)
{
    r %= sizeof(x)*8;
    return (x << r) | (x >> (sizeof(x)*8 - r));
}

// seed by more than 32 bits
void RandUniversal::initialise(unsigned int seeds[], int length)
{
    if (length > 1)
    {
        // Just XOR the seeds[2...length] into seeds[0] and [1]
        // rotate the seeds so the order affects the result
        for (int i=2; i < length; ++i)
        {
            seeds[i%2] ^= rotateLeft(seeds[i], i);
        }
        // If an odd length then XOR the last seed into [0] amd [1]
        if (length%2)
        {
            seeds[0] ^= seeds[length-1];
            seeds[1] ^= seeds[length-1];
        }
        initialise((seeds[0]%(SEED_IJ_MAX+1)), seeds[1]%(SEED_KL_MAX+1));
    }
    else
    {
        initialise(seeds[0]);
    }
}

/*
 * This is the random number generator proposed by George Marsaglia in
 * Florida State University Report: FSU-SCRI-87-50
 */
double RandUniversal::getFloat()
{
    double uni;

    uni = u[i97] - u[j97];
    if (uni < 0.0) uni += 1.0;
    u[i97] = uni;
    i97--;
    if (i97==0) i97 = 97;
    j97--;
    if (j97==0) j97 = 97;
    c -= cd;
    if (c<0.0) c += cm;
    uni -= c;
    if (uni<0.0) uni += 1.0;
    return uni;
}

} // namespace

