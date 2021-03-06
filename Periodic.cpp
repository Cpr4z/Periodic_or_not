#include <iostream>
#include <string>
#include<vector>
#include <Windows.h>
using namespace std;


void computeLPS(const string pat, int* lps){
    int j = 0;

    lps[0] = 0; // lps[0] is always 0 

    int i = 1;
    while (i < pat.size()) {
        if (pat[i] == pat[j]) {
            j++;
            lps[i] = j;
            i++;
        }
        else{
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
bool IsKPeriodic(const string pattern,int k){
	if (k <= 0) {
		while (k <= 0) {
			cout << "Input correct number";
			cin >> k;
			cout << endl;
		}
	}
    int *lps=new int[pattern.size()];
    vector <char> periodic;
    int i = 0;
    int j = 0;
    computeLPS(pattern, lps);
    if (k == pattern.size()) {
        for ( ; i < pattern.size(); i++){
            periodic.push_back(pattern[i]);
        }
        return true;
    }
    if (pattern.size() / k < 2){
        return false;
    }
    while (i < pattern.size()){//движемся по строке до ее конца
        while (lps[i] == 0){//пока lps[i]=0 записываем строку
            periodic.push_back(pattern[i++]);
        }
        if (periodic.size() != k){
            if (k / periodic.size() > 1 && k % periodic.size() == 0){
                while (i < k){
                  periodic.push_back(pattern[i++]);      
                }
            }
            else 
            {
                cout << "Pattern isn't periodic ";
                return false;
            }
                
                
        }
        
        if (lps[i] != 0){//проверка, что элемент в массиве не равен нулю
            while (lps[i] != 0&&i<pattern.size()){
                if (j < periodic.size()){//пока не дошли до конца повторяющейся строки
                    if (pattern[i] == periodic[j]){
                        i++;
                        j++;
                        continue;
                    }
                    else {
                        cout << "Pattern isn't periodic ";
                        return false;
                    }
                }
                else{
                    j = 0;
                  
                    continue;
                }
            }
        }
        else{
            cout << "Pattern isn't periodic ";
            return false;
        }
    }
   
    for (const char i : periodic){
        cout << i;
    }
    cout << endl;
    periodic.clear();
	return true;
}
void testFunction(const string str, int k, bool expectation){
    auto result = IsKPeriodic(str, k);
    cout << str << " is " << (result ? "periodic by " : "non-periodic by ") << k << " ";

    static const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    if (result == expectation){
        SetConsoleTextAttribute(handle, 0xA0);//set green background and black text color
        cout << "PASSED" << endl;
    }
    else{
        SetConsoleTextAttribute(handle, 0x40);//set red background and black text color
        cout << "FAILED" << endl;
    }
    SetConsoleTextAttribute(handle, 0x0f);//set default text color
}
int main() {
    //one sym block
    testFunction("aaaaaa", 1, true);
    testFunction("aaaaaa", 2, true);
    testFunction("aaaaaa", 3, true);
    testFunction("aaaaaa", 4, false);
    testFunction("aaaaaa", 5, false);
    testFunction("aaaaaa", 6, true);
    //two sym block
    testFunction("ababab", 1, false);
    testFunction("ababab", 2, true);
    testFunction("ababab", 3, false);
    testFunction("ababab", 4, false);
    testFunction("ababab", 5, false);
    testFunction("ababab", 6, true);
    //more symbols
    testFunction("abababab", 1, false);
    testFunction("abababab", 2, true);
    testFunction("abababab", 3, false);
    testFunction("abababab", 4, true);
    testFunction("abababab", 5, false);
    testFunction("abababab", 6, false);
    testFunction("abababab", 7, false);
    testFunction("abababab", 8, true);
    
	return 0;
}