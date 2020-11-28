#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct timeval tv1,tv2,dtv;

struct timezone tz;

void time_start() 
{ mingw_gettimeofday(&tv1, &tz); }

long time_stop()
{ mingw_gettimeofday(&tv2, &tz);

  dtv.tv_sec= tv2.tv_sec -tv1.tv_sec;

  dtv.tv_usec=tv2.tv_usec-tv1.tv_usec;

  if(dtv.tv_usec<0) { dtv.tv_sec--; dtv.tv_usec+=1000000; }

  return dtv.tv_sec*1000+dtv.tv_usec/1000;
}

void my_shellsort(int * array, int N)
{
	int inc[100]; 

	int p1 = 1, p2 = 1, p3 = 1;
	int i = -1;
	do{
  		if(++i % 2) 
    		inc[i] = 8*p1 - 6*p2 + 1;
  		else
  		{
    		inc[i] = 9*p1 - 9*p3 + 1;
    		p2 *= 2;
    		p3 *= 2;
  		}
  		p1 *= 2;
  	}while(3*inc[i] <= N);

	if(i > 0)
	{
  		--i;
  		while(i>=0)
  		{
  			int step = inc[--i];
			int tmp;
			for(int i = step; i < N; i++)
			{
				for (int j = i - step; j >= 0 && array[j] > array[j + step]; j -= step)
				{
					tmp = array[j];
					array[j] = array[j + step];
					array[j + step] = tmp;
				}
			}
  		}
	}
}

int main(int argc, char * argv[])
{
	int N;
	FILE *fp;
	struct timeval tv1,tv2,dtv;
	struct timezone tz;

	if ((fp = fopen(argv[1], "r")) == NULL)
 	{
		return 0;
	}
	fscanf(fp, "%d", &N);
	int * array = malloc(N * sizeof(int));
	if(array == NULL)
	{
		return 0;
	}
	for(int i = 0; i < N; i++)
	{
		fscanf(fp, "%d", &array[i]);
	}

	time_start();
	my_shellsort(array, N);
	printf("%ld\r", time_stop());
	printf("%d\r", N);

	for(int i = 0; i < N-1; i++)
	{
		printf("%d ", array[i]);
	}
	printf("%d", array[N-1]);

	fclose(fp);
	free(array);
	return 0;
}
