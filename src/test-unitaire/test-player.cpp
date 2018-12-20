#include <iostream>
#include <string>
#include "../player.h"

using namespace std;

void get_info(Player j) {
    cout << "Le nom du joueur : '"<< j.get_name() << "'" << endl
        << "\tBalle restante : " <<  j.get_ball() << endl
        << "\tScore actuel : " << j.get_score() << endl
        << "\tNiveau actuel : " << j.get_niveau() << endl;
}

main(int argc, char const *argv[])
{
    Player j1;
    Player j2("massy",3,300,2);

    get_info(j1);
    get_info(j2);

    j1.set_name("sans nom");
    j1.set_ball(5);
    j1.set_score(1000);
    j1.set_niveau(10);

    j2.set_name("massy 2");
    j2.increment_ball();
    j2.increment_score(10);
    j2.increment_niveau(-1);

    get_info(j1);
    get_info(j2);

    j2.increment_ball(-1);
    j2.increment_score(-10);
    j2.increment_niveau(1);

    get_info(j2);

    j1.increment_ball(-10);
    j1.increment_niveau(-100);
    j1.increment_score(-2000);
    get_info(j1);
    return 0;
}
