#ifndef DATOS_H
#define DATOS_H

#include <string>
using namespace std;

// constantes
const int MAX_PRODUCTOS = 100;
const int MAX_PEDIDO    = 50;
const string ARCHIVO_PRODUCTOS = "productos.txt";
const string ARCHIVO_PEDIDO    = "pedido.txt";
const string ARCHIVO_FACTURA   = "factura.txt";
const string PASSWORD_CREADOR  = "admin123";

// estructuras para el sistema
struct Producto {
    string nombre;
    float  precio;
    int    cantidadActual;
};

struct ItemPedido {
    string nombreProducto;
    float  precioProducto;
    int    cantidadPedido;
};

// ARREGLOS
extern Producto   listaProductos[MAX_PRODUCTOS];
extern ItemPedido listaPedido[MAX_PEDIDO];
extern int        nProductos;
extern int        nPedido;

// utilidades
bool cargarProductosDesdeArchivo();
void guardarProductosEnArchivo();
bool abrirArchivoPedidoCorrectamente();
void escribirPedidoEnArchivo();

// menuCreador
void menuCreador();
void verProductos();
void agregarProducto();
void eliminarProducto();
void editarMenu();
void estimarProductos();

// menuCliente
void menuCliente();
void verCarta();
void agregarPedido();
void verCarrito();
void facturarYTodo();
void cancelarTodo();

#endif