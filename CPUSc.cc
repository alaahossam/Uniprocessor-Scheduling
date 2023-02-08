/*
    Hend Khaled Abdelhamid Mohamed Mohamed Aly 6986
    Alaa Hossam Abdelmawla Abu Hashima         6750                
*/
/* Cpu Scheduling*/

#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include <algorithm>
#include <bits/stdc++.h>
#include <iomanip>
#include <vector>
#include<fstream>
#include <queue>

using namespace std;




/****           Global Implementations         ****/ 
struct process
{
    int pid;
    char name;
    int arrivaltime;
    int bursttime;
    int starttime;
    int remainingtime;
    int finishtime;
    int responsetime;
    int turnAtime;
    int waittime;
    float NTAT;
    float rr=0;
    queue <int> start;
    queue <int> finishing;
    queue <int> running;
};

string mode;
int pro,timer;
string n;
string k;
string algo;
string algorithm;
int arrive[10];
int serv[10];
string pr;
int l;

struct process p[200];
int nprocesses;
int quantum;
int c;
float avg_waittime;
float avg_NTAT;
float avg_turnAtime;
float avg_responsetime;
int total_burst;
int total_turnAround;
float total_NTAT;
int total_wait;
int total_response;
int currenttime;
int bursttime_rem[100];
float NTAT[100];
char letter[10];
char temp[1];

void insertion(int nprocesses){
    int i;
    int x;
    for(i=0;i<nprocesses;i++){
       std:: getline(cin,pr);
        l=pr.length();
        char str[l+1];
		strcpy(str,pr.c_str());
        char *tok=strtok(str,",");
        int count=0;
        while(tok!=NULL)
        {
            count++;
            switch (count)
            {
                case 1:
                {
                    strcpy(temp,tok);
                    letter[i]=temp[0];
		            break;
                }
		        case 2:
		        {
		            char arrival[10];
		            strcpy(arrival,tok);
		            arrive[i]= stoi(arrival);
		            break;
		        }
                case 3:
		        {
		           char burst[10];
		            strcpy(burst,tok);
		            serv[i]=stoi(burst);
		            break;
		        }

            }
            tok=strtok(NULL,",");	
        }
        p[i].pid = i+1;
        
    }
    for(i=0;i<nprocesses;i++){
     p[i].name=letter[i];
     p[i].arrivaltime = arrive[i];
     p[i].bursttime = serv[i];
    }
}

void printing()
{
    
    avg_turnAtime=(float)total_turnAround / (float)nprocesses;
   
    cout<<"\nProcess    |";
    for (int i=0; i<nprocesses; i++){
    cout << "  " << p[i].name << "  |";
    }

    cout<<"\nArrival    |";
    for (int i=0; i<nprocesses; i++){
        if (p[i].arrivaltime > 9999)
            cout << p[i].arrivaltime << "|";
        else if (p[i].arrivaltime > 999)
            cout << p[i].arrivaltime << " |";
        else if (p[i].arrivaltime > 99)
            cout << p[i].arrivaltime << "  |";
        else if (p[i].arrivaltime > 9)
            cout << " " << p[i].arrivaltime << "  |";
        else
            cout << "  " << p[i].arrivaltime << "  |";
    }
    
    cout<<"\nService    |";
    for (int i=0; i<nprocesses; i++){
        if (p[i].bursttime > 9999)
            cout << p[i].bursttime << "|";
        else if (p[i].bursttime > 999)
            cout << p[i].bursttime << " |";
        else if (p[i].bursttime > 99)
            cout << p[i].bursttime << "  |";
        else if (p[i].bursttime > 9)
            cout << " " << p[i].bursttime << "  |";
        else
            cout << "  " << p[i].bursttime << "  |";
    }
    cout<<" Mean|";

    cout<<"\nFinish     |";
    for (int i=0; i<nprocesses; i++){
        if (p[i].finishtime > 9999)
            cout << p[i].finishtime << "|";
        else if (p[i].finishtime > 999)
            cout << p[i].finishtime << " |";
        else if (p[i].finishtime > 99)
            cout << p[i].finishtime << "  |";
        else if (p[i].finishtime > 9)
            cout << " " << p[i].finishtime << "  |";
        else
            cout << "  " << p[i].finishtime << "  |";
    }
    cout<<"-----|";

    cout<<"\nTurnaround |";
    for (int i=0; i<nprocesses; i++){
        if (p[i].turnAtime > 9999)
            cout << p[i].turnAtime << "|";
        else if (p[i].turnAtime > 999)
            cout << p[i].turnAtime << " |";
        else if (p[i].turnAtime > 99)
            cout << p[i].turnAtime << "  |";
        else if (p[i].turnAtime > 9)
            cout << " " << p[i].turnAtime << "  |";
        else
            cout << "  " << p[i].turnAtime << "  |";
    }
    if(avg_turnAtime>9.99)
    {
        printf("%0.2f|",avg_turnAtime);
    }
    else
    {
        printf(" %0.2f|",avg_turnAtime);
    }

    cout<< "\nNormTurn   |";
    for (int i=0; i<nprocesses; i++){
    NTAT [i]= ((1.0)*(p[i].turnAtime)) /((1.0)*( p[i].bursttime));
    total_NTAT = total_NTAT + NTAT[i];
    printf(" %0.2f|", NTAT[i]);
    }
    avg_NTAT= (float)total_NTAT /(float)nprocesses;
    if (avg_NTAT>9.99)
    {
        printf("%0.2f|\n",avg_NTAT);
    }
    else {
        printf(" %0.2f|\n",avg_NTAT);
    }
}

/*Finish Time Calculation*/
void finishTime( process p[100] , int nprocesses)
{
    /*first process waiting time is 0*/
    p[0].finishtime = p[0].bursttime;
    p[1].finishtime=p[1].bursttime + p[0].finishtime;
    /*finish time = burst time old + burst time*/
    for (int  i = 2; i < nprocesses ; i++)
    {
        p[i].finishtime =p[i].bursttime + p[i-1].finishtime ;
    }
}

/*Turn Around Time Calculation*/
void turnAroundTime(process p[100], int nprocesses)
{
    /*turn around time = burst time + waiting time*/
    for (int  i = 0; i < nprocesses ; i++)
    {
        p[i].turnAtime = p[i].finishtime - p[i].arrivaltime;
    }
}

/*Waiting Time Calculation*/
void waitingTime(process p[100], int nprocesses)
{
    /*n is number of processes*/
    /*first process waiting time is 0*/
    p[0].waittime = 0;
    /*Calculating wait time of the rest of the processes*/
    for (int  i = 1; i < nprocesses ; i++ )
    {
        p[i].waittime = p[i].turnAtime - p[i].bursttime;
    }
}

bool bursttimeSort(process a,process b){
    return a.bursttime < b.bursttime; 
}
bool arrivetimeSort(process a,process b){
    return a.arrivaltime < b.arrivaltime; 
}
bool nameSort(process a , process b){
    return a.name < b.name;
}
bool rrtimeSort(process a,process b){
    return a.rr > b.rr; 
}

/*===========================================================================================*/

/****           FCFS ===> Trace      ****/ 

void FCFStrace ()
{
    insertion(nprocesses);
   
    total_wait = 0;
    total_turnAround = 0;  
    /*finish time calculation*/
    finishTime(p,nprocesses);
    /*turnaround time calculation*/
    turnAroundTime(p, nprocesses);
    /*waiting time calculation*/
    waitingTime(p, nprocesses);

    /*total wait time and total turnaround time calculation*/
    for(int i=0;i<nprocesses;i++)
    {
        total_wait = total_wait + p[i].waittime ;
        total_turnAround = total_turnAround + p[i].turnAtime;
    }
    

    avg_waittime= (float)total_wait /(float)nprocesses;
    avg_turnAtime=(float)total_turnAround / (float)nprocesses;
    
    int k=20;
    char trace[nprocesses][k];
    printf("FCFS  ");
    for(int i=0;i<k+1;i++)
    {
        printf("%d ",i%10);
    }
    cout<<"\n------------------------------------------------\n";
    for(int i=0;i<nprocesses;i++){

    	cout <<p[i].name <<"     "<<"|";
    	for(int j=0;j<k;j++){
    	 trace[i][j]={' '};
                if(j>=p[i].arrivaltime && p[i].waittime!=0 && j<p[i].finishtime){
                    trace[i][j]={'.'};
    		}
    	     	if(j>=p[i].arrivaltime+p[i].waittime && j<p[i].finishtime){
                        trace[i][j]={'*'};
    		}

   	 cout<<trace[i][j];
    	 cout<<"|";
    	}
        cout<<" ";
    	cout<<"\n";
    }
    cout<<"------------------------------------------------\n";
}
   

/*===========================================================================================*/

/****           FCFS     ===> Stats      ****/ 

void FCFSstats ()
{
    insertion(nprocesses);
    total_wait = 0;
    total_turnAround = 0;  
    /*finish time calculation*/
    finishTime(p,nprocesses);
    /*turnaround time calculation*/
    turnAroundTime(p, nprocesses);
    /*waiting time calculation*/
    waitingTime(p, nprocesses);

    /*total wait time and total turnaround time calculation*/
    for(int i=0;i<nprocesses;i++)
    {
        total_wait = total_wait + p[i].waittime ;
        total_turnAround = total_turnAround + p[i].turnAtime;
    }
    printf("FCFS");    
    printing();

}
   


/*===========================================================================================*/
/****           Round Robin  insertion        ****/ 
void insertrr(int nprocesses){
    int i;
    int x;
    for(i=0;i<nprocesses;i++){
       std:: getline(cin,pr);
        l=pr.length();
        char str[l+1];
		strcpy(str,pr.c_str());
        char *tok=strtok(str,",");
        int count=0;
        while(tok!=NULL)
        {
            count++;
            switch (count)
            {
                case 1:
                {
                    strcpy(temp,tok);
                    letter[i]=temp[0];
		            break;
                }
		        case 2:
		        {
		            char arrival[10];
		            strcpy(arrival,tok);
		            arrive[i]= stoi(arrival);
		            break;
		        }
                case 3:
		        {
		           char burst[10];
		            strcpy(burst,tok);
		            serv[i]=stoi(burst);
		            break;
		        }

            }
            tok=strtok(NULL,",");	
        }
        p[i].pid = i+1;
        
    }
    for(i=0;i<nprocesses;i++){
     p[i].name=letter[i];
     p[i].arrivaltime = arrive[i];
     p[i].bursttime = serv[i];
    }
}

/*===========================================================================================*/
/****           Round Robin  trace        ****/ 
void RRtrace()
{
    vector<int> ns;

    insertrr(nprocesses);
    /*storing the burst or service time of each process in new array*/
    for(int i=0;i<nprocesses;i++)
        {
         bursttime_rem[i] = p[i].bursttime;
        }

/*Sorting processes according to arrival time*/
    sort(p,p+nprocesses,arrivetimeSort);
    process temp[200];
    for(int i=0;i<nprocesses;i++)
        {
            temp[i] = p[i];
        }
/*creating queue Q to enqueue the running process in it*/
    queue <int> Q;
    currenttime=0;
    total_wait = 0;
    total_turnAround = 0;
    int index =0;
    int done=0;
    int finished[100];
    Q.push(0);
    memset(finished,0,sizeof(finished));
    finished[0]=1;

    /*loop until all processes are finished*/
    while (done != nprocesses)
    {

        index = Q.front();
        ns.push_back(Q.front());
        Q.pop();

        /*if the process is ready, didn't run before*/
        if(bursttime_rem[index] == p[index].bursttime)
        {
            p[index].starttime = max(currenttime, p[index].arrivaltime);
            currenttime = p[index].starttime;
        }
        /*c is the quantum*/
        if (bursttime_rem[index] - c > 0)
        {
            bursttime_rem[index] = bursttime_rem[index] - c;
            currenttime = currenttime + c;
        }
        else{
            currenttime = currenttime + bursttime_rem[index];
            bursttime_rem[index] = 0;
            /*the process is finished*/
            done ++;
            /*calculate finish time, turnaround time, and waiting time*/
            p[index].finishtime = currenttime;
            temp[index].finishtime = p[index].finishtime;
            p[index].turnAtime = p[index].finishtime - p[index].arrivaltime;
            p[index].waittime = p[index].turnAtime - p[index].bursttime;
        
            /*calculating total turnaround time and total wait time*/
            total_turnAround += p[index].turnAtime;
            total_wait += p[index].waittime;
        }

                for(int i = 1; i < nprocesses; i++) {
             /*if the remaining time of process > 0 and
            the process arrival time is in the past and
            process isn't finished yet
            put it into the queue of unfinished processes*/
            if(bursttime_rem[i] > 0 && p[i].arrivaltime <= currenttime && finished[i] == 0) {
                Q.push(i);
                finished[i] = 1;
            }
        }
        /*if the process has stopped due to quantum but didn't finish yet
        put it into the queue*/
        if(bursttime_rem[index] > 0) {
            Q.push(index);
        }

        if(Q.empty()) {
            for(int i = 1; i < nprocesses; i++) {
                if(bursttime_rem[i] > 0) {
                    Q.push(i);
                    finished[i] = 1;
                    break;
                }
            }
        }

        /*average turnaround time and wait time calculation*/
    avg_turnAtime = (float) total_turnAround / nprocesses;
    avg_waittime = (float) total_wait / nprocesses;
    }
    sort(p,p+nprocesses,nameSort);
   
    int k=20;
    char trace[nprocesses][k];
    vector<vector<char>> status(nprocesses, vector<char>(k, ' '));
    vector<int> nss;
    for(int i = 0 ; i < ns.size();i++){
        if(temp[ns[i]].bursttime  > c){
            for(int x = 0 ; x < c ; x++) nss.push_back(ns[i]);
            temp[ns[i]].bursttime-=c;
        }else if(temp[ns[i]].bursttime <= c){
            for(int x = 0 ; x < temp[ns[i]].bursttime ; x++) nss.push_back(ns[i]);
            temp[ns[i]].bursttime = 0;
        }
    }
    ns = nss;
    for(int i = 0 ; i < status[0].size();i++){
        for(int x = 0 ; x < status.size();x++){
            if(temp[x].finishtime > i && temp[x].arrivaltime <= i)
                status[x][i] = '.';
        }
    }
    for(int i = 0 ; i < ns.size() && i <= k ; i++){
            status[ns[i]][i] = '*';
    }

    cout << "RR-" <<c<<"  ";
    for (int i = 0; i <= k; i++)
        cout << i % 10 << " ";
    cout << "\n";
    cout << "------";
    for (int i = 0; i <= k * 2; i++)
        cout << "-";
    cout << "-\n";
    for (int i = 0; i < status.size(); i++)
    {
        cout << p[i].name << "     |";
        for (int x = 0; x < status[i].size(); x++)
        {
            cout << status[i][x] << "|";
        }
        cout << " \n";
    }
    cout << "------";
    for (int i = 0; i <= k * 2; i++)
        cout << "-";
    cout << "-\n";
    cout << endl;

    vector<int> v;
    ns = v;
}

/*===========================================================================================*/
/****           Round Robin  ===> Stats        ****/ 
void RR()
{

}
void RRstats()
{
    vector<int> ns;

    insertrr(nprocesses);
    /*storing the burst or service time of each process in new array*/
    for(int i=0;i<nprocesses;i++)
        {
         bursttime_rem[i] = p[i].bursttime;
        }

/*Sorting processes according to arrival time*/
    sort(p,p+nprocesses,arrivetimeSort);
    process temp[200];
    for(int i=0;i<nprocesses;i++)
        {
            temp[i] = p[i];
        }
/*creating queue Q to enqueue the running process in it*/
    queue <int> Q;
    currenttime=0;
    total_wait = 0;
    total_turnAround = 0;
    int index =0;
    int done=0;
    int finished[100];
    Q.push(0);
    memset(finished,0,sizeof(finished));
    finished[0]=1;

    /*loop until all processes are finished*/
    while (done != nprocesses)
    {

        index = Q.front();
        ns.push_back(Q.front());
        Q.pop();

        /*if the process is ready, didn't run before*/
        if(bursttime_rem[index] == p[index].bursttime)
        {
            p[index].starttime = max(currenttime, p[index].arrivaltime);
            currenttime = p[index].starttime;
        }
        if (bursttime_rem[index] - c > 0)
        {
            bursttime_rem[index] = bursttime_rem[index] - c;
            currenttime = currenttime + c;
        }
        else{
            currenttime = currenttime + bursttime_rem[index];
            bursttime_rem[index] = 0;
            /*the process is finished*/
            done ++;
            /*calculate finish time, turnaround time, and waiting time*/
            p[index].finishtime = currenttime;
            temp[index].finishtime = p[index].finishtime;
            p[index].turnAtime = p[index].finishtime - p[index].arrivaltime;
            p[index].waittime = p[index].turnAtime - p[index].bursttime;
        
            /*calculating total turnaround time and total wait time*/
            total_turnAround += p[index].turnAtime;
            total_wait += p[index].waittime;
        }

                for(int i = 1; i < nprocesses; i++) {
             /*if the remaining time of process > 0 and
            the process arrival time is in the past and
            process isn't finished yet
            put it into the queue of unfinished processes*/
            if(bursttime_rem[i] > 0 && p[i].arrivaltime <= currenttime && finished[i] == 0) {
                Q.push(i);
                finished[i] = 1;
            }
        }
        /*if the process has stopped due to quantum but didn't finish yet
        put it into the queue*/
        if(bursttime_rem[index] > 0) {
            Q.push(index);
        }

        if(Q.empty()) {
            for(int i = 1; i < nprocesses; i++) {
                if(bursttime_rem[i] > 0) {
                    Q.push(i);
                    finished[i] = 1;
                    break;
                }
            }
        }

        /*average turnaround time and wait time calculation*/
    avg_turnAtime = (float) total_turnAround / nprocesses;
    avg_waittime = (float) total_wait / nprocesses;
    }
    sort(p,p+nprocesses,nameSort);

    printf("RR-%d",c);
    printing();

}


/*===========================================================================================*/

/****           SPN Implementation    ===> Trace     ****/

void SPNtrace()
{
    insertion(nprocesses);

    int total_burst =0;
    for(int i=0;i<nprocesses;i++)
        {
            total_burst= total_burst + p[i].bursttime;
        }
    /*sort the processes according to their burst time and arrival time*/
    sort(p,p+nprocesses,bursttimeSort);
    sort(p,p+nprocesses,arrivetimeSort);

    int totaltime=0;
    /*store a copy of the total time of each process*/
    int TA[nprocesses];
    int i,j;
    for(i=0;i<nprocesses;i++){
        j=i;
        while(p[j].arrivaltime<=totaltime&&j!=nprocesses){
            j++;
        }
        /*sort the ready processes according to their burst time*/
        sort(p+i,p+j,bursttimeSort);
        TA[i]=totaltime;
        totaltime+=p[i].bursttime;
    }

    TA[i] = totaltime;

    /*wait time storing in processes*/
    for(int i=0;i<nprocesses;i++)
    {
        p[i].waittime = TA[i]-p[i].arrivaltime;
        total_wait = total_wait+(TA[i]-p[i].arrivaltime);
    }
    /*turnaround time storing in processes*/
    for(int i=0;i<nprocesses;i++)
    {
        p[i].turnAtime=TA[i]-p[i].arrivaltime+p[i].bursttime;
        total_turnAround = total_turnAround+(TA[i]-p[i].arrivaltime+p[i].bursttime);
    }
    /*Norm TA time storing in processes*/
    for(int i=0;i<nprocesses;i++)
    {
        NTAT[i] = (1.0*(TA[i]-p[i].arrivaltime+p[i].bursttime)) /(1.0*( p[i].bursttime));
    }
    /*Finish Time storing in processes*/
        for(int i=0;i<nprocesses;i++)
    {
        p[i].finishtime = TA[i+1];
    }
    /*Norm TAT storing in process*/
    for(int i=0;i<nprocesses;i++)
    {
        p[i].NTAT = NTAT[i];
    }
    /*sort the processes by name to display them ascendingly*/
    sort(p,p+nprocesses,nameSort);
    
    avg_waittime= (float)total_wait /(float)nprocesses;
    avg_turnAtime=(float)total_turnAround / (float)nprocesses;


        int k=20;
    char trace[nprocesses][k];
    printf("SPN   ");
    for(int i=0;i<k+1;i++)
    {
        printf("%d ",i%10);
    }
    cout<<"\n------------------------------------------------\n";
    for(int i=0;i<nprocesses;i++){

    	cout <<p[i].name <<"     "<<"|";
    	for(int j=0;j<k;j++){
    	 trace[i][j]={' '};
                if(j>=p[i].arrivaltime && p[i].waittime!=0 && j<p[i].finishtime){
                    trace[i][j]={'.'};
    		}
    	     	if(j>=p[i].arrivaltime+p[i].waittime && j<p[i].finishtime){
                        trace[i][j]={'*'};
    		}

   	 cout<<trace[i][j];
    	 cout<<"|";
         
    	}
        cout<<" ";
        cout<<"\n";
    }
    cout<<"------------------------------------------------\n";
}

/*===========================================================================================*/

/****           SPN Implementation ===> Stats        ****/

void SPNstats()
{
    insertion(nprocesses);

    int total_burst =0;
    for(int i=0;i<nprocesses;i++)
        {
            total_burst= total_burst + p[i].bursttime;
        }
    /*sort the processes according to their burst time and arrival time*/
    sort(p,p+nprocesses,bursttimeSort);
    sort(p,p+nprocesses,arrivetimeSort);

    int totaltime=0;
    /*store a copy of the total time of each process*/
    int TA[nprocesses];
    int i,j;
    for(i=0;i<nprocesses;i++){
        j=i;
        while(p[j].arrivaltime<=totaltime&&j!=nprocesses){
            j++;
        }
        /*sort the ready processes according to their burst time*/
        sort(p+i,p+j,bursttimeSort);
        TA[i]=totaltime;
        totaltime+=p[i].bursttime;
    }

    TA[i] = totaltime;

    /*wait time storing in processes*/
    for(int i=0;i<nprocesses;i++)
    {
        p[i].waittime = TA[i]-p[i].arrivaltime;
        total_wait = total_wait+(TA[i]-p[i].arrivaltime);
    }
    /*turnaround time storing in processes*/
    for(int i=0;i<nprocesses;i++)
    {
        p[i].turnAtime=TA[i]-p[i].arrivaltime+p[i].bursttime;
        total_turnAround = total_turnAround+(TA[i]-p[i].arrivaltime+p[i].bursttime);
    }
    /*Norm TA time storing in processes*/
    for(int i=0;i<nprocesses;i++)
    {
        NTAT[i] = (1.0*(TA[i]-p[i].arrivaltime+p[i].bursttime)) /(1.0*( p[i].bursttime));
    }
    /*Finish Time storing in processes*/
        for(int i=0;i<nprocesses;i++)
    {
        p[i].finishtime = TA[i+1];
    }
    /*Norm TAT storing in process*/
    for(int i=0;i<nprocesses;i++)
    {
        p[i].NTAT = NTAT[i];
    }
    /*sort the processes by name to display them ascendingly*/
    sort(p,p+nprocesses,nameSort);
    
    avg_waittime= (float)total_wait /(float)nprocesses;
    avg_turnAtime=(float)total_turnAround / (float)nprocesses; 
    
    printf("SPN");
    printing();
}

/*===========================================================================================*/

/****           SRT Implementation   ===> trace      ****/ 

void SRTtrace ()
{
    int waiting[10],turnaround[10],finish[10],arrival[10],burst[10],bt[10];
    int i,j,time;
    int shortest,count=0;
    double avg=0,tt=0,end;

    insertion(nprocesses);

    for(int i=0;i<nprocesses;i++)
    {
        burst[i] = p[i].bursttime;
    }
    for(int i=0;i<nprocesses;i++)
    {
        arrival[i] = p[i].arrivaltime;
    }
    for(i=0; i<nprocesses; i++)
        bt[i]=burst[i];

    burst[9]=1000;
    for(time=0; count!=nprocesses; time++)
    {
        shortest=9;
        for(i=0; i<nprocesses; i++)
        {
            if(arrival[i]<=time && burst[i]<burst[shortest] && burst[i]>0 ){
                shortest=i;
                }
        }
        p[shortest].start.push(time);
        burst[shortest]--;
        if(burst[shortest]==0)
        {
            count++;
            end=time+1;
            finish[shortest] = end;
            waiting[shortest] = end - arrival[shortest] - bt[shortest];
            turnaround[shortest] = end - arrival[shortest];
        }
        p[shortest].finishing.push(time+1);
    }
    for(int i=0;i<nprocesses;i++)
    {
        p[i].finishtime = finish[i];
        p[i].waittime = waiting[i];
        p[i].turnAtime = turnaround[i];
    }

    total_wait = 0;
    total_turnAround = 0;
    for(i=0; i<nprocesses;i++)
    {
        total_wait = total_wait + p[i].waittime;
        total_turnAround = total_turnAround + p[i].turnAtime;
    }

    avg_waittime= (float)total_wait /(float)nprocesses;
    avg_turnAtime=(float)total_turnAround / (float)nprocesses;


    int k=20; 
    char trace[nprocesses][k];
    printf("\n");
    cout<<"SRT   ";
        for(int j = 0 ; j<k+1 ; j++){
            printf("%d ",j%10);
    	}
        cout<<"\n------------------------------------------------\n";
    for(int i=0;i<nprocesses;i++){
            cout <<p[i].name <<"     "<<"|";

                for(int j=0;j<k;j++){
                if(j<p[i].arrivaltime)
                    printf(" |");
            }
            while(p[i].arrivaltime<p[i].start.front()){
                    printf(".|");
                    p[i].arrivaltime++;
            }

            while(!p[i].start.empty()){
 int startTime = p[i].start.front();
 int endTime = p[i].finishing.front();
 p[i].finishing.pop();
 p[i].start.pop();
    	 while(startTime<endTime){
                printf("*|");
            startTime++;
    	 }
if(!p[i].start.empty()){
    	 startTime=endTime;
    	 endTime= p[i].start.front();
    	 while(startTime<endTime)
         {
                printf(".|");
             startTime++;
         }
    	}
            }
    for(j=0;j<k+1;j++){
        if(j>p[i].finishtime)
        {
          printf(" |");
        }
    }
    cout<<" ";
    printf("\n");
    }
    cout<<"------------------------------------------------\n";
}

/*===========================================================================================*/

/****           SRT Implementation  ===> stats       ****/ 

void SRTstats ()
{
    int waiting[10],turnaround[10],finish[10],arrival[10],burst[10],bt[10];
    int i,j,time;
    int shortest,count=0;
    double avg=0,tt=0,end;

    insertion(nprocesses);

    for(int i=0;i<nprocesses;i++)
    {
        burst[i] = p[i].bursttime;
    }
    for(int i=0;i<nprocesses;i++)
    {
        arrival[i] = p[i].arrivaltime;
    }
    for(i=0; i<nprocesses; i++)
        bt[i]=burst[i];

    burst[9]=9999;
    for(time=0; count!=nprocesses; time++)
    {
        shortest=9;
        for(i=0; i<nprocesses; i++)
        {
            if(arrival[i]<=time && burst[i]<burst[shortest] && burst[i]>0 ){
                shortest=i;
                }
        }
        p[shortest].start.push(time);
        burst[shortest]--;
        if(burst[shortest]==0)
        {
            count++;
            end=time+1;
            finish[shortest] = end;
            waiting[shortest] = end - arrival[shortest] - bt[shortest];
            turnaround[shortest] = end - arrival[shortest];
        }
        p[shortest].finishing.push(time+1);
    }
    for(int i=0;i<nprocesses;i++)
    {
        p[i].finishtime = finish[i];
        p[i].waittime = waiting[i];
        p[i].turnAtime = turnaround[i];
    }
    total_wait = 0;
    total_turnAround = 0;
    for(i=0; i<nprocesses;i++)
    {
        total_wait = total_wait + p[i].waittime;
        total_turnAround = total_turnAround + p[i].turnAtime;
    }

    avg_waittime= (float)total_wait /(float)nprocesses;
    avg_turnAtime=(float)total_turnAround / (float)nprocesses;

    printf("\nSRT");
    printing();
    
}


/*===========================================================================================*/
/****           HRRN              ****/

void insertHRRN(int nprocesses){
    int i;
    int x;
    for(i=0;i<nprocesses;i++){
       std:: getline(cin,pr);
        l=pr.length();
        char str[l+1];
		strcpy(str,pr.c_str());
        char *tok=strtok(str,",");
        int count=0;
        while(tok!=NULL)
        {
            count++;
            switch (count)
            {
                case 1:
                {
                    strcpy(temp,tok);
                    letter[i]=temp[0];
		            break;
                }
		        case 2:
		        {
		            char arrival[10];
		            strcpy(arrival,tok);
		            arrive[i]= stoi(arrival);
		            break;
		        }
                case 3:
		        {
		           char burst[10];
		            strcpy(burst,tok);
		            serv[i]=stoi(burst);
		            break;
		        }

            }
            tok=strtok(NULL,",");	
        }
        p[i].pid = i+1;
        
    }
    for(i=0;i<nprocesses;i++){
         p[i].name = letter[i];
        p[i].arrivaltime = arrive[i];
        p[i].bursttime = serv[i];
 	    p[i].rr=0;
        p[i].waittime=-p[i].arrivaltime;
    }
}


/****           HRRN Implementation ===> trace        ****/ 


void HRRNtrace(){


    insertHRRN(nprocesses);
    sort(p,p+nprocesses,bursttimeSort);
    sort(p,p+nprocesses,arrivetimeSort);
    int finish_time=0,i;
    int j,totalService[6];
    int turnaround=0;
    float norm=0;
    for(i=0;i<nprocesses;i++){
        j=i;
        while(p[j].arrivaltime<=finish_time&&j!=nprocesses){
            j++;
        }
        for(int q = i;q<j;q++){
            p[q].waittime=finish_time-p[q].arrivaltime;
            p[q].rr=(float)(p[q].waittime+p[q].bursttime)/(float)p[q].bursttime;
        }
       sort(p+i,p+j,rrtimeSort);
        totalService[i]=finish_time;
        finish_time+=p[i].bursttime;

    }
    totalService[i] = finish_time;
    float avgwt=0;
    float avgtat=0; 

    for(i=0;i<nprocesses;i++)
    {
        p[i].finishtime = totalService[i+1];
        p[i].turnAtime = totalService[i]-p[i].arrivaltime+p[i].bursttime ;
        p[i].NTAT = ((1.0)*(totalService[i]-p[i].arrivaltime+p[i].bursttime))/(1.0*p[i].bursttime);
    }

    sort(p,p+nprocesses,nameSort);
    int k=20;
    int x;
    char trace[nprocesses][k];

    cout<<"\n";
    cout<<"HRRN  ";
    for(int j = 0 ; j<k+1; j++){
            printf("%d ",j%10);
    	}
    cout<<"\n------------------------------------------------\n";
    
    int temp;
    temp=totalService[4];
	totalService[4]=totalService[5];
	totalService[5]=temp;
    
    for(i=0;i<nprocesses;i++){
    	cout <<p[i].name <<"     |"; 
    	for(int j=0;j<k;j++){
    	 trace[i][j]={' '};
    	     	if(j>=p[i].arrivaltime && j<p[i].finishtime){

    		trace[i][j]={'.'};
    		}
    		if(j>= (p[i].arrivaltime + p[i].waittime) && j<p[i].finishtime){
    		trace[i][j]={'*'};
    		}
   	 cout<<trace[i][j];
    	 cout<<"|";
    	}
        cout<<" ";
        cout<<"\n";
    }
        	cout<<"------------------------------------------------\n";
}

/*===========================================================================================*/

/****           HRRN Implementation  ===> stats       ****/ 


void HRRNstats(){

    insertHRRN(nprocesses);
    sort(p,p+nprocesses,bursttimeSort);
    sort(p,p+nprocesses,arrivetimeSort);
    int finish_time=0,i;
    int j,totalService[6];
    int turnaround=0;
    float norm=0;
    for(i=0;i<nprocesses;i++){
        j=i;
        while(p[j].arrivaltime<=finish_time&&j!=nprocesses){
            j++;
        }
        for(int q = i;q<j;q++){
            p[q].waittime=finish_time-p[q].arrivaltime;
            p[q].rr=(float)(p[q].waittime+p[q].bursttime)/(float)p[q].bursttime;
        }
       sort(p+i,p+j,rrtimeSort);
        totalService[i]=finish_time;
        finish_time+=p[i].bursttime;

    }
    totalService[i] = finish_time;
    float avgwt=0;
    float avgtat=0; 

    for(i=0;i<nprocesses;i++)
    {
        p[i].finishtime = totalService[i+1];
        p[i].turnAtime = totalService[i]-p[i].arrivaltime+p[i].bursttime ;
        p[i].NTAT = ((1.0)*(totalService[i]-p[i].arrivaltime+p[i].bursttime))/(1.0*p[i].bursttime);
    }

    sort(p,p+nprocesses,nameSort);
    total_turnAround = 0;
    for(int i=0;i<nprocesses;i++)
    {
        total_turnAround = total_turnAround + p[i].turnAtime;
    }
    printf("HRRN");
    printing();

    
}


/*===========================================================================================*/

void tracemenu ()
{
    switch (pro)
    {
        case 1:
            FCFStrace();
        break;
        case 2:
                        {
                int h = algorithm.length();
                char str2[h+1];
                strcpy(str2,algorithm.c_str());
                char *token = strtok(str2,"-");
                while(token!=NULL)
                {
                    char q[3];
                    strcpy(q,token);
                    quantum = stoi(q);
                    token=strtok(NULL,"-");
                }
                c = quantum;
                RRtrace();
            }
        break;
        case 3:
            SPNtrace();
        break;
       
        case 4:
           SRTtrace();
        break;
        
        case 5:
            HRRNtrace();
        break;
    }

}


void statsmenu ()
{   
    switch (pro)
    {
        case 1:
            FCFSstats();
        break;
        case 2:
            {
                int h = algorithm.length();
                char str2[h+1];
                strcpy(str2,algorithm.c_str());
                char *token = strtok(str2,"-");
                while(token!=NULL)
                {
                    char q[3];
                    strcpy(q,token);
                    quantum = stoi(q);
                    token=strtok(NULL,"-");
                }
                c = quantum;
                RRstats();
            }
        break;
        case 3:
            SPNstats();
        break;
        case 4:
           SRTstats();
        break;
        case 5:
         HRRNstats();
        break;
    }
}



void mainmenu(string mode)
{
    if (mode =="trace")
    {
        tracemenu();
    }
    if (mode=="stats")
    {
        statsmenu();
    }
}

/*===========================================================================================*/

int main(void)
{    
    string state;
    std::	getline(cin,state);
    std::	getline(cin,algo);
    std::	getline(cin,k);
    std::	getline(cin,n);
    mode = state;
    algorithm = algo;
    pro= stoi(algo);
	nprocesses = stoi(n);
    timer= stoi(k);
    mainmenu(mode);
    
}
