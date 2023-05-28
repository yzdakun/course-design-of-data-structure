#include"manager.h"
#include<string>
using namespace std;
course::course()
{
	this->kind = 1;
	this->week = "0";
	this->c_week = 0;
}
bool cmp(course a, course b)
{
	return a.StartTime < b.StartTime;
}
void manager::init()
{
	ifstream ifs;
	course c;
	student s;
	int j = 0;
	ifs.open("course.txt", ios::in);
	ifs >> count_course;
	for (int i = 0; i < count_course; i++)
	{
		ifs >> c.name;
		ifs >> c.StartTime;
		ifs >> c.EndTime;
		ifs >> c.place;
		ifs >> c.Class;
		ifs >> c.period;

		ifs >> c.c_week;//单次的设成0
		ifs >> c.week;//单次的设成0
		course_Array.push_back(c);
	}
	ifs.close();
	ifs.open("student.txt", ios::in);
	ifs >> count_student;
	for (int i = 0; i < count_student; i++)
	{
		ifs >> s.name;
		ifs >> s.password;
		ifs >> s.ClassNum;
		ifs >> s.id;

		student_Array.push_back(s);
	}
}
void manager::add_class()
{
	int num, j = 0;
	course c;
	cout << "请选择要添加的课程数：" << endl;
	cin >> num;
	for (int i = 0; i < num; i++)
	{
		while (1)
		{
			cout << "请输入第" << i + 1 << "个课程的名称：" << endl;
			cin >> c.name;
			for (j = 0; j < count_course; j++)
			{
				if (course_Array[j].name == c.name)
				{
					cout << "该课程已存在！" << endl;
					break;
				}
			}
			if (j == count_course)
				break;
		}
		cout << "请输入第" << i + 1 << "个课程的开始时间：" << endl;
		cin >> c.StartTime;
		cout << "请输入第" << i + 1 << "个课程的结束时间：" << endl;
		cin >> c.EndTime;
		cout << "请输入第" << i + 1 << "个课程的上课地点：" << endl;
		cin >> c.place;
		cout << "请输入第" << i + 1 << "个课程的上课班级：" << endl;
		cin >> c.Class;
		cout << "第" << i + 1 << "个课程是否为单次课：" << endl;
		cout << "1.是	2.否" << endl;
		cin >> c.period;
		if (c.period == 2)
		{
			cout << "请输入第" << i + 1 << "个课程的上课周数：" << endl;
			cin >> c.c_week;
			cout << "请依次输入第" << i + 1 << "个课程的上课周：" << endl;
			cin >> c.week;
		}
		else
		{
			c.c_week = 1;
			cout << "请依次输入第" << i + 1 << "个课程的上课周：" << endl;
			cin >> c.week;
		}
		course_Array.push_back(c);
		count_course++;
	}
	
	sort(course_Array.begin(), course_Array.end(), cmp);
	fUpdate();
	cout << "添加成功！" << endl;
}
void manager::delete_class()
{
	string name;
	int num, i = 0;
	while (1)
	{
		cout << "请输入要删除的课程名称：" << endl;
		cin >> name;

		for (i = 0; i < count_course; i++)
		{
			if (course_Array[i].name == name)
			{
				num = i;
				break;
			}
		}
		if (i == count_course)
			cout << "该课程不存在！" << endl;
		else
			break;
	}
	auto it = course_Array.begin() + num;
	course_Array.erase(it);
	count_course--;
	fUpdate();
	cout << "删除成功！" << endl;
}
void manager::change_class()
{
	string name;
	int num, j = 0, i = 0;
	course c;
	while (1)
	{
		cout << "请输入要修改的课程名称：" << endl;
		cin >> name;
		for (i = 0; i < count_course; i++)
		{
			if (course_Array[i].name == name)
			{
				num = i;
				break;
			}
		}
		if (i == count_course)
			cout << "该课程不存在！" << endl;
		else
			break;
	}
	while (1)
	{
		cout << "请输入修改后课程的名称：" << endl;
		cin >> c.name;
		for (j = 0; j < count_course; j++)
		{
			if (course_Array[j].name == c.name && num != j)
			{
				cout << "该课程已存在！" << endl;
				break;
			}
		}
		if (j == count_course)
			break;
	}
	cout << "请输入修改后课程的开始时间：" << endl;
	cin >> c.StartTime;
	cout << "请输入修改后课程的结束时间：" << endl;
	cin >> c.EndTime;
	cout << "请输入修改后课程的上课地点：" << endl;
	cin >> c.place;
	cout << "请输入修改后课程的上课班级：" << endl;
	cin >> c.Class;
	cout << "修改后课程是否为单次课：" << endl;
	cout << "1.是	2.否" << endl;
	cin >> c.period;
	if (c.period == 2)
	{
		cout << "请输入修改后课程的上课周数：" << endl;
		cin >> c.c_week;
		cout << "请依次输入修改后课程的上课周：" << endl;
		cin >> c.week;
	}
	else
	{
		c.week = 1;
		cout << "请依次输入修改后课程的上课周：" << endl;
		cin >> c.week;
	}
	course_Array[num] = c;
	fUpdate();
	cout << "修改成功！" << endl;
}
void manager::add_student()
{
	int num, j = 0;
	student s;
	string s2;
	string s1 = "2021";
	cout << "请选择要添加的学生数：" << endl;
	cin >> num;
	for (int i = 0; i < num; i++)
	{
		while (1)
		{
			cout << "请输入第" << i + 1 << "个学生的id：" << endl;
			cin >> s.id;
			for (j = 0; j < count_student; j++)
			{
				if (student_Array[j].id == s.id)
				{
					cout << "该学生已存在！" << endl;
					break;
				}
			}
			if (j == count_student)
				break;
		}
		cout << "请输入第" << i + 1 << "个学生的姓名：" << endl;
		cin >> s.name;
		cout << "请输入第" << i + 1 << "个学生的班级：" << endl;
		cin >> s.ClassNum;
		s2 = to_string(s.id);
		s1 = "2021";
		s1 = s1 + s2;
		s.password = s1;//设置默认密码
		student_Array.push_back(s);
		count_student++;
	}
	fUpdate();
	cout << "添加成功！" << endl;
}
void manager::delete_student()
{
	int id;
	int num, i = 0;
	while (1)
	{
		cout << "请输入要删除的学生id：" << endl;
		cin >> id;

		for (i = 0; i < count_student; i++)
		{
			if (student_Array[i].id == id)
			{
				num = i;
				break;
			}
		}
		if (i == count_student)
			cout << "该学生不存在！" << endl;
		else
			break;
	}
	auto it = student_Array.begin() + num;
	student_Array.erase(it);
	count_student--;
	fUpdate();
	cout << "删除成功！" << endl;
}
void manager::change_student()
{
	int id;
	int num, j = 0, i = 0;
	student s;
	while (1)
	{
		cout << "请输入要修改的学生的id：" << endl;
		cin >> id;
		for (i = 0; i < count_student; i++)
		{
			if (student_Array[i].id == id)
			{
				num = i;
				break;
			}
		}
		if (i == count_student)
			cout << "该学生不存在！" << endl;
		else
			break;
	}
	while (1)
	{
		cout << "请输入修改后的id：" << endl;
		cin >> s.id;
		for (j = 0; j < count_student; j++)
		{
			if (student_Array[j].id == s.id && num != j)
			{
				cout << "该学生已存在！" << endl;
				break;
			}
		}
		if (j == count_student)
			break;
	}
	cout << "请输入修改后学生的姓名：" << endl;
	cin >> s.name;
	cout << "请输入修改后学生的班级：" << endl;
	cin >> s.ClassNum;
	s.password = student_Array[num].password;
	student_Array[num] = s;
	fUpdate();
	cout << "修改成功！" << endl;
}
void manager::fUpdate()
{
	ofstream ofs;
	ofs.open("course.txt", ios::out);//out为覆写模式，即会将原来文件中的内容全部清除
	ofs << count_course << endl;
	for (int i = 0; i < count_course; i++)
	{
		ofs << course_Array[i].name << "\t"
			<< course_Array[i].StartTime << "\t"
			<< course_Array[i].EndTime << "\t"
			<< course_Array[i].place << "\t"
			<< course_Array[i].Class << "\t"
			<< course_Array[i].period << "\t"
			<< course_Array[i].c_week << "\t"
			<< course_Array[i].week << endl;
	}//写文件操作
	ofs.close();
	ofs.open("student.txt", ios::out);
	ofs << count_student << endl;
	for (int i = 0; i < count_student; i++)
	{
		ofs << student_Array[i].name << "\t"
			<< student_Array[i].password << "\t"
			<< student_Array[i].ClassNum << "\t"
			<< student_Array[i].id << endl;
	}//写文件操作
	ofs.close();
}
void manager::connection()
{
	ofstream ofs;
	ofs.open("course_list.txt", ios::out);
	vector<course> temp;
	temp = course_Array;
	int m_time = 0;
	for (int j = 1; j <= 19; j++)
	{
		for (int k = 0; k < count_course; k++)
		{
			if (temp[k].check[j] == 1)
			{
				ofs << temp[k].name << "\t";
				ofs << temp[k].StartTime << "\t";
				ofs << temp[k].EndTime << "\t";
				ofs << temp[k].place << "\t";
				ofs << temp[k].Class << "\t";
				ofs << temp[k].kind << endl;
				m_time = temp[k].EndTime;
			}
		}
		for (int k = 0; k < count_course; k++)
		{
			temp[k].StartTime += 168;
			temp[k].EndTime += 168;
		}
	}
}
void manager::translate()
{
	string s;
	int start, end, single;

	for (int i = 0; i < count_course; i++)
	{
		s = course_Array[i].week;
		int j = 0;
		while (j < s.length())
		{
			if (s[j] == '-')
			{	
				if ((j>1)&&s[j - 2] >= '0' && s[j - 2] <= '9')//判断是不是十位数
				{
					start = s[j - 1] - '0' + (s[j - 2] - '0') * 10;
				}
				else
				{
					start = s[j - 1] - '0';
				}
				if ((j + 2) < s.length()&&s[j + 2] >= '0' && s[j + 2] <= '9')//判断是不是十位数
				{
					end = s[j + 2] - '0' + (s[j + 1] - '0') * 10;
					j += 3;
				
				}
				else
				{
					end = s[j + 1] - '0';
					j += 2;
					
				}
				for (int k = start; k <= end; k++)
				{
					course_Array[i].check[k] = 1;
				}
				continue;
			}


			else if (s[j] >= '0' && s[j] <= '9')//单个周
			{
				if ((j + 1) < s.length()&&s[j + 1] >= '0' && s[j + 1] <= '9')//看看这个数是不是十位数，如果是十位
				{
					single = 10 * (s[j] - '\0') + (s[j + 1] - '\0');
					if ((j == 0 && s[j + 2] == ',')||(j == 0 && s[j + 2] == '\0'))//第一个
					{
						course_Array[i].check[single] = 1;
						j += 3;
					}
					else if ((j + 2) < s.length() && j > 0 && s[j - 1] == ',' && s[j + 2] == ',')//并且左右都是“，”
					{
						course_Array[i].check[single] = 1;
						j += 3;

					}
					else if ((j + 2) < s.length() && j > 0 && s[j + 2] == '\0' && s[j - 1] == ',')//最后一个
					{
						course_Array[i].check[single] = 1;
						j += 3;

					}
					else
						j++;
				}
				else//不是十位数
				{
					single = s[j] - '0';
					if ((j + 1) < s.length() && j > 0 && s[j - 1] == ',' && s[j + 1] == ',')
					{
						course_Array[i].check[single] = 1;
						j += 2;

					}
					else if ((j == 0 && s[j + 1] == ',') || (j == 0 && s[j + 1] == '\0'))//第一个
					{
						course_Array[i].check[single] = 1;
						j += 2;

					}
					else if ((j + 1) < s.length() && j > 0 && s[j + 1] == '\0' && s[j - 1] == ',')
					{
						course_Array[i].check[single] = 1;
						j += 2;

					}
					else
						j++;
				}
				
			}
			else
				j++;
		}
	}
}