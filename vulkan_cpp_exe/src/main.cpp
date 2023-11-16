// *****************************************************
//    Copyright 2023 Videonetics Technology Pvt Ltd
// *****************************************************

#include "engine.h"
#include <memory>

int main(int /*argc*/, char const* /*argv*/[])
{
    std::unique_ptr<Engine> const engine(new Engine());
    return 0;
}
