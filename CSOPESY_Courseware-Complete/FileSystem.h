#pragma once
#include <memory>
#include <string>
#include <vector>

class File
{
private:
	typedef std::string String;
	String name;
	String content;
	
public:
	File(String fileName);
	void setContents(const String& content);

	String getName();
	String getContent();
	void randomizeContent();
};

class Directory
{
private:
	typedef std::string String;
	String name;

	std::shared_ptr<Directory> parent;
	std::vector<std::shared_ptr<Directory>> subDirectories;
	std::vector<std::shared_ptr<File>> files;

public:
	Directory(String name, std::shared_ptr<Directory> parent = nullptr);
	friend class FileSystem;
	friend class File;
};

class FileSystem
{
public:
	typedef std::string String;
	const String FILE_SYSTEM_PATH = "X:/GithubProjects/CSOPESY_Courseware/filesystem.csopesy";

	static FileSystem* getInstance();
	static void initialize();
	static void destroy();

	void createFile(const std::string& fileName) const;
	void loadFileSystem();
	void saveFileSystem() const;

	std::shared_ptr<Directory> createDirectory(const std::string& dirname, bool isRoot = false);
	void createDirectoryFromRegistry(const std::string& dirname, bool isRoot = false) const;
	void saveDirectoryStructure(std::ostream& stream, std::shared_ptr<Directory> dir, int depth) const;
	std::shared_ptr<Directory> findSubdirectoryByName(std::shared_ptr<Directory> parent, const std::string& name) const;

	String generateRandomDirectoryName() const;

	void mkdir(const std::string& directory);
	void cd(const std::string& directory);
	void printAllDirectories(bool printFiles) const;

	//tester functions
	void test_createRandomFiles(int howMany);

private:
	FileSystem();
	~FileSystem() = default;
	FileSystem(FileSystem const&) {}; // copy constructor is private
	FileSystem& operator=(FileSystem const&) {}; // assignment operator is private*/
	static FileSystem* sharedInstance;

	std::shared_ptr<Directory> rootDirectory;
	std::shared_ptr<Directory> currentDirectory;

	void printAllDirectories(std::ostream& stream, std::shared_ptr<Directory> dir, bool printFiles) const;
	void createRandomFilesRecursive(int fileCounter, int depth);
};

