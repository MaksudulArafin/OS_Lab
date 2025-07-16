// -------------------  Pre‑emptive SRTF WITH ARRIVAL  -------------------
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
    int burst;              // Original CPU burst

    /* filled by scheduler */
    int remaining   = 0;    // Remaining burst (changes over time)
    int completion  = 0;    // Finish time
    int waiting     = 0;
    int turnaround  = 0;
    bool done       = false;
};

bool compareByCompletion(const Process& a, const Process& b) {
    return a.completion < b.completion;
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    /* Optional – redirect from file exactly like the SJF code.
       Change / comment‑out if you prefer stdin directly.            */
    freopen("5(Preemptive).txt", "r", stdin);

    int n;
    if (!(cin >> n)) return 0;          // read number of processes

    vector<Process> p(n);
    for (int i = 0; i < n; ++i) {
        p[i].pid = i + 1;
        cin >> p[i].arrival >> p[i].burst;
        p[i].remaining = p[i].burst;    // initialise remaining burst
    }

    /* ------------------------ SRTF core loop ------------------------ */
    int finished = 0, now = 0;
    long long totWait = 0, totTurn = 0;

    while (finished < n) {

        /* pick job with smallest remaining time among arrived ones */
        int idx = -1, bestRem = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (!p[i].done && p[i].arrival <= now) {
                if (p[i].remaining < bestRem ||
                   (p[i].remaining == bestRem && p[i].arrival < p[idx].arrival))
                {
                    bestRem = p[i].remaining;
                    idx     = i;
                }
            }
        }

        /* if none available, jump clock to next arrival */
        if (idx == -1) {
            int nextArr = INT_MAX;
            for (int i = 0; i < n; ++i)
                if (!p[i].done && p[i].arrival < nextArr)
                    nextArr = p[i].arrival;
            now = nextArr;
            continue;
        }
        

        --p[idx].remaining;
        ++now;

        /* did it finish? */
        if (p[idx].remaining == 0) {
            p[idx].completion = now;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting    = p[idx].turnaround - p[idx].burst;
            p[idx].done       = true;

            totWait += p[idx].waiting;
            totTurn += p[idx].turnaround;
            ++finished;
        }
    }

    stable_sort(p.begin(), p.end(), compareByCompletion);

    /* --------------------------- output ----------------------------- */
    const int W = 12;
    cout << left << setw(W) << "PID"
         << setw(W) << "Arrival"
         << setw(W) << "Burst"
         << setw(W) << "Completion"
         << setw(W) << "Turnaround"
         << setw(W) << "Waiting" << '\n';

    for (const auto& pr : p) {
        cout << setw(W) << pr.pid
             << setw(W) << pr.arrival
             << setw(W) << pr.burst
            
             << setw(W) << pr.completion
             << setw(W) << pr.turnaround
             << setw(W) << pr.waiting << '\n';
    }

    cout << "\nAverage turnaround time : "
         << fixed << setprecision(3) << (double) totTurn / n << '\n'
         << "Average waiting time    : "
         << fixed << setprecision(3) << (double) totWait / n  << '\n';
    return 0;
}
