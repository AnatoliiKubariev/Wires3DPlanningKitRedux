#include "Utility.h"

int GetId()
{
    static int id = 0;
    return ++id;
}