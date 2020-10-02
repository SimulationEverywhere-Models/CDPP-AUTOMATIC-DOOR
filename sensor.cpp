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

/** include files **/
#include "sensor.h"      // class Sensor
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Sensor
* Description: 
********************************************************************/
Sensor::Sensor( const string &name )
: Atomic( name )
, deteccion( addInputPort( "deteccion" ) )
, consulta( addInputPort( "consulta" ) )
, aviso_deteccion( addOutputPort( "aviso_deteccion" ) )
{
}

/*******************************************************************
* Function Name: initFunction
* Description: 
* Precondition:
********************************************************************/
Model &Sensor::initFunction()
{
	
	this->fase = NoDetectado;
	this->detectado = false;
	this->informar = false;	
	
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Sensor::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == deteccion )
	{
		if ( msg.value() )
		{
			this->detectado = true;
			this->informar = true;	
		} else
		{
			this->detectado = false;
			this->informar = false;			
		}
	}

	if( msg.port() == consulta )
		this->informar = true;
		
	Time tiempo( 0, 0, 0, 0 );
	
	if ( this->informar )
	{
		this->fase = Informar;
		holdIn( active, tiempo );
	} else
	{
		this->fase = NoDetectado;
		holdIn( active, tiempo );
	}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Sensor::internalFunction( const InternalMessage & )
{
	switch (this->fase) {
		case Informar:
			this->informar = false;
			passivate();
			break;					
		case NoDetectado:
			passivate();
			break;					
	}
	
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Sensor::outputFunction( const InternalMessage &msg )
{
	switch (this->fase) {
	
		case Informar:
				double x;
				if ( this->detectado)
					x = 1;
				else
					x = 0;
			
				sendOutput(msg.time(), aviso_deteccion, x);
				break;
		case NoDetectado:
				break;
	}
	
	return *this ;
}
