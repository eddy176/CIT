#ifndef rps_h
#define rps_h

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>


void initializeRandomNumbers();
int getRandomPlayerChoice();
int getUserPlayerChoice( std::istream& input_stream, std::ostream& output_stream );
int determineWinner( int user_choice, int random_choice );
void displayMatchResults( std::ostream& output_stream, int user_choice, int random_choice, int winner );
void displayStatistics( std::ostream& output_stream, int number_user_wins, int number_user_losses, int number_user_ties );
bool askUserIfGameShouldContinue( std::istream& input_stream, std::ostream& output_stream );

#endif
