#include<iostream>
using namespace std;

void swap(int &a,int &b){
    int temp = a;
    a = b;
    b = temp;
}

void QuickSort(int arr[],int start,int end){

    if(start >= end){
        return ;
    }

    int flag = arr[start];
    int i = start;
    int j = end;

    while(i!=j){
        while(i<j && arr[j]>=flag) --j;
        swap(arr[i],arr[j]);

        while(i<j && arr[i]<=flag) ++i;
        swap(arr[i],arr[j]); 

    }
    
    QuickSort(arr,start,i-1);
    QuickSort(arr,i+1,end);

}

int main(){
    int arr[] = {23,11,2,4,1,45,65,23,22,77,30};
    int len = sizeof(arr)/sizeof(int);

    QuickSort(arr,0,len-1);

    for(auto v:arr){
        cout<<v<<" ";
    }
    cout<<endl;

    return 0;
}