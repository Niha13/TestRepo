﻿#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <winsock2.h>
#include <unistd.h>
#define PORT 3550 // El puerto que será abierto
#define BACKLOG 2 // El número de conexiones permitidas

void doprocessing (int sock)
{
    int n;
    char buffer[256];

    memset(&(buffer), '0', 256);
    int recvMsgSize;
    //char file[]="Loans.txt";
    //char recive(recvMsgSize);

    if ((recvMsgSize = recv(sock, buffer, 256, 0)) < 0) //Receive message from client
        perror("ERROR1 reading to socket ");

    /* Send received string and receive again until end of transmission */
    while (recvMsgSize > 0)      /* zero indicates end of transmission */
    {
        if (send(sock, buffer, recvMsgSize, 0) != recvMsgSize) // Echo message back to client
            perror("ERROR2 writing to socket");

        //LLAMADAs


        if ((recvMsgSize = recv(sock, buffer, 256, 0)) < 0) //See if there is more data to receive
            perror("ERROR3 reading to socket ");
    }

    closesocket(sock);    /* Close client socket */
}

//====================================================================================================

void addRFC(char b[])
 {
     FILE *p;
     char a[256];
     strcpy(a,b);

     if((p=fopen("Loans.txt","a")) == NULL)
        {
            printf("Error en apertura\n");
            getch();
            exit(1);
        }

      fputs(a,p);
      printf("\n");

     fclose(p);
 }

//====================================================================================================

void findRFC(char b[])
{
    FILE *p;
    char a[256]={0x0};

    if((p=fopen("Loans.txt","r")) == NULL)
        {
            printf("Error en apertura\n");
            getch();
            exit(1);
        }
    else
        {
            while(p!=NULL && fgets(a,sizeof(a),p)!=NULL)
            {
                if(strstr(a,b))
                //teniamos un print pero eso se debe de regresar a java
                printf("%s",a);
            }
            if(p!=NULL)
                fclose(p);
        }


}

//====================================================================================================

void prueba(char b[])
{
    char blocal[256];
    strcpy(blocal,b);
    printf("%s",blocal);

    if(findRFC(blocal)==1)
    {
        printf("no existe");
    }
    else
    {
        //findRFC(b);
    }
}

//EN proceso!


BOOL initW32()
{
		WSADATA wsaData;
		WORD version;
		int error;

		version = MAKEWORD( 2, 0 );

		error = WSAStartup( version, &wsaData );


		if ( error != 0 ) // check for error
        {
		    return FALSE; //error occured
		}

		/* check for correct version */
		if ( LOBYTE( wsaData.wVersion ) != 2 ||
		     HIBYTE( wsaData.wVersion ) != 0 )
		{
		    /* incorrect WinSock version */
		    WSACleanup();
		    return FALSE;
		}
}

int main()
{
    initW32(); // Necesaria para compilar en Windows
    int fd, fd2; // los descriptores de archivos

    struct sockaddr_in server; // para la información de la dirección del servidor
    struct sockaddr_in client; // para la información de la dirección del cliente

    unsigned int sin_size;
    pid_t pid;

    if ((fd=socket(AF_INET, SOCK_STREAM, 0)) == -1 )
        {
            printf("error en socket()\n");
            exit(-1);
        }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY coloca nuestra dirección IP automáticamente */

   //bzero(&(server.sin_zero),8);
   memset(&(server.sin_zero), '0', 8);// escribimos ceros en el resto de la estructura


   if(bind(fd,(struct sockaddr*)&server, sizeof(struct sockaddr))==-1) // A continuación la llamada a bind()
    {
      printf("error en bind() \n");
      exit(-1);
    }

   if(listen(fd,BACKLOG) == -1)
    {  // llamada a listen()
      printf("error en listen()\n");
      exit(-1);
    }

   while(1)
    {
      sin_size=sizeof(struct sockaddr_in);
      if ((fd2 = accept(fd,(struct sockaddr *)&client, &sin_size))==-1)// A continuación la llamada a accept()
        {
         printf("error en accept()\n");
         exit(-1);
        }

      printf("Connecting with Java: %s\n", inet_ntoa(client.sin_addr) );// que mostrará la IP del cliente
      send(fd2,"Niha Server\n",99,0);//Muestra que enviará el mensaje de bienvenida al cliente
      doprocessing(fd2);

   }
}

