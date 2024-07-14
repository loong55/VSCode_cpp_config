#include <iostream>
using namespace std;
#include "workerManager.h"

int main()
{
	//实例化管理对象
	WorkerManager wm;	
	int choice = 0;
	while (true)
	{
		//调用展示菜单成员函数
		wm.Show_Menu();
		cout << "请选择：" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0:	//退出系统
			wm.ExitSystem();
			break;
		case 1://添加职工
			wm.Add_Emp();
			break;
		case 2://显示职工
			wm.Show_Emp();
			break;
		case 3://删除职工
			wm.Del_Emp();
			break;
		case 4://修改职工
			wm.Mod_Emp();
			break;
		case 5://查找职工
			wm.Find_Emp();
			break;
		case 6://排序职工
			wm.Sort_Emp();
			break;
		case 7:
			wm.Clean_File();//清空文档
			break;
		default:
			system("clear");//清屏
			break;
		}
	}
	cout << "按任意键继续..." << endl;
cin.ignore(); // 清除输入缓冲区
cin.get(); // 等待用户输入
	return 0;
}