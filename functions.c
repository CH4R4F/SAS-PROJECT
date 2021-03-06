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

// sorted table
void  table(newAccount acc) {
    printf("|%9s %9s|%14s|%20f\n", acc.fn, acc.ln, acc.cin, acc.amount);
    printf("========================================================\n");
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
    table(user[index]);
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
    table(user[index]);
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
        
        table(user[i]);
        mg_s
        printf("[1] - Withdrw\n");
        printf("[2] - Deposit\n");
        printf("[0] - Back\n");
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
            case 0:
                startApplication();
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
            if(x == 1 || x == 3) {
                if(user[j].amount < user[j - 1].amount) {
                    newAccount tmp1 = user[j];
                    user[j] = user[j-1];
                    user[j-1] = tmp1;
                }
            } else {
                if(user[j].amount > user[j - 1].amount) {
                    newAccount tmp2 = user[j];
                    user[j] = user[j-1];
                    user[j-1] = tmp2;
                }
            }
        }
    }
    
}


void displayMenu() {
    clear();

    printf("########## Main Menu > Display ##########");
    mg_s
    int choice;
    // parse and loop over the data and show initial data table
    parseData();
    int count = idGen() - 1;
    printf("[1] - By Ascending Order\n");
    printf("[2] - By Descending Order\n");
    printf("[3] - Ascending Filter\n");
    printf("[4] - Descending Filter\n");
    printf("[5] - Search For Account\n");
    printf("[6] - Back\n");
    mg_s
    // keep asking if the user entered invalid choice
    do {
        printf("  Enter your choice: ");
        scanf("%d", &choice);
        fflush(stdin);
    } while (choice > 6 || choice < 1);

    if (choice == 1 || choice == 2) {
        sortData(choice);
        for (int i = 0; i < count; i++) {
            table(user[i]);
        }
    } else if(choice == 3 || choice == 4) {
        sortData(choice);
        mg_s
        float min;
        printf("   => Enter the minimun amount: ");
        scanf("%f", &min);
        fflush(stdin);
        for (int i = 0; i < count; i++) {
            if(user[i].amount >= min) {
                table(user[i]);
            }
        }
    } else if(choice == 5) {
        int i = 0, exist = 0;
        char cin[15];
        printf("==> Enter the account cin: ");
        scanf("%s", cin);
        while (i < count) {
            if (strcmp(strupr(cin), strupr(user[i].cin)) == 0) {
                exist = 1;
                break;
            }
            i++;
        }
        if (exist) {
            table(user[i]);
        } else {
            printf("#### ERROR 404: account with CIN: %s not found", cin);
        }
    } else {
        startApplication();
    }
    int finalMenu;
    mg_s
    printf("[1] - Back          [2] - Main Menu           [Any key] - Quite");
    printf("\n     Enter your choice: ");
    scanf("%d", &finalMenu);
    fflush(stdin);
    if (finalMenu == 1) {
        displayMenu();
    } else if(finalMenu == 2) {
        startApplication();
    }
}

void reprise() {
    parseData();
    int count = idGen();
    printf("The biggest accounts in the bank\n\n");;
    for (int i = 0; i < 3; i++) {
        table(user[i]);
    }
    mg_s
    int choice;
    printf("[1] - Add bonus to top 3 accounts        [any key] - Back\n\n");
    printf("  => Enter your choice: ");
    scanf("%d", &choice);
    fflush(stdin);

    if(choice == 1) {
        sortData(2);
        for (int i = 0; i < 3; i++) {
            user[i].amount *= 1.013;
        }

        FILE *db = fopen("bank.db", "w");
        fclose(db);
        for (int i = 0; i < count - 1; i++) {
            saveAccount(user[i]);
        }

        for (int i = 0; i < 3; i++) {
            table(user[i]);
        }
    } else {
        startApplication();
    }
    
}

void startLetter(char c, char u, int count) {
    int i = 0, kayn = 0;
    while(i < count) {
        if(user[i].fn[0] == c || user[i].fn[0] == u) {
            kayn = 1;
            table(user[i]);
        }
        i++;
    }
    if(!kayn) {
        printf("\nOops, There is no account starts with letter '%c'", c);
    }
}

// Challenges Suppl??mentaires
void challengesSup() {
    int ch;
    clear();
    do {
        do {
            printf("########## Optional Challenges ##########");
            mg_s
            printf("[1] - Total amount stored in the bank\n");
            printf("[2] - Average amount per Account\n");
            printf("[3] - Show accounts that stars with letter \"A\"\n");   
            printf("[4] - Show accounts that stars with letter \"B\"\n");  
            printf("[5] - Back\n");
            mg_s
            printf("  => Enter your choice: ");
            scanf("%d", &ch);
        } while(ch < 0 || ch > 6);
        
        parseData();
        float total = 0;
        int count = idGen() - 1;

        if(ch == 1) {
            int i = 0;
            while (i < count) {
                table(user[i]);
                total += user[i].amount;
                i++;
            }
            mg_s
            printf("  => The Total amount of money stored in the bank is %f\n", total);
        } else if(ch == 2) {
            int i = 0;
            while (i < count) {
                table(user[i]);
                total += user[i].amount;
                i++;
            }
            mg_s
            printf("  => The Average Amount per account in the bank is %f\n", (total / count));
        } else if(ch == 3) {
            startLetter('a', 'A', count);
        } else if(ch == 4) {
            startLetter('b', 'B', count);
        } else {
            break;
        }
    } while(ch != 5);
    startApplication();
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
    printf("[4] - Display.\n");
    printf("[5] - Loyalty.\n");
    printf("[6] - Quite.\n");

    printf("[7] - Sup ;).\n");
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
            break;
        case 4:
            displayMenu();
            break;
        case 5:
            reprise();
            break;
        case 6:
            break;
        case 7:
            challengesSup();
            break;
        default:
            goto invalid;
    }

    printf("Have a good day :)");
}