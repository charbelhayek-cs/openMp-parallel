#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int *array;
int length;
int count;

int count3s()
{
   // Solving Count3s problem using OpenMP
   int i;
   count = 0;
   int count_p = 0;
   omp_set_num_threads(8);
#pragma omp parallel firstprivate(count_p)
   {
#pragma omp for
      for (i = 0; i < length; i++)
      {
         if (array[i] == 3)
         {
            count_p++;
         }
      }
#pragma omp critical
      {
         count += count_p;
      }
   }
   return count;
}

int main(int argc, char *argv[])
{
   length = 100000000;
   array = calloc(length, sizeof(int));

   srand(time(NULL));
   // Randomizing the array
   for (int i = 0; i < length; i++)
   {
      array[i] = rand() % 10;
   }

   // Measuring the runtime of the count3s() function
   clock_t begin = clock();
   count3s();
   clock_t end = clock();
   double time_spent = ((double)(end - begin) / CLOCKS_PER_SEC) * 1000.0;
   printf("OpenMP: The number of 3's is %d and it took %fms\n", count, time_spent);

   // Measuring the runtime of the serial execution of Count3s problem
   begin = clock();
   count = 0;
   for (int i = 0; i < length; i++)
      if (array[i] == 3)
         count++;
   end = clock();
   time_spent = ((double)(end - begin) / CLOCKS_PER_SEC) * 1000.0;
   printf("Serial: The number of 3's is %d and it took %fms\n", count, time_spent);

   return 0;
}