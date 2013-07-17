#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "main.h"


void signal_handler(int sign)
{
   debug_printf ("signal_handler(): Received signal %d. Shutting down...\n", sign);

   exit(0);
}


void block_signals(void)
{
   debug_printf ("block_signals(): Blocking signals...\n");
   signal (SIGHUP,  signal_handler);
   signal (SIGINT,  signal_handler);
   signal (SIGTERM, signal_handler);
   signal (SIGQUIT, signal_handler);
   signal (SIGFPE,  signal_handler);
//   signal (SIGSEGV, signal_handler);
   signal (SIGSTOP, signal_handler);
   signal (SIGTSTP, signal_handler);
   signal (SIGILL,  signal_handler);
   signal (SIGPIPE, SIG_IGN);
   signal (SIGALRM, SIG_IGN);
   signal (SIGTTIN, SIG_IGN);
   signal (SIGTTOU, SIG_IGN);
   signal (SIGTRAP, SIG_IGN);
   signal (SIGIO,   SIG_IGN);
   signal (SIGBUS,  SIG_IGN);
   signal (SIGURG,  SIG_IGN);
   
   return;
}
