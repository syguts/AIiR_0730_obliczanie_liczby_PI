// Obliczanie_liczby_pi.cpp :wersja zwykla -jednowatkowa 
// Autor : Pawel Sternik 
// Data : 17.03.2015
// Metoda Monte Carlo wyznaczania liczby Pi


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
 
using namespace std;
 
void PobieranieDanych(int &iloscPunktow)
{
        cout << "Prosze podac ilosc wszystkich punktow: ";
        cin >> iloscPunktow;          
}
 
int main( int argc, char * argv[] )
{
        // Delaracja wszystkich zmiennych
        int liczbaWszystkichPunktow, bokKwadratu,
            poleKwadratu, liczbaPunktowKolo = 0;
        double promienKola;
        double **wszystkiePunkty;      
        long double mojePi;
        srand(time(NULL));
        // Pobieranie od uzytkownia liczby punktow
        PobieranieDanych(liczbaWszystkichPunktow);
        bokKwadratu = 1;
        poleKwadratu = 1;
        promienKola = bokKwadratu / 2;
        // Utworzenie macierzy do przechowywania punktow w kwadracie
        wszystkiePunkty = new double*[liczbaWszystkichPunktow];
                for(int i=0; i < liczbaWszystkichPunktow; i++)                 
                {
                        wszystkiePunkty[i] = new double[2];            
                }
    
        // Losowanie wspolrzednych punktu w kwadracie z zakresu -0,5 do 0,5
                for(int i=0; i < liczbaWszystkichPunktow; i++)                          {
                                for(int j=0; j < 2 ; j++)
                                {
                                        double a = ( rand() % 10000 ) - 5000;
                                        a = a / 10000;
                                        wszystkiePunkty[i][j] = a;
                                }
                }
                               
                for(int i=0; i < liczbaWszystkichPunktow; i++)
                {
                	double potega = pow(wszystkiePunkty[i][0], 2) + pow(wszystkiePunkty[i][1], 2);
                        double odleglosc = sqrt(potega);
                        	if(odleglosc <= 0.5)
                                {
                                	liczbaPunktowKolo++;
                                }
                }

	// "WYSWIETLENIE REZULTATOW DZIALANIA PROGRAMU - POROWNANIE"
	cout << "----------------------------------------------------------------\n";
	cout << "Liczba punktow w kole: " << liczbaPunktowKolo
         <<" na " << liczbaWszystkichPunktow << "\n";
    mojePi = ((double)liczbaPunktowKolo/(double)liczbaWszystkichPunktow) * 4.0;
    cout << "Moje  Pi = " << mojePi << "\n";
    cout << "Orginalne Pi = 3.14159265359\n";
	cout << "----------------------------------------------------------------\n";

         // Zwolnienie pamieci zaalokowanej przez macierz
		for(int i=0; i < liczbaWszystkichPunktow; i++)
        {
            delete []wszystkiePunkty[i];
        }
                               
    delete []wszystkiePunkty;
    return 0;
}
