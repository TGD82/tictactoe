#include<stdio.h>
#include<string.h>
#include <stdlib.h>

void save_result(const char *player1, const char *player2, const char *result) {
    FILE *file = fopen("game_results.txt", "a"); 
    if (file == NULL) {
        printf("Error: Unable to open file for saving results.\n");
        return;
        
    }
    if(strcmp(result, "draw") == 0){
    fprintf(file, "Player 1: %s, Player 2: %s, Result: %s \n", player1, player2, result);
    fclose(file); 
    printf("Game result saved successfully!\n");
    return;
    }
    else{

    fprintf(file, "Player 1: %s, Player 2: %s, Result: %s wins \n", player1, player2, result);
    fclose(file); 
    printf("Game result saved successfully!\n");
}
}
void view_history() {
    FILE *file = fopen("game_results.txt", "r"); 
    if (file == NULL) {
        printf("No game history found.\n");
        return;
    }

    char line[256];
    printf("Game History:\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file); 
}


int win(char array[3][3]) {
    for(int i = 0; i < 3; i++) {
        if(array[i][0] == array[i][1] && array[i][1] == array[i][2] && array[i][0] != ' '){
            return 1;
        }
        if(array[0][i] == array[1][i] && array[1][i] == array[2][i] && array[0][i] != ' '){
            return 1;
        }
    }
    if(array[0][0] == array[1][1] && array[1][1] == array[2][2] && array[0][0] != ' '){
        return 1;
    }
    if(array[0][2] == array[1][1] && array[1][1] == array[2][0] && array[0][2] != ' '){ 
        return 1;
    }
    return 0;
}

struct Details {
    char name[20];
};

int main(){
    char choice;
    printf("Welcome to Tic Tac Toe!\n");
    printf("Enter 'H' to view game history or 'N' to start a new game: ");
    scanf(" %c", &choice);
    getchar();

    if (choice == 'H' ) {
        view_history();
        return 0;
    }

    else if (choice == 'N' ){
    char array[3][3];
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            array[i][j]=' ';
            }
        }

    int demo[3][3];
    int k=1;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            demo[i][j]=k;
            k=k+1;
        }
    }
    
    struct Details player1;
    printf("Enter name of player1: ");
    fgets(player1.name, 20, stdin);
    player1.name[strcspn(player1.name, "\n")] = '\0';
    struct Details player2;
    printf("Enter name of player2: ");
    fgets(player2.name, 20, stdin);
    player2.name[strcspn(player2.name, "\n")] = '\0';

    printf("Demo Board:\n");
    for(int i=0; i<3; i++){
        printf("_______\n");
        for(int j=0; j<3; j++){
          
           printf("|%d", demo[i][j]);
        }
        printf("|\n");
    }
    printf("_______\n\n");
 
    printf("Enter the number where you want to mark your input \nie. if you choose number 1, X/O will replace 1\n\n");


    for(int i=1; i<=9; i++){
        int a;
        char turn=(i % 2 != 0) ? 'X' : 'O';
        printf("Enter the number where you want to mark %c: ", turn);
        scanf("%d",&a);
        if(1<=a && 9>=a){
            int r = (a - 1) / 3;
            int c = (a - 1) % 3;
            if(array[r][c] != ' ') {
            printf("Position already taken! Choose a different number.\n");
            i=i-1;
            
            }
            else{
                array[r][c]=turn;
            }
        }
        else if(a < 1 || a > 9) {
            printf("Invalid move! Please enter a number between 1 and 9.\n");
            i=i-1;
        }
        system("cls");
        printf("Demo Board:\n");
        for(int i=0; i<3; i++){
        printf("_______\n");
        for(int j=0; j<3; j++){
          
           printf("|%d", demo[i][j]);
        }
        printf("|\n");
        }
        printf("_______\n\n");
        printf("Current board:\n");
        for(int m=0; m<3; m++){
            printf("_______\n");
            for(int n=0; n<3; n++){
               if (array[m][n] == 'X') {
                printf("|\033[31m%c\033[0m", array[m][n]); 
               } 
               else if (array[m][n] == 'O') {
               printf("|\033[33m%c\033[0m", array[m][n]); 
               }
               else {
               printf("|%c", array[m][n]);
               } 
            }
            printf("|\n");
        }
        printf("_______\n\n");

        if(win(array)) {
            if(i%2==0){
            printf("Victory is yours, and it's been hard-won! With unmatched skill and unwavering courage, you've conquered every challenge in your path.");
            printf("You've proven that determination and strength can overcome anything.");
            printf(" Today, you stand as a true champion. Congratulations %s on this legendary achievement!\n", player2.name);
            printf("Do you wish to save the results? Press Y to save results.\n");
            char saveresults;
            while (getchar() != '\n');
            scanf("%c",&saveresults);
            if(saveresults == 'Y') save_result(player1.name, player2.name, player2.name);
            else return 0;
            }
            else{
            printf("Victory is yours, and it's been hard-won! With unmatched skill and unwavering courage, you've conquered every challenge in your path.");
            printf("You've proven that determination and strength can overcome anything.");
            printf(" Today, you stand as a true champion. Congratulations %s on this legendary achievement!\n", player1.name);
            printf("Do you wish to save the results? Press Y to save results.\n");
            char saveresults;
            while (getchar() != '\n');
            scanf("%c",&saveresults);
            if(saveresults == 'Y') save_result(player1.name, player2.name, player1.name );
            else return 0;
            }
            return 0;
        }
    }
    printf("Game over!\nResult: draw\n");
    printf("Do you wish to save the results? Press Y to save results.\n");
    char saveresults;
    while (getchar() != '\n');
    scanf("%c",&saveresults);
    if(saveresults == 'Y') save_result(player1.name, player2.name, "draw");
    else return 0;
return 0;
}
}
