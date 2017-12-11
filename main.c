#include "header.h"

int main(){
	int sem = semget(SEM_KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
	error(sem);

	printf("Checking if resources are available...\n");
	struct sembuf sb;
	sb.sem_op = -1;
	sb.sem_num = 0;
	sb.sem_flg = SEM_UNDO;
	semop(sem, &sb, 1);

	printf("Last line: \n");
}