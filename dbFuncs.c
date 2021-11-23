#include "ucode.h" 

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

void saveAccount(char *fn, char *ln, char *cin, char *amount) {
    FILE *db = fopen("bank.db", "a");
    newAccount acc = {fn, ln, cin, amount};
    //generate the id of the account based on the number of lines
    fprintf(db, "%d|%s|%s|%s|%s\n", idGen(), acc.fn, acc.ln, acc.cin, acc.amount);
    fclose(db);
}

char *parseData() {
    int i = 0;
    char data[50][100];
    FILE *db = fopen("bank.db", "r");
    while (fgets(data[i], 100, db)) {
        i++;
    }
    i = 0;
    while (i < 2) {
        printf("%s", data[i]);
        i++;
    }
    

}