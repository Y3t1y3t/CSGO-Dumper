#include "HNetVarManager.h"

namespace Dumper
{

	namespace NetVarManager
	{

		RecvTable::RecvTable( const uintptr_t& base ) : Remote::CMemory( base, 0x10 )
		{
		}

		RecvTable::~RecvTable( void )
		{
		}

		RecvProp::RecvProp( const uintptr_t& base, int run ) : Remote::CMemory( base, 0x3C ), _run( run )
		{
		}

		RecvProp::~RecvProp( void )
		{
		}

		ClientClass::ClientClass( const uintptr_t& base ) : Remote::CMemory( base, 0x28 )
		{
		}

		ClientClass::~ClientClass( void )
		{
		}

		CNetVarManager::CNetVarManager( void )
		{
		}

		CNetVarManager::~CNetVarManager( void )
		{
		}

		bool CNetVarManager::Load( void )
		{

			pProcess->Attach( "csgo.exe" );

			uintptr_t firstclass = pProcess->FindPattern( pProcess->GetModuleByName( "client.dll" ), ( unsigned char* )"\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\x66\xC7\x05\xD0\x74\x00\x00\x00\x00\xC3", "xx????????xx????????xxxxx????x", Remote::SignatureType::READIT, 0x3B, 0x0 );

			if( !firstclass )
				return false;

			for( ClientClass Class = ClientClass( firstclass ); Class.Get( ); Class = ClientClass( Class.GetNextClass( ) ) ) {

				auto table = RecvTable( Class.GetTable( ) );
				if( !table.Get( ) )
					continue;

				ScanTable( table, 0, table.GetName( ) );
			}

			return true;
		}

		void CNetVarManager::Dump( void )
		{

			std::ofstream file( "NetVarManager.txt" );
			file << "- - - - - - Tool by Y3t1y3t ( uc ) - - - - - - " << std::endl;
			file << "| -> http://www.unknowncheats.me/forum/counterstrike-global-offensive/100856-cs-go-offset-dumper-small-one.html" << std::endl;
			file << "| -> " << Utilis::GetTime( );
			file << "- -" << std::endl << std::endl;

			for( auto& table : _tables ) {
				file << table.first << std::endl;
				for( auto& prop : table.second ) {
					file << std::setw( 53 ) << std::setfill( '_' ) << std::left << ( std::string( prop.second->GetRun( ), '  ' ) + "|__" + prop.first ).c_str( ) << std::right << std::hex << " -> 0x" << std::setw( 4 ) << std::setfill( '0' ) << std::uppercase << prop.second->GetOffset( ) << std::endl;
				}
			}
		}

		void CNetVarManager::Release( void )
		{

			for( auto& table : _tables ) {
				for( auto& prop : table.second ) {
					delete prop.second;
				}
				table.second.clear( );
			}

			_tables.clear( );
		}

		int CNetVarManager::GetNetVar( const std::string& tablename, const std::string& varname )
		{

			auto table = _tables.find( tablename );
			if( table != _tables.end( ) ) {
				for( auto& prop : table->second ) {
					if( prop.first == varname ) {
						return prop.second->GetOffset( );
					}
				}
			}
			return 0;
		}

		void CNetVarManager::ScanTable( RecvTable& table, int run, const char* name )
		{

			for( int i = 0; i < table.GetMaxProp( ); ++i ) {

				RecvProp* pProp = new RecvProp( table.GetPropById( i ), run );
				if( isdigit( pProp->GetName( )[ 0 ] ) )
					continue;

				_tables[ name ].push_back( std::pair< std::string, RecvProp* >( pProp->GetName( ), pProp ) );

				auto table = pProp->GetTable( );
				if( !table )
					continue;

				ScanTable( RecvTable( table ), ++run, name );
			}
		}
	}
}