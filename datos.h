#ifndef DATOS_H
#define DATOS_H

#include <string>
using namespace std;

// [OPTIMIZACION POR IA]
#define MAXP 100
#define MAXPED 50

// [VISTO EN CLASE]
const string ARCHP = "productos.txt";
const string ARCHPED = "pedido.txt";
const string CONTRA = "cafeteros123";

// [VISTO EN CLASE]
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

// [VISTO EN CLASE]
extern Producto menu[MAXP];
extern Orden carrito[MAXPED];
extern int totalMenu;
extern int totalCarrito;

//Funciones del sistema
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