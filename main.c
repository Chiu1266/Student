#include <stdio.h>
#include <stdlib.h>
#include <conio.h>  //包含不用回车的输入的函数,即_getch(),方便使用
#include<string.h>
#include"Student.h"

int main()
{
    Node* head = malloc(sizeof(Node));
    head->next = NULL;

    //从文件里读取信息
    Load(head);

    mainpage();  //主界面可以仅输出一次
    while(1)  //死循环,使得用户可以一直输入数字使用对应功能,直到输入0才退出
{
    char c = _getch();  //不需要回车
    switch (c)
    {
    case '1':  //录入学生信息
        inputStudent(head);
        break;
    case '2':  //修改学生信息
        modifyStudent(head);
        break;
    case '3':  //删除学生信息
        deleteStudent(head);
        break;
    case '4':  //根据学号查找学生信息
        findStudent(head);
        break;
    case '5':  //显示班级学生信息
        findClass(head);
        break;
    case '6':  //统计学生人数
        countStudent(head);
        break;
    case '7': //输出所有学生信息
        printStudent(head);
        break;
    case '8': //学号排序
        sort(head);
        break;
    case '0':  //退出系统
        printf("程序结束");
        exit(0);
        break;
    default:
        break;
    }
}
    return 0;
}

void mainpage()  //输出主界面
{
    printf("*********************************\n");
    printf("\t学生证管理系统\t\n");
    printf("*********************************\n");
    printf("\t1.录入学生信息\t\t\n");
    printf("\t2.修改学生信息\t\t\n");
    printf("\t3.删除学生信息\t\t\n");
    printf("\t4.根据学号查找学生信息\t\n");
    printf("\t5.显示班级学生信息\t\n");
    printf("\t6.统计学生人数\t\t\n");
    printf("\t7.输出所有学生信息\t\n");
    printf("\t8.按学号排序输出信息\t\n");
    printf("\t0.退出系统\t\t\n");
    printf("*********************************\n");
}

void inputStudent(Node* head)  //输入(尾插)
{
    //定义临时指针move指向头节点，用于遍历链表
    Node* move = head;
    while (move->next != NULL)  //move还没到尾节点就一直往后移动
{
    move = move->next;
}
    //新节点
    Node* fresh = malloc(sizeof(Node));
    fresh->next = NULL;

    printf("请输入学生的学号、姓名、性别、专业班级: ");
    scanf("%lld%s%s%s", &fresh->stu.ID, fresh->stu.name, fresh->stu.gender,fresh->stu.major);

    //尾插
    move->next = fresh;
    //保存至文件
    Save(head);

    printf("已录入\n");
}

void printStudent(Node* head)  //输出所有学生信息
{
    printf("所有学生信息:\n");
    Node* move = head->next;
    while (move != NULL)
        {
        printf("学号:%lld 姓名:%s 性别:%s 专业班级:%s\n",move->stu.ID,move->stu.name,move->stu.gender,move->stu.major);
        move = move->next;
    }
}

void countStudent(Node* head) //统计学生人数
{
    int count = 0;
    Node* move = head->next;
    while (move != NULL)
    {
        count++;
        move = move->next;
    }
    printf("学生总人数为:%d\n",count);
}

void findStudent(Node* head) //学号查找学生信息
{
    long long ID;
    printf("请输入要查找的学生的学号: ");
    scanf("%lld", &ID);
    Node* move = head->next;
    while (move != NULL)
        {
        if (move->stu.ID == ID)
            {
            printf("学号:%lld 姓名:%s 性别:%s 专业班级:%s\n",move->stu.ID,move->stu.name,move->stu.gender,move->stu.major);
            return;
        }
        move = move->next;
    }
    printf("未查找到学生信息\n");
}

void Save(Node* head)  //保存到文件
{
    //打开文件
    FILE* file = fopen("./stu.txt", "w");   //只写
    if (file == NULL)
    {
        printf("打开文件失败\n");
        return;
    }
    Node* move = head->next;
    while (move != NULL) {
        //写入文件
        if (fwrite(&move->stu, sizeof(Student), 1, file) != 1) {
            printf("保存%s出现错误\n", move->stu.name);
        }
        move = move->next;
    }
    //关闭文件
    fclose(file);
}

void Load(Node* head)  //读取文件
{
    FILE* file = fopen("./stu.txt", "r");
    if (!file)
    {
        printf("未能读取(第一次使用录入学生信息,创建文件)\n");
        return;
    }
    //创建结点
    Node* fresh = malloc(sizeof(Node));
    fresh->next = NULL;
    Node* move = head;
    while (fread(&fresh->stu, sizeof(Student), 1, file) == 1)
    {
    move->next = fresh;
    move = fresh;
    fresh = malloc(sizeof(Node));
    fresh->next = NULL;
    }
    free(fresh);
    fclose(file);
    printf("\t读取文件成功\n");
}

void modifyStudent(Node* head)  //修改学生信息
{
    printf("请输入需要修改的学生学号:");
    long long ID = 0;
    scanf("%lld", &ID);
    Node* move = head;
    while (move != NULL)
    {
        if (move->stu.ID == ID)
        {
            printf("请输入学生姓名、性别、专业班级\n");
            scanf("%s%s%s",move->stu.name,move->stu.gender,move->stu.major);
            printf("修改学生信息成功\n");
            break;
        }
        move = move->next;
    }
    //没找到学生
    if (move == NULL)
    {
        printf("未找到学生信息\n");
    }
    //修改文件
    Save(head);
}

void deleteStudent(Node* head)  //删除学生信息
{
    printf("请输入要删除的学生学号:");
    long long ID = 0;
    scanf("%lld", &ID);
    Node* move = head;
    int flag = 0;
    while (move->next != NULL)
        {
        if (ID == move->next->stu.ID)
        {
            Node* temp = move->next;
            move->next = move->next->next;  //删除节点
            free(temp);      //释放
            temp = NULL;  //释放后指向NULL
            Save(head);
            printf("删除学生成功\n");
            flag = 1;
            break;
        }
        move = move->next;
    }
   if (flag == 0)
    {
        printf("未找到学生信息\n");
    }
}

void findClass(Node* head) //显示班级学生信息
{
    char major[50];
    printf("请输入要查找的班级: ");
    scanf("%s", major);
    Node* move = head->next;
    int found = 0;
    while (move != NULL)
    {
        if (strcmp(move->stu.major,major)==0)  //字符串比较用到strcmp,返回0为相同
        {
            printf("学号:%lld 姓名:%s 性别:%s 专业班级:%s\n",move->stu.ID,move->stu.name,move->stu.gender,move->stu.major);
            found = 1;
        }
        move = move->next;
    }
    if(found == 0)
    {
        printf("未查找到该班级\n");
    }
}

void sort(Node* head) //按学号排序
{
    Node* save = NULL;
    Node* move = NULL;
    for (Node* turn = head->next; turn->next != NULL; turn = turn->next)
    {
        for (move = head->next; move->next != save; move = move->next)
        {
            if (move->stu.ID > move->next->stu.ID)
            {
                Student temp = move->stu;
                move->stu = move->next->stu;
                move->next->stu = temp;
            }
        }
        save = move;
    }
    printf("按学号排序:\n");
    printStudent(head);
}

