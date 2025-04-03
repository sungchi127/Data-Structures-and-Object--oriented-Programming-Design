#include<bits/stdc++.h>
using namespace std;
const int Max=1000000000;
const int MaxSZ=1000;
int n=50;
void merge(vector<int> &array ,int front ,int mid,int end)
{
    vector<int> l(array.begin()+front,array.begin()+mid+1);
    vector<int> r(array.begin()+mid+1,array.begin()+end+1);
    l.insert(l.end(), Max);
    r.insert(r.end(), Max);
    
    int rindex=0,lindex=0;
    for(int i=front;i<=end;i++){
        if(l[lindex]<=r[rindex])
        {
            array[i]=l[lindex];
            lindex++;
        }
        else
        {
            array[i]=r[rindex];
            rindex++;
        }
    }
}

void Mergesort(vector<int> &array,int front,int end)
{
    if(front<end){
        int mid = (front+end)/2;
        Mergesort(array,front,mid);
        Mergesort(array,mid+1,end);
        merge(array,front,mid,end);
    }
}
int main(){
    srand(time(NULL));
    vector<int> array(MaxSZ);
    cout<<"before:";
    for(int i=0;i<n;i++){
        array[i]=rand();
        cout<<array[i]<<" ";
    }
    cout<<endl;
    
    Mergesort(array,0,n-1);

    cout<<"after:";
    for(int i=0;i<n;i++){
       cout<<array[i]<<" ";
    }
    cout<<endl;

    cout <<"check:"<< is_sorted(begin(array), begin(array) + n) << "\n";
    return 0;
}
