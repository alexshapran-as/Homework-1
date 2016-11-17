/*
Домашняя работа №1
Алексей Шапран 
Группа: ИУ8-14
*/
#include <iostream>
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime> 
#define shift 4
using namespace std; 

int main(void)
{
	int size = 0;
	double* gamma = 0;
	int* x = 0;
	int* y = 0;
	
	const char txt[] = {'H', 'i'}; // символы сообщения для шифрования
	cout << endl << "Data size: " << sizeof(txt) << " bytes" << endl;
	cout << "Message text: "<< txt << endl << endl << "Encryption" << endl;

		for ( int i = 0; txt[i] != '\0';  i++ ) size = size + 1; // вычисление кол-ва символов сообщения
	gamma = (double *)malloc( size*sizeof(double) ); // выделение памяти под гамму
	
	// Печать символов сообщения в десятичной системе счисления
	cout << "Initial numbers: ";
		for ( int i = 0; i < size; i++ ) cout << (int)txt[i] << " ";
	cout << endl;

	// Инициализация гаммы
	cout << "Gamma: ";
	srand(time(NULL));
		for ( int i = 0; i < size; i++ )
		{
			gamma[i] = rand() % 127; 
			cout << gamma[i] << " "; 
		}
	cout << endl;

	//Вычисление "Исключающего или" / XOR 
	x = (int *)malloc( size*sizeof(int) );
	cout << "XOR: ";
		for ( int i = 0; i < size; i++ ) 
		{
			x[i] = (int)( (int)txt[i] + gamma[i] ) % 127;
			if ( x[i] == 0) x[i] = 127;
			cout << x[i] << " ";
		}
	cout << endl;

	// Циклический сдвиг вправо на shift бит
	y = (int *)malloc( size*sizeof(int) );
	cout << "Cyclic shift: ";
		for ( int j = 0; j < shift; j++ )
		{
				for ( int i = 0; i < size; i++ ) y[i] = x[i];
			x[0] = y[size-1];
				for ( int i = 0; i < size-1; i++ ) x[i+1] = y[i];
		}
		for (int i = 0; i < size; i++) cout << x[i] << " ";

	// Печать зашифрованного сообщения	
			cout << endl << "The encrypted message: ";
		for (int i = 0; i < size; i++) cout << (char)x[i];
	
	cout << endl << endl << "Decryption" << endl;
	
	cout << "Reverse XOR: ";
		for ( int j = 0; j < shift; j++ )
		{
				for ( int i = 0; i < size; i++ ) y[i] = x[i];
			x[size-1] = y[0];
				for ( int i = 0; i < size-1; i++ ) x[i] = y[i+1];
		}
		for (int i = 0; i < size; i++) cout << x[i] << " ";
	cout << endl;
	
	cout << "Gamma: ";
		for (int i = 0; i < size; i++) cout << gamma[i] << " ";

	
	cout << endl << "The decrypted numbers: ";
		for ( int i = 0; i < size; i++ ) 
		{
			y[i] = (int)( x[i] - gamma[i] + 127 ) % 127;
			if ( y[i] == 0 ) y[i] = 127;
			cout << y[i] << " ";
		}
	cout << endl;

	cout << "The decrypted message text: ";
		for ( int i = 0; i < size; i++ ) cout << (char)y[i];
	cout << endl << endl << "Press any button to exit the program" << endl;
			
	free(gamma);
	free(x);
	free(y);
	_getch();
	return 0;
}