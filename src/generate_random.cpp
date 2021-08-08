#include <assert.h>
#include <generate_random.h>

using namespace std;

IntRandom::IntRandom() {
    mt_rand = mt19937(chrono::high_resolution_clock::now().time_since_epoch().count());
}

int IntRandom::generateRandom(uint32_t min, uint32_t max) {
    assert(max > min);
    return (int) ((float) min + ((float) mt_rand() / (float) mt19937::max()) * ((float) (max - min) + 0.999f));
}

