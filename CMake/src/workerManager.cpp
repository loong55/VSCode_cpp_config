#include "workerManager.h"

WorkerManager::WorkerManager()//构造函数，初始化数据
{
	//1.文件不存在情况
	ifstream ifs;//创建 读文件流类 的对象
	ifs.open(FILENAME, ios::in);//以读文件方式 打开文件

	if (!ifs.is_open())//如果文件没有被打开
	{
		cout << "文件不存在" << endl; //测试输出
		this->m_EmpNum = 0;  //初始化人数
		this->m_FileIsEmpty = true; //初始化文件为空标志
		this->m_EmpArray = NULL; //初始化数组
		ifs.close(); //关闭文件
		return;
	}

	//2.文件存在，并且数据为空
	char ch;
	ifs >> ch;
	//从文件流ifs中提取一个字符，并将其存储在变量ch中。ifs是一个ifstream对象，它用于读取文件内容。
	//“>>”是提取符，用于从流中提取数据。在这种情况下，它从文件中读取下一个字符。
	if (ifs.eof())//如果读到的第一个字符 为文件 尾字符
	{
		cout << "文件为空!" << endl;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}

	//3.文件存在，并且记录数据
	this->m_FileIsEmpty = false;
	int num = this->get_EmpNum();
	cout << "职工个数为：" << num << endl;  //测试代码
	this->m_EmpNum = num;  //更新成员属性 


	//根据职工数创建数组
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//初始化职工,将文件中的数据存到数组中
	this->init_Emp();

	////测试代码
	//for (int i = 0; i < m_EmpNum; i++)
	//{
	//	cout << "职工号： " << this->m_EmpArray[i]->m_Id
	//		<< " 职工姓名： " << this->m_EmpArray[i]->m_Name
	//		<< " 部门编号： " << this->m_EmpArray[i]->m_DeptId << endl;
	//}

}

void WorkerManager::Show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//退出系统
void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	cout << "按任意键继续..." << endl;
cin.ignore(); // 清除输入缓冲区
cin.get(); // 等待用户输入//按任意键退出
	exit(0);//退出
}

//添加职工函数
void WorkerManager::Add_Emp()
{
	cout << "请输入添加职工数量" << endl;
	
	int addNum = 0;//添加职工数量
	cin >> addNum;

	if (addNum > 0)
	{
		//添加
		//计算新空间大小
		int newSize = this->m_EmpNum + addNum;//新总人数=原始人数+添加人数

		//开辟新空间
		Worker ** newSpace = new Worker* [newSize];
		//将原来的数据 拷贝到 新空间
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];					
			}
		}
		//批量添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int id; //职工编号
			string name;//职工姓名
			int dSelect;//部门选择

			cout << "请输入第" << i + 1 << "个新职工编号： " << endl;
			cin >> id;

			cout << "请输入第" << i + 1 << "个新职工姓名： " << endl;
			cin >> name;

			cout << "请选择该职工岗位: " << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect; 

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Empolyee(id, name,1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			//将创建职工职责 保存到数组中
			newSpace[this->m_EmpNum + i] = worker;
			//警告是编译器认为数组容量可能不够大，程序是没错的，可以忽略警告
		}		
		//释放原有空间
		delete[] this->m_EmpArray;

		//更改新空间指向
		this->m_EmpArray = newSpace;

		//更新新职工人;
		this->m_EmpNum = newSize;

		//更新文件不为空标志
		this->m_FileIsEmpty = false;

		//提示添加成功
		cout << "成功添加" << addNum << "名新职工！" << endl;

		//保存数据到文件中
		this->save();
	}
	else
	{
		cout << "输入有误！" << endl;
	}

	//按任意键后 清屏回到上级目录
	cout << "按任意键继续..." << endl;
cin.ignore(); // 清除输入缓冲区
cin.get(); // 等待用户输入
	system("clear");
}


//保存文件
void WorkerManager::save()
{
	ofstream ofs;//打开文件
	ofs.open(FILENAME, ios::out);//（打开文件地址，以写文件方式打开）
	//（打开文件地址，以写文件方式打开）

	//将每个人数据写入到文件中
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	ofs.close();//关闭文件
}


//统计文件中的人数
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//打开文件 读

	int id;
	string name;
	int dId;

	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> dId)//按行读
	{
		//记录人数
		num++;
	}
	ifs.close();

	return num;
}

//初始化员工数据
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)//将文本中的数据依次 读入 变量中
	{
		Worker* worker = NULL;
		//根据不同的部门Id创建不同对象
		if (dId == 1)  // 1普通员工
		{
			worker = new Empolyee(id, name, dId);
		}
		else if (dId == 2) //2经理
		{
			worker = new Manager(id, name, dId);
		}
		else //总裁
		{
			worker = new Boss(id, name, dId);
		}
		//存放在数组中
		this->m_EmpArray[index] = worker;
		index++;//索引位置
	}
	//关闭文件
	ifs.close();
}

//显示职工
void WorkerManager::Show_Emp()
{
	if (this->m_FileIsEmpty)//判断文件是否为空
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//利用多态调用接口
			this->m_EmpArray[i]->showInfo();
		}
	}
	//按任意键清屏
	cout << "按任意键继续..." << endl;
cin.ignore(); // 清除输入缓冲区
cin.get(); // 等待用户输入
	system("clear");
}

//判断职工是否存在
int WorkerManager::IsExist(int id)
{
	int index = -1;//索引标志

	for (int i = 0; i < this->m_EmpNum; i++)//遍历所有职工
	{
		if (this->m_EmpArray[i]->m_Id == id)//如果存在id=输入id
		{
			index = i;

			break;
		}
	}

	return index;
}

//删除职工
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		//按职工编号删除
		cout << "请输入想要删除的职工号：" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExist(id);

		if (index != -1)  //说明index上位置数据需要删除
		{
			//数据前移
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//更新数组中记录的人员个数

			this->save(); //删除后数据同步到文件中
			cout << "删除成功！" << endl;
		}
		else
		{
			cout << "删除失败，未找到该职工" << endl;
		}
	}
	//按任意键 清屏
	cout << "按任意键继续..." << endl;
cin.ignore(); // 清除输入缓冲区
cin.get(); // 等待用户输入
	system("clear");
}


//修改职工
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入修改职工的编号：" << endl;
		int id;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//查找到编号的职工
			delete this->m_EmpArray[ret];//删除原数据

			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "查到： " << id << "号职工，请输入新职工号： " << endl;
			cin >> newId;

			cout << "请输入新姓名： " << endl;
			cin >> newName;

			cout << "请输入岗位： " << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;

			Worker* worker = NULL;//创建父类指针，用父类指针指向子类对象，实现多态
			switch (dSelect)
			{
			case1:
				worker = new Empolyee(newId, newName, dSelect);
				break;
			case2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}

			//更改数据 到数组中
			this->m_EmpArray[ret] = worker;
			cout << "修改成功！" << endl;

			//保存到文件中
			this->save();
		}
		else
		{
			cout << "修改失败，查无此人" << endl;
		}
	}

	//按任意键 清屏
	cout << "按任意键继续..." << endl;
cin.ignore(); // 清除输入缓冲区
cin.get(); // 等待用户输入
	system("clear");
}

//查找职工
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入查找的方式：" << endl;
		cout << "1、按职工编号查找" << endl;
		cout << "2、按姓名查找" << endl;

		int select = 0;
		cin >> select;


		if (select == 1) //按职工号查找
		{
			int id;
			cout << "请输入查找的职工编号：" << endl;
			cin >> id;

			int ret = IsExist(id);
			if (ret != -1)
			{
				cout << "查找成功！该职工信息如下：" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "查找失败，查无此人" << endl;
			}
		}
		else if (select == 2) //按姓名查找
		{
			string name;
			cout << "请输入查找的姓名：" << endl;
			cin >> name;

			bool flag = false;  //查找到的标志
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (m_EmpArray[i]->m_Name == name)
				{
					cout << "查找成功,职工编号为："
						<< m_EmpArray[i]->m_Id
						<< " 号的信息如下：" << endl;

					flag = true;
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				cout << "查找失败，查无此人" << endl;
			}
		}
		else
		{
			cout << "输入选项有误" << endl;
		}
	}
	cout << "按任意键继续..." << endl;
cin.ignore(); // 清除输入缓冲区
cin.get(); // 等待用户输入
	system("clear");
}

//排序职工
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
		cout << "按任意键继续..." << endl;
cin.ignore(); // 清除输入缓冲区
cin.get(); // 等待用户输入
		system("clear");
	}
	else
	{
		cout << "请选择排序方式： " << endl;
		cout << "1、按职工号进行升序" << endl;
		cout << "2、按职工号进行降序" << endl;

		int select = 0;
		cin >> select;

		//选择排序算法
		for (int i = 0; i < m_EmpNum; i++)//遍历数组所有元素
		{
			int minOrMax = i;//声明最小值 或 最大值下标
			for (int j = i + 1; j < m_EmpNum; j++) 
			{
				if (select == 1) //升序
				{
					//左边比右边大
					if (m_EmpArray[minOrMax]->m_Id > m_EmpArray[j]->m_Id)
					{
						minOrMax = j;//右边 标志为 小元素
					}
				}
				else  //降序
				{
					//左边比右边小
					if (m_EmpArray[minOrMax]->m_Id < m_EmpArray[j]->m_Id)
					{
						minOrMax = j;// 右边 标志为 大元素
					}
				}
			}
			//左边元素如果没被标志；即右边元素被标志，就左右交换数据
			if (i != minOrMax)
			{
				Worker* temp = m_EmpArray[i];
				m_EmpArray[i] = m_EmpArray[minOrMax];
				m_EmpArray[minOrMax] = temp;
			}
		}
		cout << "排序成功,排序后结果为：" << endl;
		this->save();
		this->Show_Emp();
	}
}

//清空文件
void WorkerManager::Clean_File()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int select = 0;//命令选项
	cin >> select;

	if (select == 1)
	{
		//清空txt文件
		//打开模式 ios::trunc 如果存在删除文件并重新创建,truncate缩短
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		//释放系统数据
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				//删除堆区每一个职工  对象指针
				if (this->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];
					this->m_EmpArray[i] != NULL;
				}
			}

			//删除堆区职工  数组指针
			this->m_EmpNum = 0;
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功！" << endl;
	}
	cout << "按任意键继续..." << endl;
cin.ignore(); // 清除输入缓冲区
cin.get(); // 等待用户输入
	system("clear");
}

//析构函数，释放堆区数据
WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];
			}
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}