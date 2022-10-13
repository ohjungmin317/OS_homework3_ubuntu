#include "types.h"
#include "stat.h"
#include "user.h"

#define PNUM 5
#define PRINT_CYCLE 100000000
#define TOTAL_COUNTER 500000000

void sdebug_func(void){
    int n, pid;

    int start, end;
    
    int weight = 1;

    printf(1, "start sdebug command\n");

    for (n = 0; n < PNUM; n++){
        pid = fork();

        if (pid < 0){
            printf(1, "fork error\n");
        }
        if (pid == 0){
            long counter;
            weightset(weight);
            start = uptime();

            for (counter = 0; counter < TOTAL_COUNTER; counter++){
                if (counter == PRINT_CYCLE){
                    end = uptime();
                    int totaltime = (end - start) * 10;
                    printf(1, "PID=%d, WEIGHT=%d, TIMES=%d\n", getpid(), weight, totaltime);
                }                
            }
            exit();
        }
        weight++;
       
    }

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