/*************************** EX-RAN.CPP ********************* AgF 2001-11-11 *
*                                                                            *
* Example showing how to use random number generators from class library.    *
*                                                                            *
* Compile for console mode.                                                  *               *
* © 2001 Agner Fog. GNU General Public License www.gnu.org/copyleft/gpl.html *
*****************************************************************************/

#include <stdio.h>
#include <time.h>
#include "I_Random.h"
#include "RandMersenne.h"
#include "RandMother.h"
#include "RandUniversal.h"
#include "RandSimple.h"
#include "RandANSI.h"
#include "RandCombined.h"

static void printRandom(const char* name, RNG::I_Random& rg)
{
    printf("\nUsing %s RNG\n", name);
    // make random integers in interval from 0 to 99, inclusive:
    printf("\n  Random integers in interval from 0 to 99:\n");
    for (int i=0; i<40; i++)
    {
        int ir = rg.getInt(0,99);
        printf("%6i  ", ir);
    }

    // make random floating point numbers in interval from 0 to 1:
    printf("\n\n  Random floating point numbers in interval from 0 to 1:\n");
    for (int i=0; i<32; i++)
    {
        double r = rg.getFloat();
        printf ("%8.6f  ", r);
    }

    // make random floating point numbers in interval from -10 to +10:
    printf("\n\n  Random floating point numbers in interval from -10 to +10:\n");
    for (int i=0; i<32; i++)
    {
        float r = rg.getRange<float>(-10,10);
        printf ("%+8.6f ", r);
    }

    printf("\n");
}

int main()
{
    unsigned int seed = time(0);
#if 0
    RNG::RandMersenne  rg1(seed);
    RNG::RandMother    rg2(seed);
    RNG::RandUniversal rg3(seed);
    RNG::RandSimple    rg4(seed);
    RNG::RandANSI      rg5(seed);
    printRandom("MERSENNE", rg1);
    printRandom("MOTHER", rg2);
    printRandom("UNIVERSAL", rg3);
    printRandom("SIMPLE", rg4);
    printRandom("ANSI", rg5);

    RNG::RandCombined<RNG::RandMersenne, RNG::RandMother> rg6(time(0));
    printRandom("MERSENNE + MOTHER", rg6);
#else
    RNG::RandUniversal rg(seed);
    //RNG::RandSimple rg(seed);
    for (int i=0; i<10000000; ++i)
    {
        float r = rg.getRange<float>(-2,2);
        printf ("%+8.6f\n", r);
        //int r = rg.getInt(-2,2);
        //printf ("%+d\n", r);
    }
#endif
    return 0;
}

