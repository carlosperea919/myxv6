#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"
#include "kernel/pstat.h"

int main(int argc, char **argv) {
	struct pstat up[NPROC];
	int nprocs = getprocs(up);
	
	static char *states[] = {
	[SLEEPING]  "sleeping",
	[RUNNABLE]  "runnable",
	[RUNNING]   "running ",
	[ZOMBIE]    "zombie  "
	};
	char *state;
	
	if (nprocs < 0)
		exit(-1);
	printf("pid\tstate\t\tsize\tppid\tname\tcputime\n");
	for(int i = 0; i < nprocs; i++){
		state = states[up[i].state];
		printf("%d\t%s\t%l\t%d\t%s\t%d\n", up[i].pid, state, up[i].size, up[i].ppid, up[i].name, up[i].cputime);
	}
	exit(0);
	
}
