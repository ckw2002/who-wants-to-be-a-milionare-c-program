

#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
#include<windows.h>

#define MAX_P 255
#define MAX_O 255
#define ime_dat1 "data\\pitanja_500.txt" 
#define ime_dat2 "data\\pitanja_32k.txt" 
#define ime_dat3 "data\\pitanja_1M.txt" 
#define rang_dat "data\\rang_dat.txt" 

struct Pitanja				//struktura u koju ce se ucitavati pitanja
{
	char  pitanje[MAX_P];
	char _1odgovor[MAX_O];
	char _2odgovor[MAX_O];
	char _3odgovor[MAX_O];
	char _4odgovor[MAX_O];
	char tacan;

}*pitanje;

struct Rang					//struktura potrebna za rang listu
{
	char ime[MAX_P];
	char ostalo[MAX_P];
}rez[14];


int rbr_pitanja = 1, i = 1, pomoc_pri = 1, pomoc_pola = 2, pomoc_pub = 3; pocetna inicijalizacija
int l, pomoc;
int opcija, status = 0, tacno = 0;
int osvojeno = 0, zagarantovano = 0;

char ime_igraca[20];
char *vrednosti[] = { "", "100", "200", "300", "500", "1000", "2000", "4000", "8000", "16000", "32000", "64000", "125000", "250000", "500000", "1000000" }; ovo ce zavisiti od rbr_pitanja, koristi se za prikazivanje vrednosti postavljenog pitanja


FILE *pitanja1, *pitanja2, *pitanja3, *rang_lista;

void crtaj(void);							// Funkcija za crtanje zaglavlja

void ucitavanje(void);

void greska(void);                          // Funkcija izvestava samo da se dogodila greska, kako ne bi zbunjivala korisnika

int ucitaj_pitanja(struct Pitanja *pitanje, // Funkcija kao ulazni argument dobija strukturu tipa Pitanja, vraca 0 ukoliko su pitanja uspesno ucitana
	int generisani[]);

int generisi(int generisi[],				// Funkcija za generisanje pseudoslucajnog broja u opsegu od donje do gornje granice
	int gornja,
	int donja);

void opcije(struct Pitanje pitanja[],	    //Funkcija kao ulazne argumente dobija strukturu tipa Pitanje, trenuti redni broj pitanja i izabranu opciju, nema povratnu vrednost
	int rbr_pitanja,
	int opcija);

int pola_pola(struct Pitanja pitanje[],     // Funkcija predstavlja pomoc pola pola, dobija kao argumente strukturu tipa Pitanja, trenutni redni broj pitanja i status promenljive pomoc_pola, vraca ASCII vrednost odovora na pitanje
	int rbr_pitanja,
	int pomoc_pola);

int pomoc_pr(struct Pitanja pitanje[],      // Funkcija predstavlja pomoc prijatelja, dobija kao argumente strukturu tipa Pitanja, trenutni redni broj pitanja i status promenljive pomoc_pri, vraca ASCII vrednost odovora na pitanje
	int rbr_pitanja,
	int pomoc_pri);

int glas_pub(struct Pitanja pitanje[],      // Funkcija predstavlja pomoc glas publike, dobija kao argumente strukturu tipa Pitanja, trenutni redni broj pitanja i status promenljive pomoc_pub, vraca ASCII vrednost odovora na pitanje
	int rbr_pitanja,
	int pomoc_pub);

int prikazi_pomoci(int pomoc_pri,			//Funkcija za prikazivanje preostalih pomoci.Ulazni argumenti su statusi pomocnih promenljivih za svaku pomoc, rbr pitanja i strukturu tipa Pitanja
	int pomoc_pola,
	int pomoc_pub,
	struct Pitanja pitanje[],
	int rbr_pitanja);

void prikaz_rang();							//Funkcija za prikazivanje rang liste; ulazni argumenti su datoteka rang_lista, nema izlaznih argumenata

void azuriranje_rang(int osvojeno);         //Funkcija za upisivanje(u) i brisanje rang liste; ulazni argumenti su datoteka rang_lista, nema izlaznih argumenata		

void obrisi_rang();							//Funkcija za brisanje rang liste

void kraj(int zagarantovano);			    //Funkcija koja se poziva pri netacnom odgovoru, ili ako korisnik odluci da odustane; ulazni argumenti su vrednost zagarantovane sume; nema izlaznih argumenata



int 
{
	potrebno funkciji generisi()
	int generisani[4];

	time_t t;
	srand((unsigned)time(&t));


	for (i = 0; i<4; i++)
		generisani[i] = -1; 


	system("@cls||clear"); fflush(stdin);
	crtaj();

	if ((pitanja1 = fopen(ime_dat1, "r+")) == NULL)	//provera pri otvaranju datoteke
		greska();
	if ((pitanja2 = fopen(ime_dat2, "r+")) == NULL)
		greska();
	if ((pitanja3 = fopen(ime_dat3, "r+")) == NULL)
		greska();


	Sleep(2000);								//Funkcija iz biblioteke windows.h koja sluzi za kontrolu izlaznog toka, tj. pravljenje pauza	

	if ((pitanje = (struct Pitanja*)malloc(15 * sizeof(struct Pitanja))) == NULL)  //dinamicka dodela, provera; pristup struct Pitanje pitanja[i]
		greska();

	if ((ucitaj_pitanja(pitanje, generisani)) == 0)				//ucitavanje pitanja i provera
	{
		ucitavanje();
		printf("\nPitanja uspesno ucitana...\n\n");
		Sleep(1000);
	}
	else
	{
		printf("\nDogodila se greska pri ucitavanju pitanja.\nPokusajte ponovo.\n");
		exit(1);
	}

	do {
		printf("\t1.Igraj\t\t2.Opcije\t3. O programu\t\t4.Izadji\t\n");
		scanf("%d", &opcija); fflush(stdin);
	} while (opcija != 1 && opcija != 2 && opcija != 3 && opcija != 4);

	switch (opcija)
	{

	case 1: {
				rbr_pitanja = 1;
				printf("\nUnesite vase ime:\t");
				scanf("%s", &ime_igraca); fflush(stdin);
				Sleep(1000);
				printf("\nDobrodosli u igru! Pazljivo citajte pitanja.\n");
				Sleep(2000);
				printf("\nKratko uputstvo:\n\n\t-Posle svakog pitanja umesto odgovora \n\tmozete uneti broj 0 za prikaz preostalih pomoci,\n\n\t-4. Za odustajanje,\n\n\t-Ili a, b, c, d za odgovor na pitanje.\n");
				Sleep(1500);
				printf("\n\t--Za potvrdu odgovora ne treba koristiti enter--\n\n\n");
				Sleep(1500);
				printf("<Pritisnite bilo koji taster za nastavak...>\n\n");
				getch(); fflush(stdin);
				system("@cls||clear");

				while (rbr_pitanja <= 15)
				{
					fflush(stdin);
					crtaj();
					Sleep(300);
					printf("\n Pitanje za %d din glasi:\n\n", atoi(vrednosti[rbr_pitanja]));
					Sleep(2500);
					printf("\t\t\t"); printf("%d", rbr_pitanja); puts(pitanje[rbr_pitanja].pitanje);
					Sleep(1000);
					printf("\t\t\t    "); puts(pitanje[rbr_pitanja]._1odgovor);
					Sleep(1000);
					printf("\t\t\t    "); puts(pitanje[rbr_pitanja]._2odgovor);
					Sleep(1000);
					printf("\t\t\t    "); puts(pitanje[rbr_pitanja]._3odgovor);
					Sleep(1000);
					printf("\t\t\t    "); puts(pitanje[rbr_pitanja]._4odgovor);
					i = 1;
					while (i)
					{
						fflush(stdin);
						printf("\nVas odgovor:\t");
						opcija = getch(); putchar(opcija);
						opcije(pitanje, rbr_pitanja, opcija);
						if (tacno == 1)
						{
							system("@cls||clear");
							rbr_pitanja++;
							tacno = 0;
							break;
						}
						else
						{
							if (status == 1)
							{
								printf("Nije moguce uneti to, molimo unesite ponovo! \n");
								status = 0;
							}
							else
								i--;
						}
					}while(i)
				}while(rbr)

				break; }

	case 2: {
				system("@cls||clear");
				printf("\nIzaberite opciju:\n");
				printf("1.Rang lista\n");
				printf("2.Obrisi rang listu\n");

				do {
					printf("\nUnos:\t");
					scanf("%d", &opcija); fflush(stdin);
				} while (opcija != 1 && opcija != 2);

				if (opcija == 1)
				{
					system("@cls||clear");
					prikaz_rang();
					getch(); fflush(stdin);
				}
				else if (opcija == 2)
				{
					obrisi_rang();
					getch();
				}
	}break;

	case 3: {
				system("@cls||clear");
				printf("\n-------------------------------------------------------------------------------\n\n");
				printf("\n\nIgra:  ""Zelite li da postanete Milioner""\nAutor: Milos Bolic RT-36/14\n\n\n\n\tVisoka skola elektrotehnike i racunarstva strukovnih studija\n\n\t\t\t  Beograd, januar 2016.\n\n");
				printf("\n-------------------------------------------------------------------------------\n\n");
				getch(); fflush(stdin);
				;
	} break;

	case 4:  {
				 fcloseall();
				 free(pitanje);
				 exit(1);
				 
			}break;

	}//end switch(opcija)

	
	fcloseall();
	free(pitanje);
	return 0;

} //end 

void crtaj(void)
{
	printf("\n\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
	printf("$$");							printf("\t\t\t\t\t\t\t\t\t     $$\n");
	printf("$$");							printf("\t\t\t\t\t\t\t\t\t     $$\n");
	printf("$----------------------Zelite li da postanete Milioner?-----------------------$\n");
	printf("$$");							printf("\t\t\t\t\t\t\t\t\t     $$\n");
	printf("$$");							printf("\t\t\t\t\t\t\t\t\t     $$\n");
	printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n");
}

void ucitavanje()
{
	printf("\n\t\t\t\t    ");
	for (i = 0; i<10; i++)
	{
		putchar('|');
		Sleep(100);
		putchar('\b');
		putchar('/');
		Sleep(100);
		putchar('\b');
		putchar('--');
		Sleep(100);
		putchar('\b');
		putchar('\\');
		Sleep(100);
		putchar('\b');
		putchar('|');
		Sleep(100);
		putchar('\b');
	}
	putchar('\t'); putchar('\t'); putchar('\t'); putchar('\t'); putchar('\t');
}

void greska(void)
{
	printf("\nDogodila se greska.Pokusajte ponovo.\n\n");
	fcloseall();
	free(rez); 
	free(pitanje);
	exit(1);
}
int generisi(int generisani[],
	int gornja,
	int donja)
{
	int pom, i;
	int nadjen;
	static int j = 0;

	while (1)
	{
		pom = rand() % (gornja - donja) + donja;	generise broj od donje do gornje granice
		nadjen = 0;

		for (i = 0; i<4; i++)
		if (pom == generisani[i])
			nadjen = 1;
		if (!nadjen)
		{
			generisani[j++] = pom;
			break;
		}
	}

	return pom;
}
int ucitaj_pitanja(struct Pitanja *pitanje,
	int generisani[])
{
	int pom, j, p = 1;
	char bafer[999];

	while (rbr_pitanja <= 15)
	{
		if (rbr_pitanja <= 5)
		{
			pom = generisi(generisani, 320, 300);
			p = 1;
			while (p)
			{
				fgets(bafer, 999, pitanja1);
				fgets(pitanje[rbr_pitanja]._1odgovor, MAX_O, pitanja1);
				fgets(pitanje[rbr_pitanja]._2odgovor, MAX_O, pitanja1);
				fgets(pitanje[rbr_pitanja]._3odgovor, MAX_O, pitanja1);
				fgets(pitanje[rbr_pitanja]._4odgovor, MAX_O, pitanja1);
				pitanje[rbr_pitanja].tacan = fgetc(pitanja1);	fgetc(pitanja1);

				if (atoi(bafer) == pom && atoi(bafer) != 0)		Pitanje se prvo ucitava u bafer, pa se uzima redni broj pitanja iz datoteke dok se ne poklopi sa pseudosluc. generisanim brojem
				{
					p = 0;
					break;
				}

				if (feof(pitanja1)) Ako je kraj datoteke, vracamo se na pocetak;
				{
					rewind(pitanja1);
					break;
				}

			}
			j = 0;
			for (i = 3; i<(strlen(bafer) + 4); i++)   brisanje rednog broja iscitanog pitanja (npr. 306.);
			{
				bafer[j] = bafer[i];
				j++;
			}
			strcpy(pitanje[rbr_pitanja].pitanje, bafer);

		}//end if( rbr<=5 )

		j = 0;
		if (rbr_pitanja>5 && rbr_pitanja <= 10)
		{
			pom = generisi(generisani, 330, 320);
			while (1)
			{
				fgets(bafer, 999, pitanja2);
				fgets(pitanje[rbr_pitanja]._1odgovor, MAX_O, pitanja2);
				fgets(pitanje[rbr_pitanja]._2odgovor, MAX_O, pitanja2);
				fgets(pitanje[rbr_pitanja]._3odgovor, MAX_O, pitanja2);
				fgets(pitanje[rbr_pitanja]._4odgovor, MAX_O, pitanja2);
				pitanje[rbr_pitanja].tacan = fgetc(pitanja2);	fgetc(pitanja2);

				if (atoi(bafer) == pom && atoi(bafer) != 0)
				{
					pom = generisi(generisani, 330, 320);
					break;
				}

				if (feof(pitanja2))
				{
					rewind(pitanja2);
					break;
				}
			}
			j = 0;
			for (i = 3; i<(strlen(bafer) + 4); i++)      
				for (i = 3; i<(strlen(bafer) + 4);i++)         // brisanje rednog broja iscitanog pitanja
				{
					bafer[j] = bafer[i];
					j++;
				}
			strcpy(pitanje[rbr_pitanja].pitanje, bafer);

		}//end if(rbr)

		j = 0;
		if (rbr_pitanja>10 && rbr_pitanja <= 15)
		{
			pom = generisi(generisani, 340, 330);
			while (1)
			{
				fgets(bafer, 999, pitanja3);
				fgets(pitanje[rbr_pitanja]._1odgovor, MAX_O, pitanja3);
				fgets(pitanje[rbr_pitanja]._2odgovor, MAX_O, pitanja3);
				fgets(pitanje[rbr_pitanja]._3odgovor, MAX_O, pitanja3);
				fgets(pitanje[rbr_pitanja]._4odgovor, MAX_O, pitanja3);
				pitanje[rbr_pitanja].tacan = fgetc(pitanja3);	fgetc(pitanja3);

				if (atoi(bafer) == pom && atoi(bafer) != 0)
				{
					pom = generisi(generisani, 340, 330);
					break;
				}
				if (feof(pitanja3))
				{
					rewind(pitanja3);
					break;
				}
			}
			j = 0;
			for (i = 3; i<(strlen(bafer) + 4); i++)
			{
				bafer[j] = bafer[i];
				j++;
			}
			strcpy(pitanje[rbr_pitanja].pitanje, bafer);
		}

		rbr_pitanja++;
	}//end while(rbr)

	return 0;
}


void opcije(struct Pitanja pitanje[],
	int rbr_pitanja,
	int opcija)
{

	if (opcija == '1')
		opcija = pomoc_pr(pitanje, rbr_pitanja, pomoc_pri);
	else if (opcija == '2')
		opcija = pola_pola(pitanje, rbr_pitanja, pomoc_pola);
	else if (opcija == '3')
		opcija = glas_pub(pitanje, rbr_pitanja, pomoc_pub);
	else if (opcija == '4')
		kraj(zagarantovano);
	else if (opcija == '0')
		opcija = prikazi_pomoci(pomoc_pri, pomoc_pola, pomoc_pub, pitanje, rbr_pitanja);

	else if (opcija == 'a')
	{
		if (pitanje[rbr_pitanja].tacan == opcija)
		{
			tacno = 1;
			osvojeno = atoi(vrednosti[rbr_pitanja]);
			Sleep(500);
			printf("\nTo je tacan odgovor!\n");
			Sleep(1000);
			printf("Osvojili ste %d din.\n", osvojeno);
			Sleep(1000);

			if (rbr_pitanja == 5 || rbr_pitanja == 10)
			{
				Sleep(500);
				printf("\nZagarantovana suma od %d din.\n", osvojeno);
				zagarantovano = osvojeno;
				Sleep(1000);
			}

			else if (rbr_pitanja == 15)
			{
				system("@cls||clear");
				printf("\n\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
				Sleep(1000);
				printf("\n\nCESTITAMO, "); Sleep(500); printf("POSTALI STE MILIONER!!!\n\n");
				Sleep(1000);
				printf("\n\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
				kraj(osvojeno);
				getch();
			}
		}
		else
		{
			printf("\nNazalost, to nije tacan odgovor.\n");
			kraj(zagarantovano);
		}


	}//end else if (opcija =='a' )

	else if (opcija == 'b')
	{
		if (pitanje[rbr_pitanja].tacan == opcija)
		{
			tacno = 1;
			osvojeno = atoi(vrednosti[rbr_pitanja]);
			Sleep(500);
			printf("\nTo je tacan odgovor!\n");
			Sleep(1000);
			printf("Osvojili ste %d din.\n", osvojeno);
			Sleep(1000);

			if (rbr_pitanja == 5 || rbr_pitanja == 10)
			{
				Sleep(500);
				printf("\nZagarantovana suma od %d din.\n", osvojeno);
				zagarantovano = osvojeno;
				Sleep(1000);
			}
			else if (rbr_pitanja == 15)
			{
				system("@cls||clear");
				printf("\n\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
				Sleep(1000);
				printf("\n\nCESTITAMO, "); Sleep(500); printf("POSTALI STE MILIONER!!!\n\n");
				Sleep(1000);
				printf("\n\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
				kraj(osvojeno);
				getch();
			}
		}

		else
		{
			printf("\nNazalost, to nije tacan odgovor.\n");
			kraj(zagarantovano);
		}
	} //end else if (opcija == 'b' )

	else if (opcija == 'c')
	{
		if (pitanje[rbr_pitanja].tacan == opcija)
		{
			tacno = 1;
			osvojeno = atoi(vrednosti[rbr_pitanja]);
			Sleep(500);
			printf("\nTo je tacan odgovor!\n");
			Sleep(1000);
			printf("Osvojili ste %d din.\n", osvojeno);
			Sleep(1000);

			if (rbr_pitanja == 5 || rbr_pitanja == 10)
			{
				Sleep(500);
				printf("\nZagarantovana suma od %d din.\n", osvojeno);
				zagarantovano = osvojeno;
				Sleep(1000);
			}
			else if (rbr_pitanja == 15)
			{
				system("@cls||clear");
				printf("\n\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
				Sleep(1000);
				printf("\n\nCESTITAMO, "); Sleep(500); printf("POSTALI STE MILIONER!!!\n\n");
				Sleep(1000);
				printf("\n\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
				kraj(osvojeno);
				getch();
			}
		}
		else
		{
			printf("\nNazalost, to nije tacan odgovor.\n");
			kraj(zagarantovano);
		}
	} //end else if (opcija == 'c' )

	else if (opcija == 'd')
	{
		if (pitanje[rbr_pitanja].tacan == opcija)
		{
			tacno = 1;
			osvojeno = atoi(vrednosti[rbr_pitanja]);
			Sleep(500);
			printf("\nTo je tacan odgovor!\n");
			Sleep(1000);
			printf("Osvojili ste %d din.\n", osvojeno);
			Sleep(1000);

			if (rbr_pitanja == 5 || rbr_pitanja == 10)
			{
				Sleep(500);
				printf("\nZagarantovana suma od %d din.\n", osvojeno);
				zagarantovano = osvojeno;
				Sleep(1000);
			}
			else if (rbr_pitanja == 15)
			{
				system("@cls||clear");
				printf("\n\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
				Sleep(1000);
				printf("\n\nCESTITAMO, "); Sleep(500); printf("POSTALI STE MILIONER!!!\n\n");
				Sleep(1000);
				printf("\n\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
				kraj(osvojeno);
				getch();
			}
		}
		else
		{
			printf("\nNazalost, to nije tacan odgovor.\n");
			kraj(zagarantovano);
		}

	} //end else if (opcija =='d' )

	else {
		printf("\nNiste uneli ni jednu od predvidjenih opcija. Unesite ponovo.\n");
		status = 1;
		tacno = 0;
	}

}// kraj funkcije

int pomoc_pr(struct Pitanja pitanje[],
	int rbr_pitanja)
{
	char pomocna[50];
	if (pomoc_pri == 0)
	{
		printf("\nOvu pomoc ste vec iskoristili u ovoj igri. \nIzaberite drugu vrstu pomoci, ili odgovor. \n");
		opcija = prikazi_pomoci(pomoc_pri, pomoc_pola, pomoc_pub, pitanje, rbr_pitanja);
	}

	else
	{
		printf("\n\nUnesite broj mobilnog telefona prijatelja:\n");
		scanf("%s", pomocna); fflush(stdin);
		printf("\n\nPoziva se"); Sleep(1000);
		printf("."); Sleep(1000);
		printf("."); Sleep(1000);
		printf(".\n\n"); Sleep(1000);
		printf("Prijatelj: Halo?\n\n");
		getch();
		printf("%s:Prijatelju, %s je na vezi, u kvizu sam ""Zelite li da postanete Milioner i treba mi tvoja pomoc."" \n\n", ime_igraca, ime_igraca);
		getch();
		printf("Prijatelj: Naravno. Zadovoljstvo mi je. Slusam pitanje:\n\n");
		getch(); fflush(stdin);

		puts(pitanje[rbr_pitanja].pitanje);
		Sleep(1000);
		putchar('\t'); puts(pitanje[rbr_pitanja]._1odgovor);
		Sleep(1000);
		putchar('\t'); puts(pitanje[rbr_pitanja]._2odgovor);
		Sleep(1000);
		putchar('\t'); puts(pitanje[rbr_pitanja]._3odgovor);
		Sleep(1000);
		putchar('\t'); puts(pitanje[rbr_pitanja]._4odgovor);
		Sleep(1000);

		printf("."); Sleep(1000);
		printf("."); Sleep(1000);
		printf("."); Sleep(1000);
		printf(".\n\n"); Sleep(1000);
		printf("Prijatelj: Mislim da je odgovor pod %c.\n", pitanje[rbr_pitanja].tacan);
		getch();
		printf("%s: Mislim i ja da je to odgovor. Koliko si siguan?\n", ime_igraca);
		getch();
		printf("Prijatelj: 99%%.\n");
		getch();
		printf("%s: Odlicno. Mnogo ti hvala!! \n\n", ime_igraca);

		printf("Unesite odgovor:\t");
		opcija = getch(); putchar(opcija);

		pomoc_pri = 0;
	}

	return opcija;

} //kraj funkcije

int glas_pub(struct Pitanja pitanje[],
	int rbr_pitanja)
{
	if (pomoc_pub == 0)
	{
		printf("\nOvu pomoc ste vec iskoristili u ovoj igri. \nIzaberite drugu vrstu pomoci, ili odgovor. \n");
		opcija = prikazi_pomoci(pomoc_pri, pomoc_pola, pomoc_pub, pitanje, rbr_pitanja);
	}

	else
	{
		printf("\n-------------------------------------------------------------------------------\n\n");
		Sleep(1000);
		printf("\nPublika je glasala:\n\n");

		Sleep(3000);

		if (pitanje[rbr_pitanja].tacan == 'a')
		{
			printf("A |********************\n");
			printf("B |******\n");
			printf("C |***\n");
			printf("D |*********\n");
		}
		if (pitanje[rbr_pitanja].tacan == 'b')
		{
			printf("A |*****\n");
			printf("B |********************\n");
			printf("C |***\n");
			printf("D |*********\n");
		}
		if (pitanje[rbr_pitanja].tacan == 'c')
		{
			printf("A |*\n");
			printf("B |*****\n");
			printf("C |********************\n");
			printf("D |*********\n");
		}
		if (pitanje[rbr_pitanja].tacan == 'd')
		{
			printf("A |***************\n");
			printf("B |*****\n");
			printf("C |\n");
			printf("D |********************\n");
		}

		printf("Unesite odgovor:\t");
		fflush(stdin);
		opcija = getch(); putchar(opcija);
		printf("\n-------------------------------------------------------------------------------\n\n");

		pomoc_pub = 0;
	}

	return opcija;

} //kraj funkcije

int pola_pola(struct Pitanja pitanje[],
	int rbr_pitanja)
{
	if (pomoc_pola == 0)
	{
		printf("\nOvu pomoc ste vec iskoristili u ovoj igri. \nIzaberite drugu vrstu pomoci, ili odgovor. \n");
		opcija = prikazi_pomoci(pomoc_pri, pomoc_pola, pomoc_pub, pitanje, rbr_pitanja);
	}

	else
	{

		if (pitanje[rbr_pitanja].tacan == pitanje[rbr_pitanja]._1odgovor[0])	trazenje tacnog odgovora pomocu slova tacnog odgovora
		{
			putchar('\n'); putchar('\n');
			putchar('\t'); puts(pitanje[rbr_pitanja]._1odgovor);
			putchar('\t'); puts(pitanje[rbr_pitanja]._4odgovor);
		}
		if (pitanje[rbr_pitanja].tacan == pitanje[rbr_pitanja]._2odgovor[0])
		{
			putchar('\n'); putchar('\n');
			putchar('\t'); puts(pitanje[rbr_pitanja]._2odgovor);
			putchar('\t'); puts(pitanje[rbr_pitanja]._1odgovor);
		}
		if (pitanje[rbr_pitanja].tacan == pitanje[rbr_pitanja]._3odgovor[0])
		{
			putchar('\n'); putchar('\n');
			putchar('\t'); puts(pitanje[rbr_pitanja]._3odgovor);
			putchar('\t'); puts(pitanje[rbr_pitanja]._2odgovor);
		}
		if (pitanje[rbr_pitanja].tacan == pitanje[rbr_pitanja]._4odgovor[0])
		{
			putchar('\n'); putchar('\n');
			putchar('\t'); puts(pitanje[rbr_pitanja]._4odgovor);
			putchar('\t'); puts(pitanje[rbr_pitanja]._3odgovor);
		}

		printf("Unesite odgovor:\t");
		opcija = getch(); putchar(opcija);

		pomoc_pola = 0;
	}

	return opcija;
} //kraj funkcije


int prikazi_pomoci(int pomoc_pri,
	int pomoc_pola,
	int pomoc_pub,
struct Pitanja pitanje[],
	int rbr_pitanja)
{

	printf("\n-------------------------------------------------------------------------------\n");
	printf("Preostale pomoci:\t\n");
	if (pomoc_pri == 1)
		printf("1.Pomoc prijatelja\n");
	if (pomoc_pola == 2)
		printf("2.Pomoc pola pola\n");
	if (pomoc_pub == 3)
		printf("3.Pomoc publike\n");

	if ((pomoc_pri == 0) && (pomoc_pola == 0) && (pomoc_pub == 0))
		printf("\nIskoristili ste sve vrste pomoci.\n");

	else
	{
	pomoc:
		printf("\nUnesite redni broj pomoci:\t");
		opcija = getch();

		switch (opcija)
		{
		case '1': {
					  opcija = pomoc_pr(pitanje, rbr_pitanja, pomoc_pri);
					  opcije(pitanje, rbr_pitanja, opcija); }break;
		case '2': {
					  opcija = pola_pola(pitanje, rbr_pitanja, pomoc_pola);
					  opcije(pitanje, rbr_pitanja, opcija); }break;
		case '3': {
					  opcija = glas_pub(pitanje, rbr_pitanja, pomoc_pub);
					  opcije(pitanje, rbr_pitanja, opcija); }break;

		case '4': kraj(zagarantovano); break;

		default: {printf("\nNiste uneli odgovarajuci broj pomoci. Unesite ponovo."); goto pomoc; } break;
		}
	}end else
	printf("\n-------------------------------------------------------------------------------\n");


	return opcija;


}// kraj funkcije

void sortiraj()
{
	struct Rang pom;
	int i, j;

	for (i = 0; i<13; i++)
	{
		for (j = i + 1; j<14; j++)
		{
			if (atoi(rez[i].ostalo) < atoi(rez[j].ostalo))
			{
				pom = rez[i];
				rez[i] = rez[j];
				rez[j] = pom;
			}
		}
	}
}// kraj funkcije

void prikaz_rang()
{
	char bafer[255];
	int i = 0;

	if ((rang_lista = fopen(rang_dat, "r+")) == NULL)
		greska();

	while (!feof(rang_lista) || i == 14)
	{
		fscanf(rang_lista, "%s", &rez[i].ime);
		fgets(rez[i].ostalo, 255, rang_lista);
		i++;
	}

	sortiraj();
	rewind(rang_lista);

	printf("Rang lista:\n\n");
	printf("Ime igraca\t\t Osvojeno   Datum\n\n");

	for (i = 0; i<14; i++)
	{
		fprintf(stdout, " %s%s", rez[i].ime, rez[i].ostalo);
	}

	fclose(rang_lista);

	getch();
	

}// kraj funkcije


void azuriranje_rang(int osvojeno)
{

	if ((rang_lista = fopen(rang_dat, "a")) == NULL)
		greska();


	fprintf(rang_lista, "*%s.................... ", ime_igraca);
	fprintf(rang_lista, "%d(%s)\n", osvojeno, __DATE__); atoi



	printf("\nRang lista uspesno azurirana!\n");

	rewind(rang_lista);
	sortiraj();

	fclose(rang_lista);

} //kraj funkcije


void obrisi_rang()
{
	FILE *rang_lista;

	if ((rang_lista = fopen(rang_dat, "w")) == NULL)
		greska();

	fprintf(rang_lista, " ");
	printf("\nRang lista obrisana. Pritisnite bilo koji taster za nastavak.\n");
	fclose(rang_lista);
	getch();

} //kraj funkcije

void kraj(int zagarantovano)
{
	if (zagarantovano>0)
	{
		printf("\nCestitamo, osvojili ste sumu od %d dinara.\n", zagarantovano);
		azuriranje_rang(zagarantovano);

	}

	else {
		printf("\nKraj igre.\n");
		Sleep(1000);
		printf("\nNiste dostigli nijednu zagarantovanu sumu. :(\n\n");

		azuriranje_rang(zagarantovano);

	}

	Sleep(3000);
	getch();
	system("@cls||clear");
}
