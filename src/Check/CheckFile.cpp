#include <Check/CheckFile.hpp>


int checkWord(string path, string pathCopy, string name)
{
    std::ifstream file(path);
    if(!file)
    {
        std::cerr << "Failed to open source file: " << path << std::endl;
            return 1;
    }
    std::string word;
    while (file >> word) {
        if(word == "TOPSECRET")
        {
            
            std::ofstream dst(pathCopy + name, ios::binary);
            if (!dst) {
                std::cerr << "Failed to open destination file: " << pathCopy + name<< std::endl;
                return 1;
            }
            file.seekg(0);
            dst << file.rdbuf();
            return 0;
        }
    }
    return 0;
}

void * CheckFiles(void *arg)
{
    paths *path = (paths*)(arg);
    cout << "Theard for check files work!" << endl;
    while(1) 
    {
        if(NameFilesForCheck.size() > 0) {
            checkWord(path->folderPath + NameFilesForCheck.front(),path->pathCopy, NameFilesForCheck.front());
            NameFilesForCheck.erase(NameFilesForCheck.begin());
        }       
    }
}