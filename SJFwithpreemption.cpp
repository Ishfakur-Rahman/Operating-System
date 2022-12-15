#include<bits/stdc++.h>

using namespace std;

typedef struct process{
    int arrival_time, burst_time, waiting_time, turn_around_time, completion_time, required_burst_time;
    string process_name;
}info;

int average_waiting_time, average_tat_time, total_wt=0, total_TAT=0;
info prcs[6];

void get_input(){

    for(int i=0;i<6;i++){
        cin>>prcs[i].process_name>>prcs[i].arrival_time>>prcs[i].burst_time;
        prcs[i].required_burst_time=prcs[i].burst_time;
    }
    return;
}

void give_output(){
    for(int i=0;i<6;i++){
        prcs[i].turn_around_time=prcs[i].completion_time-prcs[i].arrival_time;
        prcs[i].waiting_time=prcs[i].turn_around_time-prcs[i].required_burst_time;
        total_wt+=prcs[i].waiting_time;
        total_TAT+=prcs[i].turn_around_time;
        cout<<prcs[i].process_name<<" "<<prcs[i].arrival_time<<" "<<prcs[i].required_burst_time<<" "<<prcs[i].completion_time;
        cout<<" "<<prcs[i].waiting_time<<" "<<prcs[i].turn_around_time<<endl;
    }
    average_waiting_time=total_wt/6;
    average_tat_time=total_TAT/6;
    cout<<endl<<average_waiting_time<<" "<<average_tat_time;


}

int partitions_at(int start, int ends){
    int     pivot = prcs[ends].arrival_time,    i=start-1;
    info  temp;


    for(int j=start;j<=ends-1;j++){
        if(prcs[j].arrival_time<=pivot){
            i++;
            temp=prcs[i];
            prcs[i]=prcs[j];
            prcs[j]=temp;
        }

    }

    temp=prcs[i+1];
    prcs[i+1]=prcs[ends];
    prcs[ends]=temp;
    return i+1;

}

void quickSort_at(int start, int ends){

    if(start<ends){

        int mid = partitions_at(start,ends);
        quickSort_at(start,mid-1);
        quickSort_at(mid+1,ends);

    }

    return;
}


int partitions_bt(int start, int ends){
    int     pivot = prcs[ends].burst_time,    i=start-1;
    info  temp;


    for(int j=start;j<=ends-1;j++){
        if(prcs[j].burst_time<=pivot){
            i++;
            temp=prcs[i];
            prcs[i]=prcs[j];
            prcs[j]=temp;
        }

    }

    temp=prcs[i+1];
    prcs[i+1]=prcs[ends];
    prcs[ends]=temp;
    return i+1;

}

void quickSort_bt(int start, int ends){

    if(start<ends){

        int mid = partitions_bt(start,ends);
        quickSort_bt(start,mid-1);
        quickSort_bt(mid+1,ends);

    }

    return;
}

void sjf_preemption(){
    quickSort_at(0,6);
    int counts=0,cputime=0,i;
    while(counts<6){
        for(i=0;i<6;i++){
            if(prcs[i].arrival_time>cputime){
                break;
            }
        }
        quickSort_bt(0,6);

        if(i>0){
            for(i=0;i<6;i++){
                if(prcs[i].burst_time!=0){
                    break;
                }
            }
            if(prcs[i].arrival_time>cputime){
                cputime=prcs[i].arrival_time;
            }
            prcs[i].completion_time=cputime+1;
            prcs[i].burst_time-=1;
        }
        cputime+=1;
        counts=0;
        for(i=0;i<6;i++){
            if(prcs[i].burst_time==0){
                counts++;
            }
        }
    }


}

main(){
    get_input();

    sjf_preemption();

    give_output();

return 0;
}
