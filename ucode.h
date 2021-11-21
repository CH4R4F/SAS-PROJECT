#ifndef UCODE_H
# define UCODE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// titles
#define mainHeader printf("########## Main Menu ##########");
#define createAccountHeader printf("########## Main Menu > Create account ##########");
#define createMultipleAccountHeader printf("########## Main Menu > Create multiple accounts ##########");
// margins
#define mg_s printf("\n\n");
#define mg_m printf("\n\n\n");
// functions prototype
void startApplication();
void clear();
void saveAccount();
void createAccount();
int idGen();
// structs
typedef struct Account {
    char *fn;
    char *ln;
    char *cin;
    char *amount;
} newAccount;
#endif