#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

void tcp_client() {
    
    
    //Création d'un socket client
    int my_socket;
    char my_message[40000];

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
    //Adresse pour le socket
    struct sockaddr_in server_adress;
    server_adress.sin_family = AF_INET;
    server_adress.sin_port = htons(PORT);
    server_adress.sin_addr.s_addr = INADDR_ANY; //Adresse du local host IPv4

    //Connexion a un socket serveur
    int connection = connect(my_socket,(struct sockaddr*)&server_adress,sizeof(server_adress));

    //Vérification des erreurs de connexion
    if (connection == -1) {
    	printf("There was an error on making a connection to the socket !!!\n");
    }
    else {
        printf("Connected to the server !!!\n");
    }

    //Boucler tant que le client est connecter au serveur
    while(1) {
        
        memset(my_message,0,40000);
        printf("Write your message : ");
        fgets(my_message,40000,stdin);
        int envoye = send(my_socket,my_message,strlen(my_message),0);
        if ((envoye == -1) || strcmp(my_message,"quit\n") == 0) { //Vérifier si le client veut rompre la connexion avec le serveur
            break; 
        }
        
        memset(my_message,0,40000);

        
        //Recevoir des données du serveur
        int receive = recv(my_socket,my_message,40000,0);
        if (receive == -1 || strcmp(my_message,"quit\n") == 0) {
            break; 
            printf("Disconnected from the server");
        }
        else {
            printf("Hello, the server send you the message : %s\n",my_message); 
        }
    }
    close(my_socket);

}