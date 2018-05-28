#include <stdio.h>
#include <stdlib.h>

int GetRandom(int min, int max);

int main(void)
{
  int i;
  int32_t num,size;
  int32_t value,weight;
  int wmin,wmax,vmin,vmax;
  char FName[32];
  FILE *datafile;

  printf("Please input the file name. ::"); scanf("%s",FName);

  if((datafile = fopen(FName, "wb")) == NULL){
    printf("error:Cannot make the file.\n");
    return 1;
  }

  printf("Object Number: "); scanf("%d",&num);
  printf("Knapsack Size: "); scanf("%d",&size);
  printf("weight min: "); scanf("%d",&wmin);
  printf("weight max: "); scanf("%d",&wmax);
  printf("value min: "); scanf("%d",&vmin);
  printf("value max: "); scanf("%d",&vmax);

  fwrite(&size, sizeof(size), 1, datafile);
  fwrite(&num, sizeof(num), 1, datafile);

  for (i = 0;i < num-1;i++) {
    weight = GetRandom(wmin,wmax);
    value = GetRandom(vmin,vmax);
    fwrite(&weight, sizeof(weight), 1, datafile);
    fwrite(&value, sizeof(value), 1, datafile);
  }
  weight = 10000;
  value = 10000;
  fwrite(&weight, sizeof(weight), 1, datafile);
  fwrite(&value, sizeof(value), 1, datafile);
  printf("correct.\n");
  fclose(datafile);
  return 0;
}

int GetRandom(int min, int max)
{
  return (min +(int)(rand()*(max-min+1.0)/(1.0+RAND_MAX)));
}
