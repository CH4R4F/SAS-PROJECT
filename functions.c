#include "ucode.h"
// create array of structs
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

// fill the user array with the data from the database
void parseData() {
    int id, i = 0;
    float amount;

    FILE *db = fopen("bank.db", "r");
    while(1) {
        // keep looping until end of file, each loop store values to each struct in the user array
        fscanf(db, "%d %s %s %s %f", &id, &user[i].fn, &user[i].ln, &user[i].cin, &amount);
        if(feof(db))
            break;

        user[i].id = id;
        user[i].amount = amount;
        i++;
    }
    fclose(db);
}


// show table based on user's info
void infoTable(newAccount acc) {
    mg_s

    printf("Id: %d\n", acc.id);
    printf("Name: %s %s\n", acc.fn, acc.ln);
    printf("CIN: %s\n", acc.cin);
    printf("Amount: %.2f\n", acc.amount);
}


// create account function
void createAccount(int i) {
    clear();
    createAccountHeader
    mg_s
    printf("account NO %d\n", i);
    // create struct from inputs
    newAccount acc;

    // keep asking while the user gives empty input
    // first name
    do {
        printf("Enter your first name: ");
        fgets(acc.fn, 20, stdin);
        acc.fn[strlen(acc.fn) - 1] = '\0';
    } while (acc.fn[0] == '\0');
    // last name
    do {
        printf("Enter your last name: ");
        fgets(acc.ln, 20, stdin);
        acc.ln[strlen(acc.ln) - 1] = '\0';
    } while (acc.ln[0] == '\0');
    // cin
    do {
        parseData();
        int i = 0;
        int count = idGen();
        int exist = 0;
        printf("Enter your CIN: ");
        fgets(acc.cin, 10, stdin);
        acc.cin[strlen(acc.cin) - 1] = '\0';
        // loop over accounts and check if there is a similar cin
        while (i < count) {
            if (strcmp(strupr(acc.cin), strupr(user[i].cin)) == 0) {
                exist = 1;
                break;
            }
            i++;
        }
        // if exist then retry and show alert
        if(exist) {
            printf("\n### Oops, this CIN is already existed!! ###\n\n");
            acc.cin[0] = '\0';
        }
    } while (acc.cin[0] == '\0');
    // amount
    do {
        printf("Enter amount of money: ");
        scanf("%f", &acc.amount);
        fflush(stdin);
    } while ((int)acc.amount <= 0);
    
    // generate id
    acc.id = idGen();
    // send info to save them in the db
    saveAccount(acc);
}
// create multiple accounts
void createMultipleAccount() {
    int count;
    start:
    clear();
    mg_s

    createMultipleAccountHeader
    mg_s
    // ask for how many accounts
    printf("=> please enter how much account you want to create: ");
    scanf("%d", &count);
    fflush(stdin);
    while (!count) {
        goto start;
    }
    // keep creating account
    for(int i = 1; i <= count; i++) {
        createAccount(i);
    }
}

void withdraw() {
    clear();
    char userCin[15];
    int i, exist = 0;
    int count = idGen();
    goto enterCin;

    renterCin:
    printf("\n### Oops, there is no account with this CIN ###\n");
    enterCin:
    withdrawHeader
    mg_s
    i = 0;
    printf("Enter the account CIN: ");
    scanf("%s", &userCin);
    fflush(stdin);
    // parse database data
    parseData();
    // then check if there is an account with this cin or not
    while (i < count) {
        if (!strcmp(strupr(userCin), strupr(user[i].cin))) {
            infoTable(user[i]);
            exist = 1;
            break;
        }
        i++;
    }
    // if exist then
    if(exist) {
        float amnt;
        mg_s
        // store the amount to withdraw every time the user type invalid amount
        do {
            printf("    Enter the amount to withdraw: ");
            scanf("%f", &amnt);
            fflush(stdin);
        } while (amnt <= 0 || amnt > user[i].amount);
        // update the amount in the index where I found the cin
        user[i].amount -= amnt;
        // delete everything from the database
        FILE *db = fopen("bank.db", "w");
        fclose(db);
        // show changes
        infoTable(user[i]);
        // then apdate the db with the data I parsed and edited
        for (int i = 0; i < count - 1; i++) {
            saveAccount(user[i]);
        }
    } else {
        goto renterCin;
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