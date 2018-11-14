#include<iostream>
#include<list>
#include<set>
#include<stack>
#include<iterator>
#include<string>
#define INT_MAX +2147483647
#define INT_MIN -2147483648
using namespace std;

int min(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}
class graphlist;		// FORWARD DECLARATION
class graph;


struct node
{
	int data;
	int weight;
	node* next;
};

class graphlist	// COMPOSITION
{
private:
	node* head;
protected:
	int length;
public:
	graphlist()
	{
		head = NULL;
		length = 0;
	}
	void insertnode(int data,int weight)
	{
		node* temp = new node;
		temp->data = data;
		temp->weight = weight;
		temp->next = NULL;
		if (head == NULL)
		{
			head = temp;
		}
		else
		{
			node * ptr = head;
			for (; ptr->next; ptr = ptr->next);
			ptr->next = temp;
		}
		length++;
	}
	int ispresentdata(int data, node* ptr)
	{
		if (ptr == NULL)
			return 0;
		else
		{
			for (; ptr; ptr = ptr->next)
				if (ptr->data==data)
					return 1;
			return 0;
		}
	}

	int deletenode(int data)
	{
		int ispresent = ispresentdata(data, head);
		if (ispresent)
		{
			if (head->data == data)
			{
				node* ptr = head;
				head = head->next;
			}
			else
			{
				node * ptr = head;
				node* temp = head;
				for (; ptr->next->data != data; ptr = ptr->next);
				temp = ptr->next;
				ptr->next = temp->next;
				temp->next = NULL;
				delete temp;
			}

			length--;
			return 1;
		}
		else
		{
			return 0;
		}
	}
	void displaylist()
	{
		node* ptr = head;
		for (; ptr; ptr = ptr->next)
		{
			cout << ptr->data << "  ";
		}
		cout << endl;
	}
	int deletelist()
	{
		int data;
		int count = 0;
		while (head != NULL)
		{
			data = head->data;
			deletenode(data);
			count++;;
		}
		return count;
	}
	friend class graph;
};



class graph			// COMPOSITION
{
private:
	graphlist **A; int v; int e; int Asize;
	char x;
	char *p;
public:
	graph()
	{
		x = 'A';
		cout << "ENTER NUMBER OF VERTICES\n";
		cin >> v;
		cin.get();
		A = new graphlist*[v + 1];
		A[0] = NULL;
		for (int i = 1; i <= v; i++)
			A[i] = new graphlist;

		this->p = new char[v + 1];
		(this->p)[0] = 0;
		for (int i = 0; i < v; i++)
		{
				(this->p)[i + 1] = x;
				x++;
				if (x == 'Z' + 1)
					x = 'a';
				if (p[i + 1] != 0)
					cout << "NODE NUMBER " << i + 1 << " :: " << this->p[i + 1] << endl;
		}
		Asize = v;
		e=0;
    	performer();
	}
	graph(int v)
	{
		x = 'A';
		A = new graphlist*[v + 1];
		A[0] = NULL;
		for (int i = 1; i <= v; i++)
			A[i] = new graphlist;

		this->p = new char[v + 1];
		(this->p)[0] = 0;
		for (int i = 0; i < v; i++)
		{
			(this->p)[i + 1] = x;
			x++;
			if (x == 'Z' + 1)
				x = 'a';
		}
		Asize = v;
		e=0;
	}
	int isdeletedvertex(int v)
	{
		if (A[v] == NULL)
			return 1;
		return 0;
	}
	int ispresentedge(int u, int v)
	{
		if (!isdeletedvertex(u) && !isdeletedvertex(v))
		{
			if (A[u]->ispresentdata(v, A[u]->head))
				return 1;
		}
		return 0;
	}

	void insertedge()
	{
		cout << "SOURCE AND DESTINATION RESPECTIVELY\n";
		int src, dest; int weight;
		cin >> src;
		cin.get();
		cin >> dest;
		cin.get();
		cout << "ENTER WEIGHT OF THE EDGE\n";
		cin >> weight;
		cin.get();

		if(A[src] && A[dest])
		if (!A[src]->ispresentdata(dest, A[src]->head))
		{
			A[src]->insertnode(dest,weight);
			e++;
		}
		else
		{
			cout << "EDGE ALREADY EXISTS\n";
		}

	}
	void insertedge(int src,int dest,int weight)
	{
		if(A[src] && A[dest])
		if (!A[src]->ispresentdata(dest, A[src]->head))
		{
			A[src]->insertnode(dest,weight);
			e++;
		}
		else
		{
			cout << "EDGE ALREADY EXISTS\n";
		}

	}
	void deleteedge()
	{
		cout << " SOURCE AND DESTINATION RESPRCTIVELY\n";
		int src, dest;
		cin >> src;
		cin.get();
		cin >> dest;
		cin.get();
		if (!isdeletedvertex(src) && !isdeletedvertex(dest))
		{
			if((A[src]->deletenode(dest)));
			e--;
		}
		else
		{
			cout << "EDGE DOES NOT EXIST\n";
		}
	}

	void deleteedge(int src, int dest)
	{
		if (!isdeletedvertex(src) && !isdeletedvertex(dest))
		{
			if ((A[src]->deletenode(dest)));
			e--;
		}
		else
		{
			cout << "EDGE DOES NOT EXIST\n";
		}
	}
	void insertvertex()
	{
		graphlist **B;
		B = new graphlist*[Asize + 2];
		B[0] = NULL;

		for (int i = 1; i <= Asize; i++)
		{
			B[i] = A[i];
		}
		B[Asize + 1] = new graphlist;
		A = B;

		char *t = p;
		p = new char[Asize + 2];
		for (int i = 0; i <= Asize; i++)
			p[i] = t[i];
		if (x == 'Z' + 1)
		{
			x = 'a';
			p[Asize + 1] = x;
			x++;

		}
		else
		{
			p[Asize + 1] = x;
			x++;

		}
		Asize++;
		cout << "NODE "<<Asize<<" :: " << p[Asize] << " INSERTED\n";
	}
	void deletevertex()
	{
		int n;
		cout << "ENTER NODE NUMBER ::\n";
		cin >> n;
		cin.get();

		if (n<=Asize && A[n])
		{
			for (int i = 1; i <= Asize; i++)
			{
				if (A[i] && A[i]->ispresentdata(n, A[i]->head))
				{
					deleteedge(i, n);
				}
			}
			e = e - (A[n]->deletelist());
			A[n] = NULL;
			v--;
			p[n] = 0;

		}
	}

	void deletevertex(int n)
	{
		if (A[n])
		{
			for (int i = 1; i <= v; i++)
			{
				if (A[i]->ispresentdata(n, A[i]->head))
				{
					deleteedge(i, n);
				}
			}
			e = e - (A[n]->deletelist());
			A[n] = NULL;
			v--;
			p[n] = 0;
		}
	}
	int indegree(int n)
	{
		int count = 0;
		for (int i = 1; i <= Asize; i++)
		{
			if (i != n)
				if (A[i] && A[i]->ispresentdata(n, A[i]->head))
				{
					count++;
				}
		}
		return count;
	}
	int indegree()
	{
		int n;
		cout << "ENTER NODE NUMBER ::\n";
		cin >> n;
		cin.get();
		int count = 0;
		for (int i = 1; i <= Asize; i++)
		{
			if(i!=n)
				if (A[i] && A[i]->ispresentdata(n,A[i]->head))
				{
					count++;
				}
		}
		return count;
	}
	int outdegree(int v)
	{
		if(v<=Asize)
		if (!isdeletedvertex(v))
			return A[v]->length;
		return 0;
	}
	int outdegree()
	{
		int v;
		cout << "ENTER NODE NUMBER ::\n";
		cin >> v;
		cin.get();
		if(v<=Asize)
		if(!isdeletedvertex(v))
			return A[v]->length;
		return 0;
	}

	int degree(int v)
	{
		return (indegree(v) + outdegree(v));
	}

	int degree()
	{
		int v;
		cout << "ENTER NODE NUMBER ::\n";
		cin >> v;
		cin.get();
		return (indegree(v) + outdegree(v));
	}

	char * adjacentvertices(int n)
	{
		if (isdeletedvertex(n))
			return NULL;


		int temp;
		int size = outdegree(n);
		char * res = new char[size];
		int index = 0;

		node* ptr;
		ptr = A[n]->head;
		for (; ptr; ptr = ptr->next)
		{
			temp = ptr->data;
			res[index] = p[temp];
			index++;
		}
		return res;
	}
	char * adjacentvertices()
	{
		int n;
		cout << "ENTER NODE NUMBER ::\n";
		cin >> n;
		cin.get();

		if (isdeletedvertex(n))
			return NULL;


		int temp;
		int size = outdegree(n);
		char * res = new char[size];
		int index = 0;

		node* ptr;
		ptr = A[n]->head;
		for (; ptr; ptr = ptr->next)
		{
			temp = ptr->data;
			res[index] = p[temp];
			index++;
		}
		return res;
	}

	string* incomingedges(int n)
	{
		string* res;
		if (isdeletedvertex(n))
			return NULL;
		else
		{
			char temp[3];
			temp[2] = 0;
			temp[1] = p[n];
			int indeg = indegree(n);
			if (indeg == 0)
				return NULL;
			res = new string[indeg];
			int index = 0;
			for (int i = 1; i <= Asize; i++)
			{
				if (i != n)
					if (A[i] && A[i]->ispresentdata(n, A[i]->head))
					{
						temp[0] = p[i];
						res[index] = temp;
						index++;
					}
			}
			return res;
		}
	}
	string* incomingedges()
	{
		int n;
		cout << "ENTER NODE NUMBER ::\n";
		cin >> n;
		cin.get();

		string* res;
		if (isdeletedvertex(n))
			return NULL;
		else
		{
			char temp[3];
			temp[2] = 0;
			temp[1] = p[n];
			int indeg = indegree(n);
			if (indeg == 0)
				return NULL;
			res = new string[indeg];
			int index = 0;
			for (int i = 1; i <= Asize; i++)
			{
				if (i != n)
					if (A[i] && A[i]->ispresentdata(n, A[i]->head))
					{
						temp[0] = p[i];
						res[index] = temp;
						index++;
					}
			}
			return res;
		}
	}

	string* outgoingedges(int n)
	{
		string * res;
		if (isdeletedvertex(n))
			return NULL;
		int outdeg = outdegree(n);
		char* s = adjacentvertices(n);
		if (s != NULL)
		{
			res = new string[outdeg];
			char temp[3];
			temp[0] = p[n];
			temp[2] = 0;

			for (int i = 0; i < outdeg; i++)
			{
				temp[1] = s[i];
				res[i] = temp;
			}
			delete[]s;
			return res;
		}
		return NULL;
	}

	string* outgoingedges()
	{
		int n;
		cout << "ENTER NODE NUMBER ::\n";
		cin >> n;
		cin.get();

		string * res;
		if (isdeletedvertex(n))
			return NULL;
		int outdeg = outdegree(n);
		char* s = adjacentvertices(n);
		if (s != NULL)
		{
			res = new string[outdeg];
			char temp[3];
			temp[0] = p[n];
			temp[2] = 0;

			for (int i = 0; i < outdeg; i++)
			{
				temp[1] = s[i];
				res[i] = temp;
			}
			delete[]s;
			return res;
		}
		return NULL;
		if (isdeletedvertex(n))
			return NULL;
			outdeg = outdegree(n);
			s = adjacentvertices(n);
		if (s != NULL)
		{
			res = new string[outdeg];
			char temp[3];
			temp[0] = p[n];
			temp[2] = 0;

			for (int i = 0; i < outdeg; i++)
			{
				temp[1] = s[i];
				res[i] = temp;
			}
			delete[]s;
			return res;
		}
		return NULL;
	}

	string* incidentedges(int n)
	{
		string* A;
		string* B = incomingedges(n);
		string* C = outgoingedges(n);

		int indeg = indegree(n);
		int outdeg = outdegree(n);
		int deg = degree(n);

		if (deg == 0)
			return NULL;
		else
		{
			int index = 0;
			A = new string[deg];
			for (int i = 0; i < indeg; i++)
			{
				A[index] = B[i];
				index++;
			}
			for (int j = 0; j < outdeg; j++)
			{
				A[index] = C[j];
				index++;
				
			}
			delete[] B;
			delete[] C;

			return A;
		}


	}
	string* incidentedges()
	{
		int n;
		cout << "ENTER NODE NUMBER ::\n";
		cin >> n;
		cin.get();

		string* A;
		string* B = incomingedges(n);
		string* C = outgoingedges(n);

		int indeg = indegree(n);
		int outdeg = outdegree(n);
		int deg = degree(n);

		if (deg == 0)
			return NULL;
		else
		{
			int index = 0;
			A = new string[deg];
			for (int i = 0; i < indeg; i++)
			{
				A[index] = B[i];
				index++;
			}
			for (int j = 0; j < outdeg; j++)
			{
				A[index] = C[j];
				index++;
			}
			delete[] B;
			delete[] C;

			return A;
		}
	}
	int indexgiver(char t)
	{
		for (int i = 1; i <= Asize; i++)
		{
			if (p[i] == t)
				return i;
		}
	}
	void BFS(int *visited)
	{
			int n;
			cout << "ENTER ROOT NODE::\n";
			cin >> n;
			cin.get();

			int index; int outd;
			int u; char* q;
			list<int> M[100];
			list<int> ::iterator it;
			list<int> ::iterator temp;

			if (A[n])
			{

				int i = 0;
				it = M[i].end();
				M[i].insert(it, n);
				visited[n] = 1;

				while (M[i].empty() != 1)
				{
					for (temp = M[i].begin(); temp != M[i].end(); temp++)
					{
						u = *temp;
						q = adjacentvertices(u);
						outd = outdegree(u);
						if (q != NULL)
						{
							for (int j = 0; j < outd; j++)
							{
								index = indexgiver(q[j]);
								if (visited[index] != 1)
								{
									visited[index] = 1;
									it = M[i + 1].end();
									M[i + 1].insert(it, index);
								}
							}
							delete[] q;
						}
					}
					i++;
				}
				i = 0;
				while (M[i].empty() != 1)
				{
					for (it = M[i].begin(); it != M[i].end(); it++)
						cout << p[*it] << " ";
					i++;
				}
			}
			return;
	}

	void BFS(int n,int *visited)
	{
		int index; int outd;
		 int u; char* q;
		 list<int> M[100];
		 list<int> ::iterator it;
		 list<int> ::iterator temp;
		if (A[n])
		{

			int i = 0;
			it = M[i].end();
			M[i].insert(it, n);
			visited[n] = 1;

			while (M[i].empty() != 1)
			{
				for (temp = M[i].begin(); temp != M[i].end(); temp++)
				{
					u = *temp;
					q = adjacentvertices(u);
					outd = outdegree(u);
					if (q != NULL)
					{
						for (int j = 0; j < outd; j++)
						{
							index = indexgiver(q[j]);
							if (visited[index] != 1)
							{
								visited[index] = 1;
								it = M[i + 1].end();
								M[i + 1].insert(it, index);
							}
						}
						delete[] q;
					}
				}
				i++;
			}
			i = 0;
			while (M[i].empty() != 1)
			{
				for (it = M[i].begin(); it != M[i].end(); it++)
					cout << p[*it] << " ";
				i++;
			}
		}
		return;
	}

	void DFS(int n, int* visited)
	{
		if (A[n])
		{
			char *q = adjacentvertices(n); int w;
			int outd = outdegree(n);
			if (visited[n]!=1)
			{
				visited[n] = 1;
				cout << p[n] << " ";
				if (q)
				{
					for (int i = 0; i < outd; i++)
					{

						w = indexgiver(q[i]);
						if (visited[w] != 1)
						{
							DFS(w,visited);
						}
					}
					delete[]q;
				}
			}
		}
	}

	void DFS(int* visited)
	{
		int n;
		cout << "ENTER ROOT NODE::\n";
		cin >> n;
		cin.get();
		if (A[n])
		{
			char *q = adjacentvertices(n); int w;
			int outd = outdegree(n);
			if (visited[n] != 1)
			{
				visited[n] = 1;
				cout << p[n] << " ";
				if (q)
				{
					for (int i = 0; i < outd; i++)
					{

						w = indexgiver(q[i]);
						if (visited[w] != 1)
						{
							DFS(w, visited);
						}
					}
					delete[]q;
				}
			}
		}
	}

	graph copygraph()
	{
		graph f(Asize); int data, weight;
		node* ptr;
		for (int i = 0; i <= Asize; i++)
		{
			if(isdeletedvertex(i))
			{
				f.A[i] = NULL;

			}
			else
			{
				node* ptr = A[i]->head;
				for (; ptr; ptr = ptr->next)
				{
					data = ptr->data;
					weight = ptr->weight;
					f.A[i]->insertnode(data, weight);
				}
			}
		}
		return f;
	}

	void copygraph(graph * f)
	{
	     int data, weight;
		node* ptr;
		for (int i = 0; i <= Asize; i++)
		{
			if(isdeletedvertex(i))
			{
				f->A[i] = NULL;

			}
			else
			{
				node* ptr = A[i]->head;
				for (; ptr; ptr = ptr->next)
				{
					data = ptr->data;
					weight = ptr->weight;
					f->A[i]->insertnode(data, weight);
				}
			}
		}
	}
	int ispresentdirectedcycle()
	{
		int ispres = 0;
		graph t=transitiveclosure();
		for (int i = 1; i <= Asize && !ispres; i++)
		{
			for (int j = 1; j <= Asize && !ispres; j++)
			{
				if (!isdeletedvertex(i) && !isdeletedvertex(j))
				{
					if (i != j)
					{
						if (t.ispresentedge(i, j) && t.ispresentedge(j, i))
							ispres = 1;

					}

				}


			}

		}
			return ispres;

	}

	int** equivalentundirectedgraph()
	{
		graph c = equivalentundirectedgraph(*this);

		int **res; node *ptr;
		res = new int*[Asize + 1];
		for (int i = 0; i <= Asize; i++)
		{
			res[i] = new int[Asize + 1];
		}

		// res is the adjacency matrix for cost
		for (int i = 0; i <= Asize; i++)
		{
			for (int j = 0; j <= Asize; j++)
			{
				res[i][j] = 999;
			}

		}
		for (int i = 0; i <= c.Asize; i++)
		{
			if (!c.isdeletedvertex(i))
			{
				ptr = c.A[i]->head;
				for (; ptr; ptr = ptr->next)
				{
					res[i][ptr->data] = ptr->weight;
				}
			}
		}
		// res now correctly stores the costs of every edge (i,j) in c
		return res;
	}

	void kruskal()
	{

		// find Kruskals MST For graph c store it in mst and return
		int **res=equivalentundirectedgraph();

		int i, j, a,b,u,w;
		int min = 0;
		int mincost = 0;
		int *parent = new int[Asize+1];
		int numedg = 1;
		for (int i = 0; i <= Asize; i++)
		{
			parent[i] = 0;
		}
		cout << "THE EDGES OF MINIMUM COST SPANNING TREE ARE\n";
		while (numedg < v)
		{
			for (i = 1, min = 999; i <= v; i++)
			{
				for (j = 1; j <= v; j++)
				{
					if (res[i][j] < min)
					{
						min = res[i][j];
						a = u = i;
						b =  w = j;
					}
				}
			}
			u = find(u,parent);
			w = find(w,parent);
			if (unionfind(u, w,parent))
			{
				cout<< numedg++<<" edge ("<< p[a]<<" , "<< p[b]<<") = "<<min<<endl;
				mincost += min;
			}
			res[a][b] = res[b][a] = 999;


		}

		cout << "MINIMUM COST ::" << mincost << endl;

		for (int i = 0; i <= Asize; i++)
		{
			delete[] res[i];
		}
		delete[] res;
		delete[] parent;

	}

	int find(int i,int *parent)
	{
		while (parent[i])
			i = parent[i];
		return i;
	}
	int unionfind(int i, int j,int *parent)
	{
		if (i != j)
		{
			parent[j] = i;
			return 1;
		}

		return 0;
	}


		void showgraph()
		{
			char* q = p; node* ptr; int n;
			cout << "THE VERTICES OF THE GRAPH ARE :: \n";
			for (int i = 0; i <= Asize; i++)
				if (q[i] != 0)
					cout << q[i] << "  ";
			cout << endl;
			for (int i = 1; i <= Asize; i++)
			{
				if (!isdeletedvertex(i))
				{
					ptr = A[i]->head;
					for (; ptr; ptr = ptr->next)
					{
						n = ptr->data;
						cout << "GRAPH CONTAINS AN EDGE FROM " << p[i] << " TO  " << p[n] << " WEIGHING  " << ptr->weight << endl;
					}
				}
			}
		}

		int isadjacentvertex(int src, int dest)
		{
			if (!isdeletedvertex(src) && !isdeletedvertex(dest))
			{
				int isadjc = 0; int index;
				char *q = adjacentvertices(src);
				int outd = outdegree(src);
				if (q)
				{
					for (int i = 0; i < outd; i++)
					{
						index = indexgiver(q[i]);
						if (index == dest)
						{
							isadjc = 1;
							break;
						}
					}
					delete[] q;
					return isadjc;
				}
			}
			return 0;
		}

		graph transitiveclosure()
		{
			graph t = copygraph();
			for (int k = 1; k <= Asize; k++)
			{
				for (int i = 1; i <= Asize; i++)
				{
					if (i != k)
					{
						for (int j = 1; j <= Asize; j++)
						{
							if (j != i && j != k)
							{
								if (t.ispresentedge(i, k) && t.ispresentedge(k, j))
								{
									if (!t.ispresentedge(i, j))
										t.insertedge(i, j, 0);
								}
							}
						}
					}
				}

			}
			return t;
		}

		int ispresenttransitivepath(int m, int n)
		{

			if (!isdeletedvertex(m) && !isdeletedvertex(n))
			{
				int ispres = 0;
				if (ispresentedge(m, n))
				{
					return 1;
				}

				else
				{

					graph t = transitiveclosure();
					if (t.ispresentedge(m, n))
						ispres = 1;
					return ispres;
				}
			}
		}

		int ispresentDFSpath(int n,int m,int *visited)
		{
			if (A[n])
			{
				char *q = adjacentvertices(n); int w;
				int outd = outdegree(n);
				if (visited[n] != 1)
				{
					visited[n] = 1;
					if (q)
					{
						for (int i = 0; i < outd; i++)
						{

							w = indexgiver(q[i]);
							if (visited[w] != 1)
							{
								ispresentDFSpath(w,m, visited);
							}
						}
						delete[]q;
					}
				}
			}

			if (visited[m] == 1)
				return 1;
			else
				return  0;

		}
		graph equivalentundirectedgraph(graph p)
		{
			graph c(Asize);
			 copygraph(&c);
			struct node* ptr;
			for (int i = 0; i <= c.Asize; i++)
			{
				if (!c.isdeletedvertex(i))
				{
					ptr = c.A[i]->head;
					for (; ptr; ptr = ptr->next)
					{
						if (!c.ispresentedge(ptr->data, i))
						{
							c.insertedge(ptr->data, i, ptr->weight);
						}
					}
				}
			}
			return c;
		}

		void equivalentundirectedgraph(graph* c,graph p)
		{
		    struct node* ptr;
			for (int i = 0; i <= c->Asize; i++)
			{
				if (!c->isdeletedvertex(i))
				{
					ptr = c->A[i]->head;
					for (; ptr; ptr = ptr->next)
					{
						if (!c->ispresentedge(ptr->data, i))
						{
							c->insertedge(ptr->data, i, ptr->weight);
						}
					}
				}
			}

		}

		void heapinsert(list<int> &l1,list<int> &l2,list<int> &l3,list<int> &l4,int u,int edge[2],int dkey)
		{
			list <int> ::iterator it;
			list<int> ::iterator it2;
			list<int> ::iterator it3;
			list<int> ::iterator it4;

			it = l1.begin();
			it2 = l2.begin();
			it3 = l3.begin();
			it4 = l4.begin();
			if (l1.empty())
			{
				l1.insert(it, u);
				l2.insert(it2, edge[0]);
				l3.insert(it3, edge[1]);
				l4.insert(it4, dkey);
			}
			else
			{
				while (it4!=l4.end() && (*it4) < dkey)
				{
					it++;
					it2++;
					it3++;
					it4++;


				}
				l1.insert(it, u);
				l2.insert(it2, edge[0]);
				l3.insert(it3, edge[1]);
				l4.insert(it4, dkey);

			}

		}
		void heapremovemin(int *z, list<int> &l1, list<int> &l2, list<int> &l3, list<int> &l4)
		{
			list <int> ::iterator it;
			list<int> ::iterator it2;
			list<int> ::iterator it3;
			list<int> ::iterator it4;
			if (!l1.empty())
			{
				it = l1.begin();
				it2 = l2.begin();
				it3 = l3.begin();
				it4 = l4.begin();
				z[0] = *it;
				z[1] = *it2;
				z[2] = *it3;
				l1.erase(it);
				l2.erase(it2);
				l3.erase(it3);
				l4.erase(it4);
			}
			else
			{
				z[0] = 0;
				z[1] = 0;
				z[2] = 0;

			}
		}
		void heapremove(list<int> &l1, list<int> &l2, list<int> &l3, list<int> &l4, int n)
		{
			list <int> ::iterator it;
			list<int> ::iterator it2;
			list<int> ::iterator it3;
			list<int> ::iterator it4;

			it = l1.begin();
			it2 = l2.begin();
			it3 = l3.begin();
			it4 = l4.begin();

			for (; it != l1.end() && *it != n; )
			{
				it++;
				it2++;
				it3++;
				it4++;
			}
			l1.erase(it);
			l2.erase(it2);
			l3.erase(it3);
			l4.erase(it4);

		}
		int ispresinheap(list<int> l1, int n)
		{
			list <int> ::iterator it;

			for (it = l1.begin(); it != l1.end(); it++)
			{
				if (*it == n)
					return 1;
			}
			return 0;

		}
		void primalgorithm(int n)
		{
			int edge[2] = { 0,0 }; int index;

			int z[3] = { 0,0,0 };
									// stores return values of heapremovemin
									// z[0]---> vertex
									//	z[1] ,z[2] ---> edge vertices


			graph c = equivalentundirectedgraph(*this);		// stores undirected graph
			int** res = equivalentundirectedgraph();			// stores adjacency weight matrix
			int* vertexweight = new int[c.Asize+1];
			for (int i = 0; i <= c.Asize; i++)
				vertexweight[i] = INT_MAX;		// other vertex weight= infinity
			vertexweight[n] = 0;			// root weight=0

			graph mst(c.Asize);

			char *q; int outd;
			for (int i = 0; i <= c.Asize; i++)
			{
				if (isdeletedvertex(i))
				{
					mst.A[i] = NULL;
				}
			}


			list<int> l1;				// l1 ---> source vertex
			list<int> l2;					// l2 ---> edge vertex

			list<int> l3;					// l3 ---> edge vertex
										// (l2 ,l3 ) ---> edge
			list<int> l4;					// l4 --->vertex weight
			for (int i = 0; i <= c.Asize; i++)
			{
				if (!c.isdeletedvertex(i))
					heapinsert(l1, l2, l3, l4, i, edge, vertexweight[i]);

			}
			while (l1.empty() != 1)
			{
				heapremovemin(z, l1, l2, l3, l4);
				mst.insertedge(z[1], z[2],res[z[1]][z[2]]);
				mst.insertedge(z[2], z[1], res[z[2]][z[1]]);
				q = c.adjacentvertices(z[0]);
				outd = c.outdegree(z[0]);

				for (int i = 0; i <outd; i++)
				{
					index = indexgiver(q[i]);
					if (ispresinheap(l1,index))
					{
						if (res[z[0]][index] < vertexweight[index])
						{
							vertexweight[index] = res[z[0]][index];
							heapremove(l1, l2, l3, l4, index);
							edge[0] = z[0];
							edge[1] = index;
							heapinsert(l1, l2, l3, l4, index, edge, vertexweight[index]);


						}
					}
				}


			}
			int x = 1;
			res = mst.equivalentundirectedgraph();
			for (int i = 0; i <= mst.Asize; i++)
			{
				for (int j = i; j <= mst.Asize; j++)
				{
					if (res[i][j] != 999)
					{
						cout << "EDGE " << x << " :: " << "(" << c.p[i] << ", " << c.p[j] << ")    = " << res[i][j]<<endl;
						x++;
					}
				}
			}
		}


		int ismorethan1(set<int> *S,int count)
		{
			int c = 0;
			for (int i = 0; i <= Asize; i++)
			{
				if (!S[i].empty())
					c++;
			}
			if (c <= 1)
				return 1;
			else return 0;
		}
		void cheapest_edge_connecting(graph c,graph mst,set<int> S, int *RES)
		{
			if (!S.empty())
			{
				char *q; int index; int outdeg;
				int **carr = c.equivalentundirectedgraph();
				RES[0] = RES[1] = RES[2] = 999;
				int tempmin[3] = { 999,999,999 };

				set<int> ::iterator it = S.begin();
				for (; it != S.end(); it++)
				{
					tempmin[0] = tempmin[1] = tempmin[2] = 999;
					q = c.adjacentvertices(*it);
					outdeg = c.outdegree(*it);

					for (int i = 0; i < outdeg; i++)
					{
						index = indexgiver(q[i]);
						if (!mst.ispresentedge(index, *it))
						{
							if (carr[index][*it] < tempmin[2])
							{
								tempmin[0] = index;
								tempmin[1] = *it;
								tempmin[2] = carr[index][*it];

							}
						}
						if (tempmin[2] < RES[2])
						{
							RES[0] = tempmin[0];
							RES[1] = tempmin[1];
							RES[2] = tempmin[2];
						}
					}
				}
			}
		}
		int isinset(set<int> S, int n)
		{
			set<int> ::iterator it;
			for (it = S.begin(); it != S.end(); it++)
			{
				if (*it == n)
					return 1;
			}
			return 0;

		}
		void makeempty(set<int> *S)
		{
			int a;
			set<int> ::iterator it;
			set<int> ::iterator it2;
			for (int i = 0; i <= Asize; i++)
			{
				if (!S[i].empty())
				{
					for (it = S[i].begin(); it != S[i].end(); it++)
					{
						a = *it;
						for (int j = 0; j <= Asize; j++)
						{
							if (j != i)
							{
								if (!S[j].empty())
								{
									if (isinset(S[j], a))
									{
										for (it2 = S[j].begin(); it2 != S[j].end(); it2++)
										{
											S[i].insert(*it2);

										}
										while (!S[j].empty())
										{
											it2 = S[j].begin();
											S[j].erase(*it2);
										}
									}
								}

							}

						}


					}
				}
			}

		}
		void BARUVKASALGORITHM()
		{
			graph c = equivalentundirectedgraph(*this);
			int** res = equivalentundirectedgraph();

			graph mst(c.Asize);
			for (int i = 0; i <= c.Asize; i++)
			{
				if (isdeletedvertex(i))
				{
					mst.A[i] = NULL;
				}
			}

			int **minconnector;			// mincon[0]--> src , minc[1]--> dest , minc[2] --> weight of min connecting edge
			minconnector = new int*[Asize+1];
			for (int i = 0; i <= c.Asize; i++)
			{
					minconnector[i] = new int[3];
			}
			set<int> *S;
			S = new set<int>[c.Asize+1];
			int count = 0;
			for (int i = 0; i <= c.Asize; i++)
			{
				if (!c.isdeletedvertex(i))
				{
					S[i].insert(i);
				}
				else
				{
					count++;
				}
			}
			while (!ismorethan1(S,count))
			{
				for (int i = 0; i <= c.Asize; i++)
				{
					if (!isdeletedvertex(i) && !S[i].empty())
					{
						cheapest_edge_connecting(c,mst,S[i], minconnector[i]);
					}
				}
				for (int i = 0; i <= c.Asize; i++)
				{
					if (!S[i].empty())
					{
						if (!mst.ispresentedge(minconnector[i][0], minconnector[i][1]))
						{
							mst.insertedge(minconnector[i][0], minconnector[i][1], minconnector[i][2]);
							S[i].insert(minconnector[i][0]);
							S[i].insert(minconnector[i][1]);
							mst.insertedge(minconnector[i][1], minconnector[i][0], minconnector[i][2]);

						}
					}
				}
					makeempty(S);

			}
				res = mst.equivalentundirectedgraph();


				int x = 1;
				for (int i = 0; i <= mst.Asize; i++)
				{
					for (int j = i; j <= mst.Asize; j++)
					{
						if (res[i][j] != 999)
						{
							cout << "EDGE " << x << " :: " << "(" << c.p[i] << ", " << c.p[j] << ")    = " << res[i][j] << endl;
							x++;
						}
					}
				}

		}


		void heapinsert(list<int> &l1,list<int> &l2,int i,int dist)
		{
			list <int> ::iterator it;
			list<int> ::iterator it2;
			it = l1.begin();
			it2 = l2.begin();
			if (l1.empty())
			{
				l1.insert(it, dist);
				l2.insert(it2, i);
			}
			else
			{
				while (it != l1.end() && (*it) < dist)
				{
					it++;
					it2++;


				}
				l1.insert(it, dist);
				l2.insert(it2, i);
			}


		}
		int heapremovemin(int *z,list<int> &l1,list<int> &l2)
		{
			list <int> ::iterator it;
			list<int>::iterator it2;

			if (!l1.empty())
			{
				it = l1.begin();
				it2 = l2.begin();
				z[0] = *it;
				z[1] = *it2;
				l1.erase(it);
				l2.erase(it2);

			}
			return 0;

		}
		void heapremove(list<int> &l1,list<int> &l2,int n)
		{
			list <int> ::iterator it;
			list<int>::iterator it2;
			it = l1.begin();
			it2 = l2.begin();
			for (; it != l1.end() && *it != n; )
			{
				it++;
				it2++;
			}
			l1.erase(it);
			l2.erase(it2);
			return;

		}
		void Dijkstras(int src)
		{
			if (!isdeletedvertex(src))
			{
				int ** res = equivalentundirectedgraph();
				graph c = equivalentundirectedgraph(*this);
				int *dist;
				dist = new int[c.Asize + 1];
				for (int i = 0; i <= c.Asize; i++)
				{
					if (c.isdeletedvertex(i))
					{
						dist[i] = 999;

					}
					else
						dist[i] = INT_MAX;
				}
				dist[src] = 0;
				int z[2];
				list<int> l1;	// stores heap with distance of vertex with keys
				list<int> l2;	// stores the corresponding vertex
				for (int i = 0; i <= c.Asize; i++)
				{
					if (!c.isdeletedvertex(i))
						heapinsert(l1, l2, i, dist[i]);

				}
				char *q;
				int index;
				int size;
				int alt;

				while (!l1.empty())
				{
					heapremovemin(z, l1, l2);
					q = c.adjacentvertices(z[1]);
					size = c.outdegree(z[1]);
					for (int i = size-1; i >= 0; i--)
					{
							index = indexgiver(q[i]);
						if (ispresinheap(l2, index))
						{
							alt = dist[z[1]] + res[z[1]][index];
							if (alt < dist[index])
							{
								dist[index] = alt;
								heapremove(l2, l1, index);
								heapinsert(l1, l2, index, dist[index]);

							}
						}
					}

				}

				for (int i = 0; i <= c.Asize; i++)
				{
					if (!c.isdeletedvertex(i))
					{
						cout << "SHORTEST PATH FROM SOURCE " << p[src] << " TO DESTINATION " << p[i] << " COSTS " << dist[i]<<endl;
					}
				}


			}
			else;

		}

		int edgeweight(int u, int v)
		{
			if (A[u] == NULL)
				return 0;
			else if (!ispresentedge(u, v))
				return 0;
			else
			{
				node* ptr = A[u]->head;

				for (; ptr->data != v; ptr = ptr->next);
				return ptr->weight;
			}
		}
		void Bellmanford(int src)
		{
			int *dist = new int[Asize+1] ;
			for (int i = 0; i <= Asize; i++)
			{
				if (isdeletedvertex(i))
					dist[i] = 999;
				else
					dist[i] = INT_MAX;

			}
			dist[src] = 0;
			char *q;
			int index;
			int size;
			int tempdist;
			for(int i=1;i<=v;i++)
			for (int i = 0; i <= Asize; i++)
			{
				if (!isdeletedvertex(i))
				{
					q = adjacentvertices(i);
					size = outdegree(i);
					for (int j = 0; j < size; j++)
					{
						index = indexgiver(q[j]);
						tempdist = dist[i] + edgeweight(i, index);
						if (tempdist < dist[index])
							dist[index] = tempdist;
					}
				}
			}
			for (int i = 0; i <= Asize; i++)
			{
				if (!isdeletedvertex(i))
				{
					cout << "SHORTEST PATH FROM SOURCE " << p[src] << " TO DESTINATION " << p[i] << " COSTS " << dist[i] << endl;
				}
			}
		}

		void floydwarshallallpairshortestpath()
		{
			int **res = equivalentundirectedgraph();
			int **dist = new int*[Asize + 1];
			for (int j = 0; j <= Asize; j++)
				dist[j] = new int[Asize + 1];
			for (int i = 0; i <= Asize; i++)
			{
				for(int j=0;j<=Asize;j++)
					if (!ispresentedge(i, j))
					{
						res[i][j] = 999;
					}
			}

			for (int i = 0; i <= Asize; i++)
				for (int j = 0; j <= Asize; j++)
					if (i != j)
						dist[i][j] = res[i][j];
					else
						dist[i][j] = 0;


			for (int k = 0; k <= Asize; k++)
			{
				// Pick all vertices as source one by one
				for (int i = 0; i <=Asize; i++)
				{
					// Pick all vertices as destination for the
					// above picked source
					for (int j = 0; j <=Asize; j++)
					{
						// If vertex k is on the shortest path from
						// i to j, then update the value of dist[i][j]
						if (dist[i][k] + dist[k][j] < dist[i][j])
							dist[i][j] = dist[i][k] + dist[k][j];
					}
				}
			}
			for (int i = 0; i <= Asize; i++)
			{
				for (int j = 0; j <= Asize; j++)
				{
					if (!isdeletedvertex(i) && !isdeletedvertex(j))
						if (i == j || ispresenttransitivepath(i, j))
							cout << "SHORTEST PATH FROM " << p[i] << " TO " << p[j] << " COSTS " << dist[i][j] << endl;
				}
			}
		}

		int isconnectedgraph()
		{
			for (int i = 1; i <= Asize; i++)
			{
				for (int j = 1; j <= Asize; j++)
					if (i != j && !isdeletedvertex(i) && !isdeletedvertex(j))
						if (!ispresenttransitivepath(i, j))
						{
							return 0;
						}
			}
			return 1;
		}


		list<int> topologicalsort()
		{
		    list<int> res;
		    list<int>:: iterator it;
		    stack<int> s;
		    int *incounter=new int[Asize+1];
		    incounter[0]=0;
		    for(int i=1;i<=Asize;i++)
            {
                if(!isdeletedvertex(i))
                {
                    incounter[i]=indegree(i);
                    if(indegree(i)==0)
                    {
                        s.push(i);
                    }

                }

            }
            char *q;
            int index;
            int size;
            int i=1;
            while(!s.empty())
            {
                int u=s.top();
                s.pop();
                it=res.end();
                res.insert(it,u);
                i=i+1;
                q=adjacentvertices(u);
                size=outdegree(u);
                for(int j=0;j<size;j++)
                {
                    index=indexgiver(q[j]);
                    incounter[index]-=1;
                    if(incounter[index]==0)
                        s.push(index);
                }

            }
            if(i>v)
            {
                for(it=res.begin();it!=res.end();it++)
                    cout<<p[*it]<<"  ";
                cout<<endl;
                return res;
            }
            else
            {
                list<int> nonepresent;
                return nonepresent;
            }
		}



		void DAGshortestpath(int src)
		{
			cout << "SINGLE SOURCE SHORTEST PATH IN DAG\n";
			list<int> l = topologicalsort();
			if(l.empty())
			{
			    cout<<"GRAPH IS NOT A DAG\n";
                return;
			}
			list<int>::iterator it = l.begin();
			int *dist = new int[Asize + 1];
			for (int i = 0; i <= Asize; i++)
				dist[i] = INT_MAX;
			dist[src] = 0;
			int u, v;
			char *q;
			int index;
			int size;
			while (!l.empty())
			{
				it = l.begin();
				u = *it;

				l.erase(it);
				q = adjacentvertices(u);
				size = outdegree(u);
				for (int i = 0; i < size; i++)
				{
					v = indexgiver(q[i]);
					if (dist[v] > dist[u] + edgeweight(u, v))
						dist[v] = dist[u] + edgeweight(u, v);
				}
			}
			for (int i = 0; i <= Asize; i++)
			{
				if (!isdeletedvertex(i) && ispresenttransitivepath(src, i))
					cout << "SHORTEST PATH FROM " << src << " TO " << i << " COSTS :: " << dist[i] << endl;
			}
		}


        void DFSpath(list<int> &l,int *visited,int n)
        {

		if (A[n])
		{
		    list<int> :: iterator it;
			char *q = adjacentvertices(n); int w;
			int outd = outdegree(n);
			if (visited[n]!=1)
			{
				visited[n] = 1;
				it=l.end();
				l.insert(it,n);
				if (q)
				{
					for (int i = 0; i < outd; i++)
					{

						w = indexgiver(q[i]);
						if (visited[w] != 1)
						{
							DFSpath(l,visited,w);
						}
					}
					delete[]q;
				}
			}
		}

        }


        void removeelement(list<int> &l,int n)
        {
            list<int>:: iterator it;
            for(it=l.begin();it!=l.end();it++)
            {
                if(*it==n)
                {
                    break;

                }

            }
            l.erase(it);
            return;
        }
        int connectedcomponents(int* visited)
        {
            list<int> remaining;
            list<int> :: iterator it;
            list<int> :: iterator it2;
            list<int> mycomponents;
            for(int i=1;i<=Asize;i++)
            {
                if(!isdeletedvertex(i))
                {
                it=remaining.end();
                remaining.insert(it,i);
                }
            }
            int component=0;
            while(!remaining.empty())
            {
                it=remaining.begin();
                int src=*it;

                for(int i=1;i<=Asize;i++)
                    visited[i]=0;
                DFSpath(mycomponents,visited,src);
                for(it2=mycomponents.begin();it2!=mycomponents.end();it2++)
                {
                    cout<<p[*it2]<<"  ";
                    int t=*it2;
                    removeelement(remaining,t);

                }
                cout<<endl;
                component++;
                while(!mycomponents.empty())
                {
                    it2=mycomponents.begin();
                    mycomponents.erase(it2);

                }
            }
            cout<<component<<endl;
            return component;
        }

		void performer()
		{
			int option = -1;
			cout << "0. EXIT\n";
			cout << "1. ADD AN EDGE TO THE GRAPH\n";
			cout << "2. ADD A VERTEX TO GRAPH\n";
			cout << "3. STORE ADJACENT VERTICES TO A VERTEX\n";
			cout << "4. STORE INCINDENT EDGES ON A VERTEX\n";
			cout << "5. STORE INCOMING EDGES TO A VERTEX\n";
			cout << "6. STORE OUTGOING EDGE FROM A VERTEX\n";
			cout << "7. SHOW INCIDENT EDGE ON A VERTEX\n";
			cout << "8. SHOW INCOMING EDGE TO A VERTEX\n";
			cout << "9. SHOW OUTGOING EDGE OF A VERTEX\n";
			cout << "10. SHOW IDEGREE OF A VERTEX\n";
			cout << "11. SHOW OUTDEGREE OF A VERTEX\n";
			cout << "12. SHOW DEGREE OF A VERTEX\n";
			cout << "13.STORE VERTICES OF THE GRAPH\n";
			cout << "14. SHOW THE GRAPH\n";
			cout << "15. DELETE AN EDGE FROM THE GRAPH\n";
			cout << "16. DELETE A VERTEX\n";
			cout << "17. PERFORM BFS\n";
			cout << "18. PERFORM DFS\n";
			cout << "19. FIND THE TRANSITIVE CLOSURE FLOYD WARSHALL\n";
			cout << "20. MINIMUM SPANNING TREE KRUSKAL ON AN EQUIVALENT UNDIRECTED GRAPH\n";
			cout << "21. MINIMUM SPANNING TREE PRIM\'S ALGORITHM ON EQUiVALENT UNDIRECTED GRAPH\n";
			cout << "22. MINIMUM SPANNING TREE BARUVKA\'S ALGORITHM ON EQUIVALENT UNDIRECTED GRAPH\n";
			cout << "23. SHORTEST PATH- BELLMAN FORD\n";
			cout << "24. SHORTEST PATH- DIJKSTRA\'S ALGORITHM ON EQUIVALENT UNDIRECTED GRAPH\n";
			cout << "25. CHECK IF CYCLIC\n";
			cout << "26. ALL PAIRS SHORTEST PATH - FLOYD WARSHALL\n";
			cout << "27. CHECK IF CONNECTED GRAPH\n";
			cout << "28. CHECK IF A DIRECTED CYCLE EXISTS\n";
			cout << "29. PERFORM TOGOLOGICAL SORT ON DAG\n";
			cout << "30. SHORTEST PATH DAG ALGORITHM\n";
			cout << "31. SHOW THE CONNECTED COMPONENTS IN A GRAPH\n";
			cout << "32. COUNT THE NUMBER OF CONNECTED COMPONENTS AND SHOW THEM\n";
			cout << "33. SHOW THE NUMBER OF VERTICES OF THE GRAPH\n";
			cout << "34. SHOW THE NUMBER OF EDGES\n";
			cout << "35. CHECK IF THERE IS A TRANSITIVE PATH BETWEEN TWO VERTICES\n";
			int src; int n; int dest; string* s; int size; int *visited;
			char *q; node *ptr; graph t = *this; int index;int **res;
			while (option)
			{
				cin >> option;
				cin.get();

				switch (option)
				{
				case 0:
					break;
				case 1:
					insertedge();
					break;
				case 2:
					insertvertex();
					break;
				case 3:
					cout << "ENTER THE NODE NUMBER\n";
					cin >> n;
					cin.get();
					size = outdegree(n);
					q = adjacentvertices(n);
					if (size)
					{
						for (int i = 0; i < size; i++)
							cout << q[i] << "  ";
						cout << endl;
					}
					delete[] q;
					break;

				case 4:case 7:
					cout << "ENTER THE NODE NUMBER\n";
					cin >> n;
					cin.get();
					size = degree(n);
					s = incidentedges(n);

					if (size)
					{
						for (int i = 0; i < size; i++)
							cout << s[i] << "  ";
						cout << endl;
					}
					delete[] s;
					break;
				case 5:case 8:
					cout << "ENTER THE NODE NUMBER\n";
					cin >> n;
					cin.get();
					size = indegree(n);
					s = incomingedges(n);
					if (size)
					{
						for (int i = 0; i < size; i++)
							cout << s[i] << "  ";
						cout << endl;
					}
					delete[] s;
					break;
				case 6:case 9:
					cout << "ENTER THE NODE NUMBER\n";
					cin >> n;
					cin.get();
					size = outdegree(n);
					s = outgoingedges(n);

					if (size)
					{
						for (int i = 0; i < size; i++)
							cout << s[i] << "  ";
						cout << endl;
					}
					delete[] s;
					break;
				case 10:
					cout << "ENTER THE NODE NUMBER\n";
					cin >> n;
					cin.get();
					size = indegree(n);
					cout << "INDEGREE OF " << n << " :: " << size << endl;
					break;
				case 11:
					cout << "ENTER THE NODE NUMBER\n";
					cin >> n;
					cin.get();
					size = outdegree(n);
					cout << "OUTDEGREE OF " << n << " :: " << size << endl;
					break;
				case 12:
					cout << "ENTER THE NODE NUMBER\n";
					cin >> n;
					cin.get();
					size = degree(n);
					cout << "DEGREE OF " << n << " :: " << size << endl;
					break;
				case 13:
					q = p;
					for (int i = 0; i <= v; i++)
						if (q[i] != 0)
							cout << q[i] << "  ";
					cout << endl;
					break;
				case 14:
					showgraph();
					break;
				case 15:
					cout << "ENTER THE NODE NUMBER OF SOURCE AND VERTEX\n";
					cin >> src;
					cin.get();
					cin >> dest;
					cin.get();
					deleteedge(src, dest);
					break;
				case 16:
					cout << "ENTER THE NODE NUMBER\n";
					cin >> n;
					cin.get();
					deletevertex(n);
					break;

				case 17:
					cout << "ENTER ROOT NODE::\n";
					cin >> n;
					cin.get();

					visited = new int[Asize + 1];
					for (int i = 0; i <= Asize; i++)
						visited[i] = 0;

					BFS(n, visited);
					cout << endl;
					delete[] visited;

					break;
				case 18:
					cout << "ENTER ROOT NODE::\n";
					cin >> n;
					cin.get();

					visited = new int[Asize + 1];
					for (int i = 0; i <= Asize; i++)
						visited[i] = 0;

					DFS(n, visited);
					cout << endl;
					delete[] visited;

					break;


				case 19:
					t = transitiveclosure();
					cout << "TRANSITIVE CLOSURE ::\n";
					t.showgraph();
					break;

				case 20:
					kruskal();
					break;

				case 21:
					cout << "ENTER THE ROOT\n";
					cin >> src;
					cin.get();
					primalgorithm(src);
					break;

				case 22:
					BARUVKASALGORITHM();
					break;

				case 24:
					cout << "ENTER THE SOURCE\n";
					cin >> src;
					cin.get();
					Dijkstras(src);
					break;
				case 23:
					cout << "ENTER THE SOURCE\n";
					cin >> src;
					cin.get();
					Bellmanford(src);
					break;

				case 25:case 28:

					if (ispresentdirectedcycle())
						cout << "YES\n";
					else
						cout << "NO\n";
					break;
				case 26:
					floydwarshallallpairshortestpath();
					break;
				case 27:
					if (isconnectedgraph())
						cout << "YES\n" << endl;
					else
						cout << "NO\n";
					break;
				case 29:
					topologicalsort();
					break;
				case 30:
					cout << "ENTER SOURCE NODE\n";
					cin >> src;
					cin.get();
				    DAGshortestpath(src);
					break;
				case 33:
					cout << "NUMBER OF VERTICES ::" << v << endl;
					break;
				case 34:
					cout << "NUMBER OF EDGES ::" << e << endl;
					break;

				case 35:
					cout << "ENTER SOURCE AND DESTINATION RESPECTIVELY\n";
					cin >> src;
					cin.get();
					cin >> dest;
					cin.get();
					if (ispresenttransitivepath(src, dest))
						cout << "YES\n";
					else
						cout << "NO\n";
					break;
                case 32:case 31:
                    visited=new int[Asize+1];
                    for(int i=0;i<=Asize;i++)
                        visited[i]=0;
                    connectedcomponents(visited);
					delete[] visited;
					break;
				}
			}
		}
};

int main()
{
	{
		graph p;
	}
	//system("pause");
	return 0;
}

/*
7
1 1 2 7
1 2 3 8
1 3 5 5
1 5 2 7
1 2 4 9
1 4 1 5

1 4 6 6
1 6 5 8
1 5 7 9
1 6 7 11
1 4 5 15
14


*/

/*
5
1 1 2 4
1 1 3 2
1 2 3 3
1 3 2 1
1 2 4 2
1 2 5 3
1 3 4 4
1 5 4 -5
1 3 5 5




*/

/*
8
1 1 2 2
1 2 3 2
1 3 4 2

1 5 6 2
1 6 7 3


*/

/*
5
1 1 2 2
1 2 3 3
1 1 3 -2
1 3 4 2
1 4 5 3
1 3 5 -3


*/

/*
3
1 1 2 0
1 1 3 0
1 2 3 0
14

*/
