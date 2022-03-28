#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
 #include <time.h>

#define NB_METAS 31

extern uint64_t rdtsc ();

extern void baseline (int n, float a[n], float b[n], float c[n], float d[20]);

static void init_array (int n, float Tab[n]) {
   
   int i;

   for (i=0; i<n; i++)
   {
      Tab[i] = (float) rand() / RAND_MAX;
   }
}


static void print_array (int n, float Tab[n]) {
   int i;

   for (i=0; i<n; i++)
   {
      printf ("%f\n", Tab[i]);
   }
}


int main (int argc, char *argv[]) {

   /* check command line arguments */

   if (argc != 4) {
      fprintf (stderr, "Usage: %s <size> <nb warmup repets> <nb measure repets>\n", argv[0]);
      abort();
   }

   int i, m;
   
   clock_t start, end;	// to measure time taken
   double cpu_time_used;
   

   /* get command line arguments */

   start = clock();		// Start time
   
   int size = atoi (argv[1]); /* matrix size */
   int repw = atoi (argv[2]); /* repetition number */
   int repm = atoi (argv[3]); /* repetition number */

   for (m=0; m<NB_METAS; m++) {
      /* allocate arrays */

      float (*a) = malloc (size * sizeof (float) );
      float (*b) = malloc (size * sizeof (float) );
      float (*c) = malloc (size * sizeof (float) );
      float d[20];

      /* init arrays */
      srand(0);
      init_array (size, a);
      init_array (size, b);
      init_array (size, c);
      init_array (20, d);

      /* warmup (repw repetitions in first meta, 1 repet in next metas) */
      if (m == 0) {
         for (i=0; i<repw; i++)
         {
            baseline (size, a, b, c,d);
         }
      } else {
         baseline (size, a, b, c,d);
      }

      /* measure repm repetitions */
      uint64_t t1 = rdtsc();
      
      for (i=0; i<repm; i++)
      {
         baseline (size, a, b, c,d);
      }
      
      uint64_t t2 = rdtsc();

      /* print performance */
      printf ("%.2f cycles/FMA\n",  (t2 - t1) / ((float) size * size * size * repm));

      printf ("*************************************\n");
      
      /* print output */
       print_array (m, a);

      /* free arrays */
      free (a);
      free (b);
      free (c);
   }
   
    	end = clock();		//End time measure

     	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;	// time of execution

 	printf ("Temps d'éxécution : %f \n", cpu_time_used);
 
   return EXIT_SUCCESS;
}
