#include "setup.h"

#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sys/stat.h>

std::string getUCFolder() {
    std::string homeDir;

#ifdef _WIN32
    const char* userProfile = std::getenv("USERPROFILE");

    if (userProfile != nullptr) {
        homeDir = userProfile;
        homeDir += "\\AppData\\Roaming\\.unicraft";
    }
#else
    const char* home = std::getenv("HOME");
    if (home != nullptr) {
        homeDir = home;
        homeDir += "/.unicraft";
    }
#endif

    return homeDir;
}

void download() {
    std::string home = getUCFolder();

    std::vector<std::string> urls = {"", ""};
    std::vector<std::string> files = {home + "\\Bin\\dev-1.0.0\\Shaders\\frag.spv", home + "\\Bin\\dev-1.0.0\\Shaders\\vert.spv"};
    for (size_t i = 0; i < urls.size(); i++)
    {

        std::string cmd = "curl -L " + urls[i] + " -o " + files[i];
        int vysledek = std::system(cmd.c_str());
    }
}

void setup() {
    struct stat sb;

    if (stat(getUCFolder().c_str(), &sb) != 0)
    {
        //download();
    }
}