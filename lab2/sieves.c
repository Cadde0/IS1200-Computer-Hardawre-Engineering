#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define COLUMNS 6


int count = 0;

void print_number(int n){
  
  printf("%10d" , n);
  count++;
  if (count == COLUMNS)
  {
    count = 0;
    printf("\n");
  }
}


void mean_sieves(int n){

    char numbers[n];
    for(int i = 2; i <= n; i++) //Skapar array och fyller med talen
        numbers[i] = 1;

    int i = 2;  
    for (int i = 2; i <= sqrt(n); i++)
    {
      if (numbers[i] != 0)
      {
        for (int j=i*i; j < n; j= j + i) //
        {
          numbers[j] = 0;  //0 = icke primtal
        }
      }
    }
  
    
    //double mean;
    int dist = 0;
    int times = 0;

    for (i = 2; i < n; i++)    //Om det inte är 0 är det ett primtal
    {
      dist++;
        if (numbers[i] != 0)
        { 
          if (dist == 4)
          {
            times++;
          }
          dist = 0;
          //mean += i;
          //print_number(i);
        }
    }

    print_number(times);
    /*
    double m = mean/n;
    printf("%f", m);
    */
}

int main(int argc, char *argv[]){
  if(argc == 2)
    mean_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  printf("\n");  
  return 0;
}