#ifndef _HOFFSETMANAGER_H_
#define _HOFFSETMANAGER_H_

#include "..\Include\HWin.h"

#include "..\Remote\HRemote.h"
#include "..\Utilis\HUtilis.h"
#include "..\NetVarManager\HNetVarManager.h"

#include <fstream>

namespace Dumper
{

	namespace OffsetManager
	{

		class COffsetManager
		{
		public:

			COffsetManager( void );
			~COffsetManager( void );


		public:

			void Dump( void );


		private:
	
			void Dump( const std::string& tablename, const std::string& varname, uintptr_t offset, std::ofstream& file );		
			void Dump( const std::string& tablename, const std::string& varname, Remote::CModule* pModule, const unsigned char* pPattern, const char* pMask, int type, uintptr_t pattern_offset, uintptr_t address_offset, std::ofstream& file );
			void Log( const std::string& tablename, const std::string& varname, uintptr_t offset, std::ofstream& file );
		};

		inline COffsetManager* Singleton( void )
		{

			static COffsetManager* __pOffsetManager = new COffsetManager( );
			return __pOffsetManager;
		}
	}
}

#ifndef pOffsetManager
#define pOffsetManager Dumper::OffsetManager::Singleton( )
#endif

#endif /* _HOFFSETMANAGER_H_ */