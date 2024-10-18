#ifndef PRUEBA_USER_H
#define PRUEBA_USER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Interface.h"

typedef char String[100];

typedef struct {
    int id;
    String name;
    String email;
    String password;
    String pin;
    char rol;	// A: admin / R: investigador / C: cliente
} User;

typedef struct {
    int n_users;
    User* user;
} Data;

Data registerUser(Data d);

void printUsers(Data d);

void logIn(Data d);

void showClientData(Data data);

Data removeClient(Data d);

int findUserByMail(Data d);

#endif //PRUEBA_USER_H
