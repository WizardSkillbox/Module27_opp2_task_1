#ifndef ELF_TREE_H
#define ELF_TREE_H

#include <string>
#include <generate_random.h>

class Tree {
    class Branch **bigBranches = nullptr;
    int bigBranchesQuantity = 0;

public:
    Tree(IntRandom *numGenerator);
    ~Tree();

    bool SearchElf(const std::string & inElfName, int * outNumOfNeighbours);
};

#endif //ELF_TREE_H
