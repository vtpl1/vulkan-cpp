// *****************************************************
//    Copyright 2023 Videonetics Technology Pvt Ltd
// *****************************************************

#include "engine.h"
#include <memory>

int main(int argc, char const *argv[])
{
    std::unique_ptr<Engine> e(new Engine());
    return 0;
}
