#include <widgets/Application.h>

using namespace AGui;

int main(int, char**){

    Application a("hello", 1280, 720);
    a.render();

    return 0;
}