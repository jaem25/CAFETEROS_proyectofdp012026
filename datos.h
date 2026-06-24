#ifndef DATOS_H
#define DATOS_H

#include <string>
using namespace std;

#define MAXP 100
#define MAXPED 50

const string ARCHP = "productos.txt";
const string ARCHPED = "pedido.txt";
const string ARCHCONT = "contador.txt";
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
extern int contadorFacturas;

bool cargarMenu();
void guardarMenu();
bool abrirCarrito();
void guardarCarrito();
void cargarContador();
void guardarContador();

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