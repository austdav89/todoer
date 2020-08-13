#define VERSION 0.1f

#define LINE_MAX 256
#define GROUP_MAX 64

typedef u_int8_t grp;

typedef struct Todo {
    bool    completed;
    char *  name;
    char *  note;
    grp     group;
    time_t  tstamp;
    time_t  cstamp;

}Todo;

// trivial welcome message
void welcomeMsg(void);

// main program loop
int todoerLoop(void);
