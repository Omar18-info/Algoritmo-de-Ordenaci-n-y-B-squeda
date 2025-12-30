//Busqueda binaria para Vocabulario de palabras
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>

using namespace std;

struct Concepto{
    string termino;
    string definicion;
};

const int MAX=100;//tamaÃ±o mÃ¡ximo del vocabulario

//FUNCIONES PRINCIPALES
void ingresar(Concepto*,int&);
void ordenar(Concepto*, int);
void mostrar(Concepto*, int);

//BUSQUEDAS (todas void)
void busqueda_secuencial_iterativa(Concepto*, int);
void busqueda_secuencial_recursiva(Concepto*, int);
void busqueda_binaria_iterativa(Concepto*, int);
void busqueda_binaria_recursiva(Concepto*, int);

//FUNCIONES SECUNDARIAS
void interfaz(string[],string[],const int,int);
//se agrego parametros para los submenus de busqueda 
void sub_menu_busqueda(Concepto*,int);
void sub_sub_menu_implementacion(Concepto*, int, void(*)(Concepto*, int), void(*)(Concepto*, int) );
//tarea para el Ander: void* ... void*().... void (*)() puntero a funcion
void diseno_iterativa(Concepto*,int,int);
void diseno_iterativa_encontrado();
void diseno_iterativa_no_encontrado();
void limpiar_cuadro();

//FUNCIONES AUXILIARES
void gotoxy(int , int );
void cambio_color(int );
void ocultarCursor();
string mayusculas(string);//pasar a mayusculas

//PROGRAMA PRINCIPAL
int main(){
    SetConsoleOutputCP(CP_UTF8);
    ocultarCursor();
    
    Concepto Palabra[MAX];
    int contador=0;

    const int total=4;

    string opcionesMayus[total] = {"INGRESAR", "BUSCAR", "MOSTRAR","SALIR"};
    string opcionesMin[total] = {"Ingresar", "Buscar", "Mostrar","Salir"};

    int opcionActual=0;
    string palabrita;

    // Dibujar el menÃº por primera vez
    interfaz(opcionesMayus, opcionesMin, total, opcionActual);
    
    while (true) {
        int tecla = _getch();
        
        if (tecla == 0 || tecla == 224){
            tecla = _getch();
            
            if (tecla == 80) {//abajo
                opcionActual++;
                if (opcionActual >= total) {
                    opcionActual = 0;
                }
                interfaz(opcionesMayus, opcionesMin, total, opcionActual);
            }
            else if (tecla == 72) {//arriba
                opcionActual--;
                if (opcionActual < 0) {
                    opcionActual = total - 1;
                }
                interfaz(opcionesMayus, opcionesMin, total, opcionActual);
            }
        }
        else if (tecla == 13){//enter
            system("cls");
            switch(opcionActual){
                case 0:
                    ingresar(Palabra,contador);
                    break;
                case 1:
                    sub_menu_busqueda(Palabra, contador);
                    break;
                case 2:
                    ordenar(Palabra,contador);
                    mostrar(Palabra,contador);
                    break;
                case 3:
                    cout<<"\n\n\n    Saliendo...";
                    return 0;
                default:
                    break;
            }
            
            system("cls");
            interfaz(opcionesMayus, opcionesMin, total, opcionActual);

        }
    }
}

//FUNCIONES PRINCIPALES

void ingresar(Concepto* p, int &contador){
    string verifica, verifica_mayus,palabrita_mayus;//verifica si es duplicado
    bool bandera;

    do{ 
        bandera=true;
        cout<<"\n\n\n\n    Â¡Hola!, soy tu vocabulario personal.\n";
        cout<<"    Que palabra deseas agregar?: ";
        getline(cin, verifica);
        
        verifica_mayus=mayusculas(verifica);

        for(int i=0;i<contador;i++){
            palabrita_mayus=mayusculas(p[i].termino);
            if(palabrita_mayus==verifica_mayus){
                cout<<"\n    No se aceptan duplicados";
                bandera=false;
                _getch();
                system("cls");
                break;
            }
        }

    }while(bandera==false);

    p[contador].termino=verifica;
    cout<<"\n\n    Cual es su definiciÃ³n?: \n    ";
    getline(cin, p[contador].definicion);

    contador++;
    cout<<"\n    Palabra agregada exitÃ³samente.\n";
    _getch();
}

void ordenar(Concepto* p, int contador){//ordenamiento por insercion
    for(int i=0;i<contador;i++){
        Concepto temp=p[i];//crea una variable de tipo concepto temporal la cual guarda el valor de p[i]
        int pos=i;

        while(pos>0 && mayusculas(p[pos-1].termino)>mayusculas(temp.termino)){//compara en mayusculas
            p[pos]=p[pos-1];
            pos--;
        }
        
        p[pos]=temp;
    }
}

void mostrar(Concepto* p, int contador){
    ordenar(p,contador);

    if(contador==0){
        cout<<"\n\n\n    Â¡Ups! No tienes palabras registradas en el vocabulario\n";
        cout<<"    Encuentra palabras interesantes primero.\n";
        _getch();
        return;
    }

    cout<<"\n\n\n    Tus palabras son:\n\n";
    for(int i=0;i<contador;i++){
        cout<<"    "<<i+1<<". "<<p[i].termino<<": "<<p[i].definicion<<"\n";
    }
    _getch();
}

//FUNCIONES SECUNDARIAS

void interfaz(string opcionesMayus[], string opcionesMin[], const int total, int seleccionada) {
    gotoxy(0,0);//mover el cursor
    string texto;
    int x=30,y=6;
    int espacio_vertical=5;
    
    cout << "\n\n\n";
    cambio_color(11);
    cout << "                \n\n\n\n    ";
    cambio_color(7);
    
    for(int i=0;i<total;i++){

        if(i==seleccionada){
            cambio_color(5);
            texto= *(opcionesMayus+i);//opcionesMayus[i]
            gotoxy(x,y);cout<<  "â•”â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•—";
            gotoxy(x,y+1);cout<<"â•‘  "<< texto;
            gotoxy(x+18,y+1);cout<<"â•‘";
            gotoxy(x,y+2);cout<<"â•šâ•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•";
            cambio_color(7);
        }else{
            texto= *(opcionesMin+i);
            gotoxy(x,y);cout<<  "â•”â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•—";
            gotoxy(x,y+1);cout<<"â•‘  "<< texto;
            gotoxy(x+18,y+1);cout<<"â•‘";
            gotoxy(x,y+2);cout<<"â•šâ•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•";

        }
        y+=espacio_vertical;
    }
}

void sub_menu_busqueda(Concepto* p, int contador){
    const int total=3;

    string opcionesMayus[total] = {"SECUENCIAL", "BINARIA", "VOLVER"};
    string opcionesMin[total] = {"Secuencial", "Binaria", "Volver"};

    int opcionActual=0;

    // Dibujar el menÃº por primera vez
    interfaz(opcionesMayus, opcionesMin, total, opcionActual);
    
    while (true) {
        int tecla = _getch();
        
        if (tecla == 0 || tecla == 224) {
            tecla = _getch();
            
            if (tecla == 80) {//abajo
                opcionActual++;
                if (opcionActual >= total) {
                    opcionActual = 0;
                }
                interfaz(opcionesMayus, opcionesMin, total, opcionActual);
            }
            else if (tecla == 72) {//arriba
                opcionActual--;
                if (opcionActual < 0) {
                    opcionActual = total - 1;
                }
                interfaz(opcionesMayus, opcionesMin, total, opcionActual);
            }
        }
        else if (tecla == 13){//enter
            system("cls");
            switch(opcionActual){
                case 0://busqueda secuencial
                    sub_sub_menu_implementacion(p, contador, busqueda_secuencial_iterativa, busqueda_secuencial_recursiva);
                    //tarea: pasar las funciones de busqueda secuencial iterativa y recursiva(agregado para los que le toco secuencial)
                    break;
                case 1://busqueda binaria
                    sub_sub_menu_implementacion(p, contador, busqueda_binaria_iterativa, busqueda_binaria_recursiva);
                    //tarea: pasar las funciones de busqueda binaria recursiva
                    break;
                default:
                    break;
            }

            if(opcionActual==2) break;

            system("cls");
            interfaz(opcionesMayus, opcionesMin, total, opcionActual);

        }
    }
}

void sub_sub_menu_implementacion(Concepto* p, int contador, void (*opc1)(Concepto*, int), void (*opc2)(Concepto*, int)){//equivalen a (void* opc1(), void* opc2())
    const int total=3;

    string opcionesMayus[total] = {"ITERATIVA", "RECURSIVA", "VOLVER"};
    string opcionesMin[total] = {"Iterativa", "Recursiva", "Volver"};

    int opcionActual = 0;
    string palabrita;

    interfaz(opcionesMayus, opcionesMin, total, opcionActual);
    
    while (true) {
        int tecla = _getch();
        
        if (tecla == 0 || tecla == 224) {
            tecla = _getch();
            
            if (tecla == 80) {//abajo
                opcionActual++;
                if (opcionActual >= total) {
                    opcionActual = 0;
                }
                interfaz(opcionesMayus, opcionesMin, total, opcionActual);
            }
            else if (tecla == 72) {//arriba
                opcionActual--;
                if (opcionActual < 0) {
                    opcionActual = total - 1;
                }
                interfaz(opcionesMayus, opcionesMin, total, opcionActual);
            }
        }
        else if (tecla == 13) {
            system("cls");
            switch(opcionActual){
                case 0:
                    opc1(p, contador); //busqueda secuencial o binario iterativa
                    break;
                case 1:
                    opc2(p, contador); //busqueda secuencial o binaria recursiva
                    break;
                default:
                    break;
            }
            if(opcionActual==2) break;

            system("cls");
            interfaz(opcionesMayus, opcionesMin, total, opcionActual);

        }
    }
}

//BUSQUEDAS

void busqueda_secuencial_iterativa(Concepto* p, int contador){
    cout<<"\n\n\n    Por implementar\n";
    system("pause");
}

void busqueda_secuencial_recursiva(Concepto* p, int contador){
    cout<<"\n\n\n    Por implementar\n";
    system("pause");
}

void busqueda_binaria_recursiva(Concepto* p, int contador){
    cout<<"\n\n\n    Por implementar\n";
    system("pause");
}

void busqueda_binaria_iterativa(Concepto* p, int contador){
    if(contador==0){//verificar si hay palabras en el vocabulario
        system("cls");
        cout<<"\n\n\n    No hay palabras en el vocabulario.\n";
        cout<<"    Agrega algunas primero.\n";
        _getch();
        return;
    }

    system("cls");
    ordenar(p,contador);
    int inicio=0, fin=contador-1, medio;//indices (posiciones del arreglo)
    string palabrita;

    gotoxy(45,2); cout<<"Que palabra buscas?: "; 
    gotoxy(45,3); getline(cin,palabrita);
    
    string palabrita_mayus=mayusculas(palabrita);//convertir palabra ingresada a mayusculas para comparar

    system("cls");
    
    while(inicio<=fin){
        medio=(inicio+fin)/2;//base del calulo
        
        diseno_iterativa(p,inicio,fin);
        gotoxy(45,7);cout<<"Comparando.";
            Sleep(250);cout<<".";
            Sleep(250);cout<<".";
            Sleep(250);

        string termino_mayus=mayusculas(p[medio].termino);//convertir palabra del arreglo a mayusculas para comparar

        if(termino_mayus==palabrita_mayus){//compara las dos palabras en mayusculas

            diseno_iterativa_encontrado();

            gotoxy(48,7);cout<<p[medio].termino;//se mantiene el formato original
            cambio_color(9);
            gotoxy(45,11);cout<<p[medio].definicion;
            cambio_color(11);
            _getch();
            return;
        }
        else if(termino_mayus<palabrita_mayus){
            
            gotoxy(43,7);limpiar_cuadro();
            gotoxy(46,7);cout<<p[medio].termino;


            cambio_color(2);
            gotoxy(44,10); cout<<"La palabra buscada";
            gotoxy(47,11); cout<<"Es mayor";
            cambio_color(7);
            Sleep(1000);

            gotoxy(16,7);limpiar_cuadro();

            gotoxy(43,7);limpiar_cuadro();
            for(int i=0;i<27;i++){
                gotoxy(46-i,7);cout<<p[medio].termino; 
                Sleep(40);
                gotoxy(43-i,7);limpiar_cuadro();
            }

            inicio=medio+1;//buscar en la mitad superior a la actual
            
        }
        else{

            gotoxy(43,7); limpiar_cuadro();
            gotoxy(46,7);cout<<p[medio].termino;

            cambio_color(3);
            gotoxy(44,10); cout<<"La palabra buscada";
            gotoxy(47,11); cout<<"Es menor";
            cambio_color(7);
            Sleep(1000);

            gotoxy(70,7);limpiar_cuadro();

            gotoxy(43,7);limpiar_cuadro();
            for(int i=0;i<27;i++){
                gotoxy(46+i,7);cout<<p[medio].termino;
                Sleep(40);
                gotoxy(43+i,7);limpiar_cuadro();
            }
 
            fin=medio-1;//buscar en la mitad inferior a la actual
        }
    }   
    diseno_iterativa_no_encontrado();

    _getch();
}

void limpiar_cuadro(){
    cout<<"                   ";
}

void diseno_iterativa(Concepto* p,int inicio, int fin){
    int x=15, y=5;
    //izquierda
    
    gotoxy(x,y);  cout<<"       INICIO";
    gotoxy(x,y+1);cout<<"â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”";
    gotoxy(x,y+2);cout<<"â”‚     "<<p[inicio].termino;
    gotoxy(x+21,y+2);cout<<"â”‚";
    gotoxy(x,y+3);cout<<"â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜";

    //centro
    gotoxy(x+27,y);  cout<<"        ";
    gotoxy(x+27,y+1);   cout<<"â•”â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•—";
    gotoxy(x+27,y+2);   cout<<"â•‘     ";
    gotoxy(x+21+27,y+2);cout<<"â•‘";
    gotoxy(x+27,y+3);cout<<"â•šâ•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•";
      
    //derecha
    gotoxy(x+(27*2),y);  cout<<"         FIN";
    gotoxy(x+(27*2),y+1);cout<<"â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”";
    gotoxy(x+(27*2),y+2);cout<<"â”‚     "<<p[fin].termino;
    gotoxy(x+21+(27*2),y+2);cout<<"â”‚";
    gotoxy(x+(27*2),y+3);cout<<"â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜";
}

void diseno_iterativa_encontrado(){
    system("cls");
    int x=15, y=5;
    
    cambio_color(6);
    gotoxy(x+27,y);  cout<<"      EUREKA!!!";
    gotoxy(x+27,y+1);   cout<<"â•”â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•—";
    gotoxy(x+27,y+2);   cout<<"â•‘     ";
    gotoxy(x+21+27,y+2);cout<<"â•‘";
    gotoxy(x+27,y+3);cout<<"â•šâ•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•";
    cambio_color(11);
    gotoxy(x+27,y+5);cout<<"     DEFINICIÃ“N:";
}

void diseno_iterativa_no_encontrado(){
    system("cls");
    int x=15, y=5;
    
    cambio_color(14);
    gotoxy(x+27,y);  cout<<"     Â¡OH NO!";
    gotoxy(x+27,y+1);   cout<<"â•”â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•—";
    gotoxy(x+27,y+2);   cout<<"â•‘    NO ENCONTRADO";
    gotoxy(x+21+27,y+2);cout<<"â•‘";
    gotoxy(x+27,y+3);cout<<"â•šâ•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•";
    cambio_color(12);
}

//FUNCIONES AUXILIARES
void gotoxy(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void cambio_color(int x){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
}

void ocultarCursor(){
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100; 
    info.bVisible = FALSE; 
    SetConsoleCursorInfo(consoleHandle, &info);
}

string mayusculas(string cadena){
    for(int i=0;cadena[i]!='\0';i++){
        if(cadena[i]>='a' && cadena[i]<='z'){
            cadena[i]=cadena[i]-32;
        }
    }
    return cadena;
}
