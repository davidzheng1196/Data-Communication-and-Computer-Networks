/*****************************************************************************
 *
 *     This file is part of Purdue CS 536.
 *
 *     Purdue CS 536 is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     Purdue CS 536 is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with Purdue CS 536. If not, see <https://www.gnu.org/licenses/>.
 *
 *****************************************************************************/

/*
 * client.c
 * Name: Xiangyuan Zheng  
 * PUID:34171923
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>

#define SEND_BUFFER_SIZE 2048

/* TODO: client()
 * Open socket and send message from stdin.
 * Return 0 on success, non-zero on failure
 */


int client(char *server_ip, char *server_port_str)
{
  int clientSocket;
  struct sockaddr_in serverAddr;
  char sendbuff[SEND_BUFFER_SIZE];
  int iDataNum;
  uint16_t server_port = atoi(server_port_str);
  if((clientSocket = socket(AF_INET, SOCK_STREAM,0)) < 0){
    perror("socket");
    return 1;
  }

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(server_port);
  inet_pton(AF_INET, server_ip, &(serverAddr.sin_addr));

  if(connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0){
    perror("connect");
    return 1;
  }

  //printf("connect to destination host...");

  //printf("Client input:>");

  int c;
  int counter = 0;
  while((c = getchar()) != EOF){
    sendbuff[counter] = c;
    counter++;
  }

  //printf("\n");

  send(clientSocket, sendbuff, strlen(sendbuff), 0);

  
  close(clientSocket);
  return 0;
}

/*
 * main()
 * Parse command-line arguments and call client function
 */
int main(int argc, char **argv)
{
  char *server_ip;
  char *server_port;

  if (argc != 3)
  {
    fprintf(stderr, "Usage: ./client-c (server IP) (server port) < (message)\n");
    exit(EXIT_FAILURE);
  }

  server_ip = argv[1];
  server_port = argv[2];
  return client(server_ip, server_port);
}
