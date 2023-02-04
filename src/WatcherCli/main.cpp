
#include "CLI/App.hpp"
#include "CLI/Formatter.hpp"
#include "CLI/Config.hpp"
#include <Check/CheckFile.hpp>


vector<string> NameFilesForCheck;

int main(int argc, char** argv) {
    // Add option for parse information on arguments line
    CLI::App app{"App description"};

    paths path;
   
    app.add_option("-w,--pathwatch", path.folderPath, "A help string");
    app.add_option("-c,--pathcopy", path.pathCopy, "Enter number second");
      
    CLI11_PARSE(app, argc, argv);
    // Create and start Theard for check files on word "TopSecret"
    pthread_t thread1;
    int result = pthread_create(&thread1, nullptr, CheckFiles, &path);
    if (result != 0) {
        perror("Theard not creaete");
        return EXIT_FAILURE;
    }
    // Initialization inotify
    int fd, wd;
    fd = inotify_init();
    if (fd < 0) {
        std::cerr << "inotify_init failed" << std::endl;
        return 1;
    }
    wd = inotify_add_watch(fd, path.folderPath.c_str(), IN_CREATE | IN_MODIFY | IN_DELETE);
    if (wd < 0) {
        std::cerr << "inotify_add_watch failed" << std::endl;
        return 1;
    }
    // Create or Open Journal.txt
    std::ofstream out("Journal.txt");          
    if (!out)
    {
        std::cerr << "Journal not open" << std::endl;
        return 0;
    }

    // Read events from the inotify file descriptor
    while (true) {
        char buffer[1024];
        int length = read(fd, buffer, 1024);
        if (length < 0) {
            std::cerr << "read failed" << std::endl;
            return 1;
        }
        string buff;
        // Parse and process each event
        for (int i = 0; i < length;) {
            struct inotify_event *event = (struct inotify_event *) &buffer[i];
            buff = event->name;
            if (event->mask & IN_CREATE) {
                out << "File created: " << buff << std::endl;
                NameFilesForCheck.push_back(buff);
            } else if (event->mask & IN_MODIFY) {
                out << "File modified: " << buff << std::endl;
                NameFilesForCheck.push_back(buff);
            } else if (event->mask & IN_DELETE) {
                out << "File deleted: " << buff << std::endl;
            }
            
            i += sizeof(struct inotify_event) + event->len;
        }
    }
    pthread_join(thread1, nullptr);
    return 0;
}