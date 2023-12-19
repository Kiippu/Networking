#include <iostream>

#include "BSDSocket.h"
#include "simple_server.h"

int main(int argc, char const *argv[])
{
    //BSDSocket soc("look",6465);

    simple_server simp(6969, simple_server::Block::Yes);
    if(simp.Init())
    {
        std::cout << "simple server failed to initialize" << std::endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}
