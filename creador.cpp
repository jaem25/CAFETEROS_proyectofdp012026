#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "datos.h"
using namespace std;

// Menu principal del creador
void menuCreador() {
    int opcionCreador = -1;

    while (opcionCreador != 0) {
        cout << "\n--- MENU CREADOR ---\n";
        cout << "1) Ver productos\n";
        cout << "2) Agregar productos\n";
        cout << "3) Eliminar producto\n";
        cout << "4) Editar menu\n";
        cout << "5) Estimar productos\n";
        cout << "0) Salir de menu creador\n";
        cout << "Opcion: ";
        cin  >> opcionCreador;
        cin.ignore();

        switch (opcionCreador) {
            case 1: verProductos();     break;
            case 2: agregarProducto();  break;
            case 3: eliminarProducto(); break;
            case 4: editarMenu();       break;
            case 5: estimarProductos(); break;
            case 0: break;
            default: cout << "ERROR: opcion invalida.\n";
        }
    }
}
// Ver todos los productos
void verProductos() {
    if (!cargarProductosDesdeArchivo()) {
        cout << "ERROR: no se pudo abrir productos.txt\n";
        return;
    }
    if (nProductos == 0) {
        cout << "No hay datos en el archivo.\n";
        return;
    }

    cout << "\n--- LISTA DE PRODUCTOS ---\n";
    cout << left << setw(5)  << "No."
                << setw(25) << "Nombre"
                << setw(12) << "Precio"
                << "Stock\n";
    cout << string(50, '-') << "\n";

    for (int i = 0; i < nProductos; i++) {
        cout << left << setw(5)  << (i + 1)
                    << setw(25) << listaProductos[i].nombre
                    << "$" << setw(11) << fixed << setprecision(2)
                    << listaProductos[i].precio
                    << listaProductos[i].cantidadActual << "\n";
    }
}
// Agregar un producto nuevo
void agregarProducto() {
    cargarProductosDesdeArchivo();

    if (nProductos >= MAX_PRODUCTOS) {
        cout << "Error: Memoria llena.\n";
        return;
    }

    string nombre;
    float  precio;
    int    cantidad;
    cout << "Nombre del producto: ";
    getline(cin, nombre);
    cout << "Precio: ";
    cin  >> precio;
    cout << "Cantidad inicial: ";
    cin  >> cantidad;
    cin.ignore();
    for (int i = 0; i < nProductos; i++) {
        if (listaProductos[i].nombre == nombre) {
            cout << "El producto ya existe. Actualizando stock.\n";
            listaProductos[i].cantidadActual += cantidad;
            guardarProductosEnArchivo();
            return;
        }
    }
    listaProductos[nProductos].nombre         = nombre;
    listaProductos[nProductos].precio         = precio;
    listaProductos[nProductos].cantidadActual = cantidad;
    nProductos++;
    guardarProductosEnArchivo();
    cout << "Producto agregado correctamente.\n";
}

// Eliminar un producto por numero
void eliminarProducto() {
    if (!cargarProductosDesdeArchivo() || nProductos == 0) {
        cout << "No hay productos para eliminar.\n";
        return;
    }

    verProductos();
    cout << "Numero de producto a eliminar (0 para cancelar): ";
    int idx;
    cin >> idx;
    cin.ignore();

    if (idx == 0) return;
    if (idx < 1 || idx > nProductos) {
        cout << "Numero invalido.\n";
        return;
    }

    string nombreEliminar = listaProductos[idx - 1].nombre;
    for (int i = idx - 1; i < nProductos - 1; i++) {
        listaProductos[i] = listaProductos[i + 1];
    }
    nProductos--;

    guardarProductosEnArchivo();
    cout << "Producto \"" << nombreEliminar << "\" eliminado.\n";
}

// Editar nombre o precio de un producto
void editarMenu() {
    if (!cargarProductosDesdeArchivo() || nProductos == 0) {
        cout << "No hay productos para editar.\n";
        return;
    }

    verProductos();
    cout << "Numero de producto a editar (0 para cancelar): ";
    int idx;
    cin >> idx;
    cin.ignore();

    if (idx == 0) return;
    if (idx < 1 || idx > nProductos) {
        cout << "Numero invalido.\n";
        return;
    }

    cout << "Nuevo nombre (enter para mantener \""
        << listaProductos[idx-1].nombre << "\"): ";
    string nuevoNombre;
    getline(cin, nuevoNombre);
    if (!nuevoNombre.empty())
        listaProductos[idx-1].nombre = nuevoNombre;

    cout << "Nuevo precio (0 para mantener "
        << listaProductos[idx-1].precio << "): ";
    float nuevoPrecio;
    cin  >> nuevoPrecio;
    cin.ignore();
    if (nuevoPrecio > 0)
        listaProductos[idx-1].precio = nuevoPrecio;
    guardarProductosEnArchivo();
    cout << "Producto actualizado.\n";
}

// Estimar valor total del inventario
void estimarProductos() {
    if (!cargarProductosDesdeArchivo() || nProductos == 0) {
        cout << "No hay productos.\n";
        return;
    }

    cout << "\n--- ESTIMACION DE INVENTARIO ---\n";
    float totalValor = 0.0f;
    int   totalItems = 0;

    for (int i = 0; i < nProductos; i++) {
        float valorProducto = listaProductos[i].precio
                            * listaProductos[i].cantidadActual;
        totalValor += valorProducto;
        totalItems += listaProductos[i].cantidadActual;

        cout << listaProductos[i].nombre
            << " | Stock: "      << listaProductos[i].cantidadActual
            << " | Valor: $"     << fixed << setprecision(2)
            << valorProducto     << "\n";
    }

    cout << "----\n"
        << "Total items: "   << totalItems
        << " | Valor total inventario: $"
        << fixed << setprecision(2) << totalValor << "\n";
}