#include <iostream>
#include <string>
#include <cassert>

#include <elf_names.h>
#include <elf_tree.h>

using namespace std;

int main() {
    auto * generator = new IntRandom();
    Tree * trees[5];

    int i = 1;
    for (auto & tree : trees) {
        cout << "Tree " << i << " :" << endl;
        tree = new Tree (generator);
        ++i;
    }

    while (true) {
        string cmd = GetStringFromStream("Enter command (seek|exit)");
        if (cmd == "seek") {
            string elfName =  GetStringFromStream("Enter elf name");
            int numOfNeighbours = -1;
            for(auto & tree : trees) {
                if(tree->SearchElf(elfName, &numOfNeighbours)) {
                    break;
                }
            }
            if(numOfNeighbours >= 0) {
                cout << "The elf \"" << elfName << "\" has found and he has " << numOfNeighbours << " neighbours." << endl;
            } else {
                cout << "The elf \"" << elfName << "\" has not found." << endl;
            }
        } else if (cmd == "exit") {
            break;
        } else {
            cout << "Error. Incorrect command" << endl;
        }

    }

    delete generator;

    for (auto & tree : trees) {
        delete tree;
    }
    return 0;
}
