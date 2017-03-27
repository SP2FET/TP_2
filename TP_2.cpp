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
	for (size_t i = 0; i < rand() % 3; i++)
	{
		*track_it = *temp_it;
		temp_it++;
		track_it++;
		
	}

}

void CTrack::print()
{
	vector<char>::iterator it;
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
	for (int i = 0; i < number_of_tracks; i++)
		tracks->push_front(new CTrack(30));
	//test

	train = new vector<char>;
	addCars(number_of_cars);
}

void CRailway::print_tracks()
{
	list<CTrack*>::iterator it = tracks->begin();
	for (size_t i = 0; i < tracks->size(); i++)
	{
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

int main()
{

	CRailway *railway = new CRailway(5, 10);

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
	 
	if (_getch() == 27) cout << "50";
	delete railway;
	return 0;
}

