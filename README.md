# CAFETEROS_proyectofdp012026

# Descripción del sistema
El sistema de cafetería de nuestro proyecto llamado “Cafeteros.uca” es un sistema que tiene como finalidad el control de una cafetería dentro del campus universitario, teniendo una estructura en la que dividimos el programa en dos formas de uso distintas, dependiendo del rol o quien este manejando el sistema, está el de “Administrador” (resaltar que la contraseña para ingresar es: cafeteros123) y el de “Cliente”.

# Objetivo del proyecto 
El objetivo de este proyecto es automatizar un sistema de comida universitaria que controle el funcionamiento básico de la cafetería dentro del entorno universitario, permitiendo a los usuarios consultar el menú de productos disponibles, realizar pedidos, visualizar sus selecciones, modificar compras y calcular el total a pagar. El proyecto busca brindar una experiencia de interacción sencilla y ordenada mediante menús y opciones intuitivas, al mismo tiempo que permite aplicar de forma práctica los conocimientos adquiridos en la asignatura. 

# Reglas y funcionamiento del sistema 
-Al iniciar el programa, se debe seleccionar el tipo de acceso: administrador o cliente.
-Para acceder como administrador, se debe ingresar la clave correcta ("cafeteros123"); de lo contrario, el acceso será denegado. 
-El cliente solo puede pedir productos que tengan stock disponible; no se permiten pedidos que superen la cantidad existente. 
-Cada producto pedido se descuenta automáticamente del inventario al momento de agregarlo al carrito. 
-Si el cliente cancela su pedido, el sistema devuelve al inventario las cantidades que había apartado. 
-Si el total de la compra supera los $10.00, se aplica un descuento automático del 10% sobre el monto final. 
-Todas las opciones ingresadas en los menús son validadas; si la opción no existe, el sistema lo indica y vuelve a mostrar el menú. 
-El menú del administrador cuenta con las opciones: ver menú, agregar producto, quitar producto, editar producto, ver inventario y salir. 
-El menú del cliente cuenta con las opciones: ver carta, hacer pedido, ver carrito, cobrar y cancelar pedido. 
-El programa permanece en ejecución hasta que el usuario o administrador elige la opción de salir. 
-El inventario y los pedidos se guardan en archivos de texto, por lo que la información no se pierde al cerrar el programa. 
-Cada compra finalizada genera un archivo de factura individual y numerado de forma automática. 
