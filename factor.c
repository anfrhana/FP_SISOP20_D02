#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

void faktorprima(int x)
{

for (int i = 2; x > 1; i++){
     while(x % i == 0) {
      printf(1, "%d ", i);
      x = x/i; 
   }
}
    printf(1,"\n");
    return;
}

int main (int arg1,char *arg2[])
{
  int i, n;
  for(i = 1; i < arg1; i++){
    n = atoi(arg2[i]);
      printf(1, "%d: ", n);
      faktorprima(n);
  }
  exit();
}
