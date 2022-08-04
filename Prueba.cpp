/*Crear un pograma encargado del correcto procedimiento dentro de un centro de vacunacion:
Modulos:
- Verificacion de pacientes
- Registro de pacientes
- Vacunacion
- Stock de vacunas
- Eliminacion de vacunas
- Verificacion de enfermeros
- Registro de enfermeros*/

#include<iostream>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<time.h>
#include<iomanip>

using namespace std;

struct Registro1{
    char nombres[40];
    char apellidos[40];
    char sexo;
    int edad;
    char dni[9];
    char carneEx[9];
    char passport[11];
    int diaNac;
    int mesNac;
    int anioNac;
    char nacionalidad[20];
    char provincia[40];
    int diaVac;
    int mesVac;
    int anioVac;
    char lugarVac[100];
    char domicilio[100];
    char instLaboral[100];
    char celular[15];
    char correo[50];
    char dosis;
};

struct Registro2{
    char laboratorio[40];
    char codigo[15];
    char lote[10];
    int frascos;
    int numDosis;
    int diaVenc;
    int mesVenc;
    int anioVenc;
};

struct Registro3{
    char codigo[11];
    char nombres[40];
    char apellidos[40];
    char dni[9];
    char sexo;
    char turno;
};

void pestaniaAcceso(FILE *enfermeros, Registro3 enfer);
void pestaniaPrincipal();
void registroEnfermeros(FILE *enfermeros, Registro3 enfer);
int verificarAcceso(FILE *enfermeros, Registro3 enfer);
void permitirAcceso(FILE *enfermeros, Registro3 enfer);
void errorArchivos(FILE *enfermeros);
void verificarPaciente(FILE *paciente, Registro1 pacie);
void option(FILE *paciente, Registro1 pacie, int opt);
void regisPaciente(FILE *paciente, Registro1 pacie);

int main(){ //COLOCAR PESTANIAPRINCIPAL EN EL MAIN
    FILE *enfermeros;
    FILE *paciente;
    Registro1 pacie;
    Registro3 enfer;
    int opt;
    srand(time(NULL));    
    pestaniaAcceso(enfermeros,enfer);
    do{
        cin>>opt;
        option(paciente, pacie, opt);
    }
    while(opt!=6);
    system("pause");
    return 0;
}

void pestaniaPrincipal(){
    int option;
    system("cls");
    cout<<"Bienvenido a centro de vacunacion"<<endl;
    cout<<"Que desea realizar?"<<endl;
    cout<<setw(40)<<"Verificar paciente [1]"<<endl;
    cout<<setw(40)<<"Registrar paciente [2]"<<endl;
    cout<<setw(40)<<"Editar registro paciente [3]"<<endl;
    cout<<setw(40)<<"Registrar uso de vacuna [4]"<<endl;
    cout<<setw(40)<<"Editar el registro de vacunas [5]"<<endl;
    cout<<setw(40)<<"Eliminacion de vacunas [6]"<<endl;
}

void registroEnfermeros(FILE *enfermeros, Registro3 enfer){
    char dni[9];
    char codigo[11];
    enfermeros=fopen("Registro de enfermeros.txt","ab+");
    errorArchivos(enfermeros);
    cout<<"INGRESE LOS SIGUIENTES DATOS"<<endl;
    fflush(stdin);
    do{
        cout<<"DNI: ";
        gets(dni);
        if(strlen(dni)!=8)
            cout<<"Coloque correctamente su DNI"<<endl;
    }
    while(strlen(dni)!=8);
    while(!feof(enfermeros)){
        fread(&enfer,sizeof(enfer),1,enfermeros);
        if(strcmp(dni,enfer.dni)==0){
            cout<<"Este enfermero ya se encuentra registrado"<<endl;
            fclose(enfermeros);
            system("pause");
            return;
        }
    }
    memcpy(enfer.dni,dni,9);
    do{
        cout<<"Codido CEP: "<<endl;
        gets(enfer.codigo);
        if(strlen(enfer.codigo)!=10)
            cout<<"Asegurese de colocar bien su codigo CEP"<<endl;
    }
    while(strlen(enfer.codigo)!=10);
    cout<<"Nombres: ";
    gets(enfer.nombres);
    cout<<"Apellidos: ";
    gets(enfer.apellidos);
    cout<<"Sexo Masculino[M], Femenino[F]: ";
    cin>>enfer.sexo;
    enfer.sexo=toupper(enfer.sexo);
    cout<<"Turno Maniana[M], Tarde[T]: ";
    cin>>enfer.turno;
    enfer.turno=toupper(enfer.turno);
    fwrite(&enfer,sizeof(enfer),1,enfermeros);
    cout<<"Registrado con exito!!!"<<endl;
    fclose(enfermeros);
    cout<<"Presione ENTER"<<endl;
    system("pause");
    system("cls");
}

int verificarAcceso(FILE *enfermeros, Registro3 enfer){
    char aux[11];
    int simil=0;
    enfermeros=fopen("Registro de enfermeros.txt","ab+");
    errorArchivos(enfermeros);
    cout<<"Ingrese su codigo o DNI: ";
    fflush(stdin);
    do{
        gets(aux);
        if(strlen(aux)!=8 && strlen(aux)!=10)
            cout<<"Ingrese correctamente su DNI o codigo"<<endl;
    }
    while(strlen(aux)!=8 && strlen(aux)!=10);
    while(!feof(enfermeros)){
        fread(&enfer, sizeof(enfer),1, enfermeros);
        if(strcmp(aux,enfer.codigo)==0 || strcmp(aux,enfer.dni)==0)
            simil=1;
    }
    fclose(enfermeros);
    return simil;
}

void permitirAcceso(FILE *enfermeros, Registro3 enfer, int &aux){
    int verificador, reg=0;
    aux=0;
    verificador=verificarAcceso(enfermeros,enfer);
    system("cls");
    if(verificador==1)
        pestaniaPrincipal();
    else{
        cout<<"Usted no cuenta con acceso o ha colocado mal sus datos"<<endl;
        do{
            cout<<"Registrarse [1] Volver a intentar[0]: ";
            cin>>reg;
            if(reg!=1 && reg!=0)
                cout<<"Coloque una opcion valida"<<endl;
        }
        while(reg!=1 && reg!=0);
        aux=1;
        if(reg==1){
            system("cls");
            registroEnfermeros(enfermeros,enfer);
            return;
        }
    }
}

void pestaniaAcceso(FILE *enfermeros, Registro3 enfer){
    int option, aux;
    do{
    do{
        cout<<"Bienvenido al centro de vacunacion"<<endl;
        cout<<"Seleccione la accion a realizar"<<endl;
        cout<<"Acceder [1]"<<endl;
        cout<<"Registrarse [2]"<<endl;
        cin>>option;
        if(option!=1 && option!=2)
            cout<<"Coloque una opcion valida"<<endl;
    }
    while(option!=1 && option!=2);
    system("cls");
    if(option==2){
        registroEnfermeros(enfermeros,enfer);
        aux=1;
    }
    else
        permitirAcceso(enfermeros, enfer, aux);
    }
    while(aux==1);
}

void option(FILE *paciente, Registro1 pacie, int opt){
    system("cls");
    switch (opt){
        case 1: verificarPaciente(paciente,pacie);
            break;
        case 2: regisPaciente(paciente,pacie);
            break;
    }
}

void verificarPaciente(FILE *paciente, Registro1 pacie){
    char auxDoc[11];
    int aux;
    int ver;
    paciente=fopen("Registro de vacunado.txt","ab+");
    errorArchivos(paciente);
    do{
        cout<<"Tipo de documento de identidad DNI[1] Carne de extranjeria[2] Pasaporte[3]: ";
        cin>>aux;
        if(aux!=1 && aux!=2 && aux!=3)
            cout<<"Ingrese una opcion valida"<<endl;
    }
    while(aux!=1 && aux!=2 && aux!=3);
    fflush(stdin);
        switch (aux){
            case 1:
                do{
                    cout<<"DNI: ";
                    gets(auxDoc);
                    if(strlen(auxDoc)!=8){
                        cout<<"Coloque el numero de DNI correctamente"<<endl;
                        cout<<"Enter para volver a intentar"<<endl;
                        system("pause");
                        system("cls");
                    }
                }
                while(strlen(auxDoc)!=8);
                ver=0;
                while(!feof(paciente)){
                fread(&pacie,sizeof(pacie),1,paciente);
                if(strcmp(auxDoc,pacie.dni)==0){
                    ver++;
                    break;
                }
                }
                fclose(paciente);
                if(ver==1)
                    cout<<"EL ciudadano ya esta registrado"<<endl;
                else
                    cout<<"El ciudadano no esta registrado"<<endl;
                cout<<"Enter para volver a la pantalla principal";
                system("pause");
                pestaniaPrincipal();
                return;
                break;
            case 2:
                do{
                    cout<<"Carne de extranjeria: ";
                    gets(auxDoc);
                    if(strlen(auxDoc)!=8){
                        cout<<"Coloque el carne de extranjeria correctamente"<<endl;
                        cout<<"Enter para volver a intentar"<<endl;
                        system("pause");
                        system("cls");
                    }
                }
                while(strlen(auxDoc)!=8);
                ver=0;
                while(!feof(paciente)){
                fread(&pacie,sizeof(pacie),1,paciente);
                if(strcmp(auxDoc,pacie.carneEx)==0){
                    ver++;
                    break;
                }
                }
                fclose(paciente);
                if(ver==1)
                    cout<<"EL ciudadano ya esta registrado"<<endl;
                else
                    cout<<"El ciudadano no esta registrado"<<endl;
                cout<<"Enter para volver a la pantalla principal";
                system("pause");
                pestaniaPrincipal();
                return;
                break;
            case 3:
                do{
                    cout<<"Pasaporte: ";
                    gets(auxDoc);
                    if(strlen(auxDoc)!=10){
                        cout<<"Coloque el pasaporte correctamente"<<endl;
                        cout<<"Enter para volver a intentar"<<endl;
                        system("pause");
                        system("cls");
                    }
                }
                while(strlen(auxDoc)!=10);
                ver=0;
                while(!feof(paciente)){
                fread(&pacie,sizeof(pacie),1,paciente);
                if(strcmp(auxDoc,pacie.passport)==0){
                    ver++;
                    break;
                }
                }
                fclose(paciente);
                if(ver==1)
                    cout<<"EL ciudadano ya esta registrado"<<endl;
                else
                    cout<<"El ciudadano no esta registrado"<<endl;
                cout<<"Enter para volver a la pantalla principal";
                system("pause");
                pestaniaPrincipal();
                return;
                break;
        }
    }


void regisPaciente(FILE *paciente, Registro1 pacie){
    char auxDoc[11];
    char na[]="NA";
    int auxFecha, aux;
    paciente=fopen("Registro de vacunado.txt", "ab+");
    errorArchivos(paciente);
    //fflush(stdin);
    cout<<"REGISTRO DE PAVACUNADOS"<<endl;
    cout<<"INGRESE LOS SIGUIENTES DATOS"<<endl;
    do{
        cout<<"Tipo de documento de identidad DNI[1] Carne de extranjeria[2] Pasaporte[3]: ";
        cin>>aux;
        if(aux!=1 && aux!=2 && aux!=3)
            cout<<"Ingrese una opcion valida"<<endl;
    }
    while(aux!=1 && aux!=2 && aux!=3);
    fflush(stdin);
        switch (aux){
            case 1:
                do{
                    cout<<"DNI: ";
                    gets(auxDoc);
                    if(strlen(auxDoc)!=8){
                        cout<<"Coloque el numero de DNI correctamente"<<endl;
                        cout<<"Enter para volver a intentar"<<endl;
                        system("pause");
                        system("cls");
                    }
                }
                while(strlen(auxDoc)!=8);
                while(!feof(paciente)){
                fread(&pacie,sizeof(pacie),1,paciente);
                if(strcmp(auxDoc,pacie.dni)==0){
                    fclose(paciente);
                    cout<<"El paciente ya esta registrado"<<endl;
                    cout<<"Intente otra opcion"<<endl;
                    cout<<"Enter para volver a la pantalla principal"<<endl;
                    system("pause");
                    pestaniaPrincipal();
                    return;
                }
                }
                memcpy(pacie.dni,auxDoc,9);
                pacie.carneEx[0]='N';
                pacie.carneEx[1]='a';
                pacie.passport[0]='N';
                pacie.passport[1]='a';
                break;
            case 2:
                do{
                    cout<<"Carne de extranjeria: ";
                    gets(auxDoc);
                    if(strlen(auxDoc)!=8){
                        cout<<"Coloque el carne de extranjeria correctamente"<<endl;
                        cout<<"Enter para volver a intentar"<<endl;
                        system("pause");
                        system("cls");
                    }
                }
                while(strlen(auxDoc)!=8);
                while(!feof(paciente)){
                fread(&pacie,sizeof(pacie),1,paciente);
                if(strcmp(auxDoc,pacie.carneEx)==0){
                    fclose(paciente);
                    cout<<"El paciente ya esta registrado"<<endl;
                    cout<<"Intente otra opcion"<<endl;
                    cout<<"Enter para volver a la pantalla principal"<<endl;
                    system("pause");
                    pestaniaPrincipal();
                    return;
                }
                }
                memcpy(pacie.carneEx,auxDoc,9);
                pacie.dni[0]='N';
                pacie.dni[1]='a';
                pacie.passport[0]='N';
                pacie.passport[1]='a';
                break;
            case 3:
                do{
                    cout<<"Pasaporte: ";
                    gets(auxDoc);
                    if(strlen(auxDoc)!=10){
                        cout<<"Coloque el pasaporte correctamente"<<endl;
                        cout<<"Enter para volver a intentar"<<endl;
                        system("pause");
                        system("cls");
                    }
                }
                while(strlen(auxDoc)!=10);
                while(!feof(paciente)){
                fread(&pacie,sizeof(pacie),1,paciente);
                if(strcmp(auxDoc,pacie.passport)==0){
                    fclose(paciente);
                    cout<<"El paciente ya esta registrado"<<endl;
                    cout<<"Intente otra opcion"<<endl;
                    cout<<"Enter para volver a la pantalla principal"<<endl;
                    system("pause");
                    pestaniaPrincipal();
                    return;
                }
                }
                memcpy(pacie.passport,auxDoc,11);
                pacie.dni[0]='N';
                pacie.dni[1]='a';
                pacie.carneEx[0]='N';
                pacie.carneEx[1]='a';
                break;
        }
    
    cout<<"Nombres: ";
    gets(pacie.nombres);
    cout<<"Apellidos: ";
    gets(pacie.apellidos);
    cout<<"Sexo: ";
    cin>>pacie.sexo;
    pacie.sexo=toupper(pacie.sexo);
    cout<<"Edad: ";
    cin>>pacie.edad;
    do{
        auxFecha=0;
        cout<<"Fecha de nacimiento dia/mes/anio: ";
        cin>>pacie.diaNac>>pacie.mesNac>>pacie.anioNac;
        switch (pacie.mesNac)
        {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            if(pacie.diaNac<1 || pacie.diaNac>31)
                auxFecha=1;
            break;
        case 4: case 6: case 9: case 11:
            if(pacie.diaNac<1 || pacie.diaNac>30)
                auxFecha=1;
            break;
        case 2:
            if(pacie.anioNac%4==0){
                if(pacie.anioNac%100==0 && pacie.anioNac%400==0){
                    if(pacie.diaNac<1 || pacie.diaNac>29)
                    auxFecha=1;
                }
                else{
                    if(pacie.diaNac<1 || pacie.diaNac>28)
                    auxFecha=1; 
                }
            }
            else{
                if(pacie.diaNac<1 || pacie.diaNac>28)
                auxFecha=1;
            }
            break;
        default:
            auxFecha=1;
            break;
        }
        if(auxFecha==1)
            cout<<"Ingrese una fecha valida"<<endl;
    }
    while(auxFecha==1);
    fflush(stdin);
    cout<<"Nacionalidad: ";
    gets(pacie.nacionalidad);
    cout<<"Provincia: ";
    gets(pacie.provincia);
    do{
        auxFecha=0;
        cout<<"Fecha de vacunacion dia/mes/anio: ";
        cin>>pacie.diaNac>>pacie.mesNac>>pacie.anioNac;
        switch (pacie.mesNac)
        {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            if(pacie.diaNac<1 || pacie.diaNac>31)
                auxFecha=1;
            break;
        case 4: case 6: case 9: case 11:
            if(pacie.diaNac<1 || pacie.diaNac>30)
                auxFecha=1;
            break;
        case 2:
            if(pacie.anioNac%4==0){
                if(pacie.anioNac%100==0 && pacie.anioNac%400==0){
                    if(pacie.diaNac<1 || pacie.diaNac>29)
                    auxFecha=1;
                }
                else{
                    if(pacie.diaNac<1 || pacie.diaNac>28)
                    auxFecha=1; 
                }
            }
            else{
                if(pacie.diaNac<1 || pacie.diaNac>28)
                auxFecha=1;
            }
            break;
        default:
            auxFecha=1;
            break;
        }
        if(auxFecha==1)
            cout<<"Ingrese una fecha valida"<<endl;
    }
    while(auxFecha==1);
    fflush(stdin);
    cout<<"Lugar de Vacunacion: ";
    gets(pacie.lugarVac);
    cout<<"Domicilio: ";
    gets(pacie.domicilio);
    cout<<"Institucion laboral: ";
    gets(pacie.instLaboral);
    cout<<"Celular: ";
    gets(pacie.celular);
    cout<<"Correo: ";
    gets(pacie.correo);
    cout<<"Nro Dosis: ";
    cin>>pacie.dosis;
    fwrite(&pacie,sizeof(pacie),1,paciente);
    fclose(paciente);
    cout<<"REGISTRADO CON EXITO!!!"<<endl;
    cout<<"Enter para volver a la pantalla principal"<<endl;
    system("pause");
    system("cls");
    pestaniaPrincipal();
}

void errorArchivos(FILE *enfermeros){
    if(ferror(enfermeros)){
        cout<<"Error al abrir el resgitro"<<endl;
        fclose(enfermeros);
        exit(1);
    }
}