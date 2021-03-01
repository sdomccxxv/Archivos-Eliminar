#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;
const char *nombre_archivo = "archivo.dat";

struct Estudiante {
	int codigo;
	char nombres[50];
	char apellidos[50];
	int telefono;
};

void ingresar();
void abrir();
void modificar();
void buscar_id();

main(){
	/*ingresar();*/
	abrir();
	/*modificar();*/
	buscar_id();
}

void abrir(){

	system("cls");
	FILE* archivo = fopen(nombre_archivo,"rb");
	if (!archivo){
		archivo = fopen(nombre_archivo,"w+b");
	}

	Estudiante estudiante;
	int registro = 0;
	fread(&estudiante,sizeof(Estudiante),1,archivo);

	cout<<"_____________________________________________________________________________________________"<<endl;
	cout<<"id |"<<"Codigo  |"<<"Nombres      |"<<"Apellidos      |"<<"Telefono    |"<<endl;

	do{
		cout<<"_____________________________________________________________________________________________"<<endl;
		cout<<registro<<" | "<<estudiante.codigo<<" | "<<estudiante.nombres<<" | "<<estudiante.apellidos<<" | "<<estudiante.telefono<<endl;
		fread(&estudiante,sizeof(Estudiante),1,archivo);
		registro +=1;
	} while(feof(archivo)==0);

	fclose(archivo);
}

void ingresar(){
	char continuar;
	FILE* archivo = fopen(nombre_archivo,"ab");
	Estudiante estudiante;
	string nombre,apellido;

	do{
		fflush(stdin);
		cout<<"Ingrese el Codigo:";
		cin>>estudiante.codigo;
		cin.ignore();
		cout<<"Ingrese los Nombres:";
		getline(cin,nombre);
		strcpy(estudiante.nombres,nombre.c_str());
		cout<<"Ingrese los Apellidos:";
		getline(cin,apellido);
		strcpy(estudiante.apellidos,apellido.c_str());
		cout<<"Ingrese el Telefono:";
		cin>>estudiante.telefono;

		fwrite(&estudiante,sizeof(Estudiante),1,archivo);

		cout<<"Desea ingresar otro dato (s/n): ";
		cin>>continuar;
	}while(continuar == 's'||continuar == 'S');

	fclose(archivo);
	abrir();
}

void modificar (){
	FILE* archivo = fopen(nombre_archivo, "r+b");
	int id;
	string nombre, apellido;
	Estudiante estudiante;
	
	cout<<"Ingrese el ID que desea modificar: ";
	cin>>id;
	fseek(archivo, id*sizeof(Estudiante), SEEK_SET);
	
	cout<<"Ingrese el Codigo:";
	cin>>estudiante.codigo;
	cin.ignore();
	cout<<"Ingrese los Nombres:";
	getline(cin,nombre);
	strcpy(estudiante.nombres,nombre.c_str());
	cout<<"Ingrese los Apellidos:";
	getline(cin,apellido);
	strcpy(estudiante.apellidos,apellido.c_str());
	cout<<"Ingrese el Telefono:";
	cin>>estudiante.telefono;
	
	fwrite(&estudiante, sizeof(Estudiante), 1, archivo);
	fclose(archivo);
	abrir();
}

void buscar_id(){
	FILE* archivo = fopen(nombre_archivo, "rb");
	
	int pos = 0;
	cout<<"Que id o registro desea ver: ";
	cin>>pos;
	fseek(archivo, pos*sizeof(Estudiante), SEEK_SET);
	
	Estudiante estudiante;
	fread(&estudiante, sizeof(Estudiante), 1, archivo);
	cout<<"______________________"<<pos<<"______________________"<<endl;
	cout<<"Codigo: "<<estudiante.codigo<<endl;
	cout<<"Nombre: "<<estudiante.nombres<<endl;
	cout<<"Apellidos: "<<estudiante.apellidos<<endl;
	cout<<"Telefono: "<<estudiante.telefono<<endl;
	
	fclose(archivo);	
}

void buscar_codigo(){

	FILE* archivo = fopen(nombre_archivo,"rb");	
	int pos=0,indice=0,cod=0;

	cout<<"Que codigo desea ver: ";
	cin>>cod;

	Estudiante estudiante;
	fread(&estudiante,sizeof(Estudiante),1,archivo);	

	do{
		if(estudiante.codigo == cod)	{
	  	cout<<"Codigo: "<<estudiante.codigo<<endl;
	  	cout<<"Nombres: "<<estudiante.nombres<<endl;
	  	cout<<"Apellidos: "<<estudiante.apellidos<<endl;
	  	cout<<"Telefono: "<<estudiante.telefono<<endl;
	  }

	  fread(&estudiante,sizeof(Estudiante),1,archivo);	

	} while(feof(archivo)==0);

	

	

	

	fclose(archivo);

}
