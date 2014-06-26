#include <iostream>
#include "./poker.hpp"
#include "./gofish.hpp"


char choose_game();

int main() {
	game *g;
	char game_choice;
	
	game_choice = choose_game();
	
	if (game_choice == 'p')
		g = new poker;
	else if(game_choice == 'g')
		g = new gofish;
		
	g -> play();
	return 0;
}

char choose_game() {
	char letter;
	
	cout << "To play poker, please enter a p. To play go fish, please "
		<< "enter a g." << endl;
	cout << "Please enter a letter now: ";
	cin >> letter;
	
	if((letter != 'g') && (letter != 'p'))
		letter = choose_game();
	
	return letter;
	
}
