#ifndef DATOS_H
#define DATOS_H

#include <string>
using namespace std;

#define MAXP 100
#define MAXPED 50

const string ARCHP = "productos.txt";
const string ARCHPED = "pedido.txt";
const string ARCHFAC = "factura.txt";
const string CONTRA = "cafeteros123";

struct Producto {
    string nombre;
    float precio;
    int cantidad;
};

struct Orden {
    string nombre;
    float precio;
    int cantidadPedida;
};

extern Producto menu[MAXP];
extern Orden carrito[MAXPED];
extern int totalMenu;
extern int totalCarrito;

bool cargarMenu();
void guardarMenu();
bool abrirCarrito();
void guardarCarrito();

void menuPrincipal();
void validarAdmin();

void menuAdmin();
void verMenu();
void agregarProducto();
void quitarProducto();
void editarProducto();
void verCaja();

void menuCli();
void verCarta();
void hacerOrden();
void verCarrito();
void cobrar();
void cancelarOrden();

#endif