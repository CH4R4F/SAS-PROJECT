# working roadMap

> 11 / 21 / 2021: planing and start working

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
void createAccount() {
    // variables to store users infos (fn, ln, cin, amount)
    // ask for infos and store inputs
    .
    .
    .
    // create a structure from that database
    struct Account acc = {fn, ln, cin, amount};
    saveAccount(acc);
}

// after a moment of searching in stackOverflow I found a way to count lines of a file

int idGen(){
    // max character in a line (string)
    int id = 1;

    // open file in mode of reading
    FILE *f = fopen("bank.db", "r");

    // reade at least 100 char in the line, store it in a variable, then increment a counter.
    // when there is no line left then stop the loop
    while(fgets(buffer, 100, f)){
        id++;
    }
    // close the file and return the number of lines
    fclose(f);
    return id;
}

// then create saveAccount function
void saveAccount(newAccount acc) {

    // open the file in append mode and store its adress in a pointer
    // add the new data using fprintf() function
    fprintf(db, "%d:%s-%s-%s-%s\n", idGen(), acc.fn, acc.ln, acc.cin, acc.amount);
    fclose(db);
}
```
