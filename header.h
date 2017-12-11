#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define SHM_KEY 980081
#define SEM_KEY 13

union semun {
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INFO
                               (Linux-specific) */
};

void error(int val){
	if(val == -1){
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void printstory (int offset) {
  int fd = open("story.txt", O_RDONLY);
  int size = lseek(fd, offset, SEEK_END) - offset;
  lseek(fd, offset, SEEK_SET);
  char* buf = calloc(1, size + 1);
  read(fd, buf, size);
  printf("%s\n", buf);
  close(fd);
}