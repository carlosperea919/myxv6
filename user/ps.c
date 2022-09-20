#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "user/uproc.h"
#include "kernel/param.h"

int main(int argc, char **argv) {
	struct uproc *p = malloc(NPROC * sizeof *p);
	getprocs(p);
	
	/*tatic char *states[] = {
  [UUNUSED]    "unused",
  [USLEEPING]  "sleep ",
  [URUNNABLE]  "runble",
  [URUNNING]   "run   ",
  [UZOMBIE]    "zombie"
  };*/
  //char *state;
	
  printf("\n");
  //for(p = proc; p < &proc[NPROC]; p++){
    //if(p->state == UNUSED)
      //continue;
    //if(p->state >= 0 && p->state < NELEM(states) && states[p->state])
      //state = states[p->state];
    //else
      //state = "???";
    //printf("%d %s %s", p->pid, state, p->name);
    printf("%d", p->name);
    printf("\n");
  //}*/
  exit(1);
	
}
