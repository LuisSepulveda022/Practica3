#include <iostream>
#include <fstream>
#include <string>
using namespace std;
fstream archivo;

void metodo1(string , int ,int );
void metodo2(string , int ,int );
string almacenar();

int main()
{
        int tam,semilla,metodo;
        string cade = almacenar();
        tam = cade.length();

        if ( cade.empty()==true ){
            cout << "Lo siento no se encuentra el archivo..."<<endl;
        }else{
            cout <<"Ingrese el valor de la semilla: ";cin >> semilla;
            cout <<"Ingrese el metodo de codificacion:\n1.Metodo1\n2.Metodo2\n";cin>>metodo;
            switch (metodo) {
                case 1:
                    metodo1(cade,tam,semilla);
                    break;
                case 2:
                    metodo2(cade,tam,semilla);
                    break;
            default:
                cout <<"No escogio un metodo existente... "<<endl;
                break;
            }
        }

    return 0;
}

void metodo1(string cad, int tam , int sem){
    /*Para codificar se convierte el archivo a binario, luego se separa en bloques de n bits. En el
primer bloque se cambian todos los 1 por 0 y viceversa. Para los grupos siguientes se debe
contar el número de 1s y 0s en el grupo anterior y hacer cambios según la siguiente regla:
● Si hay igual cantidad de 1s y 0s se invierte cada bit del grupo.
● Si hay mayor cantidad de 0s se invierte cada 2 bits.
● Si hay mayor cantidad de 1s se invierte cada 3 bits.
     */

    int con1 =0,con0=0;

    char cadena[tam];

    for (int i=0; i < tam ; i += sem){

        //si i=0 es porque estamos en el primer bloque de bits solo se intercambiar
        if (i == 0 ){
            for(int k=i ; k  < (i+sem) ; k++){
                if(cad[k] == '0'){
                    cadena[k] = '1';
                }else{
                    cadena[k] = '0';
                }
            }
        //sino ya no es el primer bloque de bits debemos tener en cuenta los parametros
        }else if(i != 0){
            for (int k=i; k < (i+sem);k++){
                cadena[k] = cad[k];
            }
            if(con0 > con1){
                for(int k=i+1 ; k < (i+sem);k +=2){
                    if (cad[k] == '0'){
                        cadena[k] = '1';
                    }else{
                        cadena[k] = '0';
                    }
                }
            }else if(con1 > con0){
                for(int k=i+2 ; k < (i+sem);k +=3){
                    if (cad[k] == '0'){
                        cadena[k] = '1';
                    }else{
                        cadena[k] = '0';
                    }
                }
            }else{
                for(int k=i ; k < (i+sem) ; k++){
                    if (cad[k] == '0'){
                        cadena[k] = '1';
                    }else{
                        cadena[k] = '0';
                    }
                }
            }
        }

        con0=0;
        con1=0;
        //contamos la cantidad de '0' y '1' que hay en cada bloque de bits
        for(int j=i ; j < (i+sem) ; j++){
            if (cad[j] == '0'){
                con0 ++;
            }else{
                con1 ++;
            }
        }
    }

    cadena[tam] = '\0';
    cout<<"\n\n"<<"\tMetodo1, semilla:"<<sem<<"\n\n";
    cout << "Cadena original:  "<< cad << endl;
    cout << "Cadena codificada:"<< cadena<<endl;
}

void metodo2(string cad,  int tam, int sem){
    /*Para codificar se convierte el archivo a binario, luego se separa en bloques de n bits. Cada
bit dentro de un grupo se desplaza una posición, de manera que el primer bit del grupo
codificado corresponde al último bit del grupo sin codificar, el segundo bit codificado
corresponde al primero sin codificar y así sucesivamente hasta que el último corresponde
al penúltimo sin codificar*/
    char cadena[tam];

    for (int i=0;  i < tam ; i += sem){
        for(int j=i; j < (i+sem); j++){
            if ( j == i ){
                cadena[j]= cad[((i+sem)-1)];
            }else{
                cadena[j] = cad[j-1];
            }
        }
    }
    cadena[tam] = '\0';
    cout<<"\n\n"<<"\tMetodo2, semilla:"<<sem<<"\n\n";
    cout <<"Cadena original:  " <<cad <<endl;
    cout <<"Cadena codificada:"<<cadena<<endl;
}

string almacenar(){
    string alm;
    archivo.open("datos.txt",ios::in);
    if(archivo.is_open()){
        string linea;
        while (getline(archivo,linea)) {
            //cout <<linea <<endl;
            alm += linea;
        }
        archivo.close();
    }

    return alm;
}

