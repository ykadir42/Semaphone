#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>

#define KEY 2017

int main(int argc, char ** argv){
	int i = 0;
	// for(; i < argc; i++){
	// 	printf("arg[%d]: %s\n", i, argv[i]);
	// }
	if(argc < 2 || argc > 3){
		printf("please use the correct number of arguments\n");
		return 0;
	}

	if(!strcmp(argv[1], "-c")){
		if(argc != 3){
			printf("please use 3 arguments\n");
			return 0;
		}

		int sem = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
		if(sem == -1){
			printf("semaphore already exists\n");
			return 0;
		}

		printf("semaphore created: %d\n", sem);
		semctl(sem, 0, SETVAL, atoi(argv[2]));
        printf("value set: %d\n", atoi(argv[2]));
		return 0;
	}

	else if(!strcmp(argv[1], "-v")){
		if(argc != 2){
			printf("please use 2 arguments\n");
			return 0;
		}

		int sem = semget(KEY, 0, 0);
		if(sem == -1){
			printf("%s\n", strerror(errno));
			return 0;
		}

		int val = semctl(sem, 0, GETVAL);
        printf("semaphore value: %d\n", val);
		return 0;
	}

	else if(!strcmp(argv[1], "-r")){
		if(argc != 2){
			printf("please use 2 arguments\n");
			return 0;
		}

		int sem = semget(KEY, 0, 0);
		if(sem == -1){
			printf("%s\n", strerror(errno));
			return 0;
		}
		int ctl = semctl(sem, 0, IPC_RMID);
        printf("semaphore removed: %d\n", ctl);
		return 0;
	}

	else{
		printf("use flags -c to create, -v to view, or -r to remove\n");
		return 0;
	}
	return 0;
}