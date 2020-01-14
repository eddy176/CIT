#include "rps.h"

void initializeRandomNumbers(){
	std::srand(time(0));
}

int getRandomPlayerChoice(int foo, int bar){
	int cChoice = (rand() % 3) + 1;
	return 0;
}

int getUserPlayerChoice(std::istream& input_stream, std::ostream& output_stream){
	std::string cInput;
	output_stream << "Choice? (rock, paper, scissors). " << std::endl;
	input_stream >> cInput;
	while (cInput != "rock" && cInput != "paper" && cInput !=  "scissors"){
	  output_stream << "Choice? (rock, paper, scissors). " << std::endl;
	  input_stream >> cInput;
	  if (cInput != "rock" && cInput != "paper" && cInput != "scissors"){
	    output_stream << "Please input proper choice. (rock, paper, scissors)" << std::endl;
    }
	}
}
	if (cInput == "rock"){
	    output_stream << "You chose rock" << std::endl;
	    return 1;
	    }
	else if (cInput == "paper"){
	    output_stream << "You chose paper" << std::endl;
	    return 2;
	    }
	else if (cInput == "scissors"){
	    output_stream << "You chose scissors" << std::endl;
	    return 3;
	    }
	else{
	    return 0;
	}
}

int determineWinner(int user_choice, int random_choice){
	if (user_choice == 1){
		if (random_choice == 2){
			return 12;
		}
		if (random_choice == 3){
			return 11;
		}
		if (random_choice == 1){
		    return 13;
		}
	}
	else if (user_choice == 2){
		if (random_choice == 3){
			return 12;
		}
		if (random_choice == 1){
			return 11;
		}
		if (random_choice == 2){
		    return 13;
		}
	}
	else if (user_choice == 3){
		if (random_choice == 1){
			return 12;
		}
		if (random_choice == 2){
			return 11;
		}
		if (random_choice == 3){
		    return 13;
		}
	}
	return 0;
}

void displayMatchResults( std::ostream& output_stream, int user_choice, int random_choice, int winner ){
    std::string user;
    std::string cpu;
    if (user_choice == 1){
        user = "rock";
    }
    else if (user_choice == 2){
        user = "paper";
    }
    else if (user_choice == 3){
        user = "scissors";
    }
    if (random_choice == 1){
        cpu = "rock";
    }
    else if (random_choice == 2){
        cpu = "paper";
    }
    else if (random_choice == 3){
        cpu = "scissors";
    }
    std::string win;
    if (winner == 11){
        win = " win.\n";
    }
    else if (winner == 12){
        win = " lose.\n";
    }
    else if (winner == 13){
        win = " tie.\n";
    }

    output_stream << "You chose " << user << ". Computer chose " << cpu << ". You" << win;
}

void displayStatistics( std::ostream& output_stream, int number_user_wins, int number_user_losses, int number_user_ties ){
    output_stream << "Win: " << number_user_wins << "  Lose: " << number_user_losses << "  Tie: " << number_user_ties << "\n";
}

bool askUserIfGameShouldContinue( std::istream& input_stream, std::ostream& output_stream ){
    std::string pChoice;
    output_stream << "Play again? ";
    input_stream >> pChoice;
    if (pChoice[0] == 'y' || pChoice[0] == 'Y'){
        return true;
    }
    return false;

}
