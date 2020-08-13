

#define VERSION 0.1f
#define GROUP_MAX 64

typedef u_int8_t grp;

typedef struct Todo {
    char * name;
    char * description;
    grp group;
    time_t tstamp;

}Todo;


void welcomeMsg(void);
