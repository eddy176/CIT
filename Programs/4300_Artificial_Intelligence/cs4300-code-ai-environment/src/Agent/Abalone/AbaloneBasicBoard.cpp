#include <ai_abalone.h>

#include <cstdio>
#include <iostream>

namespace ai {
	namespace Abalone {
		
		BasicBoard::BasicBoard() : number_of_turns(0), legal_moves_valid(false), legal_moves(0), last_moves(2), player_times(2) {
			for (unsigned int i=0; i < 11; i++) {
				for (unsigned int j=0; j < 11; j++) {
					board.hole[i][j] = -1;
				}
			}
			InitBoard();
		}

		BasicBoard::BasicBoard(const BasicBoard &board_in)
			: number_of_turns(board_in.number_of_turns),
			  legal_moves_valid(board_in.legal_moves_valid),
			  legal_moves(board_in.legal_moves),
			  last_moves(board_in.last_moves),
			  player_times(board_in.player_times) {
			board = board_in.board;
		}

		BasicBoard::BasicBoard(const std::string &board_str_in) : legal_moves_valid(false), legal_moves(0), last_moves(2), player_times(2){
			SetBoardString(board_str_in);
		}
		
		BasicBoard::~BasicBoard(){
		}
		
		bool BasicBoard::Move(int player, const MoveData &move_in, double seconds_in) {
			for (unsigned int m = 0; m < move_in.number; m++) {
				int from_x = move_in.from_x[m];
				int from_y = move_in.from_y[m];
				int to_x = move_in.to_x[m];
				int to_y = move_in.to_y[m];
				board.hole[to_x][to_y] = player;
				board.hole[from_x][from_y] = 0;
			}
			
			board.player_turn = ((board.player_turn)%board.num_players) + 1;
			last_moves[player-1]    = move_in;
			player_times[player-1] += seconds_in;
			
			number_of_turns++;
			legal_moves_valid = false;
			return true;
		}
		
		bool BasicBoard::Move(int player, const MoveData &move_in) {
			return Move(player, move_in, 0.);
		}

		int BasicBoard::HaveWinner() const {
			if (board.p2_count < 9)
				return 1;
			if (board.p1_count < 9)
				return 2;
			return false;
		}

		const std::vector<MoveData>& BasicBoard::DetermineLegalMoves(int player) {
			int x, y, a; //, b, search_x, search_y;
			std::array<int, 5> from_x = {{0, 0, 0, 0, 0}};
			std::array<int, 5> from_y = {{0, 0, 0, 0, 0}};
			std::array<int, 5> to_x = {{0, 0, 0, 0, 0}};
			std::array<int, 5> to_y = {{0, 0, 0, 0, 0}};
			std::array<int, 5> try_x = {{0, 0, 0, 0, 0}};
			std::array<int, 5> try_y = {{0, 0, 0, 0, 0}};
			// left, right, up, down, down-right, up-right, down-left, up-left
			int x_offset[] = {0, 0, -1, 1, 1, -1, 1, -1}; // negative up, positive down
			int y_offset[] = {-1, 1, 0, 0, 1, 1, -1, -1}; // negative left, positive right
		
			if (legal_moves_valid)
				return legal_moves;

			legal_moves.resize(0, MoveData(from_x, from_y, to_x, to_y, 0));

			for (x = 0; x < 11; x++) {
				for (y = 0; y < 11; y++) {
					if (board.hole[x][y] == player) {
						for (a = 0; a < 6; a++) {
							// ONE MARBLE
							try_x[0] = x + x_offset[a];
							try_y[0] = y + y_offset[a];							
							if (Available(try_x[0], try_y[0])) {
								// push into (empty)
								from_x[0] = x;
								from_y[0] = y;
								to_x[0] = try_x[0];
								to_y[0] = try_y[0];
								legal_moves.push_back(MoveData(from_x, from_y, to_x, to_y, 1));
							}
							
							// TWO MARBLES
							/*
							try_x[1] = try_x[0] + x_offset[a];
							try_y[1] = try_x[0] + y_offset[a];
							if (board.hole[try_x[0]][try_y[0]] == player && Available(try_x[1], try_y[1])) {
								// push into (P, empty)
								from_x[1] = try_x[0];
								from_y[1] = try_y[0];
								to_x[1] = try_x[1];
								to_y[1] = try_y[1]; 
								legal_moves.push_back(MoveData(from_x, from_y, to_x, to_y, 1));
							}
							else if (Available(try_x[0], try_y[0])) {
								// for each marble around the start position
								for (b = 0; b < 6; b++) {
									search_x = x + x_offset[b];
									search_y = y + y_offset[b];
									// if the marble is owned by the player
									if (board.hole[try_x[search_x]][search_y] == player) {
										try_x[1] = search_x + x_offset[a];
										try_y[1] = search_y + y_offset[a];
										// try moving the second marble in the same direction as the first marble
										if (Available(try_x[1], try_y[1])) {
											// push into (empty, empty) || (empty, P)
											from_x[1] = try_x[0];
											from_y[1] = try_y[0];
											to_x[1] = try_x[1];
											to_y[1] = try_y[1]; 
											legal_moves.push_back(MoveData(from_x, from_y, to_x, to_y, 1));
										}
									}
								}
							}
							*/
							
							// THREE MARBLES
							// FOUR MARBLES
							// FIVE MARBLES
							
						}
					}
				}
			}
			
			legal_moves_valid = true;
			return legal_moves;
		}

		const std::vector<MoveData>& BasicBoard::GetLastMoves() const {
			return last_moves;
		}

		const std::vector<double>& BasicBoard::GetPlayerTimes() const {
			return player_times;
		}

		unsigned int BasicBoard::GetTotalMoves() const {
			return number_of_turns;
		}

		const BoardData& BasicBoard::GetBoard() const {
			return board;
		}
		
		void BasicBoard::SetBoard(const BoardData &board_in) {
			board = board_in;
		}

		std::string BasicBoard::GetPrintableBoardString() const {
			std::string board_string = "";
			char tmp[32];
			
			for (int x=0; x < 11; x++) {
				// row numbers
				if (x == 0) {
					std::sprintf(tmp, "%s", "        0 1 2 3 4 5 6 7 8 9 10\n");
					board_string += tmp;
					std::sprintf(tmp, "%s", "        _ _ _ _ _ _ _ _ _ _ _\n");
					board_string += tmp;
					std::sprintf(tmp, "%2d|%s", x, "     ");
				}
				// column numbers
				else if (x < 10)
					std::sprintf(tmp, "%2d|", x);
				else if (x == 10)
					std::sprintf(tmp, "%2d|%s", x, "     ");
				board_string += tmp;
				
				for (int y=0; y < 11; y++) {
					// append an space for any invalid hole
					if (board.hole[x][y] == -1)
						if (y==0 && (x>0 && x<10))
							if (x==4 || x == 6)
								std::sprintf(tmp, " %s", "-");
							else if (x==5)
								std::sprintf(tmp, "%s ", "-");
							else
								std::sprintf(tmp, "%s ", " ");
						else
							std::sprintf(tmp, "%s ", "-");
					// add spacing for board formatting
					else {
						if ((x==4 || x==6) && y==1)
							std::sprintf(tmp, " %d ", board.hole[x][y]);
						else if ((x==3 || x==7) && y==1)
							std::sprintf(tmp, "- %d ", board.hole[x][y]);
						else if ((x==2 || x==8) && y==1)
							std::sprintf(tmp, " - %d ", board.hole[x][y]);
						else if ((x==1 || x==9) && y==1)
							std::sprintf(tmp, "  - %d ", board.hole[x][y]); 
						else
							std::sprintf(tmp, "%d ", board.hole[x][y]);
					}
					board_string += tmp;
				}
				board_string += "\n";
			}
			return board_string;
		}
		
		std::string BasicBoard::GetBoardString() const {
			std::string board_string = "";
			char tmp[16];
			
			for (unsigned int x=0; x < 11; x++) {
				for (unsigned int y=0; y < 11; y++) {
					std::sprintf(tmp, "%d,", board.hole[x][y]);
              		board_string += tmp;
				}
			}
			std::sprintf(tmp, "%d,", board.num_players);
			board_string += tmp;
			
			std::sprintf(tmp, "%d,", board.player_turn);
			board_string += tmp;
			
			std::sprintf(tmp, "%d,", number_of_turns);
			board_string += tmp;
			
			return board_string;
		}
		
		void BasicBoard::SetBoardString(const std::string &board_str_in) {
      		const char *str = board_str_in.c_str();
      		
      		for (unsigned int x=0; x < 11; x++) {
      			for (unsigned int y=0; y < 11; y++) {
      				std::sscanf(str, "%d,", &board.hole[x][y]);
      				str = index(str, ',');
      				str++;
      			}
      		}
      		
      		std::sscanf(str, "%d,", &board.num_players);
      		str = index(str, ',');
      		str++;
      		std::sscanf(str, "%d,", &board.player_turn);
      		str = index(str, ',');
      		str++;
      		std::sscanf(str, "%d,", &number_of_turns);
      		str = index(str, ',');
      		str++;
		}

		void BasicBoard::InitBoard() {
			for (int x=0; x<11; x++) {
				for (int y=0; y<11; y++) {
					// Player 1
					if ( (x==1 && y>0 && y<6) || (x==2 && y>0 && y<7) || (x==3 && y>2 && y<6) )
						board.hole[x][y] = 1;
					// Player 2
					else if ( (x==9 && y>0 && y<6) || (x==8 && y>0 && y<7) || (x==7 && y>2 && y<6) )
						board.hole[x][y] = 2;
					// Empty
					else if ( ((x==4 || x==6) && y>0 && y<9) || (x==5 && y>0 && y<10) || (x==3 && ((y>0 && y<3) || (y>5 && y<8))) || (x==7 && ((y>0 && y<3) || (y>5 && y<8))))
						board.hole[x][y] = 0; 
				}
			}
			board.num_players = 2;
			board.player_turn = 1;
			board.p1_count = 16;
			board.p2_count = 16;
		}
		
		void BasicBoard::SetNumPlayer(int num_player_in) {
			board.num_players = num_player_in;
		}
		
		bool BasicBoard::Usable(int x, int y) const {
			if (board.hole[x][y] == -1)
				return false;
			return true;
		}

	  	bool BasicBoard::Occupied(int x, int y) const {
	  		if (Usable(x, y) && board.hole[x][y] != 0)
	  			return true;
	  		return false;
	  	}

	  	bool BasicBoard::Available(int x, int y) const {
	  		if (Usable(x, y) && board.hole[x][y] == 0)
	  			return true;
	  		return false;
	  	}

	}
}

// TESTING
/*
int main() {
	
	ai::Abalone::BasicBoard test;
	int player = 1;
	const std::vector<ai::Abalone::MoveData> legal_moves = test.DetermineLegalMoves(player);
	
	std::cout << "Legal Moves: Player "<< player << std::endl;
	for (unsigned int i = 0; i < legal_moves.size(); i++) {
		std::cout << i << ": [" << legal_moves[i].number << "] {";
		for (int j = 0; j < legal_moves[i].number; j++) {
			std::cout << "(" << legal_moves[i].from_x[j] <<  "," << legal_moves[i].from_y[j] << ") => (" << legal_moves[i].to_x[j] << "," << legal_moves[i].to_y[j] << "),";
		}
		std::cout << "}" << std::endl;
	}

	return 0;
}
*/
