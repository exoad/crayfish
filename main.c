#include "lifecycle.h"

I32 main(I32 argc, I8** argv)
{
    implyUsed(argc);
    implyUsed(argv);
    println("%s", "Hello, World!");
    cycleStart();
    draw();
    cycleEnd();
    return 0;
}