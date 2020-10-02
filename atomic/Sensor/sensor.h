/*******************************************************************
*
*  DESCRIPCION: Modelo Atómico del Sensor
*
*  AUTOR: Maximiliano M. Polimeni 
*
*  EMAIL: mailto://mmpolimeni@tutopia.com
*
*  DATE: 26/9/2004
*
*******************************************************************/

#ifndef __SENSOR_H
#define __SENSOR_H

#include "atomic.h"     // class Atomic

class Sensor : public Atomic
{
	public:
		//Constructor
		Sensor( const string &name = "Sensor" );
		//Estados
		enum Estado {Informar, NoDetectado};
		
	protected:
		//Funciones de inicializacion, transicion externa, interna y de output
		Model &initFunction();
		Model &externalFunction( const ExternalMessage & );
		Model &internalFunction( const InternalMessage & );
		Model &outputFunction( const InternalMessage & );
		
	private:
		//Puertos de entrada
		const Port &deteccion;
		const Port &consulta;
	
		//Puerto de salida
		Port &aviso_deteccion;
		
		//Variables de estado
		bool detectado;
		bool informar;
		Estado fase;
			
};	// class Sensor

#endif   //__SENSOR_H
