#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
// int 
// sys_memsize(void) // memsize system call 
// {
//   struct proc* m_proc;

//   m_proc = myproc();

//   return m_proc->sz;
// }

// int 
// sys_trace(void) // trace system call 
// {
//   if (argint(0, &myproc()->tracemask) < 0) return 1;

//   return 0;
// }

/* homework 3 for scheduler (use weightset system call) - 20180775 */

int
sys_weightset(void)
{
  int weight;

  if(argint(0, &weight) < 0 || weight == 0) // exception for weight variable return -1
  {
    return -1;
  }
  do_weightset(weight); // else for exception execute do_weightset(weight)
  return 1;
}