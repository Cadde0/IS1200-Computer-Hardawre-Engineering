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

void print_sieves(int n){
    char*numbers = malloc(n*sizeof(char));

    for(int i = 2; i <= n; i++) //Skapar array och fyller med naturliga talen
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
        
    for (i = 2; i < n; i++)    //Om det inte är 0 är det ett primtal
    {
        if (numbers[i] != 0)
        {
            print_number(i);
        }
    }
    free(numbers);
}


int main(int argc, char *argv[]){
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  printf("\n");  
  return 0;
}