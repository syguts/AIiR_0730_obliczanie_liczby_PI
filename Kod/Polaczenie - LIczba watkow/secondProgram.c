/**
 Calculate Pi with MPI protocol
 Author : Paweł Sternik
 Date: 22.05.2015
 **/
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mysql/mysql.h>
#include <string.h>
#include <stdbool.h>
 
void srandom (unsigned seed);
long double dboard (int darts);    
#define MASTER 0      
 
int main (int argc, char *argv[]) 
{
      srandom(time(NULL));
      clock_t   start=clock();
      double    homepi,                      /* value of pi calculated by current task */
                pisum,                       /* sum of tasks' pi values */
                avepi;                       /* average pi value for all iterations */
      int       taskid,                      /* task ID - also used as seed number */
                numtasks,                    /* number of tasks */
                rc,                          /* return code */
                i,
                DARTS = 0,
                ROUNDS = 1;
      long double     pi;                    /* average of pi after "darts" is thrown */
      MPI_Status status;

      /* Obtain number of tasks and task ID */
      MPI_Init(&argc,&argv);
      MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
      MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
 
      /* Set seed for random number generator equal to task ID */
      srandom (taskid);
               
      /* Number of random points */
      int zakres = atoi(argv[1])/numtasks;
      DARTS = zakres;
      avepi = 0;
               
         for (i = 0; i < ROUNDS; i++)
         {
              /* All tasks calculate pi using dartboard algorithm */
              homepi = dboard(DARTS);
              rc = MPI_Reduce(&homepi, &pisum, 1, MPI_DOUBLE, MPI_SUM,
                     MASTER, MPI_COMM_WORLD);
               
                 if (rc != MPI_SUCCESS)
                 {
                                    printf("%d: failure on mpc_reduce\n", taskid);
                 }

              /* Master computes average for this iteration and all iterations */
                 if (taskid == MASTER)
                 {
                      pi = pisum/numtasks;
                      avepi = ((avepi * i) + pi)/(i + 1);
                      printf("%10.16f\n", avepi);
                 }    
         }
 

    /* The finalize timers and display time for runnig algorithm */
    clock_t end=clock();
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    MPI_Finalize();
    return 0;
}
 
long double dboard(int darts)
{
        #define sqr(x)  ((x)*(x))
        long random(void);
        double x_coord, y_coord, pi, r;
        int score, n;
        unsigned int cconst;  /* must be 4-bytes in size */
        int counterLoop=0;
            if (sizeof(cconst) != 4)
            {
                    printf("Wrong data size for cconst variable in dboard routine!\n");
                    exit(1);
            }
        /* 2 bit shifted to MAX_RAND later used to scale random number between 0 and 1 */
        cconst = 2 << (31 - 1);
        score = 0;
        /* "throw darts at board" */
           for (n = 0; n < darts; n++)
           {
                    if(counterLoop == n)
                    {
                        counterLoop += darts/10;
                    }
               /* generate random numbers for x and y coordinates */
               r = (double)random()/cconst;
               x_coord = (2.0 * r) - 1.0;
               r = (double)random()/cconst;
               y_coord = (2.0 * r) - 1.0;
 
                     /* if dart lands in circle, increment score */
                    if ((sqr(x_coord) + sqr(y_coord)) <= 1.0)
                    {
                        score++;
                    }
           }
 
        /* calculate pi */
        pi = 4.0 * (double)score/(double)darts;
        return(pi);
}