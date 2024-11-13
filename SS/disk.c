/*
Adwaith Raj
S5 CS
Roll No.5
Experiment No. 2

                              DISK SCHEDULING
*/

#include <stdio.h>
#include <stdlib.h>

int md;

void sort(int n,int a[]){
    int temp;
  for(int i = 0 ; i<n-1 ; i++){
    for(int j = i ; j<n; j++){
        if(a[i]>a[j]){
          temp = a[i];
          a[i] = a[j];
          a[j] = temp;
        }
    }
  }
}

void FCFS(int n,int a[]){
    int head,sk=0;
    printf("Enter initial head position : ");
    scanf("%d",&head);
    for(int i = 0 ; i<n ; i++){
        printf("%d -> ", head);
        sk = sk + abs(a[i]-head);
        head = a[i];
    }
    printf("%d\n", head);
    printf("seek time = %d\n" ,sk);
}


void SCAN(int n,int a[]){
    int head,sk=0;
    printf("Enter initial head position : ");
    scanf("%d",&head);
    int h = head;
    printf("to right\n");
    for(int i = 0 ; i<n ; i++){
       if(a[i]>head){
          printf("%d -> ", head);
          sk = sk + abs(a[i]-head);
          head = a[i];
       }
    }
    printf("%d",md-1);
    sk = sk + abs(md-1-head);
    head = md-1;
    for(int i = n-1 ; i>=0 ; i--){
       if(a[i]<h){
          sk = sk + abs(a[i]-head);
          printf(" ->%d", a[i]);
          head = a[i];
       }
    }
    printf("seek time = %d\n" ,sk);
    printf("to left\n");
    head = h;
    sk = 0;
    for(int i = n-1 ; i>=0 ; i--){
       if(a[i]<head){
          printf("%d ->", head);
          sk = sk + abs(a[i]-head);
          head = a[i];
       }
    }
    printf("0");
    sk = sk + head;
    head = 0;
    for(int i = 0 ; i<n ; i++){
       if(a[i]>h){
          sk = sk + abs(a[i]-head);
          printf(" ->%d", a[i]);
          head = a[i];
       }
    }
    printf("seek time = %d\n" ,sk);
}


void CSCAN(int n,int a[]){
    int head,sk=0;
    
    printf("Enter initial head position : ");
    scanf("%d",&head);
    int h = head;
    for(int i = 0 ; i<n ; i++){
       if(a[i]>head){
          printf("%d -> ", head);
          sk = sk + abs(a[i]-head);
          head = a[i];
       }
    }
    printf("%d ->",md-1);
    sk = sk + abs(md-1-head);
    head = md-1;
    
    printf("0");
    sk = sk + (md-1);
    head = 0;
    
    for(int i = 0 ; i<n ; i++){
       if(a[i]<h){
          sk = sk + abs(a[i]-head);
          printf(" ->%d", a[i]);
          head = a[i];
       }
    }
    printf("seek time = %d\n" ,sk);

}




void main(){
  int n,ch,ar[100];
  printf("Enter No. of disk requests : ");
  scanf("%d",&n);
  printf("Enter the disk requests : ");
  for(int i=0; i<n ; i++)
    scanf("%d",&ar[i]);
    
  printf("Enter disk limit : ");
  scanf("%d",&md);
  
  printf("1.FCFS\n2.SCAN\n3.CSCAN\n");
  while(1){
    printf("Enter choice : ");
    scanf("%d",&ch);
    switch(ch){
      case 1: FCFS(n,ar);
              break;
      case 2: sort(n,ar);
              SCAN(n,ar);
              break;
      case 3: sort(n,ar);
              CSCAN(n,ar);
              break;
      default: exit(0);
    }
  }
}




/*
OUTPUT


Enter No. of disk requests : 8
Enter the disk requests : 100 175 51 133 8 140 73 77
Enter disk limit : 200
1.FCFS
2.SCAN
3.CSCAN
Enter choice : 1
Enter initial head position : 63
63 -> 100 -> 175 -> 51 -> 133 -> 8 -> 140 -> 73 -> 77
seek time = 646
Enter choice : 2
Enter initial head position : 63
to right
63 -> 73 -> 77 -> 100 -> 133 -> 140 -> 199 ->51 ->8seek time = 327
to left
63 ->51 ->0 ->73 ->77 ->100 ->133 ->140 ->175seek time = 238
Enter choice : 3
Enter initial head position : 63
63 -> 73 -> 77 -> 100 -> 133 -> 140 -> 199 ->0 ->8 ->51seek time = 386
Enter choice : 5
*/
