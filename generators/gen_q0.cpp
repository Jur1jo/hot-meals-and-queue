#include "testlib.h"
 
using namespace std;
 
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
 
    int n = atoi(argv[1]);
    int t = atoi(argv[2]);
    cout << n << '\n';
    for (int i = 0; i < n - 1; ++i)
        cout << rnd.wnext(0, i, t) << ' ';
    cout << rnd.wnext(0, n - 1, t) << '\n';
    cout << 0 << '\n';
}
