#include <iostream>

//#include "BSDSocket.h"
#include "simple_server.h"
#include "simple_client.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    std::cout << "Have " << argc << " arguments:\n";
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << "\n";
    }
    if (argc > 1)
    {
        simple_client client(6969, simple_client::Block::Yes);
        if(client.Init())
        {
            std::cout << "simple client failed to initialize" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        simple_server simp(6969, simple_server::Block::Yes);
        if(simp.Init())
        {
            std::cout << "simple server failed to initialize" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
