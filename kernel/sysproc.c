#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  if(argint(0, &n) < 0)
    return -1;
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  if(argaddr(0, &p) < 0)
    return -1;
  return wait(p);
}

uint64
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

uint64
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

uint64
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64
sys_getprocs(void) {
	uint64 st; // user pointer to struct uproc

	if (argaddr(0, &st) < 0)
		return -1;
		
	return procinfo(st);
	
}

uint64
sys_freepmem(void) {
  return kfreepagecount();
}

uint64
sys_sem_init(void)
{
  sem_t *sem;
  int pshared;
  unsigned int value;
  if (argaddr(0, (void*)&sem) < 0 || argint(1, &pshared) < 0 || argint(2, &value) < 0)
  	return -1;
  if (pshared != 1)
  	return -1;
  int allocatedsem = semalloc();
  if (allocatedsem < 0)
  	return -1;
  semtable.sem[allocatedsem].count = value;
  copyout(myproc()->pagetable, sem, allocatedsem, sizeof(allocatedsem));
}

uint64
sys_sem_destroy(void)
{
  sem_t *sem;
  if (argaddr(0, (void*)&sem) < 0)
  	return -1;
  uint64 sem_index;
  copyin(myproc()->pagetable, sem_index, sem, sizeof(sem));
  semdealloc(sem_index);
}

uint64
sys_sem_wait(void)
{
  sem_t *sem;
  if (argaddr(0, (void*)&sem) < 0)
  	return -1;
  uint64 sem_index;
  copyin(myproc()->pagetable, sem_index, sem, sizeof(sem));
  acquire(&semtable.sem[sem_index].lock);
  while (&semtable.sem[sem_index].count == 0)
    sleep(&semtable.sem[sem_index], &semtable.sem[sem_index].lock);
  release(&semtable.sem[sem_index].lock);
}

uint64
sys_sem_post(void)
{
  sem_t *sem;
  if (argaddr(0, (void*)&sem) < 0)
  	return -1;
  uint64 sem_index;
  copyin(myproc()->pagetable, sem_index, sem, sizeof(sem));
  acquire(&semtable.sem[sem_index].lock);
  while (&semtable.sem[sem_index].count == 0)
    wakeup(&semtable.sem[sem_index]);
  release(&semtable.sem[sem_index].lock);
}


