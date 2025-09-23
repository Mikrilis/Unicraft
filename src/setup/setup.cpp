#include "setup.h"

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
    std::cout << "Hmmm..." << std::endl;
}

void setup() {
    struct stat sb;

    if (stat(getUCFolder().c_str(), &sb) != 0)
    {
        download();
    }
}