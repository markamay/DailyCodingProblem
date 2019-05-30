/**
 *  Daily Coding Problem 
 *  Problem 17 Solution
 * 
 *  Written by Mark May (markamay@live.com)
 *  Sample Test file: data/fileSystem.txt 
 * 
 *  Problem Description:
 * 
 * This problem was asked by Google.
 * 
 * Suppose we represent our file system by a string in the following manner:
 * 
 * The string "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext" represents:
 * 
 * dir
 *     subdir1
 *     subdir2
 *         file.ext
 * The directory dir contains an empty sub-directory subdir1 and a sub-directory subdir2 containing a file file.ext.
 * 
 * The string "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext" represents:
 * 
 * dir
 *     subdir1
 *         file1.ext
 *         subsubdir1
 *     subdir2
 *         subsubdir2
 *             file2.ext
 * The directory dir contains two sub-directories subdir1 and subdir2. subdir1 contains a file file1.ext and an empty second-level sub-directory subsubdir1. subdir2 contains a second-level sub-directory subsubdir2 containing a file file2.ext.
 * 
 * We are interested in finding the longest (number of characters) absolute path to a file within our file system. For example, in the second example above, the longest absolute path is "dir/subdir2/subsubdir2/file2.ext", and its length is 32 (not including the double quotes).
 * 
 * Given a string representing the file system in the above format, return the length of the longest absolute path to a file in the abstracted file system. If there is no file in the system, return 0.
 * 
 * Note:
 * 
 * The name of a file contains at least a period and an extension.
 * 
 * The name of a directory or sub-directory will not contain a period.
 */
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <stack>
#include <tuple>
using namespace std;


class FileSystem {
    public:
    /**
     * Takes a filesystem represented as a single string and returns the longest path size and the
     * path from the root to the file at the end of the path
     * 
     * @param fileSystem - The filesystem represented as a string with each file/directory on its own line
     *                     and every file has a tab to represent its depth in the file system
     * @returns A pointer to a pair with the first element being the size of the biggest path and
     *          the second element being the path from the root to the file at the greatest depth
     *
     */
    pair<size_t, string>* longestPathToFile(string fileSystem) {
        pair<size_t, string> * biggestPath = new pair<size_t, string>(0, "");
        string fileName;
        stack<string> curPath;
        istringstream fileStream(fileSystem);

        while (getline(fileStream, fileName)) {
            size_t depth = depthLevel(fileName);
            curPath.push(fileName);

            while (depth  < curPath.size()) {
                curPath.pop();
            }

            if (isFile(fileName)) {
                if (curPath.size() > biggestPath->first) {
                    biggestPath->first = curPath.size();
                    biggestPath->second = getPathStr(curPath);
                }
                curPath.pop();
            }
        }

        return biggestPath;
    }
    private:
    /*
        Takes a file path represented by a stack and returns the string
        representation

        @params  pathStack - A stack of directories in the path to the file/directory at the top of the string
        @returns path      - The path as a single string with each directory separated by '/'
    */
    string getPathStr(stack<string> pathStack) {
        string path = "";

        while (pathStack.size() > 0) {
            path = pathStack.top() + "/" + path;
            pathStack.pop();
        }

        return path;
    }

    /**
     *  Determines if the string is a file or directory
     * 
     *  @params  str - the file/directory. Files must contain a '.' and directories cannot
     *  @returns true if the string is a filename, false otherwise
     */
    bool isFile(string str) {
        return (str.find('.') != string::npos);
    }

    /**
     *    Determines the depth of a file in the filesystem by the 
     *    number of tab characters that are at the start of it.
     *
     *    @param fileName - The name of the file, with a '\t' at the start for each
     *                      parent folder. All tab characters at the start are removed.
     *    @returns The number of '\t' characters found, aka the depth of the file
     */
    size_t depthLevel(string& fileName) {
        size_t depth = 1;
        while (!fileName.empty() && (fileName[0] == '\t')) {
            depth++;
            fileName.erase(0, 1);
        }

        return depth;
    }

};

//test driver
int main(int argc, char **argv) {
    FileSystem files;
    string fileSystem;
    if (argc < 2) {
        cout << "Enter the file system in string format" << endl;
        cout << ">";
        getline(cin, fileSystem, ' ');
    }
    else {
        ifstream ins(argv[1]);
        if (ins.fail()) {
            cout << "ERROR: Unable to open " << argv[1] << endl;
            return -1;
        }
        char ch;
        ins.get(ch);
        while (!ins.eof()) {
            fileSystem += ch;
            ins.get(ch);
        }
        ins.close();
    }
    pair<size_t, string> * result = files.longestPathToFile(fileSystem);
    cout << "Path:   " << result->second << endl;
    cout << "Length: " << result->first << endl;

    return 0;
}