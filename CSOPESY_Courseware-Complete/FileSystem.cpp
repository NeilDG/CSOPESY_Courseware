#include "FileSystem.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include "MathUtils.h"

FileSystem* FileSystem::sharedInstance = nullptr;

FileSystem* FileSystem::getInstance()
{
	return sharedInstance;
}

void FileSystem::initialize()
{
	sharedInstance = new FileSystem();
}

void FileSystem::destroy()
{
	delete sharedInstance;
}

void FileSystem::createFile(const std::string& fileName) const
{
    std::shared_ptr<File> newFile = std::make_shared<File>(fileName);
    newFile->randomizeContent();
    currentDirectory->files.push_back(newFile);

    std::cout << "File '" << fileName << "' created.\n";
}

void FileSystem::loadFileSystem()
{
    std::ifstream file(FILE_SYSTEM_PATH);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            this->createDirectoryFromRegistry(line);
        }
        file.close();
        std::cout << "Loaded file system. \n";
    }
    else {
        std::cout << "Creating a new file system in path: " << FILE_SYSTEM_PATH << std::endl;
    }
}

void FileSystem::saveFileSystem() const
{
    std::ofstream file(FILE_SYSTEM_PATH);
    if (file.is_open()) {
        this->saveDirectoryStructure(file, this->rootDirectory, 0);
        file.close();
        std::cout << "File system saved in path: " << FILE_SYSTEM_PATH << std::endl;
    }
    else {
        std::cerr << "Unable to save file system state.\n";
    }
}

std::shared_ptr<Directory> FileSystem::createDirectory(const std::string& dirname, bool isRoot)
{
    std::cout << "What's the dir? " << dirname << std::endl;
    if(isRoot || dirname == "root")
    {
        std::shared_ptr<Directory> newDir = std::make_shared<Directory>(dirname);
        return newDir;
    }
    else
    {
        std::shared_ptr<Directory> directory = this->findSubdirectoryByName(this->currentDirectory, dirname);
        if(directory == nullptr)
        {
            std::shared_ptr<Directory> newDir = std::make_shared<Directory>(dirname, currentDirectory);
            currentDirectory->subDirectories.push_back(newDir);
            return newDir;
        }
        else
        {
            return directory;
        }
    }
}

/**
 * \brief Used for assembling the directory read from the .csopesy file
 * \param dirname 
 * \param isRoot 
 */
void FileSystem::createDirectoryFromRegistry(const std::string& dirname, bool isRoot) const
{
    std::cout << "What's the dir? " << dirname << std::endl;
    if (isRoot || dirname == "root")
    {
        std::shared_ptr<Directory> newDir = std::make_shared<Directory>(dirname);
    }
    else
    {
        // std::shared_ptr<Directory> directory = this->findSubdirectoryByName(this->currentDirectory, dirname);
        // if(directory == nullptr)
        // {
        //     std::shared_ptr<Directory> newDir = std::make_shared<Directory>(dirname, currentDirectory);
        //     currentDirectory->subDirectories.push_back(newDir);
        //     return newDir;
        // }
        // else
        // {
        //     return directory;
        // }

        std::vector<std::string> tokens;
        std::istringstream tokenStream(dirname);
        std::string token;

        while (std::getline(tokenStream, token, '/'))
        {
            tokens.push_back(token);
        }

        std::shared_ptr<Directory> currentDir = isRoot ? rootDirectory : currentDirectory;

        // Process all tokens except the last two because it always ends with a filename and its contents.
        for (size_t i = 0; i < tokens.size() - 2; i++)
        {
            std::shared_ptr<Directory> directory = findSubdirectoryByName(currentDir, tokens[i]);

            if (directory == nullptr)
            {
                std::shared_ptr<Directory> newDir = std::make_shared<Directory>(tokens[i], currentDir);
                currentDir->subDirectories.push_back(newDir);
                currentDir = newDir;
            }
            else
            {
                currentDir = directory;
            }
        }

        std::string fileName = tokens[tokens.size() - 2]; //file name
        std::string fileContents = tokens[tokens.size() - 1]; //contents
        std::shared_ptr<File> newFile = std::make_shared<File>(fileName);
        newFile->setContents(fileContents);
        currentDir->files.push_back(newFile);
    }
}

void FileSystem::saveDirectoryStructure(std::ostream& stream, std::shared_ptr<Directory> dir, int depth) const
{
    if (dir) {
        // Indent based on depth
        // stream << std::string(depth, '\t') << dir->name << "\n";
        //Add delimiter
        stream << dir->name << "/";

        // Save subdirectories
        for (const auto& subDir : dir->subDirectories) {
            this->saveDirectoryStructure(stream, subDir, depth + 1);
        }

        // Save files
        for (const auto& file : dir->files) {
            // stream << std::string(depth + 1, '\t') << file->getContent() << "\n";
            stream << file->getName() << "/" << file->getContent() << "\n";
        }
    }
}

std::shared_ptr<Directory> FileSystem::findSubdirectoryByName(std::shared_ptr<Directory> parent,
	const std::string& name) const
{
	const auto it = std::find_if(parent->subDirectories.begin(), parent->subDirectories.end(),
	                             [name](const auto& dir) { return dir->name == name; });
    return (it != parent->subDirectories.end()) ? *it : nullptr;
}

FileSystem::String FileSystem::generateRandomDirectoryName() const
{
    return "folder_" + std::to_string(rand() % 10 + 1);
}

void FileSystem::mkdir(const std::string& directory)
{
    std::shared_ptr<Directory> newDir = this->createDirectory(directory);
    if (newDir) {
        std::cout << "Directory '" << directory << "' created.\n";
    }
}

void FileSystem::cd(const std::string& directory)
{
    if (directory == "..") {
        // Move to the parent directory
        if (currentDirectory->parent) {
            currentDirectory = currentDirectory->parent;
            std::cout << "Moved to parent directory.\n";
        }
        else {
            std::cerr << "Already at the root directory.\n";
        }
    }
    else {
        // Move to a child directory
        std::shared_ptr<Directory> subDir = this->findSubdirectoryByName(currentDirectory, directory);
        if (subDir) {
            currentDirectory = subDir;
            std::cout << "Moved to directory '" << directory << "'.\n";
        }
        else {
            std::cerr << "Directory '" << directory << "' not found.\n";
        }
    }
}

void FileSystem::printAllDirectories(bool printFiles) const
{
    this->printAllDirectories(std::cout, this->rootDirectory, printFiles);
}

void FileSystem::printAllDirectories(std::ostream& stream, std::shared_ptr<Directory> dir, bool printFiles) const
{
    if (dir) {
        // Print current directory
        stream << dir->name << "/";

        // Print files in the current directory
        if(printFiles)
        {
            for (const auto& file : dir->files) {
                stream << file->getName() << "\n";
            }
        }

        // Print subdirectories
        for (const auto& subDir : dir->subDirectories) {
            printAllDirectories(stream, subDir, printFiles);
        }
    }
}

void FileSystem::createRandomFilesRecursive(int fileCounter, int depth)
{
    if (depth <= 0 || MathUtils::chanceHit(90)) { //X% chance
        // Create a file
        std::string randomFile = "f_" + std::to_string(fileCounter) + ".txt";
        this->createFile(randomFile);
    }
    else {
        // Create a subdirectory
        std::string randomDir = generateRandomDirectoryName();
        mkdir(randomDir);
        cd(randomDir);

        // Recursively create files and subdirectories in the new directory
        createRandomFilesRecursive(fileCounter, depth - 1);

        // Move back to the parent directory
        cd("..");
    }
}

void FileSystem::test_createRandomFiles(int howMany)
{
    for (int i = 0; i < howMany; i++) {
        this->createRandomFilesRecursive(i, 5);
    }
}

FileSystem::FileSystem()
{
    this->rootDirectory = this->createDirectory("root", true);
    this->currentDirectory = this->rootDirectory;
}


Directory::Directory(String name, std::shared_ptr<Directory> parent)
{
    this->name = name;
    this->parent = parent;
}


File::File(String fileName)
{
    this->name = fileName;
    this->content = "";
}

void File::randomizeContent()
{
    // Generate a random string of length 50
    std::string randomString;
    const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const int stringLength = 50;

    for (int i = 0; i < stringLength; ++i) {
        randomString += characters[rand() % characters.length()];
    }

    this->setContents(randomString);
}

void File::setContents(const String& content)
{
    this->content = content;
}

File::String File::getName()
{
    return this->name;
}

File::String File::getContent()
{
    return this->content;
}
