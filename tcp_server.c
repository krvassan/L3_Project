#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//#define PORT 4442



///////////////////////////////////// ITERATIVE SERVER /////////////////////////////////////////////////////////////
void iterative_server() {

    char server_message[40000];

    //Création d'un socket serveur
	int my_socket;
    my_socket = socket(AF_INET,SOCK_STREAM,0);

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

    //Adresse pour le socket serveur
    struct sockaddr_in server_adress;
    server_adress.sin_family = AF_INET;
    server_adress.sin_port = htons(PORT);
    server_adress.sin_addr.s_addr = INADDR_ANY; //Adresse du local host IPv4

    //Lier le socket à l'IP et le port spécifiée
    int binding = bind(my_socket,(struct sockaddr*)&server_adress,sizeof(server_adress));

    if (binding == -1) {
        printf("An error occured while binding !!!\n");
    }
    else {
        printf("Bind to port %d!!!\n",PORT);
    }

    //Le socket écoute, Le serveur peut accepter les demandes de connexion
    int lis = listen(my_socket,6);

    if (lis == -1) {
        printf("An error occured while listening !!!\n");
    }
    else {
        printf("Listening...\n");
    }

    while(1){
    
     //Création d'un socket client
    int client_socket;
    struct sockaddr_in client_adress;
    socklen_t size_adress = sizeof(client_adress);

     client_socket = accept(my_socket, (struct sockaddr*)&client_adress, &size_adress);
        if(client_socket < 0){
            exit(1);
        }
        printf("Connection accepted from %s with port number %d\n", inet_ntoa(client_adress.sin_addr), ntohs(client_adress.sin_port));

            while(1){

                memset(server_message,0,40000); 
                int receive = recv(client_socket, server_message, 40000, 0);
        
                if (receive == -1 || strcmp(server_message,"quit")==0 || strcmp(server_message,"quit\n") == 0) {
                    break; 
                    printf("Disconnected from %s with port number %d\n", inet_ntoa(client_adress.sin_addr), ntohs(client_adress.sin_port));
                }

                printf("Client: %s\n", server_message);
                printf("Server: ");

                fgets(server_message,40000,stdin);
                int sending = send(client_socket, server_message, strlen(server_message), 0);
                if (sending == -1 || strcmp(server_message,"quit\n") ==0 || strcmp(server_message,"quit") ==0 ) {
                    printf("Disconnected from %s with port number %d\n", inet_ntoa(client_adress.sin_addr), ntohs(client_adress.sin_port));
                    break; 
                }
            }

            close(client_socket);
            printf("Connection ended. Waiting for new connection now...\n");
        }

        close(my_socket);
}



///////////////////////////////////// MULTIPLE SERVER /////////////////////////////////////////////////////////////


void multiple_server() {

    char server_message[40000];
    pid_t pid;

    //Création d'un socket serveur
	int my_socket;
    my_socket = socket(AF_INET,SOCK_STREAM,0);

    //Vérification des erreurs de création du socket
    if (my_socket == -1) {

        printf("An error occured while creating the socket !!!\n");
    }
    else {

        printf("Successfully created client socket !!!\n");
    }
    
    int PORT;
    printf(" Enter the port number for the connection :\n");
    scanf("%d",&PORT);

    if(PORT == 0){
        printf("Invalid Port\n");
        exit(0); 
    }

    //Adresse pour le socket serveur
    struct sockaddr_in server_adress;
    server_adress.sin_family = AF_INET;
    server_adress.sin_port = htons(PORT);
    server_adress.sin_addr.s_addr = INADDR_ANY; //Adresse du local host IPv4


    //Lier le socket à l'IP et le port spécifiée
    int binding = bind(my_socket,(struct sockaddr*)&server_adress,sizeof(server_adress));

    if (binding == -1) {
        printf("An error occured while binding !!!\n");
    }
    else {
        printf("Bind to port %d!!!\n",PORT);
    }

    //Le socket écoute, Le serveur peut accepter les demandes de connexion
    int lis = listen(my_socket,6);

    if (lis == -1) {
        printf("An error occured while listening !!!\n");
    }
    else {
        printf("Listening...\n");
    }

    while(1){

     //Création d'un socket client
    int client_socket;
    struct sockaddr_in client_adress;
    socklen_t size_adress = sizeof(client_adress);

     client_socket = accept(my_socket, (struct sockaddr*)&client_adress, &size_adress);
        if(client_socket < 0){

            exit(1);
        }
        printf("Connection accepted from %s with port number %d\n", inet_ntoa(client_adress.sin_addr), ntohs(client_adress.sin_port));

        if((pid = fork()) == 0){
            close(my_socket);

            while(1){

                memset(server_message,0,40000); 
                int receive = recv(client_socket, server_message, 40000, 0);

                if (receive == -1 || strcmp(server_message,"quit")==0 || strcmp(server_message,"quit\n") == 0) {
                    printf("Disconnected from %s with port number %d\n", inet_ntoa(client_adress.sin_addr), ntohs(client_adress.sin_port));
                    break; 
                } else {
                    
                printf("Client: %s\n", server_message);
                printf("Server: ");
                fgets(server_message,40000,stdin);
                int envoye = send(client_socket, server_message, strlen(server_message), 0);
                if (envoye == -1 || strcmp(server_message,"quit\n") ==0 ) {
                    printf("Disconnected from %s with port number %d\n", inet_ntoa(client_adress.sin_addr), ntohs(client_adress.sin_port));
                    break; 
                    }
                }
            }
        }
        close(client_socket);
    }
}
