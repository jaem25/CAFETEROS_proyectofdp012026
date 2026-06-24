#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "datos.h"
using namespace std;

void menuCli() {
    totalCarrito = 0;

    if (!cargarMenu()) {
        cout << "error no se pudo abrir productos.txt\n";
        return;
    }
    if (totalMenu == 0) {
        cout << "no hay productos disponibles\n";
        return;
    }
    if (!abrirCarrito()) {
        cout << "error con el archivo de pedido\n";
        return;
    }

    cargarContador();

    int opcion = 0;

    while (opcion != 5) {
        cout << "\n";
        cout << "================================\n";
        cout << "||                            ||\n";
        cout << "||      CAFETEROS.UCA         ||\n";
        cout << "||                            ||\n";
        cout << "================================\n";
        cout << "1) ver carta\n";
        cout << "2) hacer pedido\n";
        cout << "3) ver carrito\n";
        cout << "4) cobrar\n";
        cout << "5) cancelar y salir\n";
        cout << "opcion: ";
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
                cout << "esa opcion no existe\n";
        }
    }
}

void verCarta() {
    cout << "\n-- carta --\n";
    bool haySomthing = false;
    int i = 0;

    for (i = 0; i < totalMenu; i++) {
        if (menu[i].cantidad > 0) {
            cout << i + 1 << ") " << menu[i].nombre << "  $" << fixed << setprecision(2) << menu[i].precio << "  (quedan: " << menu[i].cantidad << ")\n";
            haySomthing = true;
        }
    }

    if (haySomthing == false) {
        cout << "no hay nada disponible por ahora\n";
    }
}

void hacerOrden() {
    if (totalMenu == 0) {
        cout << "no hay productos\n";
        return;
    }

    verCarta();

    cout << "numero del producto (0 para cancelar): ";
    int numero;
    cin >> numero;
    cin.ignore();

    if (numero == 0) {
        return;
    }

    if (numero < 1 || numero > totalMenu) {
        cout << "ese numero no existe\n";
        return;
    }
    if (menu[numero - 1].cantidad <= 0) {
        cout << "ese producto no tiene stock\n";
        return;
    }

    cout << "cuantos quiere pedir: ";
    int cantidad;
    cin >> cantidad;
    cin.ignore();

    if (cantidad <= 0) {
        cout << "cantidad no valida\n";
        return;
    }
    if (cantidad > menu[numero - 1].cantidad) {
        cout << "no hay suficiente stock hay: " << menu[numero - 1].cantidad << "\n";
        return;
    }

    cout << "agregar " << cantidad << " x " << menu[numero - 1].nombre << " si o no (s/n): ";
    char respuesta;
    cin >> respuesta;
    cin.ignore();

    if (respuesta != 's' && respuesta != 'S') {
        cout << "ok cancelado\n";
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
            cout << "el carrito esta lleno\n";
            return;
        }
        carrito[totalCarrito].nombre = menu[numero - 1].nombre;
        carrito[totalCarrito].precio = menu[numero - 1].precio;
        carrito[totalCarrito].cantidadPedida = cantidad;
        totalCarrito = totalCarrito + 1;
    }

    menu[numero - 1].cantidad = menu[numero - 1].cantidad - cantidad;

    guardarCarrito();
    cout << "agregado al carrito\n";
}

void verCarrito() {
    if (totalCarrito == 0) {
        cout << "el carrito esta vacio\n";
        return;
    }

    cout << "\n-- carrito --\n";
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
        cout << "no hay nada en el carrito\n";
        return;
    }

    string nombreArchivo = "factura" + to_string(contadorFacturas) + ".txt";

    ofstream factura(nombreArchivo);
    if (!factura.is_open()) {
        cout << "error al generar factura\n";
        return;
    }

    float totalNeto = 0;
    float descuento = 0;
    float totalFinal = 0;
    int i = 0;

    factura << "================================\n";
    factura << "  FACTURA No. " << contadorFacturas << "\n";
    factura << "  CAFETEROS.UCA\n";
    factura << "================================\n";

    for (i = 0; i < totalCarrito; i++) {
        float subtotal = carrito[i].precio * carrito[i].cantidadPedida;
        totalNeto = totalNeto + subtotal;
        factura << carrito[i].nombre << " x" << carrito[i].cantidadPedida << "  $" << fixed << setprecision(2) << carrito[i].precio << "  = $" << subtotal << "\n";
    }

    if (totalNeto > 10.0) {
        descuento = totalNeto * 0.10;
        factura << "descuento 10%: -$" << fixed << setprecision(2) << descuento << "\n";
    }

    totalFinal = totalNeto - descuento;

    factura << "--------------------------------\n";
    factura << "total neto:    $" << fixed << setprecision(2) << totalNeto << "\n";
    factura << "total a pagar: $" << fixed << setprecision(2) << totalFinal << "\n";
    factura << "================================\n";
    factura.close();

    contadorFacturas = contadorFacturas + 1;
    guardarContador();

    guardarMenu();

    cout << "\nfactura generada (" << nombreArchivo << ")\n";
    cout << "total a pagar: $" << fixed << setprecision(2) << totalFinal << "\n";

    totalCarrito = 0;
    ofstream limpiar(ARCHPED);
    limpiar.close();
}

void cancelarOrden() {
    if (totalCarrito == 0) {
        cout << "el carrito ya esta vacio\n";
        return;
    }

    cout << "seguro que quiere cancelar (s/n): ";
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
    ofstream limpiar(ARCHPED);
    limpiar.close();

    cout << "pedido cancelado stock devuelto\n";
}