#include <iostream>
#include <engine/physics/PhysicsManager.h>

int main(int argc, char* argv[]) {
    std::cout << "Hello, World!\n";
    PhysicsManager pm {};
    pm.doPhysics();
    return 0;
}
