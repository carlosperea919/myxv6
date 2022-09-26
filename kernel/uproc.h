struct uproc {
	int pid;
	enum procstate state;
	uint64 size;
	int ppid;
	char name[16];
};
