#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED
#include<stdio.h>
#include<stdlib.h>

//定义学生信息结构体
typedef struct
{
    long long ID;  //学号
    char name[20];  //姓名
    char gender[20];  //性别
    char major[50];  //专业班级,班级查找功能也用此项数据
}Student;

//定义节点
typedef struct Node
{
    Student stu;
    struct Node* next;
}Node;


//声明
void mainpage();
void Save(Node* head);
void Load(Node* head);
void inputStudent(Node* head);
void printStudent(Node* head);
void countStudent(Node* head);
void findStudent(Node* head);
void modifyStudent(Node* head);
void deleteStudent(Node* head);
void findClass(Node* head);
void sort(Node* head);

#endif // STUDENT_H_INCLUDED
