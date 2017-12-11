#include "header.h"

void printlast () {

  int fd = open("story.txt", O_RDONLY);
  int shmid = shmget(SHM_KEY, 0, 0);
  int* temp = (int*) shmat(shmid, 0, SHM_RDONLY);
  int linesize = *temp;
  shmdt(temp);
  lseek(fd, -1 * linesize, SEEK_END);
  char* buf = malloc(linesize + 1);
  read(fd, buf, linesize);
  printf("Last line: %s\n", buf);
  close(fd);
  free(buf);
}

int main(){
	int sem = semget(SEM_KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
	error(sem);

	printf("Checking if resources are available...\n");
	struct sembuf sb;
	sb.sem_op = -1;
	sb.sem_num = 0;
	sb.sem_flg = SEM_UNDO;
	semop(sem, &sb, 1);
	printf("You're good to go\n");

	printlast();
	printf("Write the next line:");
	char line[100];
	fgets(line, sizeof(line), stdin);

	int fd = open("story.txt", O_APPEND);
	write(fd, line, strlen(line));

	int shmid = shmget(SHM_KEY, 0, 0);
	int* temp = (int*) shmat(shmid, 0, 0);
	*temp = strlen(line);
	shmdt(temp);

	sb.sem_op = 1;
	semop(sem, &sb, 1);

	return 0;
	
}
