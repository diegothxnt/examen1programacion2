#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


bool esVocal(char c) {
    return c == 'a' ||  c == 'A' ||  c == 'e' ||  c == 'E' ||  
           c == 'i' ||  c == 'I' ||  c == 'o' ||  c == 'O' ||
           c == 'u' || c == 'U';
}


bool esDigito(char c) {
    return c >= '0' && c <= '9';
}

bool starts_with_number(const string& word){ 
    return !word.empty()&&isdigit(word[0]); 
} 

int main() {
    ifstream archivoEntrada("dataExamen2.csv");
    if (!archivoEntrada) {
        cerr << "No se pudo abrir el archivo de entrada." << endl;
        return 1;
    }

    ofstream archivoVocales("vocales.txt");
    ofstream archivoConsonantes("consonantes.txt");
    if (!archivoVocales || !archivoConsonantes) {
        cerr << "No se pudo abrir uno de los archivos de salida." << endl;
        return 1;
    }

    string linea;
    while (getline(archivoEntrada, linea)) {
        istringstream stream(linea);
        string palabra;
        while (stream >> palabra) {
            if (esDigito(palabra[0])) {
                continue;
            }
            if (esVocal(palabra[0])) {
                archivoVocales << palabra << "\n";
            } else {
                archivoConsonantes << palabra << "\n";
            }
        }
    }

    archivoEntrada.close();
    archivoVocales.close();
    archivoConsonantes.close();
    ofstream archivo_salida("dataExamenSalida2.csv"); 
 
    while(getline(archivoEntrada, linea)){ 
        stringstream ss(linea); 
        string palabra; 
        bool primera_palabra=true; 
        while (getline(ss, palabra, ',')){ 
            if (!starts_with_number(palabra)){ 
                if (!primera_palabra){ 
                    archivo_salida << ','; 
                } 
                archivo_salida << palabra; 
                primera_palabra = false; 
            } 
        } 
        archivo_salida<<'\n'; 
    } 
 
    archivoEntrada.close(); 
    archivo_salida.close(); 
 
    cout<<"Se ha eliminado correctamente las palabras que empiezan con un número."<<endl; 


    cout << "Proceso completado exitosamente." << endl;
    return 0;
}