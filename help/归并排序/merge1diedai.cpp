/*时间复杂度o(nlogn)，空间复杂度o(n)
是稳定排序
*/
#include <iostream> 
#include <cstdio> 
#include <math.h> 
#include <cstdlib> 

using namespace std; 

const int n = 40; 

void swap(int *a,int i,int j) 
{ 
int temp; 
temp = a[i]; 
a[i] = a[j]; 
a[j] = temp; 
} 

void merge(int *a,int m,int n,int *b,int i,int j) 
{ 
int begin = m,h = m,k = i; 

while(h <= n && k <= j) 
{ 
if(a[h] <= a[k]) 
{ 
b[begin] = a[h]; 
h++; 
}else{ 
b[begin] = a[k]; 
k++; 
} 
begin++; 
} 
while(h <= n) 
{ 
b[begin] = a[h]; 
begin ++; 
h++; 
} 
while(k <= j) 
{ 
b[begin] = a[k]; 
begin ++; 
k++; 
} 
} 

void mergeall(int *a,int *b,int len,int n) 
{ 
int i = 0; 
while((i + 2*len) <= n) 
{ 
merge(a,i,i+len-1,b,i+len,i + 2*len -1); 
i = i + 2*len; 
} 
if((i + len) > n) 
{ 
while(i < n) 
{ 
b[i] = a[i]; 
i++; 
} 
} 
else merge(a,i,i+len-1,b,i+len,n-1); 
} 

void mergesort(int * a,int n) 
{ 
int len = 1; 
int * temp; 

temp = new int[n]; 
while(len < n) 
{ 
mergeall(a,temp,len,n); 
len = len * 2; 
mergeall(temp,a,len,n); 
len = len * 2; 
} 
delete []temp; 
} 

void printarray(int * a,int n) 
{ 
cout << "print array " 
<< endl; 
for(int i = 0;i < n;i++) 
{ 
cout << a[i] 
<< "  "; 
if((i+1)%10 == 0) 
cout << endl; 
} 
cout << endl; 
} 

int main(int argc,char *argv[]) 
{ 
int a[n]; 

for(int i = 0;i < n;i++) 
a[i] = rand()%1000; 
printarray(a,n); 
mergesort(a,n); 
printarray(a,n); 

return 0; 
} 