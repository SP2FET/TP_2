// TP_2.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <vector>
#include <algorithm>
#include <ctime>
#include <list>
using namespace std;


class CTrain
{

private:
	queue<char> train;
public:
	CTrain(int number_of_cars);
	//~CTrain();
	int get_train_length() { return train.size(); }
	void resize_train(int number_of_cars);
	void add_car() {train.push(rand() % 4 + 65); }
	void add_car(char value) { train.push(value); }
	int get_last_car();
	void delete_last_car();


};

CTrain::CTrain(int number_of_cars)
{
	resize_train(number_of_cars);

}

int CTrain::get_last_car()
{ 
	if(!train.empty()) return train.front();
	//else cout << "End of train!" << endl;
}

void CTrain::delete_last_car() 
{

	if (!train.empty()) train.front();
	//else cout << "End of train!" << endl; 
}

void CTrain::resize_train(int number_of_cars)
{
	if(number_of_cars > train.size()) train.push(rand() % 4 + 65);
		else if (number_of_cars < train.size())
		{
			while (number_of_cars != train.size())  delete_last_car();

		}
	//    else cout<<"The train size is the same as insterted value!"<<endl;
}


#pragma endregion

#pragma region Track

class CTrack
{
private:

	vector<char> track;
	vector<char> track_template;
	void generate_template();
	void apply_template();
public:
	CTrack(int length);

	void print();
};

CTrack::CTrack(int length)
{
	track.resize(length, '=');
	//cout << "generate:" << endl;
	generate_template();
	//cout << "apply:" << endl;
	apply_template();
}

void CTrack::generate_template()
{
	//srand(time(NULL));

	for (int i = 0; i < rand() % 2 + 3; i++)
	{
		track_template.push_back(rand() % 4 + 65);
	}
}

void CTrack::apply_template()
{
	vector<char>::reverse_iterator temp_it, track_it;
	temp_it = track_template.rbegin();
	track_it = track.rbegin();
	for (int i = 0; i < rand() % 3; i++)
	{
		*track_it = *temp_it;
		temp_it++;
		track_it++;

	}

}

void CTrack::print()
{
	vector<char>::iterator it;
	for (size_t i = 0; i < 30 - track.size(); i++)
		cout << " ";

	for (it = track.begin(); it != track.end(); it++)
	{
		cout << *it;
	}
	cout << " Tor: [";
	for (it = track_template.begin(); it != track_template.end(); it++)
	{
		cout << *it;
	}
	cout << "]" << endl;
}

#pragma endregion


#pragma region Railways

class CRailway
{
private:
	list<CTrack*> *tracks;
	vector<char> *train;
public:
	CRailway(int number_of_tracks, int number_of_cars);
	~CRailway();
	int get_train_length() { return train->size(); }
	void addCar(char value) { train->push_back(value); }
	void addCar() { train->push_back((rand() % 4) + 65); }
	void addCars(size_t amount);
	void print_tracks();

};

CRailway::CRailway(int number_of_tracks, int number_of_cars)
{
	srand(time(NULL));
	tracks = new list<CTrack*>;
	int n = 30;
	for (int i = 0; i < number_of_tracks; i++)
	{
		if (i == 0) tracks->push_back(new CTrack(n));
		else tracks->push_back(new CTrack(n - 10));

		n = n - 2;

	}

	//test

	train = new vector<char>;
	addCars(number_of_cars);
}

void CRailway::print_tracks()
{

	list<CTrack*>::iterator it = tracks->begin();
	for (auto x : *train)
		cout << x;
	cout << " ";
	for (size_t i = 0; i < tracks->size(); i++)
	{

		if (i > 0)
			for (size_t i = 0; i < train->size() + 1; i++)
				cout << " ";


		(*it)->print();
		it++;
		cout << endl;

	}
}

CRailway::~CRailway()
{
	CTrack *track;

	list<CTrack*>::iterator list_it;
	for (list_it = tracks->begin(); list_it != tracks->end(); list_it++)
	{
		track = *list_it;
		delete track;
		cout << "Track " << *list_it << " DELETED" << endl;
	}
	tracks->clear();
	delete tracks;
	train->clear();
	delete train;
	cout << "Train DELETED";
	getch();

}

void CRailway::addCars(size_t amount)
{
	for (size_t i = 0; i < amount; i++)
		addCar();
}

#pragma endregion

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
	cout << "Y size: " << buffer.size() << endl;
	cout << "X size: " << buffer[0].size() << endl;
	for (; line_it != buffer.end(); line_it++)
	{
		col_it = (*line_it).begin();
		for (; col_it != (*line_it).end(); col_it++)
		{
			cout << *col_it;
		}
		cout << endl;
	}

}
#pragma endregion


int main()
{

	CRailway *railway = new CRailway(5, 7);
	CGraphics graphics(20, 20);

	cout << "train size:" << railway->get_train_length() << endl;
	railway->print_tracks();
	/*train->print();
	cout << " ";
	track->print();
	train->addCar('A');
	cout << "train size:" << railway->get_train_length() << endl;
	train->print();
	train->addCar();
	train->print();*/
	graphics.insertXY(0, 9, 'D');
	graphics.insertXY(0, 10, 5);

	graphics.print();
	if (_getch() == 27) cout << "50";
	delete railway;
	return 0;
}

