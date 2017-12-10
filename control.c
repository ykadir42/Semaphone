#include "header.h"

void error(int val){
	if(val == -1){
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char** argv){
	if(argc != 2){
		printf("error: unexpected number of arguments, expected 1\n");
		return 0;
	}

	if(!strcmp(argv[1], "-c")){
		union semun su;
		su.val = 1;
		int shm = shmget(SHM_KEY, sizeof(int), IPC_CREAT | IPC_EXCL | 0644)
		error(shm);
		int sem = semget(SEM_KEY, 1, IPC_CREAT | IPC_EXCL | 0644)
		error(sem);
		error(semctl(sem, 0, SETVAL, su))
		int fd = open("story.txt", O_CREAT | O_RDWR | O_TRUNC | 0644);
		error(fd);
		close(fd);
		return 0;
	}

	if(!strcmp(argv[1], "-r")){
		semget(SEM_KEY, 1, )
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
