#include <iostream>
using namespace std;

int main()
{
    int opcion = 0, categoria = 0, respuesta;

    do
    {
        cout << "\n======MENU USUARIO======" << endl;
        cout << "1. Ver menu" << endl;
        cout << "2. Hacer pedido" << endl;
        cout << "3. Ver pedido" << endl;
        cout << "4. Calcular total" << endl;
        cout << "5. Modificar pedido" << endl;
        cout << "6. Salir" << endl;
        cin >> opcion;

        if (opcion < 1 || opcion > 6)
        {
            cout << "Opcion invalida" << endl;
        }
        else
        {
            switch (opcion)
            {
            case 1:
            {
                cout << "\n======CATEGORIAS======" << endl;
                cout << "1. Desayunos" << endl;
                cout << "2. Almuerzos" << endl;
                cout << "3. Cenas" << endl;
                cout << "4. Snacks" << endl;
                cout << "5. Bebidas" << endl;
                cin >> categoria;
                if (categoria < 1 || categoria > 5)
                {
                    cout << "Categoria invalida" << endl;
                }
                else
                {
                    switch (categoria)
                    {
                    case 1:
                        cout << "\n======DESAYUNOS======" << endl;
                        cout << "1. Desayuno tipico----$3.50" << endl;
                        cout << "2. Pan con huevo----$1.50" << endl;
                        cout << "3. Pan con frijoles y queso----$2.00" << endl;
                        cout << "4. Pancakes----$2.50" << endl;
                        cout << "5. Sandwich de jamon----$2.50" << endl;
                        break;
                    default:
                        cout << "Opcion de desayuno no implementada." << endl;
                        break;
                    }
                }
                break;
            }
            case 2:
                // HACER PEDIDO
                break;
            case 3:
                // VER PEDIDO
                break;
            case 4:
                // CALCULAR TOTAL
                break;
            case 5:
                // MODIFICAR PEDIDO
                break;
            case 6:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion no implementada aun." << endl;
                break;
            }
        }

    } while (opcion != 6);

    return 0;
}
