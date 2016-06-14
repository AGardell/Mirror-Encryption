//Program idea taken from DailyProgrammer. "Text.txt" contains a series of '\' and '/' characters that fill a 2d array.
//The idea is that the program locates a starting point and tranverse left, right, down, or up depending on the character
//hit along the way. Used SFML libaries to implement real time conversion as the user is typing.

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <queue>
#include "Create Word.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>



void fillBottom() {
	int row = 14;
	int col = 1;
	std::string alphabet = "NOPQRSTUVWXYZ";
	for (char c : alphabet) {
		board[row][col] = c;
		col++;
	}
}

void fillLeft() {
	int row = 1;
	int col = 0;
	std::string alphabet = "ABCDEFGHIJKLM";
	for (char c : alphabet) {
		board[row][col] = c;
		row++;
	}

	fillBottom();
}

void fillRight() {
	int row = 1;
	int col = 14;
	std::string alphabet = "nopqrstuvwxyz";
	for (char c : alphabet) {
		board[row][col] = c;
		row++;
	}

	fillLeft();
}

void fillTop() {
	int row = 0;
	int col = 1;
	std::string alphabet = "abcdefghijklm";
	for (char c : alphabet) {
		board[row][col] = c;
		col++;
	}

	fillRight();
}

void fillBoard () {
	fillTop();
}

void getSymbols(std::stringstream& str, std::queue<char>& q) {
	char c;

	while (str >> std::noskipws >> c) {
		q.push(c); // push symbols into a queue including spaces to be used to fill array.
	}
	
}

void populateBoard(std::queue<char>& q) {
	for (int x = 1; x < 14; ++x) {
		for (int y = 1; y < 14; ++y) {
			board[x][y] = q.front();
			q.pop();
		}
	}
}

int main() {
	fillBoard();
	
	std::ifstream input;
	std::string str;
	std::stringstream ss;
	std::queue<char> q;
	int i = 1;

	input.open("Text.txt");

	while (i < 14) { //run through the encryption file and fill the array with '\' or '/'
		std::getline(input, str);
		ss << str;
		getSymbols(ss, q);
		ss.clear();
		++i;
	}

	populateBoard(q); //populate the board with contents of the queue

	//SFML stuff....create the window and variables to be used.
	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!", sf::Style::Titlebar);
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	sf::Text text;
	sf::String str2;
	sf::Font font;
	font.loadFromFile("arial.ttf");

	text.setFont(font);
	text.setColor(sf::Color::Green);
	text.setCharacterSize(18);
	while (window.isOpen())
	{
		sf::Event event;
		
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed){
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::BackSpace) { //allows user to backspace however the encrypted sentence won't change.
					str2.erase(str2.getSize() - 1);
					text.setString(str2);
				}
				if (event.key.code == sf::Keyboard::Return) {// allow user to input multiple lines.
					str2 += "\n";
					str = "\n";
					decodeWord(str);
					text.setString(str2);
				}
			}
			else if (event.type == sf::Event::TextEntered) { //for text entered in real time, encrypt each letter pending the encryption file.
				if (isprint(event.text.unicode)) {
					str2.insert(str2.getSize(), event.text.unicode);
					str = event.text.unicode;
					decodeWord(str);
					text.setString(str2);
				}
			}
		}
		
		window.clear();
		window.draw(text);
		window.display();
	}

	return 0;
}