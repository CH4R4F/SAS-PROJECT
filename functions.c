#include "ucode.h"


// function to clear the terminal on multiple OS
void clear(){
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

void createAccount(int i) {
    clear();
    createAccountHeader
    mg_s
    printf("account NO %d\n", i);
    char firstName[25];
    char lastName[25];
    char cin[15];
    char amount[25];

    do {
        printf("Enter your first name: ");
        fgets(firstName, 20, stdin);
        firstName[strlen(firstName) - 1] = '\0';
    } while (firstName[0] == '\0');
    do {
        printf("Enter your last name: ");
        fgets(lastName, 20, stdin);
        lastName[strlen(lastName) - 1] = '\0';
    } while (lastName[0] == '\0');
    do {
        printf("Enter your CIN: ");
        fgets(cin, 10, stdin);
        cin[strlen(cin) - 1] = '\0';
    } while (cin[0] == '\0');
    do {
        printf("Enter amount of money: ");
        fgets(amount, 30, stdin);
        amount[strlen(amount) - 1] = '\0';
    } while (amount[0] == '\0');

    saveAccount(firstName, lastName, cin, amount);
}

void createMultipleAccount() {
    int count;
    start:
    clear();
    mg_s

    createMultipleAccountHeader
    mg_s
    printf("=> please enter how much account you want to create: ");
    scanf("%d", &count);
    fflush(stdin);
    while (!count) {
        goto start;
    }
    
    for(int i = 1; i <= count; i++) {
        createAccount(i);
    }
}

void operations() {
    clear();
    operationsHeader
    int i = idGen();
    mg_s
    if(!(i - 1)) {
        int choice;
        printf("===| Ooops, it looks like you have no account |====\n");
        mg_s
        printf("[1] - create new account            [0] - back");
        mg_s
        printf("    Enter your choic: ");
        scanf("%d", &choice);
        fflush(stdin);
        if(choice == 1) {
            createAccount(i);
        } 
    } else {
        retry:
        clear();
        int choice;
        operationsHeader
        mg_s
        printf("[1] - Withdraw\n");
        printf("[2] - Deposit\n");
        printf("[0] - Back");
        mg_s
        printf("    Enter your choice: ");
        scanf("%d", &choice);
        fflush(stdin);
        if(choice == 1) {
            char cin[10];
            clear();
            withdrawHeader
            mg_s
            enterCin:
            parseData();
            printf("Enter the accounts CIN: ");
            scanf("%s", &cin);
            
            
        } else if(choice == 2) {

        } else {
            goto retry;
        }
    }
}


void startApplication() {
    int input;
    goto start;

    invalid:
    printf("####### Invalid choice try again #########\n");


    start:
    clear();
    mainHeader
    mg_s
    printf("[1] - Create new account.\n");
    printf("[2] - Create many accounts.\n");
    printf("[3] - Operations.\n");
    printf("[4] - Affichage.\n");
    printf("[5] - Loyalty.\n");
    printf("[6] - Quite.\n");

    mg_m

    printf("    Enter your choice: ");
    scanf("%d", &input);
    fflush(stdin);

    
    switch (input) {
        case 1:
            createAccount(idGen());
            startApplication();
            break;
        case 2:
            createMultipleAccount();
            startApplication();
            break;
        case 3:
            operations();
            startApplication();
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        default:
            goto invalid;
    }

}