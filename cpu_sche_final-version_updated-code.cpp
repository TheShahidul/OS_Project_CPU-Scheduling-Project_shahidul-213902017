#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct process {
    char name[5];
    int bt, at, prt, wt, ta, rt;
    int flag;
} processes;
                                                                    //shahidul islam prodhan = id 213902017
void b_sort(processes temp[], int n) {
    processes t;
    int i, j;
    for (i = 1; i < n; i++)
        for (j = 0; j < n - i; j++) {
            if (temp[j].at > temp[j + 1].at) {
                t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }
}

int accept(processes P[]) {
    int i, n;
    printf("\n Enter total no. of processes : ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("\n PROCESS [%d]", i + 1);
        printf(" Enter process name : ");
        scanf("%s", P[i].name);
        printf(" Enter burst time : ");
        scanf("%d", &P[i].bt);
        printf(" Enter arrival time : ");
        scanf("%d", &P[i].at);
        printf(" Enter priority : ");
        scanf("%d", &P[i].prt);
        P[i].rt = P[i].bt;
    }
    printf("\n PROC.\tB.T.\tA.T.\tPRIORITY");
    for (i = 0; i < n; i++)
        printf("\n %s\t%d\t%d\t%d", P[i].name, P[i].bt, P[i].at, P[i].prt);
    return n;
}

//fcfs


void FCFS(processes P[], int n, float* avgwt, float* avgta) {
    processes temp[10];
    int sumw = 0, sumt = 0;
    int x = 0;
    int i, j;
    for (i = 0; i < n; i++)
        temp[i] = P[i];

    b_sort(temp, n);

    printf("\n\n PROC.\tB.T.\tA.T.");
    for (i = 0; i < n; i++)
        printf("\n %s\t%d\t%d", temp[i].name, temp[i].bt, temp[i].at);

    sumw = temp[0].wt = 0;
    sumt = temp[0].ta = temp[0].bt - temp[0].at;

    for (i = 1; i < n; i++) {
        temp[i].wt = (temp[i - 1].bt + temp[i - 1].at + temp[i - 1].wt) - temp[i].at;
        temp[i].ta = (temp[i].wt + temp[i].bt);
        sumw += temp[i].wt;
        sumt += temp[i].ta;
    }

    *avgwt = (float)sumw / n;
    *avgta = (float)sumt / n;

    printf("\n\n PROC.\tB.T.\tA.T.\tW.T\tT.A.T");
    for (i = 0; i < n; i++)
        printf("\n %s\t%d\t%d\t%d\t%d", temp[i].name, temp[i].bt, temp[i].at, temp[i].wt, temp[i].ta);

    printf("\n\n GANTT CHART\n ");
    for (i = 0; i < n; i++)
        printf("   %s   ", temp[i].name);
    printf("\n ");

    printf("0\t");
    for (i = 1; i <= n; i++) {
        x += temp[i - 1].bt;
        printf("%d      ", x);
    }

    printf("\n\n Average waiting time = %0.2f\n Average turn-around = %0.2f.", *avgwt, *avgta);
}

//sjf np

void SJF_NP(processes P[], int n, float* avgwt, float* avgta) {
    processes temp[10];
    processes t;
    int sumw = 0, sumt = 0;
    int x = 0;
    int i, j;

    for (i = 0; i < n; i++)
        temp[i] = P[i];

    b_sort(temp, n);

    for (i = 2; i < n; i++)
        for (j = 1; j < n - i + 1; j++) {
            if (temp[j].bt > temp[j + 1].bt) {
                t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }
                                                            //shahidul islam prodhan = id 213902017
    printf("\n\n PROC.\tB.T.\tA.T.");
    for (i = 0; i < n; i++)
        printf("\n %s\t%d\t%d", temp[i].name, temp[i].bt, temp[i].at);

    sumw = temp[0].wt = 0;
    sumt = temp[0].ta = temp[0].bt - temp[0].at;

    for (i = 1; i < n; i++) {
        temp[i].wt = (temp[i - 1].bt + temp[i - 1].at + temp[i - 1].wt) - temp[i].at;
        temp[i].ta = (temp[i].wt + temp[i].bt);
        sumw += temp[i].wt;
        sumt += temp[i].ta;
    }

    *avgwt = (float)sumw / n;
    *avgta = (float)sumt / n;

    printf("\n\n PROC.\tB.T.\tA.T.\tW.T\tT.A.T");
    for (i = 0; i < n; i++)
        printf("\n %s\t%d\t%d\t%d\t%d", temp[i].name, temp[i].bt, temp[i].at, temp[i].wt, temp[i].ta);

    printf("\n\n GANTT CHART\n ");
    for (i = 0; i < n; i++)
        printf("   %s   ", temp[i].name);
    printf("\n ");

    printf("0\t");
    for (i = 1; i <= n; i++) {
        x += temp[i - 1].bt;
        printf("%d      ", x);
    }

    printf("\n\n Average waiting time = %0.2f\n Average turn-around = %0.2f.", *avgwt, *avgta);
}

//sjf p

void SJF_P(processes P[], int n, float* avgwt, float* avgta) {
    int i, j, smallest, time, count = 0, end;
    double wait_time = 0, turnaround_time = 0;
    processes temp[10];

    for (i = 0; i < n; i++)
        temp[i] = P[i];

    temp[9].bt = 9999; 

    for (time = 0; count != n; time++) {
        smallest = 9;
        for (i = 0; i < n; i++) {
            if (temp[i].at <= time && temp[i].bt < temp[smallest].bt && temp[i].bt > 0)
                smallest = i;
        }
        temp[smallest].bt--;
        if (temp[smallest].bt == 0) {
            count++;
            end = time + 1;
            temp[smallest].wt = end - temp[smallest].at - P[smallest].bt;
            temp[smallest].ta = end - temp[smallest].at;
            wait_time += temp[smallest].wt;
            turnaround_time += temp[smallest].ta;
        }
    }

    *avgwt = wait_time / n;
    *avgta = turnaround_time / n;

    printf("\n\n PROC.\tB.T.\tA.T.\tW.T\tT.A.T");
    for (i = 0; i < n; i++)
        printf("\n %s\t%d\t%d\t%d\t%d", temp[i].name, P[i].bt, temp[i].at, temp[i].wt, temp[i].ta);

    printf("\n\n Average waiting time = %0.2f\n Average turn-around = %0.2f.", *avgwt, *avgta);
}

//prio p

void PRT_P(processes P[], int n, float* avgwt, float* avgta) {
    int i, j, smallest, time, count = 0, end;
    double wait_time = 0, turnaround_time = 0;
    processes temp[10];

    for (i = 0; i < n; i++)
        temp[i] = P[i];

    temp[9].prt = 9999; 

    for (time = 0; count != n; time++) {
        smallest = 9;
        for (i = 0; i < n; i++) {
            if (temp[i].at <= time && temp[i].prt < temp[smallest].prt && temp[i].bt > 0)
                smallest = i;
        }
        temp[smallest].bt--;
        if (temp[smallest].bt == 0) {
            count++;
            end = time + 1;
            temp[smallest].wt = end - temp[smallest].at - P[smallest].bt;
            temp[smallest].ta = end - temp[smallest].at;
            wait_time += temp[smallest].wt;
            turnaround_time += temp[smallest].ta;
        }
    }

    *avgwt = wait_time / n;
    *avgta = turnaround_time / n;

    printf("\n\n PROC.\tB.T.\tA.T.\tW.T\tT.A.T");
    for (i = 0; i < n; i++)
        printf("\n %s\t%d\t%d\t%d\t%d", temp[i].name, P[i].bt, temp[i].at, temp[i].wt, temp[i].ta);

    printf("\n\n Average waiting time = %0.2f\n Average turn-around = %0.2f.", *avgwt, *avgta);
}

//prio nonp

void PRT_NP(processes P[], int n, float* avgwt, float* avgta) {
    processes temp[10];
    processes t;
    int sumw = 0, sumt = 0;
    int x = 0;
    int i, j;

    for (i = 0; i < n; i++)
        temp[i] = P[i];

    b_sort(temp, n);

    for (i = 2; i < n; i++)
        for (j = 1; j < n - i + 1; j++) {
            if (temp[j].prt > temp[j + 1].prt) {
                t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }

    printf("\n\n PROC.\tB.T.\tA.T.\tPRIORITY");
    for (i = 0; i < n; i++)
        printf("\n %s\t%d\t%d\t%d", temp[i].name, temp[i].bt, temp[i].at, temp[i].prt);

    sumw = temp[0].wt = 0;
    sumt = temp[0].ta = temp[0].bt - temp[0].at;

    for (i = 1; i < n; i++) {
        temp[i].wt = (temp[i - 1].bt + temp[i - 1].at + temp[i - 1].wt) - temp[i].at;
        temp[i].ta = (temp[i].wt + temp[i].bt);
        sumw += temp[i].wt;
        sumt += temp[i].ta;
    }

    *avgwt = (float)sumw / n;
    *avgta = (float)sumt / n;

    printf("\n\n PROC.\tB.T.\tA.T.\tW.T\tT.A.T");
    for (i = 0; i < n; i++)
        printf("\n %s\t%d\t%d\t%d\t%d", temp[i].name, temp[i].bt, temp[i].at, temp[i].wt, temp[i].ta);

    printf("\n\n GANTT CHART\n ");
    for (i = 0; i < n; i++)
        printf("   %s   ", temp[i].name);
    printf("\n ");

    printf("0\t");
    for (i = 1; i <= n; i++) {
        x += temp[i - 1].bt;
        printf("%d      ", x);
    }

    printf("\n\n Average waiting time = %0.2f\n Average turn-around = %0.2f.", *avgwt, *avgta);
}

//round


void RR(processes P[], int n, float* avgwt, float* avgta) {
    int pflag = 0, t, temp[10], k = 0, i, tq;
    int w = 0, ta = 0, sumw = 0, sumt = 0;
    float avg1 = 0, avg2 = 0;
    processes temp1[10], t1;
    processes temp2[10]; //1st cycle er pore remaining process gula store korar jonno

    printf("\n Enter time quantum : ");
    scanf("%d", &tq);

    for (i = 0; i < n; i++)
        temp1[i] = P[i];

    b_sort(temp1, n);

    for (i = 0; i < n; i++)
        temp[i] = temp1[i].bt;

    t = temp1[0].at;

    while (1) {
        for (i = 0, pflag = 0; i < n; i++) {
            if (temp[i] != 0) {
                pflag = 1;
                if (temp[i] > tq) {
                    temp[i] = temp[i] - tq;
                    t = t + tq;
                } else {
                    t = t + temp[i];
                    temp2[k] = temp1[i];
                    temp2[k].bt = temp[i];
                    temp2[k].wt = t - temp1[i].bt - temp1[i].at;
                    temp2[k].ta = t - temp1[i].at;
                    sumw += temp2[k].wt;
                    sumt += temp2[k].ta;
                    k++;
                    temp[i] = 0;
                }
            }
        }
        if (pflag == 0)
            break;
    }

    *avgwt = (float)sumw / n;
    *avgta = (float)sumt / n;

    printf("\n\n PROC.\tB.T.\tA.T.\tW.T\tT.A.T");               //shahidul islam prodhan = id 213902017
    for (i = 0; i < n; i++)
        printf("\n %s\t%d\t%d\t%d\t%d", temp2[i].name, temp2[i].bt, temp2[i].at, temp2[i].wt, temp2[i].ta);

    printf("\n\n GANTT CHART\n ");
    for (i = 0; i < k; i++)
        printf("   %s   ", temp2[i].name);
    printf("\n ");

    printf("0\t");
    for (i = 0; i < k; i++) {
        w += temp2[i].bt;
        printf("%d      ", w);
    }

    printf("\n\n Average waiting time = %0.2f\n Average turn-around = %0.2f.", *avgwt, *avgta);
}


//comparison funtion 1.0 from beta1-2.cpp
//fn compare korsi, eta main e call kora lagbe

void compare_algorithms(processes P[], int n)
{
    float fcfs_wt, fcfs_ta, sjf_np_wt, sjf_np_ta, prt_np_wt, prt_np_ta, rr_wt, rr_ta, sjf_p_wt, sjf_p_ta, prt_p_wt, prt_p_ta;
    const char* best_wt_algo;
    const char* best_ta_algo;
    float best_wt, best_ta;

    printf("\n\n--- FCFS Scheduling ---");
    FCFS(P, n, &fcfs_wt, &fcfs_ta);

    printf("\n\n--- SJF (Non-Preemptive) Scheduling ---");
    SJF_NP(P, n, &sjf_np_wt, &sjf_np_ta);

    printf("\n\n--- Priority (Non-Preemptive) Scheduling ---");
    PRT_NP(P, n, &prt_np_wt, &prt_np_ta);

    printf("\n\n--- Round Robin Scheduling ---");
    RR(P, n, &rr_wt, &rr_ta);

    printf("\n\n--- SJF (Preemptive) Scheduling ---");
    SJF_P(P, n, &sjf_p_wt, &sjf_p_ta);

    printf("\n\n--- Priority (Preemptive) Scheduling ---");
    PRT_P(P, n, &prt_p_wt, &prt_p_ta);                                  //https://github.com/TheShahidul

    printf("\n");
    printf("\n----------------------------------");
    printf("\n\nAlgorithm Performance Comparison:");
    printf("\n----------------------------------");
    printf("\n");

    // printf("\n\n Algorithm Comparison\n");
    printf("\n Algorithm\t\tAvg. Waiting Time\tAvg. Turnaround Time");
    printf("\n");
    printf("\n FCFS\t\t\t%0.2f\t\t\t%0.2f", fcfs_wt, fcfs_ta);
    printf("\n SJF (Non-Preemptive)\t%0.2f\t\t\t%0.2f", sjf_np_wt, sjf_np_ta);
    printf("\n SJF (Preemptive)\t%0.2f\t\t\t%0.2f", sjf_p_wt, sjf_p_ta);
    printf("\n Priority (Non-Preemptive)\t%0.2f\t\t\t%0.2f", prt_np_wt, prt_np_ta);
    printf("\n Priority (Preemptive)\t%0.2f\t\t\t%0.2f",   prt_p_wt, prt_p_ta);
    printf("\n Round Robin\t\t%0.2f\t\t\t%0.2f", rr_wt, rr_ta);

    // printf("\nFCFS - Average Waiting Time: %0.2f, Average Turn-Around Time: %0.2f\n", fcfs_wt, fcfs_ta);
    // printf("SJF (Non-Preemptive) - Average Waiting Time: %0.2f, Average Turn-Around Time: %0.2f\n", sjf_np_wt, sjf_np_ta);
    // printf("Priority (Non-Preemptive) - Average Waiting Time: %0.2f, Average Turn-Around Time: %0.2f\n", prt_np_wt, prt_np_ta);
    // printf("Round Robin - Average Waiting Time: %0.2f, Average Turn-Around Time: %0.2f\n", rr_wt, rr_ta);
    // printf("SJF (Preemptive) - Average Waiting Time: %0.2f, Average Turn-Around Time: %0.2f\n", sjf_p_wt, sjf_p_ta);
    // printf("Priority (Preemptive) - Average Waiting Time: %0.2f, Average Turn-Around Time: %0.2f\n", prt_p_wt, prt_p_ta);

    best_wt = fcfs_wt;
    best_ta = fcfs_ta;
    best_wt_algo = "FCFS";
    best_ta_algo = "FCFS";

    if (sjf_np_wt < best_wt) 
    {
        best_wt = sjf_np_wt;
        best_wt_algo = "SJF (Non-Preemptive)";
    }
    if (prt_np_wt < best_wt) 
    {
        best_wt = prt_np_wt;
        best_wt_algo = "Priority (Non-Preemptive)";
    }
    if (rr_wt < best_wt) 
    {
        best_wt = rr_wt;
        best_wt_algo = "Round Robin";
    }
    if (sjf_p_wt < best_wt) 
    {
        best_wt = sjf_p_wt;
        best_wt_algo = "SJF (Preemptive)";
    }
    if (prt_p_wt < best_wt) 
    {
        best_wt = prt_p_wt;
        best_wt_algo = "Priority (Preemptive)";
    }

    if (sjf_np_ta < best_ta) 
    {
        best_ta = sjf_np_ta;
        best_ta_algo = "SJF (Non-Preemptive)";
    }
    if (prt_np_ta < best_ta) 
    {
        best_ta = prt_np_ta;
        best_ta_algo = "Priority (Non-Preemptive)";
    }
    if (rr_ta < best_ta) 
    {
        best_ta = rr_ta;
        best_ta_algo = "Round Robin";
    }
    if (sjf_p_ta < best_ta) 
    {
        best_ta = sjf_p_ta;
        best_ta_algo = "SJF (Preemptive)";
    }
    if (prt_p_ta < best_ta) 
    {
        best_ta = prt_p_ta;
        best_ta_algo = "Priority (Preemptive)";
    }                                               //shahidul islam prodhan = id 213902017

    printf("\n================================================================================================");
    printf("\nFinal Results and opinion\n");
    printf("================================================================================================");
    printf("\nBest algorithm for waiting time: %s with an average waiting time of %0.2f", best_wt_algo, best_wt);
    printf("\n");
    printf("\nBest algorithm for turn-around time: %s with an average turn-around time of %0.2f", best_ta_algo, best_ta);
}

// Comparison function 0.0
// void compareAlgorithms(processes P[], int n) {
//     float avgwt_fcfs, avgta_fcfs;
//     float avgwt_sjf_np, avgta_sjf_np;
//     float avgwt_sjf_p, avgta_sjf_p;
//     float avgwt_prt_np, avgta_prt_np;
//     float avgwt_prt_p, avgta_prt_p;
//     float avgwt_rr, avgta_rr;

//     FCFS(P, n, &avgwt_fcfs, &avgta_fcfs);
//     SJF_NP(P, n, &avgwt_sjf_np, &avgta_sjf_np);
//     SJF_P(P, n, &avgwt_sjf_p, &avgta_sjf_p);
//     PRT_NP(P, n, &avgwt_prt_np, &avgta_prt_np);
//     PRT_P(P, n, &avgwt_prt_p, &avgta_prt_p);
//     RR(P, n, &avgwt_rr, &avgta_rr);

//     printf("\n\n Algorithm Comparison\n");
//     printf("\n Algorithm\t\tAvg. Waiting Time\tAvg. Turnaround Time");
//     printf("\n FCFS\t\t\t%0.2f\t\t\t%0.2f", avgwt_fcfs, avgta_fcfs);
//     printf("\n SJF (Non-Preemptive)\t%0.2f\t\t\t%0.2f", avgwt_sjf_np, avgta_sjf_np);
//     printf("\n SJF (Preemptive)\t%0.2f\t\t\t%0.2f", avgwt_sjf_p, avgta_sjf_p);
//     printf("\n Priority (Non-Preemptive)\t%0.2f\t\t\t%0.2f", avgwt_prt_np, avgta_prt_np);
//     printf("\n Priority (Preemptive)\t%0.2f\t\t\t%0.2f", avgwt_prt_p, avgta_prt_p);
//     printf("\n Round Robin\t\t%0.2f\t\t\t%0.2f", avgwt_rr, avgta_rr);
// }



//main function

int main() {
    int choice, n;
    char c;
    float avgwt = 0.0, avgta = 0.0;
    processes P[10];

    printf("\n CPU Scheduling\n");
    printf("\n A Consol Based Simulator");
    printf("\n=====================================\n\n");                  //shahidul islam prodhan = id 213902017
    printf("\n Md. Shahidul Islam Prodhan\n ID: 213902017\n\n");
    printf("\n=====================================\n\n");
    printf("\n Menu\n");
    printf("\n Press any key to continue...");
    printf("\n=====================================\n\n");

    do {
        printf("\n\n 1. FCFS");
        printf("\n 2. SJF (Non-preemptive)");
        printf("\n 3. SJF (Preemptive)");
        printf("\n 4. Priority (Non-preemptive)");
        printf("\n 5. Priority (Preemptive)");
        printf("\n 6. Round Robin");
        printf("\n 7. Compare All Algorithms");
        printf("\n 8. Exit");
        printf("\n Select your choice : ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            n = accept(P);
            FCFS(P, n, &avgwt, &avgta);
            break;
        case 2:
            n = accept(P);
            SJF_NP(P, n, &avgwt, &avgta);
            break;
        case 3:
            n = accept(P);
            SJF_P(P, n, &avgwt, &avgta);
            break;
        case 4:
            n = accept(P);
            PRT_NP(P, n, &avgwt, &avgta);
            break;
        case 5:
            n = accept(P);
            PRT_P(P, n, &avgwt, &avgta);
            break;
        case 6:
            n = accept(P);
            RR(P, n, &avgwt, &avgta);
            break;
        case 7:
            n = accept(P);
            compare_algorithms(P, n);
            break;
        case 8:
            exit(0);
        }
        printf("\n Do you want to continue? (y/n) : ");
        c = getch();
    } while (c == 'y' || c == 'Y');

    return 0;
}
