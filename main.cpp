#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <filesystem>
#include <csignal>
#include <unistd.h>

class Shell {
public:
    Shell() {
        std::signal(SIGINT, signalHandler);
    }

    void run() {
        isRunning = true;

        std::string command;
        std::cout << "\033[34m" << "Welcome to modern shell" << "\033[0m" << std::endl;
        if (!std::filesystem::exists("shell-folder")) {
            system("mkdir shell-folder");
        }
        while (isRunning) {
            std::cout << "\033[32m" << "computer:~/shell-folder/$ " << "\033[0m";
            std::getline(std::cin, command);
            
            if (command == "exit") {
                clearResourse();
                break;
            }

            if (command.rfind("touch", 0) == 0) {
                std::vector<std::string> words = splitStringBySpace(command);
                int wordsSize = words.size();
                std::ostringstream commandToCreateFile;
                commandToCreateFile << "touch " << "shell-folder/" << words[wordsSize - 1];
                std::string formatStrCommand = commandToCreateFile.str(); 
                system(formatStrCommand.c_str());
            }

            if (command.rfind("mkdir", 0) == 0) {
                std::vector<std::string> words = splitStringBySpace(command);
                int wordsSize = words.size();
                std::ostringstream commandToCreateFolder;
                commandToCreateFolder << "mkdir " << "shell-folder/" << words[wordsSize - 1];
                std::string formatStrCommand = commandToCreateFolder.str();
                system(formatStrCommand.c_str());
            }

            if (command.rfind("mkdir", 0) == 0) {
                std::vector<std::string> words = splitStringBySpace(command);
                int wordsSize = words.size();
                std::ostringstream commandToCreateFolder;
                commandToCreateFolder << "mkdir " << "shell-folder/" << words[wordsSize - 1];
                std::string formatStrCommand = commandToCreateFolder.str();
                system(formatStrCommand.c_str());
            }

            if (command == "pwd") {
                system("realpath shell-folder");
            }

            if (command == "ls") {
                system("ls shell-folder");
            }

            if (command == "clear") {
                system("clear");
            }

            
        }
    }
private:
    bool isRunning;

    std::vector<std::string> splitStringBySpace(const std::string& input) {
        std::vector<std::string> words;
        std::stringstream ss(input);
        std::string word;

        while (ss >> word) {
            words.push_back(word);
        }

        return words;
    }

    void clearResourse() {
        system("clear");
        system("rm -r shell-folder");
    }

    static Shell* getInstance() {
        static Shell instance;
        return &instance;
    }

    static void signalHandler(int sigNum) {
        Shell* instance = Shell::getInstance();
        if (instance) {
            instance->clearResourse();
            instance->isRunning = false;
        }
    }


};

int main() {
    Shell shell;
    shell.run();
}