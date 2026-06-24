#include <iostream>
#include <fstream>
#include <iomanip>
#include "datos.h"
using namespace std;

Producto menu[MAXP];
Orden carrito[MAXPED];
int totalMenu = 0;
int totalCarrito = 0;
int contadorFacturas = 1;

bool cargarMenu() {
    totalMenu = 0;
    ifstream archivo(ARCHP);
    if (!archivo.is_open()) {
        return false;
    }

    while (archivo >> menu[totalMenu].nombre >> menu[totalMenu].precio >> menu[totalMenu].cantidad) {
        totalMenu = totalMenu + 1;
        if (totalMenu >= MAXP) {
            break;
        }
    }
    archivo.close();
    return true;
}

void guardarMenu() {
    ofstream archivo(ARCHP);
    int i = 0;
    for (i = 0; i < totalMenu; i++) {
        archivo << menu[i].nombre << " " << fixed << setprecision(2) << menu[i].precio << " " << menu[i].cantidad << "\n";
    }
    archivo.close();
}

bool abrirCarrito() {
    ofstream archivo(ARCHPED);
    if (!archivo.is_open()) {
        return false;
    }
    archivo.close();
    return true;
}

void guardarCarrito() {
    ofstream archivo(ARCHPED);
    int i = 0;
    for (i = 0; i < totalCarrito; i++) {
        archivo << carrito[i].nombre << " " << fixed << setprecision(2) << carrito[i].precio << " " << carrito[i].cantidadPedida << "\n";
    }
    archivo.close();
}

void cargarContador() {
    ifstream archivo(ARCHCONT);
    if (archivo.is_open()) {
        archivo >> contadorFacturas;
        archivo.close();
    } else {
        contadorFacturas = 1;
    }
}

void guardarContador() {
    ofstream archivo(ARCHCONT);
    archivo << contadorFacturas;
    archivo.close();
}