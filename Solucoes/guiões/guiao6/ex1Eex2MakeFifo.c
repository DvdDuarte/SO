#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main() {
   if (mkfifo("fifo", 0666) == -1) {
       perror("Criação do fifo");
   }
   return 0;
}