#include<bits/stdc++.h>

using namespace std;

typedef struct process{
    int arrival_time, burst_time, waiting_time, turn_around_time, completion_time, required_burst_time;
    string process_name;
}info;

int average_waiting_time, average_tat_time, total_wt=0, total_TAT=0, time_quantum;
info prcs[6];

void get_input(){

    cin>>time_quantum;
    for(int i=0;i<6;i++){
        cin>>prcs[i].process_name>>prcs[i].burst_time;
        prcs[i].required_burst_time=prcs[i].burst_time;
    }
    return;
}

void give_output(){
    for(int i=0;i<6;i++){
        prcs[i].turn_around_time=prcs[i].required_burst_time+prcs[i].waiting_time;
        total_wt+=prcs[i].waiting_time;
        total_TAT+=prcs[i].turn_around_time;
        cout<<prcs[i].process_name;
        cout<<" burst time: "<<prcs[i].required_burst_time<<" completion time: "<<prcs[i].completion_time;
        cout<<" waiting time: "<<prcs[i].waiting_time<<" turnaround time: "<<prcs[i].turn_around_time<<endl;
    }
    average_waiting_time=total_wt/6;
    average_tat_time=total_TAT/6;
    cout<<endl<<average_waiting_time<<" "<<average_tat_time;


}

void roundrobin(){
    int counts=0,cputime=0,i,j=0;
    while(counts<6){

        for(i=j;i<6;i++){
            if(prcs[i].burst_time!=0){
                break;
            }
        }
        if(prcs[i].burst_time>=time_quantum){
            cputime+=time_quantum;
            prcs[i].waiting_time=cputime-prcs[i].burst_time;
            prcs[i].burst_time-=time_quantum;
            prcs[i].completion_time=cputime;
            j++;
        }
        else{
            cputime+=prcs[i].burst_time;
            prcs[i].waiting_time=cputime-prcs[i].burst_time;
            prcs[i].burst_time=0;
            prcs[i].completion_time=cputime;

            j++;
        }
        if(j==5){
            j=0;
        }
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

    roundrobin();

    give_output();

return 0;
}


