#ifndef _HUTILIS_H_
#define _HUTILIS_H_

#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif /* _CRT_SECURE_NO_WARNINGS */

#include "..\Include\HWin.h"

#include <time.h>
#include <iomanip>

namespace Dumper
{

	namespace Utilis
	{

		inline const char* GetTime( )
		{

			time_t rawtime;
			struct tm * timeinfo;

			time( &rawtime );
			timeinfo = localtime( &rawtime );

			return asctime( timeinfo );
		}

	}
}

#endif /* _HUTILIS_H_ */