#include <iostream>
#include "Editor.h"

int main(const int argc, char** argv)
{
    std::cout << "Argument count: " << argc << std::endl;
    for(int i = 0; i < argc; i++)
        std::cout << "Arguments: " << argv[i] << std::endl;
    
    try {
        const Editor editor;
        editor.Run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    
    return 0;
}