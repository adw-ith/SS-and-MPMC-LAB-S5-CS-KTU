/*
Adwaith Raj
S5 CS
Roll No.5
Experiment No. 5

                             PASS 2 of PASS 2 ASSEMBLER
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct qwe{
  char a[100];
}arr[100];
struct poi{
  int ind;
  int len;
}leng[100];

void main(){
  FILE *f1,*f2,*f3,*f4,*f5;
  f1 = fopen("output.txt","r");
  f2 = fopen("optab.txt","r");
  f3 = fopen("symtbl.txt","r");
  f4 = fopen("output1.txt","w");
  f5  = fopen("length.txt","r");
  leng[0].len = 0;
  char label[100],opcode[100],operand[100],value[100],locctr[100],symadd[100],mnemonic[100],symbol[100],l[100];
  int start,len,c=0,co=0,co_len=1,i=0,j;
  fscanf(f1,"%s\t%s\t%s\t%s",locctr,label,opcode,operand);
  if(strcmp(opcode, "START")==0){
    start = strtol(operand,NULL,16);
    fscanf(f5,"%s",l);
  }
  len = strtol(l,NULL,10);
  fprintf(f4,"H^%s^%06X^%02d\n",label,start,len);
  fscanf(f1,"%s\t%s\t%s\t%s",locctr,label,opcode,operand);
  while(strcmp(opcode,"END")!=0){
    while(!(feof(f2))){
      fscanf(f2,"%s\t%s",mnemonic,value);
      if(strcmp(mnemonic,opcode)==0){
        while(!(feof(f3))){
          fscanf(f3,"%s\t%s",symbol,symadd);
          if(strcmp(symbol,operand)==0){
            strcpy(arr[c].a,value);
            strcat(arr[c++].a,symadd);
            co +=strlen(value);
            co +=strlen(symadd);
            if(co>=60){
              leng[co_len].ind = c-1;
              leng[co_len++].len = co -strlen(value)-strlen(symadd);
              co  = strlen(value) + strlen(symadd);
            }
            break;
          }
        }
        fseek(f3,SEEK_SET,0);
        break;
      }
    }
    fseek(f2,SEEK_SET,0);
    if(strcmp(opcode,"WORD")==0||strcmp(opcode,"BYTE")==0){
      if(strcmp(opcode,"WORD")==0){
        char zero[6-strlen(operand)];
        for(i=0;i<(6-strlen(operand)); i++)
          zero[i] ='0';
        strcpy(arr[c].a,zero);
        strcat(arr[c++].a,operand);
        co+=6;
        if(co>=60){
          leng[co_len].ind=c-1;
          leng[co_len++].len=co-6;
          co=6;
        }
      }
      if(strcmp(opcode,"BYTE")==0){
        int byte[100],as=0,index=0;
        char str[100];
        for(i=2;i<strlen(operand)-1;i++)
          byte[as++] = (int)operand[i];
        for(i=0;i<as;i++)
          index += sprintf(&str[index],"%x",byte[i]);
        strcpy(arr[c++].a,str);
        co += strlen(str);
        if(co>=60){
          leng[co_len].ind = c-1;
          leng[co_len++].len = co -strlen(str);
          co = strlen(str);
        }
      }
    }
    fscanf(f1,"%s\t%s\t%s\t%s",locctr,label,opcode,operand);
  }
  if(co<60){
    leng[co_len].ind =c;
    leng[co_len++].len =co;
  }
  for(i=0;i<co_len-1;i++){
    start = start + leng[i].len/2;
    fprintf(f4,"T^%06X^%02X^",start,leng[i+1].len/2);
    for(j=leng[i].ind; j<leng[i+1].ind;j++)
      fprintf(f4,"%s^",arr[j].a);
    fprintf(f4,"\n");
  }
  fprintf(f4,"E^%06X",start);
}
