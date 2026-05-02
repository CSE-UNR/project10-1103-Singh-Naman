//Author: Naman Singh
//Project 10

#include <stdio.h>
#include <stdbool.h>

#define WORDLENGTH 5
#define MAXGUESSES 6

void loadWord(char word[]);
void lowercase(char str[]);
bool isLetter(char c);
bool isFive(char guess[]);
bool hasWon(char guess[], char word[]);
void compareWords(char guess[], char word[], char output[], char pointers[]);
void board(char guesses[][WORDLENGTH + 1], char outputs[][WORDLENGTH + 1], char pointers[][WORDLENGTH + 1], int count);

int main(){
	char word[WORDLENGTH + 1];
	char guess[WORDLENGTH + 1];
	char guesses[MAXGUESSES][WORDLENGTH + 1];
	char outputs[MAXGUESSES][WORDLENGTH + 1];
	char pointers[MAXGUESSES][WORDLENGTH + 1];
	int attempts = 0;
	bool won = false;
	loadWord(word);
	
	while(attempts < MAXGUESSES && !won){
		printf("GUESS %d! Enter your guess: ", attempts + 1);
		scanf("%s", guess);
		lowercase(guess);
		
		while(!isFive(guess)){
			printf("Your guess must be 5 letters long.\n");
			printf("Please try again: ");
			scanf("%s", guess);
			lowercase(guess);
		}
		for(int i = 0; i <= WORDLENGTH; i++){
			guesses[attempts][i] = guess[i];
		}
		compareWords(guess, word, outputs[attempts], pointers[attempts]);
		printf("====================================================\n");
		board(guesses, outputs, pointers, attempts + 1);
		
		if(hasWon(guess, word)){
			won = true;
		}
		else{
			attempts++;
		}
	}
	printf("====================================================");
	if(won){
		printf("\n");
		printf("                       %s\n", outputs[attempts]);
		printf("               You won in %d guesses!\n", attempts+1);
		printf("                       Nice!\n");
	}
	else{
		printf("\n");
		printf("             You lost, better luck next time!\n");
	}
	return 0;
}
void loadWord(char word[]){
	FILE *fptr = fopen("word.txt", "r");
	if(fptr != NULL){
		fscanf(fptr, "%s", word);
		fclose(fptr);
	}
}
void lowercase(char str[]){
	for(int i = 0; str[i] != '\0'; i++){
		if(str[i] >= 'A' && str[i] <= 'Z'){
			str[i] = str[i] + 32;
		}
	}
}
bool isLetter(char c){
	return(c >= 'a' && c <= 'z');
}
bool isFive(char guess[]){
	int length = 0;
	while(guess[length] != '\0'){
		if(!isLetter(guess[length])){
			return false;
		}
		length++;
	}
	if(length == WORDLENGTH){
		return true;
	}
	else{
		return false;
	}
}
bool hasWon(char guess[], char word[]){
	int i = 0;
	bool same = true;
	while(i < WORDLENGTH && same){
		if(guess[i] != word[i]){
			same = false;
		}
		i++;
	}
	return same;
}
void compareWords(char guess[], char word[], char output[], char pointers[]){
	for(int i = 0; i < WORDLENGTH; i++){
		output[i] = guess[i];
		pointers[i] = ' '; 
	}
	output[WORDLENGTH] = '\0';
	pointers[WORDLENGTH] = '\0';
	for(int i = 0; i < WORDLENGTH; i++){
		if(guess[i] == word[i]){
			output[i] = guess[i] - 32;
		}
	}
	for(int i = 0; i < WORDLENGTH; i++){
		if(guess[i] != word[i]){
			int j = 0;
			bool found = false;
			while(j < WORDLENGTH && !found){
				if(guess[i] == word[j] && i != j){
					pointers[i] = '^';
					found = true;
				}
				j++;
			}
		}
	}
}
void board(char guesses[][WORDLENGTH + 1], char outputs[][WORDLENGTH + 1], char pointers[][WORDLENGTH + 1], int count){
	for(int i = 0; i < count; i++){
		printf("%s\n", outputs[i]);
		bool hasPointer = false;
		
		for(int j = 0; j < WORDLENGTH; j++){
			if(pointers[i][j] == '^'){
				hasPointer = true;
			}
		}
		if(hasPointer){
			printf("%s\n", pointers[i]);
		}
		printf("\n");
	}
}
