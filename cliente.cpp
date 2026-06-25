#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "datos.h"
using namespace std;

void menuCli() {
    totalCarrito = 0;

    if (!cargarMenu()) {
        cout << "ERROR no se pudo abrir productos.txt\n";
        return;
    }
    if (totalMenu == 0) {
        cout << "No hay productos disponibles\n";
        return;
    }
    if (!abrirCarrito()) {
        cout << "ERROR con el archivo de pedido\n";
        return;
    }

    int opcion = 0;

    while (opcion != 5) {
        cout << "\n";
        cout << "================================\n";
        cout << "||                            ||\n";
        cout << "||       CAFETEROS.UCA        ||\n";
        cout << "||                            ||\n";
        cout << "================================\n";
        cout << "1) Ver menu\n";
        cout << "2) Hacer pedido\n";
        cout << "3) Ver carrito\n";
        cout << "4) Cobrar y hacer factura\n";
        cout << "5) Cancelar pedido y salir\n";
        cout << "Ingrese un opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                verCarta();
                break;
            case 2:
                hacerOrden();
                break;
            case 3:
                verCarrito();
                break;
            case 4:
                cobrar();
                opcion = 5;
                break;
            case 5:
                cancelarOrden();
                break;
            default:
                cout << "Esa opcion no existe\n";
        }
    }
}

void verCarta() {
    cout << "\n------ carta ------\n";
    bool haySomthing = false;
    int i = 0;

    for (i = 0; i < totalMenu; i++) {
        if (menu[i].cantidad > 0) {
            cout << i + 1 << ") " << menu[i].nombre << "  $" << fixed << setprecision(2) << menu[i].precio << "  (quedan: " << menu[i].cantidad << ")\n";
            haySomthing = true;
        }
    }

    if (haySomthing == false) {
        cout << "No hay nada disponible por ahora\n";
    }
}

// [VISTO EN CLASE]
void hacerOrden() {
    if (totalMenu == 0) {
        cout << "No hay productos\n";
        return;
    }

    verCarta();

    cout << "Ingrese numero del producto (presione 0 para cancelar): ";
    int numero;
    cin >> numero;
    cin.ignore();

    if (numero == 0) {
        return;
    }

    if (numero < 1 || numero > totalMenu) {
        cout << "Ese numero no existe\n";
        return;
    }
    if (menu[numero - 1].cantidad <= 0) {
        cout << "Ese producto no tiene stock, lo sentimos :(\n";
        return;
    }

    cout << "Cuantos desea pedir: ";
    int cantidad;
    cin >> cantidad;
    cin.ignore();

    if (cantidad <= 0) {
        cout << "Cantidad no valida\n";
        return;
    }
    if (cantidad > menu[numero - 1].cantidad) {
        cout << "No hay suficiente stock hay: " << menu[numero - 1].cantidad << "\n";
        return;
    }

    cout << "Agregar " << cantidad << " x " << menu[numero - 1].nombre << " si o no (s/n): ";
    char respuesta;
    cin >> respuesta;
    cin.ignore();

    if (respuesta != 's' && respuesta != 'S') {
        cout << "Okey, cancelando...\n";
        return;
    }

    bool yaEsta = false;
    int i = 0;
    for (i = 0; i < totalCarrito; i++) {
        if (carrito[i].nombre == menu[numero - 1].nombre) {
            carrito[i].cantidadPedida = carrito[i].cantidadPedida + cantidad;
            yaEsta = true;
        }
    }

    if (yaEsta == false) {
        if (totalCarrito >= MAXPED) {
            cout << "El carrito esta lleno\n";
            return;
        }
        carrito[totalCarrito].nombre = menu[numero - 1].nombre;
        carrito[totalCarrito].precio = menu[numero - 1].precio;
        carrito[totalCarrito].cantidadPedida = cantidad;
        totalCarrito = totalCarrito + 1;
    }

    menu[numero - 1].cantidad = menu[numero - 1].cantidad - cantidad;

    guardarCarrito();
    cout << "Agregado al carrito\n";
}

void verCarrito() {
    if (totalCarrito == 0) {
        cout << "El carrito esta vacio\n";
        return;
    }

    cout << "\n------ carrito ------\n";
    float totalCompra = 0;
    int i = 0;

    for (i = 0; i < totalCarrito; i++) {
        float subtotal = carrito[i].precio * carrito[i].cantidadPedida;
        totalCompra = totalCompra + subtotal;
        cout << i + 1 << ") " << carrito[i].nombre << " x" << carrito[i].cantidadPedida << "  $" << fixed << setprecision(2) << carrito[i].precio << "  subtotal: $" << subtotal << "\n";
    }
    cout << "total: $" << fixed << setprecision(2) << totalCompra << "\n";
}
void cobrar() {
    if (totalCarrito == 0) {
        cout << "No hay nada en el carrito\n";
        return;
    }

    // // [VISTO EN CLASE]
    int numeroFactura = 0;
    ifstream archivoNumero("num_factura.txt");
    if (archivoNumero.is_open()) {
        archivoNumero >> numeroFactura;
        archivoNumero.close();
    }
    numeroFactura = numeroFactura + 1;

    // // [OPTIMIZACIÓN IA] - Concatenación de strings dinámica usando to_string para generar archivos únicos
    string nombreFactura = "factura" + to_string(numeroFactura) + ".txt";

    // // [OPTIMIZACIÓN IA] - Apertura en modo ios::out para garantizar un archivo de factura limpio e independiente
    ofstream factura(nombreFactura, ios::out);
    if (!factura.is_open()) {
        cout << "error al generar factura\n";
        return;
    }

    float totalNeto = 0;
    float descuento = 0;
    float totalFinal = 0;
    int i = 0;

    // // [VISTO EN CLASE]
    factura << "\n================================\n";
    factura << "          FACTURA No. " << numeroFactura << "\n";
    factura << "          CAFETEROS.UCA       \n";
    factura << "================================\n";

    for (i = 0; i < totalCarrito; i++) {
        float subtotal = carrito[i].precio * carrito[i].cantidadPedida;
        totalNeto = totalNeto + subtotal;
        factura << carrito[i].nombre << " x" << carrito[i].cantidadPedida << "  $" << fixed << setprecision(2) << carrito[i].precio << "  = $" << subtotal << "\n";
    }

    // // [VISTO EN CLASE] 
    if (totalNeto > 10.0) {
        descuento = totalNeto * 0.10;
        factura << "Descuento del 10%: -$" << fixed << setprecision(2) << descuento << "\n";
    }

    totalFinal = totalNeto - descuento;

    factura << "--------------------------------\n";
    factura << "Total neto:    $" << fixed << setprecision(2) << totalNeto << "\n";
    factura << "Total a pagar: $" << fixed << setprecision(2) << totalFinal << "\n";
    factura << "--------------------------------\n";
    factura.close();
    ofstream archivoGuardar("num_factura.txt");
    archivoGuardar << numeroFactura;
    archivoGuardar.close();
    guardarMenu();

    cout << "\nFactura generada (" << nombreFactura << ")\n";
    cout << "Total a pagar: $" << fixed << setprecision(2) << totalFinal << "\n";

    // [VISTO EN CLASE]
    totalCarrito = 0;
    ofstream limpiar(ARCHPED, ios::trunc);
    limpiar.close();
}

// [VISTO EN CLASE]
void cancelarOrden() {
    if (totalCarrito == 0) {
        cout << "El carrito ya esta vacio\n";
        return;
    }

    cout << "Seguro que desea cancelar? (s/n): ";
    char respuesta;
    cin >> respuesta;
    cin.ignore();

    if (respuesta != 's' && respuesta != 'S') {
        return;
    }

    int i = 0;
    int j = 0;
    for (i = 0; i < totalCarrito; i++) {
        for (j = 0; j < totalMenu; j++) {
            if (menu[j].nombre == carrito[i].nombre) {
                menu[j].cantidad = menu[j].cantidad + carrito[i].cantidadPedida;
            }
        }
    }

    guardarMenu();
    totalCarrito = 0;
    ofstream limpiar(ARCHPED, ios::trunc);
    limpiar.close();

    cout << "Pedido cancelado stock devuelto\n";
}