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

/** include files **/
#include "uc.h"      // class UC
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: UC
* Description: 
********************************************************************/
UC::UC( const string &name )
: Atomic( name )
, aviso_deteccion( addInputPort( "aviso_deteccion" ) )
, consulta( addOutputPort( "consulta" ) )
, orden( addOutputPort( "orden" ) )
{
}

/*******************************************************************
* Function Name: initFunction
* Description: 
* Precondition:
********************************************************************/
Model &UC::initFunction()
{
	
	this->fase = EnEspera;
	this->abierta = false;
	this->detecciones = 0;
	this->no_detecciones = 0;
	
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &UC::externalFunction( const ExternalMessage &msg )
{
	Time tiempo1( 0, 0, 0, 999 );
	//Time tiempo1( 0, 0, 1, 000 );
	Time tiempo0( 0, 0, 0, 0 );
	
	if( msg.value() )
	{
		this->no_detecciones = 0;
		
		if ( this->detecciones < 3 )
		{
			this->detecciones++;
			this->fase = Consultando;
			holdIn( active, tiempo1 );
		}
		else
		{
			if ( this->abierta )
			{
				this->fase = Consultando;
				holdIn( active, tiempo1 );
			}
			else
			{
				this->abierta = true;
				this->fase = AbrirPuerta;
				holdIn( active, tiempo0);
			}
		}
	}
	else
	{
		if ( this->abierta )
		{
			if ( this->no_detecciones < 2)
			{
				this->no_detecciones++;
				this->fase = Consultando;
				holdIn( active, tiempo1 );
			}
			else
			{
				this->abierta = false;
				this->detecciones = 0;
				this->fase = CerrarPuerta;
				holdIn ( active, tiempo0 );
			}
		}
		else
		{
			this->detecciones = 0;
			this->fase = EnEspera;
			holdIn ( active, tiempo0 );
		}
	}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &UC::internalFunction( const InternalMessage & )
{
	Time tiempo1( 0, 0, 0, 999 );
	//Time tiempo1( 0, 0, 1, 000 );
	Time tiempo0( 0, 0, 0, 0 );
	
	switch (this->fase) {
		
		case AbrirPuerta:
			this->fase = Consultando;
			holdIn( active, tiempo1);
			break;					
		case CerrarPuerta:
			this->fase = EnEspera;
			holdIn( active, tiempo0);
			break;					
		case Consultando:
			this->fase = EnEspera;
			holdIn( active, tiempo0);
			break;					
		case EnEspera:
			passivate();
			break;		
	}
	
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &UC::outputFunction( const InternalMessage &msg )
{
	switch (this->fase) {
	
		case AbrirPuerta:
				sendOutput(msg.time(), orden, 1);
				break;
		case CerrarPuerta:
				sendOutput(msg.time(), orden, 0);
				break;
		case Consultando:
				sendOutput(msg.time(), consulta, 1);
				break;
		case EnEspera:
				break;
	}
	
	return *this ;
}
