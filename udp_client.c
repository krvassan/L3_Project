#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MESSAGE_SIZE 40000



void udp_client() {
    
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
    printf(" Enter the port number for the connection :\n");
    scanf("%d",&PORT);

    if(PORT == 0){
        printf("Invalid Port\n");
        exit(0); 
    }

    //Adresse pour le socket
    struct sockaddr_in client_adress;
    client_adress.sin_family = AF_INET;
    client_adress.sin_port = htons(PORT);
    client_adress.sin_addr.s_addr = INADDR_ANY; //Adresse du local host IPv4
    
    
    while(1){
        //Recevoir des données du serveur
        char server_message[MESSAGE_SIZE];//Stocker les informations reçu du serveur

        memset(server_message,0,40000); 
        //Recevoir les données de l'utilisateur
        char my_message[MESSAGE_SIZE];
        printf("Enter your message: ");
        fgets(my_message,MESSAGE_SIZE,stdin);
        socklen_t lenght;
        lenght = sizeof(client_adress);

        //Envoyer le message au serveur
        int sending = sendto(my_socket,my_message,strlen(my_message),0,(struct sockaddr*)&client_adress,sizeof(client_adress));
        
        if (sending == -1 || strcmp(my_message,"quit\n") == 0) {
            printf("Disconnected from the server\n");
            break; 
            
        }
        //Recevoir la réponse du serveur 
        int receive = recvfrom(my_socket,server_message,sizeof(server_message),0,(struct sockaddr*)&client_adress,&lenght);

        if (receive == -1) {

            printf("Error while receiving server message !!!\n");
        }

    
        //Affichage des données reçu par le serveur
        printf("Hello, the server send you the message : %s\n",server_message);
    }
    //Fermer le socket
    close(my_socket);

}