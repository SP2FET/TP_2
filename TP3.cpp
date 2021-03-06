// TP_2.cpp: Okre�la punkt wej�cia dla aplikacji konsoli.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <ctime>
#include <list>
#include <stack>
#include <cstdlib>
using namespace std;


#pragma region Track

class CTrack
{
private:

	stack<char> track;
	vector<char> pattern;
	int capacity;
	int car_number = 0;

public:

	CTrack(int length, int pattern_length);
	void generate_pattern(int pattern_length);
	int  pattern_length() { return pattern.size(); }
	char  get_rev_pattern_car(int number);
	char get_first_car() { return track.top(); }
	void delete_first_car() { if (!track.empty()) track.pop(); }
	vector<char> get_pattern() { return pattern; }
	void clear_track() { while (!track.empty()) track.pop(); }
	bool is_filled() { return (track.size() < capacity) ? false : true; }
	int  length() { return track.size(); }
	void add_car(char value) { if (!is_filled()) track.push(value); }
	void add_start_cars();
	bool check_car_combination();
	void delete_matched_cars();
	int get_capacity() { return capacity; }
};

CTrack::CTrack(int max_capacity, int pattern_length)
{
	capacity = max_capacity;
	generate_pattern(pattern_length);
	if (pattern.size() > capacity)  capacity = pattern.size();

}

void CTrack::generate_pattern(int pattern_length)
{
	//srand(time(NULL));
	pattern.clear();
	for (int i = 0; i < rand() % 2 + pattern_length; i++)
	{
		pattern.push_back(rand() % 4 + 65);
	}
}

void CTrack::add_start_cars()
{
	if (track.size() == 0)
	{
		for (int i = 0; i < rand() % 3; i++)
		{
			track.push(rand() % 4 + 65);
		}
	}
	else cout << "Track is not empty!" << endl;

}


char CTrack::get_rev_pattern_car(int number) ///!!!!!
{
	vector<char>::reverse_iterator rit;

	int counter = 0;

	for (rit = pattern.rbegin(); (rit+1) != pattern.rend() && counter < number; rit++, counter++);  //rit+1 żeby nie wyszło poza zakres vectora
	
	return *rit;
}


bool CTrack::check_car_combination()
{
	if (get_first_car() == get_rev_pattern_car(car_number)) car_number++;
	else if(get_first_car() == get_rev_pattern_car(0))
	{
		car_number = 1;
		return false;
	}
	else
	{
		car_number = 0;
		return false;
	}

	if (car_number == pattern_length())
	{
		car_number = 0;
		return true;
	}
	else return false;
}

void CTrack::delete_matched_cars()
{
	for (int i = 0; i < pattern_length(); i++)  delete_first_car();
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
	void add_car(char value) { train.push(value); }
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
	//    else cout<<"The train size is the same as insterted value!"<<endl;
}

#pragma endregion


#pragma region Grafika

class CBuffer
{
private:
	vector<vector<char>> buffer;
public:
	CBuffer(int x_size, int y_size);
	CBuffer(int x_size);
	void insertXY(int x, int y, char to_insert) { buffer[y][x] = to_insert; }
	void insertXY(int x, int y, char* to_insert);
	void insertXY(int x, int y, vector<char> to_insert);
	void insertXY(int x, int y, int to_insert);
	void clearXY(int x, int y) { buffer[y][x] = ' '; }
	void clearBuffer();
	void writeTrack(int x, int y, int length, CTrack track);
	void writeTrain(int x, int y, CTrain train);
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

CBuffer::CBuffer(int x_size)
{
	buffer.resize(x_size);
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
	cout << "Y size: " << buffer.size() << endl;
	cout << "X size: " << buffer[0].size() << endl;
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

void CBuffer::writeTrain(int x, int y, CTrain train)
{
	for (int i = 5; i > 0; i--)
	{
		buffer[y][x + i] = train.get_first_car();
		train.delete_first_car();
	}
}

void CBuffer::clearBuffer()
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
	int selected_track = 1;
	int score = 0;
	int difficulty_level = 1;
	bool game_over = false;
public:
	CRailway(int number_of_tracks, int tracks_capacity, int number_of_cars, int difficulty_level);
	~CRailway();
	void move_car(int track_number);
	void make_turn(int track_number);
	void display();
	void apply_template();
	void parse_keys();

};

void CRailway::apply_template()
{
	buffer->clearBuffer();



	for (int i = 0; i < tracks.size(); i++)
	{
		if (i == 0)				//train.length
			buffer->writeTrack(10 + (2 * i) + 5, (2 * i) + 1, 25 - (2 * i), tracks[i]);
		else
			buffer->writeTrack(10 + (2 * i) + 10, (2 * i) + 1, 20 - (2 * i), tracks[i]);

		buffer->insertXY(10 + 31, (2 * i) + 1, "TOR");
		buffer->insertXY(10 + 35, (2 * i) + 1, i + 1);
		buffer->insertXY(10 + 36, (2 * i) + 1, ": [");
		buffer->insertXY(10 + 39, (2 * i) + 1, tracks[i].get_pattern());
		buffer->insertXY(10 + 39 + tracks[i].pattern_length(), (2 * i) + 1, ']');
	}

	switch (selected_track)
	{
	case 1:
		break;

	case 5:
		buffer->insertXY(25, 8, "\\\\");
		buffer->insertXY(26, 9, "\\\\");

	case 4:
		buffer->insertXY(23, 6, "\\\\");
		buffer->insertXY(24, 7, "\\\\");

	case 3:
		buffer->insertXY(21, 4, "\\\\");
		buffer->insertXY(22, 5, "\\\\");

	case 2:
		buffer->insertXY(19, 2, "\\\\");
		buffer->insertXY(20, 3, "\\\\");
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
	//else cout << "There is no cars left" << endl;
}


void CRailway::make_turn(int track_number)   //TODO odejmowanie punktow jak tor sie zablokuje
{
	//cout << endl << "Points: " << gained_points << endl;
	if (!tracks[track_number].is_filled())
	{
		move_car(track_number);
		score++;

		if (tracks[track_number].check_car_combination())
		{
			difficulty_level++;
			tracks[track_number].delete_matched_cars();
			tracks[track_number].generate_pattern(difficulty_level);
			score += 10;

		}

		
	}
	else game_over = true;

}

CRailway::CRailway(int number_of_tracks, int tracks_capacity, int number_of_cars, int difficulty_level) : train(number_of_cars)  ///!!!!!!!!!!!!!!!
{
	buffer = new CBuffer(70, 10);


	for (int i = 0; i < number_of_tracks; i++)
	{

		tracks.push_back(CTrack(tracks_capacity,difficulty_level));
	//	tracks[i].generate_pattern(difficulty_level);
	//	tracks[i].add_start_cars();

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
		make_turn(selected_track-1);
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
		selected_track =2;
		break;

	default:
		parse_keys();
		break;
	}


}

void CRailway::display()
{
	apply_template();
	buffer->writeTrain(1, 1, train);
	buffer->insertXY(60, 1, "Score: ");
	buffer->insertXY(67, 1, score);
	if (game_over)
	{
		buffer->clearBuffer();
		buffer->insertXY(25, 5, "GAME OVER!");
		buffer->insertXY(25, 6, "Score: ");
		buffer->insertXY(32, 6, score);
		buffer->print();
		_getch();
		exit(0);
	}
	buffer->print();
}
#pragma endregion



int main()
{

	srand(time(NULL));

	CRailway *game = new CRailway(5, 5, 20, 1);
	game->display();
	while (1)
	{
		game->parse_keys();
		game->display();
	}


	if (_getch() == 27) cout << "50";
	delete game;
	return 0;
}
