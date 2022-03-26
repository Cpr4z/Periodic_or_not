#include <iostream>
#include <string>
#include<vector>
using namespace std;
vector <char> periodic;

void computeLPS(const string pat, int* lps)
{
    int j = 0;

    lps[0] = 0; 

    int i = 1;
    while (i < pat.size()) {
        if (pat[i] == pat[j]) {
            j++;
            lps[i] = j;
            i++;
        }
        else
        {
            if (j != 0) {
                j = lps[j - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}
bool IsKPeriodic(const string pattern,int k)
{
	if (k <= 0) 
	{
		while (k <= 0) {
			cout << "Input correct number";
			cin >> k;
			cout << endl;
		}
	}
    int *lps=new int[pattern.size()];
    int i = 0;
    int j = 0;
    computeLPS(pattern, lps);
    
    while (i < pattern.size())//движемся по строке до ее конца
    { 
        while (lps[i] == 0)//пока lps[i]=0 записываем строку
        {
            periodic.push_back(pattern[i++]);
        }
        if (periodic.size() != k) {
            return false;
        }
        if (lps[i] != 0)//проверка, что элемент в массиве не равен нулю
        {
            while (lps[i] != 0&&i<pattern.size())
            {
                if (j < periodic.size())//пока не дошли до конца повторяющейся строки
                {
                    if (pattern[i] == periodic[j]) {
                        i++;
                        j++;
                        continue;
                    }
                    else {
                        return false;
                    }
                }
                else
                {
                    j = 0;
                    continue;
                }
            }
        }
        else {
            return false;
        }
    }


	return true;
}
int main() {
	bool state= IsKPeriodic("periodicperiodic",8);
    if (state) {
        for (const char i : periodic) {
            cout << i;
        }
    }
    else {
        cout << "Pattern isn't periodic";
    }
	return 0;
}