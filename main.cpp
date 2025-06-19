#include <SFML\Graphics.hpp>
#include <iostream>
using namespace std;

char board[3][3] = {
	{' ', ' ', ' '},
	{' ', ' ', ' ' },
	{' ', ' ', ' '}
};
char XorY = 'X';
int turn = 0;
string name = "player1";
string display_on_window = "It's " + name + "'s turn";
bool still_playing = true;

void winner() {
	for (int i = 0; i < 3; i++) {
		bool win = true;
		// We compare the 2 remaining elements with the first in the each row
		for (int j = 1; j < 3; j++) {
			if (board[i][j] != board[i][0]) {
				win = false;
				break;
			}
		}
		if (win && board[i][0] != ' ') { still_playing = false; break; }
		// We compare the 2 remaining elements with the first in the each column
		win = true;
		for (int j = 1; j < 3; j++) {
			if (board[j][i] != board[0][i]) {
				win = false;
				break;
			}
		}
		if (win && board[0][i] != ' ') { still_playing = false; break; }
	}
	// Win with a diagonal X or O
	if (board[1][1] != ' ') {
		if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) still_playing = false;
		if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) still_playing = false;
	}
	
}

void tie() {
	bool there_is_tie = true;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == ' ') there_is_tie = false;
		}
	}
	if (still_playing && there_is_tie) {
		still_playing = false;
		display_on_window = "Tie!";
	}
}

void your_turn()   {
	// Before we start, we should know who will play (player1 or 2)
	if (still_playing) turn++;
	if (turn % 2 == 0) {
		name = "player1";
		XorY = 'X';
	}
	else {
		name = "player2";
		XorY = 'O';
	}
}

void displayBoard() {
	system("cls");
	for (int i = 0; i < 3; i++) {
		if (i) {
			cout << "___|___|___\n";
			cout << "   |   |   \n";
		}
		cout << ' ';
		for (int j = 0; j < 3; j++) {
			if (j) cout << " | ";
			cout << board[i][j];
		}
		cout << '\n';
	}
	if (still_playing) { 
		display_on_window = "It's " + name + "'s turn";
	}
	else { 
		if (display_on_window != "Tie!")
		display_on_window = name + " won the game.";
	}
	cout << display_on_window;
}


int main() {
	displayBoard();
	sf::RenderWindow win(sf::VideoMode(510, 550),"Tic-Tac-Toe");
	win.setFramerateLimit(30);

	//states
	bool press[3][3] = { false };
	bool restart = false;
	bool button1_pressed = false;

	//variables

	//insert a font
	sf::Font fo;
	if (!fo.loadFromFile("arial.ttf")) {
		cout << "Error loading font\n";
	};

	// load a texture
	sf::Texture x_icon;
	x_icon.loadFromFile("x_red.png");

	sf::Texture o_icon;
	o_icon.loadFromFile("o_blue.png");

	sf::Texture new_button;
	new_button.loadFromFile("new_button.png");
	
	// insert a text 
	sf::Text title;
	title.setFont(fo);
	title.setString("Tic-Tac-Toe game");
	title.setPosition(0,0);
	title.setFillColor(sf::Color::Black);
	title.setStyle(sf::Text::Underlined);

	//To print who should play and who wins
	sf::Text what_to_say;
	what_to_say.setFont(fo);
	what_to_say.setString(display_on_window);
	what_to_say.setFillColor(sf::Color::Black);

	sf::Text new_game;
	new_game.setFont(fo);
	new_game.setString("New Game");
	new_game.setCharacterSize(28);
	new_game.setFillColor(sf::Color::Black);


	//shapes
	sf::RectangleShape line1(sf::Vector2f(5, 310));
	line1.setPosition(200, 100);
	line1.setFillColor(sf::Color::Black);

	sf::RectangleShape line2(sf::Vector2f(5, 310));
	line2.setPosition(305, 100);
	line2.setFillColor(sf::Color::Black);

	sf::RectangleShape line3(sf::Vector2f(310, 5));
	line3.setPosition(100, 200);
	line3.setFillColor(sf::Color::Black);

	sf::RectangleShape line4(sf::Vector2f(310, 5));
	line4.setPosition(100, 305);
	line4.setFillColor(sf::Color::Black);

	//Draw the board
	//vector<vector<RectangleShape>>the_board(3, vector<RectangleShape>(3));
	sf::RectangleShape the_board(sf::Vector2f(310, 310));
	the_board.setPosition(sf::Vector2f(100, 100));
	the_board.setOutlineThickness(5);
	the_board.setOutlineColor(sf::Color::Black);

	// The new game button
	sf::RectangleShape button1(sf::Vector2f(150, 150));
	button1.setFillColor(sf::Color::Red);
	//button1.setTexture(&new_button);
	float temp = the_board.getPosition().x + the_board.getSize().x / 2 - button1.getSize().x / 2.0;
	button1.setPosition(temp, 450);
	float n_x = button1.getPosition().x + button1.getGlobalBounds().width / 2 - new_game.getGlobalBounds().width / 2;
	float n_y = button1.getPosition().y + button1.getGlobalBounds().height / 2 - new_game.getGlobalBounds().height / 2 - 75;
	new_game.setPosition(n_x, n_y);


	// To set the X O icons
	sf::Sprite rectangle[3][3];
	for (int i = 0, x = 100; i < 3; i++) {
		// iterate each column at once
		for (int j = 0, y = 100; j < 3; j++) {
			rectangle[j][i].setPosition(x, y);
			y += 105;
		}
		x += 105;
	}


	while (win.isOpen()) {
		sf::Event eve;
		while (win.pollEvent(eve)) {
			if (eve.type == sf::Event::Closed) {
				win.close();
			}
			else if (eve.type == sf::Event::MouseButtonPressed) {
				// If the mouse button pressed
				if (still_playing) {
					if (eve.mouseButton.x >= 100 && eve.mouseButton.x <= 200) {
						if (eve.mouseButton.y >= 100 && eve.mouseButton.y <= 200) {
							press[0][0] = true;
						}
						else if (eve.mouseButton.y >= 205 && eve.mouseButton.y <= 305) {
							press[1][0] = true;
						}
						else if (eve.mouseButton.y >= 310 && eve.mouseButton.y <= 410) {
							press[2][0] = true;
						}
					}
					else if (eve.mouseButton.x >= 205 && eve.mouseButton.x <= 305) {
						if (eve.mouseButton.y >= 100 && eve.mouseButton.y <= 200) {
							press[0][1] = true;
						}
						else if (eve.mouseButton.y >= 205 && eve.mouseButton.y <= 305) {
							press[1][1] = true;
						}
						else if (eve.mouseButton.y >= 310 && eve.mouseButton.y <= 410) {
							press[2][1] = true;
						}
					}
					else if (eve.mouseButton.x >= 310 && eve.mouseButton.x <= 410) {
						if (eve.mouseButton.y >= 100 && eve.mouseButton.y <= 200) {
							press[0][2] = true;
						}
						else if (eve.mouseButton.y >= 205 && eve.mouseButton.y <= 305) {
							press[1][2] = true;
						}
						else if (eve.mouseButton.y >= 310 && eve.mouseButton.y <= 410) {
							press[2][2] = true;
						}
					}
				}
				if (button1.getGlobalBounds().contains(eve.mouseButton.x, eve.mouseButton.y)) {
					button1_pressed = true;
					restart = true;
				}
			}
			else if (eve.type == sf::Event::MouseButtonReleased) {
				restart = false;
				button1_pressed = false;
			}
		}
			

		// Logic
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (press[i][j] && board[i][j] == ' ') {
					rectangle[i][j].setTexture((XorY == 'X' ? x_icon : o_icon));
					board[i][j] = XorY;
					winner();
					tie();
					your_turn();
					displayBoard(); // To see what is happening inside
					what_to_say.setString(display_on_window);
				}
			}
		}
		
		if (button1_pressed == true) {
			button1.setSize(sf::Vector2f(140, 50));
			button1.setOrigin(button1.getSize().x / 2.0, button1.getSize().y / 2.0);
			float temp = the_board.getPosition().x + the_board.getSize().x / 2;
			button1.setPosition(temp, 460);
			new_game.setCharacterSize(25);
		}
		if (button1_pressed == false) {
			button1.setSize(sf::Vector2f(160, 60));
			button1.setOrigin(button1.getSize().x / 2.0, button1.getSize().y / 2.0);
			float temp = the_board.getPosition().x + the_board.getSize().x / 2;
			button1.setPosition(temp, 460);
			new_game.setCharacterSize(28);
		}
		

		// rendering
		win.clear(sf::Color::White);

		// draw something
		if (restart) {
			// when we press the new game button we return to the begining
			XorY = 'X';
			turn = 0;
			name = "player1";
			display_on_window = "It's " + name + "'s turn";
			what_to_say.setString(display_on_window);
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					press[i][j] = false;
					board[i][j] = ' ';
				}
			}
			still_playing = true;
		}
		win.draw(the_board);
		win.draw(line1);
		win.draw(line2);
		win.draw(line3);
		win.draw(line4);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (press[i][j]) win.draw(rectangle[i][j]);
			}
		}
		win.draw(what_to_say);
		win.draw(button1);
		win.draw(new_game);

		win.display();
	}
	return 0;
}