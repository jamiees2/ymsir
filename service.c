#include "main.h"


char **scrabble;
unsigned long fibonacci[] = { 0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578, 5702887, 9227465, 14930352, 24157817, 39088169, 63245986, 102334155, 165580141, 267914296, 433494437, 701408733UL, 1134903170UL, 1836311903UL, 2971215073UL };


void alarm_handler(int sign)
{
	printf ("ERR\tTimeout.\n");
	printf ("%d\n", sizeof(fibonacci));
	exit (0);
}


void prepare_scrabble(void)
{
	char buf[256];
	FILE *fp;
	int i;

	if ( (fp = fopen ("sowpods.txt", "r")) == NULL)
		failure ("Could not open sowpods.txt");

	scrabble = (char **)xmalloc (sizeof(char *) * (NUM_WORDS+1));
	memset (scrabble, 0, sizeof(char *) * (NUM_WORDS+1));

	for (i = 0; i < NUM_WORDS; i++)
	{
		if (fgets (buf, sizeof(buf), fp) == NULL)
			failure ("SOWPODS of the wrong size (i)");

		buf[strlen(buf)-1] = 0;
		scrabble[i] = (char *)xstrdup (buf);
	}
	if (i != NUM_WORDS)
		failure ("SOWPODS of the wrong size (ii)");

	fclose (fp);

	return;
}

void service_setup(int lfd, int connfd, int ruid)
{
	service();
}


void service(void)
{
	static char *answer;
	char buf[8];
	int i, tries = 3;

	/* Set up time outs and buffering */
	// setvbuf(stdout, NULL, _IONBF, 0);
	// signal (SIGALRM, alarm_handler);
	// Alarm (20);

	/* Authenticate */

	printf ("OK\tWelcome to the RU Hacking Contest QUIZ server. You seem to be far along...\n");
	printf ("OK\tPlease enter the access word.\n");

	while (tries--)
	{
		memset (buf, 0, sizeof(buf));
		//i = Rio_readn (0, buf, sizeof(buf));
		fgets (buf, sizeof(buf), stdin);

		/* Remove carriage return and newline */
		if (strchr (buf, '\n'))
			*(strchr (buf, '\n')) = 0;
		if (strchr (buf, '\r'))
			*(strchr (buf, '\r')) = 0;

		if (!strncasecmp (buf, "MELODY", 6))
		{
			printf ("OK\tCorrect. Now answer the following questions.\n");
			break;
		}
		if (tries > 0)
			printf ("ERR\tNo... try again.\n");
	}
		
	if (tries < 0)
	{
		printf ("ERR\tToo many invalid passwords\n");
		return;
	}

	/* Ask questions */

	tries = 3;
	while (tries--)
	{

		/* Pose either Fibonacci or Scrabble question */
		if ( (rand() % 2) == 0)
		{
			i = rand() % (NUM_WORDS - 1);
			printf ("Q\t%s ?\n", scrabble[i]);
			answer = xstrdup (scrabble[i+1]);
			//answer = xstrdup (scrabble[i]);
		} else {
			i = rand() % (NUM_FIB - 1);
			printf ("Q\t%lu ?\n", fibonacci[i]);
			sprintf (buf, "%lu", fibonacci[i+1]);
			answer = xstrdup (buf);
		}

		/* Read and compare answer */		
		fgets (buf, (tries == 2) ? NUM_WORDS : sizeof(buf), stdin);
		printf("tries:\t%d\n", tries);
		if (!strncasecmp (buf, answer, strlen(answer)))
		{
			printf ("OK\tCorrect!");
			if (tries > 0)
				printf ("\t%d more to go...\n", tries);
			else
				printf ("\n");
		} else {
			printf ("ERR\tSorry. The correct answer was \"%s\"\n", answer);
			return;
		}
		free (answer);
	}

	printf ("OK\tYou made it!! Exquisite work.\n");
	printf ("OK\tThe keyword is: ASSANGE\n");
	printf ("OK\tYou should probably look at http://www.ymsir.com/hacking/quiz.tgz\n");
	printf ("OK\tIf you haven't already, it might be good to read Aleph1's 'Smashing the stack for fun and profit'\n");
	printf ("OK\t(Keep in mind that all incoming _and_ outgoing ports except for 1337 and 22 are blocked on this server)\n");
}
