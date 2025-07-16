// -------------------  Non‑pre‑emptive SJF WITH ARRIVAL  -------------------
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <climits>
#include <cstdio>

using namespace std;

struct Process {
    int pid;                // Process ID  (1‑based)
    int arrival;            // Arrival time
    int burst;              // CPU burst time

    /* filled by scheduler */
    int start       = 0;
    int completion  = 0;
    int waiting     = 0;
    int turnaround  = 0;
    bool done       = false;
};

    bool compareByCompletion(const Process&a, const Process&b){
        return a.completion < b.completion;
    }

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    freopen("5(Non-preemptive with arrival).txt","r",stdin);

    int n;
    if (!(cin >> n)) return 0;          // read number of processes

    vector<Process> p(n);
    for (int i = 0; i < n; ++i) {
        p[i].pid = i + 1;
        cin >> p[i].arrival >> p[i].burst;
    }

    /* ----------------------- SJF core loop ----------------------- */
    int finished = 0, now = 0;
    long long totWait = 0, totTurn = 0;

    while (finished < n) { //unless finished all the process

        /* pick shortest job among arrived ones */
        int idx = -1, bestBurst = INT_MAX;
        for (int i = 0; i < n; ++i) {   //Go through every process one by one.
            if (!p[i].done && p[i].arrival <= now) {  // skip any process we already finished &&  skip any process that has not arrived yet
                if (p[i].burst < bestBurst ||     //finding process which has lowest burst or
                   (p[i].burst == bestBurst && p[i].arrival < p[idx].arrival)) //If two processes have the same burst time, prefer the one that arrived earlier
                {
                    bestBurst = p[i].burst;
                    idx       = i;
                }
            }
        }

        /* if none available, jump clock to next arrival */
        if (idx == -1) {
            int nextArr = INT_MAX;
            for (int i = 0; i < n; ++i){
                if (!p[i].done && p[i].arrival < nextArr){
                    nextArr = p[i].arrival;
                }
            }
            now = nextArr;
            continue;
        }

        /* run chosen process to completion */
        p[idx].start      = now;
        now              += p[idx].burst;
        p[idx].completion = now;
        p[idx].turnaround = p[idx].completion - p[idx].arrival;
        p[idx].waiting    = p[idx].turnaround - p[idx].burst;
        p[idx].done       = true;

        totWait += p[idx].waiting;
        totTurn += p[idx].turnaround;
        ++finished;
    }

    stable_sort(p.begin(),p.end(),compareByCompletion);

    /* ------------------------- output --------------------------- */
    const int W = 12;
    cout << left << setw(W) << "PID"
         << setw(W) << "Arrival"
         << setw(W) << "Burst"
         << setw(W) << "Start"
         << setw(W) << "Completion"
         << setw(W) << "Turnaround"
         << setw(W) << "Waiting" << '\n';

    for (const auto& pr : p) {
        cout << setw(W) << pr.pid
             << setw(W) << pr.arrival
             << setw(W) << pr.burst
             << setw(W) << pr.start
             << setw(W) << pr.completion
             << setw(W) << pr.turnaround
             << setw(W) << pr.waiting << '\n';
    }

    cout << "\nAverage turnaround time : "
         << fixed << setprecision(3) << (double)totTurn / n << '\n'
         << "Average waiting time    : "
         << fixed << setprecision(3) << (double)totWait / n  << '\n';
    return 0;
}