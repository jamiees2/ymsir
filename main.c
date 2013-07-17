#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>
#include "main.h"

int debug_mode = 1;


int main(int argc, char **argv)
{
	int i, port = 1337, foreground = 0;
	uid_t ruid = 65534;
	struct sockaddr_in clientaddr;

	while ( (i = getopt(argc, argv, "p:dfu:")) != EOF)
	{
		switch (i)
		{
			case 'p':
				port = atoi(optarg);
				break;
			case 'd':
				debug_mode = !debug_mode;
				break;
			case 'f':
				foreground = 1;
				break;
			case 'u':
				ruid = atoi(optarg);
				break;
			default:
				fprintf (stderr, "Unknown command, '%c'\n", i);
				exit (0);
		}
	}

	prepare_scrabble();

	debug_printf ("Scrabble dictionary prepared.\n");

	/* Open up a listening port */

	debug_printf ("Bound to port %d.\n", port);

	/* Go in the background? */
	// if (foreground == 0)
	// {
	// 	block_signals();
	// 	if (fork() != 0)
	// 	{
	// 		debug_printf ("Running in the background.\n");
	// 		exit (0);
	// 	}
		
	// }

	/* Silently reap children */
	signal (SIGCHLD, SIG_IGN);
	signal (SIGALRM, SIG_IGN);

	/* Listen for connections */

	
	srand (getpid() ^ time(NULL));

	service();
	return -1;	
}
