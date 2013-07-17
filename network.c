#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include "all.h"

#ifndef SHUT_RDWR
# define SHUT_RDWR 2
#endif

int listening_socket = 0;


void network_initialize(void)
{
   struct sockaddr_in tmpsin;
   int tmpsock = 0;
   int optval = 1;
   struct { int a, b; } ling = { 1, 5 };

   if ( (tmpsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
      failure ("network_initialize(): Unable to apply for a socket.");

   if ( (setsockopt(tmpsock, SOL_SOCKET, SO_REUSEADDR, (void *)&optval, sizeof(optval))) < 0)
      failure ("network_initialize(): Unable to perfom a SO_REUSEADDR setsockopt().");

   if ( (setsockopt(tmpsock, SOL_SOCKET, SO_LINGER, (void *)&ling, sizeof(ling))) < 0)
      failure ("network_initialize(): Unable to perfom a SO_LINGER setsockopt().");

   tmpsin.sin_family       = AF_INET;
   tmpsin.sin_addr.s_addr  = INADDR_ANY;
   tmpsin.sin_port         = htons(port);
   memset (&(tmpsin.sin_zero), '\0', sizeof(tmpsin.sin_zero));
   
   if ( (bind(tmpsock, (struct sockaddr *)&tmpsin, sizeof(tmpsin))) < 0)
      failure ("network_initialize(): Unable to bind to port %d.\n", port);
      
   if ( (listen(tmpsock, max_connections)) < 0)
      failure ("network_initialize(): Failed to listen().");
      
   listening_socket = tmpsock;

   debug_printf ("network_initialize(): Successfully bound to port %d and awaiting up to\n%d simultaneous connections.\n", port, max_connections);

   return;
}


void network_shutdown(void)
{
   CLIENT *cur_client;

   errno = 0;

   debug_printf ("network_shutdown(): Closing sockets...\n");

   if (listening_socket > 0)
   {
#ifdef DEBUG
      printf ("Shutting down listening socket %d: ", listening_socket);
      tmp = shutdown (listening_socket, SHUT_RDWR);
      debug_printf ("shutdown() = %d (%d); ", tmp, errno);
      debug_printf ("close(): %d\n", close (listening_socket));
#else
      shutdown (listening_socket, SHUT_RDWR);
      close (listening_socket);
#endif
   }

   for (cur_client = client_top.next; cur_client != NULL; cur_client = cur_client->next)  
   {
      if (cur_client->socket > 0)
      {
#ifdef DEBUG
         printf ("Shutting down socket %d: ", cur_client->socket);
         tmp = shutdown (cur_client->socket, SHUT_RDWR);
         printf ("shutdown() = %d (%d); ", tmp, errno);
         printf ("close(): %d\n", close (cur_client->socket));
#else
         shutdown (cur_client->socket, SHUT_RDWR);
         close (cur_client->socket);
#endif
      }
   }

   return;
}


struct in_addr *hostname_resolve(char *host)
{
   static struct in_addr in;
   struct hostent *he;
   
   if ( (inet_aton(host, &in)) == 0)
   {
      if ( (he = gethostbyname(host)) == NULL)
      {
         memset (&in, '\0', sizeof(struct in_addr));
         return (&in);
      }
      memcpy (&in, he->h_addr, he->h_length);
   }
   
   return (&in);
}


void transmit(CLIENT *client, char *format, ...)
{
   char buffer[SERVER_BUFFER_SIZE];
   va_list va;
   
   va_start (va, format);
   vsnprintf (buffer, sizeof(buffer)-1, format, va);
   va_end (va);
   
   if (client == NULL)
      return;
      
   if (client->socket <= 0)
   {
      debug_printf ("transmit(): client->socket is below zero: %d\n", client->socket);
      kill_client(client);
      return;
   }
   
   if ( (write (client->socket, buffer, strlen(buffer))) != strlen(buffer))
   {
      debug_printf ("transmit(): write() was unsuccessful, killing the client.\n");
      kill_client(client);
   }
   
   return;
}
