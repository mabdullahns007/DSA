#include <bits/stdc++.h>
#include <iostream>
#include <queue>
#include <stack>
#define V 12
#define m 999
#include <string>

using namespace std;

//Stations
int arr[V][V]=
		 {
			 {m, m, 1 ,m ,m, m, m, m, m, m, m, m},
			 {m, m, 1, m, m, m, 1, m, m, m, m, m},
			 {1, 1, m, 1, m, m, m, m, m, m, m, m},
			 {m, m, 1, m, 1, 1, m, m, m, m, m, m},
			 {m, m, m, 1, m, m, m, m, m, m, m, m},
			 {m, m, m, 2, m, m, 3, 2, m, m, m, m},
			 {m, 1, m, m, m, 1, m, m, m, m, m, m},
			 {m, m, m, m, m, 1, m, m, 1, 1, m, m},
			 {m, m, m, m, m, m, m, 1, m, m, m, m},
			 {m, m, m, m, m, m, m, 1, m, m, 1, 1},
			 {m, m, m, m, m, m, m, m, m, 1, m, m},
			 {m, m, m, m, m, m, m, m, m, 1, m, m}
		};
		
//Bus routes		
int busLocations[V][6]
		 {
	         {0,1,0,0,0,0},		 
	         {1,0,0,0,1,1},
	         {0,1,0,0,1,1},
	         {0,1,1,1,1,1},
	         {0,0,1,0,1,0},
			 {1,1,1,1,0,1},
	         {1,1,0,0,0,0},
	         {0,0,1,1,0,1},
	         {0,0,0,0,0,1},
	         {0,0,1,1,0,0},
	         {0,0,0,1,0,0},
	         {0,0,1,0,0,0},
		 };	 		 		

class dijkstra
{
	private:
//	source vertex:
	int src;
//	destination vertex:
	int des;
//	array to copy stations graph:
	int (*arr)[V];
//	array to copy busses at vertices graph:
	int (*brr)[6];
//	visited array for dijkstra shortest path:
	bool visited[V]; 
//	distance array for vertices in dijkstra:
	int dist[V];
//	array storing shortest path vertices in string form:
	string path[V];
//	array storing shortest path vertices in integer form:
	int vis[V];
//	global stack used in priority method for message generation:
	stack<int> w;
//	user route:
	string tripPlan;
//	count to store number of vertices crossed:
	int cCount;

	public:
//	argument constructor:
	dijkstra(int a[V][V],int busLocations[V][6])
	{
			cCount=0;
			arr=a;
			brr=busLocations;
			for(int i=0;i<V;i++)
			{
				visited[i]=false;	
				path[i]=" ";
			}
	}
//	dijkstra algo implementation:
	void shortestPath(int x, int dest)
	{
		src=x;
		des=dest;
		int point=x;		
		
		for(int i=0;i<V;i++)
		{
//	initializing vis array to -1:
			vis[i]=-1;
			dist[i]=arr[x][i];
			if(arr[x][i]!=m)
			{
//	initializing path array according to source vertex's connections:
				path[i]=to_string(src)+"->"+to_string(i);	
			}
			else
			{
				path[i]="no path :(";
			}
		}
		
		while(allVisited()==false)
		{
//			for first iteration of loop:
			if(point==x)
			{
	
				visited[point]=true;
//				setting current point to minimum distance vertex:
				point=minIndex(x);
			}
//			for remaining iterations:
			else
			{
	
				for(int i=0;i<V;i++)
				{
					if(arr[point][i]+dist[point]<dist[i])
					{
//						updating distance of each point from the source vertex:
					 	dist[i]=arr[point][i]+dist[point];
//					 	updating path of each vertex from the source vertex:
					 	path[i]=path[point]+"->"+to_string(i);	 			
					}		 	
				}
//				set the visited point to true;
				visited[point]=true;
//				setting current point to minimum distance vertex:
				point=minIndex(point);
			}
//			next iteration of outer loop begins
		}
//		loop ends here

//  string array of paths is generated in the above code

//  now we extract the vertices from the string path to integer array
//  for further use in priority and message methods:
		initVis(dest); 
		cout<<"\n";
//		call message generation method:
		message();
		cout<<"\n";
	}
//	helper function to add balanced spaces in menu:
	void space(string x)
	{
		for(int i=0;i<22-x.length();i++)
		{
			cout<<" ";
		}
	}
	//		 private functions:
	
//	distance of each point from source:
	private: void printdist()  //unused method
	{
		for(int i=0;i<V;i++)
		{
			if(dist[i]==0)
			{
				cout<<src<<" -> "<<i<<": ";
				cout<<"infinite"<<endl;	
			}
			else
			{
				cout<<src<<" -> "<<i<<": ";
				cout<<dist[i]<<endl;
			}
		}
	}
	
	//MIN INDEX
	int minIndex(int x)
	{
		int min =m, min_index;
		for (int v = 0; v < V; v++)
			if (visited[v] == false && arr[x][v] <= min)
				min = arr[x][v], min_index = v;
		return min_index;
	}
	
    //ALL VISITED
	bool allVisited()
	{
		for(int i=0;i<V;i++)
		{
			if(visited[i]==false)
			{
				return false;
			}
		}
		return true;
	}
//	print station graph to confirm graph is correctly copied
	void printGraph()  //unused method
	{
		 	for(int i=0;i<V;i++)
			 {
		 		cout<<i <<": ";
		 		for(int j=0;j<V;j++)
				 {
		 			cout<<arr[i][j]<<"  ";
				 }
				 cout<<"\n";
			 }
		 }

//		 print boolean visited array:
	void printBool()   //unused method
	{
		for(int i=0;i<V;i++)
		{
		 	cout<<i <<": ";
		 	cout<<visited[i]<<"  ";
			cout<<"\n";
		}
	}
	
	

	void initVis(int j)
	{
		for(int i=0;i<V;i++)
		{
//			reach the destination vertex path:
			if(i==j)
			{
//				starting index for global vis[V] array:
				int index=-1;
				 for(int x=0;x<path[i].length();x++)
				 {
//				 	current character:
				 	char c=path[i][x];

				 	if(x+1<path[i].length())
					{
//				 	next character:
				 	char d=path[i][x+1];
// 						if both current and next characters are numbers between 0-9:				 		
				 		if((int)c>=48 && (int)c<=57   &&  (int)d>=48 && (int)d<=57 )
						 {
//						 	join both into one string:
				 			string a;
							a=a+c+d;

							int num;
//							convert this string to integer:							 
							num = std::stoi(a);
//							 store this number in the global integer path array:
				 			vis[++index]=num;
//				 			extra increment in x due to storing two characters at once:
				 			x++;
						    continue;
						 }
					}
//					if only current character is a number and the next character is an arrow -->
					if((int)c>=48 && (int)c<=57)
					{
//							 store this number in the global integer path array:
						vis[++index]=path[i][x]-'0';
					}
				 }
				 break;
			}
		 			
		}
	}

//	shows busses present at each vertex:
	void printBusLocations() //unused method
	{
		for(int i=0;i<V;i++)
		{
			cout<<"At "<<name(i);
			space(name(i));
			for(int b=0;b<6;b++)
			{
				if(brr[i][b]!=0)
				{
					cout<<" Wagon: "<<b;
				}
			}	
				cout<<"\n";
		}		
	}
	
//	print global vis[V] array:
	void printVis()   //unused method
	{
		for(int i=0;i<V;i++)
		{
			if(vis[i]==-1)
			{
				break;
			}
			cout<<"point: "<<vis[i]<<"\n";
		}
	}
//prints String path for destination
	void printPath(int i)  //unused method
	{
		cout<<to_string(src)+" to "+to_string(i)+":  "+path[i];
		cout<<"	";		
		cout<<"\n"; 
	}
	
	
	

//	wagon path storage:
	void message()
	{
		//index variable for accessing the vertices in the vis array
		int count=0;
		while(vis[count+1]!=-1)
		{
			tripPlan+="From "+name(vis[count])+", Take Bus num ";
			
//			calling priority function to push ideal wagon in global stack
//			and increasing count to access the next vertex at the end of that wagon route:
			count+=priority(count); //here, count is the index we will use to obtain the current vertex in vis[V] array
//			obtain the ideal wagon from the global stack:
			    string num=to_string(w.top());
			    
			    tripPlan+=num+" until "+name(vis[count])+"\n";
			
//Count for number of stations
			cCount+=count;
		}
	}
	
//	priority method to push ideal Bus in the global array
	int priority(int index)
	{	
//	an array to store counts of 6 Buses, the highest count index will be pushed in global stack
// and the highest count will be returned to be added to the count of message() method:
		int c[]={0,0,0,0,0,0};	
		
//		iterate for each wagon:
			for(int i=0;i<6;i++)
			{	
				int count=index;		
//				inner while loop to see how many consecutive stops does a bus reach:
				while(vis[count+1]!=-1)
				{
//		increment count of current bus until it is absent at the next vertex of visited array
// 
				if(brr[vis[count]][i]==1 && brr[vis[count+1]][i]==1)
				{
					c[i]++;
					count++;
					continue;
				}
//				break the inner loop if bus is absent in the present or next vertex:
				break;	
				}
			}
// max count to be returned:
		int max=c[0];
//		bus index with the maximum consecutive stops:
		int mi=0;
		for(int i=0;i<6;i++)
		{
			if(c[i]>max){
				
				max=c[i];
				mi=i;
			}
		}
//		max consecutive stops wagon is pushed in the global stack:
		w.push(mi);
//		max count is returned to be added to the count in message() function:
		return max;	
	}
	

//	switch case method to convert vertices into their actual names:
	string name(int x)
	{
		switch (x)
		{
			
			case 0:
				return "Faisal Mosque";
			case 1:
				return "Aabpara";
			case 2:
				return "Zero Point";
			case 3:
				return "Faizabad";
			case 4:
				return "Mandi Mor";
			case 5:
				return "Khanna Pul";
			case 6:
				return "Comsats University";
			case 7:
				return "Koral";
			case 8:
				return "Saddar";
			case 9:
				return "PWD";
			case 10:
				return "Bahria";
			case 11:
				return "Rawat";
		}
	}
	
	public :
	string tripPlanner()
	{
		int a;
	    int b;
		cout<<"BUS STOPS: \n";
		cout<<"1- Faisal Mosque";space("Faisal Mosque");cout<<"2- Aabpara \n";
		cout<<"3- Zero Point";space("Zero Point");cout<<"4- Faizabad \n";
		cout<<"5- Mandi Mor";space("Mandi Mor");cout<<"6- Khanna Pul \n";
		cout<<"7- Comsats University";space("Comsats University");cout<<"8- Koral \n";
		cout<<"9- Saddar";space("Saddar");cout<<"10- PWD \n";
		cout<<"11- Bahria";space("Bahriaa");cout<<"12- Rawat \n";
		cout<<"\n";
		cout<<"Enter Boarding Stop Number:: ";
		cin>>a;
		cout<<"Enter Your Destination Stop Number:: ";
		cin>>b;
		shortestPath(a-1,b-1);
		return tripPlan;
	}
	int totalStations()
	{
		return cCount;
	}
	string finalPath()
	{
		string path="";
		path+="Your path will be: \n";
		int count=0;
		while(vis[count]!=-1)
		{
			path+=name(vis[count]);
			if(vis[count+1]!=-1)
			{
				path+="-->";	
			}
			count++;
		}
		path+="\n";
		path+="\n";
		return path;	
	}	
};

//CUSTOMER STRUCT AND RELATED FUNCTIONS
struct customer
{
	string name;
	int ticketID;
	string tripPlan;
	int ticketPrice;
	customer *next=NULL;
};

//LINKED LIST OF CUSTOMERS
customer *first=NULL;
customer *last=NULL;

//ADDING CUSTOMERS
void AddCustomer()
{
    customer * cur=new customer;
	cout<<"Enter Customer Name:\n";
	cin>>cur->name;
	cout<<"Enter Ticket ID:\n";
	cin>>cur->ticketID;
	
	dijkstra d=dijkstra(arr,busLocations);
	
	//Trip Route of Customer
	cur->tripPlan=d.tripPlanner();
	cout<<d.finalPath();
	
	
	//Ticket Price 
	//20 Rs. Per Station
	cur->ticketPrice=d.totalStations()*20;
	
	//Asking customer if they want the ticket or not
	cout<<"TICKET PRICE: "<<cur->ticketPrice<<endl;
	cout<<"DO YOU WANT TO BUY TICKET?\n"<<"PRESS 1 for YES and 0 for NO\n";
	
	
	int choice;
	cin>>choice;
	cout<<endl;
	
	if(choice==1)
	{
		if(first==NULL)
		{
			first=last=cur;
		}
		else
		{
			last->next=cur;
			last=cur;
		}
		cout<<"TICKET:\n";
		cout<<"NAME: "<<cur->name<<endl;
		cout<<"TICKET ID: "<<cur->ticketID<<endl;
		cout<<"TRIP DETAILS:\n"<<cur->tripPlan;
		cout<<"TICKET PRICE: "<<cur->ticketPrice;
		cout<<endl;
		cout<<endl;
	}
	else
	{
		cout<<"HAVE A NICE DAY\n";
	}

}

//DISPLAY ALL CUSTOMERS
void Display()
{
	int i=1;
	customer *a=first;
	while(a!=NULL)
	{
		cout<<">CUSTOMER "+to_string(i)+":\n";
		cout<<"NAME: "<<a->name<<endl;
		cout<<"TICKET ID: "<<a->ticketID<<endl;
		cout<<"TRIP DETAILS:\n"<<a->tripPlan;
		cout<<"TICKET PRICE: "<<a->ticketPrice;
		cout<<endl;
		cout<<endl;
		
		a=a->next;
		i++;
	}
	cout<<endl;	
}

//SEARCH A CUSTOMER
void Search()
{
	int key;
	cout<<"Enter Ticket ID to search:\n";
	cin>>key;
	bool checkIfFound=false;
	
	customer *p=first;
	while(p!=NULL)
	{
		if(p->ticketID==key)
		{
			cout<<"RECORD:\n";
			cout<<"NAME: "<<p->name<<endl;
			cout<<"TICKET ID: "<<p->ticketID<<endl;
			cout<<"TRIP DETAILS:\n"<<p->tripPlan<<endl;
			cout<<"TICKET PRICE:\n"<<p->ticketPrice;
			checkIfFound=true;
			break;
		}
		p=p->next;
	}
	if(!checkIfFound)
	{
		cout<<"TICKET ID NOT FOUND\n";
	}
}

//TOTAL EARNING OF THE DAY
double totalEarnings()
{
	customer *c=first;
	double earnings=0;
	
	while(c!=NULL)
	{
		earnings+=c->ticketPrice;
		c=c->next;
	}
	return earnings;
}

//DELETE CUSTOMER
void deleteCustomer()
{
	int key;
	cout<<"ENTER TICKET ID TO DELETE CUSTOMER: ";
	cin>>key;
	
	customer *k,*k1;
	k1=NULL;
	k=first;
	while(k!=NULL)
	{
		if(k->ticketID==key)
		{	
			//k is the customer to be deleted
			if(k==first)
			{
				first=first->next;
				cout<<first->ticketID;
				k=NULL;
			}
			else if(k==last)
			{
				k1=first;
				while(k1->next!=k)
				{
					k1=k1->next;
				}
				last=k1;
				last->next=NULL;
			}
			else
			{
				k1=first;
				while(k1->next!=k)
				{
					k1=k1->next;
				}
				k1->next=k->next;
				k=NULL;
			}
				break;
			}
			k=k->next;	
	}
}

//BUSES
void AvailableBuses()
{
	for(int i=0;i<V;i++)
	{
		int vertex=i;
		switch(vertex)
		{
			case 0:
				cout<<"Faisal Mosque: BUSES: ";
				break;
			case 1:
				cout<<"Aabpara: BUSES: ";
				break;
			case 2:
				cout<<"Zero Point: BUSES: ";
				break;
			case 3:
				cout<<"Faizabad: BUSES: ";
				break;
			case 4:
				cout<<"Mandi Mor: BUSES: ";
				break;
			case 5:
				cout<<"Khanna Pul: BUSES: ";
				break;
			case 6:
				cout<<"Comsats University: BUSES: ";
				break;
			case 7:
				cout<<"Koral: BUSES: ";
				break;
			case 8:
				cout<<"Saddar: BUSES: ";
				break;
			case 9:
				cout<<"PWD: BUSES: ";
				break;
			case 10:
				cout<<"Bahria: BUSES: ";
				break;
			case 11:
				cout<<"Rawat: BUSES: "; 
				break;
		}
		for(int k=0;k<6;k++)
		{
			int bus=busLocations[i][k];
			if(bus==1)
			{
				cout<<k;
			}
		}
		cout<<endl;
	}
}


int main()
{
 	int x;
	while(true)
	{
		cout<<"WELCOME TO CAPITAL BUS STATION SYSTEM\n"<<endl;
		cout<<"Enter 1 to Display All Customers\n";
		cout<<"Enter 2 to PLAN ROUTE FOR CUSTOMER\n";
		cout<<"Enter 3 to Search a Customer\n";
		cout<<"Enter 4 to Check Total Earning\n";
		cout<<"ENTER 5 to Delete a Customer\n";
		cout<<"ENTER 6 to CHECK AVAILABLE BUSES\n";
		cin>>x;
		cout<<endl;
		switch(x)
		{
			case 1:
				Display();
				break;
			case 2:
				AddCustomer();
				break;
			case 3:
				Search();
				break;
			case 4:
				cout<<"TOTAL EARNING OF THE DAY: "<<totalEarnings()<<"rs\n";
				break;
			case 5:
				deleteCustomer();
				break;	
			case 6:
				AvailableBuses();
				break;	
		}
	}
	return 0;
}
