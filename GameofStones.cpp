// Memoize!
// GameofStones.cpp : https://www.hackerrank.com/challenges/game-of-stones-1/problem

#include <bits/stdc++.h>

using namespace std;
typedef vector<int> Myvec;

#define UNDEF  0
#define _R1(x) x.begin(), x.end()
#define _R2(x) auto iter = x.begin(); iter != x.end(); ++iter

Myvec Stones {2, 3, 5};
Myvec WinnerIs(101, UNDEF);		// initialize as 0/undef

bool first_is_winner(int n)
{

	if (WinnerIs[n] != UNDEF)
	{
		if (WinnerIs[n] == 1)
			return true;
		else if (WinnerIs[n] == 2)
			return false;
		else
		{
			cout << "Internal error" << endl;
			exit(1);
		}
	}

	for (_R2(Stones))
		if (!first_is_winner(n - *iter))
		{
			WinnerIs[n] = 1;
			return true;
		}
			
	WinnerIs[n] = 2;
	return false;
}

int main()
{
    // set obvious results:
	WinnerIs[1] = 2;			// cant remove any
	WinnerIs[2] = 1;			// remove 2 stones
	WinnerIs[3] = 1;			// remove 2 stones
	WinnerIs[4] = 1;			// remove 3 stones
	WinnerIs[5] = 1;			// remove 5 stones
	WinnerIs[6] = 1;			// remove 5 stones

    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (first_is_winner(n))
            fout << "First" << "\n";
        else
            fout << "Second" << "\n";
    }

    fout.close();

    return 0;
}
