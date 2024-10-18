#include "Interface.h"


void initialMenu (Data d) {
    int option;
    char aux;

    do {
        printf("\t1. Log in\n");
        printf("\t2. Sign in\n");
        printf("\t3. Quit\n");
        printf("Access: ");
        scanf("%d", &option);
        scanf("%c", &aux);

        switch (option) {
            case 1:
                logIn(d);
            break;
            case 2:
                d = registerUser(d);
            break;
            case 3:
                printf("see you soon\n");
            break;
            default:
                printf("Error\n");
            break;
        }
    } while (option != 3);
}

void printHomePage(User user){
    int option;
    switch (user.rol)
    {
    case 'A':
            printf("1.Add clients\n");
            printf("2.Modify clients\n");
            printf("3.Remove clients\n");
            printf("4.Add researchers\n");
            printf("5.Modify researchers\n");
            printf("6.Remove researchers\n");
            printf("7.Modify researchers\n");

        break;

    case 'R':
        printf("1.Create project\n");
        printf("2.View project details\n");

        break;

    case 'C':
        printf("1.Modify data\n");
        printf("2.Delete account\n");
        break;
    default:
        break;
    }
}