#include <iostream>
#include<string>
using namespace std;


int const MAX = 500; //Dimension fisica.

//---------------------------------DECLARACION DE STRUCTS----------------------------------------------



struct Pac
{
   long long int dni;
   string nombre;
   string apellido;
   long long int telefono;
};


struct Med
{
    int codigo;
    string nombre;
    string descripcion;
};


struct Tur
{
    long long int codigo;//codigo automatico del turno
    string fecha;
    int hora;
    long long int paciente;//DNI del Paciente
    int especialidad;//Codigo de la especialidad medica
    int estado;// 1. Activo, 2. Cancelado
    Tur* siguiente;
};



//-------------------------------------DECLARACION DE FUNCIONES-------------------------------------


int buscarPaciente (int dni, Pac listaPac[], int dimLPac) //esta funcion sirve para verificar si el DNI existe o no
{
    for (int i = 0; i<dimLPac; i++) //Recorre todo el arreglo de pacientes.
    {
        if(dni == listaPac[i].dni)//comparamos la entrada con cada valor de la lista de pacientes.
        {
              return i; //Retorna la posicion del paciente en el arreglo si se encuentra.
        }
    }
    return -1; //Retorna -1 si no se encuentra ningun paciente.
}


void quitarElementoArregloPac (int posArreglo, int &dimLPac, Pac listaPac[]) //Recibe una posicion como argumento y quita al elemento correspondiente del arreglo Pacientes.
{
    for(int i = posArreglo; i < dimLPac-1; i++)
    {
        listaPac[i] = listaPac[i+1]; //Realiza el corrimiento quitando al paciente del arreglo.
    }
    dimLPac--; //Disminuye la dimension logica del arreglo.
}


void quitarElementoArregloMed (int posArreglo, int &dimLMed, Med listaMed[]) //Recibe una posicion como argumento y quita al elemento correspondiente del arreglo Especialidades Medicas.
{
    for(int i = posArreglo; i < dimLMed-1; i++)
    {
        listaMed[i] = listaMed[i+1]; //Realiza el corrimiento quitando a la especialidad del arreglo.
    }
    dimLMed--; //Disminuye la dimension logica del arreglo.
}


int buscarMed (int codigoIngresado, Med listaMed[], int DimLMed) //Analiza si existe la especialidad.
{
    for (int i = 0; i<DimLMed; i++)
    {
        if(codigoIngresado == listaMed[i].codigo)
        {
            return i; //Retorna la posicion de la especialidad medica en el arreglo si la especialidad existe.
        }
    }
    return -1; //Retorna -1 si la especialidad no existe.
}


void mostrarMed(int posArreglo, Med listaMed[]) //Dada una posicion te imprime la especialidad medica.
{
    cout << "Nombre de la especialidad medica: " << listaMed[posArreglo].nombre << endl;
    cout << "Descripcion: " << listaMed[posArreglo].descripcion << endl;
    cout << "Codigo: " << listaMed[posArreglo].codigo << endl << endl;
}


void mostrarTurDni(Tur* inicio, int dniPac) //Imprime los datos de un nodo de la lista de turnos filtrando por DNI (solo muestra turnos activos).
{
    Tur* aux = inicio; //Crea nodo auxiliar igual al puntero inicio para no perderlo.
    while(aux != nullptr) //Recorre hasta que se encuentre con el ultimo nodo de la lista.
    {
        if (aux->paciente == dniPac && aux->estado != 2)
        {
            cout << "Codigo del Turno: " << aux->codigo << endl << endl;

            cout << "DNI: " << aux->paciente << endl;
            cout << "Especialidad Medica: " << aux->especialidad << endl;
            cout << "Fecha: " << aux->fecha << endl;
            cout << "Hora: " << aux->hora << endl;
            cout << "Estado(1 activo, 2 cancelado): " << aux->estado << endl << endl << endl;
        }
        aux = aux->siguiente;
    }
}


int contarTurDni(Tur* inicio, int dniPac) //Cuenta la cantidad de turnos activos que tiene un mismo paciente.
{
    Tur* aux = inicio;
    int dniEncontrado = 0;

    while(aux != nullptr) //Recorre hasta que encuentre el ultimo nodo en la lista
    {
        if(aux->paciente == dniPac && aux->estado == 1) //Cuenta turno solo si el estado es activo.
        {
            dniEncontrado++;
        }

        aux = aux->siguiente;
    }

    return dniEncontrado;
}


void mostrarPac(int posArreglo, Pac listaPac[]) //Dada una posicion te imprime los datos del paciente.
{

    cout << "DNI: " << listaPac[posArreglo].dni << endl;
    cout << "Nombre: " << listaPac[posArreglo].nombre << endl ;
    cout << "Apellido: " << listaPac[posArreglo].apellido << endl ;
    cout << "Telefono: " << listaPac[posArreglo].telefono << endl << endl;

}


bool buscarTurRepetido (int codeEsp, int dniPac, Tur* inicio) //Busca si un paciente y una especialidad medica tienen un turno activo.
{
    for (Tur* aux = inicio; aux != nullptr; aux = aux->siguiente) //Creo una variable turno auxiliar para no perder la variable inicio.
    {
        if (codeEsp == aux->especialidad && dniPac == aux->paciente && aux->estado == 1)
        {
            return false; //Retorna false si ambas especialidad medica y paciente tienen mismo turno.
        }
    }
    return true; //Retorna true si no tienen turno.
}


Tur* insertarFinal(Tur* inicio, Tur* nuevo) //Toma el puntero inicio y un nodo nuevo y agrega el nuevo nodo al final de la lista.
{
    if(inicio == nullptr) //Si el puntero inicio es nullptr entonces se esta agregando el primer nodo.
    {
        inicio = nuevo;
        inicio->estado = 1; //Hacemos que el estado del turno sea activo.
    }
    else //De lo contrario recorre la lista con un while hasta llegar al ultimo nodo a partir del cual la funcion agregara el nodo que queremos.
    {
        Tur* aux = inicio; //Crea nodo auxiliar igual al puntero inicio para no perderlo.
        while(aux->siguiente != nullptr) //Recorre hasta que se encuentre con el ultimo nodo de la lista.
        {
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo;
        aux->siguiente->estado = 1; //Estado activo.
    }

    cout << "El turno ha sido registrado en el sistema." << endl << endl;
    system("pause");
    system("cls");
    return inicio; //Siempre retornar inicio.
}


int contarTur(Tur* inicio) //Recorre la lista de turnos y cuenta la cantidad de turnos registrados y la cantidad de turnos activos.
{
    int cantidadTur = 0;
    int cantidadTurAct = 0;
    for(Tur* aux = inicio; aux != nullptr; aux = aux->siguiente)
    {
        cantidadTur++;
        if (aux->estado == 1)
        {
            cantidadTurAct++;
        }
    }

    cout << "La cantidad de turnos registrados es de: " << cantidadTur << endl;
    cout << "La cantidad de turnos activos es de: " << cantidadTurAct << endl << endl;

    system("pause");
    system("cls");

    return cantidadTur;

}


void cancelarTur(Tur* inicio, int dniPac) //Obtiene el DNI de un turno y lo busca en la lista, si lo encuentra, lo cancela.
{
    for(Tur* aux = inicio; aux != nullptr; aux = aux->siguiente)
    {
        if(aux->paciente == dniPac && aux->estado != 2)
        {
            aux->estado = 2;
            break;
        }
        else
        {
            cout << "El turno que intenta cancelar no esta registrado en el sistema o ya ha sido cancelado." << endl;
            cout << "Sera devuelto al menu anterior..." << endl << endl;
            system("pause");
            system("cls");
        }
    }
}


int cancelarTurOpcion() //Menu de opciones para cancelar o no un turno.
{
    int opcion;
    cout << "Â¿Desea cancelar este turno?" << endl << "1. Si" << endl << "0. No" << endl;
    cin >> opcion;
    system("cls");
    switch(opcion)
    {

    case 1:
        //retornar booleano y si es true llamar a cancelar tur para el caso de 1 solo tur o escribiir manualmente codigo para cancelar por codigo
        break;

    case 0:
        cout << "El turno no ha sido cancelado." << endl;
        system("pause");
        system("cls");
        break;

    default:
        cout << "Ha seleccionado una opcion incorrecta." << endl;
        system("pause");
        system("cls");
        break;
    }
    return opcion;
}


void mostrarTurAux(Tur* aux) //Dado un puntero auxiliar, te imprime el nodo.
{
    cout << "Codigo del turno: " << aux->codigo << endl << endl;
    cout << "DNI: " << aux->paciente << endl;
    cout << "Codigo medico: " << aux->especialidad << endl;
    cout << "Fecha: " << aux->fecha << endl;
    cout << "Hora:  " << aux->hora << endl;
    cout << "Estado: " << aux->estado << endl << endl << endl;
}


bool buscarTurMed(int codigo, Tur* inicio) //A traves del codigo, verifica si la especialidad tiene un turno activo.
{
    for (Tur* aux = inicio; aux != nullptr; aux = aux->siguiente)
    {
        if (codigo == aux->especialidad && aux->estado == 1)
        {
            return true; //Retorna true si tiene turno.
        }
    }
    return false; //Retorna false si no tiene turno.
}


int buscarTur(int dniPaciente, Tur* &inicio) //A traves del DNI, busca si el paciente tiene un turno activo
{
    for (Tur* aux = inicio; aux != nullptr; aux = aux->siguiente)
    {
        if (dniPaciente == aux->paciente && aux->estado == 1)
        {
            return true; //Retorna true si el paciente tiene un turno.
        }
    }
    return false; //Retorna false si el paciente no tiene un turno.
}


void menu_de_opciones();


//----------------------------------------FUNCIONES DE ADMINISTRACION PACIENTES---------------------------------------



void altaPac(int &dimLPac, Pac listaPac[]) //Introduce pacientes al arreglo.
{
    if (dimLPac < MAX) //Verifica que haya espacio en el arreglo.
    {
        long long int dni;
        cout << "Ingrese el DNI del paciente: ";
        cin >> dni;
        system("cls");

        while (buscarPaciente(dni, &listaPac[0], dimLPac) != -1)
        {
            cout << "El DNI ingresado ya esta registrado." << endl;
            cout << "Ingrese uno valido: ";
            cin >> dni;
            system("cls");
        }

        listaPac[dimLPac].dni = dni;
        cout << "Ingrese el apellido del paciente: ";
        getline(cin>>ws, listaPac[dimLPac].apellido);
        system("cls");
        cout << "Ingrese el nombre del paciente: ";
        getline(cin>>ws, listaPac[dimLPac].nombre);
        system("cls");
        cout << "Ingrese el numero de contacto del paciente: ";
        cin >> listaPac[dimLPac].telefono;
        system("cls");

        cout << "Se registro al paciente: " << endl << endl;
        mostrarPac(dimLPac, &listaPac[0]);
        dimLPac++;
        system("pause");
        system("cls");
    }
    else //Si no queda espacio en el arreglo
    {
        cout << "No queda espacio para seguir agregando pacientes al arreglo." << endl;
        cout << "Quite elementos del arreglo para poder agregar otro paciente." << endl << endl;
        system("pause");
        system("cls");
    }
}



void modPac(int &dimLPac, Pac listaPac[]) //Modifica pacientes del arreglo.
{
    long long int dni, posArreglo, modificar;
    cout << "Ingrese el DNI del paciente a modificar: ";
    cin >> dni;
    posArreglo = buscarPaciente(dni, &listaPac[0], dimLPac);
    system("cls");

    if (posArreglo == -1)
    {
        cout << "El paciente no se encuentra en el sistema." << endl << endl;
    }
    else
    {
        cout << "Que desea modificar?" << endl << endl;
        cout << "1. Apellido" << endl;
        cout << "2. Nombre" << endl;
        cout << "3. Numero de telefono" << endl;
        cin >> modificar;
        system("cls");

        switch(modificar)
        {
        case 1:
            cout << "Modifique el apellido del paciente: ";
            getline(cin>>ws, listaPac[posArreglo].apellido);
            system("cls");
            cout << "El paciente se ha modificado con exito." << endl << endl;
            break;

        case 2:
            cout << "Modifique el nombre del paciente: ";
            getline(cin>>ws, listaPac[posArreglo].nombre);
            system("cls");
            cout << "El paciente se ha modificado con exito." << endl << endl;
            break;

        case 3:
            cout << "Modifique el numero telefonico del paciente: ";
            cin >> listaPac[posArreglo].telefono;
            system("cls");
            cout << "El paciente se ha modificado con exito." << endl << endl;
            break;

        default:
            cout << "Ha introducido una opcion incorrecta." << endl;
            cout << "Sera devuelto al menu anterior..." << endl << endl;
            break;
        }
    }
    system("pause");
    system("cls");
}



void bajaPac(int &dimLPac, Pac listaPac[], Tur* &inicio) //Elimina pacientes del arreglo.
{
    long long int dni, opcion, posArreglo;

    cout << "Ingrese el DNI del paciente a dar de baja: ";
    cin >> dni;
    posArreglo = buscarPaciente(dni, &listaPac[0], dimLPac);
    system("cls");

    if (posArreglo == -1)
    {
        cout << "El paciente no se encuentra en el sistema." << endl << endl;
    }

    else
    {
        system("cls");
        cout << "Desea eliminar al paciente? " << endl << endl;
        mostrarPac(posArreglo, &listaPac[0]);
        cout << "1. Si" << endl << "2. No" << endl;

        cin >> opcion;
        system("cls");
        switch(opcion)
        {
        case 1:
            if (buscarTur(dni, inicio) != false)
            {
                cout << "El paciente no puede eliminarse debido a que posee uno o mas turnos reservados." << endl;
                break;
            }

            else
            {
                quitarElementoArregloPac(posArreglo, dimLPac, &listaPac[0]);
                cout << "El paciente ha sido dado de baja con exito." << endl;
                break;
            }

         case 2:
            cout << "El paciente no ha sido dado de baja." << endl;
            break;

         default:
            cout << "Ha introducido una opcion incorrecta." << endl;
            cout << "Sera devuelto al menu anterior..." << endl << endl;
            break;

            }
    }
    system("pause");
    system("cls");
}



void listPac(int dimLPac, Pac listaPac[]) //Busqueda de pacientes en el arreglo de pacientes.
{
    int busqueda, dni, posArreglo;
    if(dimLPac > 0)
    {
        cout << "1. Busqueda completa" << endl;
        cout << "2. Busqueda especifica" << endl;
        cout << ">>";
        cin >> busqueda;

        switch(busqueda)
        {
        case 1:
            cout << "Listado completo:" << endl << endl;
            for(int i=0; i<dimLPac; i++) //FOR PARA QUE IMPRIMA TODOS LOS PACIENTES GENERADOS(SI ALGUNO ESTA ELIMINADO LO OMITE)
            {
                mostrarPac(i,&listaPac[0]);
            }
            break;

        case 2:
            cout << "Introduzca el DNI del paciente al que desea visualizar: " << endl;
            cin >> dni;
            posArreglo = buscarPaciente(dni, &listaPac[0], dimLPac);

            if (posArreglo != -1)
            {
                mostrarPac(posArreglo, &listaPac[0]);
            }
            else
            {
                cout << "El DNI que ha ingresado no pertence a ningun paciente registrado en el sistema." << endl;
            }
            break;

        default:
            cout << "Ha introducido una opcion incorrecta." << endl;
            cout << "Sera devuelto al menu anterior..." << endl << endl;

        }
    }
    else
    {
        system("cls");
        cout << "Todavia no existe ningun paciente en el sistema." << endl;
    }

    system("pause");
    system("cls");
}


//-----------------------------FUNCIONES DE ADMINISTRACION ESPECIALIDADES MEDICAS--------------------------


void altaMed(int &dimLMed, Med listaMed[], int &codigoMed) //Introduce especialidades medicas al arreglo.
{
    if (dimLMed < MAX) //Verifica que haya espacio en el arreglo.
    {
        int descripcion, opcion=0;

        cout << "Ingrese el nombre de la especialidad medica: ";
        getline(cin>>ws, listaMed[dimLMed].nombre);
        system("cls");

        do
        {
            cout << "Desea agregar una descripcion?" << endl << "1. Si" << endl << "2. No" << endl;
            cin >> descripcion; //Opcion: agregar o no descripcion.
            system("cls");
            switch (descripcion)
            {
            case 1:
                cout << "Ingrese la descripcion de la especialidad medica: ";
                getline(cin>>ws, listaMed[dimLMed].descripcion);
                opcion = 1;
                break;

            case 2:
                listaMed[dimLMed].descripcion = "Sin descripcion.";
                opcion = 1;
                break;

            default:
                cout << "Ha introducido una opcion invalida." << endl;
                system("pause");
                system("cls");
                break;

            }
        }while(opcion!=1); //Do while que verifica que el usuario introdujo una opcion valida, si no lo hizo se repite en bucle hasta que lo haga.

        listaMed[dimLMed].codigo = codigoMed;

        system("cls");
        cout << "Se registro la Especialidad Medica: " << endl << endl;
        mostrarMed(dimLMed, &listaMed[0]);

        dimLMed++;
        codigoMed++;
        system("pause");
        system("cls");
    }

    else //En caso de que no haya espacio en el arreglo:
    {
        cout << "No queda espacio para seguir agregando especialidades medicas al arreglo." << endl;
        cout << "Quite elementos del arreglo para poder agregar otra especialidad medica." << endl;
        system("pause");
        system("cls");
    }

}



void modMed(int &dimLMed, Med listaMed[]) //Modifica especialidades medicas del arreglo.
    {
        int codigo, posArreglo, modificar;

        cout << "Ingrese el codigo de la especialidad medica a modificar: ";
        cin >> codigo;
        posArreglo = buscarMed(codigo, &listaMed[0], dimLMed); //buscarMed retorna -1 si no existe elemento y la posicion en el arreglo si existe.
        system("cls");

        if (posArreglo == -1)
        {
            cout << "La especialidad medica no se encuentra en el sistema." << endl << endl;
            system("pause");
            system("cls");
        }

        else
        {
            cout << "Que desea modificar?" << endl << endl;
            cout << "1. Nombre" << endl;
            cout << "2. Descripcion" << endl;
            cin >> modificar;

            switch (modificar)
            {
            case 1:
                cout << "Modifique el nombre de la especialidad medica: ";
                getline(cin>>ws, listaMed[posArreglo].nombre);
                system("cls");
                cout << "La especialidad medica ha sido modificada con exito." << endl << endl;
                break;

            case 2:
                cout << "Modifique la descripcion de la especialidad medica: ";
                getline(cin>>ws, listaMed[posArreglo].descripcion);
                system("cls");
                cout << "La especialidad medica ha sido modificada con exito." << endl << endl;
                break;

            default:
                cout << "Ha introducido una opcion incorrecta." << endl;
                cout << "Sera devuelto al menu anterior..." << endl << endl;
                break;

            }
            system("pause");
            system("cls");
        }
    }



void bajaMed(int &dimLMed,  Med listaMed[], Tur* inicio)
{
    int codigo, opcion, posArreglo;

    cout << "Ingrese el codigo de la especialidad medica a dar de baja: ";
    cin >> codigo;
    posArreglo = buscarMed(codigo, &listaMed[0], dimLMed);
    system("cls");

    if (posArreglo == -1)
    {
        cout << "La especialidad medica no se encuentra en el sistema." << endl << endl;
    }

    else
    {
        system("cls");

        mostrarMed(posArreglo, &listaMed[0]);
        cout << "Desea eliminar la especialidad medica?" << endl << endl;
        cout << "1. Si" << endl << "2. No" << endl;

        cin >> opcion;
        system("cls");
        switch(opcion)
        {
        case 1:
            if (buscarTurMed(codigo, inicio) == true)
            {
                cout << "La especialidad medica no puede eliminarse debido a que posee uno o mas turnos reservados." << endl << endl;
                break;
            }

            else
            {
                quitarElementoArregloMed(posArreglo, dimLMed, &listaMed[0]);
                cout << "La especialidad medica ha sido dado de baja con exito." << endl << endl;
                break;
            }

         case 2:
            cout << "La especialidad medica no ha sido dado de baja." << endl << endl;
            break;

         default:
            cout << "Ha introducido una opcion incorrecta..." << endl;
            cout << "Sera devuelto al menu anterior..." << endl << endl;
            break;
         }
    }

    system("pause");
    system("cls");
}



void listMed(int dimLMed, Med listaMed[])
{
    int busqueda, codigo, posArreglo;

    if(dimLMed > 0) //Verificamos que para poder acceder a la funcion necesiten haber especialidades medicas ya registradas.
    {
        cout << "1. Busqueda completa." << endl;
        cout << "2. Busqueda especifica." << endl;
        cout << ">>";
        cin >> busqueda;

        switch(busqueda)
        {
        case 1:
            cout << "Listado completo:" << endl << endl;
            for(int i=0; i<dimLMed; i++)
            {
                mostrarMed(i,&listaMed[0]); //i es el indice.
            }
            break;

        case 2:
            cout << "Introduzca el codigo de la especialidad medica a la que desea visualizar: " << endl;
            cin >> codigo;
            posArreglo = buscarMed(codigo, &listaMed[0], dimLMed);

            if (posArreglo != -1)
            {
                mostrarMed(posArreglo, &listaMed[0]);
            }
            else
            {
                cout << "El codigo que ha ingresado no pertenece a ninguna especialidad medica registrada en el sistema." << endl;
            }
            break;

        default:
            cout << "Ha introducido una opcion incorrecta." << endl;
            cout << "Sera devuelto al menu anterior..." << endl << endl;

        }
    }
    else
    {
        system("cls");
        cout << "Todavia no existe ninguna especialidad medica en el sistema." << endl;
    }

    system("pause");
    system("cls");
}


//------------------------------FUNCIONES DE TURNOS--------------------


Tur* reservaTur(Tur* &inicio, int &codigoTur, Pac listaPac[], int dimLPac, Med listaMed[0], int dimLMed)
{
    int hora, dniPac, codeEsp;
    string fecha;

    if(dimLMed == 0 || dimLPac == 0) //si no ingresamos ninguna especialidad ni DNI, no nos permite ingresar a la funcion
    {
        cout << "No se puede ingresar a la funcion sin antes haber ingresado un DNI y una especialidad." << endl;
        cout << "Sera devuelto al menu de opciones..." << endl << endl;
        system("pause");
        system("cls");
    }
    else //en otro caso, comenzamos a tomar los datos
    {
        Tur* nuevo; //Creamos el nuevo nodo.
        nuevo = new Tur; //Le reservamos un espacio en la memoria Heap.

        nuevo->siguiente = nullptr; //Hacemos que el siguiente al nodo que estamos creando sea null.

        nuevo->codigo = codigoTur; //Le asignamos el codigo de turno.

        cout << "Ingrese el DNI del paciente al que le quiere reservar un turno: "; //Pedimos al usuario que ingrese el DNI.
        cin >> dniPac;
        system("cls");

        while (buscarPaciente(dniPac, &listaPac[0], dimLPac) == -1) //Si el DNI no esta en la lista de pacientes, no es valido.
        {
            cout << "el DNI introducido no es valido, ingrese uno valido: ";
            cin >> dniPac; //Pedimos un DNI nuevo hasta que ingrese uno valido.
            system("cls");
        }
        nuevo->paciente = dniPac; //Almacenamos el DNI en el nodo.

        cout << "Ingrese el codigo de la especialidad medica: "; //Pedimos al usuario que ingrese la especialidad.
        cin >> codeEsp;
        system("cls");

        while (buscarMed(codeEsp, &listaMed[0], dimLMed) == -1) //Si el codigo no es valido, informamos y pedimos otro.
        {
            cout << "el codigo medico introducido no es valido." << endl;
            cout << "Introduzca uno valido: ";
            cin >> codeEsp;
            system("cls");
        }

        if (buscarTurRepetido(codeEsp, dniPac, inicio) == false) //Verificamos que no exista otro turno con mismo DNI y Especialidad Medica.
        {
            cout<<"No se pueden sacar dos turnos con un mismo paciente y una misma especialidad." << endl << endl;
            system("pause");
            system("cls");
        }

        else //Si no existe...
        {
            nuevo->especialidad = codeEsp; //En caso de que no haya turnos para misma esp. y pac. almacenamos la especialidad en el nodo.

            cout << "Ingrese la fecha para el turno: ";
            cin >> fecha;
            system("cls");
            nuevo->fecha = fecha;

            cout << "Ingrese la hora para el turno: ";
            cin >> hora;
            system("cls");
            while(hora>23 || hora <0) //Que sea una hora valida entre 23 y 0.
            {
                cout << "Ha introducido un horario invalido..." << endl;
                cout << "Asegurese de que la hora ingresada se encuentre entre 0 y 23" << endl << endl;
                cout << "Ingrese un horario valido: ";
                cin >> hora;
            }

            nuevo->hora = hora;

            inicio = insertarFinal(inicio, nuevo); //Llamamos a la funcion que agrega el nodo que acabamos de crear al final de la lista de nodos.
            codigoTur++; //Aunmentamos el valor del codigo en 1 para el siguiente turno.
        }

    }

    return inicio;
}



void modTurn(Tur* inicio)
{
    int dniPac, cantidadTur, opcion, codeTur, hora;
    string fecha;
    bool tur = false;

    cout << "Introduzca el DNI del paciente cuyo turno desea modificar: ";
    cin >> dniPac;
    system("cls");
    cantidadTur = contarTurDni(inicio, dniPac); //Contamos la cantidad de turnos que tiene el paciente.

    if (cantidadTur > 0) //Si tiene 0 turnos activos informamos por pantalla y devolvemos al menu anterior.
    {
        cout << "El paciente tiene los siguientes turnos activos: " << endl << endl;
        mostrarTurDni(inicio, dniPac);

        cout << "Introduzca el codigo del turno que desee modificar: ";
        cin >> codeTur; //busco el turno con el codigo ingresado.
        system("cls");

        for(Tur* aux = inicio; aux != nullptr; aux = aux->siguiente)
        {
            if(aux->codigo == codeTur && aux->paciente == dniPac && aux->estado == 1) //El if verifica que los turnos encontrados sean del mismo paciente y esten activos.
            {
                tur = true; //Indica que se encontro el turno a modificar.
                cout << "Â¿Que desea modificar?" << endl;
                cout << "1. Fecha" << endl;
                cout << "2. Hora" << endl;
                cin >> opcion;
                system("cls");

                switch(opcion)
                {
                case 1:
                    cout << "Introduzca la nueva fecha: ";
                    cin >> fecha;
                    system("cls");
                    aux->fecha = fecha;
                    cout << "El turno ha sido modificado exitosamente." << endl << endl;
                    system("pause");
                    system("cls");
                    break;

                case 2:
                    cout << "Introduzca la nueva hora: ";
                    cin >> hora;
                    system("cls");
                    while(hora>23 || hora <0) //Verifica que el horario este entre 0 y 23.
                    {
                        cout << "Ha introducido un horario invalido..." << endl;
                        cout << "Asegurese de que la hora ingresada se encuentre entre 0 y 23" << endl << endl;
                        cout << "Ingrese un horario valido: ";
                        cin >> hora;
                    }

                    aux->hora = hora;
                    cout << "El turno ha sido modificado exitosamente." << endl;
                    system("pause");
                    system("cls");
                    break;

                default:
                    cout << "Ha introducido una opcion incorrecta." << endl << endl;
                    system("pause");
                    system("cls");
                    break;
               }
            }
        }
        if(tur == false) //El siguiente codigo se ejecuta si no se encontro el turno a modificar.
        {
            cout << "El codigo introducido no pertenece a ningun turno en el sistema o no pertence a un turno del paciente cuyo DNI fue introducido anteriormente." << endl << endl;
            system("pause");
            system("cls");
        }
    }
    else //Si el paciente no tiene DNI se ejecuta el siguiente codigo.
    {
        cout << "El DNI introducido no corresponde a ningun turno activo registrado en el sistema." << endl << endl;
        system("pause");
        system("cls");
    }
}



void cancelarTurn(Tur* inicio)
{
    int dniPac, cantidadTur, codeTur;
    bool tur = false;

    cout << "Introduzca el DNI del paciente cuyo turno desea cancelar: ";
    cin >> dniPac;
    system("cls");
    cantidadTur = contarTurDni(inicio, dniPac); //Contamos la cantidad de turnos que tiene el paciente.

    if (cantidadTur > 0) //Si tiene 0 turnos activos informamos por pantalla y devolvemos al menu anterior.
    {
        if(cantidadTur == 1) //Si tiene un solo turno activo, mostramos en pantalla los datos y preguntamos al usuario si desea eliminarlo.
        {
            mostrarTurDni(inicio, dniPac);
            if (cancelarTurOpcion() == 1)
            {
                cancelarTur(inicio, dniPac);
                cout << "El turno ha sido cancelado con exito." << endl << endl;
                system("pause");
                system("cls");
            }
        }
        else //En caso de que tenga mas de un turno activo, mostramos todos ellos en pantalla y pedimos al usuario que seleccion cual desea eliminar
             //A traves del codigo del turno.
            {
                cout << "El paciente tiene los siguientes turnos activos: " << endl << endl;
                mostrarTurDni(inicio, dniPac);
                cout << "Introduzca el codigo del turno que desee eliminar: ";
                cin >> codeTur; //busco el turno con el codigo ingresado, si lo encuentro, usa cancelarturopcion.
                system("cls");
                for(Tur* aux = inicio; aux != nullptr; aux = aux->siguiente)
                {
                    if(aux->codigo == codeTur && aux->paciente == dniPac && aux->estado == 1)
                    {
                        tur = true;
                        if (cancelarTurOpcion() == 1)
                        {
                            aux->estado = 2;
                            cout << "El turno ha sido cancelado con exito." << endl << endl;
                            system("pause");
                            system("cls");
                        }
                    }
                 }

        if(tur == false)
          {
            cout << "El codigo introducido no pertenece a ningun turno en el sistema o no pertence a un turno del paciente cuyo DNI fue introducido anteriormente." << endl << endl;
            system("pause");
            system("cls");

          }
          }
    }
    else
    {
        cout << "El DNI introducido no corresponde a ningun turno activo registrado en el sistema." << endl << endl;
        system("pause");
        system("cls");
    }
}



void listTurn(Tur* inicio)
{
    int busqueda, dniPac, codeEsp, estado;
    string fecha;

    cout << "Â¿Que tipo de consulta desea realizar?" << endl << endl;
    cout << "1. Completa" << endl; //Completo busca turnos activos solamente.
    cout << "2. Busqueda" << endl;
    cin >> busqueda;
    system("cls");

    switch(busqueda)
    {
    case 1:
        for(Tur* aux = inicio; aux != nullptr; aux = aux->siguiente)
        {
            if(aux->estado == 1)
            {
                mostrarTurAux(aux);
            }
        }
        system("pause");
        system("cls");
        break;

    case 2:
        cout << "1. Filtrar por fecha" << endl;
        cout << "2. Filtrar por paciente" << endl;
        cout << "3. Filtrar por especialidad medica" << endl;
        cout << "4. Filtrar por estado" << endl << endl; //Se puede buscar turnos cancelados.
        cout << "Selecciona una opcion: ";
        cin >> busqueda;
        system("cls");

        switch(busqueda)
        {
        case 1: //Fecha.
            cout << "Introduzca la fecha: ";
            cin >> fecha;
            system("cls");

            cout << "RESULTADOS APLICANDO EL FILTRO DE FECHA: " << fecha << endl << endl;
            for(Tur* aux = inicio; aux != nullptr; aux = aux->siguiente)
            {
                if(aux->fecha == fecha)
                {
                    mostrarTurAux(aux);
                }
            }
            system("pause");
            system("cls");
            break;

        case 2: //Paciente
            cout << "Introduzca el DNI del paciente: ";
            cin >> dniPac;
            system("cls");

            cout << "RESULTADOS APLICANDO EL FILTRO DE PACIENTE: " << dniPac << endl << endl;
            for(Tur* aux = inicio; aux != nullptr; aux = aux->siguiente)
            {
                if(aux->paciente == dniPac)
                {
                    mostrarTurAux(aux);
                }
            }
            system("pause");
            system("cls");
            break;

        case 3: //Especialidad
            cout << "Introduzca el codigo medico: ";
            cin >> codeEsp;
            system("cls");

            cout << "RESULTADOS APLICANDO EL FILTRO DE ESPECIALIDAD: " << codeEsp << endl << endl;
            for(Tur* aux = inicio; aux != nullptr; aux = aux->siguiente)
            {
                if(aux->especialidad == codeEsp)
                {
                    mostrarTurAux(aux);
                }
            }
            system("pause");
            system("cls");
            break;

        case 4: //Estado
            cout << "Introduzca el estado(1: activo, 2: cancelado): ";
            cin >> estado;
            system("cls");

            cout << "RESULTADOS APLICANDO EL FILTRO DE ESTADO: " << estado << endl << endl;
            for(Tur* aux = inicio; aux != nullptr; aux = aux->siguiente)
            {
                if(aux->estado == estado)
                {
                    mostrarTurAux(aux);
                }
            }
            system("pause");
            system("cls");
            break;

        default:
            cout << "Ha introducido una opcion incorrecta..." << endl << endl;
            system("pause");
            system("cls");
            break;
        }
        break;


    default:
        cout << "Ha introducido una opcion incorrecta..." << endl << endl;
        system("pause");
        system("cls");
        break;
    }
}



//---------------------------------------------MENU ESPECIALIDADES MEDICAS-------------------------------


Tur*  Administrar_Especialidades_Medicas(int &dimLMed, int &codigoMed,  Med listaMed[],  Tur* &inicio)
{
    int opcion;

    do
    {
    cout<<"Menu de opciones de 'Administrar Especialidades Medicas': "<<endl<<endl;

    cout<<"1. Alta de Especialidades Medicas."<<endl;
    cout<<"2. Modificacion de Especialidades Medicas."<<endl;
    cout<<"3. Baja de Especialidades Medicas."<<endl;
    cout<<"4. Listado de Especialidades Medicas."<<endl << endl;

    cout<<"5. Menu principal."<<endl;
    cout<<endl<<"Elija una opcion valida: ";
    cin>>opcion;
    system("cls");
    }while(opcion<1 or opcion>5);

        switch(opcion)
        {
            case 1:
            altaMed(dimLMed, &listaMed[0], codigoMed);
            break;

            case 2:
            modMed(dimLMed, &listaMed[0]);
            break;

            case 3:
            bajaMed(dimLMed, &listaMed[0], inicio);
            break;

            case 4:
            listMed(dimLMed, &listaMed[0]);
            break;

            case 5:
            break;
        }
        return inicio;
    }


//---------------------------------------------MENU PACIENTES-----------------------------------------------



Tur* Administrar_Pacientes(int &dimLPac, int codigoTur, Pac listaPac[],  Tur* &inicio)
{
    int opcion;


    do
    {
    cout << "Menu de opciones de 'Administrar Pacientes': " << endl << endl;

    cout << "1. Alta de Pacientes." << endl;
    cout << "2. Modificacion de Pacientes." << endl;
    cout << "3. Baja de Pacientes." << endl;
    cout << "4. Listado de Pacientes." << endl << endl;

    cout << "5. Menu principal." << endl;

    cout << endl << "Elija una opcion valida: ";
    cin>>opcion;
    system("cls");
    }while(opcion<1 or opcion>5);


        switch(opcion)
        {
            case 1:
            altaPac(dimLPac, &listaPac[0]);
            break;

            case 2:
            modPac(dimLPac, &listaPac[0]);
            break;

            case 3:
            bajaPac(dimLPac, &listaPac[0], inicio);
            break;

            case 4:
            listPac(dimLPac, &listaPac[0]);
            break;

            case 5:
            break;
    }
        return inicio;
}



//----------------------------------MENU TURNOS---------------------------------------------------



Tur* Administrar_Turnos(int &dimLPac, int &dimLMed,  Pac listaPac[], Med listaMed[],  int &codigoTur, Tur* &inicio)
{
    int opcion;

    do
    {
    cout << "Menu de opciones de 'Administrar Turnos': " << endl << endl;

    cout<<"1. Alta de Turnos."<<endl;
    cout<<"2. Modificacion de Turnos."<<endl;
    cout<<"3. Baja de Turnos."<<endl;
    cout<<"4. Listado de Turnos."<<endl << endl;

    cout<<"5. Menu principal."<<endl;

    cout << endl << "Elija una opcion valida: ";
    cin >> opcion;
    system("cls");
    }
    while(opcion<1 or opcion>5);

    if (opcion==5)
    {
        ;//REGRESA A LA FUNCION DE OPCIONES PRINCIPALES
    }
    else
    {
        switch(opcion)
        {
            case 1:
            inicio = reservaTur(inicio, codigoTur, &listaPac[0], dimLPac, &listaMed[0], dimLMed);
            break;

            case 2:
            modTurn(inicio);
            break;

            case 3:
            cancelarTurn(inicio);
            break;

            case 4:
            listTurn(inicio);
            break;
        }
    }
    return inicio;
}



//--------------------------------FUNCION DE OPCIONES PRINCIPALES----------------------------------



void menu_de_opciones(int &dimLPac, int &dimLMed,  int &codigoMed, Pac listaPac[], Med listaMed[],  bool &corte, int &codigoTur, Tur* &inicio)
{
    int opcion;

    do{
    cout << "Menu de opciones: " << endl << endl;

    cout<<"1. Administrar Especialidades Medicas."<<endl;
    cout<<"2. Administrar Pacientes."<<endl;
    cout<<"3. Administrar Turnos."<<endl << endl;

    cout<<"4. Salir"<<endl;

    cout<<endl<<"Elija una opcion correcta: ";
    cin>>opcion;                //---------SELECCION DE OPCION
    system("cls");
    }while(opcion<1 or opcion>4);//---------------BUCLE PARA EL INGRESO DE UNA OPCION VALIDA

    if (opcion==4)
    {
        cout<<"Programa finalizado."<<endl;
        corte = true;
    }
    else
    {

        switch(opcion) //-------SWITCH(EN CADA CASO ENTRA A UNA DE LAS FUNCIONES DE ADMINISTRACION)
        {
            case 1:
            system("cls");
            Administrar_Especialidades_Medicas(dimLMed, codigoMed,  &listaMed[0], inicio);
            break;

            case 2:
            system("cls");
            Administrar_Pacientes(dimLPac, codigoTur, &listaPac[0], inicio);
            break;

            case 3:
            system("cls");
            Administrar_Turnos(dimLPac, dimLMed,  &listaPac[0], &listaMed[0], codigoTur, inicio);break;
        }

    }
}



//--------------------------------FUNCION PRINCIPAL----------------------------------------------------

int main()
{
    int dimLPac = 0, dimLMed = 0, codigoMed = 0, codigoTur = 0;

    Pac listaPac[MAX]; //Declaracion de arreglos.
    Med listaMed[MAX];

    Tur* inicio = nullptr; //Declaracion puntero inicial de lista de turnos.

    bool corte = false; //Condicion para que el programa siga andando.

    do
    {
        menu_de_opciones(dimLPac, dimLMed, codigoMed, &listaPac[0], &listaMed[0], corte, codigoTur, inicio);
    }

    while(corte == false);
    return 0;
}
