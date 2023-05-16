#include<iostream>
#include<fstream>
using namespace std;
int cnt;//ȫ�ֱ���
int inf = 0xffff;//�����
class edge
{
public:
	int to;//Ŀ�Ľڵ�
	int w;//Ȩֵ
	int next;//�Ե�ǰ�ڵ�Ϊ������һ����
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
		p_edge = new edge[1 + c_edge * 2];//edge���飬˫���*2 + 1��0��λ�ò���
		first = new int[c_node + 1]();//first����,��ȫ����ʼ��Ϊ0,�ֽ�head���飨0��λ�ò���
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
		int min;//����Ѱ����ȷ�����·��
		int m_cnt = 1;//������Ϊѭ������
		int* dis = new int[c_node + 1];//����
		int* s = new int[c_node + 1];//�Ƿ�Ϊ���·��
		int* p = new int[c_node + 1];//��·����ǰһ���ڵ�
		int* s_p = new int[c_node + 1]();//���ڴ洢���·����ģ��ջ
		for (int i = 0; i <= c_node; i++)
		{
			s[i] = 0;
			p[i] = 0;
			dis[i] = inf;
		}//��ʼ��
		s[start] = 1;
		dis[start] = 0;
		for (int i = first[start]; i != 0; i = p_edge[i].next)
		{
			dis[p_edge[i].to] = p_edge[i].w;
			p[p_edge[i].to] = start;
		}//д��������Ӧ��Ϣ

		while(m_cnt != 0)
		{
			min = 0;
			m_cnt = 0;
			for (int i = 1; i <= c_node ; i++)//i��������ΪF�Ľڵ㣬�������ҵ�min
			{
				if (s[i] == 0)
				{
					if (dis[min] > dis[i])
						min = i;//�ҵ���ȷ�������·
					m_cnt++;
				}
			}
			s[min] = 1;
			for (int j = first[min]; j != 0; j = p_edge[j].next)//j��ʾ�м̵�Ϊ���ıߵı��
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
		cout << dis[end] << endl;//�����̾���
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
					A[i][j] = 0;//�Խ���ȫ0
				else
					A[i][j] = inf;//ȫ��ʼ��Ϊ�����
				path[i][j] = -1;
			}
		}
		
		for (int i = 1; i <= c_node; i++)//i���������ڵ�
		{
			for (int j = first[i]; j != 0; j = p_edge[j].next)//j����Ѱ��
			{
				A[i][p_edge[j].to] = p_edge[j].w;
			}
		}//¼���ʼ����Ϣ

		for (int i = 1; i <= c_node; i++)//�м̽ڵ�
		{
			for (int j = 1; j <= c_node; j++)
			{
				if(i != j)
				for (int k = 1; k <= c_node; k++)
				{
					if (j != k && i != k)
					if (A[j][k] > A[j][i] + A[i][k])
					{
						A[j][k] = A[j][i] + A[i][k];//����A
						path[j][k] = i;//����path
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
		}//����
		*/
		
	//-----------------------------------------------------floyd��
		int** dp = new int* [c_point];
		int** pre = new int* [c_point];
		int* s_p = new int[c_node]();//ģ��ջ�������洢����·��
		for (int i = 0; i < c_point; i++)
		{
			dp[i] = new int[1 << c_point];
			pre[i] = new int[1 << c_point];
		}
		//����dp����
		for (int i = 0; i < c_point; i++)
		{
			for (int j = 0; j < (1 << c_point); j++)
			{
				dp[i][j] = inf;//dpȫ����ʼ��Ϊinf
				pre[i][j] = -1;//preȫ����ʼ��Ϊ-1
			}
		}
		dp[0][1] = 0;//��0Ϊ��㣬��ʼ��Ϊ0

		for (int s = 0; s < (1 << c_point); s++)
		{
			for (int i = 0; i < c_point; i++)
			{
				if (s & (1 << i))//i��s������
				{
					for (int j = 0; j < c_point; j++)
					{
						if (!(s & (1 << j)) && A[point[i]][point[j]] != inf)//j����s�У���ij�ɴ�
						{
							if (dp[j][s | (1 << j)] > dp[i][s] + A[point[i]][point[j]])
							{
								dp[j][s | (1 << j)] = dp[i][s] + A[point[i]][point[j]];//����dp
								pre[j][s | (1 << j)] = i;//����pre
							}
						}
					}
				}
			}
		}//����

		/*
		for (int i = 0; i < c_point; i++)
		{
			for (int j = 0; j < (1 << c_point); j++)
			{
				cout << pre[i][j] << "\t";
			}
			cout << endl;
		}//����
		*/
		int shortest = dp[1][(1 << c_point) - 1] + A[point[1]][point[0]];//ȫ1״̬�ص����
		int min_p = 1;
		for (int i = 2; i < c_point; i++)
		{
			if (shortest > dp[i][(1 << c_point) - 1] + A[point[i]][point[0]])
			{
				shortest = dp[i][(1 << c_point) - 1] + A[point[i]][point[0]];
				min_p = i;
			}
		}
		cout << "�ؾ�����̾���Ϊ��" << shortest << endl;

		int j = 0;
		int k = (1 << c_point) - 1;//��ʼ��Ϊȫ1��k��ʾ״̬

		int a, b;//aΪfloydѰ�����㣬bΪ�յ㣨����ֱ�ӵĽڵ��ţ�
		int l, r;//�ֱ�����temp�����������Ҽ���
		int n;//aΪfloydѰ����յ��point�����±�
		int m;//mΪpath���鷴ӳ���м̵㣨ֱ�ӵĽڵ��ţ�
		int* temp = new int[c_node]();//���ڴ洢floydδȥ0��·��

		for (int i = min_p; i != -1; i = n)//�������ؾ����˳��,k��ʾ״̬����ȫ1��ʼ��������
		{
			n = pre[i][k];
			if (n != -1)//��һ���㲻�����ʱ��Ҫ���floyd��·��
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
				temp[0] = a;//�������
				temp[c_node - 1] = b;//�����յ�

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
					}//û����-1ʱ��ͳһ��a�ķ���ת��
				}//����temp����

				for (int i = 0; i < c_node - 1; i++)
				{
					if (temp[i] != 0)
					{
						s_p[j] = temp[i];
						j++;
					}
				}//��temp�����е�·������֮�������s_p��

				//����path�ڴ��·������floyd������ıؾ���֮���·��
				k = k ^ (1 << i);//����k��������iλ���0������
			}
			else
			{
				s_p[j] = point[0];
			}
		}
		
		//����������·��
		int q = 0;
		int* s_q = new int[c_node]();//���ڴ淵������·��
		a = point[0];
		b = point[min_p];
		m = path[a][b];
		l = 1;
		r = c_node - 2;
		for (int z = 0; z < c_node; z++)
		{
			temp[z] = 0;
		};//ȫ����ʼ��Ϊ0
		temp[0] = a;//�������
		temp[c_node - 1] = b;//�����յ�

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
			}//û����-1ʱ��ͳһ��a�ķ���ת��
		}//����temp����

		for (int i = 0; i < c_node; i++)
		{
			if (temp[i] != 0)
			{
				s_q[q] = temp[i];
				q++;
			}
		}//��temp�����е�·������֮�������s_q��
		//����������·��

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
	//����ڵ��������
	graph g(c_node, c_edge);
	
	cnt = 0;
	for (int i = 0; i < c_edge; i++)
	{
		ifs >> start >> to >> w;
		g.add(start, to, w);
		g.add(to, start, w);//����ͼ˫����
	}//���ļ�����ͼ
	
	int* test = new int[3];
	test[0] = 1;
	test[1] = 24;
	test[2] = 13;
	



	g.floyd(3, test);
	
	return 0;
}