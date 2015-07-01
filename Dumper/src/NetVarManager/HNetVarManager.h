#ifndef _HNETVARMANAGER_H_
#define _HNETVARMANAGER_H_

#include "..\Include\HWin.h"

#include "..\Remote\HRemote.h"
#include "..\Utilis\HUtilis.h"

#include <map>
#include <unordered_map>
#include <fstream>

#pragma warning( disable : 4227 )
#pragma warning( disable : 4172 )

namespace Dumper
{

	namespace NetVarManager
	{

		class RecvTable : public Remote::CMemory
		{
		public:

											RecvTable( const uintptr_t& base );
											~RecvTable( void );


		public:

			inline const char* GetName( void ) {

				char buffer[ 32 ] = { 0 };
				pProcess->ReadMemory( Get< DWORD >( 0xC ), &buffer, 32 );
				return buffer;
			}

			inline uintptr_t				GetPropById( int id ) { return Get< uintptr_t >( 0x0 ) + id * 0x3C; }
			inline int						GetMaxProp( void ) { return Get< int >( 0x4 ); }
		};

		class RecvProp : public Remote::CMemory
		{
		public:

											RecvProp( const uintptr_t& base, int run );
											~RecvProp( void );


		public:

			inline const char* GetName( void ) {

				char buffer[ 64 ] = { 0 };
				pProcess->ReadMemory( Get< DWORD >( 0x0 ), &buffer, 64 );
				return buffer;
			}

			inline int						GetOffset( void ) { return Get< int >( 0x2C ); }
			inline uintptr_t				GetTable( void ) { return Get< uintptr_t >( 0x28 ); }
			inline const int& const			GetRun( void ) { return _run; }


		protected:

			int								_run;	// deepness
		};

		class ClientClass : public Remote::CMemory
		{
		public:

											ClientClass( const uintptr_t& base );
											~ClientClass( void );


		public:

			inline const char* GetName( void ) {

				char buffer[ 32 ] = { 0 };
				pProcess->ReadMemory( Get< DWORD >( 0x8 ), &buffer, 32 );
				return buffer;
			}

			inline uintptr_t				GetTable( void )		{ return Get< uintptr_t >( 0xC ); }
			inline uintptr_t				GetNextClass( void )	{ return Get< uintptr_t >( 0x10 ); }
			inline int						GetId( void )			{ return Get< int >( 0x14 ); }
		};

		typedef std::vector< std::pair< std::string, RecvProp* > >	vecProp;
		typedef std::unordered_map< std::string, vecProp >			mapTable;

		class CNetVarManager
		{
		public:

											CNetVarManager( void );
											~CNetVarManager( void );


		public:

			bool							Load( void );
			void							Dump( void );
			void							Release( void );


		public:

			int								GetNetVar( const std::string& tablename, const std::string& varname );


		private:

			void							ScanTable( RecvTable& table, int run, const char* name );


		protected:

			mapTable						_tables;				// recvtables dumped
		};

		inline CNetVarManager* Singleton( void )
		{

			static CNetVarManager* __pNetVarManager = new CNetVarManager( );
			return __pNetVarManager;
		}
	}
}

#ifndef pNetVarManager
#define pNetVarManager Dumper::NetVarManager::Singleton( )
#endif

#pragma warning( default : 4172 )
#pragma warning( default : 4227 )

#endif /* _HNETVARMANAGER_H_ */