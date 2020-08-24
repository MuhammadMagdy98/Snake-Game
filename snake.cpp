#include <iostream>
#include <vector>
#include <conio.h>
#include <cassert>


char board[25][90];
bool snake_pos[25][90];
std::vector<std::pair<int, int>> body; // body[0] head position
int cnt = 1;

void reset_board();
void draw_board();
void handle_input();

int foodX, foodY;

void reset_board() {
	for (int i = 0; i < 90; i++)
		board[0][i] = '#';
	for (int i = 1; i < 24; i++) {
		for (int j = 0; j < 90; j++) {
			if (j == 0 || j == 89) {
				board[i][j] = '#';
			}
			else {
				board[i][j] = ' ';
			}
		}
	}
	for (int i = 0; i < 90; i++) {
		board[24][i] = '#';
	}
	board[body[0].first][body[0].second] = 'O';
	for (int i = 1; i < body.size(); i++)
		board[body[i].first][body[i].second] = 'o';
	for (auto x : body)
		snake_pos[x.first][x.second] = true;
		
	board[foodX][foodY] = 'X';
}

void update() {
	//for (int i = 0; i < length; i++)
}
void draw_board() {
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 90; j++) {
			std::cout << board[i][j];
		}
		std::cout << '\n';
	}
}

int rand(int a, int b) {
	return a + rand() % (b - a + 1);
}

void food() {
	int x = rand(1, 23);
	int y = rand(1, 88);
	// while food pos is part of the snake
	while (snake_pos[x][y]) {
		x = rand(1, 23);
		y = rand(1, 88);
	}
	foodX = x;
	foodY = y;
}

#define KEY_UP 'w'
#define KEY_DOWN 's'
#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'

bool game_over(int x, int y) {
	for (int i = 1; i < body.size(); i++) {
		if (std::make_pair(x, y) == body[i])
			return true;
	}
	return false;
}

bool valid_move(char key) {
	// check if move is not in opposite direction 
	// 0, 1, 2, 3 [left, right, up, down] respectively
	if (cnt == 3 && key == KEY_UP)
		return false;
	if (cnt == 2 && key == KEY_DOWN)
		return false;
	if (cnt == 1 && key == KEY_LEFT)
		return false;
	if (cnt == 0 && key == KEY_RIGHT)
		return false;
	switch (key) {
	case KEY_LEFT:
		cnt = 0;
		break;
	case KEY_RIGHT:
		cnt = 1;
		break;
	case KEY_UP:
		cnt = 2;
		break;
	case KEY_DOWN:
		cnt = 3;
		break;
	default:
		assert(false);
	}
	return true;

}

bool food_eaten() {
	return body[0].first == foodX && body[0].second == foodY;
}

void handle_input() {
	char key = _getch();
	
	
	if (key == KEY_UP && valid_move(key)) {
		
		std::pair<int, int> prev = body[0];

		body[0].first--;
		if (body[0].first == 0)
			body[0].first = 23;
		if (game_over(body[0].first, body[0].second)) {
			std::cout << "Game is over\n";
			exit(0);
		}
		if (food_eaten()) {
			board[foodX][foodY] = ' ';
			// add tail 
			body.push_back({ body.back().first + 1, body.back().second });
			reset_board();
			// draw new food
			food();
		}

		
		for (int i = 1; i < body.size(); i++) {
			std::pair<int, int> tmp = body[i];
			body[i] = prev;
			prev = tmp;

		}
		
	}
			
		
	else if (key == KEY_DOWN && valid_move(key)) {
		
		std::pair<int, int> prev = body[0];
		body[0].first++;
		if (body[0].first == 24)
			body[0].first = 1;
		if (game_over(body[0].first, body[0].second)) {
			std::cout << "Game is over\n";
			exit(0);
		}
		if (food_eaten()) {
			board[foodX][foodY] = ' ';
			body.push_back({body.back().first - 1, body.back().second});
			reset_board();
			food();
		}
		
		for (int i = 1; i < body.size(); i++) {
			std::pair<int, int> tmp = body[i];
			body[i] = prev;
			prev = tmp;

		}
		
			
	}
	else if (key == KEY_LEFT && valid_move(key)) {
		if (cnt == 1) return;
		cnt = 0;
		std::pair<int, int> prev = body[0];
		body[0].second--;
		if (body[0].second == 0) {
			body[0].second = 88;
		}
		if (game_over(body[0].first, body[0].second)) {
			std::cout << "Game is over\n";
			exit(0);
		}
		if (food_eaten()) {
			board[foodX][foodY] = ' ';
			body.push_back({ body.back().first, body.back().second + 1 });
			reset_board();
			food();
		}
		
		for (int i = 1; i < body.size(); i++) {
			std::pair<int, int> tmp = body[i];
			body[i] = prev;
			prev = tmp;

		}
			
	}
	else if (key == KEY_RIGHT && valid_move(key)) {
		std::pair<int, int> prev = body[0];
		body[0].second++;
		if (body[0].second == 89) {
			body[0].second = 1;
		}
		if (game_over(body[0].first, body[0].second)) {
			std::cout << "Game is over\n";
			exit(0);
		}
		if (food_eaten()) {
			board[foodX][foodY] = ' ';
			body.push_back({ body.back().first, body.back().second - 1 });
			reset_board();
			food();
		}
		
		for (int i = 1; i < body.size(); i++) {
			std::pair<int, int> tmp = body[i];
			body[i] = prev;
			prev = tmp;

		}
			
	}
	system("cls");
	reset_board();
	draw_board();
	


		
}
int main()
{
	food();
	snake_pos[4][81] = snake_pos[4][80] = snake_pos[4][79] = snake_pos[4][82] = true;
	body.push_back({ 4, 82 });
	body.push_back({ 4, 81 });
	body.push_back({ 4, 80 });
	body.push_back({ 4, 79 });
	while (true) {
		//food();
		//draw();
		handle_input();
		//system("cls");
	}
	

	return 0;

}
