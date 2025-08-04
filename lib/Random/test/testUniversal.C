#include "RandUniversal.h"

#include <time.h>
#include <stdio.h>

int main()
{
    /* random seeds for the test case: */
    unsigned int seeds[2] = { 1802, 9373 };

    RNG::RandUniversal rng(0);
    rng.initialise(seeds, 2);

    /* generate 20,000 random numbers */
    for (int i=0; i < 20000; i++)
    {
        (void) rng.getFloat();
    }

    /*
       If the random number generator is working properly, the next six random
       numbers should be:
     */
    const float expected[6] = {
        6533892.0, 14220222.0, 7275067.0, 6172232.0, 8354498.0, 10633180.0
    };

    for (int i=0; i < 6; i++)
    {
        float f = 4096.0*4096.0*rng.getFloat();
        if (f != expected[i])
        {
            printf("VALUE[%d] FAILED! %12.1f BUT expected %12.1f \n",
                   i, f, expected[i]);
            return 1;
        }
        else
        {
            printf("VALUE[%d] PASSED  %12.1f\n", i, f);
        }
    }
    return 0;
}

