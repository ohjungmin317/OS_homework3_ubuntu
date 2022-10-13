#include "types.h"
#include "stat.h"
#include "user.h"

#define PNUM 5 // number of process 
#define PRINT_CYCLE 100000000 // process prints information cycle
#define TOTAL_COUNTER 500000000 // terminate the process counter

void sdebug_func(void){
    int n, pid;

    int start, end; // calculate uptime() value -> start & end 
    
    int weight = 1; // use the weightset systemcall for weight value increase 1

    printf(1, "start sdebug command\n");

    for (n = 0; n < PNUM; n++){ // loop for the process counter 
        pid = fork(); // use fork systemcall create the process 

        if (pid < 0){ // exception for fork error when pid < 0 
            printf(1, "fork error\n");
        }
        if (pid == 0){ // when pid == 0 child process fork() return value 0 so only execute child process 
            long counter;

            weightset(weight); // child process execute weightset => + 1 

            start = uptime(); // start the uptime() -> when execute process clock_tick -> + 1 

            for (counter = 0; counter < TOTAL_COUNTER; counter++){ // loop for the counter for TOTAL_COUNTER => when counter == TOTAL_COUNTER process terminated
                if (counter == PRINT_CYCLE){ // counter == PRINT_CYCLE print process info
                    
                    end = uptime(); // end the uptime() record the process running time 

                    int totaltime = (end - start) * 10; // (process print info time - process start time) * 10 

                    printf(1, "PID : %d, WEIGHT : %d, TIMES : %d ms\n", getpid(), weight, totaltime);
                }
                
            }
            exit();
        }
        weight++;
       
    }
    /* wait for all child processes by sdebug.c create process to terminate */
    /* Refer to forktest.c */
    if (n == pid){
        printf(1, "fork claimed to work N times!\n", pid);
        exit();
    }

    for (; n > 0; n--){
        if ((pid = wait() )< 0){
            printf(1, "wait stopped early\n");
            exit();
        }
        else{
            printf(1,"PID: %d terminated\n",pid);
        }
    }

    if (wait() != -1){
        printf(1, "wait got too many\n");
        exit();
    }

    printf(1, "end of sdebug command\n");
}

int main(void){
    sdebug_func();
    exit();
}