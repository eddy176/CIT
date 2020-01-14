#include "rps.h"
#include <iostream>
#include <string>
#include <cstdlib>

int main(){
	bool runGame = true;
	initializeRandomNumbers();
	int number_user_wins = 0;
	int number_user_losses = 0;
	int number_user_ties = 0;
	while (runGame == true){
		int random_choice = getRandomPlayerChoice();
		int user_choice = getUserPlayerChoice(std::cin, std::cout);
		int winner = determineWinner( user_choice, random_choice );
		if (winner == 11){
			number_user_wins++;
		}
		else if (winner == 12){
			number_user_losses++;
		}
		else if (winner == 13){
			number_user_ties++;
		}
		displayMatchResults(  std::cout, user_choice, random_choice, winner );
		displayStatistics(  std::cout,  number_user_wins,  number_user_losses,  number_user_ties );
		runGame = askUserIfGameShouldContinue(  std::cin,  std::cout );
	}

return 0;
}
