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
	int pattern_length() { return pattern.size(); }
	char get_first_car() { return track.top(); }

	void clear_track() { while (!track.empty()) track.pop(); }
	bool is_filled() { return (track.size() < capacity) ? false : true; }
	int length() { return track.size(); }
	void add_car(char value) { if (!is_filled()) track.push(value); }

};

CTrack::CTrack(int max_capacity)
{
	capacity = max_capacity;
	generate_pattern();
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

#pragma region Railways

class CRailway
{
private:
	vector<CTrack> tracks;
	CTrain train;
public:
	CRailway(int number_of_tracks, int number_of_cars);
	~CRailway();
	void add_tracks(int number_of_tracks, int pattern_sizes);
	void move_car(int track_number);
	bool check_car_combination(int track_number);




};


void CRailway::add_tracks(int number_of_tracks, int capacity)
{
	for (int i = 0; i < number_of_tracks; i++)  tracks.push_back(CTrack(capacity));
}



bool CRailway::check_car_combination(int track_number)
{
	static bool found_combination;

	if (tracks[track_number].)


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




CRailway::CRailway(int number_of_tracks, int number_of_cars)
{

}



#pragma endregion
{
	//
	//
	//#pragma region Grafika
	//
	//class CGraphics
	//{
	//private:
	//	char** buffer;
	//	int lines, columns;
	//public:
	//	CGraphics(int x_size, int y_size);
	//	CGraphics(int x_size);
	//	void insertXY(int x, int y, char to_insert) { buffer[y][x] = to_insert; }
	//	void insertXY(int x, int y, int to_insert) { buffer[y][x] = to_insert + '0'; }
	//	void clearXY(int x, int y) { buffer[y][x] = ' '; }
	//	void writeTrack(int x, int y, int length);
	//	void print();
	//};
	//
	//CGraphics::CGraphics(int x_size, int y_size)
	//{
	//	buffer = new char*[y_size];
	//
	//	for (size_t i = 0; i < y_size; i++)
	//		*(buffer + i) = new char[x_size];
	//
	//
	//	for (size_t y = 0; y < y_size; y++)
	//	{
	//		for (size_t x = 0; x < x_size; x++)
	//		{
	//			buffer[y][x] = ' ';
	//		}
	//	}
	//	lines = x_size;
	//	columns = y_size;
	//}
	//
	//CGraphics::CGraphics(int x_size)
	//{
	//	buffer = new char*[x_size];
	//
	//	for (size_t i = 0; i < x_size; i++)
	//	{
	//		*buffer = new char[x_size];
	//	}
	//
	//	for (size_t y = 0; y < x_size; y++)
	//	{
	//		for (size_t x = 0; x < x_size; x++)
	//		{
	//			buffer[y][x] = ' ';
	//		}
	//	}
	//	lines = columns = x_size;
	//
	//}
	//
	//void CGraphics::print()
	//{
	//	for (size_t y = 0; y < columns; y++)
	//	{
	//		for (size_t x = 0; x < lines; x++)
	//		{
	//			cout << buffer[y][x];
	//		}
	//		cout << endl;
	//	}
	//
	//}
	//
	//void CGraphics::writeTrack(int x, int y, int length)
	//{
	//	for (int i = 0; i < length; i++)
	//	{
	//		buffer[y][x + i] = '=';
	//	}
	//}
	//#pragma endregion
}

#pragma region Grafika

class CGraphics
{
private:
	vector<vector<char>> buffer;
public:
	CGraphics(int x_size, int y_size);
	CGraphics(int x_size);
	void insertXY(int x, int y, char to_insert) { buffer[y][x] = to_insert; }
	void insertXY(int x, int y, int to_insert) { buffer[y][x] = to_insert + '0'; }
	void clearXY(int x, int y) { buffer[y][x] = ' '; }
	void writeTrack(int x, int y, int length);
	void writeTrain(int x, int y, CTrain train);
	void print();
};

CGraphics::CGraphics(int x_size, int y_size)
{
	buffer.resize(y_size);
	vector<vector<char>>::iterator line_it = buffer.begin();
	vector<char>::iterator col_it;

	for (; line_it != buffer.end(); line_it++)
	{
		(*line_it).resize(x_size);
	}
}

CGraphics::CGraphics(int x_size)
{
	buffer.resize(x_size);
	vector<vector<char>>::iterator line_it = buffer.begin();
	vector<char>::iterator col_it;

	for (; line_it != buffer.end(); line_it++)
	{
		(*line_it).resize(x_size);
	}
}

void CGraphics::print()
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

void CGraphics::writeTrack(int x, int y, int length)
{
	for (int i = 0; i < length; i++)
	{
		buffer[y][x + i] = '=';
	}
}

void CGraphics::writeTrain(int x, int y, CTrain train)
{
	for (size_t i = 0; i < train.length(); i++)
	{
		buffer[y][x + i] = train.get_first_car();
		train.delete_first_car();
	}
}

#pragma endregion


int main()
{


	//	CRailway *railway = new CRailway(5, 7);

		//CRailway *railway = new CRailway(5, 7);

	CGraphics buffer(20, 50);

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
	buffer.insertXY(0, 9, 'D');
	buffer.insertXY(0, 10, 5);
	buffer.writeTrack(4, 4, 10);
	buffer.print();
	if (_getch() == 27) cout << "50";
	//delete railway;
	return 0;
}
