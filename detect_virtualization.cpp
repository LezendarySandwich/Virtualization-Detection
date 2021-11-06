#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
namespace fs = std::filesystem;

namespace os {

    void run(std::string command) {
        system(command.c_str());
    }

    void run_python(std::string file) {
        run(std::string{"sudo python3 "} + file);
    }

    void run_exec(std::string file) {
        run(std::string{"./"} + file);
    }

    void run_code(fs::path filePath) {
        if(filePath.extension() == ".py") {
            std::cout << "Method: " << static_cast<std::string>(filePath.filename()) << std::endl;
            run_python(filePath);
            std::cout << std::endl;
        } else if(filePath.extension() == "") {
            std::cout << "Method: " << static_cast<std::string>(filePath.filename()) << std::endl;
            run_exec(filePath);
            std::cout << std::endl;
        }
    }   

    void install_dependecies() {
        system("bash install_dependecies.bash");
        std::cout << std::endl;
    }

}

namespace recursive_iterate {

    std::vector<std::string> __ignore {
        ".vscode",
        ".git",
        "CPUID_INSTRUCTION_WIN",
        "Neo"
    };

    std::vector<std::string> __ignore_ext {
        ".cpp",
        ".md",
        ".json",
        ".txt"
    };

    bool should_run(fs::path const& file_path) {
        if(fs::is_directory(file_path)) 
            return false;
        for(std::string ignore: __ignore) {
            if (static_cast<std::string>(file_path).find(ignore) != std::string::npos) 
                return false;
        }
        for(std::string ignore_ext: __ignore_ext) {
            if (file_path.extension() == ignore_ext) 
                return false;
        }
        return true;
    }

}

int main() {

    os::install_dependecies();

    fs::path base_path(".");

    for (const fs::path& dirEntry : fs::recursive_directory_iterator(base_path)) {
        if(recursive_iterate::should_run(dirEntry)) {
            os::run_code(dirEntry);
        }
    }
}