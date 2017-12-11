#include "header.h"

int main(){
	int sem = semget(SEM_KEY, 1, 0);
	error(sem);

	printf("Checking if resources are available...\n");
	struct sembuf sb;
	sb.sem_op = -1;
	sb.sem_num = 0;
	sb.sem_flg = SEM_UNDO;
	semop(sem, &sb, 1);

	int fd = open("story.txt", O_RDWR | O_APPEND);
	error(fd);

	int shm = shmget(SHM_KEY, 0, 0);
	error(shm);
	int * val = (int *)shmat(shm, 0, 0);

	printf("Last line: \n");
	printstory(*val);
	int last_length = lseek(fd, 0, SEEK_END) - *val;

	lseek(fd, *val += last_length, SEEK_SET);
	printf("Continue the story: ");
	char input[10000];
	fgets(input, 10000, stdin);
	write(fd, input, strlen(input));

	shmdt(val);
	close(fd);

	return 0;
}
