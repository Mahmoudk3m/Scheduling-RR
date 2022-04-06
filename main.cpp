#include<bits/stdc++.h>
//ACPC2022
//TposersFTW
#define endl "\n"
#define ll long long
#define ull unsigned long long
#define pb push_back
#define lcm(x,y) x*y/__gcd(x,y)
#define summ(n) (n*(n+1))/2
using namespace std;

struct process{
    int pid;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int endTime;
};
bool cmp1(process p1,process p2){
    return(p1.burstTime<p2.burstTime);
}
bool cmp2(process p1,process p2){
    return(p1.pid<p2.pid);
}
int main(){
    struct process p[100];
    queue<int> q;
    int remainingTime[100];
    cout<<"Enter Quantum Time: ";
    int qt;cin>>qt;
    cout<<"Enter Number of Processes: ";
    int n,ct=0,av=0;cin>>n;
    for(int i=0;i<n;i++){
        cout<<endl<<"Enter the arrival time of process #"<<i+1<<": ";
        cin>>p[i].arrivalTime;
        cout<<endl<<"Enter the burst time of process #"<<i+1<<": ";
        cin>>p[i].burstTime;
        remainingTime[i]=p[i].burstTime;
        p[i].pid=i+1;
    }
    q.push(0);
    int completed=0;
    int timer=0;
    int mark[100];
    memset(mark,0,sizeof(mark));
    mark[0] = 1;
    int id;
    while(completed!=n){
        id=q.front();
        q.pop();
        if(remainingTime[id]-qt>0){
            remainingTime[id]-=qt;
            timer+=qt;
        }
        else{
            timer+=remainingTime[id];
            remainingTime[id]=0;
            completed++;
            p[id].endTime=timer;
            p[id].waitingTime=(p[id].endTime-p[id].arrivalTime)-p[id].burstTime;
            av+=p[id].waitingTime;
        }
        for(int i = 1; i < n; i++) {
            if(remainingTime[i] > 0 && p[i].arrivalTime <= timer && mark[i] == 0) {
                q.push(i);
                mark[i] = 1;
            }
        }
        if(remainingTime[id] > 0) {
            q.push(id);
        }
        if(q.empty()) {
            for(int i = 1; i < n; i++) {
                if(remainingTime[i] > 0) {
                    q.push(i);
                    mark[i] = 1;
                    break;
                }
            }
        }
    }
    for(int i=0;i<n;i++){
        cout<<endl<<"Process #"<<p[i].pid<<" "<<"Arrival Time: "<<p[i].arrivalTime<<" "<<"Burst Time: "<<p[i].burstTime<<" "<<"Waiting Time: "<<p[i].waitingTime;
    }
    cout<<endl<<"Average Time: "<<av/n;

    return 0;
}
