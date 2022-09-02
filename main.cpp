#include<bits/stdc++.h>
using namespace  std;

double wtarr[6] = {100, 100, 100, 100, 100,100};

int cnt=0;

void FCFS()
{
    int n,bt[20],wt[20],tat[20],avwt=0,avtat=0,i,j;
    cout<<"Enter total number of processes(maximum 20):";
    cin>>n;

    cout<<"\nEnter Process Burst Time\n";
    for(i=0; i<n; i++)
    {
        cout<<"P["<<i+1<<"]:";
        cin>>bt[i];
    }

    wt[0]=0;
    for(i=1; i<n; i++)
    {
        wt[i]=0;
        for(j=0; j<i; j++)
            wt[i]+=bt[j];
    }

    cout<<"\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time";


    for(i=0; i<n; i++)
    {
        tat[i]=bt[i]+wt[i];
        avwt+=wt[i];
        avtat+=tat[i];
        cout<<"\nP["<<i+1<<"]"<<"\t\t"<<bt[i]<<"\t\t"<<wt[i]<<"\t\t"<<tat[i];
    }

    avwt/=i;
    avtat/=i;


    wtarr[0] = avwt;


    cout<<"\n\nAverage Waiting Time:"<<avwt;
    cout<<"\nAverage Turnaround Time:"<<avtat;

}
bool compare(const pair<int,int>&i, const pair<int,int>&j){
    if(i.first==j.first && i.second>j.second)
        return j.first<i.first;
    else
        return i.first<j.first;
}
void FCFS_AT()
{    cout<<"\t\t\t\t FCFS for different arrival time"<<endl;
    int n;
    cout<<"Enter number of processes:"<<endl;
    cin>>n;                 //number of processes in schedular
    int AT[n],BT[n];
    cout<<"Enter arrival time and burst time"<<endl;
    for(int i=0;i<n;i++)    //input AT and BT
    {
        cin>>AT[i];
        cin>>BT[i];
    }
    vector< pair<int,int> > vect;  // linking AT and BT using vector pair
    for (int i=0; i<n; i++)
        vect.push_back( make_pair(AT[i],BT[i]) );
    sort(vect.begin(), vect.end(),compare);  //for sorting as per AT
    int CT[n],TAT[n],WT[n];
    for(int i=0;i<n;i++)
    {
        if(i==0)
        {
            CT[0]=vect[0].second;               // vect[0].second represents BT
            TAT[0]=CT[0]-vect[0].first;         // vect[0].first represents AT
            WT[0]=TAT[0]-vect[0].second;
        }
        else
        {
            CT[i]=CT[i-1]+vect[i].second;   //calculating completion time
            TAT[i]=CT[i]-vect[i].first;   //calculating Turn around time
            WT[i]=TAT[i]-vect[i].second;  //caculating Waiting time
        }

        while(WT[i]<0)      //to check negative waiting time(happens when CPU is ideal i.e. no process is available for a arrival time)
        {
            WT[i]=WT[i]+1;
            CT[i]=CT[i]+1;
            TAT[i]=TAT[i]+1;
        }

    }

    cout<<" AT "<<"| BT "<<"| CT "<<"| TAT "<<"| WT"<<endl;
    for(int i=0;i<n;i++)  //To print value of CT,TAT,WT
    {
        cout<<" "<<vect[i].first<<"    "<<vect[i].second<<"    "<<CT[i]<<"    "<<TAT[i]<<"    "<<WT[i]<<endl;
    }
    float sum1=0,sum2=0;
    for(int i=0;i<n;i++) //To find average of TAT,WT
    {
        sum1=sum1+TAT[i];
        sum2=sum2+WT[i];
    }
    wtarr[1]= sum2/n;
    cout<<"Average TAT:"<<sum1/n<<endl;
    cout<<"Average WT:"<<sum2/n;

}
void SJF()
{
    int n,temp,tt=0,min,d,i,j;
    float atat=0,awt=0,stat=0,swt=0;

    cout<<"enter no of process"<<endl;
    cin>>n;
    int a[n],b[n],e[n],tat[n],wt[n];

    for(i=0; i<n; i++)
    {
        cout<<"enter arival time "; //input
        cin>>a[i];
    }
    for(i=0; i<n; i++)
    {
        cout<<"enter brust time "; //input
        cin>>b[i];
    }
    for(i=0; i<n; i++)
    {
        for(j=i+1; j<n; j++)
        {
            if(b[i]>b[j])
            {
                temp=a[i];
                a[i]=a[j];
                a[j]=temp;

                temp=b[i];
                b[i]=b[j];
                b[j]=temp;
            }
        }
    }
    min=a[0];
    for(i=0; i<n; i++)
    {
        if(min>a[i])
        {
            min=a[i];
            d=i;
        }
    }
    tt=min;
    e[d]=tt+b[d];
    tt=e[d];

    for(i=0; i<n; i++)
    {
        if(a[i]!=min)
        {
            e[i]=b[i]+tt;
            tt=e[i];
        }
    }
    for(i=0; i<n; i++)
    {

        tat[i]=e[i]-a[i];
        stat=stat+tat[i];
        wt[i]=tat[i]-b[i];
        swt=swt+wt[i];
    }
    atat=stat/n;
    awt=swt/n;
    cout<<"Process Arrival-time(s) Burst-time(s) Waiting-time(s) Turnaround-time(s)\n";

    for(i=0; i<n; i++)
    {
        cout<<"P"<<i+1<<" "<<a[i]<<" "<<b[i]<<" "<<wt[i]<<" "<<tat[i]<<endl;
    }

    //3rd change - store the average time of SJF in the array at second position
    wtarr[2] = awt;

    cout<<"awt="<<awt<<" atat="<<atat; //average waiting time and turn around time

}
void SRT()
{
    int a[10],b[10],x[10];
    int waiting[10],turnaround[10],completion[10];
    int i,j,smallest,count=0,time,n;
    double avg=0,tt=0,end;

    cout<<"\nEnter the number of Processes: ";  //input
    cin>>n;
    for(i=0; i<n; i++)
    {
        cout<<"\nEnter arrival time of process: ";  //input
        cin>>a[i];
    }
    for(i=0; i<n; i++)
    {
        cout<<"\nEnter burst time of process: ";  //input
        cin>>b[i];
    }
    for(i=0; i<n; i++)
        x[i]=b[i];

    b[9]=9999;
    for(time=0; count!=n; time++)
    {
        smallest=9;
        for(i=0; i<n; i++)
        {
            if(a[i]<=time && b[i]<b[smallest] && b[i]>0 )
                smallest=i;
        }
        b[smallest]--;

        if(b[smallest]==0)
        {
            count++;
            end=time+1;
            completion[smallest] = end;
            waiting[smallest] = end - a[smallest] - x[smallest];
            turnaround[smallest] = end - a[smallest];
        }
    }
    cout<<"Process"<<"\t"<< "burst-time"<<"\t"<<"arrival-time" <<"\t"<<"waiting-time" <<"\t"<<"turnaround-time"<< "\t"<<"completion-time"<<endl;
    for(i=0; i<n; i++)
    {
        cout<<"p"<<i+1<<"\t\t"<<x[i]<<"\t\t"<<a[i]<<"\t\t"<<waiting[i]<<"\t\t"<<turnaround[i]<<"\t\t"<<completion[i]<<endl;
        avg = avg + waiting[i];
        tt = tt + turnaround[i];
    }
    wtarr[3] = avg;
    cout<<"\n\nAverage waiting time ="<<avg/n;
    cout<<"  Average Turnaround time ="<<tt/n<<endl;
}
void Prty()
{
    int a[10],b[10],x[10];
    int waiting[10],turnaround[10],completion[10],p[10];
    int i,j,smallest,count=0,time,n;
    double avg=0,tt=0,end;

    cout<<"\nEnter the number of Processes: ";
    cin>>n;
    for(i=0;i<n;i++)
    {
        cout<<"\nEnter arrival time of process: ";
        cin>>a[i];
    }
    for(i=0;i<n;i++)
    {
        cout<<"\nEnter burst time of process: ";
        cin>>b[i];
    }
    for(i=0;i<n;i++)
    {
        cout<<"\nEnter priority of process: ";
        cin>>p[i];
    }
    for(i=0; i<n; i++)
        x[i]=b[i];

    p[9]=-1;
    for(time=0; count!=n; time++)
    {
        smallest=9;
        for(i=0; i<n; i++)
        {
            if(a[i]<=time && p[i]>p[smallest] && b[i]>0 )
                smallest=i;
        }
        b[smallest]--;

        if(b[smallest]==0)
        {
            count++;
            end=time+1;
            completion[smallest] = end;
            waiting[smallest] = end - a[smallest] - x[smallest];
            turnaround[smallest] = end - a[smallest];
        }
    }
    cout<<"Process"<<"\t"<< "burst-time"<<"\t"<<"arrival-time" <<"\t"<<"waiting-time" <<"\t"<<"turnaround-time"<< "\t"<<"completion-time"<<"\t"<<"Priority"<<endl;
    for(i=0; i<n; i++)
    {
        cout<<"p"<<i+1<<"\t\t"<<x[i]<<"\t\t"<<a[i]<<"\t\t"<<waiting[i]<<"\t\t"<<turnaround[i]<<"\t\t"<<completion[i]<<"\t\t"<<p[i]<<endl;
        avg = avg + waiting[i];
        tt = tt + turnaround[i];
    }
    wtarr[4] = avg;
    cout<<"\n\nAverage waiting time ="<<avg/n;
    cout<<"  Average Turnaround time ="<<tt/n<<endl;
}
void robin(){
    int i,n,time,remain,temps=0,time_quantum;

    int wt=0,tat=0;

    cout<<"Enter the total number of process = ";
    cin>>n;
    cout<<endl;

    remain=n;
    // assigning the number of process to remain variable

    int at[n];
    int bt[n];
    int rt[n];


    cout<<"Enter the Arrival time, Burst time for All the processes"<<endl;
    for(i=0;i<n;i++)
    {
        int p=1;
        cout<<"Arrival time for process "<<i+1<<"-> ";
        cin>>at[i];
        cout<<endl;
        cout<<"Burst time for process "<<i+1<<"-> ";
        cin>>bt[i];
        cout<<endl;
        rt[i]=bt[i];

    }

    cout<<"Enter the value of time QUANTUM: ";
    cin>>time_quantum;
    cout<<endl;

    cout<<"\n\nProcess\t:Turnaround Time:Waiting Time\n\n";
    for(time=0,i=0;remain!=0;)
    {
        if(rt[i]<=time_quantum && rt[i]>0)
        {
            time += rt[i];

            rt[i]=0;
            temps=1;
        }

        else if(rt[i]>0)
        {
            rt[i] -= time_quantum;

            time += time_quantum;

        }

        if(rt[i]==0 && temps==1)
        {
            remain--;
            //Desplaying the result of wating, turn around time:
            printf("Process{%d}\t:\t%d\t:\t%d\n",i+1,time-at[i],time-at[i]-bt[i]);
            cout<<endl;

            wt += time-at[i]-bt[i];
            tat += time-at[i];
            temps=0;
        }

        if(i == n-1)
            i=0;
        else if(at[i+1] <= time)
            i++;
        else
            i=0;
    }
    wtarr[5] = wt;

    cout<<"Average waiting time "<<wt*1.0/n<<endl;
    cout<<"Average turn around time "<<tat*1.0/n<<endl;;


}
void bestAlgo()
{
    // get the smallest time from the global array
    double smallestTime = wtarr[0];
    // get the index position of the smallest time in the array
    int idx = 0;

    for(int i=1; i<cnt; i++)
    {
        if(wtarr[i]<smallestTime)
        {
            smallestTime = wtarr[i];
            idx = i;
        }
    }

    // display the best algorithm that has the smallest time.
    if(idx == 0)
    {
        cout<<"\t The best algorithm is FCFS";
    }
    else if(idx == 1)
    {
        cout<<"\t The best algorithm is FCFS with Artival Time ";
    }
    else if(idx == 2)
    {
        cout<<"\t The best algorithm is SJF";
    }
    else if(idx == 3)
    {
        cout<<"\t The best algorithm is SRT";
    }
    else if(idx == 4)
    {
        cout<<"\t The best algorithm is Priority";
    }
    else if(idx==5)
    {
        cout<<"\t The best algorithm is Round Robin";
    }
}
int choose()
{
    cnt++;
    int choice;
    cout<<"\n\t******************** Choose Your Algorithm ******************\n";
    cout<<"\n";
    cout<<"1. First Come First Serve\n2. First Come First Search(With Arrival Time)\n3. Shortest Job First\n4. Shortest Remaining Time\n5. Priority\n6. Round Robin\n7. Comparison\n"<<endl;
    cout<<"Your Choice-> (Enter -1 to Exit)";
    cin>>choice;
    cout<<endl;
    switch(choice)
    {


        case -1:
            cout<<"Bye"<<endl;
            break;

        case 1:
            cout<<"\t__________________You choose-First Come First Serve__________________\n";
            cout<<endl;
            cout<<endl;
            FCFS();
            break;

        case 2:
            cout<<"\tYou choose-First Come First Search(With Arrival Time)\n";
            cout<<endl;
            cout<<endl;
            FCFS_AT();
            break;

        case 3:
            cout<<"\tYou choose-Shortest Job First\n";
            cout<<endl;
            cout<<endl;
            SJF();
            break;

        case 4:
            cout<<"\tYou choose-Shortest Remaining Time\n";
            cout<<endl;
            cout<<endl;
            SRT();
            break;

        case 5:
            cout<<"\tYou choose-Priority\n";
            cout<<endl;
            cout<<endl;
            Prty();
            break;
        case 6:
            cout<<"\tYou choose-Round Robin\n";
            cout<<endl;
            cout<<endl;
            robin();
            break;

        case 7:
            bestAlgo();
            cout<<endl;
            cout<<endl;
            break;

        default:
            cout<<"Invalid Choice!! Choose Again->\n";
            cout<<endl;
            cout<<endl;
            break;
    }

    return choice;

}


int main()
{
    int choice= 0;

    while(choice != -1)
    {
        choice=choose();
    }

    return 0;
}
