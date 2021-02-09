#include <iostream>
#include <fstream>
#include <string>

#include <argparse/argparse.hpp>

int main(int argc, char *argv[])
{
    argparse::ArgumentParser program("MySed");

    program.add_argument("commands");
    program.add_argument("filename");
    program.add_argument("-n")
        .default_value(false)
        .implicit_value(true);

    try {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err) {
        std::cout << err.what() << std::endl;
        std::cout << program;
        exit(0);
    }

//    std::cout << "Got filename '" << program.get<std::string>("filename") << "'" << std::endl;
    std::ifstream infile(program.get("filename"));

    std::string line;

    std::stringstream commands(program.get("commands"));
    std::string command; // used to hold a single command inside

    std::string pattern_space;
    std::string hold_space;

    while(std::getline(infile, line)) {
        // push line to pattern space
        if (!pattern_space.empty()) pattern_space.append("\n");
        pattern_space.append(line);

        // do all the operations ...
REDO:;
        commands.clear();
        commands.seekg(0, commands.beg);
        while (std::getline(commands, command, ';')) {
            switch(command[0]) {
            case 'p': std::cout << pattern_space << '\n'; break;
            case 'd': pattern_space.clear(); goto SKIP;
            case 'D':
                pattern_space.erase(pattern_space.begin(), std::find(pattern_space.begin(), pattern_space.end(), '\n'));
                if (pattern_space.empty()) goto SKIP; else goto REDO;
            case 'q': exit(std::atoi(command.substr(1).c_str()));
            }
        }


        // print pattern space and delete it
        if (program["-n"] == false) std::cout << pattern_space << '\n';
        pattern_space.clear();
SKIP:;
    }
    return 0;
}
