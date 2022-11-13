#include "stl.h"
#include "string.h"

int main()
{
    Object3D *sus = object_from_binary("/home/marino/Desktop/susane.stl");

    object_to_stl(sus, "SUSANE", "/home/marino/Desktop/susane-text.stl");
    
    return 0;
}