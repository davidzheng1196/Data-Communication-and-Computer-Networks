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
 * server.c
 * Name:Xiangyuan Zheng
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

#define QUEUE_LENGTH 10
#define RECV_BUFFER_SIZE 2048

/* TODO: server()
 * Open socket and wait for client to connect
 * Print received message to stdout
 * Return 0 on success, non-zero on failure
 */


int server(char *server_port_str)
{
  int serverSocket;
  struct sockaddr_in server_addr;
  struct sockaddr_in clientAddr;
  int addr_len = sizeof(clientAddr);
  int client;
  char buffer[RECV_BUFFER_SIZE];
  int iDataNum;
  uint16_t server_port = atoi(server_port_str);
  if((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) <0){
    perror("socket");
    return 1;
  }

  bzero(&server_addr, sizeof(server_addr));

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(server_port);
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if(bind(serverSocket, (struct sockaddr *)&server_addr, sizeof(server_addr))<0){
    perror("connect");
    return 1;
  }

  if(listen(serverSocket, QUEUE_LENGTH) < 0){
    perror("listen");
    return 1;
  }

  while(1){
    //printf("Listening on port: %d\n", *server_port);

    client = accept(serverSocket, (struct sockaddr*)&clientAddr, (socklen_t*)&addr_len);
    if(client < 0){
      perror("accept");
      continue;
    }
    //printf("\n recv client data..n");
  
    //printf("Port is %d\n", htons(clientAddr.sin_port));
    //while(1){
      iDataNum = recv(client, buffer, RECV_BUFFER_SIZE, 0);
      if(iDataNum < 0){
        perror("recv");
        continue;
      }
    
      buffer[iDataNum] = '\0';
      printf("%s\n",buffer);
      //break;
    //}
    

  
  }
  return 0;
  
}

/*
 * main():
 * Parse command-line arguments and call server function
 */
int main(int argc, char **argv)
{
  char *server_port;

  if (argc != 2)
  {
    fprintf(stderr, "Usage: ./server-c (server port)\n");
    exit(EXIT_FAILURE);
  }

  server_port = argv[1];
  return server(server_port);
}
