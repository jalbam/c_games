/* Compilat en Turbo C++ 4.5 per a Windows. */

#include <stdio.h>
#include <conio.h>
#include <dos.h> /* Necessaria per a cursor_off(). */
#include <time.h>
#include <stdlib.h>

/* Segons la direccio, tenim uns graus o uns altres: */
#define DALT_DTA 0
#define DALT_ERA 1
#define BAIX_DTA 2
#define BAIX_ERA 3

#define X_TOPE 80
#define Y_TOPE 23

#define N_PILOTES (X_TOPE * Y_TOPE) / 3
#define N_PILOTES_MIN 1


void inicialitza_pilota(int *x, int *y, int *graus);
void mou_pilota(int *x, int *y, int *graus);
void mostra_pilota(int x, int y);
void esborra_pilota(int x, int y);
void retard();
/* void cursor_off(); */


void main()
{
	 int x[N_PILOTES], y[N_PILOTES], graus[N_PILOTES], i, n_pilotes = N_PILOTES_MIN, sortir = 0, tecla;

	 srand((int)time(NULL)); /* Es fa per utilitzar despres rand(). */

	 for (i = 0; i < n_pilotes; i++) { inicialitza_pilota(&x[i], &y[i], &graus[i]); }

	 /* Mentre no es premi cap tecla: */
	 while (!sortir)
	 {
			for (i = 0; i < n_pilotes; i++)
			{
				esborra_pilota(x[i], y[i]);
				mou_pilota(&x[i], &y[i], &graus[i]);
				mostra_pilota(x[i], y[i]);
			}

			gotoxy(0, 25); printf("[S] = Sortir, [+] = Inc. pilota, [-] = Dec. pilota, Pilotes: %d (max. %d)", n_pilotes, N_PILOTES);

			/* Retarda el moviment de la bola: */
			retard();

			if(kbhit())
			{
				tecla=getch();
				switch(tecla)
				{
					 case '+':
								if (n_pilotes < N_PILOTES)
								{
									n_pilotes++;
									inicialitza_pilota(&x[n_pilotes-1], &y[n_pilotes-1], &graus[n_pilotes-1]);
								}
								break;
					 case '-':
								if (n_pilotes > N_PILOTES_MIN)
								{
									n_pilotes--;
									esborra_pilota(x[n_pilotes], y[n_pilotes]);
								}
								break;
					 case 's': case 'S': sortir = 1; break;
				}
			}

	 }

	 /* Finalitza el programa: */
	 return;
}


/* Funcio que inicialitza la pilota: */
void inicialitza_pilota(int *x, int *y, int *graus)
{
	 /* Posicio inicial de la pilota (aleatoria): */
	 *x = rand() % X_TOPE + 1;
	 *y = rand() % Y_TOPE + 1;
	 *graus = rand() % 4; /* Graus (aleatoris). */

	 return;
}


/* Funcio que mou la pilota: */
void mou_pilota(int *x, int *y, int *graus)
{


			 switch (*graus)
			 {
					  case DALT_DTA:
							 ++*x; --*y;
							 if (*x >= X_TOPE && *y <= 1) { *graus = BAIX_ERA; }
							 else if (*x >= X_TOPE) { *graus = DALT_ERA; }
							 else if (*y <= 1) { *graus = BAIX_DTA; }
					  break;
					  case DALT_ERA:
							 --*x; --*y;
							 if (*x <= 1 && *y <= 1) { *graus = BAIX_DTA; }
							 else if (*x <= 1) { *graus = DALT_DTA; }
							 else if (*y <= 1) { *graus = BAIX_ERA; }
					  break;
					  case BAIX_DTA:
							 ++*x; ++*y;
							 if (*x >= X_TOPE && *y >= Y_TOPE) { *graus = DALT_ERA; }
							 else if (*x >= X_TOPE) { *graus = BAIX_ERA; }
							 else if (*y >= Y_TOPE) { *graus = DALT_DTA; }
					  break;
					  case BAIX_ERA:
							 --*x; ++*y;
							 if (*x <= 1 && *y >= Y_TOPE) { *graus = DALT_DTA; }
							 else if (*x <= 1) { *graus = BAIX_DTA; }
							 else if (*y >= Y_TOPE) { *graus = DALT_ERA; }
					  break;
			 }
}


/* Funcio que mostra la pilota: */
void mostra_pilota(int x, int y)
{
			 char pilota = 'O'; /* El caracter que tindra la pilota. */

			 /* Posiciona el cursor on es dibuixara la pilota: */
			 gotoxy(x, y);
			 /* Alterna l'aspecte de la pilota: */
			 pilota = (pilota == 'O') ? 'o' : 'O';
			 /* Mostra la pilota: */
			 printf("%c", pilota);
}


void esborra_pilota(int x, int y)
{
			 /* Esborra la pantalla: */
			 gotoxy(x, y);
			 printf(" ");
}


/* Funcio que oculta el cursor (requereix dos.h): */
/*
void cursor_off()
{
	  union REGS inregs, outregs;
	  inregs.h.ah=1;
	  inregs.h.ch=0x20;
	  inregs.h.cl=0;
	  int86(0x10,&inregs,&outregs);
}
*/


/* Funcio que fa retardar el sistema: */
void retard()
{
	  long x;
	  for (x=0; x<=9999999L; x++) {  }
}