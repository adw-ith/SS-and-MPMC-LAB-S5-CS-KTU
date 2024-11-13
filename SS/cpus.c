/*
Adwaith Raj
S5 CS
Roll No.5
Experiment No. 1

                             CPU SCHEDULING
*/
#include <stdio.h>
struct process{
  int ID,AT,BT,CT,TT,WT,status,prio;
}p[20],temp;
int i,j,n,min,num,b[20],p1=0,time=0;

void insert(){
   printf("Enter the number of processes\n");
    scanf("%d",&n);
    printf("Enter arrival time and burst time of each process\n");
    for(i=0;i<n;i++){
      p[i].ID=i+1;
      printf("p%d",p[i].ID);
      scanf("%d%d",&p[i].AT,&p[i].BT);
    }
}


void sort(){
    for(i=0;i<n-1;i++){
      for(j=0;j<n-1-i;j++){
        if(p[j].AT>p[j+1].AT){
          temp=p[j];
          p[j]=p[j+1];
          p[j+1]=temp;
        }
      }
    }
}

void fcfs(){
    p1=0,time=0;
    insert();
    sort();
    for(i=0;i<n;i++){
      if(p[i].AT>time){
        time=p[i].AT;
        i--;
      }
      else{
        time+=p[i].BT;
        p[i].CT=time;
        p[i].TT=p[i].CT-p[i].AT;
        p[i].WT=p[i].TT-p[i].BT;
      }
    }
    float wt=0,tt=0;
    for(i=0;i<n;i++){
      wt+=p[i].WT;
      tt+=p[i].TT;
    }
    printf("Avg TT=%f and Avg WT=%f\n",tt/n,wt/n);
}

void sjf(){
    insert();
    sort();
    num=n;
    while(num>0){
      min=100;
      for(i=0;i<n;i++){
        if(p[i].status==0&&p[i].AT<=time){
          min=i;
          break;
        }
      }
      for(i=0;i<n;i++){
        if(p[i].status==0&&p[i].AT<=time){
          if(p[i].BT<p[min].BT){
            min=i;
          }
          else if(p[i].BT==p[min].BT&&p[i].AT<p[min].AT){
            min=i;
          }
        }
      }
      if(min==100){
        for(i=0;i<n;i++){
          if(p[i].status==0){
          break;
          }
        }
        time=p[i].AT;

      }
      else{
        p[min].status=1;
        time+=p[min].BT;
        p[min].CT=time;
        p[min].TT=p[min].CT-p[min].AT;
        p[min].WT=p[min].TT-p[min].BT;
        num--;
      }
    }
    float wt=0,tt=0;
        for(i=0;i<n;i++){
      wt+=p[i].WT;
      tt+=p[i].TT;
    }
    printf("Avg TT=%f and Avg WT=%f\n",tt/n,wt/n);
}
int queue[50],rear=-1,front=-1;
void enqueue(int item){
  if(rear==-1&&front==-1){
    front=0;
    rear=0;
  }
  else{
    rear++;
  }
  queue[rear]=item;
}

int dequeue(){
  int item=queue[front];
  if(front==-1){
    return -1;
  }
  else if(front==rear){
    front=-1,rear=-1;
  }
  else{
    front++;
  }
  return item;
}

void rr(){
      p1=0,time=0;
      int k,tq;
    insert();
    sort();
    printf("Enter time quantum\n");
    scanf("%d",&tq);
    for(i=0;i<n;i++){
      b[i]=p[i].BT;
    }
    num=n;
    for(i=0;i<n;i++){
      if(p[i].status==0&&p[i].AT<=time){
        enqueue(i);
      }
    }
    while(num>0){
      k=dequeue();
      if(k==-1){
        for(i=0;i<n;i++){
          if(p[i].status==0){
            enqueue(i);
            time=p[i].AT;
          }
        }
      }
      else{
        if(p[k].BT<=tq){
          p[k].status=1;
          num--;
          for(i=0;i<n;i++){
            if(p[i].AT>time && p[i].AT<=time+p[k].BT){
              enqueue(i);
            }
          }
          time+=p[k].BT;
          p[k].CT=time;
          p[k].TT=p[k].CT-p[k].AT;
          p[k].WT=p[k].TT-b[k];
        }
        else{
          p[k].BT-=tq;
          for(i=0;i<n;i++){
            if(p[i].AT>time && p[i].AT<=time+tq){
             enqueue(i);
            }
          }
          time+=tq;
          enqueue(k);
        }
      }
    }
    float wt=0,tt=0;
        for(i=0;i<n;i++){
      wt+=p[i].WT;
      tt+=p[i].TT;
    }
    printf("Avg TT=%f and Avg WT=%f\n",tt/n,wt/n);
}
void nnp(){
    p1=0,time=0;
    printf("Enter the number of processes\n");
    scanf("%d",&n);
    printf("Enter arrival time ,burst time and priority of each process\n");
    for(i=0;i<n;i++){
      p[i].ID=i+1;
      p[i].status=0;
      printf("p%d",p[i].ID);
      scanf("%d%d%d",&p[i].AT,&p[i].BT,&p[i].prio);
    }
    sort();
    num=n;
    while(num>0){
      min=100;
      for(i=0;i<n;i++){
        if(p[i].status==0&&p[i].AT<=time){
          min=i;
          break;
        }
      }
      for(i=0;i<n;i++){
        if(p[i].status==0&&p[i].AT<=time){
          if(p[i].prio<p[min].prio){
            min=i;
          }
          else if(p[i].prio==p[min].prio&&p[i].AT<p[min].AT){
            min=i;
          }
        }
      }
      if(min==100){
        for(i=0;i<n;i++){
          if(p[i].status==0){
             break;
          }
        }
        time=p[i].AT;
      }
      else{
        p[min].status=1;
        time+=p[min].BT;
        p[min].CT=time;
        p[min].TT=p[min].CT-p[min].AT;
        p[min].WT=p[min].TT-p[min].BT;
        num--;
      }
    }
    float wt=0,tt=0;
        for(i=0;i<n;i++){
      wt+=p[i].WT;
      tt+=p[i].TT;
    }
    printf("Avg TT=%f and Avg WT=%f\n",tt/n,wt/n);
}

void main(){
  int ch;
  printf("Menu options\n1.FCFS\n2.SJF\n3.Round Robin\n4.Priority\n5.EXIT\n");
  do{
    printf("Enter your choice\n");
    scanf("%d",&ch);
    switch(ch){
      case 1:
        fcfs();
        break;
      case 2:
        sjf();
        break;
      case 3:
        rr();
        break;
      case 4:
        nnp();
        break;
      case 5:
        break;
      default:
       printf("Invalid choice\n");
      break;
    }
  }while(ch!=5);
}

/*
OUTPUT

Menu options
1.FCFS
2.SJF
3.Round Robin
4.Priority
5.EXIT
Enter your choice
1
Enter the number of processes
5
Enter arrival time and burst time of each process
p1 0 2
p2 1 3
p3 2 5
p4 3 4
p5 4 6
Avg TT=8.200000 and Avg WT=4.200000
Enter your choice
2
Enter the number of processes
5
Enter arrival time and burst time of each process
p1 3 1
p2 1 4
p3 4 2
p4 0 6
p5 2 3
Avg TT=8.000000 and Avg WT=4.800000
Enter your choice
3
Enter the number of processes
5
Enter arrival time and burst time of each process
p1 0 2
p2 2 1
p3 2 8 
p4 4 4
p5 3 5
Enter time quantum
3
Avg TT=9.800000 and Avg WT=5.800000
Enter your choice
4
Enter the number of processes
5
Enter arrival time ,burst time and priority of each process
p1 0 2 2
p2 2 1 1
p3 2 8 4
p4 4 4 2
p5 3 5 3
Avg TT=6.800000 and Avg WT=2.800000
Enter your choice

*/
