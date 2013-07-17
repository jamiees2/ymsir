#ifndef __MAIN_H_
#define __MAIN_H_

#include "csapp.h"

#define NUM_FIB			47
#define NUM_WORDS		267751


extern int debug_mode;



/* service.c */
extern void service_setup(int lfd, int connfd, int ruid);
extern void service(void);
extern void prepare_scrabble(void);

/* vital.c */
extern void failure(char *format, ...);
extern void debug_printf(char *format, ...);
extern void *xmalloc(unsigned int size);
extern char *xstrdup(char *string);

/* signal.c */
extern void block_signals(void);

#endif /* __MAIN_H_ */
