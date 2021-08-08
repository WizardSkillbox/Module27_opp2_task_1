#include <iostream>
#include <cassert>

#include <elf_names.h>
#include <elf_tree.h>

using namespace std;

class Branch {
    std::string elfName = "None";
    const Branch *parentBranch = nullptr;
    Branch **childBranches = nullptr;
    int childBranchesQuantity = 0;

public:

    Branch(const Branch *inParentBranch, int inChildBranchesQuantity)
            : parentBranch(inParentBranch),
              childBranchesQuantity(inChildBranchesQuantity) {

        assert(inChildBranchesQuantity >= 0);

        if (childBranchesQuantity) {
            cout << "Middle branches: " << childBranchesQuantity << endl;
            childBranches = new Branch *[childBranchesQuantity];
            for (int i = 0; i < childBranchesQuantity; ++i) {
                childBranches[i] = new Branch(this, 0);
            }
        }
    }

    ~Branch() {
        for (int i = 0; i < childBranchesQuantity; ++i) {
            delete childBranches[i];
        }
        delete[] childBranches;
    }

    void PopulateElfs() {
        string message = "    Enter an elf name for the " + (childBranchesQuantity
                                                             ? string("BIG")
                                                             : string("MIDDLE")) + " branch: ";

        elfName = RequestElfNameFromUser(message);
        if (childBranchesQuantity) {
            for (int i = 0; i < childBranchesQuantity; ++i) {
                cout << "    Middle branch: " << i + 1 << " :" << endl;
                childBranches[i]->PopulateElfs();
            }
        }
    }

    Branch *LookUpBranchOf(const std::string &inElfName) {
        Branch *branch = nullptr;
        if (elfName != "None" && elfName == inElfName) {
            return this;
        } else if (childBranchesQuantity) {
            for (int i = 0; i < childBranchesQuantity; ++i) {
                branch = childBranches[i]->LookUpBranchOf(inElfName);
                if (nullptr != branch) {
                    break;
                }
            }
        }

        return branch;
    }

    int GetNumberOfElfs() const {
        int numberOfElfs = (elfName != "None") ? 1 : 0;
        if (childBranchesQuantity) {
            for (int i = 0; i < childBranchesQuantity; ++i) {
                if (childBranches[i]->GetElfName() != "None") {
                    numberOfElfs++;
                }
            }
        }
        return numberOfElfs;
    }

    const string &GetElfName() {
        return elfName;
    }

    int GetNeighbourQuantity() {
        if (nullptr == parentBranch) {
            return 0;
        }
        int neighbours = parentBranch->GetNumberOfElfs();
        assert(neighbours > 0);
        return neighbours - 1;
    }
};

/*------------------------------------------------------------------------------------------*/
Tree::Tree(IntRandom *numGenerator) {
    assert(numGenerator != nullptr);
    bigBranchesQuantity = numGenerator->generateRandom(3, 5);
    cout << "    Big branches: " << bigBranchesQuantity << endl;
    bigBranches = new Branch *[bigBranchesQuantity];
    for (int i = 0; i < bigBranchesQuantity; ++i) {
        cout << "    Big branch " << i + 1 << " :";
        int numOfMiddleBranches = numGenerator->generateRandom(2, 3);
        bigBranches[i] = new Branch(nullptr, numOfMiddleBranches);
        bigBranches[i]->PopulateElfs();
    }
}

Tree::~Tree() {
    for (int i = 0; i < bigBranchesQuantity; ++i) {
        delete bigBranches[i];
    }
    delete[] bigBranches;
}

bool Tree::SearchElf(const std::string &inElfName, int *outNumOfNeighbours) {
    assert(outNumOfNeighbours != nullptr);

    for (int i = 0; i < bigBranchesQuantity; ++i) {
        Branch *branch = bigBranches[i]->LookUpBranchOf(inElfName);
        if (nullptr != branch) {
            *outNumOfNeighbours = branch->GetNeighbourQuantity();
            return true;
        }
    }

    return false;
}
