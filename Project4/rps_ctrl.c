#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int fd; 
char buf[4] = {0,1,2,3};

// Define signal handlers here.
void sigterm_handler(int signo){
	close(fd);
	exit(1);
}
void sigrtmin_handler(int signo){
	write(fd, buf, 1);
}
void sigrtmin1_handler(int signo){
	write(fd, buf+1, 1);
}
void sigrtmin2_handler(int signo){
	write(fd, buf+2, 1);
}
void sigrtmin3_handler(int signo){
	write(fd, buf+3, 1);
}
int main(void)
{
  fd = open("/dev/rps", O_WRONLY);
  // Register signal handlers here.
  signal(SIGTERM, sigterm_handler);
  signal(SIGRTMIN, sigrtmin_handler);
  signal(SIGRTMIN+1, sigrtmin1_handler);
  signal(SIGRTMIN+2, sigrtmin2_handler);
  signal(SIGRTMIN+3, sigrtmin3_handler);
  while(1) pause();
  return 0;
}
