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
void buscar_codigo();
void eliminar_codigo();

main(){
	abrir();
	
	int opcion;
	
	do{
		cout<<"Ingrese la opcion que desea realizar: "<<endl;
		cout<<"1 - Ingresar"<<endl;
		cout<<"2 - Buscar"<<endl;
		cout<<"3 - Modificar"<<endl;
		cout<<"4 - Eliminar"<<endl;
		cout<<"5 - Salir"<<endl;
		cout<<"Ingrese una opcion: ";
		cin>>opcion;
		
		system("cls");
		switch(opcion){
			case 1:{
				ingresar();
				break;
			}
			case 2:{
				int b=0;
				cout<<"De que forma desea buscar"<<endl;
				cout<<"1. Por id"<<endl;
				cout<<"2. Por codigo"<<endl;
				cout<<"Ingrese la forma de busqueda: ";
				cin>>b;
				
				if(b==1){
					buscar_id();
				}else{
					buscar_codigo();
				}
	
				break;
			}
			case 3:{
				modificar();
				break;
			}
			case 4:{
				eliminar_codigo();
				break;
			}
			case 5:{
				return 0;
				break;
			}
		}
	}while(opcion != 5);
	
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
		cout<<"Ingrese el Codigo: ";
		cin>>estudiante.codigo;
		cin.ignore();
		cout<<"Ingrese los Nombres: ";
		getline(cin,nombre);
		strcpy(estudiante.nombres,nombre.c_str());
		cout<<"Ingrese los Apellidos: ";
		getline(cin,apellido);
		strcpy(estudiante.apellidos,apellido.c_str());
		cout<<"Ingrese el Telefono: ";
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

void eliminar_codigo(){
	FILE* archivo = fopen(nombre_archivo,"r+b");	
	int pos=0,indice=0,cod=0;

	cout<<"Que codigo desea eliminar: ";
	cin>>cod;

	Estudiante estudiante;
	fread(&estudiante,sizeof(Estudiante),1,archivo);
	
	FILE* temporal = fopen("temp.dat","w+b");	

	do{
		if(estudiante.codigo == cod){
		  	cout<<"Codigo: "<<estudiante.codigo<<endl;
		  	cout<<"Nombres: "<<estudiante.nombres<<endl;
		  	cout<<"Apellidos: "<<estudiante.apellidos<<endl;
		  	cout<<"Telefono: "<<estudiante.telefono<<endl;
  	
	  }else{
	  	fwrite(&estudiante,sizeof(Estudiante),1,temporal);
	  }
	  
	  fread(&estudiante,sizeof(Estudiante),1,archivo);	

	} while(feof(archivo)==0);

	fclose(archivo);
	fclose(temporal);
	
	remove("archivo.dat");
	rename("temp.dat", "archivo.dat");
	abrir();
}
