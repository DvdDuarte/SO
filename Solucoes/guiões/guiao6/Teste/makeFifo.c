#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main() {
   if (mkfifo("serverr_fifo", 0666) == -1) {
       perror("Criação do fifo serverr");
   }
   if (mkfifo("serverw_fifo", 0666) == -1) {
       perror("Criação do fifo serverw");
   }
   return 0;
}