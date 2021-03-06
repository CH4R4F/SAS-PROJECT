#ifndef UCODE_H
# define UCODE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// titles
#define mainHeader printf("########## Main Menu ##########");
#define createAccountHeader printf("########## Main Menu > Create account ##########");
#define createMultipleAccountHeader printf("########## Main Menu > Create multiple accounts ##########");
#define operationsHeader printf("########## Main Mennu > Operations ##########");
#define withdrawHeader printf("########## Main Mennu > Operations > Withdraw ##########");
#define depositeHeader printf("########## Main Menu > Operations > Deposite");
// margins
#define mg_s printf("\n\n");
#define mg_m printf("\n\n\n");
// functions prototype
void startApplication();
void clear();
void saveAccount();
void createAccount();
int idGen();
void operations();
void parseData();
// structs
typedef struct Account {
    int id;
    char fn[20];
    char ln[20];
    char cin[20];
    float amount;
}newAccount;



#endif