#include <iostream>
#include <unistd.h>
#include <fcntl.h> 
#include <sys/wait.h>
#include <cstring> 
using namespace std;

#define BUFFER_SIZE 1024

int main() {
    int parentToChild[2], childToParent[2];
    pid_t pid;
    char filePath[BUFFER_SIZE];
    char fileContent[BUFFER_SIZE];

    if (pipe(parentToChild) == -1 || pipe(childToParent) == -1) {
        cerr << "Pipe creation failed" << endl;
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        cerr << "Fork failed" << endl;
        return 1;
    }

    if (pid > 0) { 
        close(parentToChild[0]);
        close(childToParent[1]); 

        // Get file path from user
        cout << "Enter the path of the file to read: ";
        cin.getline(filePath, BUFFER_SIZE);

        write(parentToChild[1], filePath, strlen(filePath) + 1);

        wait(NULL);

        ssize_t n = read(childToParent[0], fileContent, BUFFER_SIZE);
        if (n > 0) {
            cout << "Contents of the file:\n" << fileContent << endl;
        } else {
            cerr << "Failed to read file content from child" << endl;
        }

        close(parentToChild[1]);
        close(childToParent[0]);
    } else { 
        close(parentToChild[1]);
        close(childToParent[0]);

        read(parentToChild[0], filePath, BUFFER_SIZE);

        int file = open(filePath, O_RDONLY);
        if (file < 0) {
            cerr << "Failed to open the file: " << filePath << endl;
            strcpy(fileContent, "Error opening file");
        } else {
            ssize_t bytesRead = read(file, fileContent, BUFFER_SIZE - 1);
            fileContent[bytesRead] = '\0';
            close(file);
        }

        write(childToParent[1], fileContent, strlen(fileContent) + 1);

        close(parentToChild[0]);
        close(childToParent[1]);
    }

    return 0;
}
