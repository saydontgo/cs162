#include <stdio.h>
#include <sys/resource.h>

int main() {
    struct rlimit lim;
    if(!getrlimit(RLIMIT_STACK,&lim))
    printf("stack size: %ld\n", (long)lim.rlim_cur);
    if(!getrlimit(RLIMIT_NPROC,&lim));
    printf("process limit: %ld\n",(long) lim.rlim_cur);
    if(!getrlimit(RLIMIT_NOFILE,&lim))    
    printf("max file descriptors: %ld\n",(long) lim.rlim_max);
    return 0;
}
