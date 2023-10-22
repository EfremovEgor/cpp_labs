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

    bool swapped = true;
    int n = a.size();
    int start = 0;
    int end = n - 1;

    while (swapped)
    {
        swapped = false;
        // Цикл слева направо, как при сортировке пузырьком
        for (int i = start; i < end; ++i)
        {
            if (a[i] > a[i + 1])
            {
                swap(a[i], a[i + 1]);
                swapped = true;
            }
        }
        // Если ничего не сдвинулось, то массив отсортирован
        if (!swapped)
            break;
        // Иначе нужно сбросить флаг, чтобы его можно было использовать на следующем этапе
        swapped = false;
        // сдвинуть конец массива на один, так как значение на последнем месте всегда самое большое
        --end;
        // То же самое, только в обратном порядке
        for (int i = end - 1; i >= start; --i)
        {
            if (a[i] > a[i + 1])
            {
                swap(a[i], a[i + 1]);
                swapped = true;
            }
        }
        // Сдвинуть начало массива на один, так как наименьшее значение будет всегда в самом начале
        ++start;
    }
    return a;
}