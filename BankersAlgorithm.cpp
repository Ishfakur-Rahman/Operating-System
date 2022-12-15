#include<bits/stdc++.h>

using namespace std;

typedef struct resource_need{
    int need, allocation, total_need;
    string resource_name;

}rcs_need_info;

typedef struct process{
    string process_name;
    bool completed=false;
    rcs_need_info rcs_n_i[3];
}prcs_info;

typedef struct resource{
    int currently_available, total_available;
    string resource_name;
}rcs_info;

prcs_info prcs[5];
rcs_info rcs[3];
int sum_of_allocated_resource_instances[3];
vector<string> safe_sequence;

void get_input(){
    for(int i=0;i<5;i++){
        cin>>prcs[i].process_name;
        for(int j=0;j<3;j++){
            cin>>prcs[i].rcs_n_i[j].resource_name>>prcs[i].rcs_n_i[j].allocation>>prcs[i].rcs_n_i[j].need>>prcs[i].rcs_n_i[j].total_need;
        }
    }
    for(int i=0;i<3;i++){
        cin>>rcs[i].resource_name>>rcs[i].total_available;
    }
}

void give_output(){
    cout<<"\nSafe squence<";
    for(int i=0;i<5;i++){
        if(i<4){
            cout<<safe_sequence[i]<<",";
        }
        else
            cout<<safe_sequence[i]<<">";
    }
}

void calculation(){
    for(int i=0;i<3;i++){
        sum_of_allocated_resource_instances[i]=0;
    }
    for(int i=0;i<5;i++){
        for(int j=0;j<3;j++){
            sum_of_allocated_resource_instances[j]+=prcs[i].rcs_n_i[j].allocation;
        }
    }

    for(int i=0;i<5;i++){
        for(int j=0;j<3;j++){
            rcs[j].currently_available=rcs[j].total_available-sum_of_allocated_resource_instances[j];
            prcs[i].rcs_n_i[j].need=prcs[i].rcs_n_i[j].total_need-prcs[i].rcs_n_i[j].allocation;
        }
    }
}


void bankers_algorithm(){
    calculation();
    int counts=0,process_count=0,round=0;
    while(process_count<5){
        for(int i=round;i<5;i++){
            for(int j=0;j<3;j++){
                if(prcs[i].completed==false){
                    if(prcs[i].rcs_n_i[j].need<=prcs[i].rcs_n_i[j].total_need && prcs[i].rcs_n_i[j].need<=rcs[j].currently_available){
                        counts++;
                        if(counts==3){
                            safe_sequence.push_back(prcs[i].process_name);
                            cout<<"prc"<<prcs[i].process_name;
                            rcs[j].currently_available+=prcs[i].rcs_n_i[j].allocation;
                            prcs[i].rcs_n_i[j].allocation=0;
                            prcs[i].rcs_n_i[j].need=0;
                            counts=0;
                            process_count++;
                            prcs[i].completed=true;
                        }
                    }
                }
            }
          round++;
        }
        if(round==5){
            round=0;
        }
    }

}

int main(){
    get_input();

    bankers_algorithm();

    give_output();
}
