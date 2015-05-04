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
   	clock_t start=clock();
   	double	homepi,         					/* value of pi calculated by current task */
   		pisum,	        						   /* sum of tasks' pi values */
   		avepi;	        						   /* average pi value for all iterations */
   	int	taskid,	        						/* task ID - also used as seed number */
   		numtasks,       						   /* number of tasks */
   		rc,             						   /* return code */
   		i,
   		DARTS = 0,
   		ROUNDS = 1;
   	long double	pi;	        					/* average of pi after "darts" is thrown */
   	MPI_Status status;

      /* Variables for database connection*/
      MYSQL *conn;
      MYSQL_RES *res;
      MYSQL_ROW row = NULL;
      char *server = "192.168.1.10";                               /* set address of server */
      char *user = "admin";
      char *password = "admin";                                 
      char *database = "django_db";
      conn = mysql_init(NULL);
      int figurePoints;
      char taskID[11], dateTask[25], userID[10], zapytanie[512]; 
            
            /* Connect to database */
            if (!mysql_real_connect(conn, server,
                user, password, database, 0, NULL, 0)) {

                     fprintf(stderr, "%s\n", mysql_error(conn));
                     exit(1);

            }

      /* Obtain number of tasks and task ID */
      MPI_Init(&argc,&argv);
      MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
      MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
      printf ("MPI task %d has started...\n", taskid);

      /* Set seed for random number generator equal to task ID */
      srandom (taskid);

      while(1)
      {
               /* waiting for task */
                while(row == NULL)
                {
                     /* send SQL query */
                        if (mysql_query(conn, "SELECT * FROM PI2_task limit 1")) 
                        {
                           fprintf(stderr, "%s\n", mysql_error(conn));
                           exit(1);
                        }

                     res = mysql_use_result(conn);
                     row = mysql_fetch_row(res);
                     printf("Waiting for task...\n");
                     sleep(1);
                }
                  
      /* output table name */
      printf("Downloaded data:\n");
      printf("TaskID: %s FigurePoints: %s DataTask: %s UserID %s \n", row[0], row[1], row[2], row[3]);

      /* save data from database */
      strcpy(taskID,row[0]);
      figurePoints = atoi(row[1]);
      strcpy(dateTask,row[2]);
      strcpy(userID, row[3]);
      printf("***dateTask: %s\n", dateTask);

      /* Number of random points */
      DARTS = figurePoints;

      /* prepare answer to database - delete task */
      
      snprintf(zapytanie, 512, "DELETE FROM PI2_task WHERE ID=%s", row[0]);
      mysql_free_result(res);
      printf ("Nasz answer %s \n", zapytanie);

         if (mysql_query(conn, zapytanie)) 
         {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
         }

      printf("Deleted first task.\n");

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
					    printf("After %d throws, average value of pi = %10.16f\n",
        				 (DARTS * (i + 1)),avepi);
                   snprintf(zapytanie, 512, "INSERT INTO PI2_donetask (userID_id, numberOfPoints, add_date, value) VALUES(%s, %d, '%s', %.6f)", userID, figurePoints, dateTask, avepi);
                   printf ("Nasz answer %s \n", zapytanie);
                     if (mysql_query(conn, zapytanie)) 
                     {
                        fprintf(stderr, "%s\n", mysql_error(conn));
                        exit(1);
                     }

                   printf("Dodanie do donetask\n");
			      }    
         } 

         if (taskid == MASTER)
         { 
		      printf ("\nReal value of PI: 3.1415926535897 \n");
	      }

	         

	         /* The finalize timers and display time for runnig algorithm */
	         clock_t end=clock();
	         float seconds = (float)(end - start) / CLOCKS_PER_SEC;
	         printf("\nCzas trwania algorytmu: %f\n", seconds);
            row = NULL;
  
      }
   MPI_Finalize();
   mysql_close(conn);
	return 0;
}

long double dboard(int darts)
{
	#define sqr(x)	((x)*(x))
	long random(void);
	double x_coord, y_coord, pi, r; 
	int score, n;
	unsigned int cconst;  /* must be 4-bytes in size */
   int counterLoop=0;
	/*************************************************************************
	 * The cconst variable must be 4 bytes. We check this and bail if it is
 	 * not the right size
 	************************************************************************/
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
            if(counterLoop == n){
               printf("Zapytanie %d\n", counterLoop);
               counterLoop += darts/10;
               sleep(3);
            }
      	  	  /* generate random numbers for x and y coordinates */
      		r = (double)random()/cconst;
     		   x_coord = (2.0 * r) - 1.0;
      		r = (double)random()/cconst;
      		y_coord = (2.0 * r) - 1.0;

     		     /* if dart lands in circle, increment score */
      			if ((sqr(x_coord) + sqr(y_coord)) <= 1.0)
           			score++;
      	}

		/* calculate pi */
		pi = 4.0 * (double)score/(double)darts;
		return(pi);
} 
