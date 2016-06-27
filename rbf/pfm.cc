#include "pfm.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
using namespace std;

PagedFileManager* PagedFileManager::_pf_manager = 0;

PagedFileManager* PagedFileManager::instance() {
	if (!_pf_manager)
		_pf_manager = new PagedFileManager();

	return _pf_manager;
}

PagedFileManager::PagedFileManager() {
}

PagedFileManager::~PagedFileManager() {
}

RC PagedFileManager::createFile(const string &fileName) {
	struct stat stFileInfo;
	if (stat(fileName.c_str(), &stFileInfo) == 0) {
		cout << "File already exists" << endl;
		return -1;
	} else {
		fstream myfile(fileName.c_str(), fstream::out);
		myfile.close();
	}
	return 0;
}

RC PagedFileManager::destroyFile(const string &fileName) {
	return remove(fileName.c_str());
}

//pair a file to the fileHandle
RC PagedFileManager::openFile(const string &fileName, FileHandle &fileHandle) {
	return fileHandle.setFile(fileName);
}

RC PagedFileManager::closeFile(FileHandle &fileHandle) {
	return fileHandle.closeStream();
}

FileHandle::FileHandle() {
	readPageCounter = 0;
	writePageCounter = 0;
	appendPageCounter = 0;
	page_num = 0;
}

FileHandle::~FileHandle() {
}

RC FileHandle::setFile(string name) {
	if (!this->fileName.empty()) {
		cout << "this fileHandle has been assigned to a file" << endl;
		return -1;
	} else {
		this->fileName = name;
		this->file_stream.open(name.c_str(),
				fstream::in | fstream::out | fstream::binary);
		return 0;
	}
}

RC FileHandle::closeStream() {
	if (!this->file_stream) {
		cout << "file stream not created" << endl;
		return -1;
	} else {
		this->file_stream.close();
		return 0;
	}
}

RC FileHandle::readPage(PageNum pageNum, void *data) {
	if(this->page_num < pageNum){
		cout<<"not enough page to read"<<endl;
		return -1;
	}
	this->file_stream.seekg(pageNum*PAGE_SIZE);
	this->file_stream.read((char*)data, PAGE_SIZE);
	readPageCounter++;
	return 0;
}

RC FileHandle::writePage(PageNum pageNum, const void *data) {
	if(this->page_num < pageNum){
		cout<<"not enough page to modify"<<endl;
		return -1;
	}
	this->file_stream.seekp(pageNum*PAGE_SIZE);
	this->file_stream.write((char*)data, PAGE_SIZE);
	this->writePageCounter++;
	return 0;
}

RC FileHandle::appendPage(const void *data) {
	this->file_stream.seekp(this->getNumberOfPages()*PAGE_SIZE);
	this->file_stream.write((char *)data, PAGE_SIZE);
	this->page_num = this->file_stream.tellp()/PAGE_SIZE;
	this->appendPageCounter++;
	return 0;
}

unsigned FileHandle::getNumberOfPages() {
    struct stat results;

    if (stat(fileName.c_str(), &results) == 0){
    	return this->page_num = results.st_size/PAGE_SIZE;
    } else{
    	cout<<"get size error occur"<<endl;
    	return -1;
    }
}

RC FileHandle::collectCounterValues(unsigned &readPageCount,
		unsigned &writePageCount, unsigned &appendPageCount) {
	readPageCount = readPageCounter;
	writePageCount = writePageCounter;
	appendPageCount = appendPageCounter;
	return 0;
}
