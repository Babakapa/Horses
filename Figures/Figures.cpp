// Figures.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
using namespace std;


class Track{
private:
	char symbol;
public:
	Track(char symbol) {
		this->symbol = symbol;
	}
	void showTrack(const int lenght, int position, string name) {
		
		cout << name;
		cout << " ";
		string track;
		for (int i = position; i < lenght; i++) {
			cout << symbol;
		}
	}
};


class Horse {
private:
	string name;
	int currentPosition;
public:
	Horse(string name) {
		this->name = name;
		currentPosition = 0;
	}
	string getName() {
		return name;
	}
	int getPosition() {
		return currentPosition;
	}
	
	void positionUP() {
		
		if (rand() % 2 == 0) {
			currentPosition++;
		}
	}
};
class Field {
protected:
	int height;
public:
	void makeField(vector<Track*>, vector<Horse*>, const int, const int);
	void startRace(vector<Track*> tracks, vector<Horse*> horse, const int amount, const int distance);
};
void clearConsole();
void clearMemory(vector<Horse*>, vector<Track*>);



int main()
{
	srand((unsigned)time(NULL));
	const int distance = 100;
	int amount;
	Field field;
	vector<Track*> tracks;
	vector<Horse*> horses;
	cout << "How many horses would you like to take part in competition " << endl;
	cin >> amount;
	for (int i = 0; i < amount; i++) {
		string name;
		cout << "Name " << i + 1 << " horse : ";
		cin >> name;
		Horse *horse = new Horse(name);
		horses.push_back(horse);
		Track *track = new Track(name.front());
		tracks.push_back(track);
	}
	field.makeField(tracks, horses, amount, distance);
	_getch();
	clearConsole();
	field.startRace(tracks, horses, amount, distance);
	clearMemory(horses, tracks);
	
	
    return 0;
}

void clearConsole() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(console, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(console, &structCursorInfo);
	SetConsoleCursorPosition(console, topLeft);
}

void Field::makeField(vector<Track*> tracks, vector<Horse*> horse, const int amount, const int distance) {
	for (int i = 0; i < amount; i++) {
		cout << endl;
		cout << endl;
		for (int j = 0; j < horse[i]->getPosition(); j++) {
			cout << " ";
		}
		tracks[i]->showTrack(distance, horse[i]->getPosition() , horse[i]->getName());
		cout << endl;
		cout << endl;
	}


}


void Field::startRace(vector<Track*> tracks, vector<Horse*> horse, const int amount, const int distance) {
	bool finish = false;

	while (!finish) {
		Sleep(20);
		clearConsole();
		for (int i = 0; i < amount; i++) {
			horse[i]->positionUP();
		}
		makeField(tracks, horse, amount, distance);

		for (int i = 0; i < amount; i++) {
			if (horse[i]->getPosition() >= distance) {
				cout << "The Winner is: " << horse[i]->getName() << endl;
				finish = true;
				break;
			}
		}
		
		
	}

}



void clearMemory(vector<Horse*>horse, vector<Track*>tracks) {
	for (int i = 0; i < horse.size(); i++) {
		delete horse[i];
		delete tracks[i];
	}
}