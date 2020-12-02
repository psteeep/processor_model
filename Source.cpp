#define _CRT_SECURE_NO_WARNINGS
#define bits 20
#include <iostream>
#include <fstream>
#pragma warning(disable:4996)


using namespace std;

string a;
int R1, R2, PC, TC, PS;

void print_bit(int v) {
    for (int i = bits - 1; i >= 0; i--) {
        if (i % 4 == 3)cout << ' ';
        cout << !!(v & (1 << i));
    }
}
void print1(const char* a, char x, int v) {
    cout << "\nComand =" << a << "R" << x;
    print_bit(v);
    cout << "\nR1 =";
    print_bit(R1);
    cout << "    Ins =" << a << "| R" << x << " |";
    print_bit(v);
    cout << "\nR2 =";
    print_bit(R2);
    cout << "    PC = " << ++PC;
    cout << "    PS = " << PS;
}
void print2(const char* a, char x, char y) {
    cout << "\nCommand =" << a << "R" << x << ", R" << y;
    cout << "\nR1 =";
    print_bit(R1);
    cout << "    Ins =" << a << "| R" << x << " | R" << y;
    cout << "\nR2 =";
    print_bit(R2);
    cout << "    PC = " << ++PC;
    cout << "    TC = " << ++TC;
    cout << "    PS = " << PS;
}


void mov(char a, int b) {
    if (a == '1')R1 = b;
    if (a == '2')R2 = b;
    PS = !!(b >> (bits - 1));
}



void inv(char* a, char* b) {
    //зрівнять їх по довжині

    bool even = !(bool)b[bits - 1];

    for (int i = 0; i < bits; ++i) {
        bool sum = !a[i] && b[i] || a[i] && !b[i];

        if (even) {
            if (!sum) {
                //inverse
                a[i] = !a[i];
                PS = !!(*b >> (bits - 1));
            }
        }
        else {
            if (sum) {
                //inverse
                a[i] = !a[i];
                PS = !!(*b >> (bits - 1));
            }
        }
    }
}


int main() {
    cout << "Start";
    std::ifstream in("input.txt");
    char tmp[256];
    while (in.good()) {
        in >> a;
        if (a == "mov" || a == "Mov") {
            in >> a;
            size_t i = 3;
            for (i; i < a.length(); i++) tmp[i - 3] = a[i];
            tmp[i - 3] = 0;
            print1(" mov ", a[1], atoi(tmp));
            PC--;
            mov(a[1], atoi(tmp));
            cin.get();
            print1(" mov ", a[1], atoi(tmp));
            cin.get();
            TC = 0;
            cout << endl;
        }
    
        if (a == "inv" || a == "Inv") {
            in >> a;
            print2(" inv ", a[1], a[4]);
            PC--;
            inv(&a[1], &a[4]);
            cin.get();
            print2(" inv ", a[1], a[4]);
            cin.get();
            TC = 0;
            cout << endl;
        }
    }
    return 0;
}