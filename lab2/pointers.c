


#include <stdio.h>

char* text1 = "This is a string.";
char* text2 = "Yet another thing.";
int count;
int list1[20];
int list2[20];

//Kopierar varje char i txt till list och ökar cnt för varje char kopierad
void copycodes(const char txt[], int list[], int*cnt)
{
  char t = *txt;
  while (t){            //While ( *txt not null ) tills slutet av txt[]
    *list = t;
    txt += 1;
    list += 1;
    *cnt += 1;
    t = *txt;
  }
}

void work(){
  copycodes(text1, list1, &count);
  copycodes(text2, list2, &count);
}


void printlist(const int* lst){
  printf("ASCII codes and corresponding characters.\n");
  while(*lst != 0){
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;
  }
  printf("\n");
}

void endian_proof(const char* c){
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n", 
         (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3));
  
}

int main(void){
  work();

  printf("\nlist1: ");
  printlist(list1);
  printf("\nlist2: ");
  printlist(list2);
  printf("\nCount = %d\n", count);

  endian_proof((char*) &count);
}
