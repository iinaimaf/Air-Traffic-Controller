
#include<iostream>
#include<vector>
#include<unistd.h>
#include<string>
#include<map>
#include<limits>
#include<set>
#include<queue>
#include<string.h>
#include<algorithm>

using namespace std;

static int id = 0;//Used to give index to each airport
int dijk[11][11];//Matrix for initial connection
bool visited[11];//Visited array for prims
int con[11][11];//Connection 1 or 0
set <pair<int, int> > s;//set used in prims algo'
int parent[11][11];//matrix used to indicate parents
static int book = 0;//used in booking
map <int , string> guiz;//map used to map source id and name
map <int , string> :: iterator mapit;//map iterator

struct inform
{
	string name;
	int age;
	int seat;
};

class airport
{
	int capacity;
	int current = 0;
	int index;
public:
	vector <pair<int ,int> > v[11];
	airport()
	{
	    cout << "\n\n";
	}
	airport(int );
	void plane(int);
	void depart();
	void arrive();
	void show(airport);
	void distance(airport ,airport , int);
	int MST();	
};

class planes : public airport
{
private:
        int seats;
        int reserved;
        queue <string> waiting;
        vector <inform> info;
public:
    planes(int);
	void reserve();
	void cancel();
	void infor();
	void waiting_list();
};


void home();


planes :: planes(int x)
{
	seats = x;
	reserved = 0;
}

void planes :: infor()
{
	vector <inform> :: iterator it;
	for(it=info.begin(); it!=info.end(); it++)
	{
		cout << "\tNAME 	->	" << it->name << "  \n\tSEAT_NO	 -> " << it->seat << "\n\tAGE -> " << it->age << "\n\n";
	}
}

void planes :: reserve()
{
	int no;
	int s = seats;

	cout << "\n\tEnter no seats you want to reserve \t";
	cin >> no;

	if(reserved + no <= s)
	{
		for(int i=0;i<no;i++)
		{
			int age;
			string na;
			cout << "\n\tEnter name :\t";
			cin >> na ;
			cout <<"\n\tEnter age :\t";
			cin >> age;
			cout << "\n\tYour seat no is :	" << "AI" << book << endl;
			info.push_back({na ,age ,book});
			book++;
		}
		cout << endl;
		if(no == 1)
		{
			cout << "\n\tYour seat has been booked. \n" << endl;
		}
		if(no > 1)
		{
			cout << "\n\tYour seats has been booked. \n" << endl;
		}
		reserved = reserved + no;
	}
	else
	{
		char choice;
		cout << "\tSorry ! No more seats available." << endl;
		cout<<"\tWe are putting your name in the waiting list.\n";
		for(int i=0;i<no;i++)
        {
            cout << "\n\tEnter your name: \t";
            string name;
            cin >> name;

            cout << "\n\tEnter your age: \t";
            int age;
            cin >> age;
            waiting.push(name);
        }
	}
}

void planes :: cancel()
{
	string na;
	int seat;
	int age;
	cout << "\n\tEnter the seat no :\t";
	cin >> seat;
	cout << "\n\tEnter your age :\t";
	cin >> age;
	vector <inform> :: iterator it;
    for(it = info.begin(); it != info.end(); it++)
    {
        if(it->seat==seat)
        {
            info.erase(it);
             if(!waiting.empty())
		    {
		        na=waiting.front();
		        waiting.pop();
		        info.push_back({na ,age ,seat});
		    }
            break;
        }
    }
}

void display()
{
	cout << "\n\t\033[0;31msource id" <<  "		"  << "source_name\033[0m"  << endl;
	cout << "\n\t   0" << "		" << "\t Srinagar" ;
	cout << "\n\t   1" << "		" << "\t Delhi" ;
	cout << "\n\t   2" << "		" << "\t Ahemdabad" ;
	cout << "\n\t   3" << "		" << "\t Bhopal" ;
	cout << "\n\t   4" << "		" << "\t Kolkata" ;
	cout << "\n\t   5" << "		" << "\t Mumbai" ;
	cout << "\n\t   6" << "		" << "\t Hyderabad" ;
	cout << "\n\t   7" << "		" << "\t Goa" ;
	cout << "\n\t   8" << "		" << "\t Chennai" ;
	cout << "\n\t   9" << "		" << "\t Trivanantpuram" ;
	cout << "\n\t   10" << "		" << "\t Port_blair" ;
}

airport :: airport(int n)//Airport constructor initializing capacity
{
	capacity = n;
	index = id;
	id++;
}

void airport :: distance(airport a1 ,airport a2 ,int dis)//Function to connect or add two edges
{
	int ind1 = a1.index;
	int ind2 = a2.index;
	v[ind1].push_back(make_pair(ind2 ,dis));
	v[ind2].push_back(make_pair(ind1 ,dis));
	dijk[ind1][ind2]=dis;
	dijk[ind2][ind1]=dis;
	con[ind1][ind2] = 1;
	con[ind2][ind1] = 1;
}

void airport :: show(airport a)//Show connection of particular class to specified parameter
{
	vector <pair<int,int> > :: iterator it;
	int ind = 	a.index;
		for(it=v[ind].begin(); it!=v[ind].end(); it++)
		{
			cout << "\t\t" << it->second << " --------------- " << it->first << endl;
		}
	cout << endl;
}

void airport :: arrive()//Plane arrival
{
	if(capacity == current)
	{
		cout << "No more space available" << endl;
		return;
	}
	current++;
}

void airport :: depart()//Plane departure
{
	if(current == 0)
	{
		cout << "No plane avaialabe" << endl;
		return;
	}
	current--;
}


void airport :: plane(int n)//Initialise N numbers of plane
{
 if(current == capacity || current + n > capacity)
 {
 	cout << "Overflow" << endl;
 	return;
 }
 current = current +n;
}

void set_infi()//Set initial matrix to infinity and bool to false
{
	for(int i=0; i<11; i++)
	{
		visited[i] = false;
		for(int j=0; j<11; j++)
		{
			if(i==j)
			{
				dijk[i][j]=0;
				con[i][j]=0;
			}
			else
			{
				dijk[i][j]=99999;
			}
		}
	}
}

void mini()//print for initial matrix
{
	for(int i=0;i<11;i++)
	{
		for(int j=0;j<11;j++)
		{
			cout << dijk[i][j] << "  ";
		}
		cout << endl;
	}
}

void flyod(int x,int y)//flyod warshall algo
{
	int min[11][11];//matrix used in floyd warshall
	for(int i=0;i<11;i++)
	{
		for(int j=0;j<11;j++)
		{
			min[i][j]=dijk[i][j];
		}
	}
	for (int k=0; k<11; k++)
	{
		for(int i=0; i<11; i++)
		{
			for(int j=0; j<11; j++)
			{
				if(min[i][k] + min[k][j] < min[i][j])
				{
					min[i][j] = min[i][k] + min[k][j];
					parent[i][j] = k;
				}
			}
		}
	}
	cout << "\n\tMinimum distance between your specified source and destination is ->	" << min[x][y];
}

void flyod()//flyod warshall algo
{
	int min[11][11];//matrix used in floyd warshall
	for(int i=0;i<11;i++)
	{
		for(int j=0;j<11;j++)
		{
			min[i][j]=dijk[i][j];
		}
	}
	for (int k=0; k<11; k++)
	{
		for(int i=0; i<11; i++)
		{
			for(int j=0; j<11; j++)
			{
				if(min[i][k] + min[k][j] < min[i][j])
				{
					min[i][j] = min[i][k] + min[k][j];
					parent[i][j] = k;
				}
			}
		}
	}
}

void cost(int x,int y)
{
	double price[11][11];//matrix used in floyd warshall
	double price1[11][11];
	double price2[11][11];
	for(int i=0;i<11;i++)
	{
		for(int j=0;j<11;j++)
		{
			price[i][j]=dijk[i][j]*2.7;
			price1[i][j]=dijk[i][j]*3.0;
			price2[i][j]=dijk[i][j]*2.9;
		}
	}
	for (int k=0; k<11; k++)
	{
		for(int i=0; i<11; i++)
		{
			for(int j=0; j<11; j++)
			{
				if(price[i][k] + price[k][j] < price[i][j])
				{
					price[i][j] = price[i][k] + price[k][j];
				}
				if(price1[i][k] + price1[k][j] < price1[i][j])
				{
					price1[i][j] = price1[i][k] + price1[k][j];
				}
				if(price2[i][k] + price2[k][j] > price2[i][j])
				{
					price2[i][j] = price2[i][k] + price2[k][j];
				}
			}
		}
	}
	cout << "\n\t\033[0;31mMinimum cost between your specified source and destination is ->\033[0m " << price[x][y] << " \033[0;31mRupees\033[0m " << endl;
	cout << "\n\t\033[0;31mIntermediate cost between your specified source and destination is ->\033[0m " << price1[x][y] << " \033[0;31mRupees\033[0m " << endl;
	cout << "\n\t\033[0;31mMaximum cost between your specified source and destination is ->\033[0m " << price2[x][y] << " \033[0;31mRupees\033[0m " << endl;
}

void path(int a,int b)
{
	int min[11][11];//matrix used in floyd warshall
	for(int i=0;i<11;i++)
	{
		for(int j=0;j<11;j++)
		{
			min[i][j]=dijk[i][j];
		}
	}
	for (int k=0; k<11; k++)
	{
		for(int i=0; i<11; i++)
		{
			for(int j=0; j<11; j++)
			{
				if(min[i][k] + min[k][j] < min[i][j])
				{
					min[i][j] = min[i][k] + min[k][j];
					parent[i][j] = k;
				}
			}
		}
	}
	mapit = guiz.find(a);
	cout << "\n\t" << mapit->second << " -> ";

	while(parent[a][b]!=0)
	{
		cout << parent[a][b] << " -> ";
		int temp = parent[a][b];
		parent[a][b] = parent[temp][b];
	}

	mapit = guiz.find(b);
	cout << mapit->second << endl;
}

void soja3()
{
	//sleep(3);
	system("clear");
}

void intro()
{
	cout << "\n\n\n\n\n\n\t\t\t\033[0;31mDatastrcture Project\033[0m\n" ;
	cout << "\n\t\tThis Air traffic controller is managed by " ;
	cout << "\n\n\n\t\tHarsh Vishnoi		16803030" ;
	cout << "\n\t\tNaima Farooqi		16803005" ;
	cout << "\n\t\tKanishka Garg		16803012" ;
	cout << "\n\t\tRachit Shukla		16803023" ;
	cout << "\n\n\n\n" ;
	cout << "\t********************************************************\n" ;
	soja3();
}

int countwalks( int u, int v, int k)
{
    int count[11][11][k+1];

    for (int e = 0; e <= k; e++)
    {
        for (int i = 0; i < 11; i++)
        {
            for (int j = 0; j < 11; j++)
            {
                count[i][j][e] = 0;

                if (e == 0 && i == j)
                    count[i][j][e] = 1;
                if (e == 1 && con[i][j])
                    count[i][j][e] = 1;

                if (e > 1)
                {
                    for (int a = 0; a < 11; a++)
                        if (con[i][a])
                            count[i][j][e] += count[a][j][e-1];
                }
           }
        }
    }
    return count[u][v][k];
}

int main()
{
    planes p(2);

	airport a(50);
	a.plane(25);

	airport b(50);
	b.plane(18);

	airport c(50);
	c.plane(29);

	airport d(50);
	d.plane(25);

	airport e(50);
	e.plane(10);

	airport f(50);
	f.plane(31);

	airport g(50);
	g.plane(30);

	airport h(50);
	h.plane(20);

	airport i(50);
	i.plane(15);

	airport j(50);
	j.plane(26);

	airport k(25);
	k.plane(15);

	set_infi();

	guiz.insert(pair<int , string> (0 , "Srinagar"));
	guiz.insert(pair<int , string> (1 , "Delhi"));
	guiz.insert(pair<int , string> (2 , "Ahemdabad"));
	guiz.insert(pair<int , string> (3 , "Bhopal    "));
	guiz.insert(pair<int , string> (4 , "Kolkata"));
	guiz.insert(pair<int , string> (5 , "Mumbai"));
	guiz.insert(pair<int , string> (6 , "Hyderabad"));
	guiz.insert(pair<int , string> (7 , "Goa"));
	guiz.insert(pair<int , string> (8 , "Chennai"));
	guiz.insert(pair<int , string> (9 , "Trivanantpuram"));
	guiz.insert(pair<int , string> (10 , "Portblair"));

	a.distance(a, b, 809);
	a.distance(a, c, 1626);
	a.distance(a, d, 1589);
	a.distance(a, e, 2296);
	a.distance(a, f, 2227);

	b.distance(b, a, 809);
	b.distance(b, c, 946);
	b.distance(b, d, 797);
	b.distance(b, e, 1504);
	b.distance(b, i, 2211);

	c.distance(c, a, 1626);
	c.distance(c, b, 946);
	c.distance(c, f, 523);
	c.distance(c, g, 1219);

	d.distance(d, a, 1589);
	d.distance(d, b, 797);
	d.distance(d, f, 776);
	d.distance(d, g, 850);
	d.distance(d, h, 1212);
	d.distance(d, j, 2124);

	e.distance(e, a, 2296);
	e.distance(e, b, 1504);
	e.distance(e, f, 1950);
	e.distance(e, i, 1670);
	e.distance(e, k, 1302);

	f.distance(f, a, 2227);
	f.distance(f, c, 523);
	f.distance(f, d, 776);
	f.distance(f, e, 1950);
	f.distance(f, h, 591);
	f.distance(f, i, 1337);
	f.distance(f, j, 1676);

	g.distance(g, d, 850);
	g.distance(g, c, 1219);
	g.distance(g, i, 629);

	h.distance(h, d, 1212);
	h.distance(h, f, 591);
	h.distance(h, i, 910);
	h.distance(h, j, 1349);

	i.distance(i, b, 2211);
	i.distance(i, e, 1670);
	i.distance(i, f, 1337);
	i.distance(i, g, 629);
	i.distance(i, h, 910);
	i.distance(i, j, 727);
	i.distance(i, k, 1362);

	j.distance(j, d, 2124);
	j.distance(j, f, 1676);
	j.distance(j, h, 1349);
	j.distance(j, i, 727);

	k.distance(k, e, 1302);
	k.distance(k, i, 1362);

	intro();
	
    char ch;



a:	int choice;
	cout << "\n\n\n\t\t\t\033[0;31mAIR TRAFFIC CONTROLLER\033[0m\n\n\n";
	cout << "\n\n\033[0;31m\tEnter your choice\033[0m\n";
	cout << "\n\t\033[0;31m1.\033[0m To know shortest path.\n";
	cout << "\n\t\033[0;31m2.\033[0m Min ticket price.\n";
	cout << "\n\t\033[0;31m3.\033[0m Display path.\n";
	cout << "\n\t\033[0;31m4.\033[0m No of paths between two airport taking no of stops into consideration.\n";
	cout << "\n\t\033[0;31m5.\033[0m Reserve seat.\n";
	cout << "\n\t\033[0;31m6.\033[0m Cancel seat.\n";
	cout << "\n\t\033[0;31m7.\033[0m Booked seats information.\n";
	cout << "\n\t\033[0;31m8.\033[0m Departure flight.\t";
	cout << "\n\n\t\033[0;31mEnter your choice \033[0m\t";
	cin >> choice;
	//choose(choice);

	int source ,destination;
		
		switch(choice)
		{
			case 1:
			{
				display();
				char choice;
    			do{
				cout << "\n\n\tEnter your source id ->\t";
				cin >>	source;
				cout << "\n\tEnter your destination id ->\t";
				cin >> destination;
				flyod(source , destination);
				cout << "\n\tWant To enter other input ?\n\t\033[0;31mPress Y for yes or N to continue\t\033[0m";
				cin >> choice;
				}while(choice=='y');
				break;
			}
			case 2:
			{
				display();
				char choice;
    			do{
				cout << "\n\n\tEnter your source id ->\t";
				cin >>	source;
				cout << "\n\tEnter your destination id ->\t";
				cin >> destination;
				cost(source , destination);
				cout << "\n\tWant To enter other input ?\n\t\033[0;31mPress Y for yes or N to continue\t\033[0m";
				cin >> choice;
				}while(choice=='y');
				break;
			}
			case 3:
			{
				display();
				char choice;
    			do{
				cout << "\n\n\tEnter your source id ->\t";
				cin >>	source;
				cout << "\n\tEnter your destination id ->\t";
				cin >> destination;
				path(source ,destination);
				cout << "\n\tWant To enter other input ?\n\t\033[0;31mPress Y for yes or N to continue\t\033[0m";
				cin >> choice;
				}while(choice=='y');
				break;
			}
			case 4:
			{
				display();
				char choice;
    			do{
					int k, no_paths;
					cout << "\n\n\tEnter your source id ->\t";
					cin >>	source;
					cout << "\n\tEnter your destination id ->\t";
					cin >> destination;
					cout << "\n\tEnter no of airport ->\t";
					cin >> k;
					no_paths = countwalks(source ,destination, k+1);
					cout << "\n\tno_paths -> " << no_paths << endl;
					cout << "\n\tWant To enter other input ?\n\t\033[0;31mPress Y for yes or N to continue\t\033[0m";
					cin >> choice;
				}while(choice=='y');
				break;
			}
			case 5:
			{
				p.reserve();
				p.infor();
				goto a;
				break;
			}
			case 6:
			{
				p.cancel();
				p.infor();
				break;
			}
			case 7:
			{
				p.infor();
				break;
			}
			case 8:
			{
				char choice;
				do
				{
					system("gnome-terminal -x sh -c 'cd Desktop/datastructure/DSproject/; g++ timetesting.cpp -o time ;bash -c ./time; exec bash'");
					cout << "\n\tWhat to exit ? Press Y else anyother key.\t" ;
					cin >> choice;
				}while(choice!='y');
				break;
			}
			default:
			{
				system("clear");
				cout << "\n\t\033[0;31mWrong choice ! Enter again :\033[0m" << endl;
				goto a;
				break;
			}
		}	
	
		cout << "\n\n\t\033[0;31mEnter Y to end the program or N to continue :\033[0m \t";
		cin >> ch;
	
		if(ch == 'y' || ch == 'Y')
		{
			exit(1);
		}
		if(ch == 'n' || ch == 'N')
		{
			goto a;
		}

	return 0;
}