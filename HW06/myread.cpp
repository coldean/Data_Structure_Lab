#include "MyStudent.hpp"
#include <fcntl.h>
#include <iostream>
#include <list>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main(void) {
    Student *stu = (Student *)malloc(sizeof(Student));
    list<Student> stuList;
    ssize_t rSize = 0;
    list<Student>::iterator it;

    string filepath = "./StudentList.dat";
    int fd = open(filepath.c_str(), O_RDONLY, 0644);
    if (fd == -1) {
        perror("open() error");
        return 1;
    }

    do {
        rSize = read(fd, stu, sizeof(Student));

        if (rSize == -1) {
            perror("read() error!");
            return 2;
        }

        stuList.push_back(*stu);
    } while (rSize > 0);
    close(fd);
    //이중 저장 된 마지막 리스트 제거
    stuList.pop_back();

    int stId = 1;
    for (it = stuList.begin(); it != stuList.end(); it++) {
        cout << stId << "번째 학생 정보" << endl;
        cout << "ID: " << it->getId() << ", ";
        cout << "Name: " << it->getName() << ", ";
        cout << "Score: " << it->getScore() << endl;
        stId++;
    }

    return 0;
}
