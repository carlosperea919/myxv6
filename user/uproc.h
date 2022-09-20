enum uprocstate { UUNUSED, UUSED, USLEEPING, URUNNABLE, URUNNING, UZOMBIE };

struct uproc {
	int pid;
	enum uprocstate state;
	uint64 size;
	int ppid;
	char name[16];
};
