# working roadMap

> 11 / 21 / 2021: planing and start working - 11:59PM finish the first day, repport Done

the whole project is a bank system that can create and store users, make operations, show account details and more.

first I have to transfer the big problem into small tasks todo. I like functional programming paradigm so I'll create each tesk in it's own function

- first functions is `startApplication` that will show the first menu, I'll store the user's choices and call other functions for each choice:
  - create account
  - create multiple accounts
  - operations
  - display
  - loyality
  - quite

## create account:

this function `createAccount` will show a new menu to create account, take infos from the user then store this in a structure
then save the infos in a local database (my first time but I'll choose .db file, wanna know why, IDK hh i just like the extension)

to save infos I have create a local db file and a function to write the infos in that file, that function is `saveAccount` function and I'll take an object as argument where I'm storing the users infos then close the file
BUT: before storing data I have to generate a uniq ID to each account, I'm lazy to think of something else than so I'll generate the id based on the number of lines in the db (i break the line after each insertion of data)

**_PCode_**:

```c
void createAccount(int i) {
    clear(); // clear the terminal
    createAccountHeader // add some fancy headers
    mg_s // margins between header and content
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

    newAccount acc = {firstName, lastName, cin, amount};
    saveAccount(acc);
}

// after a moment of searching in stackOverflow I found a way to count lines of a file
int idGen() {
    char buffer[100];
    int id = 1;
    FILE *f = fopen("bank.db", "r");
    while(fgets(buffer, 100, f)){
        id++;
    }
    fclose(f);
    return id;
}

// then create saveAccount function
void saveAccount(newAccount acc) {
    FILE *db = fopen("bank.db", "a");

    // generate the id of the account based on the number of lines
    fprintf(db, "%d:%s-%s-%s-%s\n", idGen(), acc.fn, acc.ln, acc.cin, acc.amount);
    fclose(db);
}
```
after creating account all the data will be stored in the db file (each user in each line)

## create multiple accounts:
simple function that will ask for a count of account that the user wants to creat then call the `createAccount` multiple times
```c
void createMultipleAccount() {
    int count;
    start:
    clear();
    mg_s

    createMultipleAccountHeader
    mg_s
    printf("=> please enter how much account you want to create: ");
    scanf("%d", &count);
    fflush(stdin); // cleare the buffer in case of unexpected input
    while (!count) {
        goto start;
    }
    for(int i = 1; i <= count; i++) {
        createAccount(i);
    } 
}
```
