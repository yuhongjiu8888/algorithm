/*插入排序
步骤： 1 2 5 3
    1.从前往后依次比较，如果后面的数比前面小的话就交换次序；
    1 2
    1 2 5
    1 2 3 5
    1 2 3
*/
#include<iostream>
using namespace std;

void swap(int &a,int &b){
    int temp = a;
    a = b;
    b = temp;
}

void InsertSort(int arr[],int len){
    int i = 0;
    for(int i = 0;i<len;i++){
        int j = i+1;
        int value = arr[j];
        for(int k = 0;k<j;k++){
            if(arr[k]<value) continue;
            else {
                swap(arr[k],arr[j]);
            }
        }
        
    }
}

template<class T>
void  insertionSort(T a[],int n);

int main(){
    int arr[]={1,21,12,15,13,4,5};
    int len = sizeof(arr)/sizeof(int);

    InsertSort(arr,len-1);

    for(int i=0;i<len;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;

    int a[]={23,12,13,14,32,11,9};
    int l = sizeof(a)/sizeof(int);
    insertionSort(a,l);
    for(int i=0;i<len;i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}

//插入排序


template<class T>
void  insertionSort(T a[],int n){
    int i,j;//j是将要插入的位置,i是目标元素
    T temp;//模板
    //默认a[0]是已经排序好的
    for(int i=1;i<n;i++){
        //寻找将要插入的位置
        int j=i;//将已经排序好的元素的值赋值给j，让他去寻找在已经排序好的序列的位置
        temp = a[i];
        //找到要插入的位置并给他腾出位置
        while(j>0 && temp<a[j-1]){
            //temp>=a[j-1]时,j就是你要插入的位置
            //现在假设进入循环,给temp腾出位置
            a[j] = a[j-1];
            j--;
        }
        a[j] = temp;

    }

}
