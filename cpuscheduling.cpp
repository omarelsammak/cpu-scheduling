#include <iostream>







#include <stdio.h>







#include <stdlib.h>







#include <limits.h>







#include <stdbool.h>







#include <queue>







#include <stack>







#include <cstdlib>







#include <list>







#include <string.h>

# define SIZE 100

#define QUEUE_EMPTY INT_MIN

using namespace std;

typedef struct Process

{







    char name;







    int arrival_time;







    int service_time;







    int waiting_time;







    int remaining_time;







    int turnaround_time;







    int finish_time;







    int rq;







    int flag;







    char*display;







} Process;



Process* Process_new(char name,int arrival_time, int service_time)

{







    Process* p = (Process*)malloc(sizeof(Process));







    p->name=name;







    p-> arrival_time=arrival_time;







    p-> service_time=service_time;







    p->waiting_time=0;







    p->remaining_time=service_time;

    p->finish_time=0;

    p->flag=0;

    p->turnaround_time=0;

    p->rq=0;

    return p ;







}







bool My_func2( Process* a, Process* b)

{







    return ((a->waiting_time+a->service_time)/a->service_time) >((b->waiting_time+b->service_time)/b->service_time);







}



bool My_func( Process* a, Process* b)

{







    return a->service_time < b->service_time;







}



bool My_func3( Process* a, Process* b)

{







    return a->rq < b->rq;







}



bool My_func4( Process* a, Process* b)

{







    return a->remaining_time < b->remaining_time;







}



void display(char*algo_name,int totaltime,Process *arr[],int number){







printf("%-6s",algo_name);







int i,j,z,m;







int counter=0;















for (i=0;i<=totaltime;i++){







            cout<<counter;







            cout<<" " ;







            counter++;







            	if (counter==10)







                	{







                	counter=0;







                	}















        }







        printf("\n");







    for(z=0;z<48;z++){







        cout<<"-" ;







    }







    printf("\n");







    for(i=0;i<number;i++){







        cout<<arr[i]->name;







        cout<<"     " ;







        for(j=0;j<totaltime;j++){







            printf("|");















            cout<< arr[i]->display[j];







           // cout<< arr[i];



        }







            printf("|");







            //cout<< *(arr[i]);







            printf(" \n");































    }























    		 for(m=0;m<48;m++){







        		cout<< "-" ;







    }















     printf("\n"); printf("\n");







}



int count_digit(int number)

{







    int tempnum=number;







    int counting=0;







    while(tempnum != 0)







    {







        tempnum = tempnum / 10;







        counting++;







    }







    return counting;







}



void stats(char*algo_name,int totaltime,Process *arr[],int number)

{



    printf("%s\n",algo_name);







    char* proc="Process";







    char* arriv="Arrival";







    char* serv="Service";







    char* fini="Finish";







    char* turn="Turnaround";







    char* normturn="NormTurn";







    printf("%-11s","Process");







    for (int i=0; i<number; i++)







    {







        printf("|  ");







        printf("%-3c",arr[i]->name);















    }







    printf("|\n");







    printf("%-11s","Arrival");







    for (int i=0; i<number; i++)







    {







        printf("|  ");







        printf("%-3d",arr[i]->arrival_time);















    }







    printf("|\n");







    printf("%-11s","Service");







    for (int i=0; i<number; i++)







    {







        printf("|  ");







        printf("%-3d",arr[i]->service_time);















    }







    printf("| Mean|\n");















    printf("%-11s","Finish");







    for (int i=0; i<number; i++)







    {







        int digit=count_digit(arr[i]->finish_time);







        if (digit==1)







        {







            printf("|  ");







            printf("%-3d",arr[i]->finish_time);







        }







        else







        {







            printf("| ");







            printf("%-3d ",arr[i]->finish_time);















        }















    }







    printf("|-----|\n");















    printf("%-11s","Turnaround");







    float turnar=0;







    for (int i=0; i<number; i++)







    {







        int digit=count_digit(arr[i]->turnaround_time);







        if (digit==1)







        {







            printf("|  ");







            printf("%-3d",arr[i]->turnaround_time);







        }







        else







        {







            printf("| ");







            printf("%-3d ",arr[i]->turnaround_time);















        }







        turnar+=arr[i]->turnaround_time*1.0;















    }







    turnar=turnar/(number*1.0);







    printf("|%5.2f|\n",turnar);























//turntime/service







    printf("%-11s","NormTurn");







    float normturnavg=0;







    float normturnar=0;







    for (int i=0; i<number; i++)







    {







        printf("|");







        normturnar=(1.0*arr[i]->turnaround_time/(1.0*arr[i]->service_time));







        printf("%5.02f",normturnar);







        normturnavg+=normturnar;







        normturnar=0;















    }















    normturnavg=normturnavg/(number*1.0);







    printf("|%5.2f|\n\n",normturnavg);







}



void FCFS(Process*arr[],int number,int totaltime)

{



    queue<Process*> q;

    Process* current_process;

    Process* current1;

    int running =0;







    for(int i=0; i<totaltime; i++)

    {







        for(int j=0; j< number; j++)



        {

   if (arr[j]->arrival_time==i)



            {







                q.push(arr[j]); // sort according to arrival time







            }







        }















        if (!running)







        {







            if(q.size())







            {







                current_process= (Process *)q.front() ;







                q.pop();







                running=1;







            }







            else{







            		continue;







            				}







            		}















            for(int k=0; k<q.size(); k++)







            {







                current1= (Process *)q.front() ;







                current1->waiting_time++;







                current1->display[i]='.';















                q.pop();







                q.push(current1);















            }















            current_process->remaining_time--;







            current_process->display[i]='*';















            if (current_process->remaining_time==0)







            {







                current_process->finish_time=i+1;







                current_process->turnaround_time=(current_process->finish_time)-(current_process->arrival_time);







              // printf("\n" " %d,%d,%d,%d,%d,%d",current_process->arrival_time,current_process->service_time,current_process->waiting_time,current_process->remaining_time,current_process->finish_time,current_process->turnaround_time);







                running=0;







            }







        }







    }







void RR(Process*arr[],int number, int quantum,int totaltime)

{

    queue<Process*> q;

    Process* current_process;

    Process* current1;

    int current_q=quantum;

    int running =0;

    for(int i=0; i<20; i++)

    {

        for(int j=0; j< number; j++)



    {

        if (arr[j]->arrival_time==i && arr[j]->flag==0)

            {



                q.push(arr[j]);

               arr[j]->flag=1;

            }



        }



        if (!running )



    {        if(q.size())



            {

                current_process= (Process *)q.front() ;

                q.pop();

                running=1;

                current_q=quantum;

            for(int k=0; k<q.size(); k++)



           {

                current1= (Process *)q.front() ;

                q.pop();

                current1->waiting_time++;

                current1->display[i]='.';

                q.push(current1);

            }

            }

        	else

                continue;}



        	else{

            for(int k=0; k<q.size(); k++)

            {

                current1= (Process *)q.front() ;

                q.pop();

                current1->waiting_time++;

                current1->display[i]='.';

                q.push(current1);

            }



        	}



            current_process->remaining_time--;

             current_process->display[i]='*';

            current_q--;

            if (current_process->remaining_time==0 || !current_q)



           {

                if(current_process->remaining_time==0 )



               {

                    current_process->finish_time=i+1;

                    current_process->turnaround_time=(current_process->finish_time)-(current_process->arrival_time);

                  //  printf("\n" " %d,%d,%d,%d,%d,%d",current_process->arrival_time,current_process->service_time,current_process->waiting_time,current_process->remaining_time,current_process->finish_time,current_process->turnaround_time);



                }



               else



               {

                  for(int j=0; j< number; j++)



			{



		    if (arr[j]->arrival_time==i+1 && arr[j]->flag==0)



		    {



			q.push(arr[j]);

			arr[j]->flag=1;



                    



		    }



			}



                  q.push(current_process);



               }



               running=0;

              current_q=quantum;



           }



       }



  }





























void HRRN(Process*arr[],int number,int totaltime)

{







    queue<Process*> q;







    list<Process* > listp;







    Process* current_process;







    Process* current1;

    int running =0;

    for(int i=0; i<totaltime; i++)

    {

        for(int j=0; j< number; j++)

        {

                        if (arr[j]->arrival_time==i)





            {







                listp.push_back(arr[j]);







            }







        }















        if(!running&&listp.size()!=0)







        {







            listp.sort(My_func2);







            current_process=listp.front() ;







            listp.pop_front();







            running=1;







        }







        int listpsize=listp.size();







        for(int k=0; k<listpsize; k++)







        {







            q.push(listp.back());







            listp.pop_back();















        }







        int qsize=q.size();















        for(int k=0; k<qsize; k++)







        {







            current1=q.front();







            q.pop();







            current1->waiting_time++;







            current1->display[i]='.';







            listp.push_back(current1);







        }







        //listp.sort ();







        current_process->remaining_time--;







        current_process->display[i]='*';















        if (current_process->remaining_time==0)







        {







            current_process->finish_time=i+1;







            current_process->turnaround_time=(current_process->finish_time)-(current_process->arrival_time);







           // printf("\n" " %c,%d,%d,%d,%d,%d,%d",current_process->name,current_process->arrival_time,current_process->service_time,current_process->waiting_time,current_process->remaining_time,current_process->finish_time,current_process->turnaround_time);







            running=0;







        }















    }







}



void SPN(Process*arr[],int number,int totaltime)



{







    queue<Process*> q;







    list<Process* > listp;







    Process* current_process;







    Process* current1;







    int running =0;







    for(int i=0; i<totaltime; i++)







    {







        for(int j=0; j< number; j++)







        {







            if (arr[j]->arrival_time==i)







            {







                listp.push_back(arr[j]);







            }







        }















        if(!running&&listp.size()!=0)







        {







            listp.sort(My_func);







            current_process=listp.front() ;







            listp.pop_front();







            running=1;







        }







        int listpsize=listp.size();







        for(int k=0; k<listpsize; k++)







        {







            q.push(listp.back());







            listp.pop_back();















        }







        int qsize=q.size();















        for(int k=0; k<qsize; k++)







        {







            current1=q.front();







            q.pop();







            current1->waiting_time++;







            current1->display[i]='.';







            listp.push_back(current1);







        }







        current_process->remaining_time--;







        current_process->display[i]='*';















        if (current_process->remaining_time==0)







        {







            current_process->finish_time=i+1;







            current_process->turnaround_time=(current_process->finish_time)-(current_process->arrival_time);







            //printf("\n" " %c,%d,%d,%d,%d,%d,%d",current_process->name,current_process->arrival_time,current_process->service_time,current_process->waiting_time,current_process->remaining_time,current_process->finish_time,current_process->turnaround_time);







            running=0;







        }















    }



}



void SRT(Process*arr[],int number,int totaltime)



{







    list<Process* > listp;







    Process* current_process;







    Process* current1;







    int running =0;







    for(int i=0; i<totaltime; i++)







    {







        for(int j=0; j< number; j++)







        {







            if (arr[j]->arrival_time==i)







            {







                listp.push_back(arr[j]);







            }







        }







        if(!running && listp.size() != 0 )







        {







            listp.sort(My_func4);







            current_process=listp.front() ;







            listp.pop_front();







            running=1;







            int listpsize=listp.size();







            for(int k=0; k<listpsize; k++)







            {







                current1=listp.front();







                listp.pop_front();







                current1->waiting_time++;







                current1->display[i]='.';







                listp.push_back(current1);







            }







            //listp.sort ();







            current_process->remaining_time--;







            current_process->display[i]='*';





            if (current_process->remaining_time==0)







            {







                current_process->finish_time=i+1;







                current_process->turnaround_time=(current_process->finish_time)-(current_process->arrival_time);







                //printf("\nName: %c\nArrivaltime: %d\nServicetime: %d\nWaitingtime: %d\nRemainingtime: %d\nFinishtime: %d\nTurnaroundtime: %d\n",current_process->name,current_process->arrival_time,current_process->service_time,current_process->waiting_time,current_process->remaining_time,current_process->finish_time,current_process->turnaround_time);







                running=0;







            }







            else







            {







                listp.push_back(current_process);

                running=0;







            }







        }







    }







}





void fb1(Process* arr[],int number,int totaltime){







	list<Process*> list1;







	list<Process*> list2;







	list<Process*> list3;







	list<Process*> list4;







	list<Process*> list5;







	int running=0,k;







	int q=1;







	int current_q;







	Process* current_process;







	Process* waiting;







	for(int i=0; i<totaltime; i++)







    	{







        for(int j=0; j< number; j++)







        {







            if (arr[j]->arrival_time==i  && arr[j]->flag==0 )







            {







                list1.push_back(arr[j]);







         	arr[j]->flag=1;















            }







      	}







   	if(!running){







	   	if(list1.size())







	   	{







			current_process= (Process *)list1.front() ;







			running=1;







		    	list1.pop_front();







			current_q=q;







	    	}







		else if(list2.size()){







			current_process= (Process *)list2.front() ;







			running=1;







		    	list2.pop_front();







			current_q=q;







		}







		else if(list3.size()){







			current_process= (Process *)list3.front() ;







			running=1;







		    	list3.pop_front();







			current_q=q;







		}







		else if(list4.size()){







			current_process= (Process *)list4.front() ;







			running=1;







		    	list4.pop_front();







			current_q=q;







		}







		else if(list5.size()){







			current_process= (Process *)list5.front() ;







			running=1;







	    		list5.pop_front();







			current_q=q;







		}







		else







		{







			continue;







		}















    	}







        for( k=0; k<list1.size() ; k++)







        {







            waiting= (Process *)list1.front() ;







            waiting->waiting_time++;



            waiting->display[i]='.';







            list1.pop_front();







            list1.push_back(waiting);







	}















	for( k=0; k<list2.size() ; k++)







        {







            waiting= (Process *)list2.front() ;







            waiting->waiting_time++;



waiting->display[i]='.';



            list2.pop_front();







            list2.push_back(waiting);







	}















	for( k=0; k<list3.size() ; k++)







        {







            waiting= (Process *)list3.front() ;







            waiting->waiting_time++;



    waiting->display[i]='.';



            list3.pop_front();







            list3.push_back(waiting);























           }















           for( k=0; k<list4.size() ; k++)







        {







            waiting= (Process *)list4.front() ;







            waiting->waiting_time++;



            waiting->display[i]='.';







            list4.pop_front();







            list4.push_back(waiting);















        }















          for( k=0; k<list5.size() ; k++)







        {







            waiting= (Process *)list5.front() ;



            waiting->display[i]='.';



            waiting->waiting_time++;







            list5.pop_front();







            list5.push_back(waiting);















        }







        current_process->remaining_time--;



        current_process->display[i]='*';







	current_q--;







	if (current_process->remaining_time==0 || !current_q)







            {







                if(current_process->remaining_time==0 )







                {







                    current_process->finish_time=i+1;







                    current_process->turnaround_time=(current_process->finish_time)-(current_process->arrival_time);







                    //printf("\nName: %c\nArrivaltime: %d\nServicetime: %d\nWaitingtime: %d\nRemainingtime: %d\nFinishtime: %d\nTurnaroundtime: %d\n",current_process->name,current_process->arrival_time,current_process->service_time,current_process->waiting_time,current_process->remaining_time,current_process->finish_time,current_process->turnaround_time);















                running=0;







                    current_q=q;







                }















                else







                {







                    for(int j=0; j< number; j++)







			{







			    if (arr[j]->arrival_time==i+1 && arr[j]->flag==0)







			    {







				list1.push_back(arr[j]);







				arr[j]->flag=1;







			    }







		      	}







                	if (list1.size() || list2.size() || list3.size() || list4.size() || list5.size() )







                    	{







                    		current_process-> rq++;







                    		if(current_process->rq==0){







                    		list1.push_back(current_process);







                    		}







                    		else if(current_process->rq==1)







                    		{







                    		list2.push_back(current_process);







                    		}







                    		else if(current_process->rq==2)







                    		{







                    		list3.push_back(current_process);







                    		}







                    		else if(current_process->rq==3)







                    		{







                    		list4.push_back(current_process);







                    		}







                    		else







                    		{







                    		list5.push_back(current_process);







                    		}







                		running=0;







                	}















                	current_q=q;







            }







        }







    }







































}





void fb2(Process* arr[],int number,int totaltime){







	list<Process*> list1;







	list<Process*> list2;







	list<Process*> list3;







	list<Process*> list4;







	list<Process*> list5;







	int running=0,k;







	int current_q;







	int q;







	Process* current_process;







	Process* waiting;







	for(int i=0; i<totaltime; i++)







    	{







        for(int j=0; j< number; j++)







        {







            if (arr[j]->arrival_time==i  && arr[j]->flag==0 )







            {







                list1.push_back(arr[j]);







                arr[j]->flag=1;























            }







      	}







   	if(!running){







	   	if(list1.size())







	   	{







			current_process= (Process *)list1.front() ;







			running=1;







		    	list1.pop_front();







			current_q=1;







			q=current_q;







	    	}







		else if(list2.size()){







			current_process= (Process *)list2.front() ;







			running=1;







		    	list2.pop_front();







			current_q=2;







			q=current_q;







		}







		else if(list3.size()){







			current_process= (Process *)list3.front() ;







			running=1;







		    	list3.pop_front();







			current_q=4;







			q=current_q;







		}







		else if(list4.size()){







			current_process= (Process *)list4.front() ;







			running=1;







		    	list4.pop_front();







			current_q=8;







			q=current_q;







		}







		else if(list5.size()){







			current_process= (Process *)list5.front() ;







			running=1;







	    		list5.pop_front();







			current_q=16;







			q=current_q;







		}







		else







		{







			continue;







		}





    	}







        for( k=0; k<list1.size() ; k++)







        {







            waiting= (Process *)list1.front() ;







            waiting->waiting_time++;







            waiting->display[i]='.';







            list1.pop_front();







            list1.push_back(waiting);







	}















	for( k=0; k<list2.size() ; k++)







        {







            waiting= (Process *)list2.front() ;







            waiting->waiting_time++;







            waiting->display[i]='.';







            list2.pop_front();







            list2.push_back(waiting);







	}















	for( k=0; k<list3.size() ; k++)







        {







            waiting= (Process *)list3.front() ;







            waiting->waiting_time++;







            waiting->display[i]='.';







            list3.pop_front();







            list3.push_back(waiting);























           }















           for( k=0; k<list4.size() ; k++)







        {







            waiting= (Process *)list4.front() ;







            waiting->waiting_time++;







            waiting->display[i]='.';







            list4.pop_front();







            list4.push_back(waiting);















        }















          for( k=0; k<list5.size() ; k++)







        {







            waiting= (Process *)list5.front() ;







            waiting->waiting_time++;







            waiting->display[i]='.';







            list5.pop_front();







            list5.push_back(waiting);















        }







        current_process->remaining_time--;







        current_process->display[i]='*';







	current_q--;







	if (current_process->remaining_time==0 || !current_q)







            {







                if(current_process->remaining_time==0 )







                {







                    current_process->finish_time=i+1;







                    current_process->turnaround_time=(current_process->finish_time)-(current_process->arrival_time);







//                    printf("\nName: %c\nArrivaltime: %d\nServicetime: %d\nWaitingtime: %d\nRemainingtime: %d\nFinishtime: %d\nTurnaroundtime: %d\n",current_process->name,current_process->arrival_time,current_process->service_time,current_process->waiting_time,current_process->remaining_time,current_process->finish_time,current_process->turnaround_time);















                running=0;







                    //current_q=q;







                }















                else







                {







                    for(int j=0; j< number; j++)







			{







			    if (arr[j]->arrival_time==i+1 && arr[j]->flag==0)







			    {







				list1.push_back(arr[j]);







				arr[j]->flag=1;







			    }







		      	}







                	if (list1.size() || list2.size() || list3.size() || list4.size() || list5.size() )







                    	{







                    		current_process-> rq++;







                    		if(current_process->rq==0){







                    		list1.push_back(current_process);







                    		}







                    		else if(current_process->rq==1)







                    		{







                    		list2.push_back(current_process);







                    		}







                    		else if(current_process->rq==2)







                    		{







                    		list3.push_back(current_process);







                    		}







                    		else if(current_process->rq==3)







                    		{







                    		list4.push_back(current_process);







                    		}







                    		else







                    		{







                    		list5.push_back(current_process);







                    		}







                		running=0;







                	}







                	current_q=q;







            	}







        }







    }























}





int main(){







    char type[6],pname,ch;







    char alname [20];







    Process*p;







    int q=0;







    int algorithm,quantum,number,totaltime,arrivaltime,servicetime,priority;







    scanf("%s",type);







    ch = getchar();







    scanf("%d-%d",&algorithm,&quantum);







    ch=getchar();







    scanf("%d",&totaltime);







    ch=getchar();







    scanf("%d",&number);







    ch=getchar();







    Process* arr[number];







    for (int i=0;i<number;i++)







        {







            scanf("%c,%d,%d",&pname,&arrivaltime,&servicetime);







            ch=getchar();







            p=Process_new(pname,arrivaltime,servicetime);







            arr[i]=p;







        }







    //int number=(sizeof(arr)/sizeof(arr[0]));







    int k=0;







    for(k=0;k<number;k++){







        arr[k]->display=(char*)malloc(totaltime);







         for (int i = 0 ; i < totaltime ; i++)







    {







        arr[k]->display[i] = ' ';















    }







    	arr[k]->display[totaltime] = '\0';







    }







    int switching=0;







    if (!strcmp(type,"trace")){







         switching=0;







    }







    else {







             switching=1;







    }















    //fb1(arr,q,number);







if (switching==0){







        switch (algorithm){







            case 1:







            FCFS(arr,number,totaltime);







            display("FCFS",totaltime,arr,number);







            break;







        case 2:







        sprintf(alname,"RR-%d",quantum);







        RR(arr,number,quantum,totaltime);







        display(alname ,totaltime,arr,number);







        break;







        case 3:







            SPN(arr,number,totaltime);







        display("SPN",totaltime,arr,number);







        break;







        case 4:







            SRT(arr,number,totaltime);







        display("SRT",totaltime,arr,number);







        break;







        case 5:







            HRRN(arr,number,totaltime);







            display("HRRN",totaltime,arr,number);







        break;







        case 6:







            fb1(arr,number,totaltime);







            display("FB-1",totaltime,arr,number);







            break;







        case 7:







            fb2(arr,number,totaltime);







            //printf("aly\n");







            display("FB-2i",totaltime,arr,number);







        break;







}







}







else {switch(algorithm){







case 1:







    FCFS(arr,number,totaltime);







    stats("FCFS",totaltime,arr,number);







    break;







    case 2:







        RR(arr,number,quantum,totaltime);







        sprintf(alname,"RR-%d",quantum);







    stats(alname ,totaltime,arr,number);







    break;







    case 3:
        SPN(arr,number,totaltime);
    stats("SPN",totaltime,arr,number);
    break;
    case 4:
        SRT(arr,number,totaltime);
    stats("SRT",totaltime,arr,number);
    break;
    case 5:
        HRRN(arr,number,totaltime);
    stats("HRRN",totaltime,arr,number);
    break;
    case 6:
        fb1(arr,number,totaltime);
    stats("FB-1",totaltime,arr,number);
    break;
    case 7:
        fb2(arr,number,totaltime);
    stats("FB-2i",totaltime,arr,number);
    break;
}


    }
return 0;
}



