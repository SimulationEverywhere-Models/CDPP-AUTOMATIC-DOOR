/*******************************************************************
*
*  DESCRIPCION: Modelo Atómico de la Unidad de Control
*
*  AUTOR: Maximiliano M. Polimeni 
*
*  EMAIL: mailto://mmpolimeni@tutopia.com
*
*  DATE: 26/9/2004
*
*******************************************************************/

#ifndef __UC_H
#define __UC_H

#include "atomic.h"     // class Atomic

class UC : public Atomic
{
	public:
		//Constructor
		UC( const string &name = "UC" );
		//Estados
		enum Estado {EnEspera, Consultando, AbrirPuerta, CerrarPuerta};
		
	protected:
		//Funciones de inicializacion, transicion externa, interna y de output
		Model &initFunction();
		Model &externalFunction( const ExternalMessage & );
		Model &internalFunction( const InternalMessage & );
		Model &outputFunction( const InternalMessage & );
		
	private:
		//Puerto de entrada
		const Port &aviso_deteccion;		
	
		//Puertos de salida
		Port &consulta;
		Port &orden;

		
		//Variables de estado
		int detecciones;
		int no_detecciones;
		bool abierta;
		Estado fase;
			
};	// class UC

#endif   //__UC_H
