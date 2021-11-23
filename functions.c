#include "ucode.h"

newAccount user[100];

// function to clear the terminal on multiple OS
void clear(){
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

void parseData() {
    int id, i = 0;
    char fn[25], ln[25], cin[10];
    float amount;

    FILE *db = fopen("bank.db", "r");
    while(fscanf(db, "%d %s %s %s %f", &id, &fn, &ln, &cin, &amount) != EOF) {
        user[i].id = id;
        user[i].fn = fn;
        user[i].ln = ln;
        user[i].cin = cin;
        user[i].amount = amount;
        i++;
    }
    fclose(db);
}

void createAccount(int i) {
    clear();
    createAccountHeader
    mg_s
    printf("account NO %d\n", i);
    char firstName[25];
    char lastName[25];
    char cin[15];
    float amount;

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
        scanf("%f", &amount);
        fflush(stdin);
    } while ((int)amount <= 0);
    newAccount user;
    user.id = idGen();
    user.fn = firstName;
    user.ln = lastName;
    user.cin = cin;
    user.amount = amount;
    saveAccount(user);
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
void withdraw() {
    clear();
    char userCin[15];
    int i = 0;
    withdrawHeader
    mg_s
    printf("Enter the account CIN: ");
    scanf("%s", &userCin);
    parseData();
    // while (user[i].id) {
    //     if (!strcmp(strupr(cin), user[i].cin)) {
    //         printf("exist account");
    //         break;
    //     }
    //         printf("%s\n", user[i].cin);

    //     i++;
    // }
    
    while (user[i].id) {
        printf("\n== %s", user[i].cin);
        printf("%d", user[i].id);
        printf("%s", user[i].fn);
        printf("%s", user[i].ln);
        printf("%f", user[i].amount);
        i++;
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
            withdraw();
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
            // startApplication();
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