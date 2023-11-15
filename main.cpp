#include <iostream>
#include "machine.h"
int main() {
        cout << "1- Load file\n";
        cout << "2- Run untill halt\n";
        cout << "3- Display\n";
        cout << "4- Exit\n";
        cout << "Please enter the choice : \n";
        int ch;
        machine m("file.txt");
        while (ch != 4)
        {
            cin >> ch;
            if (ch == 1)
            {
                machine m("file.txt");
            }
            else if (ch == 2)
            {
                m.run();
            }
            else if (ch == 3)
            {
                Display(m);
            }
            else
            {
                break;
            }
        }
        return 0;
}
