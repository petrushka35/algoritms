#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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

void my_quicksort(int *array, int first, int last, int N, int i)
{
   	if (i < log(N))
   	{
       	int index1 = first, index2 = last, pivot = (array[index1] + array[index2]) / 2;
       	while(index1 <= index2)  
       	{	
           	while (array[index1] < pivot) index1++;
           	while (array[index2] > pivot) index2--;
           	if (index1 <= index2)
           	{
               	int tmp = array[index1];
               	array[index1] = array[index2];
               	array[index2] = tmp;
               	index1++;
                index2--;
            }
        }
        i++;
        my_quicksort(array, first, index2, index2, i);
        my_quicksort(array, index1, last, last - index1, i);
    }
}

void my_introsort(int * array, int N)
{
	my_quicksort(array, 0, N-1, N, 0);
	my_heapsort(array, N);

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
	my_introsort(array, N);
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