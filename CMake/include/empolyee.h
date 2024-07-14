//普通员工文件
#pragma once
#include <iostream>
#include "worker.h"

class Empolyee :public Worker
{
public:
	Empolyee(int id , string name ,int dId);//构造函数

	/*        职工类行为            */
	//显示个人信息
	virtual void showInfo() ;

	//获取岗位名称
	virtual string  getDeptName() ;
};