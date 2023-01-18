
#include "tcp_server.c"
#include "udp_server.c"
#include "tcp_client.c"
#include "udp_client.c"

int main()
{


    int choice_zero;
    int first_choice;
    int second_choice; 
    int third_choice;

    printf("Welcome user to our programm concerning the simulation of TCP/IP \n");

    printf("\n--------------------------------------------------------------------\n");
    printf("Type the role you want to be affected 1 for server 2 for client ");
    scanf("%d", &choice_zero);
    printf("\nYou have chosen the number : %d\n",choice_zero);
    printf("--------------------------------------------------------------------\n");

    switch (choice_zero){
    case 1:  
        printf("\n--------------------------------------------------------------------\n");
        printf("Select the protocol you want 3 for UDP and 4 for TCP ");
        scanf("%d", &first_choice);
        printf("\nYou have chosen the number : %d\n",first_choice);
        printf("--------------------------------------------------------------------\n");
        switch(first_choice){
            case 3 :
            udp_server(); 
            break;
            case 4 : 
            printf("\n--------------------------------------------------------------------\n");
            printf("Select 5 for multiple TCP or select 6 for iterative TCP ");
            scanf("%d", &second_choice);
            printf("\nYou have chosen the number : %d\n",second_choice);
            printf("--------------------------------------------------------------------\n");
            switch (second_choice){
                case  5:
                    multiple_server();
                    break;
                case 6:
                    iterative_server();
                    break;
                default:
                    break;
                }
            default: 
                break;
        }
        break;
    case 2:
        printf("\n--------------------------------------------------------------------\n");
        printf("Select the protocol you want 7 for UDP and 8 for TCP ");
        scanf("%d", &third_choice);
        printf("\nYou have chosen the number : %d\n",third_choice);
        printf("--------------------------------------------------------------------\n");

        switch(third_choice){
            case 7 :
            udp_client(); 
            break;
            case 8: 
            tcp_client();
            break;
           
        default:
            break;
        }
    default :
        break;
    }
    return 0 ;
}
