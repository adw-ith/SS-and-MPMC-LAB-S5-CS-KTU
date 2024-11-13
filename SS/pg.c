/*
Adwaith Raj
S5 CS
Roll No.5
Experiment No. 3

                             Page Replacement
*/

#include<stdio.h>
#include<stdlib.h>

int pagefound(int count,int fr[],int p){
  for(int i=0;i<count;i++)
    if(fr[i]==p) return 1;
    return 0;
}

void fifo(int fno,int fr[],int pno,int p[]){
  int i,j,k,farr[fno][pno],front=0,count=0,faults=0;
  for(i=0;i<pno;i++){
    if(pagefound(count,fr,p[i])){}
    else{
      faults++;
      fr[front]=p[i];
      front=(front+1)%fno;
      if(count<fno)count++; 
    }
    for(j=0,k=0;j<fno;j++){
      if(k<count)
       farr[k++][i]=fr[j];
      else
        farr[k++][i]=-1;
    }
  }
  for(i=0;i<fno;i++){
    for(j=0;j<pno;j++){
      if(farr[i][j]!=-1) printf("%d ",farr[i][j]);
      else printf("  ");
    }
    printf("\n");
  }
  printf("page faults:%d\n",faults);
}
int lu(int i,int p[],int num){
  int count=0,j;
  for(j=i;j>=0;j--){
    count++;
    if(p[j]==num)return count;
  }
  return count;
}
void lru(int fno,int fr[],int pno,int p[]){
  int larr[fno][pno],i,j,k,index,faults=0,count=0,max,x;
  for(i=0;i<pno;i++){
  if(pagefound(count,fr,p[i])){}
  else{
    faults++;
    if(count==fno){
      max=-1;
      for(j=0;j<fno;j++){
        x=lu(i,p,fr[j]);
        if(x>max)
          {index=j;max=x;}
      }
      fr[index]=p[i];
    }else fr[count++]=p[i];
  }
  for(j=0,k=0;j<fno;j++){
    if(k<count) larr[k++][i]=fr[j];
    else larr[k++][i]=-1;
    }
  }
  for(i=0;i<fno;i++){
    for(j=0;j<pno;j++){
      if(larr[i][j]!=-1) printf("%d ",larr[i][j]);
      else printf("  ");
    }
    printf("\n");
  }
  printf("page faults:%d\n",faults);
}
void lfu(int fno,int fr[],int pno,int p[]){
  int larr[fno][pno],order[fno],i,j,k,index,faults=0,count=0,min,min_order,x,freq[fno],counter=0;
  for(i=0;i<fno;i++) freq[i]=0,order[i]=0;
  
  for(i=0;i<pno;i++){
    if(pagefound(count,fr,p[i])){
      for(j=0;j<count;j++){
        if(fr[j]==p[i]){
          freq[j]++;order[j]=i;break;
        }
      }
    }
    else{
      faults++;
      if(count==fno){
        min=freq[0],index=0,min_order=order[0];
        for(j=1;j<fno;j++){
          if(freq[j]<min){
            min=freq[j];index=j;min_order=order[j];
          }
          else if(freq[j]==min){
            if(order[j]<min_order){
              index=j;min_order=order[j];
            }
          }
        }
        fr[index]=p[i];
        freq[index]=1;
        order[index]=i;
      }
      else{
        fr[count]=p[i];freq[count]=1;
        order[count]=i;count++;
      }
    }
    for(j=0,k=0;j<fno;j++){
      if(k<count)larr[k++][i]=fr[j];
      else larr[k++][i]=-1;
    }
  }

  for(i=0;i<fno;i++){
    for(j=0;j<pno;j++){
      if(larr[i][j]!=-1)printf("%d ",larr[i][j]);
      else printf("  ");
    }
    printf("\n");
  }
  printf("page faults:%d\n",faults);
}
void main(){
  int fno,frame[100],pno,arr[100],i,j,ch;
  printf("Enter number of frames : ");
  scanf("%d",&fno);
  printf("Enter number of pages : ");
  scanf("%d",&pno);
  printf("Enter page requests : ");
  for(i=0;i<pno;i++){
    scanf("%d",&arr[i]);
  }
  do{
    printf("1.FIFO\n2.LRU\n3.LFU\n4.Exit\nEnter your choice\n");
    scanf("%d",&ch);
    switch(ch){
      case 1:
        fifo(fno,frame,pno,arr);
        break;
      case 2:
        lru(fno,frame,pno,arr);
        break;
      case 3:
        lfu(fno,frame,pno,arr);
        break;
      default:
        exit(0);
    }
  }while(ch!=4);
}

/*

OUTPUT

Enter number of frames : 4
Enter number of pages : 12
Enter page requests : 1 2 3 4 5 1 3 1 6 3 2 3
1.FIFO
2.LRU
3.LFU
4.Exit
Enter your choice
1
1 1 1 1 5 5 5 5 5 5 2 2 
  2 2 2 2 1 1 1 1 1 1 1 
    3 3 3 3 3 3 6 6 6 6 
      4 4 4 4 4 4 3 3 3 
page faults:9
1.FIFO
2.LRU
3.LFU
4.Exit
Enter your choice
2
1 1 1 1 5 5 5 5 5 5 2 2 
  2 2 2 2 1 1 1 1 1 1 1 
    3 3 3 3 3 3 3 3 3 3 
      4 4 4 4 4 6 6 6 6 
page faults:8
1.FIFO
2.LRU
3.LFU
4.Exit
Enter your choice
3
1 1 1 1 5 5 5 5 5 5 2 2 
  2 2 2 2 1 1 1 1 1 1 1 
    3 3 3 3 3 3 3 3 3 3 
      4 4 4 4 4 6 6 6 6 
page faults:8
1.FIFO
2.LRU
3.LFU
4.Exit
Enter your choice
5
*/
