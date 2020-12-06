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


void my_shellsort(int* array, int N) {
    int step, length;
    int* m = malloc(sizeof(int));
    m[0] = 1;
    for (length = 1; (m[length-1] * 3) < N; length++) {
        if (length % 2 == 0) {
            step = 9 * pow(2, length) - 9 * pow(2, (length/2)) + 1;
        }
        else {
            step = 8 * pow(2, length) - 6 * pow(2, (length/2)) + 1;
        }
        m = realloc(m, sizeof(int) * length * 2);
        if (m)
            m[length] = step;
        else
            printf("realloc error");
    }

    int* inc = malloc(sizeof(int) * (length));
    for (int i = 0; i < length-1; i++)
        inc[i] = m[i]; 

    for (int i = length - 1; i >= 0; i--)
    {
        int step = inc[i];
        int tmp;
        for (int i = step; i < N; i++)
        {
            for (int j = i - step; j >= 0 && array[j] > array[j + step]; j -= step)
            {
                tmp = array[j];
                array[j] = array[j + step];
                array[j + step] = tmp;
            }
        }
    }
    free(inc);
    free(m);
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
