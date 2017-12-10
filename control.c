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

#define SHM_KEY 13
#define SEM_KEY 980081

union semun {
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INFO
                               (Linux-specific) */
};

int main(int argc, char** argv){
	if(argc != 2){
		printf("error: unexpected number of arguments, expected 1\n");
		return 0;
	}

	if(!strcmp(argv[1], "-c")){
		union semun su;
		su.val = 1;
		int shm = shmget(SHM_KEY, sizeof(int), IPC_CREAT | IPC_EXCL | 0644);
		int sem = semget(SEM_KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
		semctl(sem, 0, SETVAL, su);
		int fd = open("story.txt", O_CREAT | O_RDWR | O_TRUNC | 0644);
		close(fd);
		return 0;
	}

	if(!strcmp(argv[1], "-r")){
		int shm = shmget(SHM_KEY, sizeof(int), IPC_CREAT | IPC_EXCL | 0644);
		shmctl(shm, IPC_RMID, NULL);
		return 0;
	}


	if(!strcmp(argv[1], "-v")){
		int fd = open("story.txt", O_RDONLY);

		close(fd);
		return 0;
	}

	else{
		printf("error: expected -c, -r, or -v, given %s\n", argv[1]);
	}

 return 0;
}
