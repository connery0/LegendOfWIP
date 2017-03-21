#include "stdafx.h"
#include "Core.h"
#include <ctime>
void StartHeapControl( );

int main( int argc, char *argv[] )
{
	srand(int(time(nullptr)));
	{ // make sure stack objects go out of scope before _CrtDumpMemoryLeaks is called
		StartHeapControl();

		//Core core{ Window{ "Gam3 - Partoens Tom- 1DAE17", 160.0f, 160.0f } };

		Core core{ Window{ "Gam3 - Partoens Tom- 1DAE17", 320.0f, 320.0f } };
		//Core core{ Window{ "Gam3 - Partoens Tom- 1DAE17", 1200.0f, 700.0f} };
		core.Run();
	}
	_CrtDumpMemoryLeaks(); 
	return 0;
}

void StartHeapControl( )
{
#if defined(DEBUG) | defined(_DEBUG)
	// Notify user if heap is corrupt
	HeapSetInformation( NULL, HeapEnableTerminationOnCorruption, NULL, 0 );

	// Report detected leaks when the program exits
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	// Set a breakpoint on the specified object allocation order number
	//_CrtSetBreakAlloc( 156 );
#endif
}


