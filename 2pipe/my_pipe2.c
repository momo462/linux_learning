#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main()
{
  //创建pipe
  int pipe_fd[2];
  int my_pipe=pipe(pipe_fd);
  if(my_pipe < 0)
  {
    perror("pipe:");
  }
  //创建子进程
  pid_t pid=fork();
  if(pid==0)//child
  {
    //关读端
    close(pipe_fd[0]);
    int count = 5;
    int i=0;
    char buf[]="hello world\n";
    while(1)
    {
     ssize_t wr = write(pipe_fd[1],buf,strlen(buf));
     if(wr < 0)
     {
        perror("write:");
     }
     if(count-->0)
     {
       sleep(1);
     }
     printf("child: write data :%d\n",i++ );
    }
  }
  else
  {
    //关写端
    close(pipe_fd[1]);
     int count=5;
    char buf[1024];
    while(count-->0)
    {
      memset(buf,'\0',sizeof(buf));
      ssize_t rd=read(pipe_fd[0],buf,sizeof(buf));
      if(rd < 0)
      {
        perror("read:");
      }
      if(rd>0)
      {
        buf[rd]='\0';
      }
      printf(buf);
    }
    while(1);

    pid_t ret = waitpid(pid,NULL,0);
    if(ret==pid)
    {
      printf("wait child success...\n");
    }
  }
  return 0; 

}
