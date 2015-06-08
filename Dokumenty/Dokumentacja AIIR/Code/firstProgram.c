/**
 Author : Pawel Sternik
 Date : 22.05.2015
 **/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mysql/mysql.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char* argv[]) {
   	FILE *fp;
	 /* Variables for database connection*/
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row = NULL;
	char *server = "192.168.1.103";                               
	char *user = "admin";
	char *password = "admin";                                
	char *database = "django_db";
	conn = mysql_init(NULL);
	int figurePoints, numberOfThreads;
	char taskID[11], doneTaskID[11], dateTask[25],
         userID[10], zapytanie[512], napisek[25],
         polecenie[200], wynik[30];
	    /* Connect to database */
	    if (!mysql_real_connect(conn, server,
	          					user, password, 
	          					database, 0, NULL, 0)) {
	        fprintf(stderr, "%s\n", mysql_error(conn));
	        exit(1);
	    }
		while(1) {		
				/* Waiting for task */
			    while(row == NULL) {                  
			        	if (mysql_query(conn, "SELECT * FROM PI2_task limit 1")) {
			                fprintf(stderr, "%s\n", mysql_error(conn));
			                exit(1);
			            }
					res = mysql_use_result(conn);
			        row = mysql_fetch_row(res);
			        printf("Waiting for task...\n");
			        sleep(1);
			    }

			/* Output table name */
			printf("Downloaded data:\n");
			printf("TaskID: %s FigurePoints: %s DataTask: %s UserID %s NumberOfTask %s\n", row[0], row[1], row[2], row[3], row[4]);
			 /* Save data from database */
		    strcpy(taskID,row[0]);
		    figurePoints = atoi(row[1]);
		    numberOfThreads = atoi(row[4]);
		    strcpy(dateTask,row[2]);
		    strcpy(userID, row[3]);
		    strcpy(napisek, "Zadanie w trakcie");
		 
		    /* Number of random points */
		    int zakres = figurePoints/numberOfThreads;
		    DARTS = zakres;
		    snprintf(zapytanie, 512, "DELETE FROM PI2_task WHERE ID=%s", row[0]);
		    mysql_free_result(res);    
		    printf ("Nasz answer %s \n", zapytanie);
		        if (mysql_query(conn, zapytanie)) {
		            fprintf(stderr, "%s\n", mysql_error(conn));
		            exit(1);
		        }
		    printf("Deleted first task.\n");

		    /* Answer about start works algorithm */
		    snprintf(zapytanie, 512, "INSERT INTO PI2_donetask (userID_id, numberOfPoints, add_date, value) VALUES(%s, %d, '%s', '%s')", userID, figurePoints, dateTask, napisek);
		        if (mysql_query(conn, zapytanie)) {
		            fprintf(stderr, "%s\n", mysql_error(conn));
		            exit(1);
		        }
		    snprintf(polecenie, 200, "mpirun -np %d second %d >> wynik.txt", numberOfThreads, figurePoints);
		    // Wywolanie drugiego programu
		    system(polecenie);
		    fp = fopen("wynik.txt", "r");
		    fscanf(fp,"%s", wynik);
		    printf ("WYNIK: %s\n", wynik);
		    fclose(fp);
		    remove("wynik.txt");
		    snprintf(zapytanie, 512, "SELECT * FROM PI2_donetask ORDER BY add_date desc limit 1");
		        if (mysql_query(conn, zapytanie))
		        {
		            fprintf(stderr, "%s\n", mysql_error(conn));
		            exit(1);
		        }
		    res = mysql_use_result(conn);
		    row = mysql_fetch_row(res);
		    strcpy(doneTaskID,row[0]);
		    mysql_free_result(res);
		    snprintf(zapytanie, 512, "UPDATE PI2_donetask SET value=%s WHERE id=%s", wynik, doneTaskID);
		    printf ("Nasz answer %s \n", zapytanie);
				if (mysql_query(conn, zapytanie))
				{
				   fprintf(stderr, "%s\n", mysql_error(conn));
				   exit(1);
				}
			printf("Dodanie do donetask\n");
			row = NULL;
	}
	mysql_close(conn);
	return 0;
}