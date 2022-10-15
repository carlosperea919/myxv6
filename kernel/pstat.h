struct pstat {
	int pid;
	enum procstate state;
	uint64 size;
	uint arrtime;
	uint cputime;
	int ppid;
	int priority;
	char name[16];
};

struct rusage {
	uint cputime;
};
