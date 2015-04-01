#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <math.h>
using namespace std;

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int *counter;
int przydzialPunktow;
int idWatku=0;

void *MojaFunkcjaDlaWatku(void *arg) 
{
	double x, y, potega, odleglosc;
	pthread_mutex_lock(&mutex1);
	int numerek = idWatku;
	idWatku++;
	cout << endl<< numerek << endl;
	pthread_mutex_unlock(&mutex1);
		for(int i=0; i < przydzialPunktow; i++)
		{
			x  = ( ( (double)rand() / (RAND_MAX) ) * 2) - 1;
			y  = ( ( (double)rand() / (RAND_MAX) ) * 2) - 1;
			potega = pow(x, 2) + pow(y, 2);
                        odleglosc = sqrt(potega);
				if(odleglosc <= 1)
				{
					counter[numerek]+= 1;
				}
		}

        return NULL;	
}

void PobieranieDanych(int &iloscPunktow, int &watki)           // Funkcja do pobierania danych o ilosci Punktow wstrzeliwanych w kwadrat/kolo
{
        cout << "Prosze podac ilosc wszystkich punktow: ";
        cin >> iloscPunktow;
	cout << "Prosze podac ilosc watkow: ";
	cin >> watki;          
}

int main(void) 
{
	int punkty, liczbaWatkow, *tablicaPrzydzialu;
	pthread_t *mojwatek;
	PobieranieDanych(punkty, liczbaWatkow);
	mojwatek = new pthread_t[liczbaWatkow];

	srand(time(NULL));

	tablicaPrzydzialu = new int[liczbaWatkow];
	int sredniaPunktow = punkty / liczbaWatkow;

	counter = new int[liczbaWatkow];
	
		for(int i=0; i < liczbaWatkow -1; i++)
		{
			tablicaPrzydzialu[i] = sredniaPunktow;
		}

	tablicaPrzydzialu[liczbaWatkow-1] = punkty - (sredniaPunktow * (liczbaWatkow-1));
		for(int i=0; i < liczbaWatkow; i++)
		{	
		    przydzialPunktow= tablicaPrzydzialu[i];	
	  		if ( pthread_create( &mojwatek[i], NULL, MojaFunkcjaDlaWatku,NULL))
			{
        			cout << "blad przy tworzeniu watku\n"; 
				abort();
  			}
		}

		for(int i=0; i < 4; i++)
		{		
  			if ( pthread_join ( mojwatek[i], NULL ) ) 
			{
        			cout << "blad w konczeniu watku\n";
        			abort();
  			}
		}
	int suma=0;	
		for(int i=0; i < liczbaWatkow ; i++)
		{
			suma += counter[i];
		}

	// "WYSWIETLENIE REZULTATOW DZIALANIA PROGRAMU - POROWNANIE Z ORGINALEM" 	
	cout << "----------------------------------------------------------------\n";
	cout << "Liczba punktow w kole: " << suma <<" na " << punkty << "\n";
        long double mojePi = ((double)suma/(double)punkty) * 4.0;
        cout << "Moje  Pi = " << mojePi << "\n";
        cout << "Orginalne Pi = 3.14159265359\n";
	cout << "----------------------------------------------------------------\n";

  	exit(0);
}
