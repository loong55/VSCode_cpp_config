#pragma once
#include <iostream>
using namespace std;
#include "worker.h"//包含父类头文件

//老板类类
class Boss :public Worker//老板类对象 继承工作者父类  属性和行为
{
public:
	//构造函数,只作声明
	Boss(int id, string name, int dId);//名称编号，名字，部门id


	//重写父类成员函数
	/*        职工类行为            */
	//显示个人信息
	virtual void showInfo();

	//获取岗位名称
	virtual string  getDeptName();

};
