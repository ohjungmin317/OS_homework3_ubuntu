#include "types.h"
#include "stat.h"
#include "user.h"

#define PNUM 5 // number of process 
#define PRINT_CYCLE 10000000 // process prints information cycle
#define TOTAL_COUNTER 500000000 // terminate the process counter

void sdebug_func(void){
    int n, pid;
    int weight = 1; // use the weightset systemcall for weight value increase
    int start, end; // calculate uptime() value -> start & end 

    printf(1, "start sdebug command\n");

    for (n = 0; n < PNUM; n++){ // loop for the process counter 
        pid = fork(); // use fork systemcall create the process 

        if (pid < 0){ // exception for fork error when pid < 0 
            printf(1, "fork error\n");
            break;
        }
        if (pid == 0){ // when pid == 0 child process fork() return value 0 so only execute child process 
            
            start = uptime(); // start the uptime() -> when execute process clock_tick -> + 1
            
            long counter=0;
            int first = 1;

            int print_counter = PRINT_CYCLE;  

            weightset(weight); // child process execute weightset => + 1 

            while (counter++<=TOTAL_COUNTER) {  // loop for the counter for TOTAL_COUNTER => when counter == TOTAL_COUNTER process terminated
                
                print_counter--;

                if(print_counter == 0) // if print_count -> PRINT_CYCLE == 0 
                {
                    if(first){ // PRINT_CYCLE == 0 -> first == 1  and print the info
                        end = uptime();
                        int total_time = (end - start) * 10; // calculate for process time 
                        printf(1,"PID: %d, WEIGHT: %d",getpid(),weight);
                        printf(1,"TIMES: %d ms\n",total_time);
                        first = 0;
                    }
                    print_counter = PRINT_CYCLE;
                }
                
            }
            printf(1,"PID: %d terminated\n",getpid());
            exit();
        }
        weight++;      
    }
    
    /* wait for all child processes by sdebug.c create process to terminate */
    /* Refer to forktest.c */

    // if (n == pid){
    //     printf(1, "fork claimed to work N times!\n", pid);
    //     exit();
    // }

    for (; n > 0; n--){
        if ((pid = wait() )< 0){
            printf(1, "wait stopped early\n");
            exit();
        }
        // else{
        //     printf(1,"PID: %d terminated\n",pid);
        // }
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