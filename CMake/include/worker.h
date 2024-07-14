#pragma once
#include <iostream>
using namespace std;
#include <string>

//职工抽象类
class Worker
{
public:
	/*职工类行为*/

	//显示个人信息
	virtual void showInfo() = 0;

	//获取岗位名称
	virtual string  getDeptName() = 0;


	/*职工属性*/

	//职工编号
	int m_Id;
	//职工姓名
	string m_Name;
	//部门编号
	int m_DeptId;

	//抽象基类，不需要具体实现，所以不用写cpp源文件！！
};