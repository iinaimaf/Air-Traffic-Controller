#include<iostream>
#include<vector>
#include<map>
#include<unistd.h>
using namespace std;

int n=13;

int main()
{
int index;
int indes;
int mc;
int choice;	
int fuel=35000;
float distance;
float d;
float min=9999;
float price;
string source;
string des;
string bc;
string place;
string src;
string destination;

vector <pair <string ,float>> adj[n];
vector <pair <string ,float>> :: iterator it;
vector <pair <string ,float>> :: iterator it1;
map <int , string> guiz;
map <int , string> :: iterator mapit;

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

system("clear");

adj[0].push_back(make_pair("Delhi" , 809));
adj[0].push_back(make_pair("Ahemdabad" , 1626));
adj[0].push_back(make_pair("Bhopal" , 1589));
adj[0].push_back(make_pair("Kolkata" , 2296));
adj[0].push_back(make_pair("Mumbai" , 2227));

adj[1].push_back(make_pair("Srinagar" ,809));
adj[1].push_back(make_pair("Ahemdabad" , 946));
adj[1].push_back(make_pair("Bhopal" , 797));
adj[1].push_back(make_pair("Kolkata" , 1504));
adj[1].push_back(make_pair("Chennai" , 2211));

adj[2].push_back(make_pair("Srinagar" , 1626));
adj[2].push_back(make_pair("Delhi" , 946));
adj[2].push_back(make_pair("Mumbai" , 523));
adj[2].push_back(make_pair("Hyderabad" , 1219));

adj[3].push_back(make_pair("Srinagar" , 1589));
adj[3].push_back(make_pair("Delhi" , 797));
adj[3].push_back(make_pair("Mumbai" , 776));
adj[3].push_back(make_pair("Hyderabad" , 850));
adj[3].push_back(make_pair("Goa" , 1212));
adj[3].push_back(make_pair("Trivanantpuram" , 2124));

adj[4].push_back(make_pair("Srinagar" , 2296));
adj[4].push_back(make_pair("Delhi" , 1504));
adj[4].push_back(make_pair("Mumbai" , 1950));
adj[4].push_back(make_pair("Chennai" , 1670));
adj[4].push_back(make_pair("Portblair" , 1302));

adj[5].push_back(make_pair("Srinagar" , 2227));
adj[5].push_back(make_pair("Ahemdabad" , 523));
adj[5].push_back(make_pair("Bhopal" , 776));
adj[5].push_back(make_pair("Kolkata" , 1950));
adj[5].push_back(make_pair("Goa" , 591));
adj[5].push_back(make_pair("Chennai" , 1337));
adj[5].push_back(make_pair("Trivanantpuram" , 1676));

adj[6].push_back(make_pair("Ahemdabad" , 523));
adj[6].push_back(make_pair("Bhopal" , 1219));
adj[6].push_back(make_pair("Chennai" , 629));

adj[7].push_back(make_pair("Bhopal" , 1212));
adj[7].push_back(make_pair("Mumbai" , 591));
adj[7].push_back(make_pair("Chennai" , 910));
adj[7].push_back(make_pair("Trivanantpuram" , 1249));

adj[8].push_back(make_pair("Delhi" , 1504));
adj[8].push_back(make_pair("Kolkata" , 1670));
adj[8].push_back(make_pair("Mumbai" , 1337));
adj[8].push_back(make_pair("Hyderabad" , 629));
adj[8].push_back(make_pair("Goa" , 910));
adj[8].push_back(make_pair("Trivanantpuram" , 727));
adj[8].push_back(make_pair("PortBlair" , 1362));

adj[9].push_back(make_pair("Bhopal" , 2124));
adj[9].push_back(make_pair("Mumbai" , 1676));
adj[9].push_back(make_pair("Goa" , 1349));
adj[9].push_back(make_pair("Chennai" , 727));

adj[10].push_back(make_pair("Kolkata" , 1302));
adj[10].push_back(make_pair("Chennai" , 1362));


	cout << "\n\n\n\t\t\033[1;31mEnter the source :\033[0m \t";
	cin >> source; 

	source[0]=toupper(source[0]);
	
	for(int i=1;i<source.length();i++)
	{
		source[i]=tolower(source[i]);
	}
	
	cout << "\n\t\t\033[1;31mEnter the destination :\033[0m\t";
	cin >> destination;
	
	destination[0]=toupper(destination[0]);
	
	for(int i=1;i<destination.length();i++)
	{
		destination[i]=tolower(destination[i]);
	}

	for(mapit=guiz.begin();mapit!=guiz.end();mapit++)
	{
		if(mapit->second==source){
			src =source;
			index=mapit->first;
		}
		/*else{
			cout << "You have entered wrong source." << endl;
		}*/
	}

	for(mapit=guiz.begin();mapit!=guiz.end();mapit++)
	{
		if(mapit->second==destination){
			des =destination;
			indes=mapit->first;
		}
		/*else{
			cout << "You have entered wrong destination." << endl;
		}*/
	}	

	for(it=adj[index].begin();it!=adj[index].end();it++)
	{
		if(it->first==destination){
			distance=it->second;
			price=2.5*distance;
		}
	}
	if(distance==0)
	{
		int ipnt,i=1;
		vector <pair <string ,int>> sh[n];
		vector <pair <string ,int>> :: iterator shit;
		int l=0;
		static int 	j=0;
		cout<<"\n\t\tOops : Its seems to be as if there is no direct flight."<<endl;
		cout<<"\n\t\tHit key 1 to proceed for connecting flights. \t";
		cin >> ipnt;
		if(ipnt == 1){
			for(it=adj[indes].begin();it!=adj[indes].end();it++)
			{		
					bc = it->first;
				for(it1=adj[index].begin();it1!=adj[index].end();it1++)
				{
					if(it1->first==bc){
					while(j<1){
						j++;
					}
					d=it1->second;					
					sh[l].push_back(make_pair(it->first,d+it->second));					
					distance=d+it->second;
					i++;
					l++;
					}
				}
				
			}
		}
		for(l ; l>=0 ; l--)
		{
			for(shit=sh[l].begin();shit!=sh[l].end();shit++)
			{
				if(shit->second < min)
				{
					min = shit->second;
					place = shit->first;
				}
			}
		}
		distance =min;
	}
	cout << "\n\n\t\t\t";
	for(int hh=0 ; hh<2 ; hh++)
	{
		for (int mm = 0; mm < 60 ; mm++)
		{
			for(int ss = 0 ; ss < 6 ; ss++)
			{
				for(int s = 0 ; s < 10 ; s++)
				{	
					
						cout << "\r\t\ttime -> " << hh << ":" << mm << ":" << ss << s << " \tfuel -> " << fuel << " \tdistance -> " << distance ;
						fflush(stdout);
						fuel-=4;
						min-=2;
						distance-=0.27;
						if(distance<=0)
						{
							cout << "\n\n\t\tThe flight reached its destination in " << hh << ":" << mm << ":" << ss << s << " hrs" << endl ;
							break;
						}
						sleep(1);
					
				}
				if(distance<=0)
				break;
			}
			if(distance<=0)
			break;
		}
		if(distance<=0)
		break;
	}

return 0;
}	

/*case 6:
		char choice;
		do
		{
			system("gnome-terminal -x sh -c 'cd Desktop/datastructure/DSproject/; g++ timetesting.cpp -o time ;bash -c ./time; exec bash'");
			cout << "What to exit ? Press Y else anyother key.\t" ;
			cin >> choice;
		}while(choice!='y');
		break;*/