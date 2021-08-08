#include <iostream>

#include <generate_random.h>
#include "elf_names.h"

using namespace std;

string GetStringFromStream(const std::string &message) {
    std::string str;
    while (true) {
        cout << message << endl;
        getline(cin, str);
        if (cin.fail() || str.empty()) {
            cin.clear();
            cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    return str;
}


string RequestElfNameFromUser(const std::string &message) {
#if ENABLE_TESTING == 1

#define MAX_NUMBER_OF_ELFS (100)
    static bool initialized = false;
    static string names[MAX_NUMBER_OF_ELFS];
    static int ptr = 0;
    if (!initialized) {
        int emptyHouses[5];
        auto generator = IntRandom();
        for (int &emptyHouse : emptyHouses) {
            emptyHouse = generator.generateRandom(0, MAX_NUMBER_OF_ELFS);
        }

        for (int i = 0; i < MAX_NUMBER_OF_ELFS; ++i) {
            for (int &emptyHouse : emptyHouses) {
                if (i == emptyHouse) {
                    names[i] = "None";
                }
            }

            if (names[i].empty()) {
                names[i] = "Elf " + to_string(i);
            }
        }
        initialized = true;
    }
    cout << names[ptr] << endl;
    return names[ptr++];
#else
    return GetStringFromStream(message);
#endif
}
