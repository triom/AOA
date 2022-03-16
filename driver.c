#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define NB_METAS 31

extern uint64_t rdtsc ();

extern void sgemm (int n, float a[n][n], float b[n][n], float c[n][n]);

static void init_array (int n, float a[n][n]) {
   int i, j;

   for (i=0; i<n; i++)
      for (j=0; j<n; j++)
         a[i][j] = (float) rand() / RAND_MAX;
}

static void print_array (int n, float a[n][n]) {
   int i, j;

   for (i=0; i<n; i++)
      for (j=0; j<n; j++)
         printf ("%f\n", a[i][j]);
}

int main (int argc, char *argv[]) {
   /* check command line arguments */
   if (argc != 4) {
      fprintf (stderr, "Usage: %s <size> <nb warmup repets> <nb measure repets>\n", argv[0]);
      abort();
   }

   int i, m;

   /* get command line arguments */
   int size = atoi (argv[1]); /* matrix size */
   int repw = atoi (argv[2]); /* repetition number */
   int repm = atoi (argv[3]); /* repetition number */

   for (m=0; m<NB_METAS; m++) {
      /* allocate arrays */
      float (*a)[size] = malloc (size * size * sizeof a[0][0]);
      float (*b)[size] = malloc (size * size * sizeof b[0][0]);
      float (*c)[size] = malloc (size * size * sizeof c[0][0]);

      /* init arrays */
      srand(0);
      init_array (size, a);
      init_array (size, b);

      /* warmup (repw repetitions in first meta, 1 repet in next metas) */
      if (m == 0) {
         for (i=0; i<repw; i++)
            sgemm (size, a, b, c);
      } else {
         sgemm (size, a, b, c);
      }

      /* measure repm repetitions */
      uint64_t t1 = rdtsc();
      for (i=0; i<repm; i++)
         sgemm (size, a, b, c);
      uint64_t t2 = rdtsc();

      /* print performance */
      printf ("%.2f cycles/FMA\n",
              (t2 - t1) / ((float) size * size * size * repm));

      /* print output */
      //if (m == 0) print_array (n, c);

      /* free arrays */
      free (a);
      free (b);
      free (c);
   }

   return EXIT_SUCCESS;
}
