#include <bits/stdc++.h>
using namespace std;

struct Project
{
	int Num;
	int processID;  
	int arrivalTime; 
	int burstTime; 
	int Priority; 
	int finishTime; 
	int remainingTime; 
	int waitingTime; 
	int startTime; 
	int Res_time;

};

struct Project current;
typedef struct Project P_d ;

bool idsort(const P_d& x , const P_d& y)
{
	return x.processID < y.processID;
}
/** Sorting on the base of arrival time if that match then on Priority of Process if that also match than on the base of Process Id**/
bool arrivalsort( const P_d& x ,const P_d& y)
{
	if(x.arrivalTime < y.arrivalTime)
		return true;
	else if(x.arrivalTime > y.arrivalTime)
		return false;
	if(x.Priority < y.Priority)
		return true;
	else if(x.Priority > y.Priority)
		return false;
	if(x.processID < y.processID)
		return true;

	return false;
}


bool Numsort( const P_d& x ,const P_d& y)
{
	return x.Num < y.Num;
}
/*Priority Sorting if that same then PID Sorting*/
struct comPare
{
	bool operator()(const P_d& x ,const P_d& y)
	{
		if( x.Priority > y.Priority )
			return true;
		else if( x.Priority < y.Priority )
			return false;
		if( x.processID > y.processID )
			return true;

		return false;

	}

};


void my_check(vector<P_d> mv)
{
	for(unsigned int i= 0; i < mv.size() ;i++)
	{
		cout<<" Pid :"<<mv[i].processID<<"A_time : "<<mv[i].arrivalTime<<" B_time : "<<mv[i].burstTime<<" Priority : "<<mv[i].Priority<<endl;
	}

}

int main()
{
	int i;
	vector< P_d > input;
	vector<P_d> input_copy;
	P_d temp;
	int pq_process = 0; // for PQ process
	int rq_process = 0; // for RQ process
	int arrivalTime;
	int burstTime;
	int processID;
	int Priority;
	int n;
	int clock;
	int total_exection_time = 0;
	cout<<"Enter number of processes";
	cin>>n;
	for( i= 0; i< n; i++ )
	{
		cout<<"Enter process id, arrival time, burst time and priority";
		cin>>processID>>arrivalTime>>burstTime>>Priority;
		temp.Num = i+1;
		temp.arrivalTime = arrivalTime;
		temp.burstTime = burstTime;
		temp.remainingTime = burstTime;
		temp.processID = processID;
		temp.Priority = Priority;
		input.push_back(temp);
	}
	input_copy = input;
	sort( input.begin(), input.end(), arrivalsort );

    total_exection_time = total_exection_time + input[0].arrivalTime;
    for( i= 0 ;i< n; i++ )
    {
    	if( total_exection_time >= input[i].arrivalTime )
    	{
    		total_exection_time = total_exection_time +input[i].burstTime;
    	}
    	else
    	{
    		int diff = (input[i].arrivalTime - total_exection_time);
    		total_exection_time = total_exection_time + diff + burstTime;

    	}
    }

	int Ghant[total_exection_time]={0}; //Ghant Chart
	for( i= 0; i< total_exection_time; i++ )
	{
		Ghant[i]=-1;
	}


	priority_queue < P_d ,vector<Project> ,comPare> pq; 

	queue< P_d > rq; //Round Robin Queue RQ
	int cpu_state = 0; 
	int quantum = 4 ; //Time Quantum
	current.processID = -2;
	current.Priority = 999999;

	for ( clock = 0; clock< total_exection_time; clock++ )
	{
	
		for( int j = 0; j< n ; j++ )
		{
			if(clock == input[j].arrivalTime)
			{
				pq.push(input[j]);
			}
		}


		if(cpu_state == 0) //If CPU idle
		{
			if(!pq.empty())
			{
				current = pq.top();
				cpu_state = 1;
				pq_process = 1;
				pq.pop();
				quantum = 4; 
			}
			else if(!rq.empty())
			{
				current = rq.front();
				cpu_state = 1;
				rq_process = 1;
				rq.pop();
				quantum = 4;
			}
		}
		else if(cpu_state == 1) //If cpu has any procss
		{
			if(pq_process == 1 && (!pq.empty()))
			{
				if(pq.top().Priority < current.Priority ) //If new process has high priority
				{
					rq.push(current); //push current in RQ
					current = pq.top();
					pq.pop();
					quantum = 4; 
				}
			}
			else if(rq_process == 1 && (!pq.empty())) //If process is from RQ and new process come  in PQ
			{
				rq.push(current);
				current = pq.top();
				pq.pop();
				rq_process = 0;
				pq_process = 1;
				quantum = 4 ;
			}


		}


		if(current.processID != -2) // Process Execution
		{
			current.remainingTime--;
			quantum--;
			Ghant[clock] = current.processID;
			if(current.remainingTime == 0) //If process Finish
			{
				cpu_state = 0 ;
				quantum = 4 ;
				current.processID = -2;
				current.Priority = 999999;
				rq_process = 0;
				pq_process = 0;
			}
			else if(quantum == 0 ) //If time Qunatum of a current running process Finish
			{
				rq.push(current);
				current.processID = -2;
				current.Priority = 999999;
				rq_process = 0;
				pq_process = 0;
				cpu_state=0;

			}

		}

	}


	sort( input.begin(), input.end(), idsort );

	for(int i=0;i<n;i++)
	{
		for(int k=total_exection_time;k>=0;k--)
		{
			if(Ghant[k]==i+1)
			{
				input[i].finishTime=k+1;
				break;

			}
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int k=0;k<total_exection_time;k++)
		{

			if(Ghant[k]==i+1)
			{
				input[i].startTime=k;
				break;
			}
		}
	}

	sort( input.begin(), input.end(), Numsort );

	for(int i=0;i<n;i++)
	{
		input[i].Res_time=input[i].startTime-input[i].arrivalTime;
		input[i].waitingTime=(input[i].finishTime-input[i].arrivalTime)-input[i].burstTime;

	}
	cout<<"ProcessID  Res_time     Finish time      Waiting time "<<endl;
	for(int i=0;i<n;i++)
	{
		cout<<input[i].processID<<"\t\t"<<input[i].Res_time<<"\t\t"<<input[i].finishTime<<"\t\t"<<input[i].waitingTime<<endl;

	}	
	return 0;
}
