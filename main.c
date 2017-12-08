#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define SHM_KEY 13
#define SEM_KEY 980081

int main(int argc, char** argv){
  if(argc == 1){

  }
  
  if(argc > 2){
    printf("Unexpected number of arguments, expected 1");
    return 0;
  }
  
  if(!strcmp(argv[1], "-c")){
    int shm = shmget(SHM_KEY, sizeof(long), IPC_CREAT | IPC_EXCL | 0644);
    int sem = semget(SEM_KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
    int fd = open("story.txt", O_CREAT | O_EXCL | O_RDWR | O_TRUNC | 0644);
  }

  if(!strcmp(argv[1], "-r")){
    
  }


 if(!strcmp(argv[1], "-v")){
   int fd = open("story.txt", O_RDONLY);
   
   close(fd);
 }











 return 0;
}
