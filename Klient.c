#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h>
#include <sys/wait.h> 
#include <string.h> 
#include <sys/types.h> 
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/wait.h>
#include <sys/time.h>
#define ROZMIAR 1000  
#define Red "\033[31m"
#define Reset "\x1b[0m"
#define Blue "\033[36m"  
#define Green "\033[32m" 
#define Black "\033[30m"
#define BRed "\033[41m"
#define BGreen "\033[42m"
#define Clear "\033[H\033[J" 
#define SIZE 1024

void wyslij_plik(FILE *nazwa_pliku, int sdsocket,struct stat fileinfo,int x)
{
	unsigned char bufor[1024];
	long rozmiar_pliku;
	long wyslano=0;
	long wyslano_razem=0;
	long przeczytano=0;
	long rozmiar_pliku_wyslij;
	rozmiar_pliku_wyslij = htonl(fileinfo.st_size);
	rozmiar_pliku =fileinfo.st_size;
 //printf("Wysylam na serwer - dlugosc pliku: %ld\n", rozmiar_pliku);
 
	if (send(sdsocket, &rozmiar_pliku_wyslij, sizeof(long), 0) != sizeof(long))
        {
      	  printf(BRed"Blad przy wysylaniu wielkosci pliku!\n"Reset);
       	  return;
   		}
 
	printf("    Wyslano\n");
	
	while (wyslano_razem < rozmiar_pliku)
   		{
          przeczytano = fread(bufor, 1, 1024, nazwa_pliku);
          wyslano = send(sdsocket, bufor, przeczytano, 0);
          if (przeczytano != wyslano)
              {break;} 
          wyslano_razem += wyslano;
          if (x != 2)
              {printf("| %ld / %ld | "Green" %0.2f%%\n"Reset, wyslano_razem,rozmiar_pliku,(float)wyslano_razem/(float)rozmiar_pliku*100);}
  		}
    
    if (wyslano_razem >= rozmiar_pliku)
         printf(Green"\nPlik wyslany poprawnie"Reset);
	else
         printf(BRed"\nBlad przy wysylaniu pliku"Reset);
        
return;        
}


void clear() // Czyszczenie konsoli
{
	printf(Clear); 
return;
}

void blad_polecenia() // Wyswietlanie bledu
{
	printf(BRed "\noperacja niedozwolona\n" Reset);  
	printf("Wpisz "Green"'help'"Reset" aby zobaczyc wszystkie polecenia oferowane przez program kliencki\n\n"); 
	
return;
}


void help() // Wyswietlenie panelu pomocy
{
	printf(Clear);
	printf(BGreen); printf(Black);
	printf("\nProjekt - SIK - help"Reset"\n"); 
	printf("Autorzy programow:\n "Blue" 1) Krystian Osinski - klient - s444820\n  2) Szymon Ptaszynski - server - s462035"Reset"");	printf(Reset); printf("\n ------ Grupa13/2rok/Niestacjonarne ------");
	printf("\n\nPolecenia wykonywane przez program kliencki\n");
	printf("----------------------------------------------------------------------------\n");
	printf("1) "Blue"transfer"Reset" ["Green"nazwa_pliku"Reset"] (nawiaz polaczenie z serwerem aby wyslac plik)\n");
	printf("2) "Blue"transfer -two"Reset" ["Green"nazwa_pliku_1"Reset"] ["Green"nazwa_pliku_2"Reset"] (nawiaz polaczenie z serwerami aby wyslac im pliki)\n");
	printf("3) "Blue"cd"Reset" ["Green"PATH"Reset"] (zmiana katalogu roboczego na wskazany przez uzytkownika)\n");
	printf("    |- cd ["Green"."Reset"]  (biezacy katalog)\n");
	printf("    |- cd ["Green"~"Reset"]  (katalog domowy)\n");
	printf("    |- cd ["Green".."Reset"] (nadrzedna lokalizacja)\n");
	printf("    |- cd ["Green"-"Reset"]  (poprzedni katalog)\n");
	printf("4) "Blue"clear"Reset" (wyczyszczenie okna terminala)\n");
	printf("5) "Blue"exit"Reset" (zakonczenie dzialania programu)\n");
	printf("6) "Blue"help"Reset" (pomoc i informacje o autorach programu)\n");
	printf("-----------------------------------------------------------------------------\n");

return;
}


void cd(char** polecenie, char*homePATH,char* lastPATH) // Zmiana katalogu
{
	char upPATH[]=".."; 
	char pomocniczyPATH[ROZMIAR];
	char PATH[ROZMIAR];
	getcwd(PATH,sizeof(PATH));

	if (polecenie[2]!=NULL)
        {
          printf(Red"Za duzo argumentow! Bledna skladnia polecenia!\n"Reset);
          printf("\nWpisz '"Green"help"Reset"' aby zobaczyc wszystkie polecenia oferowane przez program\n");
          return;
		} 

	else if ((strcmp(polecenie[0],"cd")==0)&&(polecenie[1]==NULL))
		{
          chdir(homePATH);
          return;
		}

	else if ((strcmp(polecenie[0],"cd")==0)&&(strcmp(polecenie[1],"..")==0))
		{
 		  chdir(upPATH);
 		  return;
		}

	else if ((strcmp(polecenie[0],"cd")==0)&&(strcmp(polecenie[1],"~")==0))
		{
 		  chdir(homePATH);
 	   	  return;
		}

    else if ((strcmp(polecenie[0],"cd")==0)&&(strcmp(polecenie[1],".")==0))
		{
 	   	  chdir(PATH);
  		  return;
		}
		
	else if ((strcmp(polecenie[0],"cd")==0)&&(strcmp(polecenie[1],"-")==0))
		{
		  chdir(lastPATH);
 	 	  return;
		}
		
	else if ((strcmp(polecenie[0],"cd")==0)&&(polecenie[1]!=NULL))
		{
 		  chdir(polecenie[1]); 
 		  getcwd(pomocniczyPATH,sizeof(pomocniczyPATH));  
 	 	  if (strcmp( PATH, pomocniczyPATH ) == 0) 
		      {
			    blad_polecenia(); 
	            return;
			  }
		}
			
return;
} 



void Zmiana_naargument(char *dane_wejsciowe,char **polecenie) { //Zmiana stringu na argumnety

	char * pojedyncze_slowo = strtok (dane_wejsciowe," \n\t"); 
	int indeks=0; 
	
	while(1) 
	    {
		  if (pojedyncze_slowo==NULL)
		      {
			    break;
			  }
		  else
		      {
			    polecenie[indeks]=pojedyncze_slowo; 
                indeks=indeks+1; 
                pojedyncze_slowo=strtok(NULL," \n\t");
			  }
		} 
                
    polecenie[indeks]=NULL; 
    
return;
}


int transfer(char *nazwa_pliku,char *nazwa_pliku_2,int x) 
{
	struct stat fileinfo;
	struct sockaddr_in adr;
	unsigned int port;
	unsigned int port_2;
	char abcd[512];
	char abcd_2[512];
	int fo; //fork id
	int status; // status procesu
	int sdsocket;
	FILE *plik;
		   
		   
	if (x==2) // jesli wykonywujemy polecenie "transfer -two" -> to pytamy o dwa serwery
	    {
		  printf("Podaj adres IP odbiorcy nr 1: ");
		  scanf("%s", abcd);
	  	  printf("Podaj numer portu odbiorcy nr 1: ");
		  scanf("%u", &port);
		  printf("-----------------------------------------------\n");
		  printf("Podaj adres IP odbiorcy nr 2: ");
		  scanf("%s", abcd_2);
		  printf("Podaj numer portu odbiorcy nr 2: ");
		  scanf("%u", &port_2);
		  printf("\n\n");
		  fo = fork(); // fo od fork - ktory zwraca numer procesu potomnego
		}
		   
	if (fo > 0) // jesli wykonywujemy polecenie tylko dla pojedynczego serwera wtedy fo < 0 wiec wykona sie instrukcja else
	    {
		  plik = fopen(nazwa_pliku_2, "r");
		}
	else
		{
	      plik = fopen(nazwa_pliku, "r");
		}
		 
		   
	if (plik == NULL) 
	    {
          printf(BRed"\nPlik: %s - Nie istnieje!\n"Reset"Podaj wlasciwa nazwe pliku\n\n",nazwa_pliku);
          if (fo>0) //obsluga bledow - eliminacja procesu potomnego
              {
			    kill(fo,SIGKILL);
			  }
          return 1;
        }
	
	if (fo > 0)
	    { 
		  if (stat(nazwa_pliku_2, &fileinfo) < 0)
		      {
			    printf(BRed"Nie moge pobrac informacji o pliku! (dlugosc plku)\n"Reset);
				kill(fo,SIGKILL);
				return 1;
			  }
		}
	else
		{ 
		  if (stat(nazwa_pliku, &fileinfo) < 0)
		      {
			    printf(BRed"Nie moge pobrac informacji o pliku! (dlugosc plku)\n"Reset);
				return 1;
			  }
		}
    
    if (fileinfo.st_size == 0)
        {
          printf("rozmiar pliku: 0\n");
          return 1;
        }
    
    
   if (x==1) // jesli wykonywujemy polecenie tylko dla jednego serera
       {
	     printf("Podaj adres IP odbiorcy: ");
         scanf("%s", abcd);
         printf("Podaj numer portu odbiorcy: ");
         scanf("%u", &port);
	   }
 
	if (fo > 0) // jesli nie stworzylismy procesu potomnego to wykona siê kod zawarty w else
 	    {
		  printf("dlugosc pliku NR2: %ld\n", fileinfo.st_size);
 	      sdsocket = socket(PF_INET, SOCK_STREAM, 0);
 		  adr.sin_family = AF_INET;
 		  adr.sin_port = htons(port_2);
		  adr.sin_addr.s_addr = inet_addr(abcd_2);
        }
	else
        { 
		  printf("dlugosc pliku: %ld\n", fileinfo.st_size);
          sdsocket = socket(PF_INET, SOCK_STREAM, 0);
          adr.sin_family = AF_INET;
          adr.sin_port = htons(port);
          adr.sin_addr.s_addr = inet_addr(abcd);
		}
 
	if (connect(sdsocket, (struct sockaddr*) &adr, sizeof(adr)) < 0)
	    {
 	      printf( BRed "\nNawiazanie polaczenia nie powiodlo sie.\n\n" Reset );
          if (fo>0)
              {
			    kill(fo,SIGKILL);
			  }
 		  return 1;
		}


	if (fo > 0)
	    {
	      //printf("------------------------------------------------------------------------\n");
          printf( Green "Polaczenie (NR 2) nawiazane.\n"Reset"Wysylam wiadomosc\n");
		}
	else
	    {
		  //printf("------------------------------------------------------------------------\n");
          printf( Green "Polaczenie nawiazane.\n"Reset"Wysylam wiadomosc\n");
		}


	if (fo > 0)
        {
		  plik = fopen(nazwa_pliku_2, "r");
          wyslij_plik(plik,sdsocket,fileinfo,x);
          fclose(plik);
          close(sdsocket);
          printf("\nPolaczenie (NR 2) zakonczone!\n"); 
		}
	else 
        {
	      plik = fopen(nazwa_pliku, "r");
          wyslij_plik(plik,sdsocket,fileinfo,x);
          fclose (plik);
          close(sdsocket);
          printf("\nPolaczenie  zakonczone!\n"); 
        }

	if (fo > 0)
        {
		  waitpid(fo, &status, WUNTRACED);
		  kill(fo,SIGKILL);
		}


    //printf("------------------------------------------------------------------------\n");

return 0;
}


int main()
{
	printf(Clear);
	char PATH[ROZMIAR];
	char homePATH[ROZMIAR];
	char lastPATH[ROZMIAR];
	getcwd(PATH,sizeof(PATH));
	long int a=(strrchr(PATH,'/')-PATH+1); 
	strncpy(homePATH,PATH,a);
	char *dane_wejsciowe;
	char input[ROZMIAR];
	char *polecenie[ROZMIAR];
	
	printf(Blue"Program kliencki - Projekt - Sieci komputerowe\n"Reset);
	printf("napisz 'help' aby zobaczyc oferowane funkcjonalnosci\n\n");

	while(1)
	    { 
	      getcwd(PATH,sizeof(PATH));
		  printf("\n[%s]$ ",PATH);

		  dane_wejsciowe = fgets(input, ROZMIAR, stdin);
          Zmiana_naargument(dane_wejsciowe,polecenie);

		  if (polecenie[0]==NULL)
		      {
                continue;
		      }
		  else if (strcmp(polecenie[0],"cd")==0)
		      {
                cd(polecenie,homePATH,lastPATH); 
                strncpy(lastPATH,PATH,sizeof(lastPATH));
                continue;
			  }
          else if (strcmp(polecenie[0],"help")==0) 
		      {
                help(); 
                continue;
              }
          else if (strcmp(polecenie[0],"exit")==0)
		      {
                return 0;
			  }
          else if ((strcmp(polecenie[0],"clear")==0)&&(polecenie[1]==NULL)) 
              {
                clear();
                printf(Blue"Program kliencki - Projekt - Sieci komputerowe\n"Reset);
	            printf("napisz 'help' aby zobaczyc oferowane funkcjonalnosci\n\n");
                continue;
              }
          else if ((strcmp(polecenie[0],"transfer")==0)&&(strcmp(polecenie[1],"-two")==0)&&(polecenie[2]!=NULL)&&(polecenie[3]!=NULL))
              {
                char *nazwa_pliku1 = polecenie[2];
                char *nazwa_pliku2 = polecenie[3];
                int x = 2;
                transfer(nazwa_pliku1,nazwa_pliku2,x); 
                continue;
              }
          else if ((strcmp(polecenie[0],"transfer")==0)&&(polecenie[1]!=NULL))
              {
                char *nazwa_pliku1 = polecenie[1];
                int x = 1;
                transfer(nazwa_pliku1,nazwa_pliku1,x); 
                continue;
              }
		  else
                blad_polecenia();

		}
		
return 0;
}



