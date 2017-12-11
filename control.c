#include "header.h"

void printstory () {
  int fd = open("story.txt", O_RDONLY);
  int size = lseek(fd, 0, SEEK_END);
  lseek(fd, 0, SEEK_SET);
  char* buf = malloc(size + 1);
  read(fd, buf, size);
  printf("STORY \n%s\n", buf);
  close(fd);
}

int main(int argc, char** argv){
	if(argc != 2){
		printf("error: unexpected number of arguments, expected 1\n");
		return 0;
	}

	if(!strcmp(argv[1], "-c")){
		printf("Creating semaphore\n");
		union semun su;
		su.val = 1;
		int sem = semget(SEM_KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
		error(sem);
		semctl(sem, 0, SETVAL, su);

		printf("Creating shared memory\n");
		int shm = shmget(SHM_KEY, sizeof(int), IPC_CREAT | IPC_EXCL | 0644);
		error(shm);

		printf("Creating story file\n");
		int fd = open("story.txt", O_CREAT | O_RDWR | O_TRUNC | 0644);
		error(fd);
		close(fd);

		return 0;
	}

	if(!strcmp(argv[1], "-r")){
		int sem = semget(SEM_KEY, 1, 0);
		error(sem);
		printf("Removing semaphore\n");
		struct sembuf sb;
		sb.sem_op = -1;
		sb.sem_num = 0;
		semop(sem, &sb, 1);
		semctl(sem, 0, IPC_RMID);

		printf("Removing shared memory\n");
		int shm = shmget(SHM_KEY, sizeof(int), 0);
		error(shm);
		error(shmctl(shm, 0, IPC_RMID));
		//printf("Removed shared memory\n");

		printf("Removing story\n");
		remove("story.txt");

		printstory();
		return 0;
	}


	if(!strcmp(argv[1], "-v")){
		printstory();
		return 0;
	}

	else{
		printf("error: expected -c, -r, or -v, given %s\n", argv[1]);
	}

	return 0;
}
