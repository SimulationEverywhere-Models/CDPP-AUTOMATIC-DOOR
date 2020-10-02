/*******************************************************************
*
*  DESCRIPCION: Modelo Atómico del Motor
*
*  AUTOR: Maximiliano M. Polimeni 
*
*  EMAIL: mailto://mmpolimeni@tutopia.com
*
*  DATE: 26/9/2004
*
*******************************************************************/

#ifndef __MOTOR_H
#define __MOTOR_H

#include "atomic.h"     // class Atomic

class Motor : public Atomic
{
	public:
		//Constructor
		Motor( const string &name = "Motor" );
		//Estados
		enum Estado {Abrir, Cerrar};
		
	protected:
		//Funciones de inicializacion, transicion externa, interna y de output
		Model &initFunction();
		Model &externalFunction( const ExternalMessage & );
		Model &internalFunction( const InternalMessage & );
		Model &outputFunction( const InternalMessage & );
		
	private:
		//Puertos de entrada
		const Port &orden;
	
		//Puertos de salida
		Port &abrir_cerrar;
		
		//Variables de estados
		bool abierta;
		Estado fase;
			
};	// class Motor

#endif   //__MOTOR_H
