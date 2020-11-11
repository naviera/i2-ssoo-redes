// compile gcc -o i2p3 i2p3.c

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

int manejar_fifo(int * memoria, int pagina);
int manejar_lru(int* memoria, int pagina);
int manejar_min(int* memoria, int pagina);
int manejar_random(int* memoria, int pagina);

int main(int argc, char *argv[])
{
	time_t t;
	int memoria[5];
	char a = 0;
	int d = 7;             // tamaño en Byte de una página
	int hits = 0;
	int misses = 0;
	int estado = 0;
	char m[10*d];                 // un char es de tamaño 1 Byte
	srand((unsigned) time(&t));
	for (int i=0; i<5; i+=1)
	{
		memoria[i] = -1;
	}

	for (int i=0; i<1000; i+=1)
	{
		if (i < 23)
		{
			printf("\n");
			printf("i: %i\n", i);
		}
		// cambiar según caso
		estado = manejar_random(memoria, 0);
		if (estado == 1)
		{
			misses +=1;
		}
		if (estado == 0)
		{
			hits += 1;
		}

		// cambiar según caso
		estado = manejar_random(memoria, i%10);
		if (estado == 1)
		{
			misses +=1;
		}
		if (estado == 0)
		{
			hits += 1;
		}

		// cambiar según caso
		estado = manejar_random(memoria, 0);
		if (estado == 1)
		{
			misses +=1;
		}
		if (estado == 0)
		{
			hits += 1;
		}

		if (i < 23)
		{
			for (int j=0; j<5; j+=1)
			{
				printf("%i, ", memoria[j]);
			}
			printf("\n");
		}
	}
	printf("hits: %i\n", hits);
	printf("misses: %i\n", misses);
}

int manejar_fifo(int* memoria, int pagina)
{
	for (int i=0; i<5; i+=1)
	{
		if (pagina == memoria[i])
		{
			return 0;
		}
	}

	for (int i=0; i<4; i+=1)
	{
		memoria[i] = memoria[i+1];
	}
	memoria[4] = pagina;
	return 1;
}

int manejar_lru(int* memoria, int pagina)
{
	int buffer[5];
	for (int i=0; i<5; i+=1)
	{
		if (pagina == memoria[i])
		{
			for (int j=0; j<5; j+=1)
			{
				if (j < i)
				{
					buffer[j+1] = memoria[j];
				}
				else if (j > i)
				{
					buffer[j] = memoria[j];
				}
				else if (j == i)
				{
					buffer[0] = memoria[j];
				}
			}
			for (int j=0; j<5; j+=1)
			{
				memoria[j] = buffer[j];
			}
			// se encontró
			return 0;
		}
	}
	for (int i=0; i<5; i+=1)
	{
		buffer[i+1] = memoria[i];
	}
	buffer[0] = pagina;
	for (int j=0; j<5; j+=1)
	{
		memoria[j] = buffer[j];
	}
	return 1;
}

int manejar_min(int* memoria, int pagina)
{
	int max = pagina;
	int pos = 0;

	for (int i=0; i<5; i+=1)
	{
		if (pagina == memoria[i])
		{
			return 0;
		}

	}

	for (int i=0; i<5; i+=1)
	{
		if (memoria[i] == -1)
		{
			memoria[i] = pagina;
			return 1;
		}
	}

	if (pagina != 0)
	{
		for (int i=0; i<5; i+=1)
		{
			if (memoria[i] < pagina && memoria[i]!= 0)
			{
				if (max == pagina)
				{
					max = memoria[i];
					pos = i;
				}
				else if (max > pagina)
				{
					max = memoria[i];
					pos = i;
				}
				else if (max < pagina && memoria[i] > max)
				{
					max = memoria[i];
					pos = i;
				}
			}
			else if (memoria[i] > pagina && memoria[i]!= 0)
			{
				if (max == pagina)
				{
					max = memoria[i];
					pos = i;
				}
				else if (max > pagina && memoria[i] > max)
				{
					max = memoria[i];
					pos = i;
				}
			}
		}
		memoria[pos] = pagina;
		return 1;
	}
}

int manejar_random(int* memoria, int pagina)
{
	for (int i=0; i<5; i+=1)
	{
		if (pagina == memoria[i])
		{
			return 0;
		}

	}

	for (int i=0; i<5; i+=1)
	{
		if (memoria[i] == -1)
		{
			memoria[i] = pagina;
			return 1;
		}
	}

	memoria[rand() % 5] = pagina;
	return 1;



}