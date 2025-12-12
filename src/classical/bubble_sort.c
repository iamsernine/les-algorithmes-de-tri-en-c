#include "../../include/sort_algorithms.h"
void bubble_sort(int arr[],int n){
    int i,j;
    for  (i=0  ;i<n-1 ;i++){
        int swapped = 0;
        for(j=0 ; j<n-i-1 ; j++){
            if(arr[j]>arr[j+1]{
                int temp = arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
                swapped = 1;
            })
        }
        if(!swapped){
            break;
    }
}