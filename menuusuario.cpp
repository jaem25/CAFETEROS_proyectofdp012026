#include <iostream>
using namespace std;
int main()
{
    int opcion, categoria, respuesta = 2;

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
                do
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
                        case 2:
                            cout << "\n======ALMUERZOS======" << endl;
                            cout << "1. Pollo a la plancha----$4.50" << endl;
                            cout << "2. Hamburguesa con papas----$4.00" << endl;
                            cout << "3. Pizza personal----$3.50" << endl;
                            cout << "4. Tacos de pollo----$3.00" << endl;
                            cout << "5. Casamiento con carne----$4.50" << endl;
                            break;
                        case 3:
                            cout << "\n======CENAS======" << endl;
                            cout << "1. Sandwich de pollo----$3.00" << endl;
                            cout << "2. Hot Dog----$2.50" << endl;
                            cout << "3. Ensalada de pollo----$3.50" << endl;
                            cout << "4. Burrito de pollo----$3.50" << endl;
                            cout << "5. Nachos con queso----$2.50" << endl;
                            break;
                        case 4:
                            cout << "\n======SNACKS======" << endl;
                            cout << "1. Galletas----$0.75" << endl;
                            cout << "2. Chocolate----$1.00" << endl;
                            cout << "3. Papitas----$1.25" << endl;
                            cout << "4. Dona----$1.00" << endl;
                            cout << "5. Pastelito de piña----$1.50" << endl;
                            break;
                        case 5:
                            cout << "\n======BEBIDAS======" << endl;
                            cout << "1. Agua embotellada----$0.75" << endl;
                            cout << "2. Soda----$1.00" << endl;
                            cout << "3. Café----$1.00" << endl;
                            cout << "4. Jugo natural----$1.50" << endl;
                            cout << "5. Te frio----$1.25" << endl;
                            break;
                        }
                        cout << "\nDesea ver otra categoria?" << endl;
                        cout << "1. Si" << endl;
                        cout << "2. No" << endl;
                        cin >> respuesta;
                    }

                } while (respuesta == 1);
            }

            break;
            }
        }

    } while (opcion != 6);

    return 0;
}
