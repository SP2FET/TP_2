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
using namespace std;


#pragma region Track

class CTrack
{
private:

	stack<char> track;
	vector<char> pattern;
	int capacity;

public:

	CTrack(int length);
	void generate_pattern();
	int  pattern_length() { return pattern.size(); }
	char  get_rev_pattern_car(int number);
	char get_first_car() { return track.top(); }
	vector<char> get_pattern() { return pattern; }
	void clear_track() { while (!track.empty()) track.pop(); }
	bool is_filled() { return (track.size() < capacity) ? false : true; }
	int  length() { return track.size(); }
	void add_car(char value) { if (!is_filled()) track.push(value); }
	int get_capacity() { return capacity; }
};

CTrack::CTrack(int max_capacity)
{
	capacity = max_capacity;
	generate_pattern();
	if (pattern.size() > capacity)  capacity = pattern.size();

}

void CTrack::generate_pattern()
{
	//srand(time(NULL));
	pattern.clear();
	for (int i = 0; i < rand() % 2 + 3; i++)
	{
		pattern.push_back(rand() % 4 + 65);
	}
}


char CTrack::get_rev_pattern_car(int number)
{
	vector<char>::reverse_iterator rit;

	int counter = 0;

	for (rit = pattern.rbegin(); rit != pattern.rend() && counter < number; rit++);

	return *rit;
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
	char get_first_car() { if (!train.empty()) return train.front(); }
	void delete_first_car() { if (!train.empty()) train.pop(); }
};

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
	void insertXY(int x, int y, int to_insert) { buffer[y][x] = to_insert + '0'; }
	void clearXY(int x, int y) { buffer[y][x] = ' '; }
	void writeTrack(int x, int y, int length, int number);
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

void CBuffer::writeTrack(int x, int y, int length, int capacity)
{
	for (int i = 0; i < length; i++)
	{
		buffer[y][x + i] = '=';
		if (i == capacity) buffer[y][x + i] = '|';
	}
}

void CBuffer::writeTrain(int x, int y, CTrain train)
{
	for (int i = 0; train.length() > 0; i++)
	{
		buffer[y][x + i] = train.get_first_car();
		train.delete_first_car();
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
public:
	CRailway(int number_of_tracks, int tracks_capacity, int number_of_cars);
	~CRailway();
	void move_car(int track_number);
	bool check_car_combination(int track_number);
	void display() { buffer->print(); }
	void apply_template();

};

void CRailway::apply_template()
{
	buffer->writeTrain(1, 1, train);


	for (int i = 0; i < tracks.size(); i++)
	{
		if (i == 0)
			buffer->writeTrack(train.length() + (2 * i) + 5, (2 * i) + 1, 25 - (2 * i), tracks[i].get_capacity());
		else
			buffer->writeTrack(train.length() + (2 * i) + 10, (2 * i) + 1, 20 - (2 * i), tracks[i].get_capacity());

		buffer->insertXY(train.length() + 31, (2 * i) + 1, "TOR");
		buffer->insertXY(train.length() + 35, (2 * i) + 1, i + 1);
		buffer->insertXY(train.length() + 36, (2 * i) + 1, ": [");
		buffer->insertXY(train.length() + 39, (2 * i) + 1, tracks[i].get_pattern());
		buffer->insertXY(train.length() + 39 + tracks[i].pattern_length(), (2 * i) + 1, ']');
	}


	// szablon narysowany
}
/*
bool CRailway::check_car_combination(int track_number)      ///!! kombinacja w wektorze jest od konca
{
static int car_number = 0;
bool found_combination = false;


if(!car_number)
{
if (tracks[track_number].get_first_car() == tracks[track_number].get_rev_pattern_car(car_number))  car_number = 1;
}
else
{
if(tracks[track_number].get_first_car() == tracks[track_number].get_rev_pattern_car(car_number)) car_number++;
else
{
car_number = 0;
}
}

if (car_number == tracks[track_number].pattern_length())
{
found_combination = true;
car_number = 0;

}

return found_combination;

} */

bool CRailway::check_car_combination(int track_number)      ///!! kombinacja w wektorze jest od konca
{
	static int car_number = 0;

	if (tracks[track_number].get_first_car() == tracks[track_number].get_rev_pattern_car(car_number)) car_number++;
	else
	{
		car_number = 0;
		return false;
	}

	if (car_number == tracks[track_number].pattern_length())
	{
		car_number = 0;
		return true;
	}
	else return false;

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




CRailway::CRailway(int number_of_tracks, int tracks_capacity, int number_of_cars) : train(number_of_cars)  ///!!!!!!!!!!!!!!!
{
	buffer = new CBuffer(60, 10);


	for (int i = 0; i < number_of_tracks; i++)
	{

		tracks.push_back(CTrack(tracks_capacity));
		tracks[i].generate_pattern();
		
	}


}


#pragma endregion



int main()
{

	srand(time(NULL));
	//	CRailway *railway = new CRailway(5, 7);

	//CRailway *railway = new CRailway(5, 7);
	cout << "test";
	CRailway *game = new CRailway(5, 3, 10);

	//cout << "train size:" << railway->get_train_length() << endl;
	//railway->print_tracks();
	/*train->print();
	cout << " ";
	track->print();
	train->addCar('A');
	cout << "train size:" << railway->get_train_length() << endl;
	train->print();
	train->addCar();
	train->print(); */
	game->apply_template();
	game->display();
	//buffer.print();
	if (_getch() == 27) cout << "50";
	//delete railway;
	return 0;
}
