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
 
void PobieranieDanych(int &iloscPunktow)                                // Funkcja do pobierania danych o ilosci Punktow wstrzeliwanych w kwadrat/kolo
{
        cout << "Prosze podac ilosc wszystkich punktow: ";
        cin >> iloscPunktow;          
}
 
int main( int argc, char * argv[] )
{
        int liczbaWszystkichPunktow, bokKwadratu, poleKwadratu,
                        liczbaPunktowKolo = 0;                          // Deklaracja wszystkich zmiennych    
        double promienKola;
        double **wszystkiePunkty;      
        long double mojePi;
        srand(time(NULL));
        PobieranieDanych(liczbaWszystkichPunktow);                      // Pobieram od uzytkownika ile ma byc punktow  
        bokKwadratu = 1;
        poleKwadratu = 1;
        promienKola = bokKwadratu / 2;
        wszystkiePunkty = new double*[liczbaWszystkichPunktow];         // Tworze macierz do przechowywania punktow w kwadracie
               
                for(int i=0; i < liczbaWszystkichPunktow; i++)                 
                {
                        wszystkiePunkty[i] = new double[2];            
                }
       
                for(int i=0; i < liczbaWszystkichPunktow; i++)          // Losuje wspolrzedne punktu w kwadracie z zakresu -0,5 do 0,5
                {
                                for(int j=0; j < 2 ; j++)
                                {
                                        double a = ( rand() % 10000 ) - 5000;
                                        a = a / 10000;
                                       // cout << "A: " << a << "\n";
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

	// "WYSWIETLENIE REZULTATOW DZIALANIA PROGRAMU - POROWNANIE Z ORGINALEM" 	
	cout << "----------------------------------------------------------------\n";
	cout << "Liczba punktow w kole: " << liczbaPunktowKolo<<" na " << liczbaWszystkichPunktow << "\n";
        mojePi = ((double)liczbaPunktowKolo/(double)liczbaWszystkichPunktow) * 4.0;
        cout << "Moje  Pi = " << mojePi << "\n";
        cout << "Orginalne Pi = 3.14159265359\n";
	cout << "----------------------------------------------------------------\n";


		for(int i=0; i < liczbaWszystkichPunktow; i++)                  // Zwolnienie pamieci zaalokowanej przez macierz
        	{
        		delete []wszystkiePunkty[i];
        	}
                               
        delete []wszystkiePunkty;
        return 0;
}
