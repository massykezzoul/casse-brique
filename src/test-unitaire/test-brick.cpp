#include <iostream>
#include "../brick.h"

using namespace std;

void get_info(Brick j) {
    cout << "La forme de la brick : '"<< j.get_forme() << "'" << endl
        << "\tResistance : " <<  j.get_resistance() << endl
        << "\tPoint : " << j.get_point() << endl;
}

main(int argc, char const *argv[])
{
    Brick j1;
    Brick j2(TRIANGLE,3,300);

    get_info(j1);
    get_info(j2);
    cout << "----------------------------" << endl;
    j1.set_forme(CREUSE);
    j1.set_resistance(10);
    j1.set_point(1000);

    j2.set_forme(RONDE);
    j2.set_resistance(1);
    j2.set_point(10);

    get_info(j1);
    get_info(j2);
    cout << "----------------------------" << endl;

    j1.increment_resistance(-5);

    get_info(j1);
    cout << "----------------------------" << endl;

    j2.increment_resistance();
    get_info(j2);
    j2.increment_resistance();
    get_info(j2);
        cout << "----------------------------" << endl;
    return 0;
}
