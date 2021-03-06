#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <string>
#include <functional>
#include <fstream>
using namespace std;

#define _OS(x) ostream_iterator<x>(cout, " ")
#define _CR cout << endl
#define _R1(x) x.begin(), x.end()
#define _R2(x) auto iter = x.begin(); iter != x.end(); ++iter
#define MAX(a,b) (a > b ? a : b)
#define PRINT(X) std::cout << X << std::endl
#define PRVEC(x) copy(_R1(x), _OS(int)); _CR

typedef vector<int> I_vec;

long min_candies(int num, I_vec& ratings)
{
	bool notfound = true;
	I_vec candies( ratings.size(), 1);
	
	// pass candies to the right student
	for (size_t i = 1; i < ratings.size(); i++)
	{
		if (ratings[i] > ratings[i-1]) candies[i] += candies[i-1];
	}

	// pass candies to the left student
	std::reverse(_R1(ratings));
	std::reverse(_R1(candies));

	for (size_t i = 1; i < ratings.size(); i++)
	{
		if (ratings[i] > ratings[i - 1])
			if (candies[i] <= candies[i - 1])
				candies[i] = candies[i - 1] + 1;
	}

	return std::accumulate(_R1(candies), 0);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item;
        cin >> arr_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        arr[i] = arr_item;
    }

    long result = min_candies(n, arr);

    fout << result << "\n";

    fout.close();

    return 0;
}
