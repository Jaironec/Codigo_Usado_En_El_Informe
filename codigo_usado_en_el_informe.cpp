#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

using namespace std;

void llenarVector(int vector[], int total)
{
    // Número aleatorios entre 1 y 50000:
    for(int i=0; i<total; i++)
        vector[i]=1+rand()%(50000);
}
void imprimirVector(int vector[], int total)
{
    cout<<"\nElementos del vector: \n";
    for(int i=0; i<total; i++)
        cout<<vector[i]<< " ";
}
void intercambiar(int &a, int &b)
{
    int aux=a;
    a=b;
    b=aux;
}


void ordenSecuencial(int vector[], int total)
{
    for(int i=0; i<total; i++)
    {
        for(int j=i+1; j<total; j++)
        {
            if(vector[i]>vector[j])
                intercambiar(vector[i], vector[j]);
        }
    }
}




void OrdenamientoQuicksort(int a[], int primerValor, int ultimoValor)
{
    int central, i, j, pivote;
    central= (primerValor+ultimoValor)/2; //Posicion central del arreglo
    pivote= a[central]; //Capturar el valor medio del arreglo
    i = primerValor;
    j = ultimoValor;

    do{
        //Separando en dos partes el arreglo
        while(a[i] < pivote) i++; //Separando los valores menores al pivote
        while(a[j] > pivote) j--; //Separando los valores mayores al pivote

        if(i<=j){
            int temporal;
            //Intercambio de valores
            temporal = a[i];
            a[i] = a[j];
            a[j] = temporal;
            i++;
            j--;
        }
    }while(i<=j);

    if (primerValor < j)

        OrdenamientoQuicksort(a, primerValor, j);

    if (i < ultimoValor)

        OrdenamientoQuicksort(a, i, ultimoValor);

}



void ordenShell(int a[], int n){

    int ints,i,aux;

    bool band;

    ints=n;

    while(ints>1){

        ints=ints/2;

        band=true;

        while(band==true){

            band=false;

            i=0;

            while((i+ints)<n){

                if(a[i]>a[i + ints]){

                    aux=a[i];

                    a[i]=a[i + ints];

                    a[i + ints]=aux;

                    band=true;

                }

                i++;

            }

        }

    }

}




void ordenShell2(int a[], int n){//optimizado

    int i,j,inc;

    int temp;

    for(inc=1;inc<n;inc=inc*3+1);

    while(inc>0){

        for(i=inc;i<n;i++){

            j=i;

            temp=a[i];

            while((j>=inc)&&(a[j-inc]>temp)){

                a[j]=a[j-inc];

                j=j-inc;

            }

            a[j]=temp;

        }

        inc=inc/2;

    }

}



void ordenBurbuja(int v[], int n){

    int i=0,j=0;

    int aux;

    for(i=1;i<n;i++)

        for(j=0;j<(n-i);j++){

            if(v[j]>v[j+1]){

                aux=v[j];

                v[j]=v[j+1];

                v[j+1]=aux;

            }

        }

}



void burbujaMejorado(int arreglo[], int tamano)
{

    int comparaciones = tamano;

    bool termino = false;

    for (int i = 0; i<(tamano-1) ; i++)

    {

        if (termino)

            break;

        termino = true;

        for (int j = 0; j<comparaciones-1 ; j++)

            if(arreglo[j] > arreglo[j+1])

            {

                intercambiar(arreglo[j],arreglo[j+1]);

                termino = false;

            }

        comparaciones--;

    }

}

double performancecounter_diff(LARGE_INTEGER *a, LARGE_INTEGER *b)
{
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    return (double)(a->QuadPart - b->QuadPart) / (double)freq.QuadPart;
}

int main() {

    LARGE_INTEGER t_ini, t_fin;
    double secs;
    int total=80000;
    int vectorSec[total];
    int vectorBurbuja[total];
    int burbuja_mejorado[total];
    int shell[total];
    int shellopt[total];
    int Quicksort[total];

    srand(time(NULL));
    // Llenar los vectores con elementos aleatorios
    for(int i=0; i<total; i++){
        int elemento = 1+rand()%(50000);
        vectorSec[i]=elemento;
        vectorBurbuja[i]=elemento;
        burbuja_mejorado[i]=elemento;
        shell[i]=elemento;
        shellopt[i]=elemento;
        Quicksort[i]=elemento;
    }

    //ordenación secuencial
    QueryPerformanceCounter(&t_ini);
    ordenSecuencial(vectorSec,total);
    QueryPerformanceCounter(&t_fin);
    secs = performancecounter_diff(&t_fin, &t_ini);
    cout<<endl<<"Tiempo en ordenar " <<total <<" elementos, con el METODO SECUENCIAL: ";
    cout<<(secs*1000.0);

    //ordenación burbuja
    QueryPerformanceCounter(&t_ini);
    ordenBurbuja(vectorBurbuja,total);
    QueryPerformanceCounter(&t_fin);
    secs = performancecounter_diff(&t_fin, &t_ini);
    cout<<endl<<"Tiempo en ordenar " <<total <<" elementos, con el METODO BURBUJA: ";
    cout<<(secs*1000.0);

    //ordenación burbuja mejorado
    QueryPerformanceCounter(&t_ini);
    burbujaMejorado(burbuja_mejorado,total);
    QueryPerformanceCounter(&t_fin);
    secs = performancecounter_diff(&t_fin, &t_ini);
    cout<<endl<<"Tiempo en ordenar " <<total <<" elementos, con el METODO BURBUJA MEJORADO: ";
    cout<<(secs*1000.0);

    //ordenación shell
    QueryPerformanceCounter(&t_ini);
    ordenShell(shell,total);
    QueryPerformanceCounter(&t_fin);
    secs = performancecounter_diff(&t_fin, &t_ini);
    cout<<endl<<"Tiempo en ordenar " <<total <<" elementos, con el METODO Shell: ";
    cout<<(secs*1000.0);

    //ordenación shell optimisado
    QueryPerformanceCounter(&t_ini);
    ordenShell2(shellopt,total);
    QueryPerformanceCounter(&t_fin);
    secs = performancecounter_diff(&t_fin, &t_ini);
    cout<<endl<<"Tiempo en ordenar " <<total <<" elementos, con el METODO Shell optimisado: ";
    cout<<(secs*1000.0);

    //ordenación Quicksort
    QueryPerformanceCounter(&t_ini);
    OrdenamientoQuicksort(Quicksort,0, total-1);
    QueryPerformanceCounter(&t_fin);
    secs = performancecounter_diff(&t_fin, &t_ini);
    cout<<endl<<"Tiempo en ordenar " <<total <<" elementos, con el METODO Quicksort: ";
    cout<<(secs*1000.0);
    cout<<endl<<"ALGORITMOS DE ORDENACION: ";
    return 0;
}
