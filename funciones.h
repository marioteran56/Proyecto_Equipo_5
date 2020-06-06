#ifndef _FUNCIONES_H_
#define _FUNCIONES_H_

#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <fstream>
#include <stdexcept>
#include <ctime>
#include <typeinfo>

using namespace std;

/**
 *Variables globales externas
 */
extern int numMat, numAlu;

/**
 *Metodo que valida si una cadena es un entero valido
 *@param numeroEnCadena El parametro numeroEnCadena es el numero ingresado convertido en cadena
 *@return Regresara un booleano verdadero en caso de que la cadena sea un entero valido o un falso en caso contrario
 */
bool isValidInt(string numeroEnCadena) {
	int inicio = 0;
	int i = 0;
	bool valido = true;
	bool signo = false;
	size_t tamanioDeCadena = numeroEnCadena.size();

	if (tamanioDeCadena == 0)
		valido = 0;
	if (numeroEnCadena.at(0) == '-' || numeroEnCadena.at(0) == '+') {
		inicio = 1;
		signo = true;
	}
	if (signo && tamanioDeCadena == 1)
		valido = false;

	for (i = inicio; valido && i < tamanioDeCadena; i++) {
		if (!isdigit(numeroEnCadena.at(i)))
			valido = false;
	}
	return valido;
}


/**
 *Metodos que nos validaran si el valor ingresado es un entero valido o mayor o igual a 1
 *@param numeroEnCadena El parametro numeroEnCadena es el numero ingresado convertido en cadena
 *@param num numero ingresado por el usuario
 */
void revisarNumero(int& num) {
	string aux;
	bool condicion = false;
	while (condicion == false) {
		cin >> aux;
		try {
			if (isValidInt(aux) == false)
				throw aux;
			if (stoi(aux) < 1)
				throw stoi(aux);
			condicion = true;
		}
		catch (string e) {
			cout << "\tEl numero " << e << " es un numero entero invalido." << endl;
			cout << "\tReingrese el numero: ";
		}
		catch (int e) {
			cout << "\tEl numero " << e << " es un numero invalido. Se deben ingresar numeros mayores o iguales a 1." << endl;
			cout << "\tReingrese el numero: ";
		}
	}
	num = stoi(aux);
}

/**
 *En esta estructura se definen todo lo que tenga que ver con el alumno
 */
struct Alumno {
	//Campos de la estructura Alumno
	string nombres, apellidos;
	string ID; //Matricula del alumno
	double promedio;
	int grado;
	string* calificaciones;

	/**
	*Metodo Constructor para la estructura alumno
	*/
	Alumno() {
		nombres = "Indefinido";
		apellidos = "Indefinido";
		ID = "";
		promedio = 0;
		grado = 0;
		calificaciones = NULL;
	}

	/**
	*Metodo de Sobrecarga para operador !=
	*@param obj Recibe un objeto del tipo alumno
	*@return Regresa verdadero si los parametros son distintos
	*/
	bool operator != (Alumno const& obj) {
		return ((nombres != obj.nombres) || (apellidos != obj.apellidos) || (ID != obj.ID)
			|| (promedio != obj.promedio) || (calificaciones != obj.calificaciones) || (grado != obj.grado));
	}

	/**
	*Sobrecarga del operador >> para leer los datos del alumno
	*@param in Recibe un objeto de tipo input
	*@param ptr Recibe un objeto del tipo alumno
	*@return Regresa los datos de tipo in
	*/
	friend istream& operator>>(istream& in, Alumno& ptr) {
		cout << "\tIngrese los nombres del alumno: ";
		cin.ignore();
		getline(cin, ptr.nombres);
		cout << "\tIngrese los apellidos del alumno: ";
		getline(cin, ptr.apellidos);
		cout << "\tIngrese el grado de el alumno: ";
		revisarNumero(ptr.grado);
		cout << endl;
		return in;
	}

	/**
	 *Sobrecarga del operador << para mostrar los datos del alumno
	 *@param ot Recibe un objeto de tipo output
	 *@param ptr Recibe un objeto del tipo alumno
	 *@return Regresa los datos de tipo ot
	 */
	friend ostream& operator<<(std::ostream& ot, const Alumno& ptr) {
		ot << "\tNombres: " << ptr.nombres << endl;
		ot << "\tApellidos: " << ptr.apellidos << endl;
		ot << "\tMatricula: " << ptr.ID << endl;
		ot << "\tPromedio: " << ptr.promedio << endl;
		ot << "\tGrado: " << ptr.grado << endl;
		return ot;
	}

	/**
	 *Metodo para leer los datos del alumno guardados en el archivo .txt
	 *@param file El parametro file es el archivo .txt del cual se van a leer los datos
	 *@param linea El parametro linea es la linea del archivo que se esta leyendo
	 *@param ptr El parametro es un puntero del tipo Alumno
	 */
	void leerDatos(ifstream& file, string linea, Alumno& ptr) {
		getline(file, linea);
		ptr.nombres = linea;
		getline(file, linea);
		ptr.apellidos = linea;
		getline(file, linea);
		ptr.ID = linea;
		getline(file, linea);
		ptr.promedio = stod(linea);
		getline(file, linea);
		ptr.grado = stoi(linea);
	}

	/**
	 *Metodo para guardar los datos del alumno en el archivo .txt
	 *@param file El parametro file es el archivo .txt en el que se van a guardar los datos
	 *@param ptr El parametro es un puntero del tipo Alumno
	 */
	void guardarEnArchivo(ofstream& file, Alumno& ptr) {
		file << ptr.nombres << endl;
		file << ptr.apellidos << endl;
		file << ptr.ID << endl;
		file << ptr.promedio << endl;
		file << ptr.grado << endl;
	}

	/**
	 *Metodo para mostrar cual alumno se elimino
	 *@param ptr El parametro es un puntero del tipo Alumno
	 */
	void printEliminado(Alumno& ptr) {
		cout << "El alumno " << ptr.nombres << " " << ptr.apellidos << ", ha sido eliminado." << endl;
	}

	/**
	 *Metodo que muestra un mensaje pidiendo el ID del alumno
	 */
	void printID() {
		cout << "Ingrese la matricula del alumno: ";
	}

	/**
	 *Metodo para obtener el id (matricula) del alumno
	 *@return Regresa el id del alumno
	 */
	string getID(Alumno& ptr) {
		return ptr.ID;
	}
};

/**
 *En esta estructura se definen todo lo que tenga que ver con la materia
 */
struct Materia {
	/**
	 *Campos de la estructura Alumno
	 */
	string nombre;
	string ID;
	int grado;

	/**
	 *Metodo Constructor para la estructura alumno
	 */
	Materia() {
		nombre = "Indefinido";
		ID = "Indefinido";
		grado = 0;
	}

	/**
	 *Metodo para la Sobrecarga del operador != (Diferente)
	 *@param obj Obj es un objeto del tipo Materia
	 *@return Regresa verdadero si el parametro es diferente a los datos de la estructura
	 */
	bool operator != (Materia const& obj) {
		return ((nombre != obj.nombre) || (ID != obj.ID) || (grado != obj.grado));
	}

	/**
	 *Metodo para la Sobrecarga del operador >> para leer los datos de la materia
	 *@param in in es un parametro del tipo input
	 *@param obj Obj es un objeto del tipo Materia
	 *@return Regresa los valores de in
	 */
	friend istream& operator>>(istream& in, Materia& ptr) {
		cout << "\tIngrese el nombre de la materia: ";
		cin.ignore();
		getline(cin, ptr.nombre);
		cout << "\tIngrese el grado de la materia: ";
		revisarNumero(ptr.grado);
		cout << endl;
		return in;
	}

	/**
	 *Metodo para la Sobrecarga del operador << para mostrar los datos de la materia
	 *@param ot ot es un parametro del tipo output
	 *@param obj Obj es un objeto del tipo Materia
	 *@return Regresa los valores de ot
	 */
	friend ostream& operator<<(std::ostream& ot, const Materia& ptr) {
		ot << "\tNombre: " << ptr.nombre << endl;
		ot << "\tClave: " << ptr.ID << endl;
		ot << "\tGrado: " << ptr.grado << endl;
		return ot;
	}

	/**
	 *Metodo para leer los datos de la materia en el archivo .txt
	 *@param file file es el archivo .txt de las materias
	 *@param linea linea es la linea que se esta leyendo del archivo
	 *@param obj obj es un punturero del tipo materia
	 */
	void leerDatos(ifstream& file, string linea, Materia& ptr) {
		getline(file, linea);
		ptr.nombre = linea;
		getline(file, linea);
		ptr.ID = linea;
		getline(file, linea);
		ptr.grado = stoi(linea);
	}

	/**
	 *Metodo para guardar los datos de la materia en el archivo .txt
	 *@param file file es el archivo .txt de las materias
	 *@param obj obj es un punturero del tipo materia
	 */
	void guardarEnArchivo(ofstream& file, Materia& ptr) {
		file << ptr.nombre << endl;
		file << ptr.ID << endl;
		file << ptr.grado << endl;
	}

	/**
	 *Metodo para mostrar cual materia se elimino
	 *@param obj obj es un punturero del tipo materia
	 */
	void printEliminado(Materia& ptr) {
		cout << "La materia " << ptr.nombre << ", ha sido eliminada." << endl;
	}

	/**
	 *Metodo que muestra un mensaje pidiendo el ID de la materia
	 */
	void printID() {
		cout << "Ingrese la clave de la materia: ";
	}

	/**
	 *Metodo que regresa el ID de la materia (clave)
	 *@param ptr ptr es un puntero del tipo materia
	 *@return regresa el id de la materia
	 */
	string getID(Materia& ptr) {
		return ptr.ID;
	}
};

/**
 *Excepcion generica para la clase
 */
struct CalifasException : public exception {
	const char* what() const throw() {
		return "Todos los alumnos tienen calificaciones capturadas.";
	}
};

/**
 * Metodo que muestra las opciones del menu
 */
void menu() {
	cout << "\n\n\t\t***************MENU***************" << endl;
	cout << "\t\t1) Registrar alumnos" << endl
		<< "\t\t2) Eliminar un alumno" << endl
		<< "\t\t3) Mostrar alumnos" << endl
		<< "\t\t4) Registrar materias" << endl
		<< "\t\t5) Eliminar materia" << endl
		<< "\t\t6) Mostrar materias" << endl
		<< "\t\t7) Capturar calificaciones" << endl
		<< "\t\t8) Buscar promedios" << endl
		<< "\t\t9) Guardar" << endl
		<< "\t\t10) Salir y guardar" << endl << endl;
	cout << "\t\t**********************************" << endl;
	cout << "\t\tSeleccione una opcion: ";

}

/**
 *Metodo que busca alumnos dependiendo de el promedio que se ingrese y mostrara el porcentaje de alumnos
 *debajo y por encima del promedio
 *@param ptr El parametro ptr es un puntero del tipo estructura Alumno
 *@param n El parametro n es el numero de alumnos guardados
 */
void buscarPromedios(Alumno* ptr, int n) {
	try {
		if (!ptr)
			throw "Aun no se han registrado alumnos.";
		for (int i = 0; i < n; i++)
			if (ptr[i].promedio == 0)
				throw "Existen alumnos sin promedios capturados.";

		int num = 0;
		bool condicion = false;
		float porcentaje = 0;
		string promedioMin;
		cout << "Ingresa el promedio minimo requerido: " << endl;
		while (condicion == false) {
			cin >> promedioMin;
			try {
				if (isValidInt(promedioMin) == false)
					throw 1;
				if ((stoi(promedioMin)) < 0 || (stoi(promedioMin)) > 100)
					throw 2;
				condicion = true;
			}
			catch (int e) {
				if (e == 1)
					cout << "Numero invalido." << endl;
				if (e == 2)
					cout << "Error el numero debe ser mayor a 0 y menor o igual a 100" << endl;
				cout << "Ingresa de nuevo el promedio: ";
			}
		}

		for (int i = 0; i < n; i++) {
			if (ptr[i].promedio >= (stoi(promedioMin))) {
				cout << endl << ptr[i].nombres << " " << ptr[i].apellidos << endl;
				cout << "Promedio: " << ptr[i].promedio << endl;
				num++;
			}
		}

		porcentaje = ((float)num / (float)n) * 100;
		cout << endl << "Numero de alumnos con promedio mayor o igual a " << promedioMin << " es: " << num << endl;
		cout << "Porcentaje de alumnos con promedio mayor o igual a " << promedioMin << ": " << porcentaje << endl;
	}
	catch (const char* msgErr) {
		cout << msgErr << endl;
		return;
	}
}

/**
 *Metodo que guarda los datos ingresados en un archivo .txt
 *@param ptr El parametro ptr es un puntero del tipo de estructura usada
 *@param num El parametro num es la cantidad de registros
 *@param fileName El parametro fileName es el nombre del archivo .txt donde se vana a guardar los datos
 */
template <class typeStruct>
void guardarDatos(typeStruct* ptr, int num, string fileName) {
	ofstream archivoA;
	archivoA.open(fileName);
	if (ptr) {
		try {
			archivoA.exceptions(ifstream::failbit);
		}
		catch (const ios_base::failure& ibf) {
			cout << ibf.what() << ": Se va a crear el archivo." << endl;
			ofstream archivoA(fileName);
			archivoA.open(fileName);
		}
		archivoA.clear();
		archivoA << num << endl;
		for (int i = 0; i < num; i++)
			ptr[i].guardarEnArchivo(archivoA, ptr[i]);
		archivoA.close();
	}
	else {
		try {
			archivoA.exceptions(ifstream::failbit);
			archivoA.close();
			remove(fileName.c_str());
		}
		catch (const ios_base::failure& ibf) {
			cout << ibf.what() << "El archivo no existe.";
			return;
		}
	}
}

/**
 *Metodo que sirve para leer el archivo .txt generado con anterioridad y ver si hay datos de materias en el
 *@param ptr El parametro ptres un puntero del tipo de estructura usda
 *@param n El parametro n es la direccion de memoria donde se almacena el numero de registros
 *@return Una direccion de memoria del tipo de estructura utilizado (Materio o Alumno) para continuar almacenando datos
 */
template <class typeStruct>
typeStruct* escanear(typeStruct* ptr, int& n, string nombreArchivo) {
	ifstream archivo;
	try {
		archivo.open(nombreArchivo);
		archivo.exceptions(ifstream::failbit);

		string linea;
		getline(archivo, linea);
		n = stoi(linea);
		ptr = reservarMemoria(ptr, n);
		for (int i = 0; i < n; i++) {
			ptr[i].leerDatos(archivo, linea, ptr[i]);
		}

		archivo.close();
		return ptr;
	}
	catch (const ios_base::failure& ibf) {
		cout << ibf.what() << endl;
		return NULL;
	}
}

/**
 *Metodo que reserva memoria en el stack para cualquiere estructura
 *@param ptr El parametro ptr es un puntero a la direccion de memoria que se va a reservar
 *@param n El parametro n es la cantidad de espacios que se van a reservar
 *@return Una direccion de memoria del tipo de estructura utilizado (Materio o Alumno) (La primer direccion)
 */
template<class typeStruct>
typeStruct* reservarMemoria(typeStruct* ptr, int n) {
	try {
		if (ptr)
			delete[] ptr;
		ptr = new (nothrow) typeStruct[n];
		if (!ptr)
			throw 5; //No se reservo memoria correctamente
		return ptr;
	}
	catch (int e) {
		cout << "\tError " << e << ". No se pudo reservar memoria." << endl;
		cout << "\tEl programa sera terminado." << endl;
		exit(1);
	}
}

/**
 *Metodo que reordena la memoria al ingresar un dato nuevo
 *@param ptr El parametro ptr es un puntero a la direccion de memoria que se esta utilizando
 *@param n El parametro n es la cantidad de espacios de memoria ya usados
 *@return Una direccion de memoria del tipo de estructura utilizado (Materio o Alumno) (La primer direccion)
 */
template <class typeStruct>
typeStruct* realocarMemoria(typeStruct* ptr, int& n) {
	int num; //numero de registros nuevos
	cout << "\n\tSe tienen actualmente " << n << endl;
	cout << "\tIngrese la cantidad  que desea registrar: ";
	revisarNumero(num);
	try {
		if (num < 1)
			throw 5; //Valor invalido en num
		n += num; //Al numero ya existente se le suma los que se van a agregar
		typeStruct* dummyPtr = NULL;
		dummyPtr = reservarMemoria(dummyPtr, n);
		for (int i = num; i < n; i++)
			dummyPtr[i] = ptr[i - num];
		capturarRegistros(dummyPtr, num);
		delete[] ptr;
		ptr = dummyPtr;
		dummyPtr = NULL;
	}
	catch (int e) {
		cout << "\tError " << e << ": Valor menor o igual a cero" << endl;
	}
	return ptr;
}

/**
 *Metodo libera la memoria del stack cuando se elimina un registro
 *@param ptr El parametro ptr es un puntero a la direccion de memoria que se esta utilizando
 *@param n El parametro n es la cantidad de espacios de memoria ya usados
 *@return Una direccion de memoria del tipo de estructura utilizado (Materio o Alumno) (La primer direccion)
 */
template <class typeStruct>
typeStruct* liberarMemoria(typeStruct* ptr, int& n) {
	try {
		if (!ptr)
			throw "\tAun no hay datos ingresados en esta opcion";
		int op;
		string id;
		cout << "\tSe tienen actualmente " << n << " registros." << endl;
		cout << "\t¿Seguro que quiere eliminar uno?" << endl
			<< "\t    1)Si    2)No" << endl;
		revisarNumero(op);
		if (op == 1) {
			n -= 1;
			if (n == 0) {
				ptr[0].printEliminado(ptr[0]);
				delete[] ptr;
				ptr = NULL;
			}
			else {
				typeStruct varVacio;
				bool condicion = false;
				typeStruct* dummyPtr = NULL;
				dummyPtr = reservarMemoria(dummyPtr, n);
				ptr[0].printID();
				while (condicion == false) {
					cin >> id;
					try {
						for (int i = 0; i < (n + 1); i++) {
							if (ptr[i].getID(ptr[i]) == id) {
								condicion = true;
								break;
							}
						}
						if (condicion == false)
							throw id;
					}
					catch (string e) {
						cout << "\tNo hay coincidencias con: " << e << endl;
						cout << "\tReingrese el ID a buscar: " << endl;
						continue;
					}
					condicion = true;
				}
				for (int i = 0; i < (n + 1); i++) {
					if (ptr[i].getID(ptr[i]) == id) {
						ptr[i].printEliminado(ptr[i]);
						ptr[i] = varVacio;
					}
				}
				int aux = 0;
				for (int i = 0; i < (n + 1); i++) {
					if (ptr[i] != varVacio) {
						dummyPtr[aux] = ptr[i];
						aux++;
					}
				}
				delete[] ptr;
				ptr = dummyPtr;
				dummyPtr = NULL;
			}
		}
	}
	catch (const char* msgErr) {
		cout << msgErr << endl;
	}
	return ptr;
}

/**
 *Metodo para capturar los datos utulizando la sobrecarga de los operadores >>
 *@param ptr El parametro ptrDummy es un puntero a la direccion de memoria que se esta utilizando
 *@param n El parametro n es la cantidad de espacios de memoria ya usados
 */
template <class typeStruct>
void capturarRegistros(typeStruct* ptr, int n) {
	for (int i = 0; i < n; i++) {
		cout << "\tRegistro " << i + 1 << endl;
		cin >> ptr[i];
		ptr[i].ID = generarID(ptr);
	}
}

/**
 *Metodo para mostrar los datos utulizando la sobrecarga de los operadores <<
 *@param ptr El parametro ptr es un puntero a la direccion de memoria que se esta utilizando
 *@param n El parametro n es la cantidad de espacios de memoria ya usados
 */
template <class typeStruct>
void mostrar(typeStruct* ptr, int n) {
	try {
		if (!ptr)
			throw "\tAun no se hay registros.";
		
		for (int i = 0; i < n; i++) {
			cout << "\n\tRegistro: " << i + 1 << endl;
			cout << ptr[i] << endl;
		}
	}
	catch (const char* msgErr) {
		cout << msgErr << endl;
	}
}

/**
 *Metodo para capturar las califciaciones de los alumnos asociadas a las materias
 *@param ptrA El parametro ptr es un puntero a la direccion de memoria que se esta utilizando con los alumnos
 *@param ptrM El parametro ptr es un puntero a la direccion de memoria que se esta utilizando con las materias
 *@param numA El parametro n es la cantidad de espacios de memoria ya usados en los alumnos
 *@param numB El parametro n es la cantidad de espacios de memoria ya usados ebn las materias
 */
void capturarCalifas(Alumno* ptrA, Materia* ptrM, int numA, int numM) {
	int grado = 0;
	try {

		if (!ptrM)
			throw "\tAun no se han registrado materias.";
		if (!ptrA)
			throw "\tAun no se han registrado alumnos.";
		int aux = 0;
		int auxGrado = 0;
		cout << "\tIngresa el grado donde va a capturar calificaciones: ";
		revisarNumero(grado); //Leer el grado y revisar si es un entero valido

		for (int i = 0; i < numA; i++) {
			if (ptrA[i].promedio != 0)
				aux++;
			if (ptrA[i].grado != grado)
				auxGrado++;
			if (aux == numA)
				throw CalifasException();
			if (auxGrado == numA)
				throw "\tNo existe ese grado para Alumnos";
		}
		auxGrado = 0;
		for (int i = 0; i < numM; i++) {
			if (ptrM[i].grado != grado)
				auxGrado++;
			if (auxGrado == numM)
				throw "\tNo existe ese grado para Materias";
		}
		
	}
	catch (const char* msgErr) {
		cout << msgErr << endl;
		return;
	}
	catch (CalifasException& e) {
		int op;
		cout << e.what() << endl;
		cout << "\t¿Desea volver a capturar las calificaciones?" << endl
			<< "\t    1)Si    2)No" << endl;
		revisarNumero(op);
		if (op == 1) {
			for (int i = 0; i < numA; i++)
				ptrA[i].promedio = 0;
		}
		else {
			return;
		}
	}

	int materiasGrado = 0;
	for (int i = 0; i < numA; i++) {

		if (ptrA[i].promedio != 0 || (ptrA[i].grado != grado))
			continue;

		ptrA[i].promedio = 0;
		ptrA[i].calificaciones = reservarMemoria(ptrA[i].calificaciones, numM);
		cout << endl << "\tAlumno: " << ptrA[i].nombres << " " << ptrA[i].apellidos << endl;
		materiasGrado = 0;
		for (int j = 0; j < numM; j++) {
			try {

				if (ptrM[j].grado != ptrA[i].grado)
					continue;

				materiasGrado++;
				cout << "\tIngrese la calificacion de la materia " << ptrM[j].nombre << " [0 - 100]: ";
				cin >> ptrA[i].calificaciones[j];

				if (isValidInt(ptrA[i].calificaciones[j]) == false)
					throw ptrA[i].calificaciones[j];

				if (stoi(ptrA[i].calificaciones[j]) < 0 || stoi(ptrA[i].calificaciones[j]) > 100)
					throw stoi(ptrA[i].calificaciones[j]);



				ptrA[i].promedio += stoi(ptrA[i].calificaciones[j]);
			}
			catch (string invalidInt) {
				cout << "\tEl valor " << invalidInt << " es un numero entero invalido." << endl;
				materiasGrado--;
				j--;
				continue;
			}
			catch (int invalidInt) {
				cout << "\tEl valor " << invalidInt << " es un numero entero fuera del rango de 0 a 100." << endl;
				materiasGrado--;
				j--;
				continue;
			}

		}

		ptrA[i].promedio = ptrA[i].promedio / materiasGrado;
	}

	cout << "Se han registrado todos los promedios" << endl;

	for (int i = 0; i < numA; i++) {
		ptrA[i].calificaciones = NULL;
		delete[] ptrA[i].calificaciones;
	}
}

/**
 *Metodo para ordenar alfabeticamente los alumnos
 *@param ptr El parametro ptr es un puntero a la direccion de memoria que se esta utilizando con los alumnos
 *@param n El parametro n es la cantidad de espacios de memoria ya usados en los alumnos
 */
void ordenarAlumnos(Alumno* ptr, int n) {
	for (int i = 0; i < (n - 1); i++) {
		if (ptr[i + 1].nombres < ptr[i].nombres) {
			Alumno c = ptr[i + 1];
			ptr[i + 1] = ptr[i];
			ptr[i] = c;
			i = -1;
		}
	}
}

/**
 *Metodo para ordenar alfabeticamente las materias
 *@param ptr El parametro ptr es un puntero a la direccion de memoria que se esta utilizando con las materias
 *@param n El parametro n es la cantidad de espacios de memoria ya usados en las materias
 */
void ordenarMaterias(Materia* ptr, int n) {
	for (int i = 0; i < (n - 1); i++) {
		if (ptr[i + 1].nombre < ptr[i].nombre) {
			Materia c = ptr[i + 1];
			ptr[i + 1] = ptr[i];
			ptr[i] = c;
			i = -1;
		}
	}
}

/**
 *Metodo para generar in ID aleatorio del alumno o materia
 *@param ptr El parametro ptr es un puntero a la direccion de memoria que se esta utilizando
 *@return Un ID unico para cada alumno o materia
 */
template <class typeStruct>
string generarID(typeStruct* ptr) {
	srand((int)time(NULL));
	string id;
	int tam;
	if (typeid(ptr) == typeid(Alumno*)){
		tam = numAlu;
		id = "a" + to_string((rand() % 340000) + 300000); //Genera numeros aleatorios de 6 digitos
	}
	if (typeid(ptr) == typeid(Materia*)){
		tam = numMat;
		id = "M" + to_string((rand() % 10000) + 1000);	//Genera numeros aleatorios de 5 digitos
	}
	for (int i = 0; i < tam; i++) {
		if (ptr[i].ID == id) {	//Se valida si existen datos previos y si el ID ingresado ya existe
			i--;
			id = generarID(ptr);	//Uso de recursividad
			break;
		}
	}
	return id;
}


/**
 *Apuntador a metodo para ordenar alfabeticamente los alumnos
 *@param ptr El parametro ptr es un puntero a la direccion de memoria que se esta utilizando con los alumnos
 *@param n El parametro n es la cantidad de espacios de memoria ya usados en los alumnos
 */
void (*ordenar)(Alumno*, int) = ordenarAlumnos;

#endif
