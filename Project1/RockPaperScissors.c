/*
 * Twesha Mitra- Project 1
 * Rock Paper Scissors
 * Simulates a Rock, Paper, Scissors game with the user. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
char play[100];
int num_of_games; 
int games_won_by_computer;
int games_won_by_user=0;
char user_choice[100];
int main() {
	srand((unsigned int) time (NULL));
		printf("Welcome to Rock, Paper, Scissors!\n");
		printf("\n");
		printf("Would you like to play?");
		scanf("%s", play);
		printf("\n");
		if(strcasecmp(play, "no")==0){
			exit(0);
			}
		do{
			num_of_games=0;
			games_won_by_computer=0;
			games_won_by_user=0;
				
			while((num_of_games<5) && (games_won_by_computer<3) && (games_won_by_user<3)){
				printf("What is your choice?");
				scanf("%s", user_choice);
				int rand_number=rand() % 3; 
					if(rand_number==0){
						if(strcasecmp(user_choice,"paper")==0){
							printf("The computer chooses rock. You win this game!\n");
							games_won_by_user++;
						}
						if(strcasecmp(user_choice,"scissor")==0){
							printf("The computer chooses rock. You lose this game!\n");
							games_won_by_computer++;
						}
						if(strcasecmp(user_choice,"rock")==0){
							printf("The computer chooses rock. It's a tie!\n");
						}
					}
					if(rand_number==1){
						if(strcasecmp(user_choice,"paper")==0){
							printf("The computer chooses scissor. You lose this game!\n");
							games_won_by_computer++;
						}
						if(strcasecmp(user_choice,"scissor")==0){
							printf("The computer chooses scissor. It's a tie!\n");
						}
						if(strcasecmp(user_choice,"rock")==0){
							printf("The computer chooses scissor. You win this game!\n");
							games_won_by_user++;
						}
					}
					if(rand_number==2){
						if(strcasecmp(user_choice,"paper")==0){
							printf("The computer chooses paper. It's a tie!\n");
						}
						if(strcasecmp(user_choice,"scissor")==0){
							printf("The computer chooses paper. You lose this game!\n");
							games_won_by_computer++;
						}
						if(strcasecmp(user_choice,"rock")==0){
							printf("The computer chooses paper. You win the game!\n");
							games_won_by_user++;
						}
					}
				printf("\n");
				printf("The score is now you: %d computer: %d\n", games_won_by_user, games_won_by_computer);
				printf("\n");
				num_of_games++;
			}
			if(num_of_games==5 || games_won_by_user==3 || games_won_by_computer==3){
				if(games_won_by_computer>games_won_by_user){
					printf("The computer wins the tournament!\n");
					printf("\n");
				}
				else if(games_won_by_computer<games_won_by_user){
					printf("You win the tournament!\n");
					printf("\n");
				}
				else if(games_won_by_computer == games_won_by_user) {
					printf("The tournament was tied!\n");
					}
				printf("Would you like to play again?\n");
				printf("\n");
				scanf("%s",play);
					if(strcasecmp(play,"no")==0){
						printf("Thanks for playing!\n");
						}
				}
			}while(strcasecmp(play,"yes")==0);
	}
