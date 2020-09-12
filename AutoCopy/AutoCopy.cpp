#include <bits/stdc++.h>
#include <io.h>
#include <fcntl.h>
#include <conio.h>
#include <regex>
#include <windows.h>

using namespace std;

bool ALL[700005];
vector<string> Lop = { "input ", "lop 1.txt", "lop 2.txt", "lop 3.txt", "lop 4.txt", "lop 5.txt", "lop 6.txt",
"lop 7.txt", "lop 8.txt", "lop 9.txt", "lop 10.txt", "lop 11.txt", "lop 12.txt" };
int Class, Max = 0;

void set_DefaultSize_Console();
void checkNo_Exist_or_Empty_File(wifstream& File, string FileName);
void Input_Class();
void Input_Number();
void ProcessData();
int convert_Wstring_to_Number(wstring x);
void End_Program();

int main() {
    SetConsoleOutputCP(65001);
    set_DefaultSize_Console();
    _setmode(_fileno(stdin), 0x00020000);
    _setmode(_fileno(stdout), 0x00020000);
    //Input_Class();
    Class = 6;
    Input_Number();
    ProcessData();
    End_Program();
    return 0;
}
void set_DefaultSize_Console() {
    HWND console = GetConsoleWindow();
    RECT ConsoleRect;
    GetWindowRect(console, &ConsoleRect);
    MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 700, 250, TRUE);
}
void checkNo_Exist_or_Empty_File(wifstream& File, string FileName) {
    wstring tmp;
    tmp.assign(FileName.begin(), FileName.end());
    if (!File || File.peek() == wifstream::traits_type::eof()) {
        wcout << L"File " << tmp << L" không tồn tại hoặc rỗng" << endl;
        End_Program();
        exit(EXIT_FAILURE);
    }
}
void Input_Class() {
    wcout << L"Nhập lớp: ";
    do {
        wcin >> Class;
        if (Class < 0 || Class > 12)
            wcout << L"Lớp không hợp lệ, vui lòng nhập lại: ";
    } while (Class < 0 || Class > 12);
}
void Input_Number() {
    wifstream fin("num.txt", ios::in);
    checkNo_Exist_or_Empty_File(fin, "num.txt");
    while (!fin.eof()) {
        int tmp = 0;
        fin >> tmp;
        ALL[tmp] = true;
        if (tmp > Max)
            Max = tmp;
    }
    if (Max == 0) {
        wcout << L"File num.txt rỗng" << endl;
        End_Program();
        exit(EXIT_FAILURE);
    }
    fin.close();
}
void ProcessData() {
    wifstream fin(Lop[0] + Lop[Class], ios::in);
    checkNo_Exist_or_Empty_File(fin, Lop[0] + Lop[Class]);
    wofstream fout("output " + Lop[Class], ios::out);
    bool flag = false;
    int counter = 0;
    while (!fin.eof() && counter < Max) {
        wstring line;
        getline(fin, line);
        int num = convert_Wstring_to_Number(line);
        if (num > 0) {
            ++counter;
            if (ALL[num]) {
                fout << line << endl;
                flag = true;
            }
            else
                flag = false;
        }
        else if (flag == true)
            fout << line << endl;
    }
    wcout << L"Done!" << endl;
    fin.close();
    fout.close();
}
int convert_Wstring_to_Number(wstring x) {
    int num = 0;
    wregex findNumber(L"^[0-9]+");
    for (wsregex_iterator i = wsregex_iterator(x.begin(), x.end(), findNumber); i != wsregex_iterator(); ++i) {
        wstring tmp = ((wsmatch)*i)[0];
        num = (int)stoll(tmp.substr(0, tmp.size()));
    }
    return num;
}
void End_Program() {
    do
        wcout << L"Nhấn phím bất kì để thoát";
    while (_getch() == 0);
}
