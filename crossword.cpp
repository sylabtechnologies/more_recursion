// *temp*
// 08_crossword.cpp : https://www.hackerrank.com/challenges/crossword-puzzle/problem
// - use adjacency lists

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <iterator>
#include <string>
#include <sstream>
using namespace std;

void process_error(const string, const int);
#define _OS(x) ostream_iterator<x>(cout, " ")
#define _CR cout << endl
#define _R1(x) x.begin(), x.end()
#define _R2(x) auto iter = x.begin(); iter != x.end(); ++iter
#define PRN(x) cout << x << endl
#define PRV(x) copy(_R1(x), _OS(string)); _CR
#define ERR(X) process_error(X, __LINE__)
#define	NORTH 'N'
#define	EAST  'E'
#define	BLACK '+'
#define	WHITE '-'
#define	EMPTY ' '

typedef vector<string> Myvec;

struct Crossword
{
	int cur_x;
	int cur_y;
	Myvec lines;
};

struct Connector
{
	int x_coord;
	int y_coord;
	char value;
};

struct WordConnector
{
	int ref_num;
	int connects_at;
	int connects_to;
	char value;
};

struct Wordholder
{
	bool solved;
	char orientation;
	string word;
	int length;
	int x_start;
	int y_start;
	vector<WordConnector> connections;
};

struct CwdSolution
{
	vector<Wordholder> words;
	int horiz_words;
	int total_words;
	bool solved;
};

Myvec parseWords(const string& words)
{
	istringstream mystream(words);
	Myvec puzzle;
	string token;

	while (getline(mystream, token, ';'))
	{
		puzzle.push_back(token);
	}

	return puzzle;
}

void scanCwdString(CwdSolution& solution, Crossword& cwords, const string& curline, char myorientation)
{
	bool found = false;
	Wordholder holder;

	for (size_t j = 0; j < curline.length(); j++)
	{
		if (found)
		{
			if (j == curline.length() - 1)
				if (holder.length > 1)
					solution.words.push_back(holder);

			if (curline[j] == BLACK)
			{
				found = false;

				// ignore 1 cells
				if (holder.length > 1)
					solution.words.push_back(holder);
			}
			else
				holder.length++;

			continue;
		}

		if (curline[j] == BLACK) continue;

		// initiate new holder;
		holder.orientation = myorientation;
		holder.length = 1;
		found = true;

		if (myorientation == EAST)
		{
			holder.x_start = cwords.cur_x + j;
			holder.y_start = cwords.cur_y;
		}
		else if (myorientation == NORTH)
		{
			holder.x_start = cwords.cur_x;
			holder.y_start = cwords.cur_y + j;
		}
		else ERR("internal error");

	}
}

CwdSolution parseCwd(Crossword& cwords)
{
	CwdSolution solution;

	// scan horizontally
	for (size_t i = 0; i < cwords.lines.size(); i++)
	{
		cwords.cur_x = 0;
		cwords.cur_y = i;
		scanCwdString(solution, cwords, cwords.lines[i], EAST);
	}

	solution.horiz_words = solution.words.size();

	// scan vertically
	for (size_t i = 0; i < cwords.lines[0].length(); i++)
	{
		string temp;
		for (size_t j = 0; j < cwords.lines.size(); j++)
		{
			temp.push_back(cwords.lines[j][i]);
		}

		// scanCwdString(solution, temp, NORTH, i);
		cwords.cur_x = i;
		cwords.cur_y = 0;
		scanCwdString(solution, cwords, temp, NORTH);
	}

	solution.total_words = solution.words.size();

	// scan vertical connections
	for (size_t i = 0; i < solution.horiz_words; i++)
	{
		int current_y = solution.words[i].y_start;
		int x_start = solution.words[i].x_start;
		int x_finish = x_start + solution.words[i].length - 1;

		for (size_t j = solution.horiz_words; j < solution.total_words; j++)
		{
			int vline = solution.words[j].x_start;

			// record intersections
			if (x_start <= vline && vline <= x_finish)
			{
				WordConnector temp;
				temp.ref_num = j;
				temp.connects_to = current_y - solution.words[j].y_start;
				temp.connects_at = vline - x_start;
				temp.value = EMPTY;
				solution.words[i].connections.push_back(temp);
			}
		}
	}

	// scan horizontal connections
	for (size_t i = solution.horiz_words; i < solution.total_words; i++)
	{
		int current_x = solution.words[i].x_start;
		int y_start = solution.words[i].y_start;
		int y_finish = y_start + solution.words[i].length - 1;

		for (size_t j = 0; j < solution.horiz_words; j++)
		{
			int hline = solution.words[j].y_start;

			// record intersections
			if (y_start <= hline && hline <= y_finish)
			{
				WordConnector temp;
				temp.ref_num = j;
				temp.connects_to = current_x - solution.words[j].x_start;
				temp.connects_at = hline - y_start;
				temp.value = EMPTY;
				solution.words[i].connections.push_back(temp);
			}
		}
	}

	solution.solved = false;
	return solution;
}


bool checkConnectors(Wordholder& place, const string& puzzle)
{
	bool notfound = true;

	for (_R2(place.connections))
	{
		if (iter->value != EMPTY) notfound = false;
	}

	return notfound;
}

void fillConnectors(CwdSolution& sol, Wordholder& place)
{
	for (_R2(place.connections))
	{
		int index = iter->ref_num;
		char connect = place.word[iter->connects_at];

		PRN(index);
		PRN(iter->connects_to);
		PRN(connect);

		// sol.words[2].connections[0].value = connect;
	}
}

CwdSolution solveCwd(CwdSolution solution, Myvec puzzle)
{
	bool found = false;
	int start;

	// find first non-filled position
	for (size_t i = 0; i < solution.total_words; i++)
	{
		if (solution.words[i].word != "") continue;

		found = true;
		start = i;
		break;
	}

	if (!found) return solution;

	for (size_t i = start; i < solution.total_words; i++)
	{
		found = false;
		for (size_t j = 0; j < puzzle.size(); j++)
		{
			if (puzzle[j].length() == solution.words[i].length)
				if (checkConnectors(solution.words[i], puzzle[j]))
				{
					PRN(puzzle[j]);

					solution.words[i].word = puzzle[j];
					fillConnectors(solution, solution.words[i]);
					puzzle.erase(puzzle.begin() + j);
					return solveCwd(solution, puzzle);
				}
		}

		if (!found) ERR("No matches found");

	}
}

int main()
{
	string words = "LONDON;DELHI;ICELAND;ANKARA";
	Myvec puzzle = parseWords(words);

	Crossword mycwd;
	mycwd.cur_x = 0;
	mycwd.cur_y = 0;
	mycwd.lines.push_back("+-++++++++");
	mycwd.lines.push_back("+-++++++++");
	mycwd.lines.push_back("+-++++++++");
	mycwd.lines.push_back("+-----++++");
	mycwd.lines.push_back("+-+++-++++");
	mycwd.lines.push_back("+-+++-++++");
	mycwd.lines.push_back("+++++-++++");
	mycwd.lines.push_back("++------++");
	mycwd.lines.push_back("+++++-++++");
	mycwd.lines.push_back("+++++-++++");

	CwdSolution solution = parseCwd(mycwd);
	solution = solveCwd(solution, puzzle);

    return 0;
}

void process_error(const string msg, const int line)
{
	cerr << __FILE__ << ", line " << line << endl;
	cerr << "Error: " << msg << endl;
	cerr << msg << endl;
	exit(1);
}

