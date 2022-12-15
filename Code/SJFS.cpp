#include<bits/stdc++.h>

using namespace std;

int process[6],burst_time[6],average_TAT_time,average_waiting_time,TAT,wt=0,total_TAT=0,total_wt=0;
stack<int> waiting_time,Turn_Around_Time;

void get_input(){

     for(int i=1;i<6;i++){
        cin>>process[i]>>burst_time[i];
    }

    return;
}


void give_output(){
    for(int i=5;i>0;i--){
        int wts=waiting_time.top();
        int TATS=Turn_Around_Time.top();
        waiting_time.pop();
        Turn_Around_Time.pop();
        cout<<"process "<<process[i]<<" waiting "<<wts<<" Turn Around Time "<<TATS<<endl;
    }
    cout<<" Average Turn_Around_Time"<<average_TAT_time<<" average Waiting Time "<<average_waiting_time;

return;
}

int partitions(int start, int ends){
    int     pivot = burst_time[ends],    i=start-1,  temp;


    for(int j=start;j<=ends-1;j++){
        if(burst_time[j]<=pivot){
            i++;
            temp=burst_time[i];
            burst_time[i]=burst_time[j];
            burst_time[j]=temp;

            temp=process[i];
            process[i]=process[j];
            process[j]=temp;
        }

    }

    temp=burst_time[i+1];
    burst_time[i+1]=burst_time[ends];
    burst_time[ends]=temp;

    temp=process[i+1];
    process[i+1]=process[ends];
    process[ends]=temp;
    return i+1;

}

void quickSort(int start, int ends){

    if(start<ends){

        int mid = partitions(start,ends);
        quickSort(start,mid-1);
        quickSort(mid+1,ends);

    }

    return;
}
void SJFS(){
    get_input();
    quickSort(1,5);
    for(int i=1;i<6;i++){
        waiting_time.push(wt);

        TAT=wt+burst_time[i];
        Turn_Around_Time.push(TAT);

        total_TAT+=TAT;
        wt=TAT;
        total_wt+=wt;
    }
    average_TAT_time=total_TAT/5;
    average_waiting_time=total_wt/5;

    give_output();
}
main(){
    SJFS();
return 0;
}
