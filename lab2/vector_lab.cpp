#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <random>
#include "utilities.cpp"

using namespace std;
class StudentAnalyzer
{
private:
    vector<int> marks;
    vector<string> names;
    vector<int> getModals()
    {
        map<int, int> entries;
        for (auto &&i : this->marks)
        {
            if (entries.count(i) == 0)
            {
                entries[i] = 1;
                continue;
            }
            entries[i]++;
        };
        int current_max_entry = 0;
        vector<int> modals;
        for (auto elem : entries)
        {
            if (current_max_entry < elem.second)
            {
                modals.clear();
                current_max_entry = elem.second;
            }
            if (current_max_entry == elem.second)
            {
                modals.push_back(elem.first);
            }
        }
        return modals;
    };
    int getMedian()
    {
        vector<int> sorted_marks = ShakerSort(this->marks);
        return sorted_marks[int(this->marks.size() / 2)];
    };
    float getAverage()
    {
        int sum = accumulate(this->marks.begin(), this->marks.end(), 0);
        return sum / this->marks.size();
    }

public:
    void deleteContent(int position)
    {
        if (this->marks.size() < position)
        {
            throw invalid_argument("Position is larger than contents");
        }

        this->marks.erase(this->marks.begin() + position - 1);
        this->names.erase(this->names.begin() + position - 1);
    };
    void addContent(pair<string, int> content)
    {
        this->names.push_back(content.first);
        this->marks.push_back(content.second);
    };
    void setContents(vector<string> names, vector<int> marks)
    {
        if (marks.size() != names.size())
        {
            throw invalid_argument("Containers aren't the same size");
        }
        this->marks = vector<int>(marks);
        this->names = vector<string>(names);
    }
    void printContents()
    {
        int counter = 1;
        for (pair<string, int> item : zip(this->names, this->marks))
        {

            cout << counter << ". " << item.first << ": " << item.second << "\n";
            counter++;
        }
    };
    void printContentsIterator()
    {
        auto items = zip(this->names, this->marks);
        int counter = 1;
        for (auto it = items.begin(); it != items.end(); ++it)
        {
            cout << counter << ". " << (*it).first << ": " << (*it).second << "\n";
            counter++;
        }
    };
    void printContentsIndexBased()
    {
        auto items = zip(this->names, this->marks);
        for (int i = 0; i < items.size(); i++)
        {
            cout << i + 1 << ". " << items[i].first << ": " << items[i].second << "\n";
        }
    };
    void printInformation()
    {
        float average = getAverage();
        cout << "Среднее значение: " << average << "\n";

        int median = getMedian();
        cout << "Медианное значение: " << median << "\n";

        vector<int> modals = getModals();
        cout << "Мода:";
        for (auto elem : modals)
        {
            cout << "\n"
                 << elem;
        }
        cout << "\n\n";
    }
};

class UserMenu
{
private:
    StudentAnalyzer studentAnalyzer;
    void initiateUserExit()
    {
        cout << "Программа завершена";
        exit(0);
    };
    void initializeVectors()
    {
        while (true)
        {
            cout << "Выберите способ инициализации векторов имен и оценок:\n";
            cout << "[1] Демонстрационный вариант\n";
            cout << "[2] Случайные значения\n";
            cout << "[3] Ручной ввод\n";
            cout << "[4] Выход\n";
            int action;
            cin >> action;
            if (!(action >= 1 && action <= 4))
            {
                cout << "\n[Ошибки] Неверное действие\n \n";
                continue;
            }
            handleInitializeVectors(action);
            break;
        };
    }
    void handleInitializeVectors(int action)
    {
        if (action == 1)
            this->studentAnalyzer.setContents(DEMO_NAMES, DEMO_MARKS);
        if (action == 2)
        {
            cout << "Введите желаемый размер выборки: ";
            int max_length;
            cin >> max_length;
            vector<int> marks;
            vector<string> names;
            for (int i = 0; i < max_length; i++)
            {
                marks.push_back(rand() % 100 + 1);
                names.push_back(NAME_SAMPLE[rand() % NAME_SAMPLE.size()]);
            }
            this->studentAnalyzer.setContents(names, marks);
        }
        if (action == 3)
        {
            handleInitializeVectorsUserInput();
        }
        if (action == 4)
            initiateUserExit();
    };
    void handleInitializeVectorsUserInput()
    {
        vector<int> marks;
        vector<string> names;
        int max_length = 0;

        while (!(max_length > 0))
        {
            cout << "Введите размер контейнера [1,...]: ";
            cin >> max_length;
        }

        for (int i = 0; i < max_length; i++)
        {
            cout << "\n==================" << i + 1 << "==================";
            cout << "\nВведите имя: ";
            string name;
            cin >> name;
            int mark = -1;
            while (!(mark >= 0))
            {
                cout << "\nВведите оценку: ";
                cin >> mark;
            }
            marks.push_back(mark);
            names.push_back(name);
        }
        this->studentAnalyzer.setContents(names, marks);
    };
    void investigateMainMenu()
    {
        while (true)
        {
            cout << "Выберите действие:\n";
            cout << "[1] Добавить Имя/Значение\n";
            cout << "[2] Удалить Имя/Значение\n";
            cout << "[3] Вывести Имя/Значение\n";
            cout << "[4] Информация по оценкам\n";
            cout << "[5] Выход\n";
            int action;
            cin >> action;
            if (!(action >= 1 && action <= 5))
            {
                cout << "\n[Ошибки] Неверное действие\n \n";
                continue;
            }

            handleInvestigateMainMenu(action);
        };
    }
    void handleDeletePosition()
    {
        while (true)
        {

            cout << "Введите номер позиции, чтобы удалить:";
            int position;
            cin >> position;
            try
            {
                this->studentAnalyzer.deleteContent(position);
            }
            catch (const invalid_argument e)
            {
                cout << "\n[Ошибка] Номер позиции должен быть не больше размера контейнера.\n\n";
                continue;
            };
            return;
        }
    }
    void handleInvestigateMainMenu(int action)
    {
        if (action == 1)
        {
            cout << "Введите имя:";
            string name;
            cin >> name;
            cout << "Введите балл:";
            int mark;
            cin >> mark;
            this->studentAnalyzer.addContent(pair<string, int>(name, mark));
        }
        if (action == 2)
        {
            this->studentAnalyzer.printContents();
            handleDeletePosition();
        }
        if (action == 3)
            this->studentAnalyzer.printContents();
        // this->studentAnalyzer.printContentsIterator();
        // this->studentAnalyzer.printContentsIndexBased();
        if (action == 4)
            this->studentAnalyzer.printInformation();
        if (action == 5)
            initiateUserExit();
    }

public:
    void startMainLoop()
    {
        this->studentAnalyzer = StudentAnalyzer();
        initializeVectors();
        investigateMainMenu();
    };
};

int main()
{
    UserMenu user_menu = UserMenu();
    user_menu.startMainLoop();
    return 0;
}