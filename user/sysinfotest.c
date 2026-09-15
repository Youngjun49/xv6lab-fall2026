#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/sysinfo.h"
#include "user/user.h"

int
main(void)
{
  struct sysinfo info;

  if (sysinfo(&info) < 0) {
    printf("sysinfo failed\n");
    exit(1);
  }

  printf("freepages = %lu pages\n", info.freepages);
  printf("nproc     = %lu\n", info.nproc);

  int pid = fork();

  if (pid < 0) {
    printf("fork failed\n");
    exit(1);
  }

  if (pid == 0) {
    // 자식 프로세스
    if (sysinfo(&info) < 0) {
      printf("sysinfo failed\n");
      exit(1);
    }

    printf("[child] nproc = %lu\n", info.nproc);
    exit(0);
  }

  // 부모 프로세스
  wait(0);

  exit(0);
}