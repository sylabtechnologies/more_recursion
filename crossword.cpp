// 08_crossword.cpp : https://www.hackerrank.com/challenges/crossword-puzzle/problem
// - use adjacency lists

#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <iterator>
#include <string>
#include <sstream>
#include <fstream>
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

typedef vector<string> Myvec;

struct Crossword
{
	int cur_x;
	int cur_y;
	Myvec lines;
};

struct Filled
{
	int offset;
	char value;
};

struct WordConnector
{
	int ref_num;
	int connects_at;
	int connects_to;
};

struct Wordholder
{
	bool busy;
	char orientation;
	string word;
	int length;
	int x_start;
	int y_start;
	vector<WordConnector> connections;
	vector<Filled> checks;
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
				if (holder.length >= 1)
				{
					holder.length++;
					solution.words.push_back(holder);
				}

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
		holder.busy = false;
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
				solution.words[i].connections.push_back(temp);
			}
		}
	}

	solution.solved = false;
	return solution;
}


bool checkConnectors(Wordholder& place, const string& puzzle)
{
	if (place.checks.empty()) return true;

	for (_R2(place.checks))
	{
		int  index = iter->offset;
		char value = iter->value;

		if (puzzle[index] != value)
			return false;
	}

	return true;
}

void fillConnectors(CwdSolution& sol, Wordholder& place)
{
	for (_R2(place.connections))
	{
		Filled temp;
		int index = iter->ref_num;
		temp.offset = iter->connects_to;
		temp.value  = place.word[iter->connects_at];
		sol.words[index].checks.push_back(temp);
	}
}

CwdSolution solveCwd(CwdSolution original, Myvec puzzle)
{
	for (size_t i = 0; i < original.total_words; i++)
	{
		if (original.words[i].busy) continue;

		for (size_t j = 0; j < puzzle.size(); j++)
		{
			CwdSolution solution = original;

			if (puzzle[j].length() == solution.words[i].length)
				if (checkConnectors(solution.words[i], puzzle[j]))
				{
					// PRN(puzzle[j]);

					solution.words[i].busy = true;
					solution.words[i].word = puzzle[j];
					fillConnectors(solution, solution.words[i]);

					if (puzzle.size() == 1)
					{
						solution.solved = true;
						return solution;
					}
					else
					{
						Myvec next_pz = puzzle;
						next_pz.erase(next_pz.begin() + j);
						CwdSolution next_sol = solveCwd(solution, next_pz);
						if (next_sol.solved)
							return next_sol;
					}
				}
		}
	}

	return original;
}

void process_error(const string msg, const int line)
{
	cerr << __FILE__ << ", line " << line << endl;
	cerr << "Error: " << msg << endl;
	cerr << msg << endl;
	exit(1);
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    vector<string> crossword(10);

	Crossword mycwd;
	mycwd.cur_x = 0;
	mycwd.cur_y = 0;
    
    for (int i = 0; i < 10; i++) {
        string crossword_item;
        getline(cin, crossword_item);
        mycwd.lines.push_back(crossword_item);
    }

    string words;
    getline(cin, words);

	Myvec puzzle = parseWords(words);
	CwdSolution solution = parseCwd(mycwd);
	solution = solveCwd(solution, puzzle);
    
    // print all
	Crossword result = mycwd;

	for (size_t i = 0; i < solution.words.size(); i++)
	{
		int x = solution.words[i].x_start;
		int y = solution.words[i].y_start;
		int len = solution.words[i].length;

		if (solution.words[i].orientation == EAST)
		{
			for (size_t j = 0; j < len; j++)
			{
				result.lines[y][x+j] = solution.words[i].word[j];
			}
		}
		else if (solution.words[i].orientation == NORTH)
		{
			for (size_t j = 0; j < len; j++)
			{
				result.lines[y + j][x] = solution.words[i].word[j];
			}
		}
		else ERR("N/E error");
	}

	for (size_t i = 0; i < result.lines.size(); i++)
	{
		fout << result.lines[i] << endl;
	}

    fout.close();

    return 0;
}
