#include <vector>
#include <stdexcept>
#include <string>
using namespace std;
const vector<string> DEMO_NAMES{"James", "Robert", "John", "Michael", "David", "William", "Richard", "Joseph", "Thomas", "Christopher"};
const vector<int> DEMO_MARKS{45, 16, 87, 7, 79, 3, 7, 87, 82, 66};
const vector<string> NAME_SAMPLE{"Adam", "Adrian", "Alan", "Alexander", "Andrew", "Anthony", "Austin", "Benjamin", "Blake", "Boris", "Brandon", "Brian", "Cameron", "Carl", "Charles", "Christian", "Christopher", "Colin", "Connor", "Dan", "David", "Dominic", "Dylan", "Edward", "Eric", "Evan", "Frank", "Gavin", "Gordon", "Harry", "Ian", "Isaac", "Jack", "Jacob"};

vector<pair<string, int>> zip(vector<string> container1, vector<int> container2)
{
    if (container1.size() != container2.size())
    {
        throw invalid_argument("Containers aren't the same size");
    };
    vector<pair<string, int>> result;
    for (int i = 0; i < container1.size(); i++)
    {
        result.push_back(pair<string, int>(container1[i], container2[i]));
    }
    return result;
}

vector<int> ShakerSort(vector<int> a)
{
    int m = a.size();
    int i, j, k;
    for (i = 0; i < m;)
    {
        for (j = i + 1; j < m; j++)
        {
            if (a[j] < a[j - 1])
                swap(a[j], a[j - 1]);
        }
        m--;
        for (k = m - 1; k > i; k--)
        {
            if (a[k] < a[k - 1])
                swap(a[k], a[k - 1]);
        }
        i++;
    }
    return a;
}