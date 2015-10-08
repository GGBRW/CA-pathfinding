#include <iostream>
#include <deque>
#include <vector>
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>
#include <ctime>

using namespace std;

struct start {
public:
	int x = 10, y = 10;
} start;

struct destination {
public:
	int x = 30, y = 12;
} destination;

struct path {
public:
	int x, y, age;
} path;

string positions[32][16];

class pathfinder {
public:
	int x, y, age;
};

deque<pathfinder> pathfinders;

double pi = M_PI;

int main() {
	for (int x = 0; x < 32; x++) {
		for (int y = 0; y < 16; y++) {
			positions[x][y] = " ";
		}
	}

	positions[10][10] = "S";
	positions[30][12] = "E";

	positions[7][7] = "X";
	positions[8][7] = "X";
	positions[9][7] = "X";
	positions[10][7] = "X";
	positions[11][7] = "X";
	positions[12][7] = "X";
	positions[13][7] = "X";
	positions[14][7] = "X";
	positions[14][8] = "X";
	positions[14][9] = "X";
	positions[14][10] = "X";
	positions[14][11] = "X";
	positions[14][12] = "X";
	positions[14][13] = "X";
	positions[13][13] = "X";
	positions[12][13] = "X";
	positions[11][13] = "X";
	positions[10][13] = "X";
	positions[9][13] = "X";
	positions[8][13] = "X";
	positions[7][13] = "X";
	positions[7][12] = "X";
	positions[7][11] = "X";
	positions[7][10] = "X";
	positions[6][10] = "X";
	positions[5][10] = "X";
	positions[4][10] = "X";
	positions[4][9] = "X";
	positions[4][8] = "X";
	positions[4][7] = "X";

	positions[20][1] = "X";
	positions[20][2] = "X";
	positions[20][3] = "X";
	positions[20][4] = "X";
	positions[20][5] = "X";
	positions[20][6] = "X";
	positions[20][7] = "X";
	positions[20][8] = "X";
	positions[20][9] = "X";
	positions[20][10] = "X";
	positions[20][11] = "X";
	positions[20][12] = "X";
	positions[20][13] = "X";
	positions[20][14] = "X";

	positions[24][4] = "X";
	positions[24][5] = "X";
	positions[24][6] = "X";
	positions[24][7] = "X";
	positions[24][8] = "X";
	positions[24][9] = "X";
	positions[24][10] = "X";
	positions[24][11] = "X";
	positions[24][12] = "X";
	positions[24][13] = "X";
	positions[24][14] = "X";
	positions[24][15] = "X";

	clock_t time = clock();
	for (double r = 0, len = 2 * M_PI; r < len; r += .25 * pi) {
		int x = start.x + round(sin(r)), y = start.y + round(cos(r));
		positions[x][y] = "1";

		pathfinder p = { x, y, 0 };
		pathfinders.push_front(p);
	}


	int age = 2;
	bool reachedDestination = false;
	while (!reachedDestination) {
		deque<pathfinder> newPathfinders;
		for (int i = 0; i < pathfinders.size(); i++) {
			for (double r = 0, len = 2 * pi; r < len; r += .25 * pi) {
				int x = pathfinders[i].x + round(sin(r)),
					y = pathfinders[i].y + round(cos(r));
				if (positions[x][y] == " " && x < 33 && x > 0 && y < 16 && y > 0) {
					positions[x][y] = to_string(age);

					pathfinder p = { x, y, 0 };
					newPathfinders.push_front(p);
				}
			}
		}
		pathfinders.insert(pathfinders.end(), newPathfinders.begin(), newPathfinders.end());
		age++;

		for (double r = 0 * pi, len = 2.5 * pi; r < len; r += .5 * pi) {
			int x = destination.x + round(sin(r)),
				y = destination.y + round(cos(r));
			if (positions[x][y] != " ") {
				reachedDestination = true;

				path = { x, y, stoi(positions[x][y]) };

				positions[x][y] = "#";
				break;
			}
			if (r == 2 * pi) {
				r = .25 * pi;
			}
		}
	}

	bool reachedStart = false;
	int afstand = 0;
	for (int i = 0; i < 60; i++) {
		for (double r = 0, len = 2.5 * pi; r < len; r += .5 * pi) {
			int x = path.x + round(sin(r)),
				y = path.y + round(cos(r));

			try {
				int age = stoi(positions[x][y]);

				if (path.age - 1 == age) {
					path = { x, y, age };
					if (age > 9) {
						positions[x][y] = "#";
					}
					else {
						positions[x][y] = "#";
					}
					afstand++;
					break;
				}
			}
			catch (...) {}

			if (r == 2 * pi) {
				r = .25 * pi;
			}
		}
	}

	for (int y = 0; y < 16; y++) {
		for (int x = 0; x < 32; x++) {
			if (positions[x][y] == "S" || positions[x][y] == "E" || positions[x][y] == "X" || positions[x][y] == "#") {
				cout << positions[x][y] << " ";
			}
			else {
				cout << "  ";
			}
		}
		cout << "\n";
	}
	cout << "---------------------------------------------------------------\n\n";
	cout << "S: beginpunt, E: eindpunt: X: obstakel, #: pad \n\n";
	cout << "Kortste pad gevonden in: " << (clock() - time) / 10 << " miliseconde(n) \n";
	cout << "Afstand: " << afstand << " metertjes\n\n";
	
	// Om te voorkomen dat de console sluit na uitvoering...
	int hoi;
	cin >> hoi;
	return 0;
}