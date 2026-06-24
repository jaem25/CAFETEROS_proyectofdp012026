#include <iostream>
#include <fstream>
#include <iomanip>
#include "datos.h"
using namespace std;

Producto menu[MAXP];
Orden carrito[MAXPED];
int totalMenu = 0;
int totalCarrito = 0;

bool cargarMenu() {
    totalMenu = 0;
    ifstream archivo(ARCHP);
    if (!archivo.is_open()) {
        return false;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (totalMenu >= MAXP) {
            break;
        }

        int pos1 = linea.find('|');
        int pos2 = linea.rfind('|');

        if (pos1 == -1 || pos1 == pos2) {
            continue;
        }

        menu[totalMenu].nombre = linea.substr(0, pos1);
        menu[totalMenu].precio = stof(linea.substr(pos1 + 1, pos2 - pos1 - 1));
        menu[totalMenu].cantidad = stoi(linea.substr(pos2 + 1));
        totalMenu = totalMenu + 1;
    }
    archivo.close();
    return true;
}

void guardarMenu() {
    ofstream archivo(ARCHP, ios::trunc);
    int i = 0;
    for (i = 0; i < totalMenu; i++) {
        archivo << menu[i].nombre << "|" << fixed << setprecision(2) << menu[i].precio << "|" << menu[i].cantidad << "\n";
    }
    archivo.close();
}

bool abrirCarrito() {
    ofstream archivo(ARCHPED, ios::app);
    if (!archivo.is_open()) {
        return false;
    }
    archivo.close();
    return true;
}

void guardarCarrito() {
    ofstream archivo(ARCHPED, ios::trunc);
    int i = 0;
    for (i = 0; i < totalCarrito; i++) {
        archivo << carrito[i].nombre << "|" << fixed << setprecision(2) << carrito[i].precio << "|" << carrito[i].cantidadPedida << "\n";
    }
    archivo.close();
}