#include <stdio.h>
struct Project { 
    int p_ID; 
    int burstTime; 
    int tempburstTime; 
    int responseTime; 
    int arrivalTime; 
    int priority; 
    int outTime; 
    int inTime; 
}; 
  
void insert(struct Project Heap[],struct Project value, int* heapsize, int* currentTime) 
{ 
    int start = *heapsize, i; 
    Heap[*heapsize] = value; 
    if (Heap[*heapsize].inTime == -1) 
        Heap[*heapsize].inTime = *currentTime; 
    ++(*heapsize); 
  
    // Heap Ordering 
    while (start != 0 && Heap[(start - 1) / 2].priority >  Heap[start].priority) 
	{ 
        struct Project temp = Heap[(start - 1) / 2]; 
        Heap[(start - 1) / 2] = Heap[start]; 
        Heap[start] = temp; 
        start = (start - 1) / 2; 
    } 
} 
  
// Reorder the heap according to priority 
void order(struct Project Heap[], int* heapsize, int start) 
{ 
    int smallest = start; 
    int left = 2 * start + 1; 
    int right = 2 * start + 2; 
    if (left < *heapsize && Heap[left].priority < 
                            Heap[smallest].priority) 
        smallest = left; 
     if (right < *heapsize && Heap[right].priority <  
                           Heap[smallest].priority) 
        smallest = right; 
  
    // Heap Ordering 
    if (smallest != start) { 
        struct Project temp = Heap[smallest]; 
        Heap[smallest] = Heap[start]; 
        Heap[start] = temp; 
        order(Heap, heapsize, smallest); 
    } 
} 
  
// This function is used to find the process with 
// highest priority from the heap. It also reorders 
// the heap after extracting the highest priority process. 
struct Project extractminimum(struct Project Heap[], int* heapsize, int* currentTime) 
{ 
    struct Project min = Heap[0]; 
    if (min.responseTime == -1) 
        min.responseTime = *currentTime - min.arrivalTime; 
    --(*heapsize); 
    if (*heapsize >= 1) { 
        Heap[0] = Heap[*heapsize]; 
        order(Heap, heapsize, 0); 
    } 
    return min; 
} 

//Swapping two values in the array.
void swap(struct Project *xp, struct Project *yp) 
{ 
    struct Project temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
}
  
// Sorting time intervals in ascending order. 
void sort(struct Project arr[], int n) 
{ 
   int i, j; 
   for (i = 0; i < n-1; i++)        
       for (j = 0; j < n-i-1; j++)  
           if (arr[j].arrivalTime > arr[j+1].arrivalTime) 
              swap(&arr[j], &arr[j+1]); 
} 
  
// This function is responsible for executing 
// the highest priority extracted from Heap[]. 
void scheduling(struct Project Heap[],struct Project array[], int n, int* heapsize, int* currentTime) 
{ 
    if (heapsize == 0) 
        return; 
  
    struct Project min = extractminimum(Heap, heapsize, currentTime); 
    min.outTime = *currentTime + 1; 
    --min.burstTime; 
    printf("process id = %d current time = %d\n", min.p_ID, *currentTime); 
  
    // If the process is not yet finished 
    // insert it back into the Heap
    if (min.burstTime > 0) 
	{ 
        insert(Heap, min, heapsize, currentTime); 
        return; 
    } 
   int i;
    for (i = 0; i < n; i++) 
        if (array[i].p_ID == min.p_ID)
		 { 
            array[i] = min; 
            break; 
        } 
} 

/* This function is responsible for managing the entire execution of the 
 processes according to their arrival time. */
void priority(struct Project array[], int n) 
{ 
    sort(array, n); 
  
    int totalwaitingtime = 0, totalbursttime = 0, totalturnaroundtime = 0, i, insertedprocess = 0;
    int heapsize = 0, currentTime = array[0].arrivalTime, totalresponsetime = 0; 
  
    struct Project Heap[4 * n]; 
  
    // Calculating the total burst time of the processes 
    for (i = 0; i < n; i++) 
	{ 
        totalbursttime += array[i].burstTime; 
        array[i].tempburstTime = array[i].burstTime; 
    } 
  
    // Inserting processes in Heap according to their arrival time 
    do { 
        if (insertedprocess != n) { 
            for (i = 0; i < n; i++) { 
                if (array[i].arrivalTime == currentTime) { 
                    ++insertedprocess; 
                    array[i].inTime = -1; 
                    array[i].responseTime = -1; 
                    insert(Heap, array[i], &heapsize, &currentTime); 
                } 
            } 
        } 
        scheduling(Heap, array, n, &heapsize, &currentTime); 
        ++currentTime; 
        if (heapsize == 0 && insertedprocess == n) 
            break; 
    } while (1); 
  
    for (i = 0; i < n; i++) { 
        totalresponsetime += array[i].responseTime; 
        totalwaitingtime += (array[i].outTime - array[i].inTime - array[i].tempburstTime); 
        totalbursttime += array[i].burstTime; 
    } 
    printf("Average waiting time = %f\n", 
           ((float)totalwaitingtime / (float)n)); 
    printf("Average response time =%f\n", 
           ((float)totalresponsetime / (float)n)); 
    printf("Average turn around time = %f\n", 
           ((float)(totalwaitingtime + totalbursttime) / (float)n)); 
} 
  
int main() 
{ 
    int n, i,pid,bt,at,p; 
    struct Project a[5];
   /* printf("Enter the number of processes :");
    scanf("%d",&n);
    struct Project a[n];
    for(i=0;i<n;i++)
    {
    	printf("Enter the Process ID for %d : ",i);
    	scanf("%d",&pid);
    	printf("Enter the Arrival Time for %d : ",i);
    	scanf("%d",&at);
    	printf("Enter the Burst Time for %d : ",i);
    	scanf("%d",&bt);
    	printf("Enter the Priority for %d : ",i);
    	scanf("%d",&p);
	}
	priority(a,5);
	return 0;
}*/

    a[0].p_ID = 1; 
    a[0].arrivalTime = 4; 
    a[0].priority = 2; 
    a[0].burstTime = 6; 
    a[1].p_ID = 4; 
    a[1].arrivalTime = 5; 
    a[1].priority = 1; 
    a[1].burstTime = 3; 
    a[2].p_ID = 2; 
    a[2].arrivalTime = 5; 
    a[2].priority = 3; 
    a[3].burstTime = 7; 
    a[3].p_ID = 3; 
    a[3].arrivalTime = 1; 
    a[3].priority = 4; 
    a[3].burstTime = 2; 
    a[4].p_ID = 5; 
    a[4].arrivalTime = 3; 
    a[4].priority = 5; 
    a[4].burstTime = 4; 
    priority(a, 5); 
    return 0; 
} 


