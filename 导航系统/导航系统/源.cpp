#include<iostream>
#include<fstream>
using namespace std;
int cnt;//全局变量
int inf = 0xffff;//无穷大
class edge
{
public:
	int to;//目的节点
	int w;//权值
	int next;//以当前节点为起点的上一条边
};
class graph 
{
public:
	int c_node;
	int c_edge;
	int* first;
	edge* p_edge;
	graph(int c_node,int c_edge)
	{
		this->c_edge = c_edge;
		this->c_node = c_node;
		p_edge = new edge[1 + c_edge * 2];//edge数组，双向存*2 + 1（0号位置不存
		first = new int[c_node + 1]();//first数组,并全部初始化为0,又叫head数组（0号位置不存
	}
	void add(int start, int to, int w)
	{
		p_edge[++cnt].next = first[start];
		first[start] = cnt;
		p_edge[cnt].to = to;
		p_edge[cnt].w = w;
	}

	void dij(int start, int end)
	{
		int min;//用于寻找已确定最短路径
		int m_cnt = 1;//用于作为循环条件
		int* dis = new int[c_node + 1];//距离
		int* s = new int[c_node + 1];//是否为最短路径
		int* p = new int[c_node + 1];//该路径的前一个节点
		int* s_p = new int[c_node + 1]();//用于存储最短路径，模拟栈
		for (int i = 0; i <= c_node; i++)
		{
			s[i] = 0;
			p[i] = 0;
			dis[i] = inf;
		}//初始化
		s[start] = 1;
		dis[start] = 0;
		for (int i = first[start]; i != 0; i = p_edge[i].next)
		{
			dis[p_edge[i].to] = p_edge[i].w;
			p[p_edge[i].to] = start;
		}//写入起点的相应信息

		while(m_cnt != 0)
		{
			min = 0;
			m_cnt = 0;
			for (int i = 1; i <= c_node ; i++)//i遍历所有为F的节点，在其中找到min
			{
				if (s[i] == 0)
				{
					if (dis[min] > dis[i])
						min = i;//找到已确定的最短路
					m_cnt++;
				}
			}
			s[min] = 1;
			for (int j = first[min]; j != 0; j = p_edge[j].next)//j表示中继点为起点的边的编号
			{
				if (dis[p_edge[j].to] > dis[min] + p_edge[j].w)
				{
					dis[p_edge[j].to] = dis[min] + p_edge[j].w;
					p[p_edge[j].to] = min;
				}
			}
		}
		int j = 0;
		for (int i = end; i != 0; i = p[i])
		{
			s_p[j] = i;
			j++;
		}
		for (int i = j - 1; i > 0; i--)
		{
			cout << s_p[i];
			cout << "->";
		}
		cout << s_p[0] << endl;
		cout << dis[end] << endl;//输出最短距离
	}

	void floyd(int c_point, int* point)
	{
		int** A = new int* [c_node+1];
		int** path = new int* [c_node+1];
		for (int i = 0; i <= c_node; i++)
		{
			A[i] = new int[c_node+1];
			path[i] = new int[c_node+1];
		}
		for (int i = 0; i <= c_node; i++)
		{
			for (int j = 0; j <= c_node; j++)
			{
				if (i == j)
					A[i][j] = 0;//对角线全0
				else
					A[i][j] = inf;//全初始化为无穷大
				path[i][j] = -1;
			}
		}
		
		for (int i = 1; i <= c_node; i++)//i用来遍历节点
		{
			for (int j = first[i]; j != 0; j = p_edge[j].next)//j用来寻边
			{
				A[i][p_edge[j].to] = p_edge[j].w;
			}
		}//录入初始边信息

		for (int i = 1; i <= c_node; i++)//中继节点
		{
			for (int j = 1; j <= c_node; j++)
			{
				if(i != j)
				for (int k = 1; k <= c_node; k++)
				{
					if (j != k && i != k)
					if (A[j][k] > A[j][i] + A[i][k])
					{
						A[j][k] = A[j][i] + A[i][k];//更新A
						path[j][k] = i;//更新path
					}
				}
			}
		}
		
	
		/*
		for (int i = 1; i <= c_node; i++)
		{
			for (int j = 1; j <= c_node; j++)
			{
				cout << path[i][j] << "\t";
			}
			cout << endl;
		}//测试
		*/
		
	//-----------------------------------------------------floyd↑
		int** dp = new int* [c_point];
		int** pre = new int* [c_point];
		int* s_p = new int[c_node]();//模拟栈，用来存储最终路径
		for (int i = 0; i < c_point; i++)
		{
			dp[i] = new int[1 << c_point];
			pre[i] = new int[1 << c_point];
		}
		//创建dp矩阵
		for (int i = 0; i < c_point; i++)
		{
			for (int j = 0; j < (1 << c_point); j++)
			{
				dp[i][j] = inf;//dp全部初始化为inf
				pre[i][j] = -1;//pre全部初始化为-1
			}
		}
		dp[0][1] = 0;//设0为起点，初始化为0

		for (int s = 0; s < (1 << c_point); s++)
		{
			for (int i = 0; i < c_point; i++)
			{
				if (s & (1 << i))//i在s集合中
				{
					for (int j = 0; j < c_point; j++)
					{
						if (!(s & (1 << j)) && A[point[i]][point[j]] != inf)//j不在s中，且ij可达
						{
							if (dp[j][s | (1 << j)] > dp[i][s] + A[point[i]][point[j]])
							{
								dp[j][s | (1 << j)] = dp[i][s] + A[point[i]][point[j]];//更新dp
								pre[j][s | (1 << j)] = i;//更新pre
							}
						}
					}
				}
			}
		}//主体

		/*
		for (int i = 0; i < c_point; i++)
		{
			for (int j = 0; j < (1 << c_point); j++)
			{
				cout << pre[i][j] << "\t";
			}
			cout << endl;
		}//测试
		*/
		int shortest = dp[1][(1 << c_point) - 1] + A[point[1]][point[0]];//全1状态回到起点
		int min_p = 1;
		for (int i = 2; i < c_point; i++)
		{
			if (shortest > dp[i][(1 << c_point) - 1] + A[point[i]][point[0]])
			{
				shortest = dp[i][(1 << c_point) - 1] + A[point[i]][point[0]];
				min_p = i;
			}
		}
		cout << "必经点最短距离为：" << shortest << endl;

		int j = 0;
		int k = (1 << c_point) - 1;//初始化为全1，k表示状态

		int a, b;//a为floyd寻点的起点，b为终点（都是直接的节点编号）
		int l, r;//分别用作temp数组读入的左右计数
		int n;//a为floyd寻点的终点的point数组下标
		int m;//m为path数组反映的中继点（直接的节点编号）
		int* temp = new int[c_node]();//用于存储floyd未去0的路径

		for (int i = min_p; i != -1; i = n)//遍历出必经点的顺序,k表示状态，从全1开始持续倒退
		{
			n = pre[i][k];
			if (n != -1)//下一个点不是起点时，要输出floyd的路径
			{
				a = point[i];
				b = point[n];
				m = path[a][b];
				l = 1;
				r = c_node - 2;
				for(int z = 0; z < c_node; z++)
				{
					temp[z] = 0;
				}
				temp[0] = a;//输入起点
				temp[c_node - 1] = b;//输入终点

				while(m != -1)
				{
					if (path[a][m] == -1)
					{
						temp[l] = m;
						l++;
						a = m;
						m = path[m][b];
					}
					else if (path[m][b] == -1)
					{
						temp[r] = m;
						r--;
						b = m;
						m = path[a][m];
					}
					else if (path[a][m] != -1 && path[m][b] != -1)
					{
						m = path[a][m];
					}//没遇到-1时，统一往a的方向转移
				}//创建temp数组

				for (int i = 0; i < c_node - 1; i++)
				{
					if (temp[i] != 0)
					{
						s_p[j] = temp[i];
						j++;
					}
				}//将temp数组中的路径处理之后输出到s_p中

				//处理path内存的路径，即floyd处理出的必经点之间的路径
				k = k ^ (1 << i);//更新k，即将第i位变成0，倒退
			}
			else
			{
				s_p[j] = point[0];
			}
		}
		
		//处理返回起点的路径
		int q = 0;
		int* s_q = new int[c_node]();//用于存返回起点的路径
		a = point[0];
		b = point[min_p];
		m = path[a][b];
		l = 1;
		r = c_node - 2;
		for (int z = 0; z < c_node; z++)
		{
			temp[z] = 0;
		};//全部初始化为0
		temp[0] = a;//输入起点
		temp[c_node - 1] = b;//输入终点

		while (m != -1)
		{
			if (path[a][m] == -1)
			{
				temp[l] = m;
				l++;
				a = m;
				m = path[m][b];
			}
			else if (path[m][b] == -1)
			{
				temp[r] = m;
				r--;
				b = m;
				m = path[a][m];
			}
			else if (path[a][m] != -1 && path[m][b] != -1)
			{
				m = path[a][m];
			}//没遇到-1时，统一往a的方向转移
		}//创建temp数组

		for (int i = 0; i < c_node; i++)
		{
			if (temp[i] != 0)
			{
				s_q[q] = temp[i];
				q++;
			}
		}//将temp数组中的路径处理之后输出到s_q中
		//处理返回起点的路径

		for (int i = j; i >= 0; i--)
		{
			cout << s_p[i];
			cout << "->";
		}
		for (int i = q - 2; i > 0; i--)
		{
			cout << s_q[i];
			cout << "->";
		}
		cout << point[0];
		
	}
};
int main()
{
	ifstream ifs;
	int c_node, c_edge;
	int start, to, w;
	ifs.open("graph.txt", ios::in);
	ifs >> c_node>> c_edge;
	//读入节点数与边数
	graph g(c_node, c_edge);
	
	cnt = 0;
	for (int i = 0; i < c_edge; i++)
	{
		ifs >> start >> to >> w;
		g.add(start, to, w);
		g.add(to, start, w);//无向图双向存边
	}//从文件读入图
	
	int* test = new int[3];
	test[0] = 1;
	test[1] = 24;
	test[2] = 13;
	



	g.floyd(3, test);
	
	return 0;
}