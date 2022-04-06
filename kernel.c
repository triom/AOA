#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
/* original */

// void baseline(int n, float a[n], float b[n], float c[n], float d[20])
// {

//     unsigned i, k;

//     // all elements in b are assumed positive

//     for (k = 0; k < 20; k++)
//     {
//         for (i = 0; i < n; i++)
//         {
//             if (b[i] >= 0.0 && b[i] < 1.0)
//             {
//                 a[i] += exp(b[i] + d[k]) / c[i];
//             }
//             else if (b[i] >= 1.0)
//             {
//                 a[i] += (b[i] * d[k]) / c[i];
//             }
//         }
//     }
// }

/* OPT1 */

// fire du deroulage de boucle
//
void baseline(int n, float a[n], float b[n], float c[n], float d[20])
{

    unsigned i, k;

    // all elements in b are assumed positive

    for (k = 0; k < 20; k++)
    {
        float D = d[k]; // initialisation de D pour remplacer le tableau d
        for (i = 0; i < n; i++)
        {
            float C = 1 / b[i]; // remplacer le b[i] par sa reciproque et faire une multiplication à la place

            if (b[i] >= 0.0 && b[i] < 1.0)
            {
                a[i] += expf(b[i] + D) * C;
            }
            else if (b[i] >= 1.0)
            {
                a[i] += (b[i] * D) * C;
            }
        }
    }
}
