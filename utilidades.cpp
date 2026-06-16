#include <iostream>
#include <fstream>
#include <iomanip>
#include "datos.h"
using namespace std;

// DEFINICION de arreglos globales
// (declarados como extern en datos.h)
Producto   listaProductos[MAX_PRODUCTOS];
ItemPedido listaPedido[MAX_PEDIDO];
int        nProductos = 0;
int        nPedido    = 0;

// Carga productos desde archivo al arreglo global
bool cargarProductosDesdeArchivo() {
    nProductos = 0;
    ifstream archivo(ARCHIVO_PRODUCTOS);
    if (!archivo.is_open()) return false;

    string linea;
    while (getline(archivo, linea) && nProductos < MAX_PRODUCTOS) {
        // Formato de linea: nombre|precio|cantidad
        size_t p1 = linea.find('|');
        size_t p2 = linea.rfind('|');
        if (p1 == string::npos || p1 == p2) continue;

        listaProductos[nProductos].nombre         = linea.substr(0, p1);
        listaProductos[nProductos].precio         = stof(linea.substr(p1 + 1, p2 - p1 - 1));
        listaProductos[nProductos].cantidadActual = stoi(linea.substr(p2 + 1));
        nProductos++;
    }
    archivo.close();
    return true;
}

// Guarda arreglo global en archivo
void guardarProductosEnArchivo() {
    ofstream archivo(ARCHIVO_PRODUCTOS, ios::trunc);
    for (int i = 0; i < nProductos; i++) {
        archivo << listaProductos[i].nombre        << "|"
                << fixed << setprecision(2)
                << listaProductos[i].precio        << "|"
                << listaProductos[i].cantidadActual << "\n";
    }
    archivo.close();
}

// Verifica que el archivo de pedido se puede abrir
bool abrirArchivoPedidoCorrectamente() {
    ofstream prueba(ARCHIVO_PEDIDO, ios::app);
    if (!prueba.is_open()) return false;
    prueba.close();
    return true;
}

// Escribe el pedido actual en archivo
void escribirPedidoEnArchivo() {
    ofstream archivo(ARCHIVO_PEDIDO, ios::trunc);
    for (int i = 0; i < nPedido; i++) {
        archivo << listaPedido[i].nombreProducto << "|"
                << fixed << setprecision(2)
                << listaPedido[i].precioProducto << "|"
                << listaPedido[i].cantidadPedido << "\n";
    }
    archivo.close();
}