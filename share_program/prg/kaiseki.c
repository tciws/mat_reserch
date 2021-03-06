#include<stdio.h>
#include<strings.h>
#include<stdlib.h>
#include<getsym.h>
TOKEN tok;
FILE *infile,*outfile;
void compiler(void);

int main(int argc, char *argv[]){
  char str[256];
  printf("Input output filename >>");
  scanf("%s",str);
  fprintf(stderr,"Simple compiler: compile start.\n");
  if(argc != 2){
    fprintf(stderr,"USAGE: comp source-file-name and outfile\n");
    exit(1);
  }
  if((infile = fopen(argv[1],"r")) == NULL){
    fprintf(stderr, "USAGE：comp source-file-name\n");
    exit(1);
  }
  if((outfile = fopen(str,"w")) == NULL){
    fprintf(stderr,"Object file creation failed.\n");
    exit(1);
  }
  compiler();
  fclose(infile);
  fclose(outfile);
  exit(0);
}
