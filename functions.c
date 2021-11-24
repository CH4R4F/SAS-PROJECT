#include "ucode.h"
// create array of structs
newAccount user[100];

// function to clear the terminal on multiple OS
void clear(){
    system("cls");
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

// row info
void rowInfo(newAccount acc) {
    printf("name: %s %s | CIN: %s | amount: %.2f\n\n", acc.fn, acc.ln, acc.cin, acc.amount);
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

void withdraw(int index, int x) {
    float amnt;
    mg_s
    // store the amount to withdraw every time the user type invalid amount
    do {
        printf("    Enter the amount to withdraw: ");
        scanf("%f", &amnt);
        fflush(stdin);
    } while (amnt <= 0 || amnt > user[index].amount);
    // update the amount in the index where I found the cin
    user[index].amount -= amnt;
    // delete everything from the database
    FILE *db = fopen("bank.db", "w");
    fclose(db);
    printf("#### => Operation Done Successfully\n");
    // show changes
    infoTable(user[index]);
    // then update the db with the data I parsed and edited
    for (int i = 0; i < x - 1; i++) {
        saveAccount(user[i]);
    }

     mg_s
    int c;
    printf("[1] - Main Menu\t\t\t");
    printf("[2] - Quite\n\n");

    printf("   Enter your choice: ");
    scanf("%d", &c);
    fflush(stdin);
    if(c == 1) {
        startApplication();
    } 
}

void deposite(int index, int count) {
    float amnt;
    mg_s
    do {
        printf("Enter the amount to add: ");
        scanf("%f", &amnt);
        fflush(stdin);
    } while (amnt <= 0);

    user[index].amount += amnt;

    FILE *db = fopen("bank.db", "w");
    fclose(db);
    // show changes
    printf("#### => Operation Done Successfully\n");
    infoTable(user[index]);
    // then update the db with the data I parsed and edited
    for (int i = 0; i < count - 1; i++) {
        saveAccount(user[i]);
    }
    mg_s
    int c;
    printf("[1] - Main Menu\t\t\t");
    printf("[2] - Quite\n\n");

    printf("   Enter your choice: ");
    scanf("%d", &c);
    fflush(stdin);
    if(c == 1) {
        startApplication();
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
        int i;
        char userCin[15];
        int count = idGen();
        int exist = 0;
        int choice;
        parseData();
        
        clear();
        operationsHeader
        mg_s
        do {
            i = 0;
            printf("Enter the account CIN: ");
            scanf("%s", &userCin);
            fflush(stdin);
            while (i < count) {
                if (strcmp(strupr(userCin), strupr(user[i].cin)) == 0) {
                    exist = 1;
                    break;
                }
                i++;
            }
            // if exist then retry and show alert
            if(!exist) {
                printf("\n### Oops, there is no acc with CIN: %s ###\n\n", userCin);
                userCin[0] = '\0';
            }
        } while (userCin[0] == '\0');
        
        infoTable(user[i]);
        mg_s
        printf("[1] - withdrw\n");
        printf("[2] - seposit\n");
        printf("[0] - back\n");
        retry:
        printf("   Enter your choice: ");
        scanf("%d", &choice);
        fflush(stdin);
        switch (choice)
        {
        case 1:
            withdraw(i, count);
            break;
        case 2:
            deposite(i, count);
            break;
        
        default:
            goto retry;
        }
    }
}


void sortData(int x){
    int max = idGen();

    for(int i = 0; i < max - 1; i++) {
        for (int j = 1; j < max - 1; j++) {
            if(x == 1) {
                if(user[j].amount > user[j - 1].amount) {
                    newAccount tmp1 = user[j];
                    user[j] = user[j+1];
                    user[j+1] = tmp1;
                }
            } else {
                if(user[j].amount < user[j + 1].amount) {
                    newAccount tmp2 = user[j];
                    user[j] = user[j+1];
                    user[j+1] = tmp2;
                }
            }
            
        }
    }
    
}


void displayMenu() {
    clear();
    int choice;
    // parse and loop over the data and show initial data table
    parseData();
    int count = idGen() - 1;
    for (int i = 0; i < count; i++) {
        rowInfo(user[i]);
    }
    mg_s
    printf("[1] - By Ascending Order\n");
    printf("[2] - By Descending Order\n");
    printf("[3] - Ascending Filter\n");
    printf("[4] - Descending Filter\n");
    printf("[5] - Back\n");
    mg_s
    // keep asking if the user entered invalid choice
    do {
        printf("  Enter your choice: ");
        scanf("%d", &choice);
        fflush(stdin);
    } while (choice > 5 || choice < 1);

    if (choice == 1 || choice == 2) {
        sortData(choice);
        for (int i = 0; i < count; i++) {
        rowInfo(user[i]);
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
            displayMenu();
            break;
        case 5:
            break;
        case 6:
            break;
        default:
            goto invalid;
    }

}