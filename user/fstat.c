#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"


int main(int argc, char **argv) {

	if (argc != 2) {
		fprintf(2, "usage: newfstat file/directory name...\n");
		exit(1);
	}
	char buf[512], *p;
	int fd;
	struct dirent de;
	struct stat st;
	if((fd = open(argv[1], 0)) < 0){
	    fprintf(2, "fstat: cannot open %s\n", argv[1]);
	    return;
	}
	if(fstat(fd, &st) < 0){
	    fprintf(2, "fstat: cannot stat %s\n", argv[1]);
	    close(fd);
	    return;
	}
	switch(st.type){
	  case T_FILE:
	    printf("Name: %s Type: File\nSize: %l bytes\nInode Number: %d Links: %d\n", argv[1], st.size, st.ino, st.nlink);
	    break;

	  case T_DIR:
	    printf("Name: %s Type: Directory\nSize: %l bytes\nInode Number: %d Links: %d\n", argv[1], st.size, st.ino, st.nlink);
	    break;
	}
	exit(0);
}
