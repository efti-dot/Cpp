#include<iostream>
#include <algorithm>
#include <queue>
#include<iomanip>
#include<climits>
using namespace std;

struct process_struct {
    int pid;
    int at;
    int bt;
    int ct, wt, tat, rt, start_time;
    int bt_remaining;
} ps[100];

bool comparatorAT(struct process_struct a, struct process_struct b) {
    int x = a.at;
    int y = b.at;
    return x < y;
}

bool comparatorPID(struct process_struct a, struct process_struct b) {
    int x = a.pid;
    int y = b.pid;
    return x < y;
}

int main() {
    int n, index;
    int cpu_utilization;
    queue<int> q;
    bool visited[100] = { false }, is_first_process = true;
    int current_time = 0, max_completion_time;
    int completed = 0, tq, total_idle_time = 0, length_cycle;
    cout << "Enter total number of processes: ";
    cin >> n;
    float sum_tat = 0, sum_wt = 0, sum_rt = 0;

    cout << fixed << setprecision(2);

    for (int i = 0; i < n; i++) {
        cout << "\nEnter Process " << i << " Arrival Time: ";
        cin >> ps[i].at;
        ps[i].pid = i;
    }

    for (int i = 0; i < n; i++) {
        cout << "\nEnter Process " << i << " Burst Time: ";
        cin >> ps[i].bt;
        ps[i].bt_remaining = ps[i].bt;
    }

    cout << "\nEnter time quanta: ";
    cin >> tq;

    sort(ps, ps + n, comparatorAT);

    q.push(0);
    visited[0] = true;

    while (completed != n) {
        index = q.front();
        q.pop();

        if (ps[index].bt_remaining == ps[index].bt) {
            ps[index].start_time = max(current_time, ps[index].at);
            total_idle_time += (is_first_process == true) ? 0 : ps[index].start_time - current_time;
            current_time = ps[index].start_time;
            is_first_process = false;
        }

        if (ps[index].bt_remaining - tq > 0) {
            ps[index].bt_remaining -= tq;
            current_time += tq;
        } else {
            current_time += ps[index].bt_remaining;
            ps[index].bt_remaining = 0;
            completed++;

            ps[index].ct = current_time;
            ps[index].tat = ps[index].ct - ps[index].at;
            ps[index].wt = ps[index].tat - ps[index].bt;
            ps[index].rt = ps[index].start_time - ps[index].at;

            sum_tat += ps[index].tat;
            sum_wt += ps[index].wt;
            sum_rt += ps[index].rt;
        }

        for (int i = 1; i < n; i++) {
            if (ps[i].bt_remaining > 0 && ps[i].at <= current_time && visited[i] == false) {
                q.push(i);
                visited[i] = true;
            }
        }

        if (ps[index].bt_remaining > 0)
            q.push(index);

        if (q.empty()) {
            for (int i = 1; i < n; i++) {
                if (ps[i].bt_remaining > 0) {
                    q.push(i);
                    visited[i] = true;
                    break;
                }
            }
        }
    }

    max_completion_time = INT_MIN;

    for (int i = 0; i < n; i++)
        max_completion_time = max(max_completion_time, ps[i].ct);

    length_cycle = max_completion_time - ps[0].at;

    cpu_utilization = (float)(length_cycle - total_idle_time) / length_cycle;

    sort(ps, ps + n, comparatorPID);

    cout << "\nProcess No.\tAT\tCPU Burst Time\tT A T\tW T\n";
    for (int i = 0; i < n; i++)
        cout << i << "\t\t" << ps[i].at << "\t" << ps[i].bt << "\t\t" << ps[i].tat << "\t" << ps[i].wt << endl;
    cout << endl;

    cout << "\nAverage Turn Around time= " << (float)sum_tat / n;
    cout << "\nAverage Waiting Time= " << (float)sum_wt / n;
return 0;
}
