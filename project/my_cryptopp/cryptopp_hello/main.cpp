#include <iostream>
#include <string>

#include "chacha.h"

using namespace std;

int main() {

    string line(50, '-');

    cout << line << " start " << line << endl;


    // ------------------------ chacha start ----------------------

    chacha::case1();

    // ------------------------ chacha end ------------------------


    cout << line << "  end  " << line << endl;

    return 0;
}
