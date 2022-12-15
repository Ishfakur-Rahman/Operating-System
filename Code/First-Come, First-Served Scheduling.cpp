#include<bits/stdc++.h>

using namespace std;

int proccess[6],burst_time[6],average_TAT_time,average_waiting_time,TAT,wt=0,total_TAT=0,total_wt=0;
stack<int> waiting_time,Turn_Around_Time;

void get_input(){

     for(int i=0;i<6;i++){
        cin>>proccess[i]>>burst_time[i];
    }

return;
}
void FCFS(){

    for(int i=0;i<6;i++){
        waiting_time.push(wt);

        TAT=wt+burst_time[i];
        Turn_Around_Time.push(TAT);

        total_TAT+=TAT;
        wt=TAT;
        total_wt+=wt;
    }
    average_TAT_time=total_TAT/6;
    average_waiting_time=total_wt/6;
}

void give_output(){
    for(int i=5;i>=0;i--){
        int wts=waiting_time.top();
        int TATS=Turn_Around_Time.top();
        waiting_time.pop();
        Turn_Around_Time.pop();
        cout<<"proccess "<<proccess[i]<<" waiting "<<wts<<" Turn Around Time "<<TATS<<endl;
    }
    cout<<" Average Turn_Around_Time"<<average_TAT_time<<" average Waiting Time "<<average_waiting_time;

return;
}
main(){
    get_input();
    FCFS();
    give_output();
return 0;
}
