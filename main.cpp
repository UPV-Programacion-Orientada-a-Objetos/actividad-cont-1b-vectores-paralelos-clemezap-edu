#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


// Arrays para almacenamiento de datos
int codigoProducto[100];
std::string nombreProducto[100];
int cantidadStock[100];
float precioUnitario[100];
std::string ubicacion[100];
int totalProductos = 0;

// Declaración de funciones
void llenadoProductosIniciales();
void consultaProducto();
void actualizarInventario();
void generarReporte();
void productoBarato();

int main() {
    
    // Se llama a la función para llenar el array de productos
    llenadoProductosIniciales();

    std::cout << "El ultimo es: " << codigoProducto[totalProductos-1] << std::endl; 

    
    int opcion = 0;

    std::cout << " - - - Bienvenido al Sistema de Inventario \"El Martillo\" - - -" << std::endl;

    do{

        std::cout << " - - - Menú principal - - - " << std::endl;
        std::cout << " " << std::endl;
        std::cout << "Selecciona una opción: " << std::endl;
        std::cout << " 1. Consultar un producto " << std::endl;
        std::cout << " 2. Actualizar inventario por ubicación " << std::endl;
        std::cout << " 3. Registrar nuevo producto " << std::endl;
        std::cout << " 4. Generar reporte de bajo stock " << std::endl;
        std::cout << " 5. Encontrar el producto más barato " << std::endl;
        std::cout << " 6. Guardar y salir " << std::endl;
        
        std::cin >> opcion;

        std::cout << "Opción seleccionada: " << opcion << std::endl;

        switch (opcion){
        case 1:
            consultaProducto();
            break;
        case 2:
            actualizarInventario();
            break;
        case 3:
            
            break;
        case 4:
            generarReporte();
            break;
        case 5:
            productoBarato();
            break;
        case 6:
            std::cout << "Guardando cambios . . ." << std::endl;
            // Lógica para guardar
            std::cout << "Saliendo . . ." << std::endl;
            break;
        default:
            std::cout << "Ingresa una opción válida " << std::endl;
            break;
        }
        
    } while (opcion != 6);


    return 0;
}

// Función para llenar los datos de los 5 productos iniciales
void llenadoProductosIniciales(){

    std::ifstream archivo("data/inventario.txt");
    std::string linea;

    // Si no existe el archivo crea uno y se le da formato al header
    if (!archivo.is_open()){
        std::cout << "No se encontró el archivo de inventario" << std::endl;
        std::cout << "Creando un archivo nuevo . . ." << std::endl;
        std::ofstream nuevoArchivo("data/inventario.txt");
        nuevoArchivo << "Código,Nombre,Cantidad,Precio,Ubicación" << std::endl;
        nuevoArchivo.close();
        return;
    }

    std::cout << "Cargando inventario desde 'inventarios.txt'..." << std::endl;

    // Lee la primera línea (encabezados) y no la almacena;
    std::getline(archivo, linea);

    // Realiza un ciclo mientras lea las lineas (renglones) del txt
    while (std::getline(archivo, linea)){

        // Variables para analizar la línea
        std::stringstream ss(linea);
        std::string dato;

        // Lógica para almacenar en código
        std::getline(ss, dato, ',');
        codigoProducto[totalProductos] = std::stoi(dato);

        // Lógica para almacenar el nombre
        std::getline(ss, dato, ',');
        nombreProducto[totalProductos] = dato;

        // Lógica para almacenar la cantidad
        std::getline(ss, dato, ',');
        cantidadStock[totalProductos] = std::stoi(dato);

        // Lógica para almacenar el precio
        std::getline(ss, dato, ',');
        precioUnitario[totalProductos] = std::stof(dato);

        // Lógica para almacenar la ubicación
        std::getline(ss, dato, '\n');
        ubicacion[totalProductos] = dato;

        totalProductos++;

    }

    std::cout << "Inventario cargado exitosamente. " << totalProductos << "productos encontrados." <<std::endl;

}

// Función para regresar los valores del producto
void consultaProducto(){

    int codigoConsulta = 0;
    bool existe = false;

    std::cout << "Ingresa el código del producto a consultar: " << std::endl;
    std::cin >> codigoConsulta;

    for (int i = 0; i < totalProductos; i ++){

        // Se hace una búsqueda y devuelve los resultados
        if (codigoProducto[i] == codigoConsulta){
            std::cout << "Código | Nombre                     | Cantidad en Stock  | Precio   |  Ubicación " << std::endl;
            std::cout << "------------------------------------------------------------------------------------" << std::endl;
            std::cout << codigoProducto[i] << " | " << nombreProducto[i] << " | " << cantidadStock[i] << " | " << precioUnitario[i] << " | " << ubicacion[i] <<std::endl;
            std::cout << "------------------------------------------------------------------------------------" << std::endl;
            existe = true;
            break;
        }
        
    }
    // Si no se activa la bandera "existe" significa que no existe el producto
    if (!existe){
        std::cout << "No se encontró ningún producto con ese código" << std::endl;
    }

}

// Función para actualizara inventario
void actualizarInventario(){

    std::string ubicacionConsulta;
    int indice = 0;
    bool existe = false;
    bool paso = false;
    int cantidadActualizar = 0;

    std::cout << "Ingresa la ubicación del producto a consultar: " << std::endl;
    std::cin >> ubicacionConsulta;

    for (int i = 0; i < totalProductos; i++){
        // Se hace la búsqueda del producto mediante la ubicación y activa la bandera si exsite
        if (ubicacion[i] == ubicacionConsulta){
            indice = i;
            existe = true;
            break;
        }
    }

    // Si la bandera esta desactivada lo imprime y no continúa la lógica de actualización
    if (!existe){
        std::cout << "No se encontró ningún producto con esta ubicación" << std::endl;
    } else {
        // Si entra a esta sección, se valida que se ingrese una cantidad que no de menor a 0 mediante un do-while
        do{
            std::cout << "Ingresa la cantidad a actualizar" << std::endl;
            std::cin >> cantidadActualizar;

            std::cout << cantidadStock[indice] << " + " << cantidadActualizar << " = " << (cantidadStock[indice] + cantidadActualizar) << std::endl;

            if ((cantidadStock[indice] + cantidadActualizar) < 0){
                std::cout << "No puedes tener cantidades negativas de stock" << std::endl;
            } else {
                cantidadStock[indice] += cantidadActualizar;
                std::cout << "¡Cantidad actualizada!" << std::endl;
                std::cout << "Cantidad actual: " << cantidadStock[indice] << std::endl;
                paso = true;
            }

        } while (!paso);
    }

}

// Función para generar reportes
void generarReporte(){

    std::cout << " - - - Reporte de Inventario - - - " << std::endl;
    
    std::cout << "Código   | Nombre               | Stock | Precio     " << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;

    for (int i = 0; i < totalProductos; i ++){
        // Se buscan e imprimen las casillos no vacías de los arrays
        if (cantidadStock[i] <=  10){
            std::cout << codigoProducto[i] << "      | " << nombreProducto[i] << " | " << cantidadStock[i] << "   | $" << precioUnitario[i] << std::endl;
        }
    }
    std::cout << "-----------------------------------------------------" << std::endl;
    
}

// Función para buscar el producto más caro
void productoBarato(){
    
    int indiceProducto = 0;
    float precioMenor = precioUnitario[0];

    for (int i = 0; i < totalProductos; i++ ){
        // Se almacena en la variable precioMenor los valores que sean menores al anterior, hasta llegar al último.
        if (precioUnitario[i] < precioMenor){
            precioMenor = precioUnitario[i];
            indiceProducto = i;
        }
    }

    std::cout << "El producto más barato es: " << nombreProducto[indiceProducto] << " con un precio de $" << precioUnitario[indiceProducto] << std::endl;

}