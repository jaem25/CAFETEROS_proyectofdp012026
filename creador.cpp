#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "datos.h"
using namespace std;

void menuPrincipal() {
    int opcion = 0;

    while (opcion != 3) {
        cout << "\n================================\n";
        cout << "   SISTEMA DE CAFETERIA\n";
        cout << "================================\n";
        cout << "1) soy admin\n";
        cout << "2) soy cliente\n";
        cout << "3) salir\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                validarAdmin();
                break;
            case 2:
                menuCli();
                break;
            case 3:
                cout << "hasta luego :D\n";
                break;
            default:
                cout << "esa opcion no existe\n";
        }
    }
}

void validarAdmin() {
    cout << "ingrese la clave: ";
    string clave;
    getline(cin, clave);

    if (clave == CONTRA) {
        menuAdmin();
    } else {
        cout << "clave incorrecta\n";
    }
}

void menuAdmin() {
    int opcion = 0;

    while (opcion != 6) {
        cout << "\n====== MENU ADMIN ======\n";
        cout << "1) ver menu\n";
        cout << "2) agregar producto\n";
        cout << "3) quitar producto\n";
        cout << "4) editar producto\n";
        cout << "5) ver caja\n";
        cout << "6) salir\n";
        cout << "opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                verMenu();
                break;
            case 2:
                agregarProducto();
                break;
            case 3:
                quitarProducto();
                break;
            case 4:
                editarProducto();
                break;
            case 5:
                verCaja();
                break;
            case 6:
                break;
            default:
                cout << "esa opcion no existe\n";
        }
    }
}

void verMenu() {
    if (!cargarMenu()) {
        cout << "error al abrir el archivo\n";
        return;
    }
    if (totalMenu == 0) {
        cout << "no hay productos todavia\n";
        return;
    }

    cout << "\n-- lista del menu --\n";
    int i = 0;
    for (i = 0; i < totalMenu; i++) {
        cout << i + 1 << ") " << menu[i].nombre << "  precio: $" << fixed << setprecision(2) << menu[i].precio << "  stock: " << menu[i].cantidad << "\n";
    }
}

void agregarProducto() {
    cargarMenu();

    if (totalMenu >= MAXP) {
        cout << "ya no caben mas productos\n";
        return;
    }

    string nombre;
    float precio;
    int cantidad;

    cout << "nombre del producto: ";
    getline(cin, nombre);
    cout << "precio: ";
    cin >> precio;
    cout << "cantidad: ";
    cin >> cantidad;
    cin.ignore();

    int i = 0;
    bool yaExiste = false;
    for (i = 0; i < totalMenu; i++) {
        if (menu[i].nombre == nombre) {
            cout << "ese producto ya existe, se le suma el stock\n";
            menu[i].cantidad = menu[i].cantidad + cantidad;
            yaExiste = true;
        }
    }

    if (yaExiste == false) {
        menu[totalMenu].nombre = nombre;
        menu[totalMenu].precio = precio;
        menu[totalMenu].cantidad = cantidad;
        totalMenu = totalMenu + 1;
        cout << "producto agregado\n";
    }

    guardarMenu();
}

void quitarProducto() {
    if (!cargarMenu()) {
        cout << "error al abrir archivo\n";
        return;
    }
    if (totalMenu == 0) {
        cout << "no hay productos para quitar\n";
        return;
    }

    verMenu();
    cout << "cual producto quiere quitar (0 para cancelar): ";
    int numero;
    cin >> numero;
    cin.ignore();

    if (numero == 0) {
        return;
    }

    if (numero < 1 || numero > totalMenu) {
        cout << "numero invalido\n";
        return;
    }

    string nombreQuitado = menu[numero - 1].nombre;

    int i = 0;
    for (i = numero - 1; i < totalMenu - 1; i++) {
        menu[i] = menu[i + 1];
    }
    totalMenu = totalMenu - 1;

    guardarMenu();
    cout << "se quito: " << nombreQuitado << "\n";
}

void editarProducto() {
    if (!cargarMenu()) {
        cout << "error al abrir archivo\n";
        return;
    }
    if (totalMenu == 0) {
        cout << "no hay productos\n";
        return;
    }

    verMenu();
    cout << "cual producto quiere editar (0 para cancelar): ";
    int numero;
    cin >> numero;
    cin.ignore();

    if (numero == 0) {
        return;
    }

    if (numero < 1 || numero > totalMenu) {
        cout << "numero invalido\n";
        return;
    }

    cout << "nuevo nombre (enter para dejar igual): ";
    string nuevoNombre;
    getline(cin, nuevoNombre);
    if (nuevoNombre != "") {
        menu[numero - 1].nombre = nuevoNombre;
    }

    cout << "nuevo precio (0 para dejar igual): ";
    float nuevoPrecio;
    cin >> nuevoPrecio;
    cin.ignore();
    if (nuevoPrecio > 0) {
        menu[numero - 1].precio = nuevoPrecio;
    }

    guardarMenu();
    cout << "producto actualizado\n";
}

void verCaja() {
    if (!cargarMenu()) {
        cout << "error al abrir archivo\n";
        return;
    }
    if (totalMenu == 0) {
        cout << "no hay productos\n";
        return;
    }

    cout << "\n-- estimacion de inventario --\n";
    float totalValor = 0;
    int totalItems = 0;
    int i = 0;

    for (i = 0; i < totalMenu; i++) {
        float valorProducto = menu[i].precio * menu[i].cantidad;
        totalValor = totalValor + valorProducto;
        totalItems = totalItems + menu[i].cantidad;
        cout << menu[i].nombre << " | stock: " << menu[i].cantidad << " | valor: $" << fixed << setprecision(2) << valorProducto << "\n";
    }

    cout << "---\n";
    cout << "total de items: " << totalItems << "\n";
    cout << "valor total del inventario: $" << fixed << setprecision(2) << totalValor << "\n";
}