#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/uproc.h"
#include "user/user.h"

struct uproc up[NPROC];
int nprocs;

void mktree(int indent, int pid) {
	int found = 0;
	int i = 0;
	
	while (!found && i < nprocs) {
		if (up[i].pid == pid)
			found = 1;
		else
			i++;
	}
	if (!found) {
		printf("pid %d not found\n", pid);
		return;
	}
	for (int j=0; j < indent; j++)
		printf(" ");
	printf("%s(%d)\n", up[i].name, up[i].pid);
	for (i=0; i < nprocs; i++) {
		if (up[i].ppid == pid) {
			mktree(indent+1, up[i].pid);
		}
	}
	return;
}

int main(int argc, char **argv) {
	int pid = 1;
	
	if (argc == 2)
		pid = atoi(argv[1]);
	nprocs = getprocs(up);
	if (nprocs < 0)
		exit(-1);
	mktree(0, pid);
	exit(0);
}
