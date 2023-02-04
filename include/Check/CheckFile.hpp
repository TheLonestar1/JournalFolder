#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sys/inotify.h>
#include <unistd.h>
#include <vector>
#include <pthread.h>
using namespace std;

struct paths{
    string pathCopy;
    string folderPath;
};  

extern  vector<string> NameFilesForCheck;

int checkWord(string path, string pathCopy,string name);
void * CheckFiles(void *arg);