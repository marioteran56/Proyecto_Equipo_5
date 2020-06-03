#include "functions.h"
/*
 * Metodo principal (Main) donde se encuntra el menu de opciones principal
 */
int main() {
	setlocale(LC_ALL, "");
	string fileNameAlumnos = "datosAlumno.txt";
	string fileNameMaterias = "datosMateria.txt";
	int ope, numMat, numAlu;
	Alumno* ptrAlumno = NULL;
	Materia* ptrMateria = NULL;
	ptrAlumno = escanear(ptrAlumno, numAlu, fileNameAlumnos);
	ptrMateria = escanear(ptrMateria, numMat, fileNameMaterias);

	do {
		system("cls");
		menu();
		revisarNumero(ope);
		system("cls");
		switch (ope) {
		case 1:
			if (ptrAlumno) { //Como ya existen registros se debe reacomodar la memoria
				ptrAlumno = realocarMemoria(ptrAlumno, numAlu);
			}
			else { //Esto es en caso de que no exista nigun registro
				cout << "\n\tIngrese la cantidad de alumnos que desea registrar: ";
				revisarNumero(numAlu);
				ptrAlumno = reservarMemoria(ptrAlumno, numAlu);
				capturarRegistros(ptrAlumno, numAlu);
			}
			ordenarAlumnos(ptrAlumno, numAlu); //Ordena los alumnos alfabeticamente
			break;
		case 2:
			if (ptrAlumno) {
				ptrAlumno = liberarMemoria(ptrAlumno, numAlu);
			}
			else {
				cout << "\tAun no se tienen alumnos registrados." << endl;
			}
			break;
		case 3:
			mostrar(ptrAlumno, numAlu);
			break;
		case 4:
			if (ptrMateria) {
				ptrMateria = realocarMemoria(ptrMateria, numMat);
			}
			else {
				cout << "Ingrese la cantidad de materias que desea registrar: ";
				revisarNumero(numMat);
				ptrMateria = reservarMemoria(ptrMateria, numMat);
				capturarRegistros(ptrMateria, numMat);
			}
			system("pause");
			break;
		case 5:
			if (ptrMateria)
				ptrMateria = liberarMemoria(ptrMateria, numMat);
			else
				cout << "Aun no se tienen materias registradas." << endl;
			break;
		case 6:
			mostrar(ptrMateria, numMat);
			break;
		case 7:
			capturarCalifas(ptrAlumno, ptrMateria, numAlu, numMat);
			break;
		case 8:
			buscarPromedios(ptrAlumno, numAlu);
			break;
		case 9:
			guardarDatos(ptrAlumno, numAlu, fileNameAlumnos);
			guardarDatos(ptrMateria, numMat, fileNameMaterias);
			cout << "\tProceso terminado" << endl;
			break;
		case 10:
			guardarDatos(ptrAlumno, numAlu, fileNameAlumnos);
			guardarDatos(ptrMateria, numMat, fileNameMaterias);

			if (ptrAlumno)
				delete[] ptrAlumno;
			if (ptrMateria)
				delete[] ptrMateria;
			break;
		default:
			cout << "Opcion invalida, seleccione del 1 al 9" << endl;
			break;
		}
		system("Pause");
	} while (ope != 10);
}
