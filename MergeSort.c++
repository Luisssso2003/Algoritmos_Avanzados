// Rodrigo Castellanos A01643147
// Luis Olmedo A01643557

#include <iostream>
#include <limits>
using namespace std;

void merge(double arr[], int left, int mid, int right){ // Función que ordena de menor a mayor el arreglo
   int n1_left = mid - left + 1;
   int n2_right = right - mid;
   double* leftarr = new double[n1_left];
   double* rightarr = new double[n2_right];

   for(int i = 0; i < n1_left; i++)
        leftarr[i] = arr[left + i];
    
   for(int i = 0; i < n2_right; i++)
        rightarr[i] = arr[mid + 1 + i];

   int i = 0; int j = 0; int k = left;

   while(i < n1_left && j < n2_right){
    if(leftarr[i] >= rightarr[j]){
        arr[k] = leftarr[i];
        i++;
    }
    else{
        arr[k] = rightarr[j];
        j++;
    }
    k++;
   };

   while (i < n1_left){
    arr[k] = leftarr[i];
    i++;
    k++;
   }

   while (j < n2_right){
    arr[k] = rightarr[j];
    j++;
    k++;
   }

   delete[] leftarr;
   delete[] rightarr;
};

void mergeSort(double arr[], int left, int right){ // Función que divide el arreglo a la mitad
      if(left < right){
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right); // Caso base
      } 

};

int main(){
    cout << "Cuantos elementos tendrá el arreglo: ";
    int N;
    while(!(cin >> N) || cin.peek() != '\n') {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Por favor, ingrese un número entero válido: ";
    }

    double* arr = new double[N];

    for(int i = 0; i < N; i++) {
        cout << "Elemento " << i + 1 << ": ";
        while(!(cin >> arr[i]) || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Por favor, ingrese un número decimal válido: ";
        }
    }

    mergeSort(arr, 0, N - 1);

    cout << "La lista final ordenada de mayor a menor es: ";
    for(int i = 0; i < N; i++){
        cout << arr[i];
        if( i < N - 1) cout << ", ";
    }
    cout << endl;

    return 0;
};