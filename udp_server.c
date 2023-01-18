#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MESSAGE_SIZE 40000

void udp_server() {

char my_message[MESSAGE_SIZE];

    //Création d'un socket client
    int my_socket;
    my_socket = socket(AF_INET,SOCK_DGRAM,0);

    //Vérification des erreurs de création du socket
    if (my_socket == -1) {

        printf("An error occured while creating the socket !!!\n");
    }

    else {

        printf("Successfully created client socket !!!\n");
    }


    int PORT;
    printf(" Enter the port number to make a connection :\n");
    scanf("%d",&PORT);

    if(PORT == 0){
        printf("Invalid Port\n");
        exit(0); 
    }

    socklen_t lenght;

	//Adresse pour le socket serveur
    struct sockaddr_in server_adress;
    struct sockaddr_in client_adress;
    server_adress.sin_family = AF_INET;
    server_adress.sin_port = htons(PORT);
    server_adress.sin_addr.s_addr = INADDR_ANY; //Adresse du local host IPv4

    //Lier le socket à l'IP et le port spécifiée
    int binding = bind(my_socket,(struct sockaddr*)&server_adress,sizeof(server_adress));

    if (binding == -1) {

        printf("An error occured while binding to the port !!!\n");
    }

    else {

        printf("Successfully binded to the port !!!\n");
    }

    lenght = sizeof(client_adress);

    while(1) {

      char client_message[MESSAGE_SIZE];
      memset(client_message,0,40000); 

      //Recevoir le message du client
      int receive = recvfrom(my_socket,client_message,sizeof(client_message),0,(struct sockaddr*)&client_adress,&lenght);

        if (receive == -1 || strcmp(client_message,"quit\n") == 0) {
             printf("Disconnected from %s with port number %d\n", inet_ntoa(client_adress.sin_addr), ntohs(client_adress.sin_port));
        }

    printf("Client message : %s\n",client_message);

    //Envoyer une réponse au client
    printf("Enter your message: ");
    fgets(my_message,MESSAGE_SIZE,stdin);
    int sending = sendto(my_socket,my_message,strlen(my_message),0,(struct sockaddr*)&client_adress,sizeof(client_adress));

    if(sending == -1) {

        printf("Error while sending your message !!!\n");
    }
    
  }

    close(my_socket);

}