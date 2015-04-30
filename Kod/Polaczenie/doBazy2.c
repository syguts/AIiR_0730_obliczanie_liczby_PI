#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv[]) {
   MYSQL *conn;
   MYSQL_RES *res;
   MYSQL_ROW row = NULL;
   char *server = "192.168.1.6";                               /* set address of server */
   char *user = "admin";
   char *password = "admin";                                     /* set me first */
   char *database = "django_db";
   conn = mysql_init(NULL);
   int figurePoints;
   char *taskID, *dateTask, *userID; 


      /* Connect to database */
      if (!mysql_real_connect(conn, server,
          user, password, database, 0, NULL, 0)) {

         fprintf(stderr, "%s\n", mysql_error(conn));
         exit(1);

      }
      
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
   taskID = row[0];
   figurePoints = atoi(row[1]);
   dateTask = row[2];
   userID = row[3];

   printf("***task id %s\n", userID);

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
   float ourvalue = 3.14f;
   *zapytanie = '\0';
   /* add row to done_task */
   snprintf(zapytanie, 512, "INSERT INTO PI2_donetask (userID_id, numberOfPoints, add_date, value) VALUES(%s, %d, %s, %f)", userID, figurePoints, dateTask, ourvalues);
   printf ("Nasz answer %s \n", zapytanie);
      if (mysql_query(conn, zapytanie)) 
      {
         fprintf(stderr, "%s\n", mysql_error(conn));
         exit(1);
      }

   printf("Dodanie do donetask\n");

   /* close connection */
   mysql_close(conn);
}
