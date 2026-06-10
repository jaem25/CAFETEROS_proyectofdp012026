#include <iostream> 
using namespace std;
int main () {
    int opcion;
    do {
        cout<<"\n======MENU USUARIO======"<<endl;
        cout<< "1. Ver menu"<<endl;
        cout<<"2. Hacer pedido"<<endl;
        cout<<"3. Ver pedido"<<endl;
        cout<<"4. Calcular total"<<endl;
        cout<<"5. Modificar pedido"<<endl;
        cout<<"6. Salir"<<endl;
        cin>>opcion; 
        if(opcion <1 || opcion >6) {
            cout<<"Opcion invalida"<<endl;
        }
    }
        while(opcion !=6);
    
    return 0; }
