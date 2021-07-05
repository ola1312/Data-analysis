#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int main(void)
{
  //deklaracja zmiennych, tablic i wskaźników
  char plik_odczyt[100];
  char plik_zapis[100];
  const int MAX_SIZE = 10000;
  double srednia = 0, odchylenie = 0, suma = 0;
  double liczby[MAX_SIZE];
  double *l = liczby;
  int wybor = 0, n = 0;
  FILE *plik;

  while (wybor != 4)
  {
    //menu
    puts("[1] Wczytaj dane.");
    puts("[2] Wykonaj analizę.");
    puts("[3] Generuj raport.");
    puts("[4] Wyjście.");
    printf("Opcja: ");
    scanf ("%d", &wybor);
    switch(wybor)
    {
    case 1:
      printf("Podaj nazwę pliku do wczytania: "); //zapytanie o nazwę pliku wejściowego
      scanf("%s", plik_odczyt); //pobranie nazwy pliku

      plik = fopen (plik_odczyt, "r");

      if(!plik) //komunikat o błędzie jeśli nie da się otworzyć pliku
      {
        fprintf(stderr, "Nie moge czytac z pliku %s\n", plik_odczyt);
        break;
      }

      //Czyszczenie tablicy
      l = liczby;
      for(int i =0; i<MAX_SIZE; i++)
        *l ++ = 0;
      
      //Wczytanie liczb do tablicy
      n = 0;
      while (!feof (plik) && n < MAX_SIZE)
      {
        fscanf(plik, "%lf\n", &liczby[n]);
        n++;
      }
      printf("Wczytano %d liczb z pliku %s. \n", n, plik_odczyt);

      //Zamknięcie pliku
      fclose(plik);
      break;
      
    case 2:
      //Sprawdzenie czy liczby zostały Wczytane
      if(n<1)
      {
        puts("Przed wykonaniem analizy należy wczytać dane");
        break;
      }

      //Obliczenie średniej
      l = liczby;
      suma = 0;
      for (int i = 0; i<n; i++)
        suma += *l ++;
      srednia = suma/n;
      printf("Średnia wynosi %lf\n", srednia);

      //Odchylenie standardowe
      l = liczby;
      suma = 0;
      for (int i = 0; i<n; i++)
        suma += pow(*l ++ - srednia, 2);
      odchylenie = sqrt(suma/(n-1));
      printf("Odchylenie standardowe wynosi %lf\n", odchylenie);
      break;

    case 3:
      printf("Podaj nazwę pliku do zapisu: "); //zapytanie o nazwę pliku do zapisu
      scanf("%s", plik_zapis); //pobranie nazwy

    plik = fopen (plik_zapis, "w"); //otwarcie pliku do zapisu
    
    fprintf(plik, "Analiza danych z pliku %s\n", plik_odczyt);
    fprintf(plik, "Autor: Aleksandra Sajna\n\n");
    fprintf(plik, "n = %d, nu = %lf, sd = %lf.", n, srednia, odchylenie);

    printf("Raport zapisano w pliku %s.\n", plik_zapis);

    fclose(plik); //zamknięcie pliku
    break;

    case 4:
        //opcja wyjście
        break;
    default:
      puts("Wybrano niewłaściwą opcję"); //kiedy wybierzemy inną opcję niż z menu
    }
  }
  return 0;
}