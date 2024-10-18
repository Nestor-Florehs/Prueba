#include "user.h"

void deleteLinespace(String str){
    str[strlen(str)-1] = '\0';
}

int addUser(Data* d, User newUser){
    int error = 0;
    User* aux = realloc(d->user, (d->n_users + 1)*sizeof(User));
    if(aux == NULL){
        printf("(ERROR) Memory failed");
        error = 1;
    }else{
        d->user = aux;
        d->user[d->n_users] = newUser;
        d->n_users++;
    }
    return error;
}

Data removeUser(Data d, int index){
    if(d.n_users < 1){
        printf("Memory is already empty");
    }else{
        memmove(&d.user[index], &d.user[index+1], (d.n_users-(index+1))* sizeof(User));
        User* aux = realloc(d.user, (d.n_users-1)*sizeof(User));
        if(aux == NULL){
            printf("Memory error");
        }else{
            d.user = aux;
            d.n_users--;
        }
    }
    return d;
}

int checkComma(String str){
    int error = 0;
    if(strstr(str, ",")){
        printf("(ERROR) Field cannot contain ','\n");
        error = 1;
    }
    return error;
}

Data registerUser(Data d){
    User newUser;
    int error = 0;
    char aux;

    printf("Enter your name: \n");
    fgets(newUser.name, 50, stdin);
    deleteLinespace(newUser.name);
    error = checkComma(newUser.name);
    printf("Enter your mail: \n");
    fgets(newUser.email, 50, stdin);
    deleteLinespace(newUser.email);
    if(!error) {
        for (int i = 0; i < d.n_users; i++) {
            if (strcmp(newUser.email, d.user[i].email) == 0) {
                error = 1;
                printf("(ERROR) Email already registered\n");
            }
        }
        if (!strstr(newUser.email, "@")) {
            printf("(ERROR) Email must contain '@'\n");
            error = 1;
        }
        if(!error){
            error = checkComma(newUser.email);
        }
    }
    if(!error){
        printf("Enter your password: \n");
        fgets(newUser.password, 50, stdin);
        deleteLinespace(newUser.password);
        if(strlen(newUser.password) < 8){
            error = 1;
            printf("(ERROR) Password must be at least 8 characters\n");
        }
        if(!error) {
            error = checkComma(newUser.password);
        }
        if(!error){
            printf("Enter your rol: \n");
            scanf("%c", &newUser.rol);
            scanf("%c", &aux);
            newUser.rol = toupper(newUser.rol);
            if(newUser.rol != 'C' && newUser.rol != 'A' && newUser.rol != 'I'){
                printf("(ERROR) This rol does not exist\n");
                error = 1;
            }else{
                if(newUser.rol == 'A'){
                    printf("Enter your PIN: \n");
                    scanf("%s", newUser.pin);
                    scanf("%c", &aux);
                    for(int i = 0; i < strlen(newUser.pin); i++){
                        if(!isdigit(newUser.pin[i])){
                            error = 1;
                            printf("a");
                        }
                    }
                    if(error){
                        printf("(ERROR) PIN must contain only numeric values\n");
                    }
                    if(strlen(newUser.pin) < 4 && !error){
                        printf("(ERROR) PIN must be at least 4 numbers\n");
                        error = 1;
                    }
                }
                if(!error){
                    if(d.n_users == 0){
                        newUser.id = 1;
                    }else{
                        newUser.id = d.user[d.n_users-1].id + 1;
                    }
                    printf("%d\n", newUser.id);
                    error = addUser(&d, newUser);
                    if(!error) {
                        printf("Register successful!\n");
                    }
                }
            }
        }
    }
    return d;
}

void showClientData(Data data) {
    int i;
    User user;

    if (data.n_users == 0) {
        printf("No clients\n");
    } else {
        for (i = 0; i < data.n_users; i++) {
            user = data.user[i];
            if (user.rol == 'C') {
                printf("User: %s\n", user.name);
                printf("\tId: %d\n", user.id);
                printf("\temail: %s\n", user.email);
                printf("\tPin: %d\n", user.pin);
            }
        }
    }
}

void logIn(Data data){
    String username;
    String password;
    int i;
    int found=0;
    char aux;
    String pin;

    printf("Enter your email: \n");
    scanf("%s",username);
    scanf("%c",&aux);
    printf("Enter your password: \n");
    scanf("%s",password);
    scanf("%c",&aux);

    for(i=0; i<data.n_users; i++){
        if(!strcmp(data.user[i].email,username) && !strcmp(data.user[i].password,password)){
            found=1;
            if(data.user[i].rol=='A'){
                printf("Enter your PIN: \n");
                fgets(pin,50,stdin);
                deleteLinespace(pin);
                if(strcmp(data.user[i].pin,pin) == 0){
                    found=1;
                }else{
                    found=0;
                }
            }
        }
    }
    if(found==1){
        printf("Log In successful");
    }else{
        printf("(ERROR) wrong email or password");
    }
}

int findUserByMail(Data d) {
    String mail;
    int index = 0;
    int ok = 0;
    printf("Enter mail of the user: \n");
    fgets(mail, 50, stdin);
    for(int i = 0; i < d.n_users && !ok; i++) {
        if(!strcmp(mail, d.user[i].email)) {
            index = i;
            ok = 1;
        }
        else {
            index = -1;
        }
    }
    return index;
}

Data removeClient(Data d) {
    int index = findUserByMail(d);
    if(index == -1) {
        printf("ERROR: Client not found");
    }
    else {
        if (d.user[index].rol == 'C') {
            removeUser(d, index);
            printf("Client deleted\n");
        } else {
            printf("ERROR: The user is not a client\n");
        }
    }
    return d;
}

void printUsers(Data d) {
    for (int i = 0; i < d.n_users; i++) {
        printf("User %d: Name=%s, Email=%s\n", i + 1, d.user[i].name, d.user[i].email);
    }
}