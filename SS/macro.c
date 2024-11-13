/*
Adwaith Raj
Roll No.5
Experiment No. 21

                             ONE PASS MACROPROCESSOR
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *itoa(int num,char *str){
    if(str==NULL){
        return NULL;
    }
    else
        sprintf(str,"%d",num);
        return str; 
}

void main(){
    FILE *f1,*f2,*f3,*f4,*f5;
    int pos=1,i;
    char la[20],m[20],op[20],name[20],pos1[20],pos2[20],m1[20],op1[20],arg[20];

    f1=fopen("input.txt","r");
    f2=fopen("namtab.txt","w+");
    f3=fopen("deftab.txt","w+");
    f4=fopen("argtab.txt","w+");
    f5=fopen("op.txt","w+");

    fscanf(f1,"%s%s%s",la,m,op);
    while(strcmp(m,"END")!=0){
        if(strcmp(m,"MACRO")==0){
            fprintf(f2,"%s\n",la);
            fseek(f2,SEEK_SET,0);
            fprintf(f3,"%s\t%s\n",la,op);
            fscanf(f1,"%s%s%s",la,m,op);
            while(strcmp(m,"MEND")!=0){
                if(op[0]=='&'){
                    itoa(pos,pos1);
                    strcpy(pos2,"?");
                    strcat(pos2,pos1);
                    strcpy(op,pos2);
                    pos=pos+1;
                }
                fprintf(f3,"%s\t%s\n",m,op);
                fscanf(f1,"%s%s%s",la,m,op);
            }
            fprintf(f3,"%s\n",m);
        }
        else{
            fscanf(f2,"%s",name);
            if(strcmp(m,name)==0){
                for(i=0;i<strlen(op);i++){
                    
                    if(op[i]!=','){
                        fprintf(f4,"%c",op[i]);
                    }
                    else{
                        fprintf(f4,"\n");}
                }
                fseek(f3,SEEK_SET,0);
                fseek(f4,SEEK_SET,0);
                fscanf(f3,"%s%s",m1,op1);
                fprintf(f5,".\t%s\t%s\n",m,op);
                fscanf(f3,"%s%s",m1,op1);
                while(strcmp(m1,"MEND")!=0){
                    if(op1[0]=='?'){
                        fscanf(f4,"%s",arg);
                        fprintf(f5,"-\t%s\t%s\n",m1,arg);
                    }
                    else
                        fprintf(f5,"-\t%s\t%s\n",m1,op1);
                    fscanf(f3,"%s%s",m1,op1);
                }
            }
            else
                fprintf(f5,"%s\t%s\t%s\n",la,m,op);
        }
        fscanf(f1,"%s%s%s",la,m,op);
    }
    fprintf(f5,"%s\t%s\t%s\n",la,m,op);
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    fclose(f5);
}



