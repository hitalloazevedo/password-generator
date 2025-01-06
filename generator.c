#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

char generate_alpha_character(){
    return 97 + (rand() % 26);
}

char generate_alpha_upper_character(){
    return 97 + (rand() % 26) - 32;
}

char generate_number_character(){
    return (rand() % 10) + 48;
}

char generate_symbol_character(){

    char symbols[] = "!@#$%^&*()-_=+[]{}|;:',.<>?/~`";

    return symbols[rand() % 30];
}

int int_input(char * message){

    printf("%s", message);
    int n;
    scanf("%d", &n);

    return n;
}

char char_input(char * message) {

    getchar();

    printf("%s", message);
    char c;
    scanf("%c", &c);

    return c;
}

void check_length(int password_length){
    if (password_length < 4){
        printf("The password length must be greater than 4\n");
        exit(1);
    }
}

char * generate_password(
    int password_length,  
    char * (*shuffle)(), 
    char (*generator[4])()){

    char base_password[5];
    for (int i = 0; i < 4; i++) { base_password[i] = generator[i](); }

    char * password = (char*)malloc(sizeof(char) * (password_length + 1));
    char * passwordcpy = password;

    while (strlen(password) < password_length - 4){
        *passwordcpy = generator[rand() % 4]();
        passwordcpy++;
    }

    strcat(password, base_password);

    password = shuffle(password, strlen(password));

    return password;
}

char * shuffle(char * string, int size){
    for (int i = size - 1; size > 0; size--){
        int j = rand() % i;

        char tmp = string[i];
        string[i] = string[j];
        string[j] = tmp;
    }

    return string;
}

int main(int argc, char * argv[]){

    // randomization config
    srand(time(NULL));

    // setting generators functions
    char (*generators[4]) () = { 
        generate_alpha_character, 
        generate_alpha_upper_character,
        generate_number_character, 
        generate_symbol_character 
    };

    printf("**** Password generator ****\n\n");

    int password_length = int_input("Password length (integer number): ");
    check_length(password_length);
    
    printf("Password: %s\n", generate_password(password_length, shuffle, generators));

    return 0;
}