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

/** include files **/
#include "motor.h"      // class Motor
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Motor
* Description: 
********************************************************************/
Motor::Motor( const string &name )
: Atomic( name )
, orden( addInputPort( "orden" ) )
, abrir_cerrar( addOutputPort( "abrir_cerrar" ) )
{
}

/*******************************************************************
* Function Name: initFunction
* Description: 
* Precondition:
********************************************************************/
Model &Motor::initFunction()
{
	this->abierta = false;
	this->fase = Cerrar;
		
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Motor::externalFunction( const ExternalMessage &msg )
{
	///Time tiempo( 0, 0, 0, 999 );
	Time tiempo( 0, 0, 1, 000 );
	
	if ( msg.value() )
	{
		if(!abierta)
		{
			abierta = true;
			this->fase = Abrir;
			holdIn( active, tiempo );
		}
	} else
	{
		if(abierta)
		{
			abierta = false;
			this->fase = Cerrar;
			holdIn( active, tiempo );		
		}
	}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Motor::internalFunction( const InternalMessage & )
{
	passivate();	
	
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Motor::outputFunction( const InternalMessage &msg )
{
	switch (this->fase) {
	
		case Abrir:
				sendOutput(msg.time(), abrir_cerrar, 1);
				break;
		case Cerrar:
				sendOutput(msg.time(), abrir_cerrar, 0);
				break;
	}
	
	return *this ;
}
