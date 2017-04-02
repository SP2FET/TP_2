// TP_2.cpp: Okre�la punkt wej�cia dla aplikacji konsoli.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <vector>
#include <queue>
#include <ctime>
#include <stack>
#include <cstdlib>

using namespace std;


const int TRAIN_LENGTH = 70;
const int TRACKS_CAPACITY = 11;
const int TRACK_LENGTH = 20;
const int VISIBLE_CARS = 5;
const int SCORE_TO_WIN = 60;

#pragma region Track

class CTrack
{
private:

	stack<char> track;
	vector<char> pattern;
	vector<char> sequence;
	int capacity;
	int car_number;

public:

	CTrack(int length);
	void generate_pattern(int level);
	int  pattern_length() { return pattern.size(); }
	char get_first_car() { return track.top(); }
	void delete_first_car() { if (!track.empty()) track.pop(); }
	vector<char> get_pattern() { return pattern; }
	void clear() { while (!track.empty()) track.pop(); }
	bool is_filled() { return (track.size() < capacity) ? false : true; }
	int  length() { return track.size(); }
	void add_car(char value) { if (!is_filled()) track.push(value); }
	void load_sequence();
	void insert_cars();
	void delete_sequence();
	int  get_capacity() { return capacity; }
	bool check_sequence();
};

CTrack::CTrack(int max_capacity)
{
	capacity = max_capacity;
	car_number = 0;
	generate_pattern(0);
	if (pattern.size() > capacity)  capacity = pattern.size();
}

void CTrack::generate_pattern(int level)
{
	pattern.clear();
	int pattern_length;

	if (level == 0)
		pattern_length = rand() % 2 + 3;
	else
		pattern_length = level;

	for (int i = 0; i < pattern_length && i < capacity; i++)
		pattern.push_back(rand() % 4 + 65);

}

void CTrack::insert_cars()
{
	for (int i = 0; i < rand() % 3; i++)
	{
		track.push(pattern[pattern.size() - i - 1]);
		car_number++;
	}
}

void CTrack::load_sequence()
{
	vector<char>::reverse_iterator rit;

	sequence.clear();

	for (int i = 0; i < pattern.size() && !track.empty(); i++)
	{
		sequence.push_back(get_first_car());
		delete_first_car();
	}

	for (rit = sequence.rbegin(); rit != sequence.rend(); rit++)
		add_car(*rit);

}

void CTrack::delete_sequence()
{
	for (int i = 0; i < pattern_length(); i++)  delete_first_car();
}

bool CTrack::check_sequence()
{
	load_sequence();
	if (sequence == pattern)
	{
		sequence.clear();
		for (int i = 0; i < pattern.size(); i++)  delete_first_car();
		return true;
	}
	else return false;
}
#pragma endregion


#pragma region Train

class CTrain
{
private:
	queue<char> train;
public:

	CTrain(int number_of_cars);
	//~CTrain();
	int length() { return train.size(); }
	void resize(int number_of_cars);
	void add_car() { train.push(rand() % 4 + 65); }
	char get_first_car();
	void delete_first_car() { if (!train.empty()) train.pop(); }
};

char CTrain::get_first_car()
{
	if (!train.empty()) return train.front();
	else return ' ';
}

CTrain::CTrain(int number_of_cars)
{
	resize(number_of_cars);
}

void CTrain::resize(int number_of_cars)
{
	if (number_of_cars > train.size())
	{
		for (int i = train.size(); i < number_of_cars; i++)  train.push(rand() % 4 + 65);
	}
	else if (number_of_cars < train.size())
	{
		while (number_of_cars != train.size())  delete_first_car();
	}
}

#pragma endregion


#pragma region Grafika

class CBuffer
{
private:
	vector<vector<char>> buffer;
public:
	CBuffer(int x_size, int y_size);
	void insertXY(int x, int y, char to_insert) { buffer[y][x] = to_insert; }
	void insertXY(int x, int y, char* to_insert);
	void insertXY(int x, int y, vector<char> to_insert);
	void insertXY(int x, int y, int to_insert);
	void clearXY(int x, int y) { buffer[y][x] = ' '; }
	void clear();
	void writeTrack(int x, int y, int length, CTrack track);
	void writeTrain(int x, int y, int visible_cars, CTrain train);
	void print();
};

CBuffer::CBuffer(int x_size, int y_size)
{
	buffer.resize(y_size);
	vector<vector<char>>::iterator line_it = buffer.begin();
	vector<char>::iterator col_it;

	for (; line_it != buffer.end(); line_it++)
	{
		(*line_it).resize(x_size);
	}
}

void CBuffer::print()
{
	vector<vector<char>>::iterator line_it = buffer.begin();
	vector<char>::iterator col_it;

	system("cls");

	for (; line_it != buffer.end(); line_it++)
	{
		for (col_it = (*line_it).begin(); col_it != (*line_it).end(); col_it++)
		{
			cout << *col_it;
		}
		cout << endl;
	}
}

void CBuffer::insertXY(int x, int y, char* to_insert)
{
	for (size_t i = 0; *(to_insert + i) != 0; i++)
		buffer[y][x + i] = *(to_insert + i);
}

void CBuffer::insertXY(int x, int y, vector<char> to_insert)
{
	for (size_t i = 0; i < to_insert.size(); i++)
		buffer[y][x + i] = to_insert[i];
}

void CBuffer::insertXY(int x, int y, int to_insert)
{
	char char_buffer[10];
	_itoa_s(to_insert, char_buffer, 10);
	for (size_t i = 0; char_buffer[i] != 0; i++)
		buffer[y][x + i] = char_buffer[i];
}

void CBuffer::writeTrack(int x, int y, int template_length, CTrack track)
{
	int capacity = track.get_capacity();
	int length = track.length();

	for (int i = 0; i < template_length; i++)
	{
		buffer[y][x + i] = '=';
		if (i == capacity) buffer[y][x + i] = '|';
	}
	for (int i = length; i > 0; i--)
	{
		buffer[y][x + capacity - i] = track.get_first_car();
		track.delete_first_car();
	}
}

void CBuffer::writeTrain(int x, int y, int visible_cars, CTrain train)
{
	for (int i = visible_cars; i > 0; i--)
	{
		buffer[y][x + i] = train.get_first_car();
		train.delete_first_car();
	}
}

void CBuffer::clear()
{
	vector<vector<char>>::iterator line_it = buffer.begin();
	vector<char>::iterator col_it;

	for (; line_it != buffer.end(); line_it++)
	{
		for (col_it = (*line_it).begin(); col_it != (*line_it).end(); col_it++)
		{
			*col_it = ' ';
		}
		cout << endl;
	}
}

#pragma endregion



#pragma region Railways

class CRailway
{
private:
	vector<CTrack> tracks;
	CTrain train;
	CBuffer *buffer;
	int selected_track;
	int score;
	int level;
public:
	bool game_over;
	CRailway(int number_of_tracks, int tracks_capacity, int number_of_cars);
	~CRailway();
	void move_car(int track_number);
	void make_turn(int track_number);
	void menu();
	void display();
	void apply_template();
	void parse_keys();

};

void CRailway::apply_template()
{
	buffer->clear();

	for (int i = 0; i < tracks.size(); i++)
	{
		int y = (2 * i) + 1;
		if (i == 0)
			buffer->writeTrack(VISIBLE_CARS + 5, y, TRACK_LENGTH + 5 - (2 * i), tracks[i]);
		else
			buffer->writeTrack(VISIBLE_CARS + (2 * i) + 10, y, TRACK_LENGTH - (2 * i), tracks[i]);

		buffer->insertXY(VISIBLE_CARS + 31, y, "TOR");
		buffer->insertXY(VISIBLE_CARS + 35, y, i + 1);
		buffer->insertXY(VISIBLE_CARS + 36, y, ": [");
		buffer->insertXY(VISIBLE_CARS + 39, y, tracks[i].get_pattern());
		buffer->insertXY(VISIBLE_CARS + 39 + tracks[i].pattern_length(), y, ']');
	}

	switch (selected_track)
	{
	case 1:
		break;

	case 5:
		buffer->insertXY(VISIBLE_CARS + 15, 8, "\\\\");
		buffer->insertXY(VISIBLE_CARS + 16, 9, "\\\\");

	case 4:
		buffer->insertXY(VISIBLE_CARS + 13, 6, "\\\\");
		buffer->insertXY(VISIBLE_CARS + 14, 7, "\\\\");

	case 3:
		buffer->insertXY(VISIBLE_CARS + 11, 4, "\\\\");
		buffer->insertXY(VISIBLE_CARS + 12, 5, "\\\\");

	case 2:
		buffer->insertXY(VISIBLE_CARS + 9, 2, "\\\\");
		buffer->insertXY(VISIBLE_CARS + 10, 3, "\\\\");
		break;
	}

	// szablon narysowany
}

CRailway::~CRailway()
{
	delete buffer;
}


void CRailway::move_car(int track_number)
{
	if (train.length())
	{
		tracks[track_number].add_car(train.get_first_car());
		train.delete_first_car();
	}
}


void CRailway::make_turn(int track_number)
{

	if (!tracks[track_number].is_filled())
	{
		move_car(track_number);
		if (level == 0) score++;

		if (tracks[track_number].check_sequence())
		{
			switch (level)
			{
			case 0:
				break;
			case 1:
				tracks[track_number].generate_pattern(0);
				break;
			case 2:
				tracks[track_number].generate_pattern(tracks[track_number].pattern_length() + 1);
				break;
			}
			score += 10;
		}

	}
	else
		game_over = true;
}

CRailway::CRailway(int number_of_tracks, int tracks_capacity, int number_of_cars) : train(number_of_cars)  ///!!!!!!!!!!!!!!!
{
	buffer = new CBuffer(70, 10);
	level = 0;
	score = 0;
	selected_track = 1;
	game_over = false;

	menu();

	for (int i = 0; i < number_of_tracks; i++)
	{
		tracks.push_back(CTrack(tracks_capacity - level * 2));
		tracks[i].generate_pattern(0);
		if (level == 0) tracks[i].insert_cars();
	}
}

void CRailway::parse_keys()
{
	char key = _getch();

	switch (key)
	{
	case '1':
		selected_track = 1;
		break;
	case 'w':
		make_turn(selected_track - 1);
		break;
	case '5':
		selected_track = 5;
		break;
	case '4':
		selected_track = 4;
		break;
	case '3':
		selected_track = 3;
		break;
	case '2':
		selected_track = 2;
		break;

	default:
		parse_keys();
		break;
	}
}

void CRailway::menu()
{
	int key;

	buffer->insertXY(25, 5, "Select level:");
	buffer->insertXY(25, 6, "* Easy");
	buffer->insertXY(27, 7, "Medium");
	buffer->insertXY(27, 8, "Hard");
	buffer->print();
	key = _getch();

	while (key != 13)
	{
		key = _getch();
		if (key == 0 || key == 0xE0) key = _getch();

		switch (key)
		{
		case 80:
			level++;
			if (level > 2) level = 0;
			break;
		case 72:
			level--;
			if (level < 0) level = 2;
			break;
		}

		switch (level)
		{
		case 0:
			buffer->clearXY(25, 7);
			buffer->clearXY(25, 8);
			buffer->insertXY(25, 6, "*");
			break;
		case 1:
			buffer->clearXY(25, 6);
			buffer->clearXY(25, 8);
			buffer->insertXY(25, 7, "*");
			break;
		case 2:
			buffer->clearXY(25, 6);
			buffer->clearXY(25, 7);
			buffer->insertXY(25, 8, "*");
			break;
		}

		buffer->print();
	}

}

void CRailway::display()
{
	apply_template();
	buffer->writeTrain(1, 1, VISIBLE_CARS - level, train);
	buffer->insertXY(60, 1, "Score: ");
	buffer->insertXY(67, 1, score);

	if (game_over)
	{
		buffer->clear();
		buffer->insertXY(25, 5, "GAME OVER!");
		buffer->insertXY(25, 6, "Score: ");
		buffer->insertXY(32, 6, score);
		buffer->print();
		_getch();
	}
	if (score > SCORE_TO_WIN)
	{
		buffer->clear();
		buffer->insertXY(25, 5, "YOU WIN!");
		buffer->insertXY(25, 6, "Score: ");
		buffer->insertXY(32, 6, score);
		buffer->print();
		_getch();
		game_over = true;
	}
	buffer->print();
}
#pragma endregion



int main()
{
	srand(time(NULL));

	CRailway *game = new CRailway(5, TRACKS_CAPACITY, TRAIN_LENGTH);
	game->display();

	while (!game->game_over)
	{
		game->parse_keys();
		game->display();
	}
	delete game;
	return 0;
}