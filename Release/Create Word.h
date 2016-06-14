#include <iostream>
#include <sstream>
#include <string>

char board[15][15];

std::pair<int, int> moveUp(std::pair<int, int>& coord);
std::pair<int, int> moveDown(std::pair<int, int>& coord);
std::pair<int, int> moveLeft(std::pair<int, int>& coord);
std::pair<int, int> moveRight(std::pair<int, int>& coord);


std::pair<int, int> locateWord(char& c) {
	std::pair <int, int> coord;
	int x = 1;
	int y = 1;

	while (x < 14) {
		if (board[x][0] == c) {
			coord.first = x;
			coord.second = 0;
			return coord;
		}
		if (board[x][14] == c) {
			coord.first = x;
			coord.second = 14;
			return coord;
		}

		x++;
	}
	
	while (y < 14) {
		if (board[0][y] == c) {
			coord.first = 0;
			coord.second = y;
			return coord;
		}
		if (board[14][y] == c) {
			coord.first = 14;
			coord.second = y;
			return coord;
		}

		y++;
	}
}

std::pair<int, int> moveRight(std::pair <int, int>& coord) {
	int x = coord.first;
	int y = coord.second + 1;
	char ch;

	while (board[x][y] == ' ') {
		y++;
	}
	ch = board[x][y];

	switch (ch) {
	case '\\':
		coord.first = x;
		coord.second = y;
		return moveDown(coord);
		break;
	case '/':
		coord.first = x;
		coord.second = y;
		return moveUp(coord);
		break;
	default:
		coord.first = x;
		coord.second = y;
		return coord;
		break;
	}
}

std::pair<int, int> moveDown(std::pair <int, int>& coord) {
	int x = coord.first + 1;
	int y = coord.second;
	char ch;

	while (board[x][y] == ' ') {
		x++;
	}
	ch = board[x][y];

	switch (ch) {
	case '\\':
		coord.first = x;
		coord.second = y;
		return moveRight(coord);
		break;
	case '/':
		coord.first = x;
		coord.second = y;
		return moveLeft(coord);
		break;
	default:
		coord.first = x;
		coord.second = y;
		return coord;
		break;
	}
}

std::pair<int, int> moveLeft(std::pair <int, int>& coord) {
	int x = coord.first;
	int y = coord.second - 1;
	char ch;

	while (board[x][y] == ' ') {
		y--;
	}
	ch = board[x][y];

	switch (ch) {
	case '\\':
		coord.first = x;
		coord.second = y;
		return moveUp(coord);
		break;
	case '/':
		coord.first = x;
		coord.second = y;
		return moveDown(coord);
		break;
	default:
		coord.first = x;
		coord.second = y;
		return coord;
		break;
	}
}

std::pair<int, int> moveUp(std::pair <int, int>& coord) {
	int x = coord.first - 1;
	int y = coord.second;
	char ch;

	while (board[x][y] == ' ') {
		x--;
	}
	ch = board[x][y];

	switch (ch) {
		case '\\':
			coord.first = x;
			coord.second = y;
			return moveLeft(coord);
			break;
		case '/':
			coord.first = x;
			coord.second = y;
			return moveRight(coord);
			break;
		default:
			coord.first = x;
			coord.second = y;
			return coord;
			break;
	}
}

std::pair<int, int> tranverseBoard (std::pair <int, int>& coord) {
	if (coord.second == 0) {
		return moveRight(coord);
	}
	else if (coord.second == 14) {
		return moveLeft(coord);
	}
	else if (coord.first == 0) {
		return moveDown(coord);
	}
	else {
		return moveUp(coord);
	}
}

void decodeWord(std::string& str) {
	std::pair <int, int> coord;
	std::pair <int, int> finalCoord;

	for (char c : str) {
		if (!isalpha(c)) {
			std::cout << c;
		}
		else {
			coord = locateWord(c);
			finalCoord = tranverseBoard(coord);

			std::cout << board[finalCoord.first][finalCoord.second];
		}
	}
}