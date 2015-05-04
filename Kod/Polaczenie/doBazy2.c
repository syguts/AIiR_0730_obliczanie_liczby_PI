#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv[]) {
   MYSQL *conn;
   MYSQL_RES *res;
   MYSQL_ROW row = NULL;
   char *server = "192.168.1.10";                               /* set address of server */
   char *user = "admin";
   char *password = "admin";                                 
   char *database = "django_db";
   conn = mysql_init(NULL);
   int figurePoints;
   char taskID[11], dateTask[25], userID[10]; 



         /* Connect to database */
         if (!mysql_real_connect(conn, server,
             user, password, database, 0, NULL, 0)) {

                  fprintf(stderr, "%s\n", mysql_error(conn));
                  exit(1);

         }

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

            /* prepare answer to database - delete task */
            char zapytanie[512]; 
            snprintf(zapytanie, 512, "DELETE FROM PI2_task WHERE ID=%s", row[0]);
            mysql_free_result(res);
            printf ("Nasz answer %s \n", zapytanie);

               if (mysql_query(conn, zapytanie)) 
               {
                  fprintf(stderr, "%s\n", mysql_error(conn));
                  exit(1);
               }
            printf("Deleted first task.\n");
            float ourvalue = 3.14;
            *zapytanie = '\0';

            /* add row to done_task */
            printf("***userID: %s\n", userID);
            printf("***figurePoints: %d\n", figurePoints);
            printf("***dateTask: %s\n", dateTask);
            printf("***ourvalue: %.2f\n", ourvalue);
            snprintf(zapytanie, 512, "INSERT INTO PI2_donetask (userID_id, numberOfPoints, add_date, value) VALUES(%s, %d, '%s', %.2f)", userID, figurePoints, dateTask, ourvalue);
            printf ("Nasz answer %s \n", zapytanie);
               if (mysql_query(conn, zapytanie)) 
               {
                  fprintf(stderr, "%s\n", mysql_error(conn));
                  exit(1);
               }

            printf("Dodanie do donetask\n");
            row = NULL;
         }
   /* close connection */
   mysql_close(conn);
}
