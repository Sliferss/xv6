struct stat;
struct rtcdate;
struct drawParam;

// system calls
int fork(void);
int exit(void) __attribute__((noreturn));
int wait(void);
int pipe(int*);
int write(int, const void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(char*, char**);
int open(const char*, int);
int mknod(const char*, short, short);
int unlink(const char*);
int fstat(int fd, struct stat*);
int link(const char*, const char*);
int mkdir(const char*);
int chdir(const char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
int getch(void);
int drawPixel(int, int, int);
int drawLine(int, int, int, int, int);
int setvideomode(int);
int executeGraphicsCall(struct drawParam *call, int count);
// TODO: Declare your user APIs for your system calls.

// ulib.c
int stat(const char*, struct stat*);
char* strcpy(char*, const char*);
void *memmove(void*, const void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void printf(int, const char*, ...);
char* gets(char*, int max);
uint strlen(const char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);

//graphicscall.c
void beginBatch();
void executeBatch();
void drawPixelBatched(int, int, int);
void drawLineBatched(int, int, int, int, int);
void fillRectBatched(int, int, int, int, int);
void drawCircleBatched(int, int, int, int);
void drawTriangleBatched(int, int, int, int);
void drawPentagonBatched(int, int, int, int);
void fillCircleBatched(int, int, int, int);
void fillPentagonBatched(int, int, int, int);
