#include <stdio.h>

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

void swap(int * a, int * b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void sorting_tree(int * array, int root, int N)
{
	int max_child = 0;
	while (root * 2 + 1 < N) {
		if ((root * 2 + 1 == N - 1) || (array[root * 2 + 1] > array[root * 2 + 2]))
			max_child = root * 2 + 1;
		else
			max_child = root * 2 + 2;
		if (array[root] < array[max_child]) {
			swap(&array[root], &array[max_child]);
			root = max_child;
		}
		else
			break;
	}
}

void my_heapsort(int * array, int N)
{
	for (int i = N / 2 - 1; i >= 0; --i)
		sorting_tree(array, i, N);
	for (int i = N - 1; i > 0; --i) 
	{
		swap(&array[0], &array[i]);
		sorting_tree(array, 0, i);
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
	my_heapsort(array, N);
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