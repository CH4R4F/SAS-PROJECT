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

void saveAccount(newAccount acc) {
    FILE *db = fopen("bank.db", "a");

    // generate the id of the account based on the number of lines
    fprintf(db, "%d:%s-%s-%s-%s\n", idGen(), acc.fn, acc.ln, acc.cin, acc.amount);
    fclose(db);
}