#pragma once
#include <iostream>
using namespace std;
#include "worker.h"
#include "empolyee.h"
#include "boss.h"
#include "manager.h"

#include <fstream>
#define  FILENAME "empFile.txt"

class WorkerManager
{
public:
	WorkerManager();//构造函数
	
	void Show_Menu();//展示菜单
	
	void ExitSystem();//退出系统

	
	int m_EmpNum;//记录职工人数
	
	Worker** m_EmpArray;//职工数组指针，里面的每个元素也是指针

	/*
	这里声明了一个指向 Worker 指针的指针的数组，但是没有指定数组的大小。
	这意味着 m_EmpArray 是一个指向指针的指针，它本身并没有分配任何内存来存储指针数组。
	为了使其成为一个实际的数组，你需要分配内存，例如使用 new：
	int size = 10; // 假设我们想要10个职工
	m_EmpArray = new Worker * [size]; // 分配一个包含10个Worker指针的数组	
	*/
	

	void Add_Emp();//添加职工函数

	
	void save();//保存文件
	
	bool m_FileIsEmpty;//标志文件是否为空

	
	int get_EmpNum();//统计人数
	
	void init_Emp();//初始化initialize员工，将文件中的 员工数据 读入系统
	
	void Show_Emp();//显示职工
	
	int IsExist(int id);//按照职工编号判断职工是否存在,若存在返回职工在数组中位置，不存在返回-1
	
	void Del_Emp();//删除职工

	void Mod_Emp();	//修改职工
	
	void Find_Emp();//查找职工
	
	void Sort_Emp();//排序职工
	
	void Clean_File();//清空文件

	~WorkerManager();//析构函数
};