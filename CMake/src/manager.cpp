#include "manager.h"


//构造函数
Manager::Manager(int id, string name, int dId)//名称编号，名字，部门id
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = dId;
}

//显示个人信息
void Manager::showInfo()
{
	cout << "职工编号： " << this->m_Id
		<< "\t职工姓名： " << this->m_Name
		<< "\t岗位: " << this->getDeptName()
		<< "\t岗位职责： 完成老板交代的任务" << endl;
}

//获取岗位名称
string  Manager::getDeptName()
{
	return string("经理");
}