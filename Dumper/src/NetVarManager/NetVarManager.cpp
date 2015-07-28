#include "HNetVarManager.h"
#include <iostream>

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
            auto firstclass = pProcess->FindPattern( pProcess->GetModuleByName( "client.dll" ), reinterpret_cast< unsigned char* >( "DT_TEWorldDecal" ), "xxxxxxxxxxxxxx", 0, 0, 0 );
            firstclass = pProcess->FindPattern( pProcess->GetModuleByName( "client.dll" ), reinterpret_cast< unsigned char* >( &firstclass ), "xxxx", Remote::SignatureType::READIT, 0x2B, 0 );

            if( !firstclass )
                return false;

            for( auto Class = ClientClass( firstclass ); Class.Get( ); Class = ClientClass( Class.GetNextClass( ) ) ) {
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
                    file << std::setw( 53 )
                        << std::setfill( '_' )
                        << std::left
                        << ( std::string( prop.second->GetRun( ), '  ' ) + "|__" + prop.first ).c_str( )
                        << std::right
                        << std::hex
                        << " -> 0x"
                        << std::setw( 4 )
                        << std::setfill( '0' )
                        << std::uppercase
                        << prop.second->GetOffset( ) << std::endl;
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
            for( auto i = 0; i < table.GetMaxProp( ); ++i ) {
                auto pProp = new RecvProp( table.GetPropById( i ), run );
                if( isdigit( pProp->GetName( )[ 0 ] ) )
                    continue;

                _tables[ name ].push_back( std::pair<std::string, RecvProp*>( pProp->GetName( ), pProp ) );

                auto child = pProp->GetTable( );
                if( !child )
                    continue;

                ScanTable( RecvTable( child ), ++run, name );
            }
        }
    }
}
