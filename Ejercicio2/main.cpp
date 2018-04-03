#include <iostream>
#include <fstream>

using namespace std;

string Almacenar(string );
void Escribir(string , string);
string metodo1(string , int ,int );
string metodo2(string , int , int);
int main()
{
    int tam,semilla,metodo;
            string nombre;

            cout << "Ingrese el nombre al archivo a leer: "; getline(cin,nombre);
            nombre +=".bin";
            string modificada,cade = Almacenar(nombre);
            tam = cade.length();

            if ( cade.empty()==true ){
                cout << "Lo siento no se encuentra el archivo..."<<endl;
            }else{

                cout << "Ingrese el nombre al archivo para guardar el texto codificado: "; getline(cin,nombre);
                nombre +=".bin";

                while(true){
                    cout <<"Ingrese el valor de la semilla: ";cin >> semilla;cout << endl;
                    if(semilla >= tam){
                        cout << "Semilla invalida ya que la longitud de la cadena es:"<<tam<<endl;
                    }else{
                        break;
                    }
                }
                cout <<"Ingrese el metodo de codificacion:\n1.Metodo1\n2.Metodo2\n";cin>>metodo;
                switch (metodo) {
                    case 1:
                        modificada=metodo1(cade,tam,semilla);
                        break;
                    case 2:
                        modificada=metodo2(cade,tam,semilla);
                        break;
                default:
                    cout <<"No escogio un metodo existente... "<<endl;
                    break;
                }
                Escribir(modificada,nombre);
            }


    return 0;
}

string Almacenar(string entrada){
    string cadena;
    ifstream lectura;

    lectura.open(entrada, ios::in);

    if (!lectura.fail() ){
        string linea;

        while( getline(lectura,linea)){
            cadena += linea;
        }
        lectura.close();
    }else{
        cout<<"No se encontro el archivo..."<<endl;
    }

    return cadena;
}

void Escribir(string cadena, string salida){
    ofstream escribir;

    escribir.open(salida, ios::out);

    escribir<<cadena;

    escribir.close();

}
string metodo1(string cad, int tam , int sem){
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
            if(con0 > con1 || con1 > con0){
                for(int k=i+1 ; k < (i+sem);k +=2){
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

    return cadena;
}

string metodo2(string cad,  int tam, int sem){
    char cadena[tam];

    for (int i=0;  i < tam ; i += sem){

        for(int j=i; j < (i+sem) ; j++){
            if ( (j+1) == (i+sem)){
                cadena[j] = cad[i];
            }else{
                cadena[j] = cad[j+1];
            }
        }
    }
    cadena[tam] = '\0';
    cout<<"\n\n"<<"\tMetodo2, semilla:"<<sem<<"\n\n";
    cout <<"Cadena original:  " <<cad <<endl;
    cout <<"Cadena codificada:"<<cadena<<endl;

    return cadena;
}
