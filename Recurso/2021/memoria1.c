#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <signal.h>
#include <stdlib.h>


 double media(int* valores){
     int ac=0;
     for (int i=0; i<10; i++){
         ac+=valores[i];
     }
     return ac/10;
 }

 int maisBaixo(int* valores){
     int menor=valores[0];
     for (int i=1; i<10;i++){
         if(valores[i]<menor){
             menor=valores[i];
         }
     }
     return menor;
 }

 int maisAlto(int* valores){
     int maior=0;
     for (int i=0; i<10;i++){
         if(valores[i]>maior){
             maior=valores[i];
         }
     }
     return maior;
 }

 int main(int args, char **argv)
 {

     int status;
     int fd[2][2];
     for(int i=0; i<2; i++){
         pipe(fd[i]);
     }
     int valores[10];
     for (int i = 0; i < 10; i++){

         pid_t pid;
         if ((pid = fork()) == 0){
             execlp(argv[0], argv[0], argv + 1, NULL);
         }
         wait(NULL);
         pid_t pid2;
         if ((pid2 = fork()) == 0)
         {
             char comando[100];
             sprintf(comando, "%s/%d/%s", "/proc", pid, "memstats");
             close(fd[0][0]);
             dup2(fd[0][1], 1);
             close(fd[0][1]);
             execlp("grep", "grep", "VnPeak", comando, NULL);
             _exit(0);
         }
         wait(NULL);
         pid_t pid3;
         if ((pid3 = fork()) == 0)
         {
             close(fd[1][0]);
             dup2(fd[1][1], 1);
             close(fd[1][1]);
             execlp("cut", "cut", "-d"", """, "-f4",NULL);
             _exit(0);
         }
         wait(NULL);
         char buffer[100];
         read(fd[1][0], buffer, 100);
         valores[i]= atoi(buffer);
     }
     printf("Menor: %d | Media: %f | Maior: %d\n", maisBaixo(valores), media(valores), maisAlto(valores));
     return 0;
 }
