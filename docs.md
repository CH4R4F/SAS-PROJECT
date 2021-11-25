# working roadMap

> 11 / 21 / 2021: planing and start working - 11:59PM finish the first day, repport Done [read here](#day-2)

> 11 / 22 / 2021: fix bugs, add features and start planing for tomorrow, 1:30AM repport Done [read here](#day-1)

> 11 / 23 / 2021: optimize the code, parse data from db and use it to make operations [read here](#day-3)

### day 1

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

### day 2

I finished the function to create multiple account and start working on the operations, I had to fix bugs and plan for how to parse data from the db so I can deal with money transformations, I added som functionalities to check if there are any accounts in the db before doing any operation, now I have to find an idea to parse data from the db and work on it, I'll check for the right account by the `CIN`, also check if there is enough money to make operations or not, then I have to find a way to update the db after each operation. this is the plan for tomorrow now I have to take some rest.

### day 3

finally I did it, I make a way to parse data from the db. well there is no easy way than working with `JSON` data format, so I tried to make similar to it.
I create an array of `structs`, loop over the db and store each element in a line in it's own variable inside each struct.
**example:**

```
bank.db
1 charaf marghin cb3324 1000
```

this line have `id`, `first name`, `last name`, `cin`, and `amount`

```C
void parseData() {
    struct Account user[100];
    .
    .
    .
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
```

now I have user[] array that stores structs. in the example i have array stores struct that store file values. it looks like this:

```
//user array (مقطع توضيحي هه):
[
    {
        id = 1;
        fn = charaf;
        ln = marghin;
        cin = cb3324;
        amount = 1000;
    }
]
```

Now I can work on operations

## Operations:

operations is a menu (withdraw, deposit, back), each choice has it's own functionality
today I finished the withdraw function that take `CIN` from the user **=>** checks for the cin in the _parsed data_ **=>** if there is a cin then show a current status of the account **=>** take the amount from the user to remove from the account (ofcourse after validating that amount) **=>** remove the amount in the struct where I already found the `CIN` **=>** remoove the database **=>** loop over the parsed/updated data and sore it again.

> in case there is no account in the db then the user have to create account first, in case the cin that he types to pull from an account is not found then ask him to retry again

### bonus work today:

I have optimized the code, add some features like checking of there is an account with the same `CIN` when the user creates an account. if true then show him an alert and rescan the `CIN`

### plan for tomorrow:

the last day. I have to finish the `deposit` function, the display tasks (sorting accounts), loyality feature of the bank and try to make some of the optional challenges.

### The Last Day

YOOO, I did it. after creating the `parseData()` function everything becomes easy. starting with **deposite()**, it takes the index of the user and the count of users in the data array. I ask for amount to add to the account (_of course It have to be positive or he will enter it again_), then change the amount in the `struct` of that user, delete data from the db then create new data based on the updated data in `user` array.

## Display:

I only used one function to sort the data, first I call the `parseData()`, then I take one of 5 choices from the user, the **first** and **second** one will sort the data in acending or decending order, all this is done by `sortData()` function and it uses the **_Bubble sort Algorithm_** (the easiest one), it affects the data array so I only print infos directly to the user.
the **third** and **fourth** uses the same function as before but after sorting the array I loop over it and only show the data that has the bigger amount.
the **fifth** choice is searching by `CIN`, I only use regular loop over the array and try to find the CIN in every user. if I found it I print the data of that user, else I print error.

## Loyalty:

parse the data then sort the data array decendently and print the first 3 accounts. then if you want to give them a bonus you just enter 1 and all the 3 users will have new data (new data means overwriting the old data in the file)

> I learned too much in that project. how to deal with files (create, write and delete), how to parse and read the data from a file. learned about structs and how to deal with arrays of structs. developed my skills of thinking and planing (and googling (solving\* poblems)). I'm happy with everything I did till now.
