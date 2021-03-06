# 1 "<stdin>"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "<stdin>"
# 36 "<stdin>"
# 1 "/usr/include/sys/times.h" 1 3 4
# 26 "/usr/include/sys/times.h" 3 4
# 1 "/usr/include/features.h" 1 3 4
# 358 "/usr/include/features.h" 3 4
# 1 "/usr/include/sys/cdefs.h" 1 3 4
# 353 "/usr/include/sys/cdefs.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 354 "/usr/include/sys/cdefs.h" 2 3 4
# 359 "/usr/include/features.h" 2 3 4
# 382 "/usr/include/features.h" 3 4
# 1 "/usr/include/gnu/stubs.h" 1 3 4



# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 5 "/usr/include/gnu/stubs.h" 2 3 4


# 1 "/usr/include/gnu/stubs-32.h" 1 3 4
# 8 "/usr/include/gnu/stubs.h" 2 3 4
# 383 "/usr/include/features.h" 2 3 4
# 27 "/usr/include/sys/times.h" 2 3 4


# 1 "/usr/include/time.h" 1 3 4
# 56 "/usr/include/time.h" 3 4
# 1 "/usr/include/bits/types.h" 1 3 4
# 28 "/usr/include/bits/types.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 29 "/usr/include/bits/types.h" 2 3 4


typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;


typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;




__extension__ typedef signed long long int __int64_t;
__extension__ typedef unsigned long long int __uint64_t;







__extension__ typedef long long int __quad_t;
__extension__ typedef unsigned long long int __u_quad_t;
# 131 "/usr/include/bits/types.h" 3 4
# 1 "/usr/include/bits/typesizes.h" 1 3 4
# 132 "/usr/include/bits/types.h" 2 3 4


__extension__ typedef __u_quad_t __dev_t;
__extension__ typedef unsigned int __uid_t;
__extension__ typedef unsigned int __gid_t;
__extension__ typedef unsigned long int __ino_t;
__extension__ typedef __u_quad_t __ino64_t;
__extension__ typedef unsigned int __mode_t;
__extension__ typedef unsigned int __nlink_t;
__extension__ typedef long int __off_t;
__extension__ typedef __quad_t __off64_t;
__extension__ typedef int __pid_t;
__extension__ typedef struct { int __val[2]; } __fsid_t;
__extension__ typedef long int __clock_t;
__extension__ typedef unsigned long int __rlim_t;
__extension__ typedef __u_quad_t __rlim64_t;
__extension__ typedef unsigned int __id_t;
__extension__ typedef long int __time_t;
__extension__ typedef unsigned int __useconds_t;
__extension__ typedef long int __suseconds_t;

__extension__ typedef int __daddr_t;
__extension__ typedef long int __swblk_t;
__extension__ typedef int __key_t;


__extension__ typedef int __clockid_t;


__extension__ typedef void * __timer_t;


__extension__ typedef long int __blksize_t;




__extension__ typedef long int __blkcnt_t;
__extension__ typedef __quad_t __blkcnt64_t;


__extension__ typedef unsigned long int __fsblkcnt_t;
__extension__ typedef __u_quad_t __fsblkcnt64_t;


__extension__ typedef unsigned long int __fsfilcnt_t;
__extension__ typedef __u_quad_t __fsfilcnt64_t;

__extension__ typedef int __ssize_t;



typedef __off64_t __loff_t;
typedef __quad_t *__qaddr_t;
typedef char *__caddr_t;


__extension__ typedef int __intptr_t;


__extension__ typedef unsigned int __socklen_t;
# 57 "/usr/include/time.h" 2 3 4



typedef __clock_t clock_t;



# 30 "/usr/include/sys/times.h" 2 3 4





struct tms
  {
    clock_t tms_utime;
    clock_t tms_stime;

    clock_t tms_cutime;
    clock_t tms_cstime;
  };






extern clock_t times (struct tms *__buffer) __attribute__ ((__nothrow__));


# 37 "<stdin>" 2
# 1 "/usr/include/sys/types.h" 1 3 4
# 28 "/usr/include/sys/types.h" 3 4






typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;




typedef __loff_t loff_t;



typedef __ino_t ino_t;
# 61 "/usr/include/sys/types.h" 3 4
typedef __dev_t dev_t;




typedef __gid_t gid_t;




typedef __mode_t mode_t;




typedef __nlink_t nlink_t;




typedef __uid_t uid_t;





typedef __off_t off_t;
# 99 "/usr/include/sys/types.h" 3 4
typedef __pid_t pid_t;





typedef __id_t id_t;




typedef __ssize_t ssize_t;





typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;





typedef __key_t key_t;
# 133 "/usr/include/sys/types.h" 3 4
# 1 "/usr/include/time.h" 1 3 4
# 74 "/usr/include/time.h" 3 4


typedef __time_t time_t;



# 92 "/usr/include/time.h" 3 4
typedef __clockid_t clockid_t;
# 104 "/usr/include/time.h" 3 4
typedef __timer_t timer_t;
# 134 "/usr/include/sys/types.h" 2 3 4
# 147 "/usr/include/sys/types.h" 3 4
# 1 "/usr/lib/gcc/i686-pc-linux-gnu/4.6.1/include/stddef.h" 1 3 4
# 212 "/usr/lib/gcc/i686-pc-linux-gnu/4.6.1/include/stddef.h" 3 4
typedef unsigned int size_t;
# 148 "/usr/include/sys/types.h" 2 3 4



typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;
# 195 "/usr/include/sys/types.h" 3 4
typedef int int8_t __attribute__ ((__mode__ (__QI__)));
typedef int int16_t __attribute__ ((__mode__ (__HI__)));
typedef int int32_t __attribute__ ((__mode__ (__SI__)));
typedef int int64_t __attribute__ ((__mode__ (__DI__)));


typedef unsigned int u_int8_t __attribute__ ((__mode__ (__QI__)));
typedef unsigned int u_int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int u_int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int u_int64_t __attribute__ ((__mode__ (__DI__)));

typedef int register_t __attribute__ ((__mode__ (__word__)));
# 217 "/usr/include/sys/types.h" 3 4
# 1 "/usr/include/endian.h" 1 3 4
# 37 "/usr/include/endian.h" 3 4
# 1 "/usr/include/bits/endian.h" 1 3 4
# 38 "/usr/include/endian.h" 2 3 4
# 61 "/usr/include/endian.h" 3 4
# 1 "/usr/include/bits/byteswap.h" 1 3 4
# 62 "/usr/include/endian.h" 2 3 4
# 218 "/usr/include/sys/types.h" 2 3 4


# 1 "/usr/include/sys/select.h" 1 3 4
# 31 "/usr/include/sys/select.h" 3 4
# 1 "/usr/include/bits/select.h" 1 3 4
# 32 "/usr/include/sys/select.h" 2 3 4


# 1 "/usr/include/bits/sigset.h" 1 3 4
# 24 "/usr/include/bits/sigset.h" 3 4
typedef int __sig_atomic_t;




typedef struct
  {
    unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
  } __sigset_t;
# 35 "/usr/include/sys/select.h" 2 3 4



typedef __sigset_t sigset_t;





# 1 "/usr/include/time.h" 1 3 4
# 120 "/usr/include/time.h" 3 4
struct timespec
  {
    __time_t tv_sec;
    long int tv_nsec;
  };
# 45 "/usr/include/sys/select.h" 2 3 4

# 1 "/usr/include/bits/time.h" 1 3 4
# 31 "/usr/include/bits/time.h" 3 4
struct timeval
  {
    __time_t tv_sec;
    __suseconds_t tv_usec;
  };
# 47 "/usr/include/sys/select.h" 2 3 4


typedef __suseconds_t suseconds_t;





typedef long int __fd_mask;
# 67 "/usr/include/sys/select.h" 3 4
typedef struct
  {






    __fd_mask __fds_bits[1024 / (8 * (int) sizeof (__fd_mask))];


  } fd_set;






typedef __fd_mask fd_mask;
# 99 "/usr/include/sys/select.h" 3 4

# 109 "/usr/include/sys/select.h" 3 4
extern int select (int __nfds, fd_set *__restrict __readfds,
     fd_set *__restrict __writefds,
     fd_set *__restrict __exceptfds,
     struct timeval *__restrict __timeout);
# 121 "/usr/include/sys/select.h" 3 4
extern int pselect (int __nfds, fd_set *__restrict __readfds,
      fd_set *__restrict __writefds,
      fd_set *__restrict __exceptfds,
      const struct timespec *__restrict __timeout,
      const __sigset_t *__restrict __sigmask);



# 221 "/usr/include/sys/types.h" 2 3 4


# 1 "/usr/include/sys/sysmacros.h" 1 3 4
# 30 "/usr/include/sys/sysmacros.h" 3 4


__extension__
extern unsigned int gnu_dev_major (unsigned long long int __dev)
     __attribute__ ((__nothrow__));
__extension__
extern unsigned int gnu_dev_minor (unsigned long long int __dev)
     __attribute__ ((__nothrow__));
__extension__
extern unsigned long long int gnu_dev_makedev (unsigned int __major,
            unsigned int __minor)
     __attribute__ ((__nothrow__));
# 64 "/usr/include/sys/sysmacros.h" 3 4

# 224 "/usr/include/sys/types.h" 2 3 4





typedef __blksize_t blksize_t;






typedef __blkcnt_t blkcnt_t;



typedef __fsblkcnt_t fsblkcnt_t;



typedef __fsfilcnt_t fsfilcnt_t;
# 271 "/usr/include/sys/types.h" 3 4
# 1 "/usr/include/bits/pthreadtypes.h" 1 3 4
# 36 "/usr/include/bits/pthreadtypes.h" 3 4
typedef unsigned long int pthread_t;


typedef union
{
  char __size[36];
  long int __align;
} pthread_attr_t;


typedef struct __pthread_internal_slist
{
  struct __pthread_internal_slist *__next;
} __pthread_slist_t;




typedef union
{
  struct __pthread_mutex_s
  {
    int __lock;
    unsigned int __count;
    int __owner;


    int __kind;
    unsigned int __nusers;
    __extension__ union
    {
      int __spins;
      __pthread_slist_t __list;
    };
  } __data;
  char __size[24];
  long int __align;
} pthread_mutex_t;

typedef union
{
  char __size[4];
  long int __align;
} pthread_mutexattr_t;




typedef union
{
  struct
  {
    int __lock;
    unsigned int __futex;
    __extension__ unsigned long long int __total_seq;
    __extension__ unsigned long long int __wakeup_seq;
    __extension__ unsigned long long int __woken_seq;
    void *__mutex;
    unsigned int __nwaiters;
    unsigned int __broadcast_seq;
  } __data;
  char __size[48];
  __extension__ long long int __align;
} pthread_cond_t;

typedef union
{
  char __size[4];
  long int __align;
} pthread_condattr_t;



typedef unsigned int pthread_key_t;



typedef int pthread_once_t;





typedef union
{
  struct
  {
    int __lock;
    unsigned int __nr_readers;
    unsigned int __readers_wakeup;
    unsigned int __writer_wakeup;
    unsigned int __nr_readers_queued;
    unsigned int __nr_writers_queued;


    unsigned char __flags;
    unsigned char __shared;
    unsigned char __pad1;
    unsigned char __pad2;
    int __writer;
  } __data;
  char __size[32];
  long int __align;
} pthread_rwlock_t;

typedef union
{
  char __size[8];
  long int __align;
} pthread_rwlockattr_t;





typedef volatile int pthread_spinlock_t;




typedef union
{
  char __size[20];
  long int __align;
} pthread_barrier_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_barrierattr_t;
# 272 "/usr/include/sys/types.h" 2 3 4



# 38 "<stdin>" 2
# 1 "/usr/include/sys/time.h" 1 3 4
# 27 "/usr/include/sys/time.h" 3 4
# 1 "/usr/include/time.h" 1 3 4
# 28 "/usr/include/sys/time.h" 2 3 4

# 1 "/usr/include/bits/time.h" 1 3 4
# 30 "/usr/include/sys/time.h" 2 3 4
# 39 "/usr/include/sys/time.h" 3 4

# 57 "/usr/include/sys/time.h" 3 4
struct timezone
  {
    int tz_minuteswest;
    int tz_dsttime;
  };

typedef struct timezone *__restrict __timezone_ptr_t;
# 73 "/usr/include/sys/time.h" 3 4
extern int gettimeofday (struct timeval *__restrict __tv,
    __timezone_ptr_t __tz) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));




extern int settimeofday (__const struct timeval *__tv,
    __const struct timezone *__tz)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));





extern int adjtime (__const struct timeval *__delta,
      struct timeval *__olddelta) __attribute__ ((__nothrow__));




enum __itimer_which
  {

    ITIMER_REAL = 0,


    ITIMER_VIRTUAL = 1,



    ITIMER_PROF = 2

  };



struct itimerval
  {

    struct timeval it_interval;

    struct timeval it_value;
  };






typedef int __itimer_which_t;




extern int getitimer (__itimer_which_t __which,
        struct itimerval *__value) __attribute__ ((__nothrow__));




extern int setitimer (__itimer_which_t __which,
        __const struct itimerval *__restrict __new,
        struct itimerval *__restrict __old) __attribute__ ((__nothrow__));




extern int utimes (__const char *__file, __const struct timeval __tvp[2])
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));



extern int lutimes (__const char *__file, __const struct timeval __tvp[2])
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int futimes (int __fd, __const struct timeval __tvp[2]) __attribute__ ((__nothrow__));
# 191 "/usr/include/sys/time.h" 3 4

# 39 "<stdin>" 2
# 1 "/usr/include/unistd.h" 1 3 4
# 28 "/usr/include/unistd.h" 3 4

# 203 "/usr/include/unistd.h" 3 4
# 1 "/usr/include/bits/posix_opt.h" 1 3 4
# 204 "/usr/include/unistd.h" 2 3 4



# 1 "/usr/include/bits/environments.h" 1 3 4
# 208 "/usr/include/unistd.h" 2 3 4
# 227 "/usr/include/unistd.h" 3 4
# 1 "/usr/lib/gcc/i686-pc-linux-gnu/4.6.1/include/stddef.h" 1 3 4
# 228 "/usr/include/unistd.h" 2 3 4
# 256 "/usr/include/unistd.h" 3 4
typedef __useconds_t useconds_t;
# 268 "/usr/include/unistd.h" 3 4
typedef __intptr_t intptr_t;






typedef __socklen_t socklen_t;
# 288 "/usr/include/unistd.h" 3 4
extern int access (__const char *__name, int __type) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
# 305 "/usr/include/unistd.h" 3 4
extern int faccessat (int __fd, __const char *__file, int __type, int __flag)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2))) ;
# 331 "/usr/include/unistd.h" 3 4
extern __off_t lseek (int __fd, __off_t __offset, int __whence) __attribute__ ((__nothrow__));
# 350 "/usr/include/unistd.h" 3 4
extern int close (int __fd);






extern ssize_t read (int __fd, void *__buf, size_t __nbytes) ;





extern ssize_t write (int __fd, __const void *__buf, size_t __n) ;
# 373 "/usr/include/unistd.h" 3 4
extern ssize_t pread (int __fd, void *__buf, size_t __nbytes,
        __off_t __offset) ;






extern ssize_t pwrite (int __fd, __const void *__buf, size_t __n,
         __off_t __offset) ;
# 414 "/usr/include/unistd.h" 3 4
extern int pipe (int __pipedes[2]) __attribute__ ((__nothrow__)) ;
# 429 "/usr/include/unistd.h" 3 4
extern unsigned int alarm (unsigned int __seconds) __attribute__ ((__nothrow__));
# 441 "/usr/include/unistd.h" 3 4
extern unsigned int sleep (unsigned int __seconds);







extern __useconds_t ualarm (__useconds_t __value, __useconds_t __interval)
     __attribute__ ((__nothrow__));






extern int usleep (__useconds_t __useconds);
# 466 "/usr/include/unistd.h" 3 4
extern int pause (void);



extern int chown (__const char *__file, __uid_t __owner, __gid_t __group)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;



extern int fchown (int __fd, __uid_t __owner, __gid_t __group) __attribute__ ((__nothrow__)) ;




extern int lchown (__const char *__file, __uid_t __owner, __gid_t __group)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;






extern int fchownat (int __fd, __const char *__file, __uid_t __owner,
       __gid_t __group, int __flag)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2))) ;



extern int chdir (__const char *__path) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;



extern int fchdir (int __fd) __attribute__ ((__nothrow__)) ;
# 508 "/usr/include/unistd.h" 3 4
extern char *getcwd (char *__buf, size_t __size) __attribute__ ((__nothrow__)) ;
# 522 "/usr/include/unistd.h" 3 4
extern char *getwd (char *__buf)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__deprecated__)) ;




extern int dup (int __fd) __attribute__ ((__nothrow__)) ;


extern int dup2 (int __fd, int __fd2) __attribute__ ((__nothrow__));
# 540 "/usr/include/unistd.h" 3 4
extern char **__environ;







extern int execve (__const char *__path, char *__const __argv[],
     char *__const __envp[]) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));




extern int fexecve (int __fd, char *__const __argv[], char *__const __envp[])
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2)));




extern int execv (__const char *__path, char *__const __argv[])
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));



extern int execle (__const char *__path, __const char *__arg, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));



extern int execl (__const char *__path, __const char *__arg, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));



extern int execvp (__const char *__file, char *__const __argv[])
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));




extern int execlp (__const char *__file, __const char *__arg, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
# 595 "/usr/include/unistd.h" 3 4
extern int nice (int __inc) __attribute__ ((__nothrow__)) ;




extern void _exit (int __status) __attribute__ ((__noreturn__));





# 1 "/usr/include/bits/confname.h" 1 3 4
# 26 "/usr/include/bits/confname.h" 3 4
enum
  {
    _PC_LINK_MAX,

    _PC_MAX_CANON,

    _PC_MAX_INPUT,

    _PC_NAME_MAX,

    _PC_PATH_MAX,

    _PC_PIPE_BUF,

    _PC_CHOWN_RESTRICTED,

    _PC_NO_TRUNC,

    _PC_VDISABLE,

    _PC_SYNC_IO,

    _PC_ASYNC_IO,

    _PC_PRIO_IO,

    _PC_SOCK_MAXBUF,

    _PC_FILESIZEBITS,

    _PC_REC_INCR_XFER_SIZE,

    _PC_REC_MAX_XFER_SIZE,

    _PC_REC_MIN_XFER_SIZE,

    _PC_REC_XFER_ALIGN,

    _PC_ALLOC_SIZE_MIN,

    _PC_SYMLINK_MAX,

    _PC_2_SYMLINKS

  };


enum
  {
    _SC_ARG_MAX,

    _SC_CHILD_MAX,

    _SC_CLK_TCK,

    _SC_NGROUPS_MAX,

    _SC_OPEN_MAX,

    _SC_STREAM_MAX,

    _SC_TZNAME_MAX,

    _SC_JOB_CONTROL,

    _SC_SAVED_IDS,

    _SC_REALTIME_SIGNALS,

    _SC_PRIORITY_SCHEDULING,

    _SC_TIMERS,

    _SC_ASYNCHRONOUS_IO,

    _SC_PRIORITIZED_IO,

    _SC_SYNCHRONIZED_IO,

    _SC_FSYNC,

    _SC_MAPPED_FILES,

    _SC_MEMLOCK,

    _SC_MEMLOCK_RANGE,

    _SC_MEMORY_PROTECTION,

    _SC_MESSAGE_PASSING,

    _SC_SEMAPHORES,

    _SC_SHARED_MEMORY_OBJECTS,

    _SC_AIO_LISTIO_MAX,

    _SC_AIO_MAX,

    _SC_AIO_PRIO_DELTA_MAX,

    _SC_DELAYTIMER_MAX,

    _SC_MQ_OPEN_MAX,

    _SC_MQ_PRIO_MAX,

    _SC_VERSION,

    _SC_PAGESIZE,


    _SC_RTSIG_MAX,

    _SC_SEM_NSEMS_MAX,

    _SC_SEM_VALUE_MAX,

    _SC_SIGQUEUE_MAX,

    _SC_TIMER_MAX,




    _SC_BC_BASE_MAX,

    _SC_BC_DIM_MAX,

    _SC_BC_SCALE_MAX,

    _SC_BC_STRING_MAX,

    _SC_COLL_WEIGHTS_MAX,

    _SC_EQUIV_CLASS_MAX,

    _SC_EXPR_NEST_MAX,

    _SC_LINE_MAX,

    _SC_RE_DUP_MAX,

    _SC_CHARCLASS_NAME_MAX,


    _SC_2_VERSION,

    _SC_2_C_BIND,

    _SC_2_C_DEV,

    _SC_2_FORT_DEV,

    _SC_2_FORT_RUN,

    _SC_2_SW_DEV,

    _SC_2_LOCALEDEF,


    _SC_PII,

    _SC_PII_XTI,

    _SC_PII_SOCKET,

    _SC_PII_INTERNET,

    _SC_PII_OSI,

    _SC_POLL,

    _SC_SELECT,

    _SC_UIO_MAXIOV,

    _SC_IOV_MAX = _SC_UIO_MAXIOV,

    _SC_PII_INTERNET_STREAM,

    _SC_PII_INTERNET_DGRAM,

    _SC_PII_OSI_COTS,

    _SC_PII_OSI_CLTS,

    _SC_PII_OSI_M,

    _SC_T_IOV_MAX,



    _SC_THREADS,

    _SC_THREAD_SAFE_FUNCTIONS,

    _SC_GETGR_R_SIZE_MAX,

    _SC_GETPW_R_SIZE_MAX,

    _SC_LOGIN_NAME_MAX,

    _SC_TTY_NAME_MAX,

    _SC_THREAD_DESTRUCTOR_ITERATIONS,

    _SC_THREAD_KEYS_MAX,

    _SC_THREAD_STACK_MIN,

    _SC_THREAD_THREADS_MAX,

    _SC_THREAD_ATTR_STACKADDR,

    _SC_THREAD_ATTR_STACKSIZE,

    _SC_THREAD_PRIORITY_SCHEDULING,

    _SC_THREAD_PRIO_INHERIT,

    _SC_THREAD_PRIO_PROTECT,

    _SC_THREAD_PROCESS_SHARED,


    _SC_NPROCESSORS_CONF,

    _SC_NPROCESSORS_ONLN,

    _SC_PHYS_PAGES,

    _SC_AVPHYS_PAGES,

    _SC_ATEXIT_MAX,

    _SC_PASS_MAX,


    _SC_XOPEN_VERSION,

    _SC_XOPEN_XCU_VERSION,

    _SC_XOPEN_UNIX,

    _SC_XOPEN_CRYPT,

    _SC_XOPEN_ENH_I18N,

    _SC_XOPEN_SHM,


    _SC_2_CHAR_TERM,

    _SC_2_C_VERSION,

    _SC_2_UPE,


    _SC_XOPEN_XPG2,

    _SC_XOPEN_XPG3,

    _SC_XOPEN_XPG4,


    _SC_CHAR_BIT,

    _SC_CHAR_MAX,

    _SC_CHAR_MIN,

    _SC_INT_MAX,

    _SC_INT_MIN,

    _SC_LONG_BIT,

    _SC_WORD_BIT,

    _SC_MB_LEN_MAX,

    _SC_NZERO,

    _SC_SSIZE_MAX,

    _SC_SCHAR_MAX,

    _SC_SCHAR_MIN,

    _SC_SHRT_MAX,

    _SC_SHRT_MIN,

    _SC_UCHAR_MAX,

    _SC_UINT_MAX,

    _SC_ULONG_MAX,

    _SC_USHRT_MAX,


    _SC_NL_ARGMAX,

    _SC_NL_LANGMAX,

    _SC_NL_MSGMAX,

    _SC_NL_NMAX,

    _SC_NL_SETMAX,

    _SC_NL_TEXTMAX,


    _SC_XBS5_ILP32_OFF32,

    _SC_XBS5_ILP32_OFFBIG,

    _SC_XBS5_LP64_OFF64,

    _SC_XBS5_LPBIG_OFFBIG,


    _SC_XOPEN_LEGACY,

    _SC_XOPEN_REALTIME,

    _SC_XOPEN_REALTIME_THREADS,


    _SC_ADVISORY_INFO,

    _SC_BARRIERS,

    _SC_BASE,

    _SC_C_LANG_SUPPORT,

    _SC_C_LANG_SUPPORT_R,

    _SC_CLOCK_SELECTION,

    _SC_CPUTIME,

    _SC_THREAD_CPUTIME,

    _SC_DEVICE_IO,

    _SC_DEVICE_SPECIFIC,

    _SC_DEVICE_SPECIFIC_R,

    _SC_FD_MGMT,

    _SC_FIFO,

    _SC_PIPE,

    _SC_FILE_ATTRIBUTES,

    _SC_FILE_LOCKING,

    _SC_FILE_SYSTEM,

    _SC_MONOTONIC_CLOCK,

    _SC_MULTI_PROCESS,

    _SC_SINGLE_PROCESS,

    _SC_NETWORKING,

    _SC_READER_WRITER_LOCKS,

    _SC_SPIN_LOCKS,

    _SC_REGEXP,

    _SC_REGEX_VERSION,

    _SC_SHELL,

    _SC_SIGNALS,

    _SC_SPAWN,

    _SC_SPORADIC_SERVER,

    _SC_THREAD_SPORADIC_SERVER,

    _SC_SYSTEM_DATABASE,

    _SC_SYSTEM_DATABASE_R,

    _SC_TIMEOUTS,

    _SC_TYPED_MEMORY_OBJECTS,

    _SC_USER_GROUPS,

    _SC_USER_GROUPS_R,

    _SC_2_PBS,

    _SC_2_PBS_ACCOUNTING,

    _SC_2_PBS_LOCATE,

    _SC_2_PBS_MESSAGE,

    _SC_2_PBS_TRACK,

    _SC_SYMLOOP_MAX,

    _SC_STREAMS,

    _SC_2_PBS_CHECKPOINT,


    _SC_V6_ILP32_OFF32,

    _SC_V6_ILP32_OFFBIG,

    _SC_V6_LP64_OFF64,

    _SC_V6_LPBIG_OFFBIG,


    _SC_HOST_NAME_MAX,

    _SC_TRACE,

    _SC_TRACE_EVENT_FILTER,

    _SC_TRACE_INHERIT,

    _SC_TRACE_LOG,


    _SC_LEVEL1_ICACHE_SIZE,

    _SC_LEVEL1_ICACHE_ASSOC,

    _SC_LEVEL1_ICACHE_LINESIZE,

    _SC_LEVEL1_DCACHE_SIZE,

    _SC_LEVEL1_DCACHE_ASSOC,

    _SC_LEVEL1_DCACHE_LINESIZE,

    _SC_LEVEL2_CACHE_SIZE,

    _SC_LEVEL2_CACHE_ASSOC,

    _SC_LEVEL2_CACHE_LINESIZE,

    _SC_LEVEL3_CACHE_SIZE,

    _SC_LEVEL3_CACHE_ASSOC,

    _SC_LEVEL3_CACHE_LINESIZE,

    _SC_LEVEL4_CACHE_SIZE,

    _SC_LEVEL4_CACHE_ASSOC,

    _SC_LEVEL4_CACHE_LINESIZE,



    _SC_IPV6 = _SC_LEVEL1_ICACHE_SIZE + 50,

    _SC_RAW_SOCKETS,


    _SC_V7_ILP32_OFF32,

    _SC_V7_ILP32_OFFBIG,

    _SC_V7_LP64_OFF64,

    _SC_V7_LPBIG_OFFBIG,


    _SC_SS_REPL_MAX,


    _SC_TRACE_EVENT_NAME_MAX,

    _SC_TRACE_NAME_MAX,

    _SC_TRACE_SYS_MAX,

    _SC_TRACE_USER_EVENT_MAX,


    _SC_XOPEN_STREAMS,


    _SC_THREAD_ROBUST_PRIO_INHERIT,

    _SC_THREAD_ROBUST_PRIO_PROTECT

  };


enum
  {
    _CS_PATH,


    _CS_V6_WIDTH_RESTRICTED_ENVS,



    _CS_GNU_LIBC_VERSION,

    _CS_GNU_LIBPTHREAD_VERSION,


    _CS_V5_WIDTH_RESTRICTED_ENVS,



    _CS_V7_WIDTH_RESTRICTED_ENVS,



    _CS_LFS_CFLAGS = 1000,

    _CS_LFS_LDFLAGS,

    _CS_LFS_LIBS,

    _CS_LFS_LINTFLAGS,

    _CS_LFS64_CFLAGS,

    _CS_LFS64_LDFLAGS,

    _CS_LFS64_LIBS,

    _CS_LFS64_LINTFLAGS,


    _CS_XBS5_ILP32_OFF32_CFLAGS = 1100,

    _CS_XBS5_ILP32_OFF32_LDFLAGS,

    _CS_XBS5_ILP32_OFF32_LIBS,

    _CS_XBS5_ILP32_OFF32_LINTFLAGS,

    _CS_XBS5_ILP32_OFFBIG_CFLAGS,

    _CS_XBS5_ILP32_OFFBIG_LDFLAGS,

    _CS_XBS5_ILP32_OFFBIG_LIBS,

    _CS_XBS5_ILP32_OFFBIG_LINTFLAGS,

    _CS_XBS5_LP64_OFF64_CFLAGS,

    _CS_XBS5_LP64_OFF64_LDFLAGS,

    _CS_XBS5_LP64_OFF64_LIBS,

    _CS_XBS5_LP64_OFF64_LINTFLAGS,

    _CS_XBS5_LPBIG_OFFBIG_CFLAGS,

    _CS_XBS5_LPBIG_OFFBIG_LDFLAGS,

    _CS_XBS5_LPBIG_OFFBIG_LIBS,

    _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS,


    _CS_POSIX_V6_ILP32_OFF32_CFLAGS,

    _CS_POSIX_V6_ILP32_OFF32_LDFLAGS,

    _CS_POSIX_V6_ILP32_OFF32_LIBS,

    _CS_POSIX_V6_ILP32_OFF32_LINTFLAGS,

    _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS,

    _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS,

    _CS_POSIX_V6_ILP32_OFFBIG_LIBS,

    _CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS,

    _CS_POSIX_V6_LP64_OFF64_CFLAGS,

    _CS_POSIX_V6_LP64_OFF64_LDFLAGS,

    _CS_POSIX_V6_LP64_OFF64_LIBS,

    _CS_POSIX_V6_LP64_OFF64_LINTFLAGS,

    _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS,

    _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS,

    _CS_POSIX_V6_LPBIG_OFFBIG_LIBS,

    _CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS,


    _CS_POSIX_V7_ILP32_OFF32_CFLAGS,

    _CS_POSIX_V7_ILP32_OFF32_LDFLAGS,

    _CS_POSIX_V7_ILP32_OFF32_LIBS,

    _CS_POSIX_V7_ILP32_OFF32_LINTFLAGS,

    _CS_POSIX_V7_ILP32_OFFBIG_CFLAGS,

    _CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS,

    _CS_POSIX_V7_ILP32_OFFBIG_LIBS,

    _CS_POSIX_V7_ILP32_OFFBIG_LINTFLAGS,

    _CS_POSIX_V7_LP64_OFF64_CFLAGS,

    _CS_POSIX_V7_LP64_OFF64_LDFLAGS,

    _CS_POSIX_V7_LP64_OFF64_LIBS,

    _CS_POSIX_V7_LP64_OFF64_LINTFLAGS,

    _CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS,

    _CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS,

    _CS_POSIX_V7_LPBIG_OFFBIG_LIBS,

    _CS_POSIX_V7_LPBIG_OFFBIG_LINTFLAGS,


    _CS_V6_ENV,

    _CS_V7_ENV

  };
# 607 "/usr/include/unistd.h" 2 3 4


extern long int pathconf (__const char *__path, int __name)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern long int fpathconf (int __fd, int __name) __attribute__ ((__nothrow__));


extern long int sysconf (int __name) __attribute__ ((__nothrow__));



extern size_t confstr (int __name, char *__buf, size_t __len) __attribute__ ((__nothrow__));




extern __pid_t getpid (void) __attribute__ ((__nothrow__));


extern __pid_t getppid (void) __attribute__ ((__nothrow__));




extern __pid_t getpgrp (void) __attribute__ ((__nothrow__));
# 643 "/usr/include/unistd.h" 3 4
extern __pid_t __getpgid (__pid_t __pid) __attribute__ ((__nothrow__));

extern __pid_t getpgid (__pid_t __pid) __attribute__ ((__nothrow__));






extern int setpgid (__pid_t __pid, __pid_t __pgid) __attribute__ ((__nothrow__));
# 669 "/usr/include/unistd.h" 3 4
extern int setpgrp (void) __attribute__ ((__nothrow__));
# 686 "/usr/include/unistd.h" 3 4
extern __pid_t setsid (void) __attribute__ ((__nothrow__));



extern __pid_t getsid (__pid_t __pid) __attribute__ ((__nothrow__));



extern __uid_t getuid (void) __attribute__ ((__nothrow__));


extern __uid_t geteuid (void) __attribute__ ((__nothrow__));


extern __gid_t getgid (void) __attribute__ ((__nothrow__));


extern __gid_t getegid (void) __attribute__ ((__nothrow__));




extern int getgroups (int __size, __gid_t __list[]) __attribute__ ((__nothrow__)) ;
# 719 "/usr/include/unistd.h" 3 4
extern int setuid (__uid_t __uid) __attribute__ ((__nothrow__));




extern int setreuid (__uid_t __ruid, __uid_t __euid) __attribute__ ((__nothrow__));




extern int seteuid (__uid_t __uid) __attribute__ ((__nothrow__));






extern int setgid (__gid_t __gid) __attribute__ ((__nothrow__));




extern int setregid (__gid_t __rgid, __gid_t __egid) __attribute__ ((__nothrow__));




extern int setegid (__gid_t __gid) __attribute__ ((__nothrow__));
# 775 "/usr/include/unistd.h" 3 4
extern __pid_t fork (void) __attribute__ ((__nothrow__));







extern __pid_t vfork (void) __attribute__ ((__nothrow__));





extern char *ttyname (int __fd) __attribute__ ((__nothrow__));



extern int ttyname_r (int __fd, char *__buf, size_t __buflen)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2))) ;



extern int isatty (int __fd) __attribute__ ((__nothrow__));





extern int ttyslot (void) __attribute__ ((__nothrow__));




extern int link (__const char *__from, __const char *__to)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2))) ;




extern int linkat (int __fromfd, __const char *__from, int __tofd,
     __const char *__to, int __flags)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2, 4))) ;




extern int symlink (__const char *__from, __const char *__to)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2))) ;




extern ssize_t readlink (__const char *__restrict __path,
    char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2))) ;




extern int symlinkat (__const char *__from, int __tofd,
        __const char *__to) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 3))) ;


extern ssize_t readlinkat (int __fd, __const char *__restrict __path,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2, 3))) ;



extern int unlink (__const char *__name) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));



extern int unlinkat (int __fd, __const char *__name, int __flag)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2)));



extern int rmdir (__const char *__path) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));



extern __pid_t tcgetpgrp (int __fd) __attribute__ ((__nothrow__));


extern int tcsetpgrp (int __fd, __pid_t __pgrp_id) __attribute__ ((__nothrow__));






extern char *getlogin (void);







extern int getlogin_r (char *__name, size_t __name_len) __attribute__ ((__nonnull__ (1)));




extern int setlogin (__const char *__name) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
# 890 "/usr/include/unistd.h" 3 4
# 1 "/usr/include/getopt.h" 1 3 4
# 59 "/usr/include/getopt.h" 3 4
extern char *optarg;
# 73 "/usr/include/getopt.h" 3 4
extern int optind;




extern int opterr;



extern int optopt;
# 152 "/usr/include/getopt.h" 3 4
extern int getopt (int ___argc, char *const *___argv, const char *__shortopts)
       __attribute__ ((__nothrow__));
# 891 "/usr/include/unistd.h" 2 3 4







extern int gethostname (char *__name, size_t __len) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));






extern int sethostname (__const char *__name, size_t __len)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;



extern int sethostid (long int __id) __attribute__ ((__nothrow__)) ;





extern int getdomainname (char *__name, size_t __len)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;
extern int setdomainname (__const char *__name, size_t __len)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;





extern int vhangup (void) __attribute__ ((__nothrow__));


extern int revoke (__const char *__file) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;







extern int profil (unsigned short int *__sample_buffer, size_t __size,
     size_t __offset, unsigned int __scale)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));





extern int acct (__const char *__name) __attribute__ ((__nothrow__));



extern char *getusershell (void) __attribute__ ((__nothrow__));
extern void endusershell (void) __attribute__ ((__nothrow__));
extern void setusershell (void) __attribute__ ((__nothrow__));





extern int daemon (int __nochdir, int __noclose) __attribute__ ((__nothrow__)) ;






extern int chroot (__const char *__path) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;



extern char *getpass (__const char *__prompt) __attribute__ ((__nonnull__ (1)));
# 976 "/usr/include/unistd.h" 3 4
extern int fsync (int __fd);
# 990 "/usr/include/unistd.h" 3 4
extern long int gethostid (void);


extern void sync (void) __attribute__ ((__nothrow__));





extern int getpagesize (void) __attribute__ ((__nothrow__)) __attribute__ ((__const__));




extern int getdtablesize (void) __attribute__ ((__nothrow__));
# 1014 "/usr/include/unistd.h" 3 4
extern int truncate (__const char *__file, __off_t __length)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;
# 1036 "/usr/include/unistd.h" 3 4
extern int ftruncate (int __fd, __off_t __length) __attribute__ ((__nothrow__)) ;
# 1057 "/usr/include/unistd.h" 3 4
extern int brk (void *__addr) __attribute__ ((__nothrow__)) ;





extern void *sbrk (intptr_t __delta) __attribute__ ((__nothrow__));
# 1078 "/usr/include/unistd.h" 3 4
extern long int syscall (long int __sysno, ...) __attribute__ ((__nothrow__));
# 1101 "/usr/include/unistd.h" 3 4
extern int lockf (int __fd, int __cmd, __off_t __len) ;
# 1132 "/usr/include/unistd.h" 3 4
extern int fdatasync (int __fildes);
# 1161 "/usr/include/unistd.h" 3 4
extern char *ctermid (char *__s) __attribute__ ((__nothrow__));
# 1170 "/usr/include/unistd.h" 3 4

# 40 "<stdin>" 2


# 1 "/usr/include/math.h" 1 3 4
# 30 "/usr/include/math.h" 3 4




# 1 "/usr/include/bits/huge_val.h" 1 3 4
# 35 "/usr/include/math.h" 2 3 4

# 1 "/usr/include/bits/huge_valf.h" 1 3 4
# 37 "/usr/include/math.h" 2 3 4
# 1 "/usr/include/bits/huge_vall.h" 1 3 4
# 38 "/usr/include/math.h" 2 3 4


# 1 "/usr/include/bits/inf.h" 1 3 4
# 41 "/usr/include/math.h" 2 3 4


# 1 "/usr/include/bits/nan.h" 1 3 4
# 44 "/usr/include/math.h" 2 3 4



# 1 "/usr/include/bits/mathdef.h" 1 3 4
# 36 "/usr/include/bits/mathdef.h" 3 4
typedef long double float_t;

typedef long double double_t;
# 48 "/usr/include/math.h" 2 3 4
# 71 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls.h" 1 3 4
# 53 "/usr/include/bits/mathcalls.h" 3 4


extern double acos (double __x) __attribute__ ((__nothrow__)); extern double __acos (double __x) __attribute__ ((__nothrow__));

extern double asin (double __x) __attribute__ ((__nothrow__)); extern double __asin (double __x) __attribute__ ((__nothrow__));

extern double atan (double __x) __attribute__ ((__nothrow__)); extern double __atan (double __x) __attribute__ ((__nothrow__));

extern double atan2 (double __y, double __x) __attribute__ ((__nothrow__)); extern double __atan2 (double __y, double __x) __attribute__ ((__nothrow__));


extern double cos (double __x) __attribute__ ((__nothrow__)); extern double __cos (double __x) __attribute__ ((__nothrow__));

extern double sin (double __x) __attribute__ ((__nothrow__)); extern double __sin (double __x) __attribute__ ((__nothrow__));

extern double tan (double __x) __attribute__ ((__nothrow__)); extern double __tan (double __x) __attribute__ ((__nothrow__));




extern double cosh (double __x) __attribute__ ((__nothrow__)); extern double __cosh (double __x) __attribute__ ((__nothrow__));

extern double sinh (double __x) __attribute__ ((__nothrow__)); extern double __sinh (double __x) __attribute__ ((__nothrow__));

extern double tanh (double __x) __attribute__ ((__nothrow__)); extern double __tanh (double __x) __attribute__ ((__nothrow__));

# 87 "/usr/include/bits/mathcalls.h" 3 4


extern double acosh (double __x) __attribute__ ((__nothrow__)); extern double __acosh (double __x) __attribute__ ((__nothrow__));

extern double asinh (double __x) __attribute__ ((__nothrow__)); extern double __asinh (double __x) __attribute__ ((__nothrow__));

extern double atanh (double __x) __attribute__ ((__nothrow__)); extern double __atanh (double __x) __attribute__ ((__nothrow__));







extern double exp (double __x) __attribute__ ((__nothrow__)); extern double __exp (double __x) __attribute__ ((__nothrow__));


extern double frexp (double __x, int *__exponent) __attribute__ ((__nothrow__)); extern double __frexp (double __x, int *__exponent) __attribute__ ((__nothrow__));


extern double ldexp (double __x, int __exponent) __attribute__ ((__nothrow__)); extern double __ldexp (double __x, int __exponent) __attribute__ ((__nothrow__));


extern double log (double __x) __attribute__ ((__nothrow__)); extern double __log (double __x) __attribute__ ((__nothrow__));


extern double log10 (double __x) __attribute__ ((__nothrow__)); extern double __log10 (double __x) __attribute__ ((__nothrow__));


extern double modf (double __x, double *__iptr) __attribute__ ((__nothrow__)); extern double __modf (double __x, double *__iptr) __attribute__ ((__nothrow__));

# 127 "/usr/include/bits/mathcalls.h" 3 4


extern double expm1 (double __x) __attribute__ ((__nothrow__)); extern double __expm1 (double __x) __attribute__ ((__nothrow__));


extern double log1p (double __x) __attribute__ ((__nothrow__)); extern double __log1p (double __x) __attribute__ ((__nothrow__));


extern double logb (double __x) __attribute__ ((__nothrow__)); extern double __logb (double __x) __attribute__ ((__nothrow__));






extern double exp2 (double __x) __attribute__ ((__nothrow__)); extern double __exp2 (double __x) __attribute__ ((__nothrow__));


extern double log2 (double __x) __attribute__ ((__nothrow__)); extern double __log2 (double __x) __attribute__ ((__nothrow__));








extern double pow (double __x, double __y) __attribute__ ((__nothrow__)); extern double __pow (double __x, double __y) __attribute__ ((__nothrow__));


extern double sqrt (double __x) __attribute__ ((__nothrow__)); extern double __sqrt (double __x) __attribute__ ((__nothrow__));





extern double hypot (double __x, double __y) __attribute__ ((__nothrow__)); extern double __hypot (double __x, double __y) __attribute__ ((__nothrow__));






extern double cbrt (double __x) __attribute__ ((__nothrow__)); extern double __cbrt (double __x) __attribute__ ((__nothrow__));








extern double ceil (double __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__)); extern double __ceil (double __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__));


extern double fabs (double __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__)); extern double __fabs (double __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__));


extern double floor (double __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__)); extern double __floor (double __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__));


extern double fmod (double __x, double __y) __attribute__ ((__nothrow__)); extern double __fmod (double __x, double __y) __attribute__ ((__nothrow__));




extern int __isinf (double __value) __attribute__ ((__nothrow__)) __attribute__ ((__const__));


extern int __finite (double __value) __attribute__ ((__nothrow__)) __attribute__ ((__const__));





extern int isinf (double __value) __attribute__ ((__nothrow__)) __attribute__ ((__const__));


extern int finite (double __value) __attribute__ ((__nothrow__)) __attribute__ ((__const__));


extern double drem (double __x, double __y) __attribute__ ((__nothrow__)); extern double __drem (double __x, double __y) __attribute__ ((__nothrow__));



extern double significand (double __x) __attribute__ ((__nothrow__)); extern double __significand (double __x) __attribute__ ((__nothrow__));





extern double copysign (double __x, double __y) __attribute__ ((__nothrow__)) __attribute__ ((__const__)); extern double __copysign (double __x, double __y) __attribute__ ((__nothrow__)) __attribute__ ((__const__));






extern double nan (__const char *__tagb) __attribute__ ((__nothrow__)) __attribute__ ((__const__)); extern double __nan (__const char *__tagb) __attribute__ ((__nothrow__)) __attribute__ ((__const__));





extern int __isnan (double __value) __attribute__ ((__nothrow__)) __attribute__ ((__const__));



extern int isnan (double __value) __attribute__ ((__nothrow__)) __attribute__ ((__const__));


extern double j0 (double) __attribute__ ((__nothrow__)); extern double __j0 (double) __attribute__ ((__nothrow__));
extern double j1 (double) __attribute__ ((__nothrow__)); extern double __j1 (double) __attribute__ ((__nothrow__));
extern double jn (int, double) __attribute__ ((__nothrow__)); extern double __jn (int, double) __attribute__ ((__nothrow__));
extern double y0 (double) __attribute__ ((__nothrow__)); extern double __y0 (double) __attribute__ ((__nothrow__));
extern double y1 (double) __attribute__ ((__nothrow__)); extern double __y1 (double) __attribute__ ((__nothrow__));
extern double yn (int, double) __attribute__ ((__nothrow__)); extern double __yn (int, double) __attribute__ ((__nothrow__));






extern double erf (double) __attribute__ ((__nothrow__)); extern double __erf (double) __attribute__ ((__nothrow__));
extern double erfc (double) __attribute__ ((__nothrow__)); extern double __erfc (double) __attribute__ ((__nothrow__));
extern double lgamma (double) __attribute__ ((__nothrow__)); extern double __lgamma (double) __attribute__ ((__nothrow__));






extern double tgamma (double) __attribute__ ((__nothrow__)); extern double __tgamma (double) __attribute__ ((__nothrow__));





extern double gamma (double) __attribute__ ((__nothrow__)); extern double __gamma (double) __attribute__ ((__nothrow__));






extern double lgamma_r (double, int *__signgamp) __attribute__ ((__nothrow__)); extern double __lgamma_r (double, int *__signgamp) __attribute__ ((__nothrow__));







extern double rint (double __x) __attribute__ ((__nothrow__)); extern double __rint (double __x) __attribute__ ((__nothrow__));


extern double nextafter (double __x, double __y) __attribute__ ((__nothrow__)) __attribute__ ((__const__)); extern double __nextafter (double __x, double __y) __attribute__ ((__nothrow__)) __attribute__ ((__const__));

extern double nexttoward (double __x, long double __y) __attribute__ ((__nothrow__)) __attribute__ ((__const__)); extern double __nexttoward (double __x, long double __y) __attribute__ ((__nothrow__)) __attribute__ ((__const__));



extern double remainder (double __x, double __y) __attribute__ ((__nothrow__)); extern double __remainder (double __x, double __y) __attribute__ ((__nothrow__));



extern double scalbn (double __x, int __n) __attribute__ ((__nothrow__)); extern double __scalbn (double __x, int __n) __attribute__ ((__nothrow__));



extern int ilogb (double __x) __attribute__ ((__nothrow__)); extern int __ilogb (double __x) __attribute__ ((__nothrow__));




extern double scalbln (double __x, long int __n) __attribute__ ((__nothrow__)); extern double __scalbln (double __x, long int __n) __attribute__ ((__nothrow__));



extern double nearbyint (double __x) __attribute__ ((__nothrow__)); extern double __nearbyint (double __x) __attribute__ ((__nothrow__));



extern double round (double __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__)); extern double __round (double __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__));



extern double trunc (double __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__)); extern double __trunc (double __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__));




extern double remquo (double __x, double __y, int *__quo) __attribute__ ((__nothrow__)); extern double __remquo (double __x, double __y, int *__quo) __attribute__ ((__nothrow__));






extern long int lrint (double __x) __attribute__ ((__nothrow__)); extern long int __lrint (double __x) __attribute__ ((__nothrow__));
extern long long int llrint (double __x) __attribute__ ((__nothrow__)); extern long long int __llrint (double __x) __attribute__ ((__nothrow__));



extern long int lround (double __x) __attribute__ ((__nothrow__)); extern long int __lround (double __x) __attribute__ ((__nothrow__));
extern long long int llround (double __x) __attribute__ ((__nothrow__)); extern long long int __llround (double __x) __attribute__ ((__nothrow__));



extern double fdim (double __x, double __y) __attribute__ ((__nothrow__)); extern double __fdim (double __x, double __y) __attribute__ ((__nothrow__));


extern double fmax (double __x, double __y) __attribute__ ((__nothrow__)); extern double __fmax (double __x, double __y) __attribute__ ((__nothrow__));


extern double fmin (double __x, double __y) __attribute__ ((__nothrow__)); extern double __fmin (double __x, double __y) __attribute__ ((__nothrow__));



extern int __fpclassify (double __value) __attribute__ ((__nothrow__))
     __attribute__ ((__const__));


extern int __signbit (double __value) __attribute__ ((__nothrow__))
     __attribute__ ((__const__));



extern double fma (double __x, double __y, double __z) __attribute__ ((__nothrow__)); extern double __fma (double __x, double __y, double __z) __attribute__ ((__nothrow__));








extern double scalb (double __x, double __n) __attribute__ ((__nothrow__)); extern double __scalb (double __x, double __n) __attribute__ ((__nothrow__));
# 72 "/usr/include/math.h" 2 3 4
# 94 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls.h" 1 3 4
# 53 "/usr/include/bits/mathcalls.h" 3 4


extern float acosf (float __x) __attribute__ ((__nothrow__)); extern float __acosf (float __x) __attribute__ ((__nothrow__));

extern float asinf (float __x) __attribute__ ((__nothrow__)); extern float __asinf (float __x) __attribute__ ((__nothrow__));

extern float atanf (float __x) __attribute__ ((__nothrow__)); extern float __atanf (float __x) __attribute__ ((__nothrow__));

extern float atan2f (float __y, float __x) __attribute__ ((__nothrow__)); extern float __atan2f (float __y, float __x) __attribute__ ((__nothrow__));


extern float cosf (float __x) __attribute__ ((__nothrow__)); extern float __cosf (float __x) __attribute__ ((__nothrow__));

extern float sinf (float __x) __attribute__ ((__nothrow__)); extern float __sinf (float __x) __attribute__ ((__nothrow__));

extern float tanf (float __x) __attribute__ ((__nothrow__)); extern float __tanf (float __x) __attribute__ ((__nothrow__));




extern float coshf (float __x) __attribute__ ((__nothrow__)); extern float __coshf (float __x) __attribute__ ((__nothrow__));

extern float sinhf (float __x) __attribute__ ((__nothrow__)); extern float __sinhf (float __x) __attribute__ ((__nothrow__));

extern float tanhf (float __x) __attribute__ ((__nothrow__)); extern float __tanhf (float __x) __attribute__ ((__nothrow__));

# 87 "/usr/include/bits/mathcalls.h" 3 4


extern float acoshf (float __x) __attribute__ ((__nothrow__)); extern float __acoshf (float __x) __attribute__ ((__nothrow__));

extern float asinhf (float __x) __attribute__ ((__nothrow__)); extern float __asinhf (float __x) __attribute__ ((__nothrow__));

extern float atanhf (float __x) __attribute__ ((__nothrow__)); extern float __atanhf (float __x) __attribute__ ((__nothrow__));







extern float expf (float __x) __attribute__ ((__nothrow__)); extern float __expf (float __x) __attribute__ ((__nothrow__));


extern float frexpf (float __x, int *__exponent) __attribute__ ((__nothrow__)); extern float __frexpf (float __x, int *__exponent) __attribute__ ((__nothrow__));


extern float ldexpf (float __x, int __exponent) __attribute__ ((__nothrow__)); extern float __ldexpf (float __x, int __exponent) __attribute__ ((__nothrow__));


extern float logf (float __x) __attribute__ ((__nothrow__)); extern float __logf (float __x) __attribute__ ((__nothrow__));


extern float log10f (float __x) __attribute__ ((__nothrow__)); extern float __log10f (float __x) __attribute__ ((__nothrow__));


extern float modff (float __x, float *__iptr) __attribute__ ((__nothrow__)); extern float __modff (float __x, float *__iptr) __attribute__ ((__nothrow__));

# 127 "/usr/include/bits/mathcalls.h" 3 4


extern float expm1f (float __x) __attribute__ ((__nothrow__)); extern float __expm1f (float __x) __attribute__ ((__nothrow__));


extern float log1pf (float __x) __attribute__ ((__nothrow__)); extern float __log1pf (float __x) __attribute__ ((__nothrow__));


extern float logbf (float __x) __attribute__ ((__nothrow__)); extern float __logbf (float __x) __attribute__ ((__nothrow__));






extern float exp2f (float __x) __attribute__ ((__nothrow__)); extern float __exp2f (float __x) __attribute__ ((__nothrow__));


extern float log2f (float __x) __attribute__ ((__nothrow__)); extern float __log2f (float __x) __attribute__ ((__nothrow__));








extern float powf (float __x, float __y) __attribute__ ((__nothrow__)); extern float __powf (float __x, float __y) __attribute__ ((__nothrow__));


extern float sqrtf (float __x) __attribute__ ((__nothrow__)); extern float __sqrtf (float __x) __attribute__ ((__nothrow__));





extern float hypotf (float __x, float __y) __attribute__ ((__nothrow__)); extern float __hypotf (float __x, float __y) __attribute__ ((__nothrow__));






extern float cbrtf (float __x) __attribute__ ((__nothrow__)); extern float __cbrtf (float __x) __attribute__ ((__nothrow__));








extern float ceilf (float __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__)); extern float __ceilf (float __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__));


extern float fabsf (float __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__)); extern float __fabsf (float __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__));


extern float floorf (float __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__)); extern float __floorf (float __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__));


extern float fmodf (float __x, float __y) __attribute__ ((__nothrow__)); extern float __fmodf (float __x, float __y) __attribute__ ((__nothrow__));




extern int __isinff (float __value) __attribute__ ((__nothrow__)) __attribute__ ((__const__));


extern int __finitef (float __value) __attribute__ ((__nothrow__)) __attribute__ ((__const__));





extern int isinff (float __value) __attribute__ ((__nothrow__)) __attribute__ ((__const__));


extern int finitef (float __value) __attribute__ ((__nothrow__)) __attribute__ ((__const__));


extern float dremf (float __x, float __y) __attribute__ ((__nothrow__)); extern float __dremf (float __x, float __y) __attribute__ ((__nothrow__));



extern float significandf (float __x) __attribute__ ((__nothrow__)); extern float __significandf (float __x) __attribute__ ((__nothrow__));





extern float copysignf (float __x, float __y) __attribute__ ((__nothrow__)) __attribute__ ((__const__)); extern float __copysignf (float __x, float __y) __attribute__ ((__nothrow__)) __attribute__ ((__const__));






extern float nanf (__const char *__tagb) __attribute__ ((__nothrow__)) __attribute__ ((__const__)); extern float __nanf (__const char *__tagb) __attribute__ ((__nothrow__)) __attribute__ ((__const__));





extern int __isnanf (float __value) __attribute__ ((__nothrow__)) __attribute__ ((__const__));



extern int isnanf (float __value) __attribute__ ((__nothrow__)) __attribute__ ((__const__));


extern float j0f (float) __attribute__ ((__nothrow__)); extern float __j0f (float) __attribute__ ((__nothrow__));
extern float j1f (float) __attribute__ ((__nothrow__)); extern float __j1f (float) __attribute__ ((__nothrow__));
extern float jnf (int, float) __attribute__ ((__nothrow__)); extern float __jnf (int, float) __attribute__ ((__nothrow__));
extern float y0f (float) __attribute__ ((__nothrow__)); extern float __y0f (float) __attribute__ ((__nothrow__));
extern float y1f (float) __attribute__ ((__nothrow__)); extern float __y1f (float) __attribute__ ((__nothrow__));
extern float ynf (int, float) __attribute__ ((__nothrow__)); extern float __ynf (int, float) __attribute__ ((__nothrow__));






extern float erff (float) __attribute__ ((__nothrow__)); extern float __erff (float) __attribute__ ((__nothrow__));
extern float erfcf (float) __attribute__ ((__nothrow__)); extern float __erfcf (float) __attribute__ ((__nothrow__));
extern float lgammaf (float) __attribute__ ((__nothrow__)); extern float __lgammaf (float) __attribute__ ((__nothrow__));






extern float tgammaf (float) __attribute__ ((__nothrow__)); extern float __tgammaf (float) __attribute__ ((__nothrow__));





extern float gammaf (float) __attribute__ ((__nothrow__)); extern float __gammaf (float) __attribute__ ((__nothrow__));






extern float lgammaf_r (float, int *__signgamp) __attribute__ ((__nothrow__)); extern float __lgammaf_r (float, int *__signgamp) __attribute__ ((__nothrow__));







extern float rintf (float __x) __attribute__ ((__nothrow__)); extern float __rintf (float __x) __attribute__ ((__nothrow__));


extern float nextafterf (float __x, float __y) __attribute__ ((__nothrow__)) __attribute__ ((__const__)); extern float __nextafterf (float __x, float __y) __attribute__ ((__nothrow__)) __attribute__ ((__const__));

extern float nexttowardf (float __x, long double __y) __attribute__ ((__nothrow__)) __attribute__ ((__const__)); extern float __nexttowardf (float __x, long double __y) __attribute__ ((__nothrow__)) __attribute__ ((__const__));



extern float remainderf (float __x, float __y) __attribute__ ((__nothrow__)); extern float __remainderf (float __x, float __y) __attribute__ ((__nothrow__));



extern float scalbnf (float __x, int __n) __attribute__ ((__nothrow__)); extern float __scalbnf (float __x, int __n) __attribute__ ((__nothrow__));



extern int ilogbf (float __x) __attribute__ ((__nothrow__)); extern int __ilogbf (float __x) __attribute__ ((__nothrow__));




extern float scalblnf (float __x, long int __n) __attribute__ ((__nothrow__)); extern float __scalblnf (float __x, long int __n) __attribute__ ((__nothrow__));



extern float nearbyintf (float __x) __attribute__ ((__nothrow__)); extern float __nearbyintf (float __x) __attribute__ ((__nothrow__));



extern float roundf (float __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__)); extern float __roundf (float __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__));



extern float truncf (float __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__)); extern float __truncf (float __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__));




extern float remquof (float __x, float __y, int *__quo) __attribute__ ((__nothrow__)); extern float __remquof (float __x, float __y, int *__quo) __attribute__ ((__nothrow__));






extern long int lrintf (float __x) __attribute__ ((__nothrow__)); extern long int __lrintf (float __x) __attribute__ ((__nothrow__));
extern long long int llrintf (float __x) __attribute__ ((__nothrow__)); extern long long int __llrintf (float __x) __attribute__ ((__nothrow__));



extern long int lroundf (float __x) __attribute__ ((__nothrow__)); extern long int __lroundf (float __x) __attribute__ ((__nothrow__));
extern long long int llroundf (float __x) __attribute__ ((__nothrow__)); extern long long int __llroundf (float __x) __attribute__ ((__nothrow__));



extern float fdimf (float __x, float __y) __attribute__ ((__nothrow__)); extern float __fdimf (float __x, float __y) __attribute__ ((__nothrow__));


extern float fmaxf (float __x, float __y) __attribute__ ((__nothrow__)); extern float __fmaxf (float __x, float __y) __attribute__ ((__nothrow__));


extern float fminf (float __x, float __y) __attribute__ ((__nothrow__)); extern float __fminf (float __x, float __y) __attribute__ ((__nothrow__));



extern int __fpclassifyf (float __value) __attribute__ ((__nothrow__))
     __attribute__ ((__const__));


extern int __signbitf (float __value) __attribute__ ((__nothrow__))
     __attribute__ ((__const__));



extern float fmaf (float __x, float __y, float __z) __attribute__ ((__nothrow__)); extern float __fmaf (float __x, float __y, float __z) __attribute__ ((__nothrow__));








extern float scalbf (float __x, float __n) __attribute__ ((__nothrow__)); extern float __scalbf (float __x, float __n) __attribute__ ((__nothrow__));
# 95 "/usr/include/math.h" 2 3 4
# 141 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls.h" 1 3 4
# 53 "/usr/include/bits/mathcalls.h" 3 4


extern long double acosl (long double __x) __attribute__ ((__nothrow__)); extern long double __acosl (long double __x) __attribute__ ((__nothrow__));

extern long double asinl (long double __x) __attribute__ ((__nothrow__)); extern long double __asinl (long double __x) __attribute__ ((__nothrow__));

extern long double atanl (long double __x) __attribute__ ((__nothrow__)); extern long double __atanl (long double __x) __attribute__ ((__nothrow__));

extern long double atan2l (long double __y, long double __x) __attribute__ ((__nothrow__)); extern long double __atan2l (long double __y, long double __x) __attribute__ ((__nothrow__));


extern long double cosl (long double __x) __attribute__ ((__nothrow__)); extern long double __cosl (long double __x) __attribute__ ((__nothrow__));

extern long double sinl (long double __x) __attribute__ ((__nothrow__)); extern long double __sinl (long double __x) __attribute__ ((__nothrow__));

extern long double tanl (long double __x) __attribute__ ((__nothrow__)); extern long double __tanl (long double __x) __attribute__ ((__nothrow__));




extern long double coshl (long double __x) __attribute__ ((__nothrow__)); extern long double __coshl (long double __x) __attribute__ ((__nothrow__));

extern long double sinhl (long double __x) __attribute__ ((__nothrow__)); extern long double __sinhl (long double __x) __attribute__ ((__nothrow__));

extern long double tanhl (long double __x) __attribute__ ((__nothrow__)); extern long double __tanhl (long double __x) __attribute__ ((__nothrow__));

# 87 "/usr/include/bits/mathcalls.h" 3 4


extern long double acoshl (long double __x) __attribute__ ((__nothrow__)); extern long double __acoshl (long double __x) __attribute__ ((__nothrow__));

extern long double asinhl (long double __x) __attribute__ ((__nothrow__)); extern long double __asinhl (long double __x) __attribute__ ((__nothrow__));

extern long double atanhl (long double __x) __attribute__ ((__nothrow__)); extern long double __atanhl (long double __x) __attribute__ ((__nothrow__));







extern long double expl (long double __x) __attribute__ ((__nothrow__)); extern long double __expl (long double __x) __attribute__ ((__nothrow__));


extern long double frexpl (long double __x, int *__exponent) __attribute__ ((__nothrow__)); extern long double __frexpl (long double __x, int *__exponent) __attribute__ ((__nothrow__));


extern long double ldexpl (long double __x, int __exponent) __attribute__ ((__nothrow__)); extern long double __ldexpl (long double __x, int __exponent) __attribute__ ((__nothrow__));


extern long double logl (long double __x) __attribute__ ((__nothrow__)); extern long double __logl (long double __x) __attribute__ ((__nothrow__));


extern long double log10l (long double __x) __attribute__ ((__nothrow__)); extern long double __log10l (long double __x) __attribute__ ((__nothrow__));


extern long double modfl (long double __x, long double *__iptr) __attribute__ ((__nothrow__)); extern long double __modfl (long double __x, long double *__iptr) __attribute__ ((__nothrow__));

# 127 "/usr/include/bits/mathcalls.h" 3 4


extern long double expm1l (long double __x) __attribute__ ((__nothrow__)); extern long double __expm1l (long double __x) __attribute__ ((__nothrow__));


extern long double log1pl (long double __x) __attribute__ ((__nothrow__)); extern long double __log1pl (long double __x) __attribute__ ((__nothrow__));


extern long double logbl (long double __x) __attribute__ ((__nothrow__)); extern long double __logbl (long double __x) __attribute__ ((__nothrow__));






extern long double exp2l (long double __x) __attribute__ ((__nothrow__)); extern long double __exp2l (long double __x) __attribute__ ((__nothrow__));


extern long double log2l (long double __x) __attribute__ ((__nothrow__)); extern long double __log2l (long double __x) __attribute__ ((__nothrow__));








extern long double powl (long double __x, long double __y) __attribute__ ((__nothrow__)); extern long double __powl (long double __x, long double __y) __attribute__ ((__nothrow__));


extern long double sqrtl (long double __x) __attribute__ ((__nothrow__)); extern long double __sqrtl (long double __x) __attribute__ ((__nothrow__));





extern long double hypotl (long double __x, long double __y) __attribute__ ((__nothrow__)); extern long double __hypotl (long double __x, long double __y) __attribute__ ((__nothrow__));






extern long double cbrtl (long double __x) __attribute__ ((__nothrow__)); extern long double __cbrtl (long double __x) __attribute__ ((__nothrow__));








extern long double ceill (long double __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__)); extern long double __ceill (long double __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__));


extern long double fabsl (long double __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__)); extern long double __fabsl (long double __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__));


extern long double floorl (long double __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__)); extern long double __floorl (long double __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__));


extern long double fmodl (long double __x, long double __y) __attribute__ ((__nothrow__)); extern long double __fmodl (long double __x, long double __y) __attribute__ ((__nothrow__));




extern int __isinfl (long double __value) __attribute__ ((__nothrow__)) __attribute__ ((__const__));


extern int __finitel (long double __value) __attribute__ ((__nothrow__)) __attribute__ ((__const__));





extern int isinfl (long double __value) __attribute__ ((__nothrow__)) __attribute__ ((__const__));


extern int finitel (long double __value) __attribute__ ((__nothrow__)) __attribute__ ((__const__));


extern long double dreml (long double __x, long double __y) __attribute__ ((__nothrow__)); extern long double __dreml (long double __x, long double __y) __attribute__ ((__nothrow__));



extern long double significandl (long double __x) __attribute__ ((__nothrow__)); extern long double __significandl (long double __x) __attribute__ ((__nothrow__));





extern long double copysignl (long double __x, long double __y) __attribute__ ((__nothrow__)) __attribute__ ((__const__)); extern long double __copysignl (long double __x, long double __y) __attribute__ ((__nothrow__)) __attribute__ ((__const__));






extern long double nanl (__const char *__tagb) __attribute__ ((__nothrow__)) __attribute__ ((__const__)); extern long double __nanl (__const char *__tagb) __attribute__ ((__nothrow__)) __attribute__ ((__const__));





extern int __isnanl (long double __value) __attribute__ ((__nothrow__)) __attribute__ ((__const__));



extern int isnanl (long double __value) __attribute__ ((__nothrow__)) __attribute__ ((__const__));


extern long double j0l (long double) __attribute__ ((__nothrow__)); extern long double __j0l (long double) __attribute__ ((__nothrow__));
extern long double j1l (long double) __attribute__ ((__nothrow__)); extern long double __j1l (long double) __attribute__ ((__nothrow__));
extern long double jnl (int, long double) __attribute__ ((__nothrow__)); extern long double __jnl (int, long double) __attribute__ ((__nothrow__));
extern long double y0l (long double) __attribute__ ((__nothrow__)); extern long double __y0l (long double) __attribute__ ((__nothrow__));
extern long double y1l (long double) __attribute__ ((__nothrow__)); extern long double __y1l (long double) __attribute__ ((__nothrow__));
extern long double ynl (int, long double) __attribute__ ((__nothrow__)); extern long double __ynl (int, long double) __attribute__ ((__nothrow__));






extern long double erfl (long double) __attribute__ ((__nothrow__)); extern long double __erfl (long double) __attribute__ ((__nothrow__));
extern long double erfcl (long double) __attribute__ ((__nothrow__)); extern long double __erfcl (long double) __attribute__ ((__nothrow__));
extern long double lgammal (long double) __attribute__ ((__nothrow__)); extern long double __lgammal (long double) __attribute__ ((__nothrow__));






extern long double tgammal (long double) __attribute__ ((__nothrow__)); extern long double __tgammal (long double) __attribute__ ((__nothrow__));





extern long double gammal (long double) __attribute__ ((__nothrow__)); extern long double __gammal (long double) __attribute__ ((__nothrow__));






extern long double lgammal_r (long double, int *__signgamp) __attribute__ ((__nothrow__)); extern long double __lgammal_r (long double, int *__signgamp) __attribute__ ((__nothrow__));







extern long double rintl (long double __x) __attribute__ ((__nothrow__)); extern long double __rintl (long double __x) __attribute__ ((__nothrow__));


extern long double nextafterl (long double __x, long double __y) __attribute__ ((__nothrow__)) __attribute__ ((__const__)); extern long double __nextafterl (long double __x, long double __y) __attribute__ ((__nothrow__)) __attribute__ ((__const__));

extern long double nexttowardl (long double __x, long double __y) __attribute__ ((__nothrow__)) __attribute__ ((__const__)); extern long double __nexttowardl (long double __x, long double __y) __attribute__ ((__nothrow__)) __attribute__ ((__const__));



extern long double remainderl (long double __x, long double __y) __attribute__ ((__nothrow__)); extern long double __remainderl (long double __x, long double __y) __attribute__ ((__nothrow__));



extern long double scalbnl (long double __x, int __n) __attribute__ ((__nothrow__)); extern long double __scalbnl (long double __x, int __n) __attribute__ ((__nothrow__));



extern int ilogbl (long double __x) __attribute__ ((__nothrow__)); extern int __ilogbl (long double __x) __attribute__ ((__nothrow__));




extern long double scalblnl (long double __x, long int __n) __attribute__ ((__nothrow__)); extern long double __scalblnl (long double __x, long int __n) __attribute__ ((__nothrow__));



extern long double nearbyintl (long double __x) __attribute__ ((__nothrow__)); extern long double __nearbyintl (long double __x) __attribute__ ((__nothrow__));



extern long double roundl (long double __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__)); extern long double __roundl (long double __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__));



extern long double truncl (long double __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__)); extern long double __truncl (long double __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__));




extern long double remquol (long double __x, long double __y, int *__quo) __attribute__ ((__nothrow__)); extern long double __remquol (long double __x, long double __y, int *__quo) __attribute__ ((__nothrow__));






extern long int lrintl (long double __x) __attribute__ ((__nothrow__)); extern long int __lrintl (long double __x) __attribute__ ((__nothrow__));
extern long long int llrintl (long double __x) __attribute__ ((__nothrow__)); extern long long int __llrintl (long double __x) __attribute__ ((__nothrow__));



extern long int lroundl (long double __x) __attribute__ ((__nothrow__)); extern long int __lroundl (long double __x) __attribute__ ((__nothrow__));
extern long long int llroundl (long double __x) __attribute__ ((__nothrow__)); extern long long int __llroundl (long double __x) __attribute__ ((__nothrow__));



extern long double fdiml (long double __x, long double __y) __attribute__ ((__nothrow__)); extern long double __fdiml (long double __x, long double __y) __attribute__ ((__nothrow__));


extern long double fmaxl (long double __x, long double __y) __attribute__ ((__nothrow__)); extern long double __fmaxl (long double __x, long double __y) __attribute__ ((__nothrow__));


extern long double fminl (long double __x, long double __y) __attribute__ ((__nothrow__)); extern long double __fminl (long double __x, long double __y) __attribute__ ((__nothrow__));



extern int __fpclassifyl (long double __value) __attribute__ ((__nothrow__))
     __attribute__ ((__const__));


extern int __signbitl (long double __value) __attribute__ ((__nothrow__))
     __attribute__ ((__const__));



extern long double fmal (long double __x, long double __y, long double __z) __attribute__ ((__nothrow__)); extern long double __fmal (long double __x, long double __y, long double __z) __attribute__ ((__nothrow__));








extern long double scalbl (long double __x, long double __n) __attribute__ ((__nothrow__)); extern long double __scalbl (long double __x, long double __n) __attribute__ ((__nothrow__));
# 142 "/usr/include/math.h" 2 3 4
# 157 "/usr/include/math.h" 3 4
extern int signgam;
# 198 "/usr/include/math.h" 3 4
enum
  {
    FP_NAN,

    FP_INFINITE,

    FP_ZERO,

    FP_SUBNORMAL,

    FP_NORMAL

  };
# 291 "/usr/include/math.h" 3 4
typedef enum
{
  _IEEE_ = -1,
  _SVID_,
  _XOPEN_,
  _POSIX_,
  _ISOC_
} _LIB_VERSION_TYPE;




extern _LIB_VERSION_TYPE _LIB_VERSION;
# 316 "/usr/include/math.h" 3 4
struct exception

  {
    int type;
    char *name;
    double arg1;
    double arg2;
    double retval;
  };




extern int matherr (struct exception *__exc);
# 472 "/usr/include/math.h" 3 4

# 43 "<stdin>" 2
# 1 "/usr/include/time.h" 1 3 4
# 30 "/usr/include/time.h" 3 4








# 1 "/usr/lib/gcc/i686-pc-linux-gnu/4.6.1/include/stddef.h" 1 3 4
# 39 "/usr/include/time.h" 2 3 4



# 1 "/usr/include/bits/time.h" 1 3 4
# 43 "/usr/include/time.h" 2 3 4
# 131 "/usr/include/time.h" 3 4


struct tm
{
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;


  long int tm_gmtoff;
  __const char *tm_zone;




};








struct itimerspec
  {
    struct timespec it_interval;
    struct timespec it_value;
  };


struct sigevent;
# 180 "/usr/include/time.h" 3 4



extern clock_t clock (void) __attribute__ ((__nothrow__));


extern time_t time (time_t *__timer) __attribute__ ((__nothrow__));


extern double difftime (time_t __time1, time_t __time0)
     __attribute__ ((__nothrow__)) __attribute__ ((__const__));


extern time_t mktime (struct tm *__tp) __attribute__ ((__nothrow__));





extern size_t strftime (char *__restrict __s, size_t __maxsize,
   __const char *__restrict __format,
   __const struct tm *__restrict __tp) __attribute__ ((__nothrow__));

# 215 "/usr/include/time.h" 3 4
# 1 "/usr/include/xlocale.h" 1 3 4
# 28 "/usr/include/xlocale.h" 3 4
typedef struct __locale_struct
{

  struct __locale_data *__locales[13];


  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;


  const char *__names[13];
} *__locale_t;


typedef __locale_t locale_t;
# 216 "/usr/include/time.h" 2 3 4

extern size_t strftime_l (char *__restrict __s, size_t __maxsize,
     __const char *__restrict __format,
     __const struct tm *__restrict __tp,
     __locale_t __loc) __attribute__ ((__nothrow__));
# 230 "/usr/include/time.h" 3 4



extern struct tm *gmtime (__const time_t *__timer) __attribute__ ((__nothrow__));



extern struct tm *localtime (__const time_t *__timer) __attribute__ ((__nothrow__));





extern struct tm *gmtime_r (__const time_t *__restrict __timer,
       struct tm *__restrict __tp) __attribute__ ((__nothrow__));



extern struct tm *localtime_r (__const time_t *__restrict __timer,
          struct tm *__restrict __tp) __attribute__ ((__nothrow__));





extern char *asctime (__const struct tm *__tp) __attribute__ ((__nothrow__));


extern char *ctime (__const time_t *__timer) __attribute__ ((__nothrow__));







extern char *asctime_r (__const struct tm *__restrict __tp,
   char *__restrict __buf) __attribute__ ((__nothrow__));


extern char *ctime_r (__const time_t *__restrict __timer,
        char *__restrict __buf) __attribute__ ((__nothrow__));




extern char *__tzname[2];
extern int __daylight;
extern long int __timezone;




extern char *tzname[2];



extern void tzset (void) __attribute__ ((__nothrow__));



extern int daylight;
extern long int timezone;





extern int stime (__const time_t *__when) __attribute__ ((__nothrow__));
# 313 "/usr/include/time.h" 3 4
extern time_t timegm (struct tm *__tp) __attribute__ ((__nothrow__));


extern time_t timelocal (struct tm *__tp) __attribute__ ((__nothrow__));


extern int dysize (int __year) __attribute__ ((__nothrow__)) __attribute__ ((__const__));
# 328 "/usr/include/time.h" 3 4
extern int nanosleep (__const struct timespec *__requested_time,
        struct timespec *__remaining);



extern int clock_getres (clockid_t __clock_id, struct timespec *__res) __attribute__ ((__nothrow__));


extern int clock_gettime (clockid_t __clock_id, struct timespec *__tp) __attribute__ ((__nothrow__));


extern int clock_settime (clockid_t __clock_id, __const struct timespec *__tp)
     __attribute__ ((__nothrow__));






extern int clock_nanosleep (clockid_t __clock_id, int __flags,
       __const struct timespec *__req,
       struct timespec *__rem);


extern int clock_getcpuclockid (pid_t __pid, clockid_t *__clock_id) __attribute__ ((__nothrow__));




extern int timer_create (clockid_t __clock_id,
    struct sigevent *__restrict __evp,
    timer_t *__restrict __timerid) __attribute__ ((__nothrow__));


extern int timer_delete (timer_t __timerid) __attribute__ ((__nothrow__));


extern int timer_settime (timer_t __timerid, int __flags,
     __const struct itimerspec *__restrict __value,
     struct itimerspec *__restrict __ovalue) __attribute__ ((__nothrow__));


extern int timer_gettime (timer_t __timerid, struct itimerspec *__value)
     __attribute__ ((__nothrow__));


extern int timer_getoverrun (timer_t __timerid) __attribute__ ((__nothrow__));
# 417 "/usr/include/time.h" 3 4

# 44 "<stdin>" 2
# 1 "/usr/include/stdlib.h" 1 3 4
# 33 "/usr/include/stdlib.h" 3 4
# 1 "/usr/lib/gcc/i686-pc-linux-gnu/4.6.1/include/stddef.h" 1 3 4
# 324 "/usr/lib/gcc/i686-pc-linux-gnu/4.6.1/include/stddef.h" 3 4
typedef long int wchar_t;
# 34 "/usr/include/stdlib.h" 2 3 4








# 1 "/usr/include/bits/waitflags.h" 1 3 4
# 43 "/usr/include/stdlib.h" 2 3 4
# 1 "/usr/include/bits/waitstatus.h" 1 3 4
# 67 "/usr/include/bits/waitstatus.h" 3 4
union wait
  {
    int w_status;
    struct
      {

 unsigned int __w_termsig:7;
 unsigned int __w_coredump:1;
 unsigned int __w_retcode:8;
 unsigned int:16;







      } __wait_terminated;
    struct
      {

 unsigned int __w_stopval:8;
 unsigned int __w_stopsig:8;
 unsigned int:16;






      } __wait_stopped;
  };
# 44 "/usr/include/stdlib.h" 2 3 4
# 68 "/usr/include/stdlib.h" 3 4
typedef union
  {
    union wait *__uptr;
    int *__iptr;
  } __WAIT_STATUS __attribute__ ((__transparent_union__));
# 96 "/usr/include/stdlib.h" 3 4


typedef struct
  {
    int quot;
    int rem;
  } div_t;



typedef struct
  {
    long int quot;
    long int rem;
  } ldiv_t;







__extension__ typedef struct
  {
    long long int quot;
    long long int rem;
  } lldiv_t;


# 140 "/usr/include/stdlib.h" 3 4
extern size_t __ctype_get_mb_cur_max (void) __attribute__ ((__nothrow__)) ;




extern double atof (__const char *__nptr)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;

extern int atoi (__const char *__nptr)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;

extern long int atol (__const char *__nptr)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;





__extension__ extern long long int atoll (__const char *__nptr)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;





extern double strtod (__const char *__restrict __nptr,
        char **__restrict __endptr)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;





extern float strtof (__const char *__restrict __nptr,
       char **__restrict __endptr) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;

extern long double strtold (__const char *__restrict __nptr,
       char **__restrict __endptr)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;





extern long int strtol (__const char *__restrict __nptr,
   char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;

extern unsigned long int strtoul (__const char *__restrict __nptr,
      char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;




__extension__
extern long long int strtoq (__const char *__restrict __nptr,
        char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;

__extension__
extern unsigned long long int strtouq (__const char *__restrict __nptr,
           char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;





__extension__
extern long long int strtoll (__const char *__restrict __nptr,
         char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;

__extension__
extern unsigned long long int strtoull (__const char *__restrict __nptr,
     char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;

# 311 "/usr/include/stdlib.h" 3 4
extern char *l64a (long int __n) __attribute__ ((__nothrow__)) ;


extern long int a64l (__const char *__s)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;
# 327 "/usr/include/stdlib.h" 3 4
extern long int random (void) __attribute__ ((__nothrow__));


extern void srandom (unsigned int __seed) __attribute__ ((__nothrow__));





extern char *initstate (unsigned int __seed, char *__statebuf,
   size_t __statelen) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2)));



extern char *setstate (char *__statebuf) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));







struct random_data
  {
    int32_t *fptr;
    int32_t *rptr;
    int32_t *state;
    int rand_type;
    int rand_deg;
    int rand_sep;
    int32_t *end_ptr;
  };

extern int random_r (struct random_data *__restrict __buf,
       int32_t *__restrict __result) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));

extern int srandom_r (unsigned int __seed, struct random_data *__buf)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2)));

extern int initstate_r (unsigned int __seed, char *__restrict __statebuf,
   size_t __statelen,
   struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2, 4)));

extern int setstate_r (char *__restrict __statebuf,
         struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));






extern int rand (void) __attribute__ ((__nothrow__));

extern void srand (unsigned int __seed) __attribute__ ((__nothrow__));




extern int rand_r (unsigned int *__seed) __attribute__ ((__nothrow__));







extern double drand48 (void) __attribute__ ((__nothrow__));
extern double erand48 (unsigned short int __xsubi[3]) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern long int lrand48 (void) __attribute__ ((__nothrow__));
extern long int nrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern long int mrand48 (void) __attribute__ ((__nothrow__));
extern long int jrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern void srand48 (long int __seedval) __attribute__ ((__nothrow__));
extern unsigned short int *seed48 (unsigned short int __seed16v[3])
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern void lcong48 (unsigned short int __param[7]) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));





struct drand48_data
  {
    unsigned short int __x[3];
    unsigned short int __old_x[3];
    unsigned short int __c;
    unsigned short int __init;
    unsigned long long int __a;
  };


extern int drand48_r (struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
extern int erand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));


extern int lrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
extern int nrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));


extern int mrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
extern int jrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));


extern int srand48_r (long int __seedval, struct drand48_data *__buffer)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2)));

extern int seed48_r (unsigned short int __seed16v[3],
       struct drand48_data *__buffer) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));

extern int lcong48_r (unsigned short int __param[7],
        struct drand48_data *__buffer)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));









extern void *malloc (size_t __size) __attribute__ ((__nothrow__)) __attribute__ ((__malloc__)) ;

extern void *calloc (size_t __nmemb, size_t __size)
     __attribute__ ((__nothrow__)) __attribute__ ((__malloc__)) ;










extern void *realloc (void *__ptr, size_t __size)
     __attribute__ ((__nothrow__)) __attribute__ ((__warn_unused_result__));

extern void free (void *__ptr) __attribute__ ((__nothrow__));




extern void cfree (void *__ptr) __attribute__ ((__nothrow__));



# 1 "/usr/include/alloca.h" 1 3 4
# 25 "/usr/include/alloca.h" 3 4
# 1 "/usr/lib/gcc/i686-pc-linux-gnu/4.6.1/include/stddef.h" 1 3 4
# 26 "/usr/include/alloca.h" 2 3 4







extern void *alloca (size_t __size) __attribute__ ((__nothrow__));






# 498 "/usr/include/stdlib.h" 2 3 4





extern void *valloc (size_t __size) __attribute__ ((__nothrow__)) __attribute__ ((__malloc__)) ;




extern int posix_memalign (void **__memptr, size_t __alignment, size_t __size)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;




extern void abort (void) __attribute__ ((__nothrow__)) __attribute__ ((__noreturn__));



extern int atexit (void (*__func) (void)) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
# 531 "/usr/include/stdlib.h" 3 4





extern int on_exit (void (*__func) (int __status, void *__arg), void *__arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));






extern void exit (int __status) __attribute__ ((__nothrow__)) __attribute__ ((__noreturn__));
# 554 "/usr/include/stdlib.h" 3 4






extern void _Exit (int __status) __attribute__ ((__nothrow__)) __attribute__ ((__noreturn__));






extern char *getenv (__const char *__name) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;




extern char *__secure_getenv (__const char *__name)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;





extern int putenv (char *__string) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));





extern int setenv (__const char *__name, __const char *__value, int __replace)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2)));


extern int unsetenv (__const char *__name) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));






extern int clearenv (void) __attribute__ ((__nothrow__));
# 606 "/usr/include/stdlib.h" 3 4
extern char *mktemp (char *__template) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;
# 620 "/usr/include/stdlib.h" 3 4
extern int mkstemp (char *__template) __attribute__ ((__nonnull__ (1))) ;
# 642 "/usr/include/stdlib.h" 3 4
extern int mkstemps (char *__template, int __suffixlen) __attribute__ ((__nonnull__ (1))) ;
# 663 "/usr/include/stdlib.h" 3 4
extern char *mkdtemp (char *__template) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;
# 712 "/usr/include/stdlib.h" 3 4





extern int system (__const char *__command) ;

# 734 "/usr/include/stdlib.h" 3 4
extern char *realpath (__const char *__restrict __name,
         char *__restrict __resolved) __attribute__ ((__nothrow__)) ;






typedef int (*__compar_fn_t) (__const void *, __const void *);
# 752 "/usr/include/stdlib.h" 3 4



extern void *bsearch (__const void *__key, __const void *__base,
        size_t __nmemb, size_t __size, __compar_fn_t __compar)
     __attribute__ ((__nonnull__ (1, 2, 5))) ;



extern void qsort (void *__base, size_t __nmemb, size_t __size,
     __compar_fn_t __compar) __attribute__ ((__nonnull__ (1, 4)));
# 771 "/usr/include/stdlib.h" 3 4
extern int abs (int __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__)) ;
extern long int labs (long int __x) __attribute__ ((__nothrow__)) __attribute__ ((__const__)) ;



__extension__ extern long long int llabs (long long int __x)
     __attribute__ ((__nothrow__)) __attribute__ ((__const__)) ;







extern div_t div (int __numer, int __denom)
     __attribute__ ((__nothrow__)) __attribute__ ((__const__)) ;
extern ldiv_t ldiv (long int __numer, long int __denom)
     __attribute__ ((__nothrow__)) __attribute__ ((__const__)) ;




__extension__ extern lldiv_t lldiv (long long int __numer,
        long long int __denom)
     __attribute__ ((__nothrow__)) __attribute__ ((__const__)) ;

# 808 "/usr/include/stdlib.h" 3 4
extern char *ecvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3, 4))) ;




extern char *fcvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3, 4))) ;




extern char *gcvt (double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3))) ;




extern char *qecvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qfcvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qgcvt (long double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3))) ;




extern int ecvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int fcvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3, 4, 5)));

extern int qecvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int qfcvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3, 4, 5)));







extern int mblen (__const char *__s, size_t __n) __attribute__ ((__nothrow__)) ;


extern int mbtowc (wchar_t *__restrict __pwc,
     __const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__)) ;


extern int wctomb (char *__s, wchar_t __wchar) __attribute__ ((__nothrow__)) ;



extern size_t mbstowcs (wchar_t *__restrict __pwcs,
   __const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__));

extern size_t wcstombs (char *__restrict __s,
   __const wchar_t *__restrict __pwcs, size_t __n)
     __attribute__ ((__nothrow__));








extern int rpmatch (__const char *__response) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1))) ;
# 896 "/usr/include/stdlib.h" 3 4
extern int getsubopt (char **__restrict __optionp,
        char *__const *__restrict __tokens,
        char **__restrict __valuep)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2, 3))) ;
# 948 "/usr/include/stdlib.h" 3 4
extern int getloadavg (double __loadavg[], int __nelem)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
# 964 "/usr/include/stdlib.h" 3 4

# 45 "<stdin>" 2
# 1 "/usr/include/stdio.h" 1 3 4
# 30 "/usr/include/stdio.h" 3 4




# 1 "/usr/lib/gcc/i686-pc-linux-gnu/4.6.1/include/stddef.h" 1 3 4
# 35 "/usr/include/stdio.h" 2 3 4
# 45 "/usr/include/stdio.h" 3 4
struct _IO_FILE;



typedef struct _IO_FILE FILE;





# 65 "/usr/include/stdio.h" 3 4
typedef struct _IO_FILE __FILE;
# 75 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/libio.h" 1 3 4
# 32 "/usr/include/libio.h" 3 4
# 1 "/usr/include/_G_config.h" 1 3 4
# 15 "/usr/include/_G_config.h" 3 4
# 1 "/usr/lib/gcc/i686-pc-linux-gnu/4.6.1/include/stddef.h" 1 3 4
# 16 "/usr/include/_G_config.h" 2 3 4




# 1 "/usr/include/wchar.h" 1 3 4
# 83 "/usr/include/wchar.h" 3 4
typedef struct
{
  int __count;
  union
  {

    unsigned int __wch;



    char __wchb[4];
  } __value;
} __mbstate_t;
# 21 "/usr/include/_G_config.h" 2 3 4

typedef struct
{
  __off_t __pos;
  __mbstate_t __state;
} _G_fpos_t;
typedef struct
{
  __off64_t __pos;
  __mbstate_t __state;
} _G_fpos64_t;
# 53 "/usr/include/_G_config.h" 3 4
typedef int _G_int16_t __attribute__ ((__mode__ (__HI__)));
typedef int _G_int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int _G_uint16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int _G_uint32_t __attribute__ ((__mode__ (__SI__)));
# 33 "/usr/include/libio.h" 2 3 4
# 53 "/usr/include/libio.h" 3 4
# 1 "/usr/lib/gcc/i686-pc-linux-gnu/4.6.1/include/stdarg.h" 1 3 4
# 40 "/usr/lib/gcc/i686-pc-linux-gnu/4.6.1/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 54 "/usr/include/libio.h" 2 3 4
# 172 "/usr/include/libio.h" 3 4
struct _IO_jump_t; struct _IO_FILE;
# 182 "/usr/include/libio.h" 3 4
typedef void _IO_lock_t;





struct _IO_marker {
  struct _IO_marker *_next;
  struct _IO_FILE *_sbuf;



  int _pos;
# 205 "/usr/include/libio.h" 3 4
};


enum __codecvt_result
{
  __codecvt_ok,
  __codecvt_partial,
  __codecvt_error,
  __codecvt_noconv
};
# 273 "/usr/include/libio.h" 3 4
struct _IO_FILE {
  int _flags;




  char* _IO_read_ptr;
  char* _IO_read_end;
  char* _IO_read_base;
  char* _IO_write_base;
  char* _IO_write_ptr;
  char* _IO_write_end;
  char* _IO_buf_base;
  char* _IO_buf_end;

  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;

  struct _IO_marker *_markers;

  struct _IO_FILE *_chain;

  int _fileno;



  int _flags2;

  __off_t _old_offset;



  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];



  _IO_lock_t *_lock;
# 321 "/usr/include/libio.h" 3 4
  __off64_t _offset;
# 330 "/usr/include/libio.h" 3 4
  void *__pad1;
  void *__pad2;
  void *__pad3;
  void *__pad4;
  size_t __pad5;

  int _mode;

  char _unused2[15 * sizeof (int) - 4 * sizeof (void *) - sizeof (size_t)];

};


typedef struct _IO_FILE _IO_FILE;


struct _IO_FILE_plus;

extern struct _IO_FILE_plus _IO_2_1_stdin_;
extern struct _IO_FILE_plus _IO_2_1_stdout_;
extern struct _IO_FILE_plus _IO_2_1_stderr_;
# 366 "/usr/include/libio.h" 3 4
typedef __ssize_t __io_read_fn (void *__cookie, char *__buf, size_t __nbytes);







typedef __ssize_t __io_write_fn (void *__cookie, __const char *__buf,
     size_t __n);







typedef int __io_seek_fn (void *__cookie, __off64_t *__pos, int __w);


typedef int __io_close_fn (void *__cookie);
# 418 "/usr/include/libio.h" 3 4
extern int __underflow (_IO_FILE *);
extern int __uflow (_IO_FILE *);
extern int __overflow (_IO_FILE *, int);
# 462 "/usr/include/libio.h" 3 4
extern int _IO_getc (_IO_FILE *__fp);
extern int _IO_putc (int __c, _IO_FILE *__fp);
extern int _IO_feof (_IO_FILE *__fp) __attribute__ ((__nothrow__));
extern int _IO_ferror (_IO_FILE *__fp) __attribute__ ((__nothrow__));

extern int _IO_peekc_locked (_IO_FILE *__fp);





extern void _IO_flockfile (_IO_FILE *) __attribute__ ((__nothrow__));
extern void _IO_funlockfile (_IO_FILE *) __attribute__ ((__nothrow__));
extern int _IO_ftrylockfile (_IO_FILE *) __attribute__ ((__nothrow__));
# 492 "/usr/include/libio.h" 3 4
extern int _IO_vfscanf (_IO_FILE * __restrict, const char * __restrict,
   __gnuc_va_list, int *__restrict);
extern int _IO_vfprintf (_IO_FILE *__restrict, const char *__restrict,
    __gnuc_va_list);
extern __ssize_t _IO_padn (_IO_FILE *, int, __ssize_t);
extern size_t _IO_sgetn (_IO_FILE *, void *, size_t);

extern __off64_t _IO_seekoff (_IO_FILE *, __off64_t, int, int);
extern __off64_t _IO_seekpos (_IO_FILE *, __off64_t, int);

extern void _IO_free_backup_area (_IO_FILE *) __attribute__ ((__nothrow__));
# 76 "/usr/include/stdio.h" 2 3 4




typedef __gnuc_va_list va_list;
# 109 "/usr/include/stdio.h" 3 4


typedef _G_fpos_t fpos_t;




# 161 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/bits/stdio_lim.h" 1 3 4
# 162 "/usr/include/stdio.h" 2 3 4



extern struct _IO_FILE *stdin;
extern struct _IO_FILE *stdout;
extern struct _IO_FILE *stderr;







extern int remove (__const char *__filename) __attribute__ ((__nothrow__));

extern int rename (__const char *__old, __const char *__new) __attribute__ ((__nothrow__));




extern int renameat (int __oldfd, __const char *__old, int __newfd,
       __const char *__new) __attribute__ ((__nothrow__));








extern FILE *tmpfile (void) ;
# 206 "/usr/include/stdio.h" 3 4
extern char *tmpnam (char *__s) __attribute__ ((__nothrow__)) ;





extern char *tmpnam_r (char *__s) __attribute__ ((__nothrow__)) ;
# 224 "/usr/include/stdio.h" 3 4
extern char *tempnam (__const char *__dir, __const char *__pfx)
     __attribute__ ((__nothrow__)) __attribute__ ((__malloc__)) ;








extern int fclose (FILE *__stream);




extern int fflush (FILE *__stream);

# 249 "/usr/include/stdio.h" 3 4
extern int fflush_unlocked (FILE *__stream);
# 263 "/usr/include/stdio.h" 3 4






extern FILE *fopen (__const char *__restrict __filename,
      __const char *__restrict __modes) ;




extern FILE *freopen (__const char *__restrict __filename,
        __const char *__restrict __modes,
        FILE *__restrict __stream) ;
# 292 "/usr/include/stdio.h" 3 4

# 303 "/usr/include/stdio.h" 3 4
extern FILE *fdopen (int __fd, __const char *__modes) __attribute__ ((__nothrow__)) ;
# 316 "/usr/include/stdio.h" 3 4
extern FILE *fmemopen (void *__s, size_t __len, __const char *__modes)
  __attribute__ ((__nothrow__)) ;




extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc) __attribute__ ((__nothrow__)) ;






extern void setbuf (FILE *__restrict __stream, char *__restrict __buf) __attribute__ ((__nothrow__));



extern int setvbuf (FILE *__restrict __stream, char *__restrict __buf,
      int __modes, size_t __n) __attribute__ ((__nothrow__));





extern void setbuffer (FILE *__restrict __stream, char *__restrict __buf,
         size_t __size) __attribute__ ((__nothrow__));


extern void setlinebuf (FILE *__stream) __attribute__ ((__nothrow__));








extern int fprintf (FILE *__restrict __stream,
      __const char *__restrict __format, ...);




extern int printf (__const char *__restrict __format, ...);

extern int sprintf (char *__restrict __s,
      __const char *__restrict __format, ...) __attribute__ ((__nothrow__));





extern int vfprintf (FILE *__restrict __s, __const char *__restrict __format,
       __gnuc_va_list __arg);




extern int vprintf (__const char *__restrict __format, __gnuc_va_list __arg);

extern int vsprintf (char *__restrict __s, __const char *__restrict __format,
       __gnuc_va_list __arg) __attribute__ ((__nothrow__));





extern int snprintf (char *__restrict __s, size_t __maxlen,
       __const char *__restrict __format, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 4)));

extern int vsnprintf (char *__restrict __s, size_t __maxlen,
        __const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 0)));

# 414 "/usr/include/stdio.h" 3 4
extern int vdprintf (int __fd, __const char *__restrict __fmt,
       __gnuc_va_list __arg)
     __attribute__ ((__format__ (__printf__, 2, 0)));
extern int dprintf (int __fd, __const char *__restrict __fmt, ...)
     __attribute__ ((__format__ (__printf__, 2, 3)));








extern int fscanf (FILE *__restrict __stream,
     __const char *__restrict __format, ...) ;




extern int scanf (__const char *__restrict __format, ...) ;

extern int sscanf (__const char *__restrict __s,
     __const char *__restrict __format, ...) __attribute__ ((__nothrow__));
# 445 "/usr/include/stdio.h" 3 4
extern int fscanf (FILE *__restrict __stream, __const char *__restrict __format, ...) __asm__ ("" "__isoc99_fscanf")

                               ;
extern int scanf (__const char *__restrict __format, ...) __asm__ ("" "__isoc99_scanf")
                              ;
extern int sscanf (__const char *__restrict __s, __const char *__restrict __format, ...) __asm__ ("" "__isoc99_sscanf") __attribute__ ((__nothrow__))

                      ;
# 465 "/usr/include/stdio.h" 3 4








extern int vfscanf (FILE *__restrict __s, __const char *__restrict __format,
      __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 2, 0))) ;





extern int vscanf (__const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 1, 0))) ;


extern int vsscanf (__const char *__restrict __s,
      __const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__scanf__, 2, 0)));
# 496 "/usr/include/stdio.h" 3 4
extern int vfscanf (FILE *__restrict __s, __const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vfscanf")



     __attribute__ ((__format__ (__scanf__, 2, 0))) ;
extern int vscanf (__const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vscanf")

     __attribute__ ((__format__ (__scanf__, 1, 0))) ;
extern int vsscanf (__const char *__restrict __s, __const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vsscanf") __attribute__ ((__nothrow__))



     __attribute__ ((__format__ (__scanf__, 2, 0)));
# 524 "/usr/include/stdio.h" 3 4









extern int fgetc (FILE *__stream);
extern int getc (FILE *__stream);





extern int getchar (void);

# 552 "/usr/include/stdio.h" 3 4
extern int getc_unlocked (FILE *__stream);
extern int getchar_unlocked (void);
# 563 "/usr/include/stdio.h" 3 4
extern int fgetc_unlocked (FILE *__stream);











extern int fputc (int __c, FILE *__stream);
extern int putc (int __c, FILE *__stream);





extern int putchar (int __c);

# 596 "/usr/include/stdio.h" 3 4
extern int fputc_unlocked (int __c, FILE *__stream);







extern int putc_unlocked (int __c, FILE *__stream);
extern int putchar_unlocked (int __c);






extern int getw (FILE *__stream);


extern int putw (int __w, FILE *__stream);








extern char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
     ;






extern char *gets (char *__s) ;

# 658 "/usr/include/stdio.h" 3 4
extern __ssize_t __getdelim (char **__restrict __lineptr,
          size_t *__restrict __n, int __delimiter,
          FILE *__restrict __stream) ;
extern __ssize_t getdelim (char **__restrict __lineptr,
        size_t *__restrict __n, int __delimiter,
        FILE *__restrict __stream) ;







extern __ssize_t getline (char **__restrict __lineptr,
       size_t *__restrict __n,
       FILE *__restrict __stream) ;








extern int fputs (__const char *__restrict __s, FILE *__restrict __stream);





extern int puts (__const char *__s);






extern int ungetc (int __c, FILE *__stream);






extern size_t fread (void *__restrict __ptr, size_t __size,
       size_t __n, FILE *__restrict __stream) ;




extern size_t fwrite (__const void *__restrict __ptr, size_t __size,
        size_t __n, FILE *__restrict __s) ;

# 730 "/usr/include/stdio.h" 3 4
extern size_t fread_unlocked (void *__restrict __ptr, size_t __size,
         size_t __n, FILE *__restrict __stream) ;
extern size_t fwrite_unlocked (__const void *__restrict __ptr, size_t __size,
          size_t __n, FILE *__restrict __stream) ;








extern int fseek (FILE *__stream, long int __off, int __whence);




extern long int ftell (FILE *__stream) ;




extern void rewind (FILE *__stream);

# 766 "/usr/include/stdio.h" 3 4
extern int fseeko (FILE *__stream, __off_t __off, int __whence);




extern __off_t ftello (FILE *__stream) ;
# 785 "/usr/include/stdio.h" 3 4






extern int fgetpos (FILE *__restrict __stream, fpos_t *__restrict __pos);




extern int fsetpos (FILE *__stream, __const fpos_t *__pos);
# 808 "/usr/include/stdio.h" 3 4

# 817 "/usr/include/stdio.h" 3 4


extern void clearerr (FILE *__stream) __attribute__ ((__nothrow__));

extern int feof (FILE *__stream) __attribute__ ((__nothrow__)) ;

extern int ferror (FILE *__stream) __attribute__ ((__nothrow__)) ;




extern void clearerr_unlocked (FILE *__stream) __attribute__ ((__nothrow__));
extern int feof_unlocked (FILE *__stream) __attribute__ ((__nothrow__)) ;
extern int ferror_unlocked (FILE *__stream) __attribute__ ((__nothrow__)) ;








extern void perror (__const char *__s);






# 1 "/usr/include/bits/sys_errlist.h" 1 3 4
# 27 "/usr/include/bits/sys_errlist.h" 3 4
extern int sys_nerr;
extern __const char *__const sys_errlist[];
# 847 "/usr/include/stdio.h" 2 3 4




extern int fileno (FILE *__stream) __attribute__ ((__nothrow__)) ;




extern int fileno_unlocked (FILE *__stream) __attribute__ ((__nothrow__)) ;
# 866 "/usr/include/stdio.h" 3 4
extern FILE *popen (__const char *__command, __const char *__modes) ;





extern int pclose (FILE *__stream);





extern char *ctermid (char *__s) __attribute__ ((__nothrow__));
# 906 "/usr/include/stdio.h" 3 4
extern void flockfile (FILE *__stream) __attribute__ ((__nothrow__));



extern int ftrylockfile (FILE *__stream) __attribute__ ((__nothrow__)) ;


extern void funlockfile (FILE *__stream) __attribute__ ((__nothrow__));
# 936 "/usr/include/stdio.h" 3 4

# 46 "<stdin>" 2
# 1 "/usr/include/ctype.h" 1 3 4
# 30 "/usr/include/ctype.h" 3 4

# 48 "/usr/include/ctype.h" 3 4
enum
{
  _ISupper = ((0) < 8 ? ((1 << (0)) << 8) : ((1 << (0)) >> 8)),
  _ISlower = ((1) < 8 ? ((1 << (1)) << 8) : ((1 << (1)) >> 8)),
  _ISalpha = ((2) < 8 ? ((1 << (2)) << 8) : ((1 << (2)) >> 8)),
  _ISdigit = ((3) < 8 ? ((1 << (3)) << 8) : ((1 << (3)) >> 8)),
  _ISxdigit = ((4) < 8 ? ((1 << (4)) << 8) : ((1 << (4)) >> 8)),
  _ISspace = ((5) < 8 ? ((1 << (5)) << 8) : ((1 << (5)) >> 8)),
  _ISprint = ((6) < 8 ? ((1 << (6)) << 8) : ((1 << (6)) >> 8)),
  _ISgraph = ((7) < 8 ? ((1 << (7)) << 8) : ((1 << (7)) >> 8)),
  _ISblank = ((8) < 8 ? ((1 << (8)) << 8) : ((1 << (8)) >> 8)),
  _IScntrl = ((9) < 8 ? ((1 << (9)) << 8) : ((1 << (9)) >> 8)),
  _ISpunct = ((10) < 8 ? ((1 << (10)) << 8) : ((1 << (10)) >> 8)),
  _ISalnum = ((11) < 8 ? ((1 << (11)) << 8) : ((1 << (11)) >> 8))
};
# 81 "/usr/include/ctype.h" 3 4
extern __const unsigned short int **__ctype_b_loc (void)
     __attribute__ ((__nothrow__)) __attribute__ ((__const));
extern __const __int32_t **__ctype_tolower_loc (void)
     __attribute__ ((__nothrow__)) __attribute__ ((__const));
extern __const __int32_t **__ctype_toupper_loc (void)
     __attribute__ ((__nothrow__)) __attribute__ ((__const));
# 96 "/usr/include/ctype.h" 3 4






extern int isalnum (int) __attribute__ ((__nothrow__));
extern int isalpha (int) __attribute__ ((__nothrow__));
extern int iscntrl (int) __attribute__ ((__nothrow__));
extern int isdigit (int) __attribute__ ((__nothrow__));
extern int islower (int) __attribute__ ((__nothrow__));
extern int isgraph (int) __attribute__ ((__nothrow__));
extern int isprint (int) __attribute__ ((__nothrow__));
extern int ispunct (int) __attribute__ ((__nothrow__));
extern int isspace (int) __attribute__ ((__nothrow__));
extern int isupper (int) __attribute__ ((__nothrow__));
extern int isxdigit (int) __attribute__ ((__nothrow__));



extern int tolower (int __c) __attribute__ ((__nothrow__));


extern int toupper (int __c) __attribute__ ((__nothrow__));








extern int isblank (int) __attribute__ ((__nothrow__));


# 142 "/usr/include/ctype.h" 3 4
extern int isascii (int __c) __attribute__ ((__nothrow__));



extern int toascii (int __c) __attribute__ ((__nothrow__));



extern int _toupper (int) __attribute__ ((__nothrow__));
extern int _tolower (int) __attribute__ ((__nothrow__));
# 247 "/usr/include/ctype.h" 3 4
extern int isalnum_l (int, __locale_t) __attribute__ ((__nothrow__));
extern int isalpha_l (int, __locale_t) __attribute__ ((__nothrow__));
extern int iscntrl_l (int, __locale_t) __attribute__ ((__nothrow__));
extern int isdigit_l (int, __locale_t) __attribute__ ((__nothrow__));
extern int islower_l (int, __locale_t) __attribute__ ((__nothrow__));
extern int isgraph_l (int, __locale_t) __attribute__ ((__nothrow__));
extern int isprint_l (int, __locale_t) __attribute__ ((__nothrow__));
extern int ispunct_l (int, __locale_t) __attribute__ ((__nothrow__));
extern int isspace_l (int, __locale_t) __attribute__ ((__nothrow__));
extern int isupper_l (int, __locale_t) __attribute__ ((__nothrow__));
extern int isxdigit_l (int, __locale_t) __attribute__ ((__nothrow__));

extern int isblank_l (int, __locale_t) __attribute__ ((__nothrow__));



extern int __tolower_l (int __c, __locale_t __l) __attribute__ ((__nothrow__));
extern int tolower_l (int __c, __locale_t __l) __attribute__ ((__nothrow__));


extern int __toupper_l (int __c, __locale_t __l) __attribute__ ((__nothrow__));
extern int toupper_l (int __c, __locale_t __l) __attribute__ ((__nothrow__));
# 323 "/usr/include/ctype.h" 3 4

# 47 "<stdin>" 2
# 1 "/usr/include/string.h" 1 3 4
# 29 "/usr/include/string.h" 3 4





# 1 "/usr/lib/gcc/i686-pc-linux-gnu/4.6.1/include/stddef.h" 1 3 4
# 35 "/usr/include/string.h" 2 3 4









extern void *memcpy (void *__restrict __dest,
       __const void *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));


extern void *memmove (void *__dest, __const void *__src, size_t __n)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));






extern void *memccpy (void *__restrict __dest, __const void *__restrict __src,
        int __c, size_t __n)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));





extern void *memset (void *__s, int __c, size_t __n) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int memcmp (__const void *__s1, __const void *__s2, size_t __n)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 95 "/usr/include/string.h" 3 4
extern void *memchr (__const void *__s, int __c, size_t __n)
      __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));


# 126 "/usr/include/string.h" 3 4


extern char *strcpy (char *__restrict __dest, __const char *__restrict __src)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));

extern char *strncpy (char *__restrict __dest,
        __const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));


extern char *strcat (char *__restrict __dest, __const char *__restrict __src)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));

extern char *strncat (char *__restrict __dest, __const char *__restrict __src,
        size_t __n) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strcmp (__const char *__s1, __const char *__s2)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));

extern int strncmp (__const char *__s1, __const char *__s2, size_t __n)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strcoll (__const char *__s1, __const char *__s2)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));

extern size_t strxfrm (char *__restrict __dest,
         __const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2)));

# 165 "/usr/include/string.h" 3 4
extern int strcoll_l (__const char *__s1, __const char *__s2, __locale_t __l)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));

extern size_t strxfrm_l (char *__dest, __const char *__src, size_t __n,
    __locale_t __l) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2, 4)));





extern char *strdup (__const char *__s)
     __attribute__ ((__nothrow__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));






extern char *strndup (__const char *__string, size_t __n)
     __attribute__ ((__nothrow__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));
# 210 "/usr/include/string.h" 3 4

# 235 "/usr/include/string.h" 3 4
extern char *strchr (__const char *__s, int __c)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 262 "/usr/include/string.h" 3 4
extern char *strrchr (__const char *__s, int __c)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));


# 281 "/usr/include/string.h" 3 4



extern size_t strcspn (__const char *__s, __const char *__reject)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern size_t strspn (__const char *__s, __const char *__accept)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 314 "/usr/include/string.h" 3 4
extern char *strpbrk (__const char *__s, __const char *__accept)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 342 "/usr/include/string.h" 3 4
extern char *strstr (__const char *__haystack, __const char *__needle)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));




extern char *strtok (char *__restrict __s, __const char *__restrict __delim)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2)));




extern char *__strtok_r (char *__restrict __s,
    __const char *__restrict __delim,
    char **__restrict __save_ptr)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2, 3)));

extern char *strtok_r (char *__restrict __s, __const char *__restrict __delim,
         char **__restrict __save_ptr)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2, 3)));
# 397 "/usr/include/string.h" 3 4


extern size_t strlen (__const char *__s)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));





extern size_t strnlen (__const char *__string, size_t __maxlen)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));





extern char *strerror (int __errnum) __attribute__ ((__nothrow__));

# 427 "/usr/include/string.h" 3 4
extern int strerror_r (int __errnum, char *__buf, size_t __buflen) __asm__ ("" "__xpg_strerror_r") __attribute__ ((__nothrow__))

                        __attribute__ ((__nonnull__ (2)));
# 445 "/usr/include/string.h" 3 4
extern char *strerror_l (int __errnum, __locale_t __l) __attribute__ ((__nothrow__));





extern void __bzero (void *__s, size_t __n) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));



extern void bcopy (__const void *__src, void *__dest, size_t __n)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));


extern void bzero (void *__s, size_t __n) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int bcmp (__const void *__s1, __const void *__s2, size_t __n)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 489 "/usr/include/string.h" 3 4
extern char *index (__const char *__s, int __c)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 517 "/usr/include/string.h" 3 4
extern char *rindex (__const char *__s, int __c)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));




extern int ffs (int __i) __attribute__ ((__nothrow__)) __attribute__ ((__const__));
# 536 "/usr/include/string.h" 3 4
extern int strcasecmp (__const char *__s1, __const char *__s2)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strncasecmp (__const char *__s1, __const char *__s2, size_t __n)
     __attribute__ ((__nothrow__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 559 "/usr/include/string.h" 3 4
extern char *strsep (char **__restrict __stringp,
       __const char *__restrict __delim)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));




extern char *strsignal (int __sig) __attribute__ ((__nothrow__));


extern char *__stpcpy (char *__restrict __dest, __const char *__restrict __src)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *stpcpy (char *__restrict __dest, __const char *__restrict __src)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));



extern char *__stpncpy (char *__restrict __dest,
   __const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *stpncpy (char *__restrict __dest,
        __const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
# 646 "/usr/include/string.h" 3 4

# 48 "<stdin>" 2
# 1 "/usr/lib/gcc/i686-pc-linux-gnu/4.6.1/include/stdarg.h" 1 3 4
# 49 "<stdin>" 2
# 1 "/usr/lib/gcc/i686-pc-linux-gnu/4.6.1/include-fixed/limits.h" 1 3 4
# 34 "/usr/lib/gcc/i686-pc-linux-gnu/4.6.1/include-fixed/limits.h" 3 4
# 1 "/usr/lib/gcc/i686-pc-linux-gnu/4.6.1/include-fixed/syslimits.h" 1 3 4






# 1 "/usr/lib/gcc/i686-pc-linux-gnu/4.6.1/include-fixed/limits.h" 1 3 4
# 169 "/usr/lib/gcc/i686-pc-linux-gnu/4.6.1/include-fixed/limits.h" 3 4
# 1 "/usr/include/limits.h" 1 3 4
# 145 "/usr/include/limits.h" 3 4
# 1 "/usr/include/bits/posix1_lim.h" 1 3 4
# 157 "/usr/include/bits/posix1_lim.h" 3 4
# 1 "/usr/include/bits/local_lim.h" 1 3 4
# 39 "/usr/include/bits/local_lim.h" 3 4
# 1 "/usr/include/linux/limits.h" 1 3 4
# 40 "/usr/include/bits/local_lim.h" 2 3 4
# 158 "/usr/include/bits/posix1_lim.h" 2 3 4
# 146 "/usr/include/limits.h" 2 3 4



# 1 "/usr/include/bits/posix2_lim.h" 1 3 4
# 150 "/usr/include/limits.h" 2 3 4
# 170 "/usr/lib/gcc/i686-pc-linux-gnu/4.6.1/include-fixed/limits.h" 2 3 4
# 8 "/usr/lib/gcc/i686-pc-linux-gnu/4.6.1/include-fixed/syslimits.h" 2 3 4
# 35 "/usr/lib/gcc/i686-pc-linux-gnu/4.6.1/include-fixed/limits.h" 2 3 4
# 50 "<stdin>" 2
# 63 "<stdin>"
# 1 "/usr/lib/gcc/i686-pc-linux-gnu/4.6.1/include/xmmintrin.h" 1 3 4
# 64 "<stdin>" 2
# 74 "<stdin>"
# 1 "axml.h" 1
# 32 "axml.h"
# 1 "/usr/include/assert.h" 1 3 4
# 66 "/usr/include/assert.h" 3 4



extern void __assert_fail (__const char *__assertion, __const char *__file,
      unsigned int __line, __const char *__function)
     __attribute__ ((__nothrow__)) __attribute__ ((__noreturn__));


extern void __assert_perror_fail (int __errnum, __const char *__file,
      unsigned int __line,
      __const char *__function)
     __attribute__ ((__nothrow__)) __attribute__ ((__noreturn__));




extern void __assert (const char *__assertion, const char *__file, int __line)
     __attribute__ ((__nothrow__)) __attribute__ ((__noreturn__));



# 33 "axml.h" 2
# 1 "/usr/lib/gcc/i686-pc-linux-gnu/4.6.1/include/stdint.h" 1 3 4


# 1 "/usr/include/stdint.h" 1 3 4
# 27 "/usr/include/stdint.h" 3 4
# 1 "/usr/include/bits/wchar.h" 1 3 4
# 28 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 29 "/usr/include/stdint.h" 2 3 4
# 49 "/usr/include/stdint.h" 3 4
typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;

typedef unsigned int uint32_t;





__extension__
typedef unsigned long long int uint64_t;






typedef signed char int_least8_t;
typedef short int int_least16_t;
typedef int int_least32_t;



__extension__
typedef long long int int_least64_t;



typedef unsigned char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned int uint_least32_t;



__extension__
typedef unsigned long long int uint_least64_t;






typedef signed char int_fast8_t;





typedef int int_fast16_t;
typedef int int_fast32_t;
__extension__
typedef long long int int_fast64_t;



typedef unsigned char uint_fast8_t;





typedef unsigned int uint_fast16_t;
typedef unsigned int uint_fast32_t;
__extension__
typedef unsigned long long int uint_fast64_t;
# 129 "/usr/include/stdint.h" 3 4
typedef unsigned int uintptr_t;
# 138 "/usr/include/stdint.h" 3 4
__extension__
typedef long long int intmax_t;
__extension__
typedef unsigned long long int uintmax_t;
# 4 "/usr/lib/gcc/i686-pc-linux-gnu/4.6.1/include/stdint.h" 2 3 4
# 34 "axml.h" 2
# 304 "axml.h"
typedef int boolean;


typedef struct {
  double lh;
  int tree;
  double weight;
} elw;

struct ent
{
  unsigned int *bitVector;
  unsigned int *treeVector;
  unsigned int amountTips;
  int *supportVector;
  unsigned int bipNumber;
  unsigned int bipNumber2;
  unsigned int supportFromTreeset[2];
  struct ent *next;
};

typedef struct ent entry;

typedef unsigned int hashNumberType;

typedef unsigned int parsimonyNumber;
# 346 "axml.h"
typedef struct
{
  hashNumberType tableSize;
  entry **table;
  hashNumberType entryCount;
}
  hashtable;


struct stringEnt
{
  int nodeNumber;
  char *word;
  struct stringEnt *next;
};

typedef struct stringEnt stringEntry;

typedef struct
{
  hashNumberType tableSize;
  stringEntry **table;
}
  stringHashtable;




typedef struct ratec
{
  double accumulatedSiteLikelihood;
  double rate;
}
  rateCategorize;


typedef struct
{
  int tipCase;
  int pNumber;
  int qNumber;
  int rNumber;
  double qz[128];
  double rz[128];
} traversalInfo;

typedef struct
{
  traversalInfo *ti;
  int count;
} traversalData;


struct noderec;

typedef struct epBrData
{
  int *countThem;
  int *executeThem;
  unsigned int *parsimonyScore;
  double *branches;
  double *distalBranches;
  double *likelihoods;
  double originalBranchLength;
  char branchLabel[64];
  int leftNodeNumber;
  int rightNodeNumber;
  int *leftScaling;
  int *rightScaling;
  double branchLengths[128];
  double *left;
  double *right;
  int branchNumber;
  int jointLabel;
} epaBranchData;

typedef struct
{
  epaBranchData *epa;

  unsigned int *vector;
  int support;
  struct noderec *oP;
  struct noderec *oQ;
} branchInfo;
# 439 "axml.h"
typedef struct
{
  boolean valid;
  int partitions;
  int *partitionList;
}
  linkageData;

typedef struct
{
  int entries;
  linkageData* ld;
}
  linkageList;


typedef struct noderec
{
  unsigned int isPresent[128 / 32];
  struct noderec *backs[128];
  char xs[128];
  branchInfo *bInf;
  double z[128];
  struct noderec *next;
  struct noderec *back;
  hashNumberType hash;
  int support;
  int number;
  char x;
}
  node, *nodeptr;

typedef struct
  {
    double lh;
    double pendantBranch;
    double distalBranch;
    int number;
  }
  info;

typedef struct bInf {
  double likelihood;
  nodeptr node;
} bestInfo;

typedef struct iL {
  bestInfo *list;
  int n;
  int valid;
} infoList;




typedef struct
{
  int numsp;
  int sites;
  unsigned char **y;
  unsigned char *y0;
  unsigned char *yBUF;
  int *wgt;
} rawdata;

typedef struct {
  int *alias;
  int *aliaswgt;
  int *rateCategory;
  int endsite;
  double *patrat;
  double *patratStored;
} cruncheddata;




typedef struct {
  int states;
  int maxTipStates;
  size_t lower;
  size_t upper;
  size_t width;
  int dataType;
  int protModels;
  boolean usePredefinedProtFreqs;
  int mxtips;
  int numberOfCategories;
  int **expVector;
  double **xVector;
  size_t *xSpaceVector;
  size_t *expSpaceVector;

  unsigned char **yVector;

  char *partitionName;
  char proteinSubstitutionFileName[2048];
  double externalAAMatrix[420];
  double *sumBuffer;

  double *gammaRates;

  double *EIGN;
  double *EV;



  double *EI;





  double *left;
  double *right;




  double *frequencies;
  double *tipVector;

  double *substRates;
  double *perSiteLL;

  double *perSiteRates;

  double *wr;
  double *wr2;



  unsigned int *globalScaler;
  double *globalScalerDouble;
  int *perSiteAAModel;
  int *wgt;
  int *invariant;
  int *rateCategory;
  int *symmetryVector;
  int *frequencyGrouping;
  boolean nonGTR;
  double alpha;
  double propInvariant;

  int gapVectorLength;
  unsigned int *gapVector;
  double *gapColumn;

  size_t initialGapVectorSize;

  size_t parsimonyLength;
  parsimonyNumber *parsVect;

} pInfo;



typedef struct
{
  int left;
  int right;
  double likelihood;
} lhEntry;


typedef struct
{
  int count;
  int size;
  lhEntry *entries;
} lhList;


typedef struct List_{
  void *value;
  struct List_ *next;
} List;


typedef struct {
  double EIGN[19];
  double EV[400];
  double EI[380];
  double substRates[190];
  double frequencies[20];
  double tipVector[460];
  double fracchange[1];
  double left[1600];
  double right[1600];
} siteAAModels;

typedef struct {
  siteAAModels siteProtModel[2 * (21 - 3)];

  boolean estimatePerSiteAA;

  boolean useGappedImplementation;
  boolean saveMemory;

  int *resample;

  int numberOfBranches;
  int numberOfTipsForInsertion;
  int *inserts;
  int branchCounter;

  int *ti;

  int numberOfTrees;

  stringHashtable *nameHash;

  pInfo *partitionData;
  pInfo *initialPartitionData;
  pInfo *extendedPartitionData;

  int *dataVector;
  int *initialDataVector;
  int *extendedDataVector;

  int *patternPosition;
  int *columnPosition;

  char *secondaryStructureInput;

  boolean *executeModel;

  double *perPartitionLH;
  double *storedPerPartitionLH;

  traversalData td[128];

  unsigned int *parsimonyScore;

  int maxCategories;

  double *wr;
  double *wr2;
  double *sumBuffer;
  double *perSiteLL;
  double coreLZ[128];
  int modelNumber;
  int multiBranch;
  int numBranches;
  int bootStopCriterion;
  int consensusType;
  double wcThreshold;

  int multiGene;

  nodeptr startVector[128];

  nodeptr removeNodes[128];
  nodeptr leftNodes[128];
  nodeptr rightNodes[128];
  nodeptr storedBacks[128];
  lhList *likelihoodList[128];

  double zLeft[128];
  double zRight[128];
  double zDown[128];

  boolean useFastScaling;

  branchInfo *bInf;

  int multiStateModel;


  size_t innerNodes;

  boolean curvatOK[128];



  double *invariants;
  double *fracchanges;



  unsigned char **yVector;
  int secondaryStructureModel;
  int discreteRateCategories;
  int originalCrunchedLength;
  int fullSites;
  int *originalModel;
  int *originalDataVector;
  int *originalWeights;
  int *secondaryStructurePairs;


  double *partitionContributions;
  double fracchange;
  double lhCutoff;
  double lhAVG;
  unsigned long lhDEC;
  unsigned long itCount;
  int numberOfInvariableColumns;
  int weightOfInvariableColumns;
  int rateHetModel;

  double startLH;
  double endLH;
  double likelihood;
  double *likelihoods;
  int *invariant;
  node **nodep;
  node *start;
  int mxtips;
  int mxtipsVector[128];
  int *model;

  int *constraintVector;
  int numberOfSecondaryColumns;
  boolean searchConvergenceCriterion;
  int ntips;
  int nextnode;
  int NumberOfModels;
  int parsimonyLength;

  int checkPointCounter;
  int treeID;
  int numberOfOutgroups;
  int *outgroupNums;
  char **outgroups;
  boolean useEpaHeuristics;
  double fastEPAthreshold;
  boolean bigCutoff;
  boolean partitionSmoothed[128];
  boolean partitionConverged[128];
  boolean rooted;
  boolean grouped;
  boolean constrained;
  boolean doCutoff;
  boolean catOnly;
  rawdata *rdta;
  cruncheddata *cdta;

  char **nameList;
  char *tree_string;
  int treeStringLength;
  unsigned int bestParsimony;
  double bestOfNode;
  nodeptr removeNode;
  nodeptr insertNode;

  double zqr[128];
  double currentZQR[128];

  double currentLZR[128];
  double currentLZQ[128];
  double currentLZS[128];
  double currentLZI[128];
  double lzs[128];
  double lzq[128];
  double lzr[128];
  double lzi[128];


  int mr_thresh;

  boolean wasRooted;
  nodeptr leftRootNode;
  nodeptr rightRootNode;
  int rootLabel;
# 884 "axml.h"
} tree;




typedef struct
{
  double z[128];
  nodeptr p, q;
  int cp, cq;
}
  connectRELL, *connptrRELL;

typedef struct
{
  connectRELL *connect;
  int start;
  double likelihood;
}
  topolRELL;


typedef struct
{
  int max;
  topolRELL **t;
}
  topolRELL_LIST;






typedef struct conntyp {
    double z[128];
    node *p, *q;
    void *valptr;
    int descend;
    int sibling;
    } connect, *connptr;

typedef struct {
    double likelihood;
  int initialTreeNumber;
    connect *links;
    node *start;
    int nextlink;

    int ntips;
    int nextnode;
    int scrNum;
    int tplNum;

    } topol;

typedef struct {
    double best;
    double worst;
    topol *start;
    topol **byScore;
    topol **byTopol;
    int nkeep;
    int nvalid;
    int ninit;
    int numtrees;
    boolean improved;
    } bestlist;

typedef struct {
  int categories;
  int model;
  int bestTrav;
  int max_rearrange;
  int stepwidth;
  int initial;
  boolean initialSet;
  int mode;
  long boot;
  long rapidBoot;
  boolean bootstrapBranchLengths;
  boolean restart;
  boolean useWeightFile;
  boolean useMultipleModel;
  boolean constraint;
  boolean grouping;
  boolean randomStartingTree;
  boolean useInvariant;
  int protEmpiricalFreqs;
  int proteinMatrix;
  int checkpoints;
  int startingTreeOnly;
  int multipleRuns;
  long parsimonySeed;
  boolean perGeneBranchLengths;
  boolean likelihoodTest;
  boolean outgroup;
  boolean permuteTreeoptimize;
  boolean allInOne;
  boolean generateBS;
  boolean bootStopping;
  boolean useExcludeFile;
  boolean userProteinModel;
  boolean computeELW;
  boolean computeDistance;
  boolean compressPatterns;
  boolean useSecondaryStructure;
  double likelihoodEpsilon;
  double gapyness;
  int similarityFilterMode;
  double externalAAMatrix[420];
  boolean useFloat;
  boolean readTaxaOnly;
  int meshSearch;
  boolean veryFast;
  boolean useBinaryModelFile;
  boolean leaveDropMode;
  int slidingWindowSize;
} analdef;


typedef struct
{
  int leftLength;
  int rightLength;
  int eignLength;
  int evLength;
  int eiLength;
  int substRatesLength;
  int frequenciesLength;
  int tipVectorLength;
  int symmetryVectorLength;
  int frequencyGroupingLength;

  boolean nonGTR;

  int undetermined;

  const char *inverseMeaning;

  int states;

  boolean smoothFrequencies;

  const unsigned int *bitVector;

} partitionLengths;



extern void computePlacementBias(tree *tr, analdef *adef);

extern int lookupWord(char *s, stringHashtable *h);

extern void getDataTypeString(tree *tr, int model, char typeOfData[1024]);

extern unsigned int genericBitCount(unsigned int* bitVector, unsigned int bitVectorLength);
extern int countTips(nodeptr p, int numsp);
extern entry *initEntry(void);
extern void computeRogueTaxa(tree *tr, char* treeSetFileName, analdef *adef);
extern unsigned int precomputed16_bitcount(unsigned int n);


extern double evaluateGenericMulti (tree *tr, nodeptr p, int model);
extern void setupPointerMesh(tree *tr);
extern void determineFullTraversalMulti(nodeptr p, tree *tr);
extern void computeTraversalInfoMulti(nodeptr p, traversalInfo *ti, int *counter, int maxTips, int model);
extern double evaluateIterativeMulti(tree *, boolean writeVector);
extern void newviewIterativeMulti (tree *tr);
extern void getxsnode (nodeptr p, int model);
extern void findNext(nodeptr p, tree *tr, nodeptr *result);




extern partitionLengths * getPartitionLengths(pInfo *p);
extern boolean getSmoothFreqs(int dataType);
extern const unsigned int *getBitVector(int dataType);
extern int getUndetermined(int dataType);
extern int getStates(int dataType);
extern char getInverseMeaning(int dataType, unsigned char state);
extern void printModelParams(tree *tr, analdef *adef);
extern double gettime ( void );
extern int gettimeSrand ( void );
extern double randum ( long *seed );

extern void getxnode ( nodeptr p );
extern void hookup ( nodeptr p, nodeptr q, double *z, int numBranches);
extern void hookupDefault ( nodeptr p, nodeptr q, int numBranches);
extern boolean whitechar ( int ch );
extern void errorExit ( int e );
extern void printResult ( tree *tr, analdef *adef, boolean finalPrint );
extern void printBootstrapResult ( tree *tr, analdef *adef, boolean finalPrint );
extern void printBipartitionResult ( tree *tr, analdef *adef, boolean finalPrint );
extern void printLog ( tree *tr, analdef *adef, boolean finalPrint );
extern void printStartingTree ( tree *tr, analdef *adef, boolean finalPrint );
extern void writeInfoFile ( analdef *adef, tree *tr, double t );
extern int main ( int argc, char *argv[] );
extern void calcBipartitions ( tree *tr, analdef *adef, char *bestTreeFileName, char *bootStrapFileName );
extern void initReversibleGTR (tree *tr, int model);
extern double LnGamma ( double alpha );
extern double IncompleteGamma ( double x, double alpha, double ln_gamma_alpha );
extern double PointNormal ( double prob );
extern double PointChi2 ( double prob, double v );
extern void makeGammaCats (double alpha, double *gammaRates, int K);
extern void initModel ( tree *tr, rawdata *rdta, cruncheddata *cdta, analdef *adef );
extern void doAllInOne ( tree *tr, analdef *adef );

extern void classifyML(tree *tr, analdef *adef);
extern void classifyMP(tree *tr, analdef *adef);
extern void markTips(nodeptr p, int *perm, int maxTips);
extern char *Tree2StringClassify(char *treestr, tree *tr, int *inserts,
     boolean originalTree, boolean jointLabels);


extern void doBootstrap ( tree *tr, analdef *adef, rawdata *rdta, cruncheddata *cdta );
extern void doInference ( tree *tr, analdef *adef, rawdata *rdta, cruncheddata *cdta );
extern void resetBranches ( tree *tr );
extern void modOpt ( tree *tr, analdef *adef , boolean resetModel, double likelihoodEpsilon, boolean testGappedImplementation);


extern void parsePartitions ( analdef *adef, rawdata *rdta, tree *tr);
extern void computeBOOTRAPID (tree *tr, analdef *adef, long *radiusSeed);
extern void optimizeRAPID ( tree *tr, analdef *adef );
extern void thoroughOptimization ( tree *tr, analdef *adef, topolRELL_LIST *rl, int index );
extern int treeOptimizeThorough ( tree *tr, int mintrav, int maxtrav);

extern int checker ( tree *tr, nodeptr p );
extern int randomInt ( int n );
extern void makePermutation ( int *perm, int n, analdef *adef );
extern boolean tipHomogeneityChecker ( tree *tr, nodeptr p, int grouping );
extern void makeRandomTree ( tree *tr, analdef *adef );
extern void nodeRectifier ( tree *tr );
extern void makeParsimonyTreeThorough(tree *tr, analdef *adef);
extern void makeParsimonyTree ( tree *tr, analdef *adef );
extern void makeParsimonyTreeFast(tree *tr, analdef *adef, boolean full);
extern void makeParsimonyTreeIncomplete ( tree *tr, analdef *adef );
extern void makeParsimonyInsertions(tree *tr, nodeptr startNodeQ, nodeptr startNodeR);



extern FILE *myfopen(const char *path, const char *mode);


extern boolean initrav ( tree *tr, nodeptr p );
extern void initravPartition ( tree *tr, nodeptr p, int model );
extern boolean update ( tree *tr, nodeptr p );
extern boolean smooth ( tree *tr, nodeptr p );
extern boolean smoothTree ( tree *tr, int maxtimes );
extern boolean localSmooth ( tree *tr, nodeptr p, int maxtimes );
extern boolean localSmoothMulti(tree *tr, nodeptr p, int maxtimes, int model);
extern void initInfoList ( int n );
extern void freeInfoList ( void );
extern void insertInfoList ( nodeptr node, double likelihood );
extern boolean smoothRegion ( tree *tr, nodeptr p, int region );
extern boolean regionalSmooth ( tree *tr, nodeptr p, int maxtimes, int region );
extern nodeptr removeNodeBIG ( tree *tr, nodeptr p, int numBranches);
extern nodeptr removeNodeRestoreBIG ( tree *tr, nodeptr p );
extern boolean insertBIG ( tree *tr, nodeptr p, nodeptr q, int numBranches);
extern boolean insertRestoreBIG ( tree *tr, nodeptr p, nodeptr q );
extern boolean testInsertBIG ( tree *tr, nodeptr p, nodeptr q );
extern void addTraverseBIG ( tree *tr, nodeptr p, nodeptr q, int mintrav, int maxtrav );
extern int rearrangeBIG ( tree *tr, nodeptr p, int mintrav, int maxtrav );
extern void traversalOrder ( nodeptr p, int *count, nodeptr *nodeArray );
extern double treeOptimizeRapid ( tree *tr, int mintrav, int maxtrav, analdef *adef, bestlist *bt);
extern boolean testInsertRestoreBIG ( tree *tr, nodeptr p, nodeptr q );
extern void restoreTreeFast ( tree *tr );
extern int determineRearrangementSetting ( tree *tr, analdef *adef, bestlist *bestT, bestlist *bt );
extern void computeBIGRAPID ( tree *tr, analdef *adef, boolean estimateModel);
extern boolean treeEvaluate ( tree *tr, double smoothFactor );
extern boolean treeEvaluatePartition ( tree *tr, double smoothFactor, int model );

extern void meshTreeSearch(tree *tr, analdef *adef, int thorough);

extern void initTL ( topolRELL_LIST *rl, tree *tr, int n );
extern void freeTL ( topolRELL_LIST *rl);
extern void restoreTL ( topolRELL_LIST *rl, tree *tr, int n );
extern void resetTL ( topolRELL_LIST *rl );
extern void saveTL ( topolRELL_LIST *rl, tree *tr, int index );

extern int saveBestTree (bestlist *bt, tree *tr);
extern int recallBestTree (bestlist *bt, int rank, tree *tr);
extern int initBestTree ( bestlist *bt, int newkeep, int numsp );
extern void resetBestTree ( bestlist *bt );
extern boolean freeBestTree ( bestlist *bt );


extern char *Tree2String ( char *treestr, tree *tr, nodeptr p, boolean printBranchLengths, boolean printNames, boolean printLikelihood,
      boolean rellTree, boolean finalPrint, analdef *adef, int perGene, boolean branchLabelSupport, boolean printSHSupport);
extern void printTreePerGene(tree *tr, analdef *adef, char *fileName, char *permission);



extern int treeReadLen (FILE *fp, tree *tr, boolean readBranches, boolean readNodeLabels, boolean topologyOnly, analdef *adef, boolean completeTree);
extern boolean treeReadLenMULT ( FILE *fp, tree *tr, analdef *adef );

extern void getStartingTree ( tree *tr, analdef *adef );
extern double treeLength(tree *tr, int model);

extern void computeBootStopOnly(tree *tr, char *bootStrapFileName, analdef *adef);
extern boolean bootStop(tree *tr, hashtable *h, int numberOfTrees, double *pearsonAverage, unsigned int **bitVectors, int treeVectorLength, unsigned int vectorLength);
extern void computeConsensusOnly(tree *tr, char* treeSetFileName, analdef *adef);
extern double evaluatePartialGeneric (tree *, int i, double ki, int _model);
extern double evaluateGeneric (tree *tr, nodeptr p);
extern void newviewGeneric (tree *tr, nodeptr p);
extern void newviewGenericMulti (tree *tr, nodeptr p, int model);
extern void newviewGenericMasked (tree *tr, nodeptr p);
extern void makenewzGeneric(tree *tr, nodeptr p, nodeptr q, double *z0, int maxiter, double *result, boolean mask);
extern void makenewzGenericDistance(tree *tr, int maxiter, double *z0, double *result, int taxon1, int taxon2);
extern double evaluatePartitionGeneric (tree *tr, nodeptr p, int model);
extern void newviewPartitionGeneric (tree *tr, nodeptr p, int model);
extern double evaluateGenericVector (tree *tr, nodeptr p);
extern void categorizeGeneric (tree *tr, nodeptr p);
extern double makenewzPartitionGeneric(tree *tr, nodeptr p, nodeptr q, double z0, int maxiter, int model);
extern boolean isTip(int number, int maxTips);
extern void computeTraversalInfo(nodeptr p, traversalInfo *ti, int *counter, int maxTips, int numBranches);



extern void newviewIterative(tree *);

extern double evaluateIterative(tree *, boolean writeVector);

extern void *malloc_aligned( size_t size, size_t align);





extern void makenewzIterative(tree *);
extern void execCore(tree *, volatile double *dlnLdlz, volatile double *d2lnLdlz2);



extern void determineFullTraversal(nodeptr p, tree *tr);


extern unsigned int evaluateParsimonyIterative(tree *);
extern void newviewParsimonyIterative(tree *);

extern unsigned int evaluateParsimonyIterativeFast(tree *);
extern void newviewParsimonyIterativeFast(tree *);


extern void initravParsimonyNormal(tree *tr, nodeptr p);

extern double evaluateGenericInitrav (tree *tr, nodeptr p);
extern double evaluateGenericInitravPartition(tree *tr, nodeptr p, int model);
extern void evaluateGenericVectorIterative(tree *, int startIndex, int endIndex);
extern void categorizeIterative(tree *, int startIndex, int endIndex);
extern void onlyInitrav(tree *tr, nodeptr p);
extern void onlyInitravPartition(tree *tr, nodeptr p, int model);

extern void fixModelIndices(tree *tr, int endsite, boolean fixRates);
extern void calculateModelOffsets(tree *tr);
extern void gammaToCat(tree *tr);
extern void catToGamma(tree *tr, analdef *adef);
extern void handleExcludeFile(tree *tr, analdef *adef, rawdata *rdta);
extern void printBaseFrequencies(tree *tr);
extern nodeptr findAnyTip(nodeptr p, int numsp);

extern void parseProteinModel(double *externalAAMatrix, char *fileName);
extern int filexists(char *filename);
extern void computeFullTraversalInfo(nodeptr p, traversalInfo *ti, int *counter, int maxTips, int numBranches);

extern void computeNextReplicate(tree *tr, long *seed, int *originalRateCategories, int *originalInvariant, boolean isRapid, boolean fixRates);


extern void reductionCleanup(tree *tr, int *originalRateCategories, int *originalInvariant);
extern void parseSecondaryStructure(tree *tr, analdef *adef, int sites);
extern void printPartitions(tree *tr);
extern void calcDiagptable(double z, int data, int numberOfCategories, double *rptr, double *EIGN, double *diagptable);
extern void compareBips(tree *tr, char *bootStrapFileName, analdef *adef);
extern void computeRF(tree *tr, char *bootStrapFileName, analdef *adef);


extern unsigned int **initBitVector(tree *tr, unsigned int *vectorLength);
extern hashtable *copyHashTable(hashtable *src, unsigned int vectorLength);
extern hashtable *initHashTable(unsigned int n);
extern void cleanupHashTable(hashtable *h, int state);
extern double convergenceCriterion(hashtable *h, int mxtips);
extern void freeBitVectors(unsigned int **v, int n);
extern void freeHashTable(hashtable *h);
extern stringHashtable *initStringHashTable(hashNumberType n);
extern void addword(char *s, stringHashtable *h, int nodeNumber);


extern void printBothOpen(const char* format, ... );
extern void printBothOpenMPI(const char* format, ... );
extern void initRateMatrix(tree *tr);

extern void bitVectorInitravSpecial(unsigned int **bitVectors, nodeptr p, int numsp, unsigned int vectorLength, hashtable *h, int treeNumber, int function, branchInfo *bInf,
        int *countBranches, int treeVectorLength, boolean traverseOnly, boolean computeWRF);

extern int getIncrement(tree *tr, int model);

extern void fastSearch(tree *tr, analdef *adef, rawdata *rdta, cruncheddata *cdta);
extern void shSupports(tree *tr, analdef *adef, rawdata *rdta, cruncheddata *cdta);

extern FILE *getNumberOfTrees(tree *tr, char *fileName, analdef *adef);

extern void writeBinaryModel(tree *tr);
extern void readBinaryModel(tree *tr);
extern void treeEvaluateRandom (tree *tr, double smoothFactor);
extern void treeEvaluateProgressive(tree *tr);

extern void testGapped(tree *tr);

extern boolean issubset(unsigned int* bipA, unsigned int* bipB, unsigned int vectorLen);
extern boolean compatible(entry* e1, entry* e2, unsigned int bvlen);



extern int *permutationSH(tree *tr, int nBootstrap, long _randomSeed);

extern void updatePerSiteRates(tree *tr, boolean scaleRates);

extern void newviewIterativeAncestral(tree *tr);
extern void newviewGenericAncestral(tree *tr, nodeptr p, boolean atRoot);
extern void computeAncestralStates(tree *tr, double referenceLikelihood, analdef *adef);
extern void makeP_Flex(double z1, double z2, double *rptr, double *EI, double *EIGN, int numberOfCategories, double *left, double *right, const int numStates);
# 75 "<stdin>" 2
# 1 "globalVariables.h" 1
# 40 "globalVariables.h"
int processID;
infoList iList;
FILE *INFILE;

int Thorough = 0;



char run_id[128] = "",
  workdir[1024] = "",
  seq_file[1024] = "",
  tree_file[1024]="",
  weightFileName[1024] = "",
  modelFileName[1024] = "",
  excludeFileName[1024] = "",
  bootStrapFile[1024] = "",
  permFileName[1024] = "",
  resultFileName[1024] = "",
  logFileName[1024] = "",
  checkpointFileName[1024] = "",
  infoFileName[1024] = "",
  randomFileName[1024] = "",
  bootstrapFileName[1024] = "",
  bootstrapFileNamePID[1024] = "",
  bipartitionsFileName[1024] = "",
  bipartitionsFileNameBranchLabels[1024] = "",
  ratesFileName[1024] = "",
  perSiteLLsFileName[1024] = "",
  lengthFileName[1024] = "",
  lengthFileNameModel[1024] = "",
  proteinModelFileName[1024] = "",
  secondaryStructureFileName[1024] = "",
  binaryModelParamsOutputFileName[1024] = "",
  binaryModelParamsInputFileName[1024] = "";




char *protModels[21] = {"DAYHOFF", "DCMUT", "JTT", "MTREV", "WAG", "RTREV", "CPREV", "VT",
         "BLOSUM62", "MTMAM", "LG", "MTART", "MTZOA", "PMB", "HIVB", "HIVW",
         "JTTDCMUT", "FLU", "PROT_FILE", "GTR_UNLINKED", "GTR"};

const char binaryStateNames[2] = {'0', '1'};
const char dnaStateNames[4] = {'A', 'C', 'G', 'T'};
const char protStateNames[20] = {'A','R', 'N', 'D', 'C', 'Q', 'E', 'G', 'H',
        'I', 'L', 'K', 'M', 'F', 'P', 'S', 'T', 'W',
        'Y', 'V'};
const char genericStateNames[32] = {'0', '1', '2', '3', '4', '5', '6', '7',
        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
        'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
        'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V'};

const char inverseMeaningBINARY[4] = {'_', '0', '1', '-'};
const char inverseMeaningDNA[16] = {'_', 'A', 'C', 'M', 'G', 'R', 'S', 'V', 'T', 'W', 'Y', 'H', 'K', 'D', 'B', '-'};
const char inverseMeaningPROT[23] = {'A','R', 'N', 'D', 'C', 'Q', 'E', 'G', 'H', 'I', 'L', 'K', 'M', 'F', 'P', 'S',
          'T', 'W', 'Y', 'V', 'B', 'Z', '-'};
const char inverseMeaningGeneric32[33] = {'0', '1', '2', '3', '4', '5', '6', '7',
        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
        'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
        'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
        '-'};
const char inverseMeaningGeneric64[33] = {'0', '1', '2', '3', '4', '5', '6', '7',
        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
        'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
        'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
        '-'};

const unsigned int bitVectorIdentity[256] = {0 ,1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9 ,10 ,11 ,12 ,13 ,14 ,15 ,16 ,17 ,18 ,19 ,20 ,21 ,22 ,23 ,24 ,25 ,26 ,
          27 ,28 ,29 ,30 ,31 ,32 ,33 ,34 ,35 ,36 ,37 ,38 ,39 ,40 ,41 ,42 ,43 ,44 ,45 ,46 ,47 ,48 ,49 ,50 ,51 ,
          52 ,53 ,54 ,55 ,56 ,57 ,58 ,59 ,60 ,61 ,62 ,63 ,64 ,65 ,66 ,67 ,68 ,69 ,70 ,71 ,72 ,73 ,74 ,75 ,76 ,
          77 ,78 ,79 ,80 ,81 ,82 ,83 ,84 ,85 ,86 ,87 ,88 ,89 ,90 ,91 ,92 ,93 ,94 ,95 ,96 ,97 ,98 ,99 ,100 ,101 ,
          102 ,103 ,104 ,105 ,106 ,107 ,108 ,109 ,110 ,111 ,112 ,113 ,114 ,115 ,116 ,117 ,118 ,119 ,120 ,121 ,122 ,
          123 ,124 ,125 ,126 ,127 ,128 ,129 ,130 ,131 ,132 ,133 ,134 ,135 ,136 ,137 ,138 ,139 ,140 ,141 ,142 ,143 ,
          144 ,145 ,146 ,147 ,148 ,149 ,150 ,151 ,152 ,153 ,154 ,155 ,156 ,157 ,158 ,159 ,160 ,161 ,162 ,163 ,164 ,
          165 ,166 ,167 ,168 ,169 ,170 ,171 ,172 ,173 ,174 ,175 ,176 ,177 ,178 ,179 ,180 ,181 ,182 ,183 ,184 ,185 ,
          186 ,187 ,188 ,189 ,190 ,191 ,192 ,193 ,194 ,195 ,196 ,197 ,198 ,199 ,200 ,201 ,202 ,203 ,204 ,205 ,206 ,
          207 ,208 ,209 ,210 ,211 ,212 ,213 ,214 ,215 ,216 ,217 ,218 ,219 ,220 ,221 ,222 ,223 ,224 ,225 ,226 ,227 ,
          228 ,229 ,230 ,231 ,232 ,233 ,234 ,235 ,236 ,237 ,238 ,239 ,240 ,241 ,242 ,243 ,244 ,245 ,246 ,247 ,248 ,
          249 ,250 ,251 ,252 ,253 ,254 ,255};



const unsigned int bitVectorAA[23] = {1, 2, 4, 8, 16, 32, 64, 128,
          256, 512, 1024, 2048, 4096,
          8192, 16384, 32768, 65536, 131072, 262144,
          524288, 12 , 96 , 1048575 };

const unsigned int bitVectorSecondary[256] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
           10, 11, 12, 13, 14, 15, 0, 16, 32, 48, 64, 80, 96, 112, 128, 144, 160, 176, 192,
           208, 224, 240, 0, 17, 34, 51, 68, 85, 102, 119, 136, 153, 170, 187, 204, 221, 238,
           255, 0, 256, 512, 768, 1024, 1280, 1536, 1792, 2048, 2304, 2560, 2816, 3072, 3328,
           3584, 3840, 0, 257, 514, 771, 1028, 1285, 1542, 1799, 2056, 2313, 2570, 2827, 3084,
           3341, 3598, 3855, 0, 272, 544, 816, 1088, 1360, 1632, 1904, 2176, 2448, 2720, 2992,
           3264, 3536, 3808, 4080, 0, 273, 546, 819, 1092, 1365, 1638, 1911, 2184, 2457, 2730,
           3003, 3276, 3549, 3822, 4095, 0, 4096, 8192, 12288, 16384, 20480, 24576, 28672, 32768,
           36864, 40960, 45056, 49152, 53248, 57344, 61440, 0, 4097, 8194, 12291, 16388, 20485, 24582,
           28679, 32776, 36873, 40970, 45067, 49164, 53261, 57358, 61455, 0, 4112, 8224, 12336, 16448,
           20560, 24672, 28784, 32896, 37008, 41120, 45232, 49344, 53456, 57568, 61680, 0, 4113, 8226,
           12339, 16452, 20565, 24678, 28791, 32904, 37017, 41130, 45243, 49356, 53469, 57582, 61695,
           0, 4352, 8704, 13056, 17408, 21760, 26112, 30464, 34816, 39168, 43520, 47872, 52224, 56576,
           60928, 65280, 0, 4353, 8706, 13059, 17412, 21765, 26118, 30471, 34824, 39177, 43530, 47883,
           52236, 56589, 60942, 65295, 0, 4368, 8736, 13104, 17472, 21840, 26208, 30576, 34944, 39312,
           43680, 48048, 52416, 56784, 61152, 65520, 0, 4369, 8738, 13107, 17476, 21845, 26214, 30583,
           34952, 39321, 43690, 48059, 52428, 56797, 61166, 65535};

const unsigned int bitVector32[33] = {1, 2, 4, 8, 16, 32, 64, 128,
                                      256, 512, 1024, 2048, 4096, 8192, 16384, 32768,
                                      65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608,
                                      16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648u,
          4294967295u};



const unsigned int mask32[32] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072,
     262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728,
     268435456, 536870912, 1073741824, 2147483648U};

const char *secondaryModelList[21] = { "S6A (GTR)", "S6B", "S6C", "S6D", "S6E", "S7A (GTR)", "S7B", "S7C", "S7D", "S7E", "S7F", "S16 (GTR)", "S16A", "S16B", "S16C",
           "S16D", "S16E", "S16F", "S16I", "S16J", "S16K"};

double masterTime;
int partCount = 0;
int optimizeRateCategoryInvocations = 1;





partitionLengths pLengths[8] = {


  {4, 4, 1, 4, 2, 1, 2, 8, 2, 2, 0, 3, inverseMeaningBINARY, 2, 0, bitVectorIdentity},


  {16, 16, 3, 16, 12, 6, 4, 64, 6, 4, 0, 15, inverseMeaningDNA, 4, 0, bitVectorIdentity},


  {400, 400, 19, 400, 380, 190, 20, 460, 190, 20, 0, 22, inverseMeaningPROT, 20, 1, bitVectorAA},



  {256, 256, 15, 256, 240, 120, 16, 4096, 120, 16, 0, 255, (char*)((void *)0), 16, 1, bitVectorSecondary},



  {36, 36, 5, 36, 30, 15, 6, 384, 15, 6, 0, 63, (char*)((void *)0), 6, 1, bitVectorIdentity},



  {49, 49, 6, 49, 42, 21, 7, 896, 21, 7, 0, 127, (char*)((void *)0), 7, 1, bitVectorIdentity},


  {1024, 1024, 31, 1024, 992, 496, 32, 1056, 496, 32, 0, 32, inverseMeaningGeneric32, 32, 1, bitVector32},


  {4096, 4096, 63, 4096, 4032, 2016, 64, 4160, 64, 2016, 0, 64, (char*)((void *)0), 64, 1, (unsigned int*)((void *)0)}
};

partitionLengths pLength;
# 76 "<stdin>" 2
# 88 "<stdin>"
void *malloc_aligned(size_t size, size_t align)
{
  void *ptr = (void *)((void *)0);
  int res;
# 108 "<stdin>"
  res = posix_memalign( &ptr, align, size );

  if(res != 0)
    ((0) ? (void) (0) : __assert_fail ("0", "<stdin>", 111, __PRETTY_FUNCTION__));
# 126 "<stdin>"
  return ptr;
}




FILE *getNumberOfTrees(tree *tr, char *fileName, analdef *adef)
{
  FILE
    *f = myfopen(fileName, "r");

  int
    trees = 0,
    ch;

  while((ch = fgetc(f)) != (-1))
    if(ch == ';')
      trees++;

  ((trees > 0) ? (void) (0) : __assert_fail ("trees > 0", "<stdin>", 145, __PRETTY_FUNCTION__));

  tr->numberOfTrees = trees;

  if(!adef->allInOne)
    printBothOpen("\n\nFound %d trees in File %s\n\n", trees, fileName);


  rewind(f);

  return f;
}

static void printBoth(FILE *f, const char* format, ... )
{
  va_list args;
  __builtin_va_start(args,format);
  vfprintf(f, format, args );
  __builtin_va_end(args);

  __builtin_va_start(args,format);
  vprintf(format, args );
  __builtin_va_end(args);
}

void printBothOpen(const char* format, ... )
{
  FILE *f = myfopen(infoFileName, "ab");

  va_list args;
  __builtin_va_start(args,format);
  vfprintf(f, format, args );
  __builtin_va_end(args);

  __builtin_va_start(args,format);
  vprintf(format, args );
  __builtin_va_end(args);

  fclose(f);
}

void printBothOpenMPI(const char* format, ... )
{



    {
      FILE *f = myfopen(infoFileName, "ab");

      va_list args;
      __builtin_va_start(args,format);
      vfprintf(f, format, args );
      __builtin_va_end(args);

      __builtin_va_start(args,format);
      vprintf(format, args );
      __builtin_va_end(args);

      fclose(f);
    }
}


boolean getSmoothFreqs(int dataType)
{
  ((-1 < dataType && dataType < 8) ? (void) (0) : __assert_fail ("-1 < dataType && dataType < 8", "<stdin>", 210, __PRETTY_FUNCTION__));

  return pLengths[dataType].smoothFrequencies;
}

const unsigned int *getBitVector(int dataType)
{
  ((-1 < dataType && dataType < 8) ? (void) (0) : __assert_fail ("-1 < dataType && dataType < 8", "<stdin>", 217, __PRETTY_FUNCTION__));

  return pLengths[dataType].bitVector;
}


int getStates(int dataType)
{
  ((-1 < dataType && dataType < 8) ? (void) (0) : __assert_fail ("-1 < dataType && dataType < 8", "<stdin>", 225, __PRETTY_FUNCTION__));

  return pLengths[dataType].states;
}

int getUndetermined(int dataType)
{
  ((-1 < dataType && dataType < 8) ? (void) (0) : __assert_fail ("-1 < dataType && dataType < 8", "<stdin>", 232, __PRETTY_FUNCTION__));

  return pLengths[dataType].undetermined;
}



char getInverseMeaning(int dataType, unsigned char state)
{
  ((-1 < dataType && dataType < 8) ? (void) (0) : __assert_fail ("-1 < dataType && dataType < 8", "<stdin>", 241, __PRETTY_FUNCTION__));

  return pLengths[dataType].inverseMeaning[state];
}

partitionLengths *getPartitionLengths(pInfo *p)
{
  int
    dataType = p->dataType,
    states = p->states,
    tipLength = p->maxTipStates;

  ((states != -1 && tipLength != -1) ? (void) (0) : __assert_fail ("states != -1 && tipLength != -1", "<stdin>", 253, __PRETTY_FUNCTION__));

  ((-1 < dataType && dataType < 8) ? (void) (0) : __assert_fail ("-1 < dataType && dataType < 8", "<stdin>", 255, __PRETTY_FUNCTION__));

  pLength.leftLength = pLength.rightLength = states * states;
  pLength.eignLength = states -1;
  pLength.evLength = states * states;
  pLength.eiLength = states * states - states;
  pLength.substRatesLength = (states * states - states) / 2;
  pLength.frequenciesLength = states;
  pLength.tipVectorLength = tipLength * states;
  pLength.symmetryVectorLength = (states * states - states) / 2;
  pLength.frequencyGroupingLength = states;
  pLength.nonGTR = 0;

  return (&pLengths[dataType]);
}



static boolean isCat(analdef *adef)
{
  if(adef->model == 5 || adef->model == 1 || adef->model == 3 || adef->model == 7 || adef->model == 9)
    return 1;
  else
    return 0;
}

static boolean isGamma(analdef *adef)
{
  if(adef->model == 6 || adef->model == 2 || adef->model == 4 ||
     adef->model == 8 || adef->model == 10)
    return 1;
  else
    return 0;
}


static int stateAnalyzer(tree *tr, int model, int maxStates)
{
  boolean
    counter[256],
    previous,
    inputError = 0;

  int
    lower = tr->partitionData[model].lower,
    upper = tr->partitionData[model].upper,
    i,
    j,
    states = 0;

  for(i = 0; i < 256; i++)
    counter[i] = 0;

  for(i = 0; i < tr->rdta->numsp; i++)
    {
      unsigned char *yptr = &(tr->rdta->y0[((size_t)i) * ((size_t)tr->originalCrunchedLength)]);

      for(j = lower; j < upper; j++)
 if(yptr[j] != getUndetermined(6))
   counter[yptr[j]] = 1;

    }

  for(i = 0; i < maxStates; i++)
    {
      if(counter[i])
 states++;
    }


  previous = counter[0];

  for(i = 1; i < 256; i++)
    {
      if(previous == 0 && counter[i] == 1)
 {
   inputError = 1;
   break;
 }
      else
 {
   if(previous == 1 && counter[i] == 0)
     previous = 0;
 }
    }

  if(inputError)
    {
      printf("Multi State Error, characters must be used in the order they are available, i.e.\n");
      printf("0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V\n");
      printf("You are using the following characters: \n");
      for(i = 0; i < 256; i++)
 if(counter[i])
   printf("%c ", inverseMeaningGeneric32[i]);
      printf("\n");
      exit(-1);
    }

  return states;
}




static void setRateHetAndDataIncrement(tree *tr, analdef *adef)
{
  int model;

  if(isCat(adef))
    tr->rateHetModel = 0;
  else
    {
      if(adef->useInvariant)
 tr->rateHetModel = 2;
      else
 tr->rateHetModel = 1;
    }

  switch(tr->rateHetModel)
    {
    case 1:
    case 2:
      tr->discreteRateCategories = 4;
      break;
    case 0:
      if((adef->boot && !adef->bootstrapBranchLengths) || (adef->mode == 9) || (tr->catOnly))
 tr->discreteRateCategories = 1;
      else
 tr->discreteRateCategories = 4;
      break;
    default:
      ((0) ? (void) (0) : __assert_fail ("0", "<stdin>", 386, __PRETTY_FUNCTION__));
    }

  for(model = 0; model < tr->NumberOfModels; model++)
    {
      int
 states = -1,
 maxTipStates = getUndetermined(tr->partitionData[model].dataType) + 1;

      switch(tr->partitionData[model].dataType)
 {
 case 0:
 case 1:
 case 2:
 case 3:
 case 4:
 case 5:
   states = getStates(tr->partitionData[model].dataType);
   break;
 case 6:
 case 7:
   states = stateAnalyzer(tr, model, getStates(tr->partitionData[model].dataType));
   break;
 default:
   ((0) ? (void) (0) : __assert_fail ("0", "<stdin>", 410, __PRETTY_FUNCTION__));
 }

      tr->partitionData[model].states = states;
      tr->partitionData[model].maxTipStates = maxTipStates;
    }
}


double gettime(void)
{







  struct timeval ttime;
  gettimeofday(&ttime , ((void *)0));
  return ttime.tv_sec + ttime.tv_usec * 0.000001;

}

int gettimeSrand(void)
{







  struct timeval ttime;
  gettimeofday(&ttime , ((void *)0));
  return ttime.tv_sec + ttime.tv_usec;

}

double randum (long *seed)
{
  long sum, mult0, mult1, seed0, seed1, seed2, newseed0, newseed1, newseed2;
  double res;

  mult0 = 1549;
  seed0 = *seed & 4095;
  sum = mult0 * seed0;
  newseed0 = sum & 4095;
  sum >>= 12;
  seed1 = (*seed >> 12) & 4095;
  mult1 = 406;
  sum += mult0 * seed1 + mult1 * seed0;
  newseed1 = sum & 4095;
  sum >>= 12;
  seed2 = (*seed >> 24) & 255;
  sum += mult0 * seed2 + mult1 * seed1;
  newseed2 = sum & 255;

  *seed = newseed2 << 24 | newseed1 << 12 | newseed0;
  res = 0.00390625 * (newseed2 + 0.000244140625 * (newseed1 + 0.000244140625 * newseed0));

  return res;
}

int filexists(char *filename)
{
  FILE *fp;
  int res;
  fp = fopen(filename,"rb");

  if(fp)
    {
      res = 1;
      fclose(fp);
    }
  else
    res = 0;

  return res;
}


FILE *myfopen(const char *path, const char *mode)
{
  FILE *fp = fopen(path, mode);

  if(strcmp(mode,"r") == 0 || strcmp(mode,"rb") == 0)
    {
      if(fp)
 return fp;
      else
 {
   if(processID == 0)
     printf("The file %s you want to open for reading does not exist, exiting ...\n", path);
   errorExit(-1);
   return (FILE *)((void *)0);
 }
    }
  else
    {
      if(fp)
 return fp;
      else
 {
   if(processID == 0)
     printf("The file %s RAxML wants to open for writing or appending can not be opened [mode: %s], exiting ...\n",
     path, mode);
   errorExit(-1);
   return (FILE *)((void *)0);
 }
    }


}
# 535 "<stdin>"
boolean isTip(int number, int maxTips)
{
  ((number > 0) ? (void) (0) : __assert_fail ("number > 0", "<stdin>", 537, __PRETTY_FUNCTION__));

  if(number <= maxTips)
    return 1;
  else
    return 0;
}





void getxsnode (nodeptr p, int model)
{
  ((p->xs[model] || p->next->xs[model] || p->next->next->xs[model]) ? (void) (0) : __assert_fail ("p->xs[model] || p->next->xs[model] || p->next->next->xs[model]", "<stdin>", 551, __PRETTY_FUNCTION__));
  ((p->xs[model] + p->next->xs[model] + p->next->next->xs[model] == 1) ? (void) (0) : __assert_fail ("p->xs[model] + p->next->xs[model] + p->next->next->xs[model] == 1", "<stdin>", 552, __PRETTY_FUNCTION__));

  ((p == p->next->next->next) ? (void) (0) : __assert_fail ("p == p->next->next->next", "<stdin>", 554, __PRETTY_FUNCTION__));

  p->xs[model] = 1;

  if(p->next->xs[model])
    {
      p->next->xs[model] = 0;
      return;
    }
  else
    {
      p->next->next->xs[model] = 0;
      return;
    }

  ((0) ? (void) (0) : __assert_fail ("0", "<stdin>", 569, __PRETTY_FUNCTION__));
}



void getxnode (nodeptr p)
{
  nodeptr s;

  if ((s = p->next)->x || (s = s->next)->x)
    {
      p->x = s->x;
      s->x = 0;
    }

  ((p->x) ? (void) (0) : __assert_fail ("p->x", "<stdin>", 584, __PRETTY_FUNCTION__));
}





void hookup (nodeptr p, nodeptr q, double *z, int numBranches)
{
  int i;

  p->back = q;
  q->back = p;

  for(i = 0; i < numBranches; i++)
    p->z[i] = q->z[i] = z[i];
}

void hookupDefault (nodeptr p, nodeptr q, int numBranches)
{
  int i;

  p->back = q;
  q->back = p;

  for(i = 0; i < numBranches; i++)
    p->z[i] = q->z[i] = 0.9;
}




static void getnums (rawdata *rdta)
{
  if (fscanf(INFILE, "%d %d", & rdta->numsp, & rdta->sites) != 2)
    {
      if(processID == 0)
 printf("ERROR: Problem reading number of species and sites\n");
      errorExit(-1);
    }

  if (rdta->numsp < 4)
    {
      if(processID == 0)
 printf("TOO FEW SPECIES\n");
      errorExit(-1);
    }

  if (rdta->sites < 1)
    {
      if(processID == 0)
 printf("TOO FEW SITES\n");
      errorExit(-1);
    }

  return;
}





boolean whitechar (int ch)
{
  return (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r');
}


static void uppercase (int *chptr)
{
  int ch;

  ch = *chptr;
  if ((ch >= 'a' && ch <= 'i') || (ch >= 'j' && ch <= 'r')
      || (ch >= 's' && ch <= 'z'))
    *chptr = ch + 'A' - 'a';
}




static void getyspace (rawdata *rdta)
{
  size_t size = 4 * ((size_t)(rdta->sites / 4 + 1));
  int i;
  unsigned char *y0;

  rdta->y = (unsigned char **) malloc((rdta->numsp + 1) * sizeof(unsigned char *));
  ((rdta->y) ? (void) (0) : __assert_fail ("rdta->y", "<stdin>", 672, __PRETTY_FUNCTION__));

  y0 = (unsigned char *) malloc(((size_t)(rdta->numsp + 1)) * size * sizeof(unsigned char));
  ((y0) ? (void) (0) : __assert_fail ("y0", "<stdin>", 675, __PRETTY_FUNCTION__));

  rdta->y0 = y0;

  for (i = 0; i <= rdta->numsp; i++)
    {
      rdta->y[i] = y0;
      y0 += size;
    }

  return;
}


static unsigned int KISS32(void)
{
  static unsigned int
    x = 123456789,
    y = 362436069,
    z = 21288629,
    w = 14921776,
    c = 0;

  unsigned int t;

  x += 545925293;
  y ^= (y<<13);
  y ^= (y>>17);
  y ^= (y<<5);
  t = z + w + c;
  z = w;
  c = (t>>31);
  w = t & 2147483647;

  return (x+y+w);
}

static boolean setupTree (tree *tr, analdef *adef)
{
  nodeptr p0, p, q;
  int
    i,
    j,
    k,
    tips,
    inter;

  if(!adef->readTaxaOnly)
    {
      tr->bigCutoff = 0;

      tr->patternPosition = (int*)((void *)0);
      tr->columnPosition = (int*)((void *)0);

      tr->maxCategories = (((4)>(adef->categories)) ? (4) : (adef->categories));

      tr->partitionContributions = (double *)malloc(sizeof(double) * tr->NumberOfModels);

      for(i = 0; i < tr->NumberOfModels; i++)
 tr->partitionContributions[i] = -1.0;

      tr->perPartitionLH = (double *)malloc(sizeof(double) * tr->NumberOfModels);
      tr->storedPerPartitionLH = (double *)malloc(sizeof(double) * tr->NumberOfModels);

      for(i = 0; i < tr->NumberOfModels; i++)
 {
   tr->perPartitionLH[i] = 0.0;
   tr->storedPerPartitionLH[i] = 0.0;
 }

      if(adef->grouping)
 tr->grouped = 1;
      else
 tr->grouped = 0;

      if(adef->constraint)
 tr->constrained = 1;
      else
 tr->constrained = 0;

      tr->treeID = 0;
    }

  tips = tr->mxtips;
  inter = tr->mxtips - 1;

  if(!adef->readTaxaOnly)
    {
      tr->yVector = (unsigned char **) malloc((tr->mxtips + 1) * sizeof(unsigned char *));

      tr->fracchanges = (double *)malloc(tr->NumberOfModels * sizeof(double));
      tr->likelihoods = (double *)malloc(adef->multipleRuns * sizeof(double));
    }

  tr->numberOfTrees = -1;



  tr->treeStringLength = tr->mxtips * (256 +128) + 256 + tr->mxtips * 2;

  tr->tree_string = (char*)calloc(tr->treeStringLength, sizeof(char));



  if(!adef->readTaxaOnly)
    {

      if(tr->multiGene)
 {
   for(i = 0; i < tr->NumberOfModels; i++)
     {
       tr->td[i].count = 0;
       tr->td[i].ti = (traversalInfo *)malloc(sizeof(traversalInfo) * tr->mxtips);
     }
 }
      else
 {
   tr->td[0].count = 0;
   tr->td[0].ti = (traversalInfo *)malloc(sizeof(traversalInfo) * tr->mxtips);
 }

      for(i = 0; i < tr->NumberOfModels; i++)
 tr->fracchanges[i] = -1.0;
      tr->fracchange = -1.0;

      tr->constraintVector = (int *)malloc((2 * tr->mxtips) * sizeof(int));

      tr->nameList = (char **)malloc(sizeof(char *) * (tips + 1));
    }

  if (!(p0 = (nodeptr) malloc((tips + 3*inter) * sizeof(node))))
    {
      printf("ERROR: Unable to obtain sufficient tree memory\n");
      return 0;
    }

  if (!(tr->nodep = (nodeptr *) malloc((2*tr->mxtips) * sizeof(nodeptr))))
    {
      printf("ERROR: Unable to obtain sufficient tree memory, too\n");
      return 0;
    }

  tr->nodep[0] = (node *) ((void *)0);

  for (i = 1; i <= tips; i++)
    {
      p = p0++;

      p->hash = KISS32();
      p->x = 0;
      p->number = i;
      p->next = p;
      p->back = (node *)((void *)0);
      p->bInf = (branchInfo *)((void *)0);


      for(k = 0; k < 128; k++)
 {
   p->xs[k] = 0;
   p->backs[k] = (nodeptr)((void *)0);
 }

      for(k = 0; k < (128 / 32); k++)
 p->isPresent[k] = 0;

      tr->nodep[i] = p;
    }

  for (i = tips + 1; i <= tips + inter; i++)
    {
      q = (node *) ((void *)0);
      for (j = 1; j <= 3; j++)
 {
   p = p0++;
   if(j == 1)
     p->x = 1;
   else
     p->x = 0;
   p->number = i;
   p->next = q;
   p->bInf = (branchInfo *)((void *)0);
   p->back = (node *) ((void *)0);
   p->hash = 0;

   if(j == 1)
     for(k = 0; k < 128; k++)
       {
  p->xs[k] = 1;
  p->backs[k] = (nodeptr)((void *)0);
       }
   else
     for(k = 0; k < 128; k++)
       {
  p->xs[k] = 0;
  p->backs[k] = (nodeptr)((void *)0);
       }

   for(k = 0; k < (128 / 32); k++)
     p->isPresent[k] = 0;


   q = p;
 }
      p->next->next->next = p;
      tr->nodep[i] = p;
    }

  tr->likelihood = -1.0E300;
  tr->start = (node *) ((void *)0);

  for(i = 0; i < 128; i++)
    tr->startVector[i] = (node *) ((void *)0);

  tr->ntips = 0;
  tr->nextnode = 0;

  if(!adef->readTaxaOnly)
    {
      for(i = 0; i < tr->numBranches; i++)
 tr->partitionSmoothed[i] = 0;
    }

  return 1;
}


static void checkTaxonName(char *buffer, int len)
{
  int i;

  for(i = 0; i < len - 1; i++)
    {
      boolean valid;

      switch(buffer[i])
 {
 case '\0':
 case '\t':
 case '\n':
 case '\r':
 case ' ':
 case ':':
 case ',':
 case '(':
 case ')':
 case ';':
 case '[':
 case ']':
 case '\'':
   valid = 0;
   break;
 default:
   valid = 1;
 }

      if(!valid)
 {
   printf("ERROR: Taxon Name \"%s\" is invalid at position %d, it contains illegal character %c\n", buffer, i, buffer[i]);
   printf("Illegal characters in taxon-names are: tabulators, carriage returns, spaces, \":\", \",\", \")\", \"(\", \";\", \"]\", \"[\", \"\'\" \n");
   printf("Exiting\n");
   exit(-1);
 }

    }
  ((buffer[len - 1] == '\0') ? (void) (0) : __assert_fail ("buffer[len - 1] == '\\0'", "<stdin>", 939, __PRETTY_FUNCTION__));
}

static boolean getdata(analdef *adef, rawdata *rdta, tree *tr)
{
  int
    i,
    j,
    basesread,
    basesnew,
    ch, my_i, meaning,
    len,
    meaningAA[256],
    meaningDNA[256],
    meaningBINARY[256],
    meaningGeneric32[256],
    meaningGeneric64[256];

  boolean
    allread,
    firstpass;

  char
    buffer[256 + 2];

  unsigned char
    genericChars32[32] = {'0', '1', '2', '3', '4', '5', '6', '7',
     '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
     'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
     'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V'};
  unsigned long
    total = 0,
    gaps = 0;

  for (i = 0; i < 256; i++)
    {
      meaningAA[i] = -1;
      meaningDNA[i] = -1;
      meaningBINARY[i] = -1;
      meaningGeneric32[i] = -1;
      meaningGeneric64[i] = -1;
    }



  for(i = 0; i < 32; i++)
    meaningGeneric32[genericChars32[i]] = i;
  meaningGeneric32['-'] = getUndetermined(6);
  meaningGeneric32['?'] = getUndetermined(6);



  meaningAA['A'] = 0;
  meaningAA['R'] = 1;
  meaningAA['N'] = 2;
  meaningAA['D'] = 3;
  meaningAA['C'] = 4;
  meaningAA['Q'] = 5;
  meaningAA['E'] = 6;
  meaningAA['G'] = 7;
  meaningAA['H'] = 8;
  meaningAA['I'] = 9;
  meaningAA['L'] = 10;
  meaningAA['K'] = 11;
  meaningAA['M'] = 12;
  meaningAA['F'] = 13;
  meaningAA['P'] = 14;
  meaningAA['S'] = 15;
  meaningAA['T'] = 16;
  meaningAA['W'] = 17;
  meaningAA['Y'] = 18;
  meaningAA['V'] = 19;
  meaningAA['B'] = 20;
  meaningAA['Z'] = 21;

  meaningAA['X'] =
    meaningAA['?'] =
    meaningAA['*'] =
    meaningAA['-'] =
    getUndetermined(2);



  meaningDNA['A'] = 1;
  meaningDNA['B'] = 14;
  meaningDNA['C'] = 2;
  meaningDNA['D'] = 13;
  meaningDNA['G'] = 4;
  meaningDNA['H'] = 11;
  meaningDNA['K'] = 12;
  meaningDNA['M'] = 3;
  meaningDNA['R'] = 5;
  meaningDNA['S'] = 6;
  meaningDNA['T'] = 8;
  meaningDNA['U'] = 8;
  meaningDNA['V'] = 7;
  meaningDNA['W'] = 9;
  meaningDNA['Y'] = 10;

  meaningDNA['N'] =
    meaningDNA['O'] =
    meaningDNA['X'] =
    meaningDNA['-'] =
    meaningDNA['?'] =
    getUndetermined(1);



  meaningBINARY['0'] = 1;
  meaningBINARY['1'] = 2;

  meaningBINARY['-'] =
    meaningBINARY['?'] =
    getUndetermined(0);




  basesread = basesnew = 0;

  allread = 0;
  firstpass = 1;
  ch = ' ';

  while (! allread)
    {
      for (i = 1; i <= tr->mxtips; i++)
 {
   if (firstpass)
     {
       ch = _IO_getc (INFILE);
       while(ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r')
  ch = _IO_getc (INFILE);

       my_i = 0;

       do
  {
    buffer[my_i] = ch;
    ch = _IO_getc (INFILE);
    my_i++;
    if(my_i >= 256)
      {
        if(processID == 0)
   {
     printf("Taxon Name to long at taxon %d, adapt constant nmlngth in\n", i);
     printf("axml.h, current setting %d\n", 256);
   }
        errorExit(-1);
      }
  }
       while(ch != ' ' && ch != '\n' && ch != '\t' && ch != '\r');

       while(ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r')
  ch = _IO_getc (INFILE);

       ungetc(ch, INFILE);

       buffer[my_i] = '\0';
       len = strlen(buffer) + 1;
       checkTaxonName(buffer, len);
       tr->nameList[i] = (char *)malloc(sizeof(char) * len);
       strcpy(tr->nameList[i], buffer);
     }

   j = basesread;

   while ((j < rdta->sites) && ((ch = _IO_getc (INFILE)) != (-1)) && (ch != '\n') && (ch != '\r'))
     {
       uppercase(& ch);

       ((tr->dataVector[j + 1] != -1) ? (void) (0) : __assert_fail ("tr->dataVector[j + 1] != -1", "<stdin>", 1110, __PRETTY_FUNCTION__));

       switch(tr->dataVector[j + 1])
  {
  case 0:
    meaning = meaningBINARY[ch];
    break;
  case 1:
  case 3:
  case 4:
  case 5:




    meaning = meaningDNA[ch];
    break;
  case 2:
    meaning = meaningAA[ch];
    break;
  case 6:
    meaning = meaningGeneric32[ch];
    break;
  case 7:
    meaning = meaningGeneric64[ch];
    break;
  default:
    ((0) ? (void) (0) : __assert_fail ("0", "<stdin>", 1137, __PRETTY_FUNCTION__));
  }

       if (meaning != -1)
  {
    j++;
    rdta->y[i][j] = ch;
  }
       else
  {
    if(!whitechar(ch))
      {
        printf("ERROR: Bad base (%c) at site %d of sequence %d\n",
        ch, j + 1, i);
        return 0;
      }
  }
     }

   if (ch == (-1))
     {
       printf("ERROR: End-of-file at site %d of sequence %d\n", j + 1, i);
       return 0;
     }

   if (! firstpass && (j == basesread))
     i--;
   else
     {
       if (i == 1)
  basesnew = j;
       else
  if (j != basesnew)
    {
      printf("ERROR: Sequences out of alignment\n");
      printf("%d (instead of %d) residues read in sequence %d %s\n",
      j - basesread, basesnew - basesread, i, tr->nameList[i]);
      return 0;
    }
     }
   while (ch != '\n' && ch != (-1) && ch != '\r') ch = _IO_getc (INFILE);
 }

      firstpass = 0;
      basesread = basesnew;
      allread = (basesread >= rdta->sites);
    }

  for(j = 1; j <= tr->mxtips; j++)
    for(i = 1; i <= rdta->sites; i++)
      {
 ((tr->dataVector[i] != -1) ? (void) (0) : __assert_fail ("tr->dataVector[i] != -1", "<stdin>", 1188, __PRETTY_FUNCTION__));

 switch(tr->dataVector[i])
   {
   case 0:
     meaning = meaningBINARY[rdta->y[j][i]];
     if(meaning == getUndetermined(0))
       gaps++;
     break;

   case 3:
   case 4:
   case 5:
     ((tr->secondaryStructurePairs[i - 1] != -1) ? (void) (0) : __assert_fail ("tr->secondaryStructurePairs[i - 1] != -1", "<stdin>", 1201, __PRETTY_FUNCTION__));
     ((i - 1 == tr->secondaryStructurePairs[tr->secondaryStructurePairs[i - 1]]) ? (void) (0) : __assert_fail ("i - 1 == tr->secondaryStructurePairs[tr->secondaryStructurePairs[i - 1]]", "<stdin>", 1202, __PRETTY_FUNCTION__));




   case 1:
     meaning = meaningDNA[rdta->y[j][i]];
     if(meaning == getUndetermined(1))
       gaps++;
     break;

   case 2:
     meaning = meaningAA[rdta->y[j][i]];
     if(meaning == getUndetermined(2))
       gaps++;
     break;

   case 6:
     meaning = meaningGeneric32[rdta->y[j][i]];
     if(meaning == getUndetermined(6))
       gaps++;
     break;

   case 7:
     meaning = meaningGeneric64[rdta->y[j][i]];
     if(meaning == getUndetermined(7))
       gaps++;
     break;
   default:
     ((0) ? (void) (0) : __assert_fail ("0", "<stdin>", 1231, __PRETTY_FUNCTION__));
   }

 total++;
 rdta->y[j][i] = meaning;
      }

  adef->gapyness = (double)gaps / (double)total;




  return 1;
}



static void inputweights (rawdata *rdta)
{
  int i, w, fres;
  FILE *weightFile;
  int *wv = (int *)malloc(sizeof(int) * rdta->sites);

  weightFile = myfopen(weightFileName, "rb");

  i = 0;

  while((fres = fscanf(weightFile,"%d", &w)) != (-1))
    {
      if(!fres)
 {
   if(processID == 0)
     printf("error reading weight file probably encountered a non-integer weight value\n");
   errorExit(-1);
 }
      wv[i] = w;
      i++;
    }

  if(i != rdta->sites)
    {
      if(processID == 0)
 printf("number %d of weights not equal to number %d of alignment columns\n", i, rdta->sites);
      errorExit(-1);
    }

  for(i = 1; i <= rdta->sites; i++)
    rdta->wgt[i] = wv[i - 1];

  fclose(weightFile);
  free(wv);
}



static void getinput(analdef *adef, rawdata *rdta, cruncheddata *cdta, tree *tr)
{
  int i;

  if(!adef->readTaxaOnly)
    {
      INFILE = myfopen(seq_file, "rb");

      getnums(rdta);
    }

  tr->mxtips = rdta->numsp;

  if(!adef->readTaxaOnly)
    {
      rdta->wgt = (int *) malloc((rdta->sites + 1) * sizeof(int));
      cdta->alias = (int *) malloc((rdta->sites + 1) * sizeof(int));
      cdta->aliaswgt = (int *) malloc((rdta->sites + 1) * sizeof(int));
      cdta->rateCategory = (int *) malloc((rdta->sites + 1) * sizeof(int));
      tr->model = (int *) calloc((rdta->sites + 1), sizeof(int));
      tr->initialDataVector = (int *) malloc((rdta->sites + 1) * sizeof(int));
      tr->extendedDataVector = (int *) malloc((rdta->sites + 1) * sizeof(int));
      cdta->patrat = (double *) malloc((rdta->sites + 1) * sizeof(double));
      cdta->patratStored = (double *) malloc((rdta->sites + 1) * sizeof(double));
      tr->wr = (double *) malloc((rdta->sites + 1) * sizeof(double));
      tr->wr2 = (double *) malloc((rdta->sites + 1) * sizeof(double));


      if(!adef->useWeightFile)
 {
   for (i = 1; i <= rdta->sites; i++)
     rdta->wgt[i] = 1;
 }
      else
 {
   ((!adef->useSecondaryStructure) ? (void) (0) : __assert_fail ("!adef->useSecondaryStructure", "<stdin>", 1321, __PRETTY_FUNCTION__));
   inputweights(rdta);
 }
    }

  tr->multiBranch = 0;
  tr->numBranches = 1;

  if(!adef->readTaxaOnly)
    {
      if(adef->useMultipleModel)
 {
   int ref;

   parsePartitions(adef, rdta, tr);

   for(i = 1; i <= rdta->sites; i++)
     {
       ref = tr->model[i];
       tr->initialDataVector[i] = tr->initialPartitionData[ref].dataType;
     }
 }
      else
 {
   int
     dataType = -1;

   tr->initialPartitionData = (pInfo*)malloc(sizeof(pInfo));
   tr->initialPartitionData[0].partitionName = (char*)malloc(128 * sizeof(char));
   strcpy(tr->initialPartitionData[0].partitionName, "No Name Provided");

   tr->initialPartitionData[0].protModels = adef->proteinMatrix;
   if(adef->protEmpiricalFreqs)
     tr->initialPartitionData[0].usePredefinedProtFreqs = 0;
   else
     tr->initialPartitionData[0].usePredefinedProtFreqs = 1;



   tr->NumberOfModels = 1;

   if(adef->model == 5 || adef->model == 6)
     dataType = 2;
   if(adef->model == 1 || adef->model == 2)
     dataType = 1;
   if(adef->model == 3 || adef->model == 4)
     dataType = 0;
   if(adef->model == 7 || adef->model == 8)
     dataType = 6;
   if(adef->model == 9 || adef->model == 10)
     dataType = 7;



   ((dataType == 0 || dataType == 1 || dataType == 2 || dataType == 6 || dataType == 7) ? (void) (0) : __assert_fail ("dataType == 0 || dataType == 1 || dataType == 2 || dataType == 6 || dataType == 7",
 "<stdin>"
# 1375 "<stdin>"
   ,
 1376
# 1375 "<stdin>"
   , __PRETTY_FUNCTION__))
                                                     ;

   tr->initialPartitionData[0].dataType = dataType;

   if(dataType == 2 && adef->userProteinModel)
     {
       tr->initialPartitionData[0].protModels = 18;
       tr->initialPartitionData[0].usePredefinedProtFreqs = 1;
       strcpy(tr->initialPartitionData[0].proteinSubstitutionFileName, proteinModelFileName);
     }

   for(i = 0; i <= rdta->sites; i++)
     {
       tr->initialDataVector[i] = dataType;
       tr->model[i] = 0;
     }
 }

      if(adef->useSecondaryStructure)
 {
   memcpy(tr->extendedDataVector, tr->initialDataVector, (rdta->sites + 1) * sizeof(int));

   tr->extendedPartitionData =(pInfo*)malloc(sizeof(pInfo) * tr->NumberOfModels);

   for(i = 0; i < tr->NumberOfModels; i++)
     {
       tr->extendedPartitionData[i].partitionName = (char*)malloc((strlen(tr->initialPartitionData[i].partitionName) + 1) * sizeof(char));
       strcpy(tr->extendedPartitionData[i].partitionName, tr->initialPartitionData[i].partitionName);
       strcpy(tr->extendedPartitionData[i].proteinSubstitutionFileName, tr->initialPartitionData[i].proteinSubstitutionFileName);
       tr->extendedPartitionData[i].dataType = tr->initialPartitionData[i].dataType;
       tr->extendedPartitionData[i].protModels = tr->initialPartitionData[i].protModels;
       tr->extendedPartitionData[i].usePredefinedProtFreqs = tr->initialPartitionData[i].usePredefinedProtFreqs;
     }

   parseSecondaryStructure(tr, adef, rdta->sites);

   tr->dataVector = tr->extendedDataVector;
   tr->partitionData = tr->extendedPartitionData;
 }
      else
 {
   tr->dataVector = tr->initialDataVector;
   tr->partitionData = tr->initialPartitionData;
 }



      for(i = 0; i < tr->NumberOfModels; i++)
 if(tr->partitionData[i].dataType == 2 && tr->partitionData[i].protModels == 18)
   parseProteinModel(tr->partitionData[i].externalAAMatrix, tr->partitionData[i].proteinSubstitutionFileName);



      tr->executeModel = (boolean *)malloc(sizeof(boolean) * tr->NumberOfModels);

      for(i = 0; i < tr->NumberOfModels; i++)
 tr->executeModel[i] = 1;

      getyspace(rdta);
    }

  setupTree(tr, adef);


  if(!adef->readTaxaOnly)
    {
      if(!getdata(adef, rdta, tr))
 {
   printf("Problem reading alignment file \n");
   errorExit(1);
 }
      tr->nameHash = initStringHashTable(10 * tr->mxtips);
      for(i = 1; i <= tr->mxtips; i++)
 addword(tr->nameList[i], tr->nameHash, i);

      fclose(INFILE);
    }
}



static unsigned char buildStates(int secModel, unsigned char v1, unsigned char v2)
{
  unsigned char new = 0;

  switch(secModel)
    {
    case 3:
      new = v1;
      new = new << 4;
      new = new | v2;
      break;
    case 4:
      {
 int
   meaningDNA[256],
   i;

 const unsigned char
   allowedStates[6][2] = {{'A','T'}, {'C', 'G'}, {'G', 'C'}, {'G','T'}, {'T', 'A'}, {'T', 'G'}};

 const unsigned char
   finalBinaryStates[6] = {1, 2, 4, 8, 16, 32};

 unsigned char
   intermediateBinaryStates[6];

 int length = 6;

 for(i = 0; i < 256; i++)
   meaningDNA[i] = -1;

 meaningDNA['A'] = 1;
 meaningDNA['B'] = 14;
 meaningDNA['C'] = 2;
 meaningDNA['D'] = 13;
 meaningDNA['G'] = 4;
 meaningDNA['H'] = 11;
 meaningDNA['K'] = 12;
 meaningDNA['M'] = 3;
 meaningDNA['N'] = 15;
 meaningDNA['O'] = 15;
 meaningDNA['R'] = 5;
 meaningDNA['S'] = 6;
 meaningDNA['T'] = 8;
 meaningDNA['U'] = 8;
 meaningDNA['V'] = 7;
 meaningDNA['W'] = 9;
 meaningDNA['X'] = 15;
 meaningDNA['Y'] = 10;
 meaningDNA['-'] = 15;
 meaningDNA['?'] = 15;

 for(i = 0; i < length; i++)
   {
     unsigned char n1 = meaningDNA[allowedStates[i][0]];
     unsigned char n2 = meaningDNA[allowedStates[i][1]];

     new = n1;
     new = new << 4;
     new = new | n2;

     intermediateBinaryStates[i] = new;
   }

 new = v1;
 new = new << 4;
 new = new | v2;

 for(i = 0; i < length; i++)
   {
     if(new == intermediateBinaryStates[i])
       break;
   }
 if(i < length)
   new = finalBinaryStates[i];
 else
   {
     new = 0;
     for(i = 0; i < length; i++)
       {
  if(v1 & meaningDNA[allowedStates[i][0]])
    {

      new |= finalBinaryStates[i];
    }
  if(v2 & meaningDNA[allowedStates[i][1]])
    {

      new |= finalBinaryStates[i];
    }
       }
   }
      }
      break;
    case 5:
      {
 int
   meaningDNA[256],
   i;

 const unsigned char
   allowedStates[6][2] = {{'A','T'}, {'C', 'G'}, {'G', 'C'}, {'G','T'}, {'T', 'A'}, {'T', 'G'}};

 const unsigned char
   finalBinaryStates[7] = {1, 2, 4, 8, 16, 32, 64};

 unsigned char
   intermediateBinaryStates[7];

 for(i = 0; i < 256; i++)
   meaningDNA[i] = -1;

 meaningDNA['A'] = 1;
 meaningDNA['B'] = 14;
 meaningDNA['C'] = 2;
 meaningDNA['D'] = 13;
 meaningDNA['G'] = 4;
 meaningDNA['H'] = 11;
 meaningDNA['K'] = 12;
 meaningDNA['M'] = 3;
 meaningDNA['N'] = 15;
 meaningDNA['O'] = 15;
 meaningDNA['R'] = 5;
 meaningDNA['S'] = 6;
 meaningDNA['T'] = 8;
 meaningDNA['U'] = 8;
 meaningDNA['V'] = 7;
 meaningDNA['W'] = 9;
 meaningDNA['X'] = 15;
 meaningDNA['Y'] = 10;
 meaningDNA['-'] = 15;
 meaningDNA['?'] = 15;


 for(i = 0; i < 6; i++)
   {
     unsigned char n1 = meaningDNA[allowedStates[i][0]];
     unsigned char n2 = meaningDNA[allowedStates[i][1]];

     new = n1;
     new = new << 4;
     new = new | n2;

     intermediateBinaryStates[i] = new;
   }

 new = v1;
 new = new << 4;
 new = new | v2;

 for(i = 0; i < 6; i++)
   {

     if(new == intermediateBinaryStates[i])
       break;
   }
 if(i < 6)
   new = finalBinaryStates[i];
 else
   {


     for(i = 0; i < 6; i++)
       if((v1 & meaningDNA[allowedStates[i][0]]) && (v2 & meaningDNA[allowedStates[i][1]]))
  break;
     if(i < 6)
       {


  new = 0;
  for(i = 0; i < 6; i++)
    {
      if((v1 & meaningDNA[allowedStates[i][0]]) && (v2 & meaningDNA[allowedStates[i][1]]))
        {

   new |= finalBinaryStates[i];
        }
      else
        new |= finalBinaryStates[6];
    }
       }
     else
       new = finalBinaryStates[6];
   }
      }
      break;
    default:
      ((0) ? (void) (0) : __assert_fail ("0", "<stdin>", 1644, __PRETTY_FUNCTION__));
    }

  return new;

}



static void adaptRdataToSecondary(tree *tr, rawdata *rdta)
{
  int *alias = (int*)calloc(rdta->sites, sizeof(int));
  int i, j, realPosition;

  for(i = 0; i < rdta->sites; i++)
    alias[i] = -1;

  for(i = 0, realPosition = 0; i < rdta->sites; i++)
    {
      int partner = tr->secondaryStructurePairs[i];
      if(partner != -1)
 {
   ((tr->dataVector[i+1] == 3 || tr->dataVector[i+1] == 4 || tr->dataVector[i+1] == 5) ? (void) (0) : __assert_fail ("tr->dataVector[i+1] == 3 || tr->dataVector[i+1] == 4 || tr->dataVector[i+1] == 5", "<stdin>", 1666, __PRETTY_FUNCTION__));

   if(i < partner)
     {
       for(j = 1; j <= rdta->numsp; j++)
  {
    unsigned char v1 = rdta->y[j][i+1];
    unsigned char v2 = rdta->y[j][partner+1];

    ((i+1 < partner+1) ? (void) (0) : __assert_fail ("i+1 < partner+1", "<stdin>", 1675, __PRETTY_FUNCTION__));

    rdta->y[j][i+1] = buildStates(tr->dataVector[i+1], v1, v2);
  }
       alias[realPosition] = i;
       realPosition++;
     }
 }
      else
 {
   alias[realPosition] = i;
   realPosition++;
 }
    }

  ((rdta->sites - realPosition == tr->numberOfSecondaryColumns / 2) ? (void) (0) : __assert_fail ("rdta->sites - realPosition == tr->numberOfSecondaryColumns / 2", "<stdin>", 1690, __PRETTY_FUNCTION__));

  rdta->sites = realPosition;

  for(i = 0; i < rdta->sites; i++)
    {
      ((alias[i] != -1) ? (void) (0) : __assert_fail ("alias[i] != -1", "<stdin>", 1696, __PRETTY_FUNCTION__));
      tr->model[i+1] = tr->model[alias[i]+1];
      tr->dataVector[i+1] = tr->dataVector[alias[i]+1];
      rdta->wgt[i+1] = rdta->wgt[alias[i]+1];

      for(j = 1; j <= rdta->numsp; j++)
 rdta->y[j][i+1] = rdta->y[j][alias[i]+1];
    }

  free(alias);
}

static void sitesort(rawdata *rdta, cruncheddata *cdta, tree *tr, analdef *adef)
{
  int gap, i, j, jj, jg, k, n, nsp;
  int
    *index,
    *category = (int*)((void *)0);

  boolean flip, tied;
  unsigned char **data;

  if(adef->useSecondaryStructure)
    {
      ((tr->NumberOfModels > 1 && adef->useMultipleModel) ? (void) (0) : __assert_fail ("tr->NumberOfModels > 1 && adef->useMultipleModel", "<stdin>", 1720, __PRETTY_FUNCTION__));

      adaptRdataToSecondary(tr, rdta);
    }

  if(adef->useMultipleModel)
    category = tr->model;


  index = cdta->alias;
  data = rdta->y;
  n = rdta->sites;
  nsp = rdta->numsp;
  index[0] = -1;


  if(adef->compressPatterns)
    {
      for (gap = n / 2; gap > 0; gap /= 2)
 {
   for (i = gap + 1; i <= n; i++)
     {
       j = i - gap;

       do
  {
    jj = index[j];
    jg = index[j+gap];
    if(adef->useMultipleModel)
      {
        ((category[jj] != -1 && category[jg] != -1) ? (void) (0) : __assert_fail ("category[jj] != -1 && category[jg] != -1",
 "<stdin>"
# 1750 "<stdin>"
        ,
 1751
# 1750 "<stdin>"
        , __PRETTY_FUNCTION__))
                           ;

        flip = (category[jj] > category[jg]);
        tied = (category[jj] == category[jg]);

      }
    else
      {
        flip = 0;
        tied = 1;
      }

    for (k = 1; (k <= nsp) && tied; k++)
      {
        flip = (data[k][jj] > data[k][jg]);
        tied = (data[k][jj] == data[k][jg]);
      }

    if (flip)
      {
        index[j] = jg;
        index[j+gap] = jj;
        j -= gap;
      }
  }
       while (flip && (j > 0));
     }
 }
    }
}


static void sitecombcrunch (rawdata *rdta, cruncheddata *cdta, tree *tr, analdef *adef)
{
  int i, sitei, j, sitej, k;
  boolean tied;
  int
    *aliasModel = (int*)((void *)0),
    *aliasSuperModel = (int*)((void *)0);

  if(adef->useMultipleModel)
    {
      aliasSuperModel = (int*)malloc(sizeof(int) * (rdta->sites + 1));
      aliasModel = (int*)malloc(sizeof(int) * (rdta->sites + 1));
    }

  i = 0;
  cdta->alias[0] = cdta->alias[1];
  cdta->aliaswgt[0] = 0;

  if(adef->mode == 6)
    {
      int i;

      tr->patternPosition = (int*)malloc(sizeof(int) * rdta->sites);
      tr->columnPosition = (int*)malloc(sizeof(int) * rdta->sites);

      for(i = 0; i < rdta->sites; i++)
 {
   tr->patternPosition[i] = -1;
   tr->columnPosition[i] = -1;
 }
    }



  i = 0;
  for (j = 1; j <= rdta->sites; j++)
    {
      sitei = cdta->alias[i];
      sitej = cdta->alias[j];
      if(!adef->compressPatterns)
 tied = 0;
      else
 {
   if(adef->useMultipleModel)
     {
       tied = (tr->model[sitei] == tr->model[sitej]);
       if(tied)
  ((tr->dataVector[sitei] == tr->dataVector[sitej]) ? (void) (0) : __assert_fail ("tr->dataVector[sitei] == tr->dataVector[sitej]", "<stdin>", 1830, __PRETTY_FUNCTION__));
     }
   else
     tied = 1;
 }

      for (k = 1; tied && (k <= rdta->numsp); k++)
 tied = (rdta->y[k][sitei] == rdta->y[k][sitej]);

      if (tied)
 {
   if(adef->mode == 6)
     {
       tr->patternPosition[j - 1] = i;
       tr->columnPosition[j - 1] = sitej;

     }


   cdta->aliaswgt[i] += rdta->wgt[sitej];
   if(adef->useMultipleModel)
     {
       aliasModel[i] = tr->model[sitej];
       aliasSuperModel[i] = tr->dataVector[sitej];
     }
 }
      else
 {
   if (cdta->aliaswgt[i] > 0) i++;

   if(adef->mode == 6)
     {
       tr->patternPosition[j - 1] = i;
       tr->columnPosition[j - 1] = sitej;

     }

   cdta->aliaswgt[i] = rdta->wgt[sitej];
   cdta->alias[i] = sitej;
   if(adef->useMultipleModel)
     {
       aliasModel[i] = tr->model[sitej];
       aliasSuperModel[i] = tr->dataVector[sitej];
     }
 }
    }

  cdta->endsite = i;
  if (cdta->aliaswgt[i] > 0) cdta->endsite++;

  if(adef->mode == 6)
    {
      for(i = 0; i < rdta->sites; i++)
 {
   int p = tr->patternPosition[i];
   int c = tr->columnPosition[i];

   ((p >= 0 && p < cdta->endsite) ? (void) (0) : __assert_fail ("p >= 0 && p < cdta->endsite", "<stdin>", 1887, __PRETTY_FUNCTION__));
   ((c >= 1 && c <= rdta->sites) ? (void) (0) : __assert_fail ("c >= 1 && c <= rdta->sites", "<stdin>", 1888, __PRETTY_FUNCTION__));
 }
    }


  if(adef->useMultipleModel)
    {
      for(i = 0; i <= rdta->sites; i++)
 {
   tr->model[i] = aliasModel[i];
   tr->dataVector[i] = aliasSuperModel[i];
 }
    }

  if(adef->useMultipleModel)
    {
      free(aliasModel);
      free(aliasSuperModel);
    }
}


static boolean makeweights (analdef *adef, rawdata *rdta, cruncheddata *cdta, tree *tr)
{
  int i;

  for (i = 1; i <= rdta->sites; i++)
    cdta->alias[i] = i;

  sitesort(rdta, cdta, tr, adef);
  sitecombcrunch(rdta, cdta, tr, adef);

  return 1;
}




static boolean makevalues(rawdata *rdta, cruncheddata *cdta, tree *tr, analdef *adef)
{
  int i, j, model, fullSites = 0, modelCounter;

  unsigned char
    *y = (unsigned char *)malloc(((size_t)rdta->numsp) * ((size_t)cdta->endsite) * sizeof(unsigned char)),
    *yBUF = (unsigned char *)malloc( ((size_t)rdta->numsp) * ((size_t)cdta->endsite) * sizeof(unsigned char));

  for (i = 1; i <= rdta->numsp; i++)
    for (j = 0; j < cdta->endsite; j++)
      y[(((size_t)(i - 1)) * ((size_t)cdta->endsite)) + j] = rdta->y[i][cdta->alias[j]];

  free(rdta->y0);
  free(rdta->y);

  rdta->y0 = y;
  memcpy(yBUF, y, ((size_t)rdta->numsp) * ((size_t)cdta->endsite) * sizeof(unsigned char));
  rdta->yBUF = yBUF;

  if(!adef->useMultipleModel)
    tr->NumberOfModels = 1;

  if(adef->useMultipleModel)
    {
      tr->partitionData[0].lower = 0;

      model = tr->model[0];
      modelCounter = 0;

      i = 1;

      while(i < cdta->endsite)
 {
   if(tr->model[i] != model)
     {
       tr->partitionData[modelCounter].upper = i;
       tr->partitionData[modelCounter + 1].lower = i;

       model = tr->model[i];
       modelCounter++;
     }
   i++;
 }


      tr->partitionData[tr->NumberOfModels - 1].upper = cdta->endsite;

      for(i = 0; i < tr->NumberOfModels; i++)
 tr->partitionData[i].width = tr->partitionData[i].upper - tr->partitionData[i].lower;

      model = tr->model[0];
      modelCounter = 0;
      tr->model[0] = modelCounter;
      i = 1;

      while(i < cdta->endsite)
 {
   if(tr->model[i] != model)
     {
       model = tr->model[i];
       modelCounter++;
       tr->model[i] = modelCounter;
     }
   else
     tr->model[i] = modelCounter;
   i++;
 }
    }
  else
    {
      tr->partitionData[0].lower = 0;
      tr->partitionData[0].upper = cdta->endsite;
      tr->partitionData[0].width = tr->partitionData[0].upper - tr->partitionData[0].lower;
    }

  tr->rdta = rdta;
  tr->cdta = cdta;

  tr->invariant = (int *)malloc(cdta->endsite * sizeof(int));
  tr->originalDataVector = (int *)malloc(cdta->endsite * sizeof(int));
  tr->originalModel = (int *)malloc(cdta->endsite * sizeof(int));
  tr->originalWeights = (int *)malloc(cdta->endsite * sizeof(int));

  memcpy(tr->originalModel, tr->model, cdta->endsite * sizeof(int));
  memcpy(tr->originalDataVector, tr->dataVector, cdta->endsite * sizeof(int));
  memcpy(tr->originalWeights, tr->cdta->aliaswgt, cdta->endsite * sizeof(int));

  tr->originalCrunchedLength = tr->cdta->endsite;
  for(i = 0; i < tr->cdta->endsite; i++)
    fullSites += tr->cdta->aliaswgt[i];

  tr->fullSites = fullSites;

  for(i = 0; i < rdta->numsp; i++)
    tr->yVector[i + 1] = &(rdta->y0[((size_t)tr->originalCrunchedLength) * ((size_t)i)]);

  return 1;
}


static void makeMissingData(tree *tr)
{
  if(tr->multiGene)
    {
      int
 model,
 i,
 j;

      double
 totalWidth = 0.0,
 missingWidth = 0.0;

      unsigned char
 undetermined;





      ((tr->NumberOfModels > 1 && tr->numBranches > 1) ? (void) (0) : __assert_fail ("tr->NumberOfModels > 1 && tr->numBranches > 1", "<stdin>", 2046, __PRETTY_FUNCTION__));

      for(model = 0; model < tr->NumberOfModels; model++)
 {
   int
     countMissing = 0,
     width = tr->partitionData[model].upper - tr->partitionData[model].lower;

   tr->mxtipsVector[model] = 0;

   undetermined = getUndetermined(tr->partitionData[model].dataType);

   for(i = 1; i <= tr->mxtips; i++)
     {
       unsigned char *tip = tr->partitionData[model].yVector[i];


       ((width > 0) ? (void) (0) : __assert_fail ("width > 0", "<stdin>", 2063, __PRETTY_FUNCTION__));

       for(j = 0; j < width; j++)
  if(tip[j] != undetermined)
    break;

       if(j == width)
  countMissing++;
       else
  {
    tr->nodep[i]->isPresent[model / 32] |= mask32[model % 32];
    if(!tr->startVector[model])
      {
        tr->startVector[model] = tr->nodep[i];

      }
  }
     }

   tr->mxtipsVector[model] = tr->mxtips - countMissing;
   ((tr->mxtipsVector[model] + countMissing == tr->mxtips) ? (void) (0) : __assert_fail ("tr->mxtipsVector[model] + countMissing == tr->mxtips", "<stdin>", 2083, __PRETTY_FUNCTION__));

   printBothOpen("Partition %d has %d missing taxa and %d present taxa\n\n", model, countMissing, tr->mxtipsVector[model]);
   ((countMissing < tr->mxtips) ? (void) (0) : __assert_fail ("countMissing < tr->mxtips", "<stdin>", 2086, __PRETTY_FUNCTION__));

   totalWidth += (double)(tr->mxtips) * (double)(width);
   missingWidth += (double)(countMissing) * (double)(width);
 }

      printBothOpen("Percentage of gene-sampling induced gappyness in this alignment: %2.2f%s\n", 100 * (missingWidth / totalWidth), "%");

    }
}






static int sequenceSimilarity(unsigned char *tipJ, unsigned char *tipK, int n)
{
  int i;

  for(i = 0; i < n; i++)
    if(*tipJ++ != *tipK++)
      return 0;

  return 1;
}

static void checkSequences(tree *tr, rawdata *rdta, analdef *adef)
{
  int n = tr->mxtips + 1;
  int i, j;
  int *omissionList = (int *)calloc(n, sizeof(int));
  int *undeterminedList = (int *)calloc((rdta->sites + 1), sizeof(int));
  int *modelList = (int *)malloc((rdta->sites + 1)* sizeof(int));
  int count = 0;
  int countNameDuplicates = 0;
  int countUndeterminedColumns = 0;
  int countOnlyGaps = 0;
  int modelCounter = 1;
  unsigned char *tipI, *tipJ;

  for(i = 1; i < n; i++)
    {
      for(j = i + 1; j < n; j++)
 if(strcmp(tr->nameList[i], tr->nameList[j]) == 0)
   {
     countNameDuplicates++;
     if(processID == 0)
       printBothOpen("Sequence names of taxon %d and %d are identical, they are both called %s\n", i, j, tr->nameList[i]);
   }
    }

  if(countNameDuplicates > 0)
    {
      if(processID == 0)
 printBothOpen("ERROR: Found %d taxa that had equal names in the alignment, exiting...\n", countNameDuplicates);
      errorExit(-1);
    }

  for(i = 1; i < n; i++)
    {
      j = 1;

      while(j <= rdta->sites)
 {
   if(rdta->y[i][j] != getUndetermined(tr->dataVector[j]))
     break;

   j++;
 }

      if(j == (rdta->sites + 1))
 {
   if(processID == 0)
     printBothOpen("ERROR: Sequence %s consists entirely of undetermined values which will be treated as missing data\n",
     tr->nameList[i]);

   countOnlyGaps++;
 }
    }

  if(countOnlyGaps > 0)
    {
      if(processID == 0)
 printBothOpen("ERROR: Found %d sequences that consist entirely of undetermined values, exiting...\n", countOnlyGaps);

      errorExit(-1);
    }

  for(i = 0; i <= rdta->sites; i++)
    modelList[i] = -1;

  for(i = 1; i <= rdta->sites; i++)
    {
      j = 1;

      while(j < n)
 {
   if(rdta->y[j][i] != getUndetermined(tr->dataVector[i]))
     break;


   j++;
 }

      if(j == n)
 {
   undeterminedList[i] = 1;

   if(processID == 0)
     printBothOpen("IMPORTANT WARNING: Alignment column %d contains only undetermined values which will be treated as missing data\n", i);

   countUndeterminedColumns++;
 }
      else
 {
   if(adef->useMultipleModel)
     {
       modelList[modelCounter] = tr->model[i];
       modelCounter++;
     }
 }
    }


  for(i = 1; i < n; i++)
    {
      if(omissionList[i] == 0)
 {
   tipI = &(rdta->y[i][1]);

   for(j = i + 1; j < n; j++)
     {
       if(omissionList[j] == 0)
  {
    tipJ = &(rdta->y[j][1]);
    if(sequenceSimilarity(tipI, tipJ, rdta->sites))
      {
        if(processID == 0)
   printBothOpen("\n\nIMPORTANT WARNING: Sequences %s and %s are exactly identical\n", tr->nameList[i], tr->nameList[j]);

        omissionList[j] = 1;
        count++;
      }
  }
     }
 }
    }

  if(count > 0 || countUndeterminedColumns > 0)
    {
      char noDupFile[2048];
      char noDupModels[2048];
      char noDupSecondary[2048];

      if(count > 0 &&processID == 0)
 {
   printBothOpen("\nIMPORTANT WARNING\n");

   printBothOpen("Found %d %s that %s exactly identical to other sequences in the alignment.\n", count, (count == 1)?"sequence":"sequences", (count == 1)?"is":"are");

   printBothOpen("Normally they should be excluded from the analysis.\n\n");
 }

      if(countUndeterminedColumns > 0 && processID == 0)
 {
   printBothOpen("\nIMPORTANT WARNING\n");

   printBothOpen("Found %d %s that %s only undetermined values which will be treated as missing data.\n",
   countUndeterminedColumns, (countUndeterminedColumns == 1)?"column":"columns", (countUndeterminedColumns == 1)?"contains":"contain");

   printBothOpen("Normally these columns should be excluded from the analysis.\n\n");
 }

      strcpy(noDupFile, seq_file);
      strcat(noDupFile, ".reduced");

      strcpy(noDupModels, modelFileName);
      strcat(noDupModels, ".reduced");

      strcpy(noDupSecondary, secondaryStructureFileName);
      strcat(noDupSecondary, ".reduced");

      if(processID == 0)
 {
   if(adef->useSecondaryStructure)
     {
       if(countUndeterminedColumns && !filexists(noDupSecondary))
  {
    FILE *newFile = myfopen(noDupSecondary, "wb");
    int count;

    printBothOpen("\nJust in case you might need it, a secondary structure file with \n");
    printBothOpen("structure assignments for undetermined columns removed is printed to file %s\n",noDupSecondary);

    for(i = 1, count = 0; i <= rdta->sites; i++)
      {
        if(undeterminedList[i] == 0)
   fprintf(newFile, "%c", tr->secondaryStructureInput[i - 1]);
        else
   count++;
      }

    ((count == countUndeterminedColumns) ? (void) (0) : __assert_fail ("count == countUndeterminedColumns", "<stdin>", 2289, __PRETTY_FUNCTION__));

    fprintf(newFile,"\n");

    fclose(newFile);
  }
       else
  {
    if(countUndeterminedColumns)
      {
        printBothOpen("\nA secondary structure file with model assignments for undetermined\n");
        printBothOpen("columns removed has already been printed to  file %s\n",noDupSecondary);
      }
  }
     }


   if(adef->useMultipleModel && !filexists(noDupModels) && countUndeterminedColumns)
     {
       FILE *newFile = myfopen(noDupModels, "wb");

       printBothOpen("\nJust in case you might need it, a mixed model file with \n");
       printBothOpen("model assignments for undetermined columns removed is printed to file %s\n",noDupModels);

       for(i = 0; i < tr->NumberOfModels; i++)
  {
    boolean modelStillExists = 0;

    for(j = 1; (j <= rdta->sites) && (!modelStillExists); j++)
      {
        if(modelList[j] == i)
   modelStillExists = 1;
      }

    if(modelStillExists)
      {
        int k = 1;
        int lower, upper;
        int parts = 0;


        switch(tr->partitionData[i].dataType)
   {
   case 2:
     {
       char
         AAmodel[1024];

       if(tr->partitionData[i].protModels != 18)
         {
    strcpy(AAmodel, protModels[tr->partitionData[i].protModels]);
    if(tr->partitionData[i].usePredefinedProtFreqs == 0)
      strcat(AAmodel, "F");

    fprintf(newFile, "%s, ", AAmodel);
         }
       else
         fprintf(newFile, "[%s], ", tr->partitionData[i].proteinSubstitutionFileName);
     }
     break;
   case 1:
     fprintf(newFile, "DNA, ");
     break;
   case 0:
     fprintf(newFile, "BIN, ");
     break;
   case 6:
     fprintf(newFile, "MULTI, ");
     break;
   case 7:
     fprintf(newFile, "CODON, ");
     break;
   default:
     ((0) ? (void) (0) : __assert_fail ("0", "<stdin>", 2362, __PRETTY_FUNCTION__));
   }

        fprintf(newFile, "%s = ", tr->partitionData[i].partitionName);

        while(k <= rdta->sites)
   {
     if(modelList[k] == i)
       {
         lower = k;
         while((modelList[k + 1] == i) && (k <= rdta->sites))
    k++;
         upper = k;

         if(lower == upper)
    {
      if(parts == 0)
        fprintf(newFile, "%d", lower);
      else
        fprintf(newFile, ",%d", lower);
    }
         else
    {
      if(parts == 0)
        fprintf(newFile, "%d-%d", lower, upper);
      else
        fprintf(newFile, ",%d-%d", lower, upper);
    }
         parts++;
       }
     k++;
   }
        fprintf(newFile, "\n");
      }
  }
       fclose(newFile);
     }
   else
     {
       if(adef->useMultipleModel)
  {
    printBothOpen("\nA mixed model file with model assignments for undetermined\n");
    printBothOpen("columns removed has already been printed to  file %s\n",noDupModels);
  }
     }


   if(!filexists(noDupFile))
     {
       FILE *newFile;

       printBothOpen("Just in case you might need it, an alignment file with \n");
       if(count && !countUndeterminedColumns)
  printBothOpen("sequence duplicates removed is printed to file %s\n", noDupFile);
       if(!count && countUndeterminedColumns)
  printBothOpen("undetermined columns removed is printed to file %s\n", noDupFile);
       if(count && countUndeterminedColumns)
  printBothOpen("sequence duplicates and undetermined columns removed is printed to file %s\n", noDupFile);

       newFile = myfopen(noDupFile, "wb");

       fprintf(newFile, "%d %d\n", tr->mxtips - count, rdta->sites - countUndeterminedColumns);

       for(i = 1; i < n; i++)
  {
    if(!omissionList[i])
      {
        fprintf(newFile, "%s ", tr->nameList[i]);
        tipI = &(rdta->y[i][1]);

        for(j = 0; j < rdta->sites; j++)
   {
     if(undeterminedList[j + 1] == 0)
       fprintf(newFile, "%c", getInverseMeaning(tr->dataVector[j + 1], tipI[j]));
   }

        fprintf(newFile, "\n");
      }
  }

       fclose(newFile);
     }
   else
     {
       if(count && !countUndeterminedColumns)
  printBothOpen("An alignment file with sequence duplicates removed has already\n");
       if(!count && countUndeterminedColumns)
  printBothOpen("An alignment file with undetermined columns removed has already\n");
       if(count && countUndeterminedColumns)
  printBothOpen("An alignment file with undetermined columns and sequence duplicates removed has already\n");

       printBothOpen("been printed to file %s\n", noDupFile);
     }
 }
    }

  free(undeterminedList);
  free(omissionList);
  free(modelList);
}







static void generateBS(tree *tr, analdef *adef)
{
  int i, j, k, w;
  int count;
  char outName[1024], buf[16];
  FILE *of;

  ((adef->boot != 0) ? (void) (0) : __assert_fail ("adef->boot != 0", "<stdin>", 2476, __PRETTY_FUNCTION__));

  for(i = 0; i < adef->multipleRuns; i++)
    {
      computeNextReplicate(tr, &adef->boot, (int*)((void *)0), (int*)((void *)0), 0, 0);

      count = 0;
      for(j = 0; j < tr->cdta->endsite; j++)
 count += tr->cdta->aliaswgt[j];

      ((count == tr->rdta->sites) ? (void) (0) : __assert_fail ("count == tr->rdta->sites", "<stdin>", 2486, __PRETTY_FUNCTION__));

      strcpy(outName, workdir);
      strcat(outName, seq_file);
      strcat(outName, ".BS");
      sprintf(buf, "%d", i);
      strcat(outName, buf);
      printf("Printing replicate %d to %s\n", i, outName);

      of = myfopen(outName, "wb");

      fprintf(of, "%d %d\n", tr->mxtips, count);

      for(j = 1; j <= tr->mxtips; j++)
 {
   unsigned char *tip = tr->yVector[tr->nodep[j]->number];
   fprintf(of, "%s ", tr->nameList[j]);

   for(k = 0; k < tr->cdta->endsite; k++)
     {
       for(w = 0; w < tr->cdta->aliaswgt[k]; w++)
  fprintf(of, "%c", getInverseMeaning(tr->dataVector[k], tip[k]));
     }

   fprintf(of, "\n");
 }
      fclose(of);
    }
}





static void splitMultiGene(tree *tr, rawdata *rdta)
{
  int i, l;
  int n = rdta->sites + 1;
  int *modelFilter = (int *)malloc(sizeof(int) * n);
  int length, k;
  unsigned char *tip;
  FILE *outf;
  char outFileName[2048];
  char buf[16];

  for(i = 0; i < tr->NumberOfModels; i++)
    {
      strcpy(outFileName, seq_file);
      sprintf(buf, "%d", i);
      strcat(outFileName, ".GENE.");
      strcat(outFileName, buf);
      outf = myfopen(outFileName, "wb");
      length = 0;
      for(k = 1; k < n; k++)
 {
   if(tr->model[k] == i)
     {
       modelFilter[k] = 1;
       length++;
     }
   else
     modelFilter[k] = -1;
 }

      fprintf(outf, "%d %d\n", rdta->numsp, length);

      for(l = 1; l <= rdta->numsp; l++)
 {
   fprintf(outf, "%s ", tr->nameList[l]);

   tip = &(rdta->y[l][0]);

   for(k = 1; k < n; k++)
     {
       if(modelFilter[k] == 1)
  fprintf(outf, "%c", getInverseMeaning(tr->dataVector[k], tip[k]));
     }
   fprintf(outf, "\n");

 }

      fclose(outf);

      printf("Wrote individual gene/partition alignment to file %s\n", outFileName);
    }

  free(modelFilter);
  printf("Wrote all %d individual gene/partition alignments\n", tr->NumberOfModels);
  printf("Exiting normally\n");
}


static int countTaxaInTopology(void)
{
  FILE *f = myfopen(tree_file, "rb");

  int
    c,
    taxaCount = 0;

  while((c = fgetc(f)) != (-1))
    {
      if(c == '(' || c == ',')
 {
   c = fgetc(f);
   if(c == '(' || c == ',')
     ungetc(c, f);
   else
     {
       do
  {
    c = fgetc(f);
  }
       while(c != ':' && c != ')' && c != ',');

       taxaCount++;

       ungetc(c, f);
     }
 }
    }

  printBothOpen("Found a total of %d taxa in tree file %s\n", taxaCount, tree_file);

  fclose(f);

  return taxaCount;
}







static void allocPartitions(tree *tr)
{
  int
    i,
    maxCategories = tr->maxCategories;




  for(i = 0; i < tr->NumberOfModels; i++)
    {
      const partitionLengths *pl = getPartitionLengths(&(tr->partitionData[i]));

      size_t
 k,
 width = tr->partitionData[i].width;

      tr->partitionData[i].perSiteAAModel = (int *)malloc(sizeof(int) * width);
      for(k = 0; k < width; k++)
 tr->partitionData[i].perSiteAAModel[k] = 4;


      tr->partitionData[i].wr = (double *)malloc(sizeof(double) * width);
      tr->partitionData[i].wr2 = (double *)malloc(sizeof(double) * width);



      if(tr->useFastScaling)
 {
   tr->partitionData[i].globalScaler = (unsigned int *)calloc(2 * tr->mxtips, sizeof(unsigned int));
 }

      tr->partitionData[i].left = (double *)malloc_aligned(pl->leftLength * maxCategories * sizeof(double), 16);
      tr->partitionData[i].right = (double *)malloc_aligned(pl->rightLength * maxCategories * sizeof(double), 16);
      tr->partitionData[i].EIGN = (double*)malloc(pl->eignLength * sizeof(double));
      tr->partitionData[i].EV = (double*)malloc_aligned(pl->evLength * sizeof(double), 16);
      tr->partitionData[i].EI = (double*)malloc(pl->eiLength * sizeof(double));
      tr->partitionData[i].substRates = (double *)malloc(pl->substRatesLength * sizeof(double));
      tr->partitionData[i].frequencies = (double*)malloc(pl->frequenciesLength * sizeof(double));
      tr->partitionData[i].tipVector = (double *)malloc_aligned(pl->tipVectorLength * sizeof(double), 16);
      tr->partitionData[i].symmetryVector = (int *)malloc(pl->symmetryVectorLength * sizeof(int));
      tr->partitionData[i].frequencyGrouping = (int *)malloc(pl->frequencyGroupingLength * sizeof(int));
      tr->partitionData[i].perSiteRates = (double *)malloc(sizeof(double) * tr->maxCategories);


      tr->partitionData[i].nonGTR = 0;



      tr->partitionData[i].gammaRates = (double*)malloc(sizeof(double) * 4);
      tr->partitionData[i].yVector = (unsigned char **)malloc(sizeof(unsigned char*) * (tr->mxtips + 1));


      tr->partitionData[i].xVector = (double **)malloc(sizeof(double*) * tr->innerNodes);
      tr->partitionData[i].xSpaceVector = (size_t *)calloc(tr->innerNodes, sizeof(size_t));

      tr->partitionData[i].expVector = (int **)malloc(sizeof(int*) * tr->innerNodes);
      tr->partitionData[i].expSpaceVector = (size_t *)calloc(tr->innerNodes, sizeof(size_t));

      tr->partitionData[i].mxtips = tr->mxtips;





      {
 int j;

 for(j = 1; j <= tr->mxtips; j++)
   tr->partitionData[i].yVector[j] = &(tr->yVector[j][tr->partitionData[i].lower]);
      }


    }
}







static void allocNodex (tree *tr)
{
  size_t
    i,
    model,
    offset,
    memoryRequirements = 0;

  allocPartitions(tr);

  for(model = 0; model < (size_t)tr->NumberOfModels; model++)
    {
      size_t
 width = tr->partitionData[model].upper - tr->partitionData[model].lower;

      int
 undetermined,
 j;

      memoryRequirements += (size_t)(tr->discreteRateCategories) * (size_t)(tr->partitionData[model].states) * width;

      tr->partitionData[model].gapVectorLength = ((int)width / 32) + 1;

      tr->partitionData[model].gapVector = (unsigned int*)calloc(tr->partitionData[model].gapVectorLength * 2 * tr->mxtips, sizeof(unsigned int));


      tr->partitionData[model].initialGapVectorSize = tr->partitionData[model].gapVectorLength * 2 * tr->mxtips * sizeof(int);

      tr->partitionData[model].gapColumn = (double *)malloc_aligned(((size_t)tr->innerNodes) *
            ((size_t)(tr->discreteRateCategories)) *
            ((size_t)(tr->partitionData[model].states)) *
            sizeof(double), 16);

      undetermined = getUndetermined(tr->partitionData[model].dataType);

      for(j = 1; j <= tr->mxtips; j++)
 for(i = 0; i < width; i++)
   if(tr->partitionData[model].yVector[j][i] == undetermined)
     tr->partitionData[model].gapVector[tr->partitionData[model].gapVectorLength * j + i / 32] |= mask32[i % 32];
    }

  tr->perSiteLL = (double *)malloc((size_t)tr->cdta->endsite * sizeof(double));
  ((tr->perSiteLL != ((void *)0)) ? (void) (0) : __assert_fail ("tr->perSiteLL != ((void *)0)", "<stdin>", 2745, __PRETTY_FUNCTION__));

  tr->sumBuffer = (double *)malloc_aligned(memoryRequirements * sizeof(double), 16);
  ((tr->sumBuffer != ((void *)0)) ? (void) (0) : __assert_fail ("tr->sumBuffer != ((void *)0)", "<stdin>", 2748, __PRETTY_FUNCTION__));

  offset = 0;



  for(model = 0; model < (size_t)tr->NumberOfModels; model++)
    {
      size_t
 lower = tr->partitionData[model].lower,
 width = tr->partitionData[model].upper - lower;




      tr->partitionData[model].sumBuffer = &tr->sumBuffer[offset];


      tr->partitionData[model].perSiteLL = &tr->perSiteLL[lower];


      tr->partitionData[model].wgt = &tr->cdta->aliaswgt[lower];
      tr->partitionData[model].invariant = &tr->invariant[lower];
      tr->partitionData[model].rateCategory = &tr->cdta->rateCategory[lower];

      offset += (size_t)(tr->discreteRateCategories) * (size_t)(tr->partitionData[model].states) * width;
    }

  for(i = 0; i < tr->innerNodes; i++)
    {
      for(model = 0; model < (size_t)tr->NumberOfModels; model++)
 {
   tr->partitionData[model].expVector[i] = (int*)((void *)0);
   tr->partitionData[model].xVector[i] = (double*)((void *)0);
 }
    }
}




static void initAdef(analdef *adef)
{
  adef->useSecondaryStructure = 0;
  adef->bootstrapBranchLengths = 0;
  adef->model = 1;
  adef->max_rearrange = 21;
  adef->stepwidth = 5;
  adef->initial = adef->bestTrav = 10;
  adef->initialSet = 0;
  adef->restart = 0;
  adef->mode = 1;
  adef->categories = 25;
  adef->boot = 0;
  adef->rapidBoot = 0;
  adef->useWeightFile = 0;
  adef->checkpoints = 0;
  adef->startingTreeOnly = 0;
  adef->multipleRuns = 1;
  adef->useMultipleModel = 0;
  adef->likelihoodEpsilon = 0.1;
  adef->constraint = 0;
  adef->grouping = 0;
  adef->randomStartingTree = 0;
  adef->parsimonySeed = 0;
  adef->proteinMatrix = 2;
  adef->protEmpiricalFreqs = 0;
  adef->outgroup = 0;
  adef->useInvariant = 0;
  adef->permuteTreeoptimize = 0;
  adef->useInvariant = 0;
  adef->allInOne = 0;
  adef->likelihoodTest = 0;
  adef->perGeneBranchLengths = 0;
  adef->generateBS = 0;
  adef->bootStopping = 0;
  adef->gapyness = 0.0;
  adef->similarityFilterMode = 0;
  adef->useExcludeFile = 0;
  adef->userProteinModel = 0;
  adef->computeELW = 0;
  adef->computeDistance = 0;
  adef->compressPatterns = 1;
  adef->readTaxaOnly = 0;
  adef->meshSearch = 0;
  adef->useBinaryModelFile = 0;
  adef->leaveDropMode = 0;
  adef->slidingWindowSize = 100;
}




static int modelExists(char *model, analdef *adef)
{
  int i;
  char thisModel[1024];



   if(strcmp(model, "BINGAMMAI\0") == 0)
    {
      adef->model = 4;
      adef->useInvariant = 1;
      return 1;
    }

  if(strcmp(model, "BINGAMMA\0") == 0)
    {
      adef->model = 4;
      adef->useInvariant = 0;
      return 1;
    }

  if(strcmp(model, "BINCAT\0") == 0)
    {
      adef->model = 3;
      adef->useInvariant = 0;
      return 1;
    }

  if(strcmp(model, "BINCATI\0") == 0)
    {
      adef->model = 3;
      adef->useInvariant = 1;
      return 1;
    }



  if(strcmp(model, "MULTIGAMMAI\0") == 0)
    {
      adef->model = 8;
      adef->useInvariant = 1;
      return 1;
    }

  if(strcmp(model, "MULTIGAMMA\0") == 0)
    {
      adef->model = 8;
      adef->useInvariant = 0;
      return 1;
    }

  if(strcmp(model, "MULTICAT\0") == 0)
    {
      adef->model = 7;
      adef->useInvariant = 0;
      return 1;
    }

  if(strcmp(model, "MULTICATI\0") == 0)
    {
      adef->model = 7;
      adef->useInvariant = 1;
      return 1;
    }



  if(strcmp(model, "CODONGAMMAI\0") == 0)
    {
      adef->model = 10;
      adef->useInvariant = 1;
      return 1;
    }

  if(strcmp(model, "CODONGAMMA\0") == 0)
    {
      adef->model = 10;
      adef->useInvariant = 0;
      return 1;
    }

  if(strcmp(model, "CODONCAT\0") == 0)
    {
      adef->model = 9;
      adef->useInvariant = 0;
      return 1;
    }

  if(strcmp(model, "CODONCATI\0") == 0)
    {
      adef->model = 9;
      adef->useInvariant = 1;
      return 1;
    }




  if(strcmp(model, "GTRGAMMAI\0") == 0)
    {
      adef->model = 2;
      adef->useInvariant = 1;
      return 1;
    }

  if(strcmp(model, "GTRGAMMA\0") == 0)
    {
      adef->model = 2;
      adef->useInvariant = 0;
      return 1;
    }



  if(strcmp(model, "GTRCAT\0") == 0)
    {
      adef->model = 1;
      adef->useInvariant = 0;
      return 1;
    }



  if(strcmp(model, "GTRCATI\0") == 0)
    {
      adef->model = 1;
      adef->useInvariant = 1;
      return 1;
    }
# 2978 "<stdin>"
  if(strcmp(model, "PROTCATGTR\0") == 0)
    {
      adef->model = 5;
      adef->proteinMatrix = 20;
      adef->useInvariant = 0;
      adef->protEmpiricalFreqs = 1;
      return 1;
    }

  if(strcmp(model, "PROTCATIGTR\0") == 0)
    {
      adef->model = 5;
      adef->proteinMatrix = 20;
      adef->useInvariant = 1;
      return 1;
    }

  if(strcmp(model, "PROTGAMMAGTR\0") == 0)
    {
      adef->model = 6;
      adef->proteinMatrix = 20;
      adef->useInvariant = 0;
      adef->protEmpiricalFreqs = 1;
      return 1;
    }

  if(strcmp(model, "PROTGAMMAIGTR\0") == 0)
    {
      adef->model = 6;
      adef->proteinMatrix = 20;
      adef->useInvariant = 1;
      adef->protEmpiricalFreqs = 1;
      return 1;
    }



  if(strcmp(model, "PROTCATGTR_UNLINKED\0") == 0)
    {
      printf("Advisory: GTR_UNLINKED only has an effect if specified in the partition file\n");

      adef->model = 5;
      adef->proteinMatrix = 19;
      adef->useInvariant = 0;
      adef->protEmpiricalFreqs = 1;
      return 1;
    }

  if(strcmp(model, "PROTCATIGTR_UNLINKED\0") == 0)
    {
      printf("Advisory: GTR_UNLINKED only has an effect if specified in the partition file\n");

      adef->model = 5;
      adef->proteinMatrix = 19;
      adef->useInvariant = 1;
      adef->protEmpiricalFreqs = 1;
      return 1;
    }

  if(strcmp(model, "PROTGAMMAGTR_UNLINKED\0") == 0)
    {
      printf("Advisory: GTR_UNLINKED only has an effect if specified in the partition file\n");

      adef->model = 6;
      adef->proteinMatrix = 19;
      adef->useInvariant = 0;
      adef->protEmpiricalFreqs = 1;
      return 1;
    }

  if(strcmp(model, "PROTGAMMAIGTR_UNLINKED\0") == 0)
    {
      printf("Advisory: GTR_UNLINKED only has an effect if specified in the partition file\n");

      adef->model = 6;
      adef->proteinMatrix = 19;
      adef->useInvariant = 1;
      return 1;
    }



  for(i = 0; i < 21 - 2; i++)
    {


      strcpy(thisModel, "PROTCAT");
      strcat(thisModel, protModels[i]);

      if(strcmp(model, thisModel) == 0)
 {
   adef->model = 5;
   adef->proteinMatrix = i;
   return 1;
 }



      strcpy(thisModel, "PROTCAT");
      strcat(thisModel, protModels[i]);
      strcat(thisModel, "F");

      if(strcmp(model, thisModel) == 0)
 {
   adef->model = 5;
   adef->proteinMatrix = i;
   adef->protEmpiricalFreqs = 1;
   return 1;
 }




      strcpy(thisModel, "PROTCATI");
      strcat(thisModel, protModels[i]);

      if(strcmp(model, thisModel) == 0)
 {
   adef->model = 5;
   adef->proteinMatrix = i;
   adef->useInvariant = 1;
   return 1;
 }



      strcpy(thisModel, "PROTCATI");
      strcat(thisModel, protModels[i]);
      strcat(thisModel, "F");

      if(strcmp(model, thisModel) == 0)
 {
   adef->model = 5;
   adef->proteinMatrix = i;
   adef->protEmpiricalFreqs = 1;
   adef->useInvariant = 1;
   return 1;
 }




      strcpy(thisModel, "PROTGAMMA");
      strcat(thisModel, protModels[i]);

      if(strcmp(model, thisModel) == 0)
 {
   adef->model = 6;
   adef->proteinMatrix = i;
   adef->useInvariant = 0;
   return 1;
 }






      strcpy(thisModel, "PROTGAMMAI");
      strcat(thisModel, protModels[i]);

      if(strcmp(model, thisModel) == 0)
 {
   adef->model = 6;
   adef->proteinMatrix = i;
   adef->useInvariant = 1;
   return 1;
 }




      strcpy(thisModel, "PROTGAMMA");
      strcat(thisModel, protModels[i]);
      strcat(thisModel, "F");

      if(strcmp(model, thisModel) == 0)
 {
   adef->model = 6;
   adef->proteinMatrix = i;
   adef->protEmpiricalFreqs = 1;
   adef->useInvariant = 0;
   return 1;
 }




      strcpy(thisModel, "PROTGAMMAI");
      strcat(thisModel, protModels[i]);
      strcat(thisModel, "F");

      if(strcmp(model, thisModel) == 0)
 {
   adef->model = 6;
   adef->proteinMatrix = i;
   adef->protEmpiricalFreqs = 1;
   adef->useInvariant = 1;
   return 1;
 }

    }





  return 0;
}



static int mygetopt(int argc, char **argv, char *opts, int *optind, char **optarg)
{
  static int sp = 1;
  register int c;
  register char *cp;

  if(sp == 1)
    {
      if(*optind >= argc || argv[*optind][0] != '-' || argv[*optind][1] == '\0')
 return -1;
    }
  else
    {
      if(strcmp(argv[*optind], "--") == 0)
 {
   *optind = *optind + 1;
   return -1;
 }
    }

  c = argv[*optind][sp];
  if(c == ':' || (cp=strchr(opts, c)) == 0)
    {
      printf(": illegal option -- %c \n", c);
      if(argv[*optind][++sp] == '\0')
 {
   *optind = *optind + 1;
   sp = 1;
 }
      return('?');
    }
  if(*++cp == ':')
    {
      if(argv[*optind][sp+1] != '\0')
 {
   *optarg = &argv[*optind][sp+1];
   *optind = *optind + 1;
 }
      else
 {
   *optind = *optind + 1;
   if(*optind >= argc)
     {
       printf(": option requires an argument -- %c\n", c);
       sp = 1;
       return('?');
     }
   else
     {
       *optarg = argv[*optind];
       *optind = *optind + 1;
     }
 }
      sp = 1;
    }
  else
    {
      if(argv[*optind][++sp] == '\0')
 {
   sp = 1;
   *optind = *optind + 1;
 }
      *optarg = 0;
    }
  return(c);
  }

static void checkOutgroups(tree *tr, analdef *adef)
{
  if(adef->outgroup)
    {
      boolean found;
      int i, j;

      for(j = 0; j < tr->numberOfOutgroups; j++)
 {
   found = 0;
   for(i = 1; (i <= tr->mxtips) && !found; i++)
     {
       if(strcmp(tr->nameList[i], tr->outgroups[j]) == 0)
  {
    tr->outgroupNums[j] = i;
    found = 1;
  }
     }
   if(!found)
     {
       printf("Error, the outgroup name \"%s\" you specified can not be found in the alignment, exiting ....\n", tr->outgroups[j]);
       errorExit(-1);
     }
 }
    }

}

static void parseOutgroups(char *outgr, tree *tr)
{
  int count = 1, i, k;
  char name[256];

  i = 0;
  while(outgr[i] != '\0')
    {
      if(outgr[i] == ',')
 count++;
      i++;
    }

  tr->numberOfOutgroups = count;

  tr->outgroups = (char **)malloc(sizeof(char *) * count);

  for(i = 0; i < tr->numberOfOutgroups; i++)
    tr->outgroups[i] = (char *)malloc(sizeof(char) * 256);

  tr->outgroupNums = (int *)malloc(sizeof(int) * count);

  i = 0;
  k = 0;
  count = 0;
  while(outgr[i] != '\0')
    {
      if(outgr[i] == ',')
 {
   name[k] = '\0';
   strcpy(tr->outgroups[count], name);
   count++;
   k = 0;
 }
      else
 {
   name[k] = outgr[i];
   k++;
 }
      i++;
    }

  name[k] = '\0';
  strcpy(tr->outgroups[count], name);






}





static void printVersionInfo(void)
{
  printf("\n\nThis is %s version %s released by Alexandros Stamatakis in %s.\n\n", "RAxML", "7.3.0", "June 2011");
  printf("With greatly appreciated code contributions by:\n");
  printf("Andre Aberer (HITS)\n");
  printf("Simon Berger (HITS)\n");
  printf("Nick Pattengale (Sandia)\n");
  printf("Wayne Pfeiffer (SDSC)\n");
  printf("Akifumi S. Tanabe (Univ. Tsukuba)\n\n");
}

static void printMinusFUsage(void)
{
  printf("\n");
  printf("              \"-f a\": rapid Bootstrap analysis and search for best-scoring ML tree in one program run\n");

  printf("              \"-f A\": compute marginal ancestral states on a ROOTED reference tree provided with \"t\"\n");

  printf("              \"-f b\": draw bipartition information on a tree provided with \"-t\" based on multiple trees\n");
  printf("                      (e.g., from a bootstrap) in a file specifed by \"-z\"\n");

  printf("              \"-f c\": check if the alignment can be properly read by RAxML\n");

  printf("              \"-f d\": new rapid hill-climbing \n");
  printf("                      DEFAULT: ON\n");

  printf("              \"-f e\": optimize model+branch lengths for given input tree under GAMMA/GAMMAI only\n");

  printf("              \"-f E\": execute very fast experimental tree search, at present only for testing\n");

  printf("              \"-f F\": execute fast experimental tree search, at present only for testing\n");

  printf("              \"-f g\": compute per site log Likelihoods for one ore more trees passed via\n");
  printf("                      \"-z\" and write them to a file that can be read by CONSEL\n");

  printf("              \"-f h\": compute log likelihood test (SH-test) between best tree passed via \"-t\"\n");
  printf("                      and a bunch of other trees passed via \"-z\" \n");

  printf("              \"-f i\": EXPERIMENTAL do not use for real tree inferences: conducts a single cycle of fast lazy SPR moves\n");
  printf("                      on a given input tree, to be used in combination with -C and -M \n");

  printf("              \"-f I\": EXPERIMENTAL do not use for real tree inferences: conducts a single cycle of thorough lazy SPR moves\n");
  printf("                      on a given input tree, to be used in combination with -C and -M \n");

  printf("              \"-f j\": generate a bunch of bootstrapped alignment files from an original alignemnt file.\n");
  printf("                      You need to specify a seed with \"-b\" and the number of replicates with \"-#\" \n");

  printf("              \"-f J\": Compute SH-like support values on a given tree passed via \"-t\".\n");

  printf("              \"-f m\": compare bipartitions between two bunches of trees passed via \"-t\" and \"-z\" \n");
  printf("                      respectively. This will return the Pearson correlation between all bipartitions found\n");
  printf("                      in the two tree files. A file called RAxML_bipartitionFrequencies.outpuFileName\n");
  printf("                      will be printed that contains the pair-wise bipartition frequencies of the two sets\n");

  printf("              \"-f n\": compute the log likelihood score of all trees contained in a tree file provided by\n");
  printf("                      \"-z\" under GAMMA or GAMMA+P-Invar\n");

  printf("              \"-f o\": old and slower rapid hill-climbing without heuristic cutoff\n");

  printf("              \"-f p\": perform pure stepwise MP addition of new sequences to an incomplete starting tree and exit\n");

  printf("              \"-f r\": compute pairwise Robinson-Foulds (RF) distances between all pairs of trees in a tree file passed via \"-z\" \n");
  printf("                      if the trees have node labales represented as integer support values the program will also compute two flavors of\n");
  printf("                      the weighted Robinson-Foulds (WRF) distance\n");

  printf("              \"-f s\": split up a multi-gene partitioned alignment into the respective subalignments \n");

  printf("              \"-f S\": compute site-specific placement bias using a leave one out test inspired by the evolutionary placement algorithm\n");

  printf("              \"-f t\": do randomized tree searches on one fixed starting tree\n");

  printf("              \"-f u\": execute morphological weight calibration using maximum likelihood, this will return a weight vector.\n");
  printf("                      you need to provide a morphological alignment and a reference tree via \"-t\" \n");

  printf("              \"-f v\": classify a bunch of environmental sequences into a reference tree using thorough read insertions\n");
  printf("                      you will need to start RAxML with a non-comprehensive reference tree and an alignment containing all sequences (reference + query)\n");

  printf("              \"-f w\": compute ELW test on a bunch of trees passed via \"-z\" \n");

  printf("              \"-f x\": compute pair-wise ML distances, ML model parameters will be estimated on an MP \n");
  printf("                      starting tree or a user-defined tree passed via \"-t\", only allowed for GAMMA-based\n");
  printf("                      models of rate heterogeneity\n");

  printf("              \"-f y\": classify a bunch of environmental sequences into a reference tree using parsimony\n");
  printf("                      you will need to start RAxML with a non-comprehensive reference tree and an alignment containing all sequences (reference + query)\n");

  printf("\n");
  printf("              DEFAULT for \"-f\": new rapid hill climbing\n");

  printf("\n");
}


static void printREADME(void)
{
  printVersionInfo();
  printf("\n");
  printf("Please also consult the RAxML-manual\n");
  printf("\nTo report bugs send an email to stamatak@cs.tum.edu\n");
  printf("Please send me all input files, the exact invocation, details of the HW and operating system,\n");
  printf("as well as all error messages printed to screen.\n\n\n");

  printf("raxmlHPC[-SSE3|-PTHREADS|-PTHREADS-SSE3|-HYBRID|-HYBRID-SSE3]\n");
  printf("      -s sequenceFileName -n outputFileName -m substitutionModel\n");
  printf("      [-a weightFileName] [-A secondaryStructureSubstModel]\n");
  printf("      [-b bootstrapRandomNumberSeed] [-B wcCriterionThreshold]\n");
  printf("      [-c numberOfCategories] [-C] [-d] [-D]\n");
  printf("      [-e likelihoodEpsilon] [-E excludeFileName]\n");
  printf("      [-f a|A|b|c|d|e|E|F|g|h|i|I|j|J|m|n|o|p|r|s|S|t|u|v|w|x|y] [-F]\n");
  printf("      [-g groupingFileName] [-G placementThreshold] [-h]\n");
  printf("      [-i initialRearrangementSetting] [-I autoFC|autoMR|autoMRE|autoMRE_IGN]\n");
  printf("      [-j] [-J MR|MR_DROP|MRE|STRICT|STRICT_DROP] [-k] [-K] [-M]\n");
  printf("      [-o outGroupName1[,outGroupName2[,...]]]\n");
  printf("      [-p parsimonyRandomSeed] [-P proteinModel]\n");
  printf("      [-q multipleModelFileName] [-r binaryConstraintTree]\n");
  printf("      [-R binaryModelParamFile] [-S secondaryStructureFile] [-t userStartingTree]\n");
  printf("      [-T numberOfThreads] [-U] [-v] [-w outputDirectory] [-W slidingWindowSize]\n");
  printf("      [-x rapidBootstrapRandomNumberSeed] [-X] [-y]\n");
  printf("      [-z multipleTreesFile] [-#|-N numberOfRuns|autoFC|autoMR|autoMRE|autoMRE_IGN]\n");
  printf("\n");
  printf("      -a      Specify a column weight file name to assign individual weights to each column of \n");
  printf("              the alignment. Those weights must be integers separated by any type and number \n");
  printf("              of whitespaces whithin a separate file, see file \"example_weights\" for an example.\n");
  printf("\n");
  printf("      -A      Specify one of the secondary structure substitution models implemented in RAxML.\n");
  printf("              The same nomenclature as in the PHASE manual is used, available models: \n");
  printf("              S6A, S6B, S6C, S6D, S6E, S7A, S7B, S7C, S7D, S7E, S7F, S16, S16A, S16B\n");
  printf("\n");
  printf("              DEFAULT: 16-state GTR model (S16)\n");
  printf("\n");
  printf("      -b      Specify an integer number (random seed) and turn on bootstrapping\n");
  printf("\n");
  printf("              DEFAULT: OFF\n");
  printf("\n");
  printf("      -B      specify a floating point number between 0.0 and 1.0 that will be used as cutoff threshold \n");
  printf("              for the MR-based bootstopping criteria. The recommended setting is 0.03.\n");
  printf("\n");
  printf("              DEFAULT: 0.03 (recommended empirically determined setting)\n");
  printf("\n");
  printf("      -c      Specify number of distinct rate catgories for RAxML when modelOfEvolution\n");
  printf("              is set to GTRCAT or GTRMIX\n");
  printf("              Individual per-site rates are categorized into numberOfCategories rate \n");
  printf("              categories to accelerate computations. \n");
  printf("\n");
  printf("              DEFAULT: 25\n");
  printf("\n");
  printf("      -C      Conduct model parameter optimization on gappy, partitioned multi-gene alignments with per-partition\n");
  printf("              branch length estimates (-M enabled) using the fast method with pointer meshes described in:\n");
  printf("              Stamatakis and Ott: \"Efficient computation of the phylogenetic likelihood function on multi-gene alignments and multi-core processors\"\n");
  printf("              WARNING: We can not conduct useful tree searches using this method yet! Does not work with Pthreads version.\n");
  printf("\n");
  printf("      -d      start ML optimization from random starting tree \n");
  printf("\n");
  printf("              DEFAULT: OFF\n");
  printf("\n");
  printf("      -D      ML search convergence criterion. This will break off ML searches if the relative \n");
  printf("              Robinson-Foulds distance between the trees obtained from two consecutive lazy SPR cycles\n");
  printf("              is smaller or equal to 1%s. Usage recommended for very large datasets in terms of taxa.\n", "%");
  printf("              On trees with more than 500 taxa this will yield execution time improvements of approximately 50%s\n", "%");
  printf("              While yielding only slightly worse trees.\n");
  printf("\n");
  printf("              DEFAULT: OFF\n");
  printf("\n");
  printf("      -e      set model optimization precision in log likelihood units for final\n");
  printf("              optimization of tree topology under MIX/MIXI or GAMMA/GAMMAI\n");
  printf("\n");
  printf("              DEFAULT: 0.1   for models not using proportion of invariant sites estimate\n");
  printf("                       0.001 for models using proportion of invariant sites estimate\n");
  printf("\n");
  printf("      -E      specify an exclude file name, that contains a specification of alignment positions you wish to exclude.\n");
  printf("              Format is similar to Nexus, the file shall contain entries like \"100-200 300-400\", to exclude a\n");
  printf("              single column write, e.g., \"100-100\", if you use a mixed model, an appropriatly adapted model file\n");
  printf("              will be written.\n");
  printf("\n");
  printf("      -f      select algorithm:\n");

  printMinusFUsage();

  printf("\n");
  printf("      -F      enable ML tree searches under CAT model for very large trees without switching to \n");
  printf("              GAMMA in the end (saves memory).\n");
  printf("              This option can also be used with the GAMMA models in order to avoid the thorough optimization \n");
  printf("              of the best-scoring ML tree in the end.\n");
  printf("\n");
  printf("              DEFAULT: OFF\n");
  printf("\n");
  printf("      -g      specify the file name of a multifurcating constraint tree\n");
  printf("              this tree does not need to be comprehensive, i.e. must not contain all taxa\n");
  printf("\n");
  printf("      -G      enable the ML-based evolutionary placement algorithm heuristics\n");
  printf("              by specifiyng a threshold value (fraction of insertion branches to be evaluated\n");
  printf("              using slow insertions under ML).\n");
  printf("\n");
  printf("      -h      Display this help message.\n");
  printf("\n");
  printf("      -i      Initial rearrangement setting for the subsequent application of topological \n");
  printf("              changes phase\n");
  printf("\n");
  printf("      -I      a posteriori bootstopping analysis. Use:\n");
  printf("             \"-I autoFC\" for the frequency-based criterion\n");
  printf("             \"-I autoMR\" for the majority-rule consensus tree criterion\n");
  printf("             \"-I autoMRE\" for the extended majority-rule consensus tree criterion\n");
  printf("             \"-I autoMRE_IGN\" for metrics similar to MRE, but include bipartitions under the threshold whether they are compatible\n");
  printf("                              or not. This emulates MRE but is faster to compute.\n");
  printf("              You also need to pass a tree file containg several bootstrap replicates via \"-z\" \n");
  printf("\n");
  printf("      -j      Specifies that intermediate tree files shall be written to file during the standard ML and BS tree searches.\n");
  printf("\n");
  printf("              DEFAULT: OFF\n");
  printf("\n");
  printf("      -J      Compute majority rule consensus tree with \"-J MR\" or extended majority rule consensus tree with \"-J MRE\"\n");
  printf("              or strict consensus tree with \"-J STRICT\".\n");
  printf("              Options \"-J STRICT_DROP\" and \"-J MR_DROP\" will execute an algorithm that identifies dropsets which contain\n");
  printf("              rogue taxa as proposed by Pattengale et al. in the paper \"Uncovering hidden phylogenetic consensus\".\n");
  printf("              You will also need to provide a tree file containing several UNROOTED trees via \"-z\"\n");
  printf("\n");
  printf("      -k      Specifies that bootstrapped trees should be printed with branch lengths.\n");
  printf("              The bootstraps will run a bit longer, because model parameters will be optimized\n");
  printf("              at the end of each run under GAMMA or GAMMA+P-Invar respectively.\n");
  printf("\n");
  printf("              DEFAULT: OFF\n");
  printf("\n");
  printf("      -K      Specify one of the multi-state substitution models (max 32 states) implemented in RAxML.\n");
  printf("              Available models are: ORDERED, MK, GTR\n");
  printf("\n");
  printf("              DEFAULT: GTR model \n");
  printf("\n");
  printf("      -m      Model of Binary (Morphological), Nucleotide, Multi-State, or Amino Acid Substitution: \n");
  printf("\n");
  printf("              BINARY:\n\n");
  printf("                \"-m BINCAT\"         : Optimization of site-specific\n");
  printf("                                      evolutionary rates which are categorized into numberOfCategories distinct \n");
  printf("                                      rate categories for greater computational efficiency. Final tree might be evaluated\n");
  printf("                                      automatically under BINGAMMA, depending on the tree search option\n");
  printf("                \"-m BINCATI\"        : Optimization of site-specific\n");
  printf("                                      evolutionary rates which are categorized into numberOfCategories distinct \n");
  printf("                                      rate categories for greater computational efficiency. Final tree might be evaluated\n");
  printf("                                      automatically under BINGAMMAI, depending on the tree search option \n");
  printf("                \"-m BINGAMMA\"       : GAMMA model of rate \n");
  printf("                                      heterogeneity (alpha parameter will be estimated)\n");
  printf("                \"-m BINGAMMAI\"      : Same as BINGAMMA, but with estimate of proportion of invariable sites\n");
  printf("\n");
  printf("              NUCLEOTIDES:\n\n");
  printf("                \"-m GTRCAT\"         : GTR + Optimization of substitution rates + Optimization of site-specific\n");
  printf("                                      evolutionary rates which are categorized into numberOfCategories distinct \n");
  printf("                                      rate categories for greater computational efficiency.  Final tree might be evaluated\n");
  printf("                                      under GTRGAMMA, depending on the tree search option\n");
  printf("                \"-m GTRCATI\"        : GTR + Optimization of substitution rates + Optimization of site-specific\n");
  printf("                                      evolutionary rates which are categorized into numberOfCategories distinct \n");
  printf("                                      rate categories for greater computational efficiency.  Final tree might be evaluated\n");
  printf("                                      under GTRGAMMAI, depending on the tree search option\n");
  printf("                \"-m GTRGAMMA\"       : GTR + Optimization of substitution rates + GAMMA model of rate \n");
  printf("                                      heterogeneity (alpha parameter will be estimated)\n");
  printf("                \"-m GTRGAMMAI\"      : Same as GTRGAMMA, but with estimate of proportion of invariable sites \n");
  printf("\n");
  printf("              MULTI-STATE:\n\n");
  printf("                \"-m MULTICAT\"         : Optimization of site-specific\n");
  printf("                                      evolutionary rates which are categorized into numberOfCategories distinct \n");
  printf("                                      rate categories for greater computational efficiency. Final tree might be evaluated\n");
  printf("                                      automatically under MULTIGAMMA, depending on the tree search option\n");
  printf("                \"-m MULTICATI\"        : Optimization of site-specific\n");
  printf("                                      evolutionary rates which are categorized into numberOfCategories distinct \n");
  printf("                                      rate categories for greater computational efficiency. Final tree might be evaluated\n");
  printf("                                      automatically under MULTIGAMMAI, depending on the tree search option \n");
  printf("                \"-m MULTIGAMMA\"       : GAMMA model of rate \n");
  printf("                                      heterogeneity (alpha parameter will be estimated)\n");
  printf("                \"-m MULTIGAMMAI\"      : Same as MULTIGAMMA, but with estimate of proportion of invariable sites\n");
  printf("\n");
  printf("                You can use up to 32 distinct character states to encode multi-state regions, they must be used in the following order:\n");
  printf("                0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V\n");
  printf("                i.e., if you have 6 distinct character states you would use 0, 1, 2, 3, 4, 5 to encode these.\n");
  printf("                The substitution model for the multi-state regions can be selected via the \"-K\" option\n");
  printf("\n");
  printf("              AMINO ACIDS:\n\n");
  printf("                \"-m PROTCATmatrixName[F]\"         : specified AA matrix + Optimization of substitution rates + Optimization of site-specific\n");
  printf("                                                    evolutionary rates which are categorized into numberOfCategories distinct \n");
  printf("                                                    rate categories for greater computational efficiency.   Final tree might be evaluated\n");
  printf("                                                    automatically under PROTGAMMAmatrixName[f], depending on the tree search option\n");
  printf("                \"-m PROTCATImatrixName[F]\"        : specified AA matrix + Optimization of substitution rates + Optimization of site-specific\n");
  printf("                                                    evolutionary rates which are categorized into numberOfCategories distinct \n");
  printf("                                                    rate categories for greater computational efficiency.   Final tree might be evaluated\n");
  printf("                                                    automatically under PROTGAMMAImatrixName[f], depending on the tree search option\n");
  printf("                \"-m PROTGAMMAmatrixName[F]\"       : specified AA matrix + Optimization of substitution rates + GAMMA model of rate \n");
  printf("                                                    heterogeneity (alpha parameter will be estimated)\n");
  printf("                \"-m PROTGAMMAImatrixName[F]\"      : Same as PROTGAMMAmatrixName[F], but with estimate of proportion of invariable sites \n");
  printf("\n");
  printf("                Available AA substitution models: DAYHOFF, DCMUT, JTT, MTREV, WAG, RTREV, CPREV, VT, BLOSUM62, MTMAM, LG, MTART, MTZOA, PMB, HIVB, HIVW, JTTDCMUT, FLU, GTR\n");
  printf("                With the optional \"F\" appendix you can specify if you want to use empirical base frequencies\n");
  printf("                Please note that for mixed models you can in addition specify the per-gene AA model in\n");
  printf("                the mixed model file (see manual for details). Also note that if you estimate AA GTR parameters on a partitioned\n");
  printf("                dataset, they will be linked (estimated jointly) across all partitions to avoid over-parametrization\n");
  printf("\n");
  printf("      -M      Switch on estimation of individual per-partition branch lengths. Only has effect when used in combination with \"-q\"\n");
  printf("              Branch lengths for individual partitions will be printed to separate files\n");
  printf("              A weighted average of the branch lengths is computed by using the respective partition lengths\n");
  printf("\n"),
  printf("              DEFAULT: OFF\n");
  printf("\n");
  printf("      -n      Specifies the name of the output file.\n");
  printf("\n");
  printf("      -o      Specify the name of a single outgrpoup or a comma-separated list of outgroups, eg \"-o Rat\" \n");
  printf("              or \"-o Rat,Mouse\", in case that multiple outgroups are not monophyletic the first name \n");
  printf("              in the list will be selected as outgroup, don't leave spaces between taxon names!\n");
  printf("\n");
  printf("      -p      Specify a random number seed for the parsimony inferences. This allows you to reproduce your results\n");
  printf("              and will help me debug the program.\n");
  printf("\n");
  printf("      -P      Specify the file name of a user-defined AA (Protein) substitution model. This file must contain\n");
  printf("              420 entries, the first 400 being the AA substitution rates (this must be a symmetric matrix) and the\n");
  printf("              last 20 are the empirical base frequencies\n");
  printf("\n");
  printf("      -q      Specify the file name which contains the assignment of models to alignment\n");
  printf("              partitions for multiple models of substitution. For the syntax of this file\n");
  printf("              please consult the manual.\n");
  printf("\n");
  printf("      -r      Specify the file name of a binary constraint tree.\n");
  printf("              this tree does not need to be comprehensive, i.e. must not contain all taxa\n");
  printf("\n");
  printf("      -R      Specify the file name of a binary model parameter file that has previously been generated\n");
  printf("              with RAxML using the -f e tree evaluation option. The file name should be: \n");
  printf("              RAxML_binaryModelParameters.runID\n");
  printf("\n");
  printf("      -s      Specify the name of the alignment data file in PHYLIP format\n");
  printf("\n");
  printf("      -S      Specify the name of a secondary structure file. The file can contain \".\" for \n");
  printf("              alignment columns that do not form part of a stem and characters \"()<>[]{}\" to define \n");
  printf("              stem regions and pseudoknots\n");
  printf("\n");
  printf("      -t      Specify a user starting tree file name in Newick format\n");
  printf("\n");
  printf("      -T      PTHREADS VERSION ONLY! Specify the number of threads you want to run.\n");
  printf("              Make sure to set \"-T\" to at most the number of CPUs you have on your machine,\n");
  printf("              otherwise, there will be a huge performance decrease!\n");
  printf("\n");
  printf("      -U      Try to save memory by using SEV-based implementation for gap columns on large gappy alignments\n");
  printf("              WARNING: this will only work for DNA under GTRGAMMA and is still in an experimental state.\n");
  printf("\n");
  printf("      -v      Display version information\n");
  printf("\n");
  printf("      -w      FULL (!) path to the directory into which RAxML shall write its output files\n");
  printf("\n");
  printf("              DEFAULT: current directory\n");
  printf("\n");
  printf("      -W      Sliding window size for leave-one-out site-specific placement bias algorithm\n");
  printf("              only effective when used in combination with \"-f S\" \n");
  printf("\n");
  printf("              DEFAULT: 100 sites\n");
  printf("\n");
  printf("      -x      Specify an integer number (random seed) and turn on rapid bootstrapping\n");
  printf("              CAUTION: unlike in version 7.0.4 RAxML will conduct rapid BS replicates under \n");
  printf("              the model of rate heterogeneity you specified via \"-m\" and not by default under CAT\n");
  printf("\n");
  printf("      -X      EXPERIMENTAL OPTION: This option will do a per-site estimate of protein substitution models\n");
  printf("              by looping over all given, fixed models LG, WAG, JTT, etc and using their respective base frequencies to independently\n");
  printf("              assign a prot subst. model to each site via ML optimization\n");
  printf("              At present this option only works with the GTR+GAMMA model, unpartitioned datasets, and in the sequential\n");
  printf("              version only.\n");
  printf("\n");
  printf("              DEFAULT: OFF\n");
  printf("\n");
  printf("      -y      If you want to only compute a parsimony starting tree with RAxML specify \"-y\",\n");
  printf("              the program will exit after computation of the starting tree\n");
  printf("\n");
  printf("              DEFAULT: OFF\n");
  printf("\n");
  printf("      -z      Specify the file name of a file containing multiple trees e.g. from a bootstrap\n");
  printf("              that shall be used to draw bipartition values onto a tree provided with \"-t\",\n");
  printf("              It can also be used to compute per site log likelihoods in combination with \"-f g\"\n");
  printf("              and to read a bunch of trees for a couple of other options (\"-f h\", \"-f m\", \"-f n\").\n");
  printf("\n");
  printf("      -#|-N   Specify the number of alternative runs on distinct starting trees\n");
  printf("              In combination with the \"-b\" option, this will invoke a multiple boostrap analysis\n");
  printf("              Note that \"-N\" has been added as an alternative since \"-#\" sometimes caused problems\n");
  printf("              with certain MPI job submission systems, since \"-#\" is often used to start comments.\n");
  printf("              If you want to use the bootstopping criteria specify \"-# autoMR\" or \"-# autoMRE\" or \"-# autoMRE_IGN\"\n");
  printf("              for the majority-rule tree based criteria (see -I option) or \"-# autoFC\" for the frequency-based criterion.\n");
  printf("              Bootstopping will only work in combination with \"-x\" or \"-b\"\n");
  printf("\n");
  printf("              DEFAULT: 1 single analysis\n");
  printf("\n\n\n\n");

}




static void analyzeRunId(char id[128])
{
  int i = 0;

  while(id[i] != '\0')
    {
      if(i >= 128)
 {
   printf("Error: run id after \"-n\" is too long, it has %d characters please use a shorter one\n", i);
   ((0) ? (void) (0) : __assert_fail ("0", "<stdin>", 3736, __PRETTY_FUNCTION__));
 }

      if(id[i] == '/')
 {
   printf("Error character %c not allowed in run ID\n", id[i]);
   ((0) ? (void) (0) : __assert_fail ("0", "<stdin>", 3742, __PRETTY_FUNCTION__));
 }


      i++;
    }

  if(i == 0)
    {
      printf("Error: please provide a string for the run id after \"-n\" \n");
      ((0) ? (void) (0) : __assert_fail ("0", "<stdin>", 3752, __PRETTY_FUNCTION__));
    }

}

static void get_args(int argc, char *argv[], analdef *adef, tree *tr)
{
  boolean
    bad_opt =0,
    resultDirSet = 0;

  char
    resultDir[1024] = "",
    aut[256],
    *optarg,
    model[2048] = "",
    secondaryModel[2048] = "",
    multiStateModel[2048] = "",
    modelChar;

  double
    likelihoodEpsilon,
    wcThreshold,
    fastEPAthreshold;

  int
    optind = 1,
    c,
    nameSet = 0,
    alignmentSet = 0,
    multipleRuns = 0,
    constraintSet = 0,
    treeSet = 0,
    groupSet = 0,
    modelSet = 0,
    treesSet = 0;

  boolean
    bSeedSet = 0,
    xSeedSet = 0,
    multipleRunsSet = 0;

  run_id[0] = 0;
  workdir[0] = 0;
  seq_file[0] = 0;
  tree_file[0] = 0;
  model[0] = 0;
  weightFileName[0] = 0;
  modelFileName[0] = 0;
# 3809 "<stdin>"
  tr->useFastScaling = 1;


  tr->bootStopCriterion = -1;
  tr->wcThreshold = 0.03;
  tr->doCutoff = 1;
  tr->secondaryStructureModel = 11;
  tr->searchConvergenceCriterion = 0;
  tr->catOnly = 0;
  tr->multiGene = 0;
  tr->useEpaHeuristics = 0;
  tr->fastEPAthreshold = -1.0;
  tr->multiStateModel = 2;
  tr->useGappedImplementation = 0;
  tr->saveMemory = 0;
  tr->estimatePerSiteAA = 0;




  while(!bad_opt &&
 ((c = mygetopt(argc,argv,"R:T:E:N:B:L:P:S:A:G:H:I:J:K:W:l:x:z:g:r:e:a:b:c:f:i:m:t:w:s:n:o:q:#:p:vdyjhkMDFCQUX", &optind, &optarg))!=-1))
    {
    switch(c)
      {
      case 'X':
 tr->estimatePerSiteAA = 1;
 tr->useFastScaling = 0;
 break;
      case 'W':
 sscanf(optarg,"%d", &(adef->slidingWindowSize));
 if(adef->slidingWindowSize <= 0)
   {
     printf("You can't use a sliding window size smaller than 1, you specified %d\n", adef->slidingWindowSize);
     exit(-1);
   }
 if(adef->slidingWindowSize <= 10)
   {
     printf("You specified a small sliding window size of %d sites\n", adef->slidingWindowSize);
     printf("Are you sure you want to do this?\n");
   }
 if(adef->slidingWindowSize >= 500)
   {
     printf("You specified a large sliding window size of %d sites\n", adef->slidingWindowSize);
     printf("Are you sure you want to do this?\n");
   }
 break;
      case 'U':
 tr->saveMemory = 1;
 break;
      case 'R':
 adef->useBinaryModelFile = 1;
 strcpy(binaryModelParamsInputFileName, optarg);
 break;
      case 'K':
 {
   const char *modelList[3] = { "ORDERED", "MK", "GTR"};
   const int states[3] = {0, 1, 2};
   int i;

   sscanf(optarg, "%s", multiStateModel);

   for(i = 0; i < 3; i++)
     if(strcmp(multiStateModel, modelList[i]) == 0)
       break;

   if(i < 3)
     tr->multiStateModel = states[i];
   else
     {
       printf("The multi-state model %s you want to use does not exist, exiting .... \n", multiStateModel);
       errorExit(0);
     }


 }
 break;
      case 'A':
 {
   const char *modelList[21] = { "S6A", "S6B", "S6C", "S6D", "S6E", "S7A", "S7B", "S7C", "S7D", "S7E", "S7F", "S16", "S16A", "S16B", "S16C",
          "S16D", "S16E", "S16F", "S16I", "S16J", "S16K"};
   int i;

   sscanf(optarg, "%s", secondaryModel);

   for(i = 0; i < 21; i++)
     if(strcmp(secondaryModel, modelList[i]) == 0)
       break;

   if(i < 21)
     tr->secondaryStructureModel = i;
   else
     {
       printf("The secondary structure model %s you want to use does not exist, exiting .... \n", secondaryModel);
       errorExit(0);
     }
 }
 break;
      case 'B':
 sscanf(optarg,"%lf", &wcThreshold);
 tr->wcThreshold = wcThreshold;
 if(wcThreshold <= 0.0 || wcThreshold >= 1.0)
   {
     printf("\nBootstrap threshold must be set to values between 0.0 and 1.0, you just set it to %f\n", wcThreshold);
     exit(-1);
   }
 if(wcThreshold < 0.01 || wcThreshold > 0.05)
   {
     printf("\n\nWARNING, reasonable settings for Bootstopping threshold with MR-based criteria range between 0.01 and 0.05.\n");
     printf("You are just setting it to %f, the most reasonable empirically determined setting is 0.03 \n\n", wcThreshold);
   }
 break;
      case 'C':
 tr->multiGene = 1;
 break;
      case 'D':
 tr->searchConvergenceCriterion = 1;
 break;
      case 'E':
 strcpy(excludeFileName, optarg);
 adef->useExcludeFile = 1;
 break;
      case 'F':
 tr->catOnly = 1;
 break;
      case 'G':
 tr->useEpaHeuristics = 1;

 sscanf(optarg,"%lf", &fastEPAthreshold);
 tr->fastEPAthreshold = fastEPAthreshold;

 if(fastEPAthreshold <= 0.0 || fastEPAthreshold >= 1.0)
   {
     printf("\nHeuristic EPA threshold must be set to values between 0.0 and 1.0, you just set it to %f\n", fastEPAthreshold);
     exit(-1);
   }
 if(fastEPAthreshold < 0.015625 || fastEPAthreshold > 0.5)
   {
     printf("\n\nWARNING, reasonable settings for heuristic EPA threshold range between 0.015625 (1/64) and 0.5 (1/2).\n");
     printf("You are just setting it to %f\n\n", fastEPAthreshold);
   }



 break;

      case 'I':
 adef->readTaxaOnly = 1;
 adef->mode = 14;
 if((sscanf(optarg,"%s", aut) > 0) && ((strcmp(aut, "autoFC") == 0) || (strcmp(aut, "autoMR") == 0) ||
           (strcmp(aut, "autoMRE") == 0) || (strcmp(aut, "autoMRE_IGN") == 0)))
   {
     if((strcmp(aut, "autoFC") == 0))
       tr->bootStopCriterion = 0;
     if((strcmp(aut, "autoMR") == 0))
       tr->bootStopCriterion = 1;
     if((strcmp(aut, "autoMRE") == 0))
       tr->bootStopCriterion = 2;
     if((strcmp(aut, "autoMRE_IGN") == 0))
       tr->bootStopCriterion = 3;
   }
 else
   {
     if(processID == 0)
       printf("Use -I a posteriori bootstop option either as \"-I autoFC\" or \"-I autoMR\" or \"-I autoMRE\" or \"-I autoMRE_IGN\"\n");
     errorExit(0);
   }
 break;
      case 'J':
 adef->readTaxaOnly = 1;
 adef->mode = 22;

 if((sscanf(optarg,"%s", aut) > 0) && ((strcmp(aut, "MR") == 0) || (strcmp(aut, "MRE") == 0) || (strcmp(aut, "STRICT") == 0) ||
           (strcmp(aut, "STRICT_DROP") == 0) || (strcmp(aut, "MR_DROP") == 0)))
   {
     if((strcmp(aut, "MR") == 0))
       tr->consensusType = 0;
     if((strcmp(aut, "MR_DROP") == 0))
       {
  tr->consensusType = 0;
  adef->leaveDropMode = 1;
       }

     if((strcmp(aut, "MRE") == 0))
       tr->consensusType = 1;


     if((strcmp(aut, "STRICT") == 0))
       tr->consensusType = 2;
     if((strcmp(aut, "STRICT_DROP") == 0))
       {
  tr->consensusType = 2;
  adef->leaveDropMode = 1;
       }
   }
 else
   {
     if(processID == 0)
       printf("Use -J consensus tree option either as \"-J MR\" or \"-J MRE\" or \"-J STRICT\" or \"-J MR_DROP\"  or \"-J STRICT_DROP\"\n");
     errorExit(0);
   }

 break;
      case 'M':
 adef->perGeneBranchLengths = 1;
 break;
      case 'P':
 strcpy(proteinModelFileName, optarg);
 adef->userProteinModel = 1;

 break;
      case 'S':
 adef->useSecondaryStructure = 1;
 strcpy(secondaryStructureFileName, optarg);
 break;
      case 'T':



 if(processID == 0)
   {
     printf("Option -T does not have any effect with the sequential or parallel MPI version.\n");
     printf("It is used to specify the number of threads for the Pthreads-based parallelization\n");
   }

 break;
      case 'o':
 {
   char *outgroups;
   outgroups = (char*)malloc(sizeof(char) * (strlen(optarg) + 1));
   strcpy(outgroups, optarg);
   parseOutgroups(outgroups, tr);
   free(outgroups);
   adef->outgroup = 1;
 }
 break;
      case 'k':
 adef->bootstrapBranchLengths = 1;
 break;
      case 'z':
 strcpy(bootStrapFile, optarg);
 treesSet = 1;
 break;
      case 'd':
 adef->randomStartingTree = 1;
 break;
      case 'g':
 strcpy(tree_file, optarg);
 adef->grouping = 1;
 adef->restart = 1;
 groupSet = 1;
 break;
      case 'r':
 strcpy(tree_file, optarg);
 adef->restart = 1;
 adef->constraint = 1;
 constraintSet = 1;
 break;
      case 'e':
 sscanf(optarg,"%lf", &likelihoodEpsilon);
 adef->likelihoodEpsilon = likelihoodEpsilon;
 break;
      case 'q':
 strcpy(modelFileName,optarg);
 adef->useMultipleModel = 1;
        break;
      case 'p':
 sscanf(optarg,"%ld", &(adef->parsimonySeed));
 if(adef->parsimonySeed <= 0)
   {
     printf("Parsimony seed specified via -p must be greater than zero\n");
     errorExit(-1);
   }
 break;
      case 'N':
      case '#':
 if(sscanf(optarg,"%d", &multipleRuns) > 0)
   {
     adef->multipleRuns = multipleRuns;
   }
 else
   {
     if((sscanf(optarg,"%s", aut) > 0) && ((strcmp(aut, "autoFC") == 0) || (strcmp(aut, "autoMR") == 0) ||
        (strcmp(aut, "autoMRE") == 0) || (strcmp(aut, "autoMRE_IGN") == 0)))

       {
  adef->bootStopping = 1;
  adef->multipleRuns = 1000;

  if((strcmp(aut, "autoFC") == 0))
    tr->bootStopCriterion = 0;
  if((strcmp(aut, "autoMR") == 0))
    tr->bootStopCriterion = 1;
  if((strcmp(aut, "autoMRE") == 0))
    tr->bootStopCriterion = 2;
  if((strcmp(aut, "autoMRE_IGN") == 0))
    tr->bootStopCriterion = 3;
       }
     else
       {
  if(processID == 0)
    {
      printf("Use -# or -N option either with an integer, e.g., -# 100 or with -# autoFC or -# autoMR or -# autoMRE or -# autoMRE_IGN\n");
      printf("or -N 100 or  -N autoFC or -N autoMR or -N autoMRE or -N autoMRE_IGN respectively, note that auto will not work for the\n");
      printf("MPI-based parallel version\n");
    }
  errorExit(0);
       }
   }
 multipleRunsSet = 1;
 break;
      case 'v':
 printVersionInfo();
 errorExit(0);
      case 'y':
 adef->startingTreeOnly = 1;
 break;
      case 'h':
 printREADME();
 errorExit(0);
      case 'j':
 adef->checkpoints = 1;
 break;
      case 'a':
 strcpy(weightFileName,optarg);
 adef->useWeightFile = 1;
        break;
      case 'b':
 sscanf(optarg,"%ld", &adef->boot);
 if(adef->boot <= 0)
   {
     printf("Bootstrap seed specified via -b must be greater than zero\n");
     errorExit(-1);
   }
 bSeedSet = 1;
 break;
      case 'x':
 sscanf(optarg,"%ld", &adef->rapidBoot);
 if(adef->rapidBoot <= 0)
   {
     printf("Bootstrap seed specified via -x must be greater than zero\n");
     errorExit(-1);
   }
 xSeedSet = 1;
 break;
      case 'c':
 sscanf(optarg, "%d", &adef->categories);
 break;
      case 'f':
 sscanf(optarg, "%c", &modelChar);
 switch(modelChar)
   {
   case 'A':
     adef->mode = 30;
     adef->compressPatterns = 0;
     break;
   case 'a':
     adef->allInOne = 1;
     adef->mode = 1;
     tr->doCutoff = 1;
     break;
   case 'b':
     adef->readTaxaOnly = 1;
     adef->mode = 3;
     break;
   case 'c':
     adef->mode = 5;
     break;
   case 'd':
     adef->mode = 1;
     tr->doCutoff = 1;
     break;
   case 'e':
     adef->mode = 0;
     break;
   case 'F':
     adef->mode = 24;
     adef->veryFast = 0;
     break;
   case 'E':
     adef->mode = 24;
     adef->veryFast = 1;
     break;
   case 'g':
     tr->useFastScaling = 0;
     adef->mode = 6;
     break;
   case 'h':
     adef->mode = 0;
     adef->likelihoodTest = 1;
     tr->useFastScaling = 0;
     break;
   case 'i':
     adef->mode = 23;
     adef->meshSearch = 0;
     break;
   case 'I':
     adef->mode = 23;
     adef->meshSearch = 1;
     break;
   case 'j':
     adef->mode = 12;
     adef->generateBS = 1;
     break;
   case 'J':
     adef->mode = 28;
     tr->useFastScaling = 0;
     break;
   case 'm':
     adef->readTaxaOnly = 1;
     adef->mode = 18;
     break;
   case 'n':
     adef->mode = 17;
     break;
   case 'o':
     adef->mode = 1;
     tr->doCutoff = 0;
     break;
   case 'p':
     adef->mode = 7;
     break;
   case 'r':
     adef->readTaxaOnly = 1;
     adef->mode = 20;
     break;
   case 's':
     adef->mode = 4;
     break;
   case 'S':
     adef->mode = 27;
     tr->useFastScaling = 0;
     adef->compressPatterns = 0;
     break;
   case 't':
     adef->mode = 1;
     tr->doCutoff = 1;
     adef->permuteTreeoptimize = 1;
     break;
   case 'u':
     adef->mode = 21;
     tr->useFastScaling = 0;
     adef->compressPatterns = 0;
     break;
   case 'v':
     adef->mode = 9;







     break;
   case 'y':
     adef->mode = 29;
     break;
   case 'w':
     adef->mode = 13;
     adef->computeELW = 1;
     break;
   case 'x':
     adef->mode = 11;
     adef->computeDistance = 1;
     break;
   default:
     {
       if(processID == 0)
  {
    printf("Error select one of the following algorithms via -f :\n");
    printMinusFUsage();
  }
       errorExit(-1);
     }
   }
 break;
      case 'i':
 sscanf(optarg, "%d", &adef->initial);
 adef->initialSet = 1;
 break;
      case 'n':
        strcpy(run_id,optarg);
 analyzeRunId(run_id);
 nameSet = 1;
        break;
      case 'w':
        strcpy(resultDir, optarg);
 resultDirSet = 1;
        break;
      case 't':
 strcpy(tree_file, optarg);
 adef->restart = 1;
 treeSet = 1;
 break;
      case 's':
 strcpy(seq_file, optarg);
 alignmentSet = 1;
 break;
      case 'm':
 strcpy(model,optarg);
 if(modelExists(model, adef) == 0)
   {
     if(processID == 0)
       {
  printf("Model %s does not exist\n\n", model);
                printf("For BINARY data use: BINCAT                or BINGAMMA                or\n");
  printf("                     BINCATI               or BINGAMMAI                 \n");
  printf("For DNA data use:    GTRCAT                or GTRGAMMA                or\n");
  printf("                     GTRCATI               or GTRGAMMAI                 \n");
  printf("For AA data use:     PROTCATmatrixName[F]  or PROTGAMMAmatrixName[F]  or\n");
  printf("                     PROTCATImatrixName[F] or PROTGAMMAImatrixName[F]   \n");
  printf("The AA substitution matrix can be one of the following: \n");
  printf("DAYHOFF, DCMUT, JTT, MTREV, WAG, RTREV, CPREV, VT, BLOSUM62, MTMAM, LG, MTART, MTZOA, PMB, HIVB, HIVW, JTTDCMUT, FLU, GTR\n\n");
  printf("With the optional \"F\" appendix you can specify if you want to use empirical base frequencies\n");
  printf("Please note that for mixed models you can in addition specify the per-gene model in\n");
  printf("the mixed model file (see manual for details)\n");
       }
     errorExit(-1);
   }
 else
   modelSet = 1;
 break;
      default:
 errorExit(-1);
    }
  }
# 4350 "<stdin>"
  if(bSeedSet && xSeedSet)
    {
      printf("Error, you can't seed random seeds by using -x and -b at the same time\n");
      printf("use either -x or -b, exiting ......\n");
      errorExit(-1);
    }

  if(bSeedSet || xSeedSet)
    {
      if(!multipleRunsSet)
 {
   printf("Error, you have specified a random number seed via -x or -b for some sort of bootstrapping,\n");
   printf("but you have not specified a number of replicates via -N or -#, exiting ....\n");
   errorExit(-1);
 }

      if(adef->multipleRuns == 1)
 {
   printf("WARNING, you have specified a random number seed via -x or -b for some sort of bootstrapping,\n");
   printf("but you have specified a number of replicates via -N or -# euqal to one\n");
   printf("Are you really sure that this is what you want to do?\n");
 }


    }


  if(adef->computeELW)
    {
      if(processID == 0)
 {
   if(adef->boot == 0)
     {
       printf("Error, you must specify a bootstrap seed via \"-b\" to compute ELW statistics\n");
       errorExit(-1);
     }

   if(adef->multipleRuns < 2)
     {
       printf("Error, you must specify the number of BS replicates via \"-#\" or \"-N\" to compute ELW statistics\n");
       printf("it should be larger than 1, recommended setting is 100\n");
       errorExit(-1);
     }

   if(!treesSet)
     {
       printf("Error, you must specify an input file containing several candidate trees\n");
       printf("via \"-z\" to compute ELW statistics.\n");
       errorExit(-1);
     }

   if(!isGamma(adef))
     {
       printf("Error ELW test can only be conducted undetr GAMMA or GAMMA+P-Invar models\n");
       errorExit(-1);
     }
 }
    }





  if(((!adef->boot) && (!adef->rapidBoot)) && adef->bootStopping)
    {
      if(processID == 0)
 {
   printf("Can't use automatic bootstopping without actually doing a Bootstrap\n");
   printf("Specify either -x randomNumberSeed (rapid) or -b randomNumberSeed (standard)\n");
   errorExit(-1);
 }
    }

  if(adef->boot && adef->rapidBoot)
    {
      if(processID == 0)
 {
   printf("Can't use standard and rapid BOOTSTRAP simultaneously\n");
   errorExit(-1);
 }
    }

  if(adef->rapidBoot)
    {
      if(processID == 0 && (adef->restart || treesSet) && !(groupSet || constraintSet))
 {
   printf("Error, starting tree(s) will be ignored by rapid Bootstrapping\n");
   errorExit(-1);
 }
    }

  if(adef->allInOne && (adef->rapidBoot == 0))
    {
      if(processID == 0)
 {
   printf("Error, to carry out an ML search after a rapid BS inference you must specify a random number seed with -x\n");
   errorExit(-1);
 }
    }




  if(adef->mode == 6)
    {
      if(!isGamma(adef))
 {
   if(processID == 0)
     printf("\n ERROR: Computation of per-site log LHs is only allowed under GAMMA model of rate heterogeneity!\n");
   errorExit(-1);
 }

      if(!treesSet)
 {
   if(processID == 0)
     printf("\n ERROR: For Computation of per-site log LHs you need to specify several input trees with \"-z\"\n");
   errorExit(-1);
 }
    }



  if(adef->mode == 4 && (!adef->useMultipleModel))
    {
      if(processID == 0)
 {
   printf("\n  Error, you are trying to split a multi-gene alignment into individual genes with the \"-f s\" option\n");
   printf("Without specifying a multiple model file with \"-q modelFileName\" \n");
 }
      errorExit(-1);
    }

  if(adef->mode == 3 && !treesSet)
    {
      if(processID == 0)
 printf("\n  Error, in bipartition computation mode you must specify a file containing multiple trees with the \"-z\" option\n");
      errorExit(-1);
    }

  if(adef->mode == 3 && !adef->restart)
    {
      if(processID == 0)
 printf("\n  Error, in bipartition computation mode you must specify a tree on which bipartition information will be drawn with the \"-t\" option\n");
      errorExit(-1);
    }

  if(!modelSet)
    {
      if(processID == 0)
 printf("\n Error, you must specify a model of substitution with the \"-m\" option\n");
      errorExit(-1);
    }

  if(adef->computeDistance)
    {
      if(isCat(adef))
 {
   if(processID == 0)
     printf("\n Error pairwise distance computation only allowed for GAMMA-based models of rate heterogeneity\n");
   errorExit(-1);
 }

      if(adef->restart)
 {
   if(adef->randomStartingTree)
     {
       if(processID == 0)
  printf("\n Error pairwise distance computation not allowed for random starting trees\n");
       errorExit(-1);
     }

   if(adef->constraint)
     {
       if(processID == 0)
  printf("\n Error pairwise distance computation not allowed for binary backbone  constraint tree\n");
       errorExit(-1);
     }

   if(adef->grouping)
     {
       if(processID == 0)
  printf("\n Error pairwise distance computation not allowed for constraint tree\n");
       errorExit(-1);
     }

 }

      if(adef->boot || adef->rapidBoot)
 {
   if(processID == 0)
     printf("\n Bootstrapping not implemented for pairwise distance computation\n");
   errorExit(-1);
 }
    }
# 4552 "<stdin>"
  if(!adef->restart && adef->mode == 7)
    {
       if(processID == 0)
  {
    printf("\n You need to specify an incomplete binary input tree with \"-t\" to execute \n");
    printf(" RAxML MP stepwise addition with \"-f p\"\n");
  }
      errorExit(-1);
    }



  if(adef->restart && adef->randomStartingTree)
    {
      if(processID == 0)
 {
   if(adef->constraint)
     {
       printf("\n Error you specified a binary constraint tree with -r AND the computation\n");
       printf("of a random starting tree with -d for the same run\n");
     }
   else
     {
       if(adef->grouping)
  {
    printf("\n Error you specified a multifurcating constraint tree with -g AND the computation\n");
    printf("of a random starting tree with -d for the same run\n");
  }
       else
  {
    printf("\n Error you specified a starting tree with -t AND the computation\n");
    printf("of a random starting tree with -d for the same run\n");
  }
     }
 }
      errorExit(-1);
    }

  if(!treeSet && adef->mode == 30)
    {
      if(processID == 0)
 printf("\n Error you need to specify a ROOTED binary reference tree for ancestral state computations\n");
      errorExit(-1);
    }

  if(treeSet && constraintSet)
    {
      if(processID == 0)
 printf("\n Error you specified a binary constraint tree AND a starting tree for the same run\n");
      errorExit(-1);
    }


  if(treeSet && groupSet)
    {
      if(processID == 0)
 printf("\n Error you specified a multifurcating constraint tree AND a starting tree for the same run\n");
      errorExit(-1);
    }


  if(groupSet && constraintSet)
    {
      if(processID == 0)
 printf("\n Error you specified a bifurcating constraint tree AND a multifurcating constraint tree for the same run\n");
      errorExit(-1);
    }

  if(adef->restart && adef->startingTreeOnly)
    {
      if(processID == 0)
 {
   printf("\n Error conflicting options: you want to compute only a parsimony starting tree with -y\n");
   printf(" while you actually specified a starting tree with -t %s\n", tree_file);
 }
      errorExit(-1);
    }

  if((adef->mode == 0) && (!adef->restart))
    {
      if(processID == 0)
 printf("\n Error: please specify a treefile for the tree you want to evaluate with -t\n");
      errorExit(-1);
    }
# 4672 "<stdin>"
   if((adef->mode == 0) && (isCat(adef)))
     {
       if(processID == 0)
  {
    printf("\n Warning: tree evaluation with CAT model of rate heterogeneity\n");
    printf("Only compare likelihood values for identical rate category assignments\n");
    printf("CAT-based Branch lengths are on average shorter by factor 0.5 than GAMMA-based branch lengths\n");
    printf("... but highly correlated with GAMMA branch lengths\n");
  }
     }

  if(!nameSet)
    {
      if(processID == 0)
 printf("\n Error: please specify a name for this run with -n\n");
      errorExit(-1);
    }

  if(! alignmentSet && !adef->readTaxaOnly)
    {
      if(processID == 0)
 printf("\n Error: please specify an alignment for this run with -s\n");
      errorExit(-1);
    }


  {




    const
      char *separator = "/";


    if(resultDirSet)
      {
 char
   dir[1024] = "";


 if(resultDir[0] != separator[0])
   strcat(dir, separator);


 strcat(dir, resultDir);

 if(dir[strlen(dir) - 1] != separator[0])
   strcat(dir, separator);
 strcpy(workdir, dir);
      }
    else
      {
 char
   dir[1024] = "",
   *result = getcwd(dir, sizeof(dir));

 ((result != (char*)((void *)0)) ? (void) (0) : __assert_fail ("result != (char*)((void *)0)", "<stdin>", 4729, __PRETTY_FUNCTION__));

 if(dir[strlen(dir) - 1] != separator[0])
   strcat(dir, separator);

 strcpy(workdir, dir);
      }
  }

  return;
}




void errorExit(int e)
{





  exit(e);

}



static void makeFileNames(void)
{
  int infoFileExists = 0;


  strcpy(permFileName, workdir);
  strcpy(resultFileName, workdir);
  strcpy(logFileName, workdir);
  strcpy(checkpointFileName, workdir);
  strcpy(infoFileName, workdir);
  strcpy(randomFileName, workdir);
  strcpy(bootstrapFileName, workdir);
  strcpy(bipartitionsFileName, workdir);
  strcpy(bipartitionsFileNameBranchLabels, workdir);
  strcpy(ratesFileName, workdir);
  strcpy(lengthFileName, workdir);
  strcpy(lengthFileNameModel, workdir);
  strcpy(perSiteLLsFileName, workdir);
  strcpy(binaryModelParamsOutputFileName, workdir);

  strcat(permFileName, "RAxML_parsimonyTree.");
  strcat(resultFileName, "RAxML_result.");
  strcat(logFileName, "RAxML_log.");
  strcat(checkpointFileName, "RAxML_checkpoint.");
  strcat(infoFileName, "RAxML_info.");
  strcat(randomFileName, "RAxML_randomTree.");
  strcat(bootstrapFileName, "RAxML_bootstrap.");
  strcat(bipartitionsFileName, "RAxML_bipartitions.");
  strcat(bipartitionsFileNameBranchLabels, "RAxML_bipartitionsBranchLabels.");
  strcat(ratesFileName, "RAxML_perSiteRates.");
  strcat(lengthFileName, "RAxML_treeLength.");
  strcat(lengthFileNameModel, "RAxML_treeLengthModel.");
  strcat(perSiteLLsFileName, "RAxML_perSiteLLs.");
  strcat(binaryModelParamsOutputFileName, "RAxML_binaryModelParameters.");

  strcat(permFileName, run_id);
  strcat(resultFileName, run_id);
  strcat(logFileName, run_id);
  strcat(checkpointFileName, run_id);
  strcat(infoFileName, run_id);
  strcat(randomFileName, run_id);
  strcat(bootstrapFileName, run_id);
  strcat(bipartitionsFileName, run_id);
  strcat(bipartitionsFileNameBranchLabels, run_id);
  strcat(ratesFileName, run_id);
  strcat(lengthFileName, run_id);
  strcat(lengthFileNameModel, run_id);
  strcat(perSiteLLsFileName, run_id);
  strcat(binaryModelParamsOutputFileName, run_id);
# 4818 "<stdin>"
  if(processID == 0)
    {
      infoFileExists = filexists(infoFileName);

      if(infoFileExists)
 {
   printf("RAxML output files with the run ID <%s> already exist \n", run_id);
   printf("in directory %s ...... exiting\n", workdir);

   exit(-1);
 }
    }
}
# 4846 "<stdin>"
void printBaseFrequencies(tree *tr)
{
  if(processID == 0)
    {
      int
 model;

      for(model = 0; model < tr->NumberOfModels; model++)
 {
   int i;

   printBothOpen("Partition: %d with name: %s\n", model, tr->partitionData[model].partitionName);
   printBothOpen("Base frequencies: ");

   for(i = 0; i < tr->partitionData[model].states; i++)
     printBothOpen("%1.3f ", tr->partitionData[model].frequencies[i]);

   printBothOpen("\n\n");
 }
    }
}

static void printModelAndProgramInfo(tree *tr, analdef *adef, int argc, char *argv[])
{
  if(processID == 0)
    {
      int i, model;
      FILE *infoFile = myfopen(infoFileName, "ab");
      char modelType[128];

      if(!adef->readTaxaOnly)
 {
   if(adef->useInvariant)
     strcpy(modelType, "GAMMA+P-Invar");
   else
     strcpy(modelType, "GAMMA");
 }

      printBoth(infoFile, "\n\nThis is %s version %s released by Alexandros Stamatakis in %s.\n\n", "RAxML", "7.3.0", "June 2011");
      printBoth(infoFile, "With greatly appreciated code contributions by:\n");
      printBoth(infoFile, "Andre Aberer (HITS)\n");
      printBoth(infoFile, "Simon Berger (HITS)\n");
      printBoth(infoFile, "Nick Pattengale (Sandia)\n");
      printBoth(infoFile, "Wayne Pfeiffer (SDSC)\n");
      printBoth(infoFile, "Akifumi S. Tanabe (Univ. Tsukuba)\n\n");

      if(!adef->readTaxaOnly)
 {
   if(!adef->compressPatterns)
     printBoth(infoFile, "\nAlignment has %d columns\n\n", tr->cdta->endsite);
   else
     printBoth(infoFile, "\nAlignment has %d distinct alignment patterns\n\n", tr->cdta->endsite);

   if(adef->useInvariant)
     printBoth(infoFile, "Found %d invariant alignment patterns that correspond to %d columns \n", tr->numberOfInvariableColumns, tr->weightOfInvariableColumns);

   printBoth(infoFile, "Proportion of gaps and completely undetermined characters in this alignment: %3.2f%s\n", 100.0 * adef->gapyness, "%");
 }

      switch(adef->mode)
 {
 case 11:
   printBoth(infoFile, "\nRAxML Computation of pairwise distances\n\n");
   break;
 case 0 :
   printBoth(infoFile, "\nRAxML Model Optimization up to an accuracy of %f log likelihood units\n\n", adef->likelihoodEpsilon);
   break;
 case 1:
   if(adef->rapidBoot)
     {
       if(adef->allInOne)
  printBoth(infoFile, "\nRAxML rapid bootstrapping and subsequent ML search\n\n");
       else
  printBoth(infoFile, "\nRAxML rapid bootstrapping algorithm\n\n");
     }
   else
     printBoth(infoFile, "\nRAxML rapid hill-climbing mode\n\n");
   break;
 case 3:
   printBoth(infoFile, "\nRAxML Bipartition Computation: Drawing support values from trees in file %s onto tree in file %s\n\n",
      bootStrapFile, tree_file);
   break;
 case 6:
   printBoth(infoFile, "\nRAxML computation of per-site log likelihoods\n");
   break;
 case 7:
   printBoth(infoFile, "\nRAxML stepwise MP addition to incomplete starting tree\n\n");
   break;
 case 9:
   printBoth(infoFile, "\nRAxML likelihood-based placement algorithm\n\n");
   break;
 case 29:
   printBoth(infoFile, "\nRAxML parsimony-based placement algorithm\n\n");
   break;
 case 12:
   printBoth(infoFile, "\nRAxML BS replicate generation\n\n");
   break;
 case 13:
   printBoth(infoFile, "\nRAxML ELW test\n\n");
   break;
 case 14:
   printBoth(infoFile, "\nRAxML a posteriori Bootstrap convergence assessment\n\n");
   break;
 case 22:
   if(adef->leaveDropMode)
     printBoth(infoFile, "\nRAxML rogue taxa computation by Andre Aberer (HITS)\n\n");
   else
     printBoth(infoFile, "\nRAxML consensus tree computation\n\n");
   break;
 case 17:
   printBoth(infoFile, "\nRAxML computation of likelihoods for a set of trees\n\n");
   break;
 case 18:
   printBoth(infoFile, "\nRAxML computation of bipartition support correlation on two sets of trees\n\n");
   break;
 case 20:
   printBoth(infoFile, "\nRAxML computation of RF distances for all pairs of trees in a set of trees\n\n");
   break;
 case 21:
   printBoth(infoFile, "\nRAxML morphological calibrator using Maximum Likelihood\n\n");
   break;
 case 23:
   printBoth(infoFile, "\nRAxML experimental mesh tree search\n\n");
   break;
 case 24:
   printBoth(infoFile, "\nRAxML experimental very fast tree search\n\n");
   break;
 case 28:
   printBoth(infoFile, "\nRAxML computation of SH-like support values on a given tree\n\n");
   break;
 case 27:
   printBoth(infoFile, "\nRAxML exprimental site-specfific phylogenetic placement bias analysis algorithm\n\n");
   break;

 case 30:
   printBoth(infoFile, "\nRAxML marginal ancestral state computation\n\n");
   break;
 default:
   ((0) ? (void) (0) : __assert_fail ("0", "<stdin>", 4984, __PRETTY_FUNCTION__));
 }


      if(!adef->readTaxaOnly)
 {
   if(adef->perGeneBranchLengths)
     printBoth(infoFile, "Using %d distinct models/data partitions with individual per partition branch length optimization\n\n\n", tr->NumberOfModels);
   else
     printBoth(infoFile, "Using %d distinct models/data partitions with joint branch length optimization\n\n\n", tr->NumberOfModels);
 }

      if(adef->mode == 1)
 {
   if(adef->rapidBoot)
     {
       if(adef->allInOne)
  printBoth(infoFile, "\nExecuting %d rapid bootstrap inferences and thereafter a thorough ML search \n\n", adef->multipleRuns);
       else
  printBoth(infoFile, "\nExecuting %d rapid bootstrap inferences\n\n", adef->multipleRuns);
     }
   else
     {
       if(adef->boot)
  printBoth(infoFile, "Executing %d non-parametric bootstrap inferences\n\n", adef->multipleRuns);
       else
  {
    char treeType[1024];

    if(adef->restart)
      strcpy(treeType, "user-specifed");
    else
      {
        if(adef->randomStartingTree)
   strcpy(treeType, "distinct complete random");
        else
   strcpy(treeType, "distinct randomized MP");
      }

    printBoth(infoFile, "Executing %d inferences on the original alignment using %d %s trees\n\n",
       adef->multipleRuns, adef->multipleRuns, treeType);
  }
     }
 }


      if(!adef->readTaxaOnly)
 {
   printBoth(infoFile, "All free model parameters will be estimated by RAxML\n");


   if(tr->rateHetModel == 1 || tr->rateHetModel == 2)
     printBoth(infoFile, "%s model of rate heteorgeneity, ML estimate of alpha-parameter\n\n", modelType);
   else
     {
       printBoth(infoFile, "ML estimate of %d per site rate categories\n\n", adef->categories);
       if(adef->mode != 9 && adef->mode != 29)
  printBoth(infoFile, "Likelihood of final tree will be evaluated and optimized under %s\n\n", modelType);
     }

   if(adef->mode != 9 && adef->mode != 29)
     printBoth(infoFile, "%s Model parameters will be estimated up to an accuracy of %2.10f Log Likelihood units\n\n",
        modelType, adef->likelihoodEpsilon);


   for(model = 0; model < tr->NumberOfModels; model++)
     {
       printBoth(infoFile, "Partition: %d\n", model);
       printBoth(infoFile, "Alignment Patterns: %d\n", tr->partitionData[model].upper - tr->partitionData[model].lower);
       printBoth(infoFile, "Name: %s\n", tr->partitionData[model].partitionName);

       switch(tr->partitionData[model].dataType)
  {
  case 1:
    printBoth(infoFile, "DataType: DNA\n");
    printBoth(infoFile, "Substitution Matrix: GTR\n");
    break;
  case 2:
    ((tr->partitionData[model].protModels >= 0 && tr->partitionData[model].protModels < 21) ? (void) (0) : __assert_fail ("tr->partitionData[model].protModels >= 0 && tr->partitionData[model].protModels < 21", "<stdin>", 5062, __PRETTY_FUNCTION__));
    printBoth(infoFile, "DataType: AA\n");
    if(tr->partitionData[model].protModels != 18)
      {
        printBoth(infoFile, "Substitution Matrix: %s\n", protModels[tr->partitionData[model].protModels]);
        printBoth(infoFile, "Using %s base frequencies\n", (tr->partitionData[model].usePredefinedProtFreqs == 1)?"fixed":"empirical");
      }
    else
      {
         printBoth(infoFile, "Substitution Matrix File name: %s\n", tr->partitionData[model].proteinSubstitutionFileName);
         printBoth(infoFile, "Using base frequencies as provided in the model file\n");
      }
    break;
  case 0:
    printBoth(infoFile, "DataType: BINARY/MORPHOLOGICAL\n");
    printBoth(infoFile, "Substitution Matrix: Uncorrected\n");
    break;
  case 3:
    printBoth(infoFile, "DataType: SECONDARY STRUCTURE\n");
    printBoth(infoFile, "Substitution Matrix: %s\n", secondaryModelList[tr->secondaryStructureModel]);
    break;
  case 4:
    printBoth(infoFile, "DataType: SECONDARY STRUCTURE 6 STATE\n");
    printBoth(infoFile, "Substitution Matrix: %s\n", secondaryModelList[tr->secondaryStructureModel]);
    break;
  case 5:
    printBoth(infoFile, "DataType: SECONDARY STRUCTURE 7 STATE\n");
    printBoth(infoFile, "Substitution Matrix: %s\n", secondaryModelList[tr->secondaryStructureModel]);
    break;
  case 6:
    printBoth(infoFile, "DataType: Multi-State with %d distinct states in use (maximum 32)\n",tr->partitionData[model].states);
    switch(tr->multiStateModel)
      {
      case 0:
        printBoth(infoFile, "Substitution Matrix: Ordered Likelihood\n");
        break;
      case 1:
        printBoth(infoFile, "Substitution Matrix: MK model\n");
        break;
      case 2:
        printBoth(infoFile, "Substitution Matrix: GTR\n");
        break;
      default:
        ((0) ? (void) (0) : __assert_fail ("0", "<stdin>", 5105, __PRETTY_FUNCTION__));
      }
    break;
  case 7:
    printBoth(infoFile, "DataType: Codon\n");
    break;
  default:
    ((0) ? (void) (0) : __assert_fail ("0", "<stdin>", 5112, __PRETTY_FUNCTION__));
  }
       printBoth(infoFile, "\n\n\n");
     }
 }

      printBoth(infoFile, "\n");

      printBoth(infoFile, "RAxML was called as follows:\n\n");
      for(i = 0; i < argc; i++)
 printBoth(infoFile,"%s ", argv[i]);
      printBoth(infoFile,"\n\n\n");

      fclose(infoFile);
    }
}

void printResult(tree *tr, analdef *adef, boolean finalPrint)
{
  FILE *logFile;
  char temporaryFileName[1024] = "", treeID[64] = "";

  strcpy(temporaryFileName, resultFileName);

  switch(adef->mode)
    {
    case 23:
    case 21:
      break;
    case 0:


      Tree2String(tr->tree_string, tr, tr->start->back, 1, 1, 0, 0, finalPrint, adef, -2, 0, 0);

      logFile = myfopen(temporaryFileName, "wb");
      fprintf(logFile, "%s", tr->tree_string);
      fclose(logFile);

      if(adef->perGeneBranchLengths)
 printTreePerGene(tr, adef, temporaryFileName, "wb");


      break;
    case 1:
      if(!adef->boot)
 {
   if(adef->multipleRuns > 1)
     {
       sprintf(treeID, "%d", tr->treeID);
       strcat(temporaryFileName, ".RUN.");
       strcat(temporaryFileName, treeID);
     }


   if(finalPrint)
     {
       switch(tr->rateHetModel)
  {
  case 1:
  case 2:
    Tree2String(tr->tree_string, tr, tr->start->back, 1, 1, 0, 0, finalPrint, adef,
         -2, 0, 0);

    logFile = myfopen(temporaryFileName, "wb");
    fprintf(logFile, "%s", tr->tree_string);
    fclose(logFile);

    if(adef->perGeneBranchLengths)
      printTreePerGene(tr, adef, temporaryFileName, "wb");
    break;
  case 0:
    Tree2String(tr->tree_string, tr, tr->start->back, 0, 1, 0, 0, finalPrint, adef,
         -1, 0, 0);

    logFile = myfopen(temporaryFileName, "wb");
    fprintf(logFile, "%s", tr->tree_string);
    fclose(logFile);

    break;
  default:
    ((0) ? (void) (0) : __assert_fail ("0", "<stdin>", 5192, __PRETTY_FUNCTION__));
  }
     }
   else
     {
       Tree2String(tr->tree_string, tr, tr->start->back, 0, 1, 0, 0, finalPrint, adef,
     -1, 0, 0);
       logFile = myfopen(temporaryFileName, "wb");
       fprintf(logFile, "%s", tr->tree_string);
       fclose(logFile);
     }
 }
      break;
    default:
      printf("FATAL ERROR call to printResult from undefined STATE %d\n", adef->mode);
      exit(-1);
      break;
    }
}

void printBootstrapResult(tree *tr, analdef *adef, boolean finalPrint)
{
  FILE
    *logFile;




  char
    *fileName = bootstrapFileName;


  if(adef->mode == 1 && (adef->boot || adef->rapidBoot))
    {
      if(adef->bootstrapBranchLengths)
 {
   Tree2String(tr->tree_string, tr, tr->start->back, 1, 1, 0, 0, finalPrint, adef, -2, 0, 0);

   logFile = myfopen(fileName, "ab");
   fprintf(logFile, "%s", tr->tree_string);
   fclose(logFile);

   if(adef->perGeneBranchLengths)
     printTreePerGene(tr, adef, fileName, "ab");
 }
      else
 {
   Tree2String(tr->tree_string, tr, tr->start->back, 0, 1, 0, 0, finalPrint, adef, -1, 0, 0);

   logFile = myfopen(fileName, "ab");
   fprintf(logFile, "%s", tr->tree_string);
   fclose(logFile);
 }
    }
  else
    {
      printf("FATAL ERROR in  printBootstrapResult\n");
      exit(-1);
    }
}



void printBipartitionResult(tree *tr, analdef *adef, boolean finalPrint)
{
  if(processID == 0 || adef->allInOne)
    {
      FILE *logFile;

      Tree2String(tr->tree_string, tr, tr->start->back, 0, 1, 0, 1, finalPrint, adef, -1, 0, 0);
      logFile = myfopen(bipartitionsFileName, "ab");
      fprintf(logFile, "%s", tr->tree_string);
      fclose(logFile);

      Tree2String(tr->tree_string, tr, tr->start->back, 0, 1, 0, 0, finalPrint, adef, -1, 1, 0);

      logFile = myfopen(bipartitionsFileNameBranchLabels, "ab");
      fprintf(logFile, "%s", tr->tree_string);
      fclose(logFile);

    }
}



void printLog(tree *tr, analdef *adef, boolean finalPrint)
{
  FILE *logFile;
  char temporaryFileName[1024] = "", checkPoints[1024] = "", treeID[64] = "";
  double lh, t;

  lh = tr->likelihood;
  t = gettime() - masterTime;

  strcpy(temporaryFileName, logFileName);
  strcpy(checkPoints, checkpointFileName);

  switch(adef->mode)
    {
    case 0:
      logFile = myfopen(temporaryFileName, "ab");

      printf("%f %f\n", t, lh);
      fprintf(logFile, "%f %f\n", t, lh);

      fclose(logFile);
      break;
    case 1:
      if(adef->boot || adef->rapidBoot)
 {


 }
      else
 {
   if(adef->multipleRuns > 1)
     {
       sprintf(treeID, "%d", tr->treeID);
       strcat(temporaryFileName, ".RUN.");
       strcat(temporaryFileName, treeID);

       strcat(checkPoints, ".RUN.");
       strcat(checkPoints, treeID);
     }


   if(!adef->checkpoints)
     {
       logFile = myfopen(temporaryFileName, "ab");

       fprintf(logFile, "%f %f\n", t, lh);

       fclose(logFile);
     }
   else
     {
       logFile = myfopen(temporaryFileName, "ab");

       fprintf(logFile, "%f %f %d\n", t, lh, tr->checkPointCounter);

       fclose(logFile);

       strcat(checkPoints, ".");

       sprintf(treeID, "%d", tr->checkPointCounter);
       strcat(checkPoints, treeID);

       Tree2String(tr->tree_string, tr, tr->start->back, 0, 1, 0, 0, finalPrint, adef, -1, 0, 0);

       logFile = myfopen(checkPoints, "ab");
       fprintf(logFile, "%s", tr->tree_string);
       fclose(logFile);

       tr->checkPointCounter++;
     }
 }
      break;
    case 21:
      break;
    default:
      ((0) ? (void) (0) : __assert_fail ("0", "<stdin>", 5352, __PRETTY_FUNCTION__));
    }
}



void printStartingTree(tree *tr, analdef *adef, boolean finalPrint)
{
  if(adef->boot)
    {

    }
  else
    {
      FILE *treeFile;
      char temporaryFileName[1024] = "", treeID[64] = "";

      Tree2String(tr->tree_string, tr, tr->start->back, 0, 1, 0, 0, finalPrint, adef, -1, 0, 0);

      if(adef->randomStartingTree)
 strcpy(temporaryFileName, randomFileName);
      else
 strcpy(temporaryFileName, permFileName);

      if(adef->multipleRuns > 1)
 {
   sprintf(treeID, "%d", tr->treeID);
   strcat(temporaryFileName, ".RUN.");
   strcat(temporaryFileName, treeID);
 }

      treeFile = myfopen(temporaryFileName, "ab");
      fprintf(treeFile, "%s", tr->tree_string);
      fclose(treeFile);
    }
}

void writeInfoFile(analdef *adef, tree *tr, double t)
{

    {
      switch(adef->mode)
 {
 case 23:
   break;
 case 0:
   break;
 case 1:
   if(adef->boot || adef->rapidBoot)
     {
       if(!adef->initialSet)
  printBothOpen("Bootstrap[%d]: Time %f seconds, bootstrap likelihood %f, best rearrangement setting %d\n", tr->treeID, t, tr->likelihood, adef->bestTrav);
       else
  printBothOpen("Bootstrap[%d]: Time %f seconds, bootstrap likelihood %f\n", tr->treeID, t, tr->likelihood);
     }
   else
     {
       int model;
       char modelType[128];

       switch(tr->rateHetModel)
  {
  case 2:
    strcpy(modelType, "GAMMA+P-Invar");
    break;
  case 1:
    strcpy(modelType, "GAMMA");
    break;
  case 0:
    strcpy(modelType, "CAT");
    break;
  default:
    ((0) ? (void) (0) : __assert_fail ("0", "<stdin>", 5424, __PRETTY_FUNCTION__));
  }

       if(!adef->initialSet)
  printBothOpen("Inference[%d]: Time %f %s-based likelihood %f, best rearrangement setting %d\n",
         tr->treeID, t, modelType, tr->likelihood, adef->bestTrav);
       else
  printBothOpen("Inference[%d]: Time %f %s-based likelihood %f\n",
         tr->treeID, t, modelType, tr->likelihood);

       {
  FILE *infoFile = myfopen(infoFileName, "ab");

  for(model = 0; model < tr->NumberOfModels; model++)
    {
      fprintf(infoFile, "alpha[%d]: %f ", model, tr->partitionData[model].alpha);
      if(adef->useInvariant)
        fprintf(infoFile, "invar[%d]: %f ", model, tr->partitionData[model].propInvariant);

      if(tr->partitionData[model].dataType == 1)
        {
   int
     k,
     states = tr->partitionData[model].states,
     rates = ((states * states - states) / 2);

   fprintf(infoFile, "rates[%d] ac ag at cg ct gt: ", model);
   for(k = 0; k < rates; k++)
     fprintf(infoFile, "%f ", tr->partitionData[model].substRates[k]);
        }

    }

  fprintf(infoFile, "\n");
  fclose(infoFile);
       }
     }
   break;
 default:
   ((0) ? (void) (0) : __assert_fail ("0", "<stdin>", 5463, __PRETTY_FUNCTION__));
 }
    }
}

static void printFreqs(int n, double *f, char **names)
{
  int k;

  for(k = 0; k < n; k++)
    printBothOpen("freq pi(%s): %f\n", names[k], f[k]);
}

static void printRatesDNA_BIN(int n, double *r, char **names)
{
  int i, j, c;

  for(i = 0, c = 0; i < n; i++)
    {
      for(j = i + 1; j < n; j++)
 {
   if(i == n - 2 && j == n - 1)
     printBothOpen("rate %s <-> %s: %f\n", names[i], names[j], 1.0);
   else
     printBothOpen("rate %s <-> %s: %f\n", names[i], names[j], r[c]);
   c++;
 }
    }
}

static void printRatesRest(int n, double *r, char **names)
{
  int i, j, c;

  for(i = 0, c = 0; i < n; i++)
    {
      for(j = i + 1; j < n; j++)
 {
   printBothOpen("rate %s <-> %s: %f\n", names[i], names[j], r[c]);
   c++;
 }
    }
}


void getDataTypeString(tree *tr, int model, char typeOfData[1024])
{
  switch(tr->partitionData[model].dataType)
    {
    case 2:
      strcpy(typeOfData,"AA");
      break;
    case 1:
      strcpy(typeOfData,"DNA");
      break;
    case 0:
      strcpy(typeOfData,"BINARY/MORPHOLOGICAL");
      break;
    case 3:
      strcpy(typeOfData,"SECONDARY 16 STATE MODEL USING ");
      strcat(typeOfData, secondaryModelList[tr->secondaryStructureModel]);
      break;
    case 4:
      strcpy(typeOfData,"SECONDARY 6 STATE MODEL USING ");
      strcat(typeOfData, secondaryModelList[tr->secondaryStructureModel]);
      break;
    case 5:
      strcpy(typeOfData,"SECONDARY 7 STATE MODEL USING ");
      strcat(typeOfData, secondaryModelList[tr->secondaryStructureModel]);
      break;
    case 6:
      strcpy(typeOfData,"Multi-State");
      break;
    case 7:
      strcpy(typeOfData,"Codon");
      break;
    default:
      ((0) ? (void) (0) : __assert_fail ("0", "<stdin>", 5540, __PRETTY_FUNCTION__));
    }
}



void printModelParams(tree *tr, analdef *adef)
{
  int
    model;

  double
    *f = (double*)((void *)0),
    *r = (double*)((void *)0);

  for(model = 0; model < tr->NumberOfModels; model++)
    {
      double tl;
      char typeOfData[1024];

      getDataTypeString(tr, model, typeOfData);

      printBothOpen("Model Parameters of Partition %d, Name: %s, Type of Data: %s\n",
      model, tr->partitionData[model].partitionName, typeOfData);
      printBothOpen("alpha: %f\n", tr->partitionData[model].alpha);

      if(adef->useInvariant)
 printBothOpen("invar: %f\n", tr->partitionData[model].propInvariant);

      if(adef->perGeneBranchLengths)
 tl = treeLength(tr, model);
      else
 tl = treeLength(tr, 0);

      printBothOpen("Tree-Length: %f\n", tl);

      f = tr->partitionData[model].frequencies;
      r = tr->partitionData[model].substRates;

      switch(tr->partitionData[model].dataType)
 {
 case 2:
   {
     char *freqNames[20] = {"A", "R", "N ","D", "C", "Q", "E", "G",
       "H", "I", "L", "K", "M", "F", "P", "S",
       "T", "W", "Y", "V"};

     printRatesRest(20, r, freqNames);
     printBothOpen("\n");
     printFreqs(20, f, freqNames);
   }
   break;
 case 6:
   {
     char *freqNames[32] = {"0", "1", "2", "3", "4", "5", "6", "7",
       "8", "9", "A", "B", "C", "D", "E", "F",
       "G", "H", "I", "J", "K", "L", "M", "N",
       "O", "P", "Q", "R", "S", "T", "U", "V"};

     printRatesRest(32, r, freqNames);
     printBothOpen("\n");
     printFreqs(32, f, freqNames);
   }
   break;
 case 7:
   ((0) ? (void) (0) : __assert_fail ("0", "<stdin>", 5605, __PRETTY_FUNCTION__));
   break;
 case 1:
   {
     char *freqNames[4] = {"A", "C", "G", "T"};

     printRatesDNA_BIN(4, r, freqNames);
     printBothOpen("\n");
     printFreqs(4, f, freqNames);
   }
   break;
 case 4:
    {
     char *freqNames[6] = {"AU", "CG", "GC", "GU", "UA", "UG"};

     printRatesRest(6, r, freqNames);
     printBothOpen("\n");
     printFreqs(6, f, freqNames);
   }
   break;
 case 5:
   {
     char *freqNames[7] = {"AU", "CG", "GC", "GU", "UA", "UG", "REST"};

     printRatesRest(7, r, freqNames);
     printBothOpen("\n");
     printFreqs(7, f, freqNames);
   }
   break;
 case 3:
   {
     char *freqNames[16] = {"AA", "AC", "AG", "AU", "CA", "CC", "CG", "CU",
       "GA", "GC", "GG", "GU", "UA", "UC", "UG", "UU"};

     printRatesRest(16, r, freqNames);
     printBothOpen("\n");
     printFreqs(16, f, freqNames);
   }
   break;
 case 0:
   {
     char *freqNames[2] = {"0", "1"};

     printRatesDNA_BIN(2, r, freqNames);
     printBothOpen("\n");
     printFreqs(2, f, freqNames);
   }
   break;
 default:
   ((0) ? (void) (0) : __assert_fail ("0", "<stdin>", 5654, __PRETTY_FUNCTION__));
 }

      printBothOpen("\n");
    }
}

static void finalizeInfoFile(tree *tr, analdef *adef)
{
  if(processID == 0)
    {
      double t;

      t = gettime() - masterTime;

      switch(adef->mode)
 {
 case 23:
   break;
 case 0 :
   printBothOpen("\n\nOverall Time for Tree Evaluation %f\n", t);
   printBothOpen("Final GAMMA  likelihood: %f\n", tr->likelihood);

   {
     int
       params,
       paramsBrLen;

     if(tr->NumberOfModels == 1)
       {
  if(adef->useInvariant)
    {
      params = 1 + 5 + 3 + 1 ;
      paramsBrLen = 1 + 5 + 3 + 1 +
        (2 * tr->mxtips - 3);
    }
  else
    {
      params = 5 + 3 + 1 ;
      paramsBrLen = 5 + 3 + 1 +
        (2 * tr->mxtips - 3);
    }
       }
     else
       {
  if(tr->multiBranch)
    {
      if(adef->useInvariant)
        {
   params = tr->NumberOfModels * (1 + 5 + 3 + 1 );
   paramsBrLen = tr->NumberOfModels * (1 + 5 + 3 + 1 +
           (2 * tr->mxtips - 3));
        }
      else
        {
   params = tr->NumberOfModels * (5 + 3 + 1 );
   paramsBrLen = tr->NumberOfModels * (5 + 3 + 1 +
           (2 * tr->mxtips - 3));
        }
    }
  else
    {
      if(adef->useInvariant)
        {
   params = tr->NumberOfModels * (1 + 5 + 3 + 1 );
   paramsBrLen = tr->NumberOfModels * (1 + 5 + 3 + 1 )
     + (2 * tr->mxtips - 3);
        }
      else
        {
   params = tr->NumberOfModels * (5 + 3 + 1 );
   paramsBrLen = tr->NumberOfModels * (5 + 3 + 1 )
     + (2 * tr->mxtips - 3);
        }

    }
       }

     if(tr->partitionData[0].dataType == 1)
       {
  printBothOpen("Number of free parameters for AIC-TEST(BR-LEN): %d\n", paramsBrLen);
  printBothOpen("Number of free parameters for AIC-TEST(NO-BR-LEN): %d\n", params);
       }

   }

   printBothOpen("\n\n");

   printModelParams(tr, adef);

   printBothOpen("Final tree written to:                 %s\n", resultFileName);
   printBothOpen("Execution Log File written to:         %s\n", logFileName);


   break;
 case 1:
   if(adef->boot)
     {
       printBothOpen("\n\nOverall Time for %d Bootstraps %f\n", adef->multipleRuns, t);
       printBothOpen("\n\nAverage Time per Bootstrap %f\n", (double)(t/((double)adef->multipleRuns)));
       printBothOpen("All %d bootstrapped trees written to: %s\n", adef->multipleRuns, bootstrapFileName);
     }
   else
     {
       if(adef->multipleRuns > 1)
  {
    double avgLH = 0;
    double bestLH = -1.0E300;
    int i, bestI = 0;

    for(i = 0; i < adef->multipleRuns; i++)
      {
        avgLH += tr->likelihoods[i];
        if(tr->likelihoods[i] > bestLH)
   {
     bestLH = tr->likelihoods[i];
     bestI = i;
   }
      }
    avgLH /= ((double)adef->multipleRuns);

    printBothOpen("\n\nOverall Time for %d Inferences %f\n", adef->multipleRuns, t);
    printBothOpen("Average Time per Inference %f\n", (double)(t/((double)adef->multipleRuns)));
    printBothOpen("Average Likelihood   : %f\n", avgLH);
    printBothOpen("\n");
    printBothOpen("Best Likelihood in run number %d: likelihood %f\n\n", bestI, bestLH);

    if(adef->checkpoints)
      printBothOpen("Checkpoints written to:                 %s.RUN.%d.* to %d.*\n", checkpointFileName, 0, adef->multipleRuns - 1);
    if(!adef->restart)
      {
        if(adef->randomStartingTree)
   printBothOpen("Random starting trees written to:       %s.RUN.%d to %d\n", randomFileName, 0, adef->multipleRuns - 1);
        else
   printBothOpen("Parsimony starting trees written to:    %s.RUN.%d to %d\n", permFileName, 0, adef->multipleRuns - 1);
      }
    printBothOpen("Final trees written to:                 %s.RUN.%d to %d\n", resultFileName, 0, adef->multipleRuns - 1);
    printBothOpen("Execution Log Files written to:         %s.RUN.%d to %d\n", logFileName, 0, adef->multipleRuns - 1);
    printBothOpen("Execution information file written to:  %s\n", infoFileName);
  }
       else
  {
    printBothOpen("\n\nOverall Time for 1 Inference %f\n", t);
    printBothOpen("Likelihood   : %f\n", tr->likelihood);
    printBothOpen("\n\n");

    if(adef->checkpoints)
    printBothOpen("Checkpoints written to:                %s.*\n", checkpointFileName);
    if(!adef->restart)
      {
        if(adef->randomStartingTree)
   printBothOpen("Random starting tree written to:       %s\n", randomFileName);
        else
   printBothOpen("Parsimony starting tree written to:    %s\n", permFileName);
      }
    printBothOpen("Final tree written to:                 %s\n", resultFileName);
    printBothOpen("Execution Log File written to:         %s\n", logFileName);
    printBothOpen("Execution information file written to: %s\n",infoFileName);
  }
     }

   break;
 case 3:
   printBothOpen("\n\nTime for Computation of Bipartitions %f\n", t);
   printBothOpen("Tree with bipartitions written to file:  %s\n", bipartitionsFileName);
   printBothOpen("Tree with bipartitions as branch labels written to file:  %s\n", bipartitionsFileNameBranchLabels);
   printBothOpen("Execution information file written to :  %s\n",infoFileName);
   break;
 case 6:
   printBothOpen("\n\nTime for Optimization of per-site log likelihoods %f\n", t);
   printBothOpen("Per-site Log Likelihoods written to File %s in Tree-Puzzle format\n", perSiteLLsFileName);
   printBothOpen("Execution information file written to :  %s\n",infoFileName);

   break;
 case 7:
   printBothOpen("\n\nTime for MP stepwise addition %f\n", t);
   printBothOpen("Execution information file written to :  %s\n",infoFileName);
   printBothOpen("Complete parsimony tree written to:      %s\n", permFileName);
   break;
 case 30:
   printBothOpen("\n\nTime for marginal ancestral state computation: %f\n\n", t);
   break;
 default:
   ((0) ? (void) (0) : __assert_fail ("0", "<stdin>", 5837, __PRETTY_FUNCTION__));
 }
    }

}
# 7153 "<stdin>"
static int elwCompare(const void *p1, const void *p2)
{
  elw *rc1 = (elw *)p1;
  elw *rc2 = (elw *)p2;

  double i = rc1->weight;
  double j = rc2->weight;

  if (i > j)
    return (-1);
  if (i < j)
    return (1);
  return (0);
}

static int elwCompareLikelihood(const void *p1, const void *p2)
{
  elw *rc1 = (elw *)p1;
  elw *rc2 = (elw *)p2;

  double i = rc1->lh;
  double j = rc2->lh;

  if (i > j)
    return (-1);
  if (i < j)
    return (1);
  return (0);
}

static void computeLHTest(tree *tr, analdef *adef, char *bootStrapFileName)
{
  int
    i;

  double
    bestLH,
    currentLH,
    weightSum = 0.0;

  FILE
    *treeFile = getNumberOfTrees(tr, bootStrapFileName, adef);

  double
    *bestVector = (double*)malloc(sizeof(double) * tr->cdta->endsite);

  for(i = 0; i < tr->cdta->endsite; i++)
    weightSum += (double)(tr->cdta->aliaswgt[i]);

  modOpt(tr, adef, 1, adef->likelihoodEpsilon, 1);
  printBothOpen("Model optimization, best Tree: %f\n", tr->likelihood);
  bestLH = tr->likelihood;

  evaluateGenericVector(tr, tr->start);
  memcpy(bestVector, tr->perSiteLL, tr->cdta->endsite * sizeof(double));

  for(i = 0; i < tr->numberOfTrees; i++)
    {
      int
 j;

      double
 temp,
 wtemp,
 sum = 0.0,
 sum2 = 0.0,
 sd;

      treeReadLen(treeFile, tr, 0, 0, 0, adef, 1);

      treeEvaluate(tr, 2);
      tr->start = tr->nodep[1];

      currentLH = tr->likelihood;

      if(currentLH > bestLH)
 printBothOpen("Better tree found %d at %f\n", i, currentLH);

      evaluateGenericVector(tr, tr->start);

      sum = 0.0;
      sum2 = 0.0;

      for (j = 0; j < tr->cdta->endsite; j++)
 {
   temp = bestVector[j] - tr->perSiteLL[j];
   wtemp = tr->cdta->aliaswgt[j] * temp;
   sum += wtemp;
   sum2 += wtemp * temp;
 }

      sd = sqrt( weightSum * (sum2 - sum*sum / weightSum) / (weightSum - 1) );


      printBothOpen("Tree: %d Likelihood: %f D(LH): %f SD: %f Significantly Worse: %s (5%s), %s (2%s), %s (1%s)\n",
      i, currentLH, currentLH - bestLH, sd,
      (sum > 1.95996 * sd) ? "Yes" : " No", "%",
      (sum > 2.326 * sd) ? "Yes" : " No", "%",
      (sum > 2.57583 * sd) ? "Yes" : " No", "%");
    }


  free(bestVector);
  fclose(treeFile);
  exit(0);
}

static void computePerSiteLLs(tree *tr, analdef *adef, char *bootStrapFileName)
{
  int
    i;

  FILE
    *treeFile = getNumberOfTrees(tr, bootStrapFileName, adef),
    *tlf = myfopen(perSiteLLsFileName, "wb");

  double
    *unsortedSites = (double*)malloc(sizeof(double) * tr->rdta->sites);



  fprintf(tlf, "  %d  %d\n", tr->numberOfTrees, tr->rdta->sites);

  for(i = 0; i < tr->numberOfTrees; i++)
    {
      int
 k,
 j;

      treeReadLen(treeFile, tr, 0, 0, 0, adef, 1);
      ((tr->ntips == tr->mxtips) ? (void) (0) : __assert_fail ("tr->ntips == tr->mxtips", "<stdin>", 7283, __PRETTY_FUNCTION__));

      if(i == 0)
 modOpt(tr, adef, 1, adef->likelihoodEpsilon, 1);
      else
 treeEvaluate(tr, 2);

      tr->start = tr->nodep[1];

      evaluateGenericVector(tr, tr->start);

      printBothOpen("Tree %d: %f\n", i, tr->likelihood);

      fprintf(tlf, "tr%d\t", i + 1);

      for(j = 0; j < tr->cdta->endsite; j++)
 {
   for(k = 0; k < tr->rdta->sites; k++)
     if(j == tr->patternPosition[k])
       unsortedSites[tr->columnPosition[k] - 1] = tr->perSiteLL[j];
 }

      for(j = 0; j < tr->rdta->sites; j++)
 fprintf(tlf, "%f ", unsortedSites[j]);

      fprintf(tlf, "\n");
    }

  fclose(treeFile);

  free(unsortedSites);
  fclose(tlf);
}


static double cumulativeTreeLength(tree *tr, analdef *adef)
{
  double tl = 0.0;

  if(adef->perGeneBranchLengths)
    {
      int
 accWgt = 0,
 model;

      double
 accLength = 0.0;

      for(model = 0; model < tr->NumberOfModels; model++)
 {
   int
     wgt = 0,
     i,
     lower,
     upper;

   double
     tlm;

   tlm = treeLength(tr, model);

   lower = tr->partitionData[model].lower;
   upper = tr->partitionData[model].upper;

   for(i = lower; i < upper; i++)
     wgt += tr->cdta->aliaswgt[i];

   accLength += ((double)wgt) * tlm;
   accWgt += wgt;
 }

      tl = accLength / ((double)accWgt);

    }
  else
    tl = treeLength(tr, 0);


  return tl;
}

static void computeAllLHs(tree *tr, analdef *adef, char *bootStrapFileName)
{
  int
    i;

  double
    bestLH = -1.0E300;

  bestlist
    *bestT;

  FILE
    *treeFile = getNumberOfTrees(tr, bootStrapFileName, adef),
    *result = myfopen(resultFileName, "wb");

  elw
    *list;

  INFILE = getNumberOfTrees(tr, bootStrapFileName, adef);

  bestT = (bestlist *) malloc(sizeof(bestlist));
  bestT->ninit = 0;
  initBestTree(bestT, 1, tr->mxtips);

  list = (elw *)malloc(sizeof(elw) * tr->numberOfTrees);

  for(i = 0; i < tr->numberOfTrees; i++)
    {
      treeReadLen(treeFile, tr, 0, 0, 0, adef, 1);
      resetBranches(tr);

      if(i == 0)
 {
   testGapped(tr);

   if(adef->useBinaryModelFile)
     {
       readBinaryModel(tr);
       evaluateGenericInitrav(tr, tr->start);
       treeEvaluate(tr, 2);
     }
   else
     modOpt(tr, adef, 1, adef->likelihoodEpsilon, 0);

   printBothOpen("Model optimization on first Tree: %f\n", tr->likelihood);
 }
      else
       {
   evaluateGenericInitrav(tr, tr->start);






   treeEvaluate(tr, 2);
 }

      list[i].tree = i;
      list[i].lh = tr->likelihood;

      Tree2String(tr->tree_string, tr, tr->start->back, 1, 1, 0, 0,
    1, adef, -2, 0, 0);

      fprintf(result, "%s", tr->tree_string);

      saveBestTree(bestT, tr);

      if(tr->likelihood > bestLH)
 bestLH = tr->likelihood;

      printBothOpen("Tree %d Likelihood %f Tree-Length %f\n", i, tr->likelihood, cumulativeTreeLength(tr, adef));
    }

  qsort(list, tr->numberOfTrees, sizeof(elw), elwCompareLikelihood);

  printBothOpen("\n");
  for(i = 0; i < tr->numberOfTrees; i++)
    printBothOpen("%d %f\n", list[i].tree, list[i].lh);

  printBothOpen("\n");
# 7457 "<stdin>"
  printBothOpen("\nAll evaluated trees with branch lengths written to File: %s\n", resultFileName);
  printBothOpen("\nTotal execution time: %f\n", gettime() - masterTime);


  fclose(result);
  exit(0);
}




static void computeELW(tree *tr, analdef *adef, char *bootStrapFileName)
{
  FILE
    *treeFile = getNumberOfTrees(tr, bootStrapFileName, adef);

  int
    position = 0,
    bestIndex = -1,
    i,
    k,
    *originalRateCategories = (int*)malloc(tr->cdta->endsite * sizeof(int)),
    *originalInvariant = (int*)malloc(tr->cdta->endsite * sizeof(int)),
    *countBest;

  long
    startSeed;

  double
    best = -1.0E300,
    **lhs,
    **lhweights,
    sum = 0.0;

  elw
    *bootweights,
    **rankTest;

  initModel(tr, tr->rdta, tr->cdta, adef);

  if(tr->numberOfTrees < 2)
    {
      printBothOpen("Error, there is only one tree in file %s which you want to use to conduct an ELW test\n", bootStrapFileName);

      exit(-1);
    }

  bootweights = (elw *)malloc(sizeof(elw) * tr->numberOfTrees);

  rankTest = (elw **)malloc(sizeof(elw *) * adef->multipleRuns);

  for(k = 0; k < adef->multipleRuns; k++)
    rankTest[k] = (elw *)malloc(sizeof(elw) * tr->numberOfTrees);

  lhs = (double **)malloc(sizeof(double *) * tr->numberOfTrees);

  for(k = 0; k < tr->numberOfTrees; k++)
    lhs[k] = (double *)calloc(adef->multipleRuns, sizeof(double));


  lhweights = (double **)malloc(sizeof(double *) * tr->numberOfTrees);

  for(k = 0; k < tr->numberOfTrees; k++)
    lhweights[k] = (double *)calloc(adef->multipleRuns, sizeof(double));

  countBest = (int*)calloc(adef->multipleRuns, sizeof(int));



  treeReadLen(treeFile, tr, 0, 0, 0, adef, 1);

  modOpt(tr, adef, 1, adef->likelihoodEpsilon, 1);
  rewind(treeFile);

  printBothOpen("Model optimization, first Tree: %f\n", tr->likelihood);

  memcpy(originalRateCategories, tr->cdta->rateCategory, sizeof(int) * tr->cdta->endsite);
  memcpy(originalInvariant, tr->invariant, sizeof(int) * tr->cdta->endsite);

  ((adef->boot > 0) ? (void) (0) : __assert_fail ("adef->boot > 0", "<stdin>", 7536, __PRETTY_FUNCTION__));



  startSeed = adef->boot;
# 7550 "<stdin>"
  for(i = 0; i < tr->numberOfTrees; i++)
    {
      position = 0;



      treeReadLen(treeFile, tr, 0, 0, 0, adef, 1);
      treeEvaluate(tr, 2.0);
      printBothOpen("Original tree %d likelihood %f\n", i, tr->likelihood);

      if(tr->likelihood > best)
 {
   best = tr->likelihood;
   bestIndex = i;
 }


      resetBranches(tr);



      adef->rapidBoot = startSeed;

      for(k = 0; k < adef->multipleRuns; k++)
 {


   computeNextReplicate(tr, &adef->rapidBoot, originalRateCategories, originalInvariant, 1, 1);




   if(k == 0)
     treeEvaluate(tr, 2.0);
   else
     treeEvaluate(tr, 0.5);


   lhs[i][k] = tr->likelihood;

   rankTest[k][i].lh = tr->likelihood;
   rankTest[k][i].tree = i;
 }



      reductionCleanup(tr, originalRateCategories, originalInvariant);
    }

  ((bestIndex >= 0 && best != -1.0E300) ? (void) (0) : __assert_fail ("bestIndex >= 0 && best != -1.0E300", "<stdin>", 7599, __PRETTY_FUNCTION__));

  printBothOpen("Best-Scoring tree is tree %d with score %f\n", bestIndex, best);




  for(k = 0; k < adef->multipleRuns; k++)
    {


      for(i = 0, best = -1.0E300; i < tr->numberOfTrees; i++)
 if(lhs[i][k] > best)
   best = lhs[i][k];



      for(i = 0; i < tr->numberOfTrees; i++)
 lhweights[i][k] = exp(lhs[i][k] - best);



      for(i = 0, sum = 0.0; i < tr->numberOfTrees; i++)
 sum += lhweights[i][k];



      for(i = 0; i < tr->numberOfTrees; i++)
 lhweights[i][k] = lhweights[i][k] / sum;

    }



  for(i = 0; i < tr->numberOfTrees; i++)
    {



      for(k = 0, sum = 0.0; k < adef->multipleRuns; k++)
 sum += lhweights[i][k];



      bootweights[i].weight = sum / ((double)adef->multipleRuns);
      bootweights[i].tree = i;
    }



  qsort(bootweights, tr->numberOfTrees, sizeof(elw), elwCompare);

  printBothOpen("Tree\t Posterior Probability \t Cumulative posterior probability\n");



  for(i = 0, sum = 0.0; i < tr->numberOfTrees; i++)
    {
      sum += bootweights[i].weight;

      printBothOpen("%d\t\t %f \t\t %f\n", bootweights[i].tree, bootweights[i].weight, sum);
    }
# 7719 "<stdin>"
  printBothOpen("\nTotal execution time: %f\n\n", gettime() - masterTime);

  free(originalRateCategories);
  free(originalInvariant);
  fclose(treeFile);

  exit(0);
}



static void computeDistances(tree *tr, analdef *adef)
{
  int i, j, modelCounter;
  double z0[128];
  double result[128];
  double t;
  char distanceFileName[1024];

  FILE
    *out;

  strcpy(distanceFileName, workdir);
  strcat(distanceFileName, "RAxML_distances.");
  strcat(distanceFileName, run_id);

  out = myfopen(distanceFileName, "wb");

  modOpt(tr, adef, 1, adef->likelihoodEpsilon, 1);

  printBothOpen("\nLog Likelihood Score after parameter optimization: %f\n\n", tr->likelihood);
  printBothOpen("\nComputing pairwise ML-distances ...\n");

  for(modelCounter = 0; modelCounter < tr->NumberOfModels; modelCounter++)
    z0[modelCounter] = 0.9;

  t = gettime();

  for(i = 1; i <= tr->mxtips; i++)
    for(j = i + 1; j <= tr->mxtips; j++)
      {
 double z, x;

 makenewzGenericDistance(tr, 10, z0, result, i, j);

 if(tr->multiBranch)
   {
     int k;

     for(k = 0, x = 0.0; k < tr->numBranches; k++)
       {
  ((tr->partitionContributions[k] != -1.0) ? (void) (0) : __assert_fail ("tr->partitionContributions[k] != -1.0", "<stdin>", 7770, __PRETTY_FUNCTION__));
  ((tr->fracchanges[k] != -1.0) ? (void) (0) : __assert_fail ("tr->fracchanges[k] != -1.0", "<stdin>", 7771, __PRETTY_FUNCTION__));
  z = result[k];
  if (z < 1.0E-15)
    z = 1.0E-15;
  x += (-log(z) * tr->fracchanges[k]) * tr->partitionContributions[k];
       }
   }
 else
   {
     z = result[0];
     if (z < 1.0E-15)
       z = 1.0E-15;
     x = -log(z) * tr->fracchange;
   }


 fprintf(out, "%s %s \t %f\n", tr->nameList[i], tr->nameList[j], x);
      }

  fclose(out);

  t = gettime() - t;

  printBothOpen("\nTime for pair-wise ML distance computation of %d distances: %f seconds\n",
   (tr->mxtips * tr->mxtips - tr->mxtips) / 2, t);
  printBothOpen("\nDistances written to file: %s\n", distanceFileName);



  exit(0);
}



static void morphologicalCalibration(tree *tr, analdef *adef)
{
  int
    replicates = adef->multipleRuns,
    i,
    *significanceCounter = (int*)malloc(sizeof(int) * tr->cdta->endsite);

  double
    *reference = (double*)malloc(sizeof(double) * tr->cdta->endsite);

  char
    integerFileName[1024] = "";

  FILE
    *integerFile;

  if(replicates == 1)
    {
      printBothOpen("You did not specify the number of random trees to be generated by \"-#\" !\n");
      printBothOpen("Automatically setting it to 100.\n");
      replicates = 100;
    }

  printBothOpen("Likelihood on Reference tree: %f\n\n", tr->likelihood);

  evaluateGenericVector(tr, tr->start);

  for(i = 0; i < tr->cdta->endsite; i++)
    significanceCounter[i] = 0;

  memcpy(reference, tr->perSiteLL, tr->cdta->endsite * sizeof(double));

  for(i = 0; i < replicates; i++)
    {
      int k;

      printBothOpen("Testing Random Tree [%d]\n", i);
      makeRandomTree(tr, adef);
      evaluateGenericInitrav(tr, tr->start);
      treeEvaluate(tr, 2);






      evaluateGenericVector(tr, tr->start);


      for(k = 0; k < tr->cdta->endsite; k++)
 if(tr->perSiteLL[k] <= reference[k])
   significanceCounter[k] = significanceCounter[k] + 1;
    }

  strcpy(integerFileName, workdir);
  strcat(integerFileName, "RAxML_weights.");
  strcat(integerFileName, run_id);

  integerFile = myfopen(integerFileName, "wb");

  for(i = 0; i < tr->cdta->endsite; i++)
    fprintf(integerFile, "%d ", significanceCounter[i]);

  fclose(integerFile);

  printBothOpen("RAxML calibrated integer weight file written to: %s\n", integerFileName);

  exit(0);
}
# 7883 "<stdin>"
static void extractTaxaFromTopology(tree *tr, rawdata *rdta, cruncheddata *cdta)
{
  FILE *f = myfopen(bootStrapFile, "rb");

  char
    **nameList,
    buffer[256 + 2];

  int
    i = 0,
    c,
    taxaSize = 1024,
    taxaCount = 0;

  nameList = (char**)malloc(sizeof(char*) * taxaSize);

  while((c = fgetc(f)) != ';')
    {
      if(c == '(' || c == ',')
 {
   c = fgetc(f);
   if(c == '(' || c == ',')
     ungetc(c, f);
   else
     {
       i = 0;

       do
  {
    buffer[i++] = c;
    c = fgetc(f);
  }
       while(c != ':' && c != ')' && c != ',');
       buffer[i] = '\0';

       for(i = 0; i < taxaCount; i++)
  {
    if(strcmp(buffer, nameList[i]) == 0)
      {
        printf("A taxon labelled by %s appears twice in the first tree of tree collection %s, exiting ...\n", buffer, bootStrapFile);
        exit(-1);
      }
  }

       if(taxaCount == taxaSize)
  {
    taxaSize *= 2;
    nameList = (char **)realloc(nameList, sizeof(char*) * taxaSize);
  }

       nameList[taxaCount] = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
       strcpy(nameList[taxaCount], buffer);

       taxaCount++;

       ungetc(c, f);
     }
 }
    }

  printf("Found a total of %d taxa in first tree of tree collection %s\n", taxaCount, bootStrapFile);
  printf("Expecting all remaining trees in collection to have the same taxon set\n");

  rdta->numsp = taxaCount;

  tr->nameList = (char **)malloc(sizeof(char *) * (taxaCount + 1));
  for(i = 1; i <= taxaCount; i++)
    tr->nameList[i] = nameList[i - 1];

  free(nameList);

  tr->rdta = rdta;
  tr->cdta = cdta;

  if (rdta->numsp < 4)
    {
      printf("TOO FEW SPECIES, tree contains only %d species\n", rdta->numsp);
      ((0) ? (void) (0) : __assert_fail ("0", "<stdin>", 7960, __PRETTY_FUNCTION__));
    }

  tr->nameHash = initStringHashTable(10 * taxaCount);
  for(i = 1; i <= taxaCount; i++)
    addword(tr->nameList[i], tr->nameHash, i);

  fclose(f);
}


static void myfwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
  size_t
    bytes_written = fwrite(ptr, size, nmemb, stream);

  ((bytes_written = nmemb) ? (void) (0) : __assert_fail ("bytes_written = nmemb", "<stdin>", 7976, __PRETTY_FUNCTION__));
}


void writeBinaryModel(tree *tr)
{
  int
    model;

  FILE
    *f = myfopen(binaryModelParamsOutputFileName, "w");



  myfwrite(tr->cdta->rateCategory, sizeof(int), tr->rdta->sites + 1, f);
  myfwrite(tr->cdta->patrat, sizeof(double), tr->rdta->sites + 1, f);
  myfwrite(tr->cdta->patratStored, sizeof(double), tr->rdta->sites + 1, f);




  for(model = 0; model < tr->NumberOfModels; model++)
    {
      int
 dataType = tr->partitionData[model].dataType;

      myfwrite(tr->partitionData[model].gammaRates, sizeof(double), 4, f);
      myfwrite(tr->partitionData[model].EIGN, sizeof(double), pLengths[dataType].eignLength, f);
      myfwrite(tr->partitionData[model].EV, sizeof(double), pLengths[dataType].evLength, f);
      myfwrite(tr->partitionData[model].EI, sizeof(double), pLengths[dataType].eiLength, f);

      myfwrite(tr->partitionData[model].frequencies, sizeof(double), pLengths[dataType].frequenciesLength, f);
      myfwrite(tr->partitionData[model].tipVector, sizeof(double), pLengths[dataType].tipVectorLength, f);
      myfwrite(tr->partitionData[model].substRates, sizeof(double), pLengths[dataType].substRatesLength, f);

      myfwrite(&(tr->partitionData[model].alpha), sizeof(double), 1, f);
      myfwrite(&(tr->partitionData[model].propInvariant), sizeof(double), 1, f);
    }

  printBothOpen("\nModel parameters (binary file format) written to: %s\n", binaryModelParamsOutputFileName);

  fclose(f);
}

static void myfread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
  size_t
    bytes_read;

  bytes_read = fread(ptr, size, nmemb, stream);

  ((bytes_read == nmemb) ? (void) (0) : __assert_fail ("bytes_read == nmemb", "<stdin>", 8027, __PRETTY_FUNCTION__));
}

void readBinaryModel(tree *tr)
{
  int
    model;

  FILE
    *f = fopen(binaryModelParamsInputFileName, "r");



  myfread(tr->cdta->rateCategory, sizeof(int), (size_t)(tr->rdta->sites + 1), f);
  myfread(tr->cdta->patrat, sizeof(double), (size_t)(tr->rdta->sites + 1), f);
  myfread(tr->cdta->patratStored, sizeof(double), (size_t)(tr->rdta->sites + 1), f);




  for(model = 0; model < tr->NumberOfModels; model++)
    {
      int
 dataType = tr->partitionData[model].dataType;

      myfread(tr->partitionData[model].gammaRates, sizeof(double), 4, f);

      myfread(tr->partitionData[model].EIGN, sizeof(double), (size_t)(pLengths[dataType].eignLength), f);
      myfread(tr->partitionData[model].EV, sizeof(double), (size_t)(pLengths[dataType].evLength), f);
      myfread(tr->partitionData[model].EI, sizeof(double), (size_t)(pLengths[dataType].eiLength), f);

      myfread(tr->partitionData[model].frequencies, sizeof(double), (size_t)(pLengths[dataType].frequenciesLength), f);
      myfread(tr->partitionData[model].tipVector, sizeof(double), (size_t)(pLengths[dataType].tipVectorLength), f);
      myfread(tr->partitionData[model].substRates, sizeof(double), (size_t)(pLengths[dataType].substRatesLength), f);

      myfread(&(tr->partitionData[model].alpha), sizeof(double), 1, f);
      myfread(&(tr->partitionData[model].propInvariant), sizeof(double), 1, f);
    }






  fclose(f);
}


void testGapped(tree *tr)
{
  if((!tr->saveMemory) && (!tr->estimatePerSiteAA) && tr->rateHetModel == 1 && tr->useGappedImplementation == 0)
    {
      int
 i;

      double
 gappedTime,
 ungappedTime;

      printBothOpen("Testing which likelihood implementation to use\n");

      tr->useGappedImplementation = 0;
      ungappedTime = gettime();
      for(i = 0; i < 8; i++)
 evaluateGenericInitrav(tr, tr->start);
      ungappedTime = gettime() - ungappedTime;

      tr->useGappedImplementation = 1;





      gappedTime = gettime();
      for(i = 0; i < 8; i++)
 evaluateGenericInitrav(tr, tr->start);
      gappedTime = gettime() - gappedTime;


      printBothOpen("Standard Implementation full tree traversal time: %f\n", ungappedTime);

      printBothOpen("Subtree Equality Vectors for gap columns full tree traversal time: %f\n", gappedTime);

      if((0.8 * ungappedTime) <= gappedTime)
 {
   tr->useGappedImplementation = 0;
   printBothOpen("... using standard implementation\n\n");
 }
      else
 {
   tr->useGappedImplementation = 1;
   printBothOpen("... using SEV-based implementation\n\n");
 }




    }
}

static int iterated_bitcount(unsigned int n)
{
    int
      count=0;

    while(n)
      {
        count += n & 0x1u ;
        n >>= 1 ;
      }

    return count;
}

static char bits_in_16bits [0x1u << 16];

static void compute_bits_in_16bits(void)
{
    unsigned int i;

    for (i = 0; i < (0x1u<<16); i++)
        bits_in_16bits[i] = iterated_bitcount(i);

    return ;
}

unsigned int precomputed16_bitcount (unsigned int n)
{


    return bits_in_16bits [n & 0xffffu]
        + bits_in_16bits [(n >> 16) & 0xffffu] ;
}




int main (int argc, char *argv[])
{
  rawdata *rdta;
  cruncheddata *cdta;
  tree *tr;
  analdef *adef;
  int
    i,
    countGTR = 0,
    countOtherModel = 0;
# 8185 "<stdin>"
  processID = 0;


  masterTime = gettime();
# 8202 "<stdin>"
   _mm_setcsr( _mm_getcsr() | _MM_FLUSH_ZERO_ON);



  adef = (analdef *)malloc(sizeof(analdef));
  rdta = (rawdata *)malloc(sizeof(rawdata));
  cdta = (cruncheddata *)malloc(sizeof(cruncheddata));
  tr = (tree *)malloc(sizeof(tree));



  compute_bits_in_16bits();

  initAdef(adef);
  get_args(argc,argv, adef, tr);

  if(adef->readTaxaOnly)
    extractTaxaFromTopology(tr, rdta, cdta);

  getinput(adef, rdta, cdta, tr);

  checkOutgroups(tr, adef);
  makeFileNames();





  if(adef->useInvariant && adef->likelihoodEpsilon > 0.001)
    {
      printBothOpen("\nYou are using a proportion of Invariable sites estimate, although I don't\n");
      printBothOpen("like it. The likelihood epsilon \"-f e\" will be automatically lowered to 0.001\n");
      printBothOpen("to avoid unfavorable effects caused by simultaneous optimization of alpha and P-Invar\n");

      adef->likelihoodEpsilon = 0.001;
    }







  if(adef->useSecondaryStructure)
    {
      tr->dataVector = tr->initialDataVector;
      tr->partitionData = tr->initialPartitionData;
      tr->NumberOfModels--;
    }

  if(adef->useExcludeFile)
    {
      handleExcludeFile(tr, adef, rdta);
      exit(0);
    }


  if(!adef->readTaxaOnly && adef->mode != 24 && adef->mode != 28)
    checkSequences(tr, rdta, adef);


  if(adef->mode == 4)
    {
      splitMultiGene(tr, rdta);
      exit(0);
    }

  if(adef->mode == 5)
    {
      printf("Alignment format can be read by RAxML \n");
      exit(0);
    }






  if(adef->useSecondaryStructure && !adef->readTaxaOnly)
    {
      tr->dataVector = tr->extendedDataVector;
      tr->partitionData = tr->extendedPartitionData;
      tr->NumberOfModels++;


    }

  if(!adef->readTaxaOnly)
    {
      makeweights(adef, rdta, cdta, tr);
      makevalues(rdta, cdta, tr, adef);

      for(i = 0; i < tr->NumberOfModels; i++)
 {
   if(tr->partitionData[i].dataType == 2)
     {
       if(tr->partitionData[i].protModels == 20 || tr->partitionData[i].protModels == 19)
  countGTR++;
       else
  countOtherModel++;
     }
 }

      if(countGTR > 0 && countOtherModel > 0)
 {
   printf("Error, it is only allowed to conduct partitioned AA analyses\n");
   printf("with a GTR model of AA substitution, if all AA partitions are assigned\n");
   printf("the GTR or GTR_UNLINKED model.\n\n");

   printf("The following partitions do not use GTR:\n");

   for(i = 0; i < tr->NumberOfModels; i++)
     {
       if(tr->partitionData[i].dataType == 2 && (tr->partitionData[i].protModels != 20 || tr->partitionData[i].protModels != 19))
  printf("Partition %s\n", tr->partitionData[i].partitionName);
     }
   printf("exiting ...\n");
   errorExit(-1);
 }

      if(countGTR > 0 && tr->NumberOfModels > 1)
 {
   FILE *info = myfopen(infoFileName, "ab");

   printBoth(info, "You are using the GTR model of AA substitution!\n");
   printBoth(info, "GTR parameters for AA substiution will automatically be estimated\n");
   printBoth(info, "either jointly (GTR params will be linked) or independently (when using GTR_UNLINKED) across all partitions.\n");
   printBoth(info, "WARNING: you may be over-parametrizing the model!\n\n\n");

   fclose(info);
 }
    }

  if(adef->mode == 9 || adef->mode == 29)
    tr->innerNodes = (size_t)(countTaxaInTopology() - 1);
  else
    tr->innerNodes = tr->mxtips;


  setRateHetAndDataIncrement(tr, adef);







  if(!adef->readTaxaOnly)
    allocNodex(tr);


  makeMissingData(tr);

  printModelAndProgramInfo(tr, adef, argc, argv);

  switch(adef->mode)
    {
    case 29:
      getStartingTree(tr, adef);
      ((0) ? (void) (0) : __assert_fail ("0", "<stdin>", 8361, __PRETTY_FUNCTION__));
      break;
    case 9:
      initModel(tr, rdta, cdta, adef);
      getStartingTree(tr, adef);
      exit(0);
      break;
    case 12:
      generateBS(tr, adef);
      exit(0);
      break;
    case 13:
      computeELW(tr, adef, bootStrapFile);
      exit(0);
      break;
    case 17:
      initModel(tr, rdta, cdta, adef);
      computeAllLHs(tr, adef, bootStrapFile);
      exit(0);
      break;
    case 18:
      compareBips(tr, bootStrapFile, adef);
      exit(0);
      break;
    case 20:
      computeRF(tr, bootStrapFile, adef);
      exit(0);
      break;
    case 14:
      computeBootStopOnly(tr, bootStrapFile, adef);
      exit(0);
      break;
    case 22:
      if(adef->leaveDropMode)
 computeRogueTaxa(tr, bootStrapFile, adef);
      else
 computeConsensusOnly(tr, bootStrapFile, adef);
      exit(0);
      break;
    case 11:
      initModel(tr, rdta, cdta, adef);
      getStartingTree(tr, adef);
      computeDistances(tr, adef);
      break;
    case 7:
      initModel(tr, rdta, cdta, adef);
      getStartingTree(tr, adef);
      printStartingTree(tr, adef, 1);
      break;
    case 6:
      initModel(tr, rdta, cdta, adef);
      computePerSiteLLs(tr, adef, bootStrapFile);
      break;
    case 0:
      initModel(tr, rdta, cdta, adef);

      getStartingTree(tr, adef);

      if(adef->likelihoodTest)
 computeLHTest(tr, adef, bootStrapFile);
      else
 {
   modOpt(tr, adef, 1, adef->likelihoodEpsilon, 1);
   writeBinaryModel(tr);
   printLog(tr, adef, 1);
   printResult(tr, adef, 1);
 }



      break;
    case 30:
      initModel(tr, rdta, cdta, adef);

      getStartingTree(tr, adef);
      modOpt(tr, adef, 1, adef->likelihoodEpsilon, 0);

      evaluateGenericInitrav(tr, tr->start);

      computeAncestralStates(tr, tr->likelihood, adef);
      break;
    case 3:
      calcBipartitions(tr, adef, tree_file, bootStrapFile);
      break;
    case 1:
      if(adef->boot)
 doBootstrap(tr, adef, rdta, cdta);
      else
 {
   if(adef->rapidBoot)
     {
       initModel(tr, rdta, cdta, adef);
       doAllInOne(tr, adef);
     }
   else
     doInference(tr, adef, rdta, cdta);
 }
      break;
    case 21:
      initModel(tr, rdta, cdta, adef);
      getStartingTree(tr, adef);
      modOpt(tr, adef, 1, adef->likelihoodEpsilon, 0);
      morphologicalCalibration(tr, adef);
      break;
    case 23:
      initModel(tr, rdta, cdta, adef);
      getStartingTree(tr, adef);
      meshTreeSearch(tr, adef, adef->meshSearch);

      break;
    case 24:
      fastSearch(tr, adef, rdta, cdta);
      exit(0);
    case 28:
      shSupports(tr, adef, rdta, cdta);
      break;
    case 27:
      initModel(tr, rdta, cdta, adef);
      getStartingTree(tr, adef);
      modOpt(tr, adef, 1, adef->likelihoodEpsilon, 0);
      computePlacementBias(tr, adef);
      break;
    default:
      ((0) ? (void) (0) : __assert_fail ("0", "<stdin>", 8484, __PRETTY_FUNCTION__));
    }

  finalizeInfoFile(tr, adef);





  return 0;
}
