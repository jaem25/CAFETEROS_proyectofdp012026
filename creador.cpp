#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "datos.h"
using namespace std;

// // [VISTO EN CLASE]
void menuPrincipal() {
    int opcion = 0;

    while (opcion != 3) {
        cout << "\n================================\n";
        cout << "    SISTEMA DE CAFETERIA       \n";
        cout << "================================\n";
        cout << "1) Administrador\n";
        cout << "2) Cliente\n";
        cout << "3) Salir\n";
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
                cout << "Hasta luego... :D\n";
                break;
            default:
                cout << "Esa opcion no existe, intente nuevamente\n";
        }
    }
}

// [VISTO EN CLASE]
void validarAdmin() {
    cout << "Ingrese la clave: ";
    string clave;
    getline(cin, clave);

    if (clave == CONTRA) {
        menuAdmin();
    } else {
        cout << "Clave incorrecta\n";
    }
}

void menuAdmin() {
    int opcion = 0;

    while (opcion != 6) {
        cout << "\n====== MENU ADMIN ======\n";
        cout << "1) Ver menu\n";
        cout << "2) Agregar producto\n";
        cout << "3) Quitar/Eliminar producto\n";
        cout << "4) Editar producto\n";
        cout << "5) Ver inventario general\n";
        cout << "6) Salir\n";
        cout << "Ingrese una opcion: ";
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
                cout << "Esa opcion no existe\n";
        }
    }
}

// [VISTO EN CLASE]
void verMenu() {
    if (!cargarMenu()) {
        cout << "ERROR al abrir el archivo\n";
        return;
    }
    if (totalMenu == 0) {
        cout << "No hay productos todavia\n";
        return;
    }

    cout << "\n---- Lista del menu ----\n";
    int i = 0;
    for (i = 0; i < totalMenu; i++) {
        cout << i + 1 << ") " << menu[i].nombre << "  precio: $" << fixed << setprecision(2) << menu[i].precio << "  stock: " << menu[i].cantidad << "\n";
    }
}

// [VISTO EN CLASE]
void agregarProducto() {
    cargarMenu();

    if (totalMenu >= MAXP) {
        cout << "Ya no caben mas productos\n";
        return;
    }

    string nombre;
    float precio;
    int cantidad;

    cout << "Nombre del producto: ";
    getline(cin, nombre);
    cout << "Precio: ";
    cin >> precio;
    cout << "Cantidad en existencia: ";
    cin >> cantidad;
    cin.ignore();

    int i = 0;
    // [OPTIMIZACIÓN IA] - Uso de una bandera booleana para optimizar el control de existencia
    bool yaExiste = false; 
    for (i = 0; i < totalMenu; i++) {
        if (menu[i].nombre == nombre) {
            cout << "Ese producto ya existe, se le suma el stock\n";
            menu[i].cantidad = menu[i].cantidad + cantidad;
            yaExiste = true;
        }
    }

    if (yaExiste == false) {
        menu[totalMenu].nombre = nombre;
        menu[totalMenu].precio = precio;
        menu[totalMenu].cantidad = cantidad;
        totalMenu = totalMenu + 1;
        cout << "Producto agregado :)\n";
    }
    guardarMenu();
}

// [VISTO EN CLASE]
void quitarProducto() {
    if (!cargarMenu()) {
        cout << "ERROR al abrir archivo\n";
        return;
    }
    if (totalMenu == 0) {
        cout << "No hay productos para quitar\n";
        return;
    }

    verMenu();
    cout << "Cual producto desea eliminar? (presionar 0 para cancelar): ";
    int numero;
    cin >> numero;
    cin.ignore();

    if (numero == 0) {
        return;
    }

    if (numero < 1 || numero > totalMenu) {
        cout << "Numero invalido\n";
        return;
    }

    string nombreQuitado = menu[numero - 1].nombre;

    int i = 0;
    for (i = numero - 1; i < totalMenu - 1; i++) {
        menu[i] = menu[i + 1];
    }
    totalMenu = totalMenu - 1;

    guardarMenu();
    cout << "Se elimino: " << nombreQuitado << "\n";
}

void editarProducto() {
    if (!cargarMenu()) {
        cout << "ERROR al abrir archivo\n";
        return;
    }
    if (totalMenu == 0) {
        cout << "No hay productos\n";
        return;
    }

    verMenu();
    cout << "Cual producto desea editar? (presionar 0 para cancelar): ";
    int numero;
    cin >> numero;
    cin.ignore();

    if (numero == 0) {
        return;
    }

    if (numero < 1 || numero > totalMenu) {
        cout << "Numero invalido\n";
        return;
    }

    cout << "nuevo nombre (presione ENTER para dejarlo igual): ";
    string nuevoNombre;
    getline(cin, nuevoNombre);
    if (nuevoNombre != "") {
        menu[numero - 1].nombre = nuevoNombre;
    }

    cout << "Nuevo precio (presionar 0 para dejar igual): ";
    float nuevoPrecio;
    cin >> nuevoPrecio;
    cin.ignore();
    if (nuevoPrecio > 0) {
        menu[numero - 1].precio = nuevoPrecio;
    }

    guardarMenu();
    cout << "Producto actualizado\n";
}

// [VISTO EN CLASE]
void verCaja() {
    if (!cargarMenu()) {
        cout << "ERROR al abrir archivo\n";
        return;
    }
    if (totalMenu == 0) {
        cout << "No hay productos\n";
        return;
    }

    cout << "\n---- Inventario general de la cafeteria ----\n";
    float totalValor = 0;
    int totalItems = 0;
    int i = 0;

    for (i = 0; i < totalMenu; i++) {
        float valorProducto = menu[i].precio * menu[i].cantidad;
        totalValor = totalValor + valorProducto;
        totalItems = totalItems + menu[i].cantidad;
        cout << menu[i].nombre << " | stock: " << menu[i].cantidad << " | valor: $" << fixed << setprecision(2) << valorProducto << "\n";
    }
    cout << "--------------------------------------\n";
    cout << "Total de items de la cafeteria: " << totalItems << "\n";
    cout << "Valor total del inventario: $" << fixed << setprecision(2) << totalValor << "\n";
}