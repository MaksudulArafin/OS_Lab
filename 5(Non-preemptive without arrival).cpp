// To write a C program for implementation of SJF(Non-preemptive) scheduling algorithm

#include<iostream>  //std::cin, std::cout
#include<cstdio>   // std::freopen
#include<vector>    //std::vector
#include <algorithm>    //std::stable_sort
#include <iomanip>      // for std::setw  std::setprecision std::fixed


using namespace std;

struct Process{
    int pid;            // process ID (P1, P2, …)
    //int arrival;        // arrival time
    int burst;          // CPU burst time
    int completion = 0;     // completion time
    int waiting = 0;    // waiting time = start − arrival
    int turnaround = 0; // turnaround time = finish − arrival
};

bool compareByArrival(const Process& a, const Process& b){
        return a.burst < b.burst;
}

int main(){

    freopen("5.txt", "r", stdin); // reading value from text file "4.txt"

    int n; // Number of processes
    cin >> n;

    vector<Process> p(n);

    for (int i = 0; i < n; ++i) {
        p[i].pid = i + 1;
        cin >> p[i].burst;
    }

    stable_sort(p.begin(), p.end(), compareByArrival);



    int temp = 0;
    auto totalturnaround = 0;
    auto totalwaiting = 0;
    for (int i = 0; i < p.size(); ++i) {
        
        p[i].completion = temp + p[i].burst;
        p[i].turnaround = p[i].completion;
        p[i].waiting = p[i].turnaround - p[i].burst;
        temp =  p[i].completion ;

        //find out average waiting time and turnaround time
        totalturnaround += p[i].turnaround;
        totalwaiting += p[i].waiting;
    }


    //std::setw is a manipulator from the <iomanip> header in C++ that sets the width of the next output field on a stream like std::cout
      const int w = 12;                      // column width
    cout << left << setw(w) << "PID"
         << setw(w) << "Burst" 
         << setw(w) << "Completion"
         << setw(w) << "Turnaround"
         << setw(w) << "Waiting" <<'\n';

    


    for (int i = 0; i < p.size(); ++i) {
        cout << setw(w) << p[i].pid
            << setw(w) << p[i].burst
            << setw(w) << p[i].completion
            << setw(w) << p[i].turnaround
            << setw(w) << p[i].waiting << '\n';
    }

    cout << "\n" << "Average turnaround time : "  << fixed << setprecision(3) << (totalturnaround)*1.00/n << "\n"
        << "Average waiting time : " << fixed << setprecision(3) << (totalwaiting)*1.00/n << "\n";

            /*std::fixed:
            Forces the number to be printed in fixed-point notation (i.e., not scientific/exponential form).

            std::setprecision(3):
            When used with std::fixed, this sets the number of digits after the decimal point to 3.*/
    return 0;
}