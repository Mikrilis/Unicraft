#include "setup.h"

#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sys/stat.h>
#include <filesystem>
#include <Windows.h>

void runCommand(const std::string& cmd) {
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;
    ZeroMemory(&pi, sizeof(pi));

    if (CreateProcessA(
        NULL,
        (LPSTR)cmd.c_str(),
        NULL,
        NULL,
        FALSE,
        CREATE_NO_WINDOW,
        NULL,
        NULL,
        &si,
        &pi
    )) {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
} //Comment(From #include <Windows.h> to here) when compiling for Linux

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

    std::vector<std::string> urls = {"https://github.com/Mikrilis/Unicraft/releases/download/pre-dev-1.1.0/frag.spv", "https://github.com/Mikrilis/Unicraft/releases/download/pre-dev-1.1.0/vert.spv"};
    std::vector<std::string> files = {std::filesystem::path(home + "/Bin/dev-1.1.0/Shaders/frag.spv").string(), std::filesystem::path(home + "/Bin/dev-1.1.0/Shaders/vert.spv").string()};
    for (size_t i = 0; i < urls.size(); i++)
    {
        std::filesystem::create_directories(std::filesystem::path(home + "/Bin/dev-1.1.0/Shaders"));
        
        std::ofstream file(files[i]);
        file.close();

        std::string cmd = "curl -L " + urls[i] + " -o " + files[i];
#ifdef _WIN32

        runCommand(cmd);

#else

        std::system(cmd.c_str());

#endif
    }
}

void setup() {
    struct stat sb;

    std::filesystem::path home = std::filesystem::path(getUCFolder() + "/Bin/dev-1.1.0");
    std::string h = home.string();

    if (stat(h.c_str(), &sb) != 0)
    {
        download();
    }
}