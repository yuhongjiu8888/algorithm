#include<iostream>
using namespace std;

void merge(int arr[],int start,int mid,int end,int temp[]){
    int p = 0;
    int v = start;
    int v2 = mid+1;

    while(v<=mid && v2<=end){
        if (arr[v] < arr[v2])
        {
            temp[p++] = arr[v++];
        }else{
            temp[p++] = arr[v2++];
        }
        
    }

    while(v<=mid) temp[p++] = arr[v++];
    while(v2<=end) temp[p++] = arr[v2++];

    for(int i = 0;i<end-start+1;i++){
        arr[start+i] = temp[i];
    }

}

void MergeSort(int arr[],int start,int end,int temp[]){
    if(start < end){
        int mid = start+(end-start)/2;
        MergeSort(arr,start,mid,temp);
        MergeSort(arr,mid+1,end,temp);
        merge(arr,start,mid,end,temp);
    }

}

int main(){
    int arr[]={23,1,13,12,5,45,31,20};
    int len = sizeof(arr)/sizeof(int);

    int temp[8]; //临时数组

    MergeSort(arr,0,len-1,temp);

    for(auto v:arr){
        cout<<v<<" ";
    }
    cout<<endl;

    return 0;
}