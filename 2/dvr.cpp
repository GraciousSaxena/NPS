#include<bits/stdc++.h>
#define ll long long
#define u_int unsigned int
#define u_char unsigned char
#define mod 1000000007
#define INT_MAX 100000
using namespace std;
template<typename T>
void accept_array(T arr[],int n)
{
	for(int i=0;i<n;i++)
	{
		cin>>arr[i];
	}
}
template<typename T>
void print_array(T arr[],int n)
{
	for(int i=0;i<n;i++)
		cout<<arr[i]<<" ";
	cout<<endl;
}
struct router{
	int no;
	int n=4;
	int a[10][10];
	//set<int> s;
	vector<pair<int,int>> v;
	void init()
	{
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				a[i][j]=INT_MAX;
	}
	void assign_neighbours()
	{
		a[no][no]=0;
		for(auto it=v.begin();it!=v.end();it++)
		{
			a[no][it->first] = it->second;
		}
	}

	void print_details()
	{
		cout<<no<<endl;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
				cout<<a[i][j]<<" ";
			cout<<endl;
		}

	}
	//int next_hop[10];
	void calc_min_dis(router r[])
	{
		for(int i=0;i<n;i++)
		{
			int mini=INT_MAX;
			if(i!=no)
			{
				router x=r[i];
				for(int j=0;j<n;j++)
				{
					a[i][j]=x.a[i][j];
				}
				for(int p=0;p<n;p++){
					for(int q=0;q<n;q++){
						int mini=a[p][q];
						for(int k=0;k<n;k++)
						{
							if(a[p][k] + a[k][q] < mini)
							{
								/*if(s.find(k)!=s.end())
								{
									cout<<"k->"<<k<<endl;
									next_hop[i]=k;
								}*/
							}
							mini=min(a[p][k]+a[k][q],mini);

						}
						a[p][q]=mini;
					}
				}

			}
		}
	}
	/*void print_hop()
	{
		for(int i=0;i<n;i++)
			cout<<next_hop[i]<<endl;
	}*/

};
typedef struct router router;
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("ip.txt","r",stdin);
	freopen("op.txt","w",stdout);
	#endif

	int n=4;
	router r[n];
	for(int i=0;i<n;i++)
	{
		r[i].init();
		r[i].no=i;
	}
	for(int i=0;i<n;i++)
	{
		vector<pair<int,int>> v;
		pair<int,int> p;
		int no_of_neighbours;
		cin>>no_of_neighbours;
		for(int j=0;j<no_of_neighbours;j++)
		{
			int x,y;
			cin>>x>>y;
			//cout<<"j->"<<j<<"x->"<<x<<endl;
			//r[i].s.insert(x);
			p=make_pair(x,y);
			v.push_back(p);
		}
		r[i].v=v;
	}
	for(int i=0;i<n;i++)
		r[i].assign_neighbours();
	for(int i=0;i<n;i++)
		r[i].print_details();

	cout<<"After Calculating minium distance"<<endl;

	for(int i=0;i<n;i++)
		r[i].calc_min_dis(r);

	for(int i=0;i<n;i++){
		r[i].print_details();
		/*cout<<"Printing next hop"<<endl;
		r[0].print_hop();*/	
	}
		//set<int> s=r[0].s;
		/*cout<<"size = "<<s.size()<<endl;
		for(auto it=s.begin();it!=s.end();it++)
			cout<<*it<<" ";
		cout<<endl;*/

	return 0;
}
