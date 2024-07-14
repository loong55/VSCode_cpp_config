#include "empolyee.h"

//构造函数
Empolyee::Empolyee(int id, string name, int dId)
{
	//初始化
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = dId;

}


/*职工类行为*/
//显示个人信息
void Empolyee::showInfo()
{ 
	cout << "职工编号： " << this->m_Id
		<< "\t职工姓名： " << this->m_Name
		<< "\t岗位: " << this->getDeptName()
		<< "\t岗位职责： 完成经理交代的任务" << endl;
}

//获取岗位名称
string  Empolyee::getDeptName()
{
	return string("员工");
}