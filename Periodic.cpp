#include <iostream>
#include <string>
#include<vector>
#include <Windows.h>
using namespace std;
vector <char> periodic;

void computeLPS(const string pat, int* lps)
{
    int j = 0;

    lps[0] = 0; // lps[0] is always 0 

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
    if (k == pattern.size()) {
        
        for ( ; i < pattern.size(); i++)
        {
            periodic.push_back(pattern[i]);
        }
        return true;
    }
    if (periodic.size() % pattern.size() != 0)
    {
        return false;
    }
    while (i < pattern.size())//движемся по строке до ее конца
    { 
        while (lps[i] == 0)//пока lps[i]=0 записываем строку
        {
            periodic.push_back(pattern[i++]);
        }
        if (periodic.size() != k) {
            if (k / periodic.size() > 1 && k % periodic.size() == 0) 
            {
                while (i < k) 
                {
                  periodic.push_back(pattern[i++]);      
                }
            }
            else {
                return false;
            }
                
                
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
void testFunction(const string str, int k, bool expectation)
{
    auto result = IsKPeriodic(str, k);
    cout << str << " is " << (result ? "periodic by " : "non-periodic by ") << k << " ";

    static const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    if (result == expectation)
    {
        SetConsoleTextAttribute(handle, 0xA0);//set green background and black text color
        cout << "PASSED" << endl;
    }
    else
    {
        SetConsoleTextAttribute(handle, 0x40);//set red background and black text color
        cout << "FAILED" << endl;
    }
    SetConsoleTextAttribute(handle, 0x0f);//set default text color
}
int main() {
	bool state = IsKPeriodic("abababab",4);
    if (state) {
        for (const char i : periodic) {
            cout << i;
        }
    }
    else {
        cout << "Pattern isn't periodic";
    }
    //one sym block
    testFunction("aaaaaa", 1, true);//да
    testFunction("aaaaaa", 2, true);//нет
    testFunction("aaaaaa", 3, true);//нет
    testFunction("aaaaaa", 4, false);//да
    testFunction("aaaaaa", 5, false);//да
    testFunction("aaaaaa", 6, true);//да
    //two sym block
    testFunction("ababab", 1, false);//да
    testFunction("ababab", 2, true);//нет
    testFunction("ababab", 3, false);//да
    testFunction("ababab", 4, false);//да
    testFunction("ababab", 5, false);//да
    testFunction("ababab", 6, true);//да
    //more symbols
    testFunction("abababab", 1, false);//да
    testFunction("abababab", 2, true);//нет
    testFunction("abababab", 3, false);//да
    testFunction("abababab", 4, true);//нет
    testFunction("abababab", 5, false);//да
    testFunction("abababab", 6, false);//да
    testFunction("abababab", 7, false);//да
    testFunction("abababab", 8, true);//да
    
	return 0;
}