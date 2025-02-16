#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
using namespace std;

void sorting(string archivo, string output_file) {
    fstream archivo1(archivo,ios::in|ios::binary);
    ofstream output(output_file, ios::out | ios::binary);
    int tamanio = 256;
    archivo1.seekg(0, ios::end);

    int loops = archivo1.tellg() / tamanio;
    string linea(tamanio,'\0');

    for(int i = 0; i < loops-1;i=i+1){

        int index = i;


        archivo1.seekg(i*tamanio);
        archivo1.read(&linea[0],tamanio);

        for(int j = i+1;j<loops;j=j+1){
            string linea2(tamanio,'\0');
            archivo1.seekg(j * tamanio);
            archivo1.read(&linea2[0], tamanio);

            if(linea2<linea){
                index = j;
                linea=linea2;
            }
         }
       if(index != i){

        string record1(tamanio,'\0');
        archivo1.seekg(i*tamanio);
        archivo1.read(&record1[0], tamanio);

        archivo1.seekp(i*tamanio);
        archivo1.write(&linea[0],tamanio);

        archivo1.seekp(index*tamanio);
        archivo1.write(&record1[0],tamanio);
       }
    }


    archivo1.close();
    archivo1.open(archivo, ios::in | ios::binary);
    while (archivo1.read(&linea[0], tamanio)) {
        output.write(&linea[0], tamanio);
    }

    output.close();
}





int main()
{
    string archivo,archivo2;
    archivo = "data.txt";
    archivo2="sorted.txt";

    cout << "Duracion: " << endl;
    auto start = chrono::high_resolution_clock::now();

    sorting(archivo,archivo2);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, ratio<60>> duration = end - start;
    cout << "Duracion: " << duration.count() << " minutos" << endl;

    return 0;
}
