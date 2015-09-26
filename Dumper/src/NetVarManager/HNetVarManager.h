#ifndef _HNETVARMANAGER_H_
#define _HNETVARMANAGER_H_

#include "..\Include\HWin.h"

#include "..\Remote\HRemote.h"

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

            explicit                                RecvTable( const uintptr_t& base );
                                                    ~RecvTable( void );


        public:

            std::string&                            GetName( std::string& name = std::string() )
            {
                name.resize( 32 );
                pProcess->ReadMemory( Get<DWORD>( 0xC ), &name.at( 0 ), 32 );
                return name;
            }

            uintptr_t                               GetPropById( int id ) { return Get<uintptr_t>( 0x0 ) + id * 0x3C; }
            int                                     GetMaxProp( void ) { return Get<int>( 0x4 ); }
        };

        class RecvProp : public Remote::CMemory
        {
        public:

            RecvProp( const uintptr_t& base, int run );
            ~RecvProp( void );


        public:

            std::string&                            GetName( std::string& name = std::string() )
            {
                name.resize( 64 );
                pProcess->ReadMemory( Get<DWORD>( 0x0 ), &name.at( 0 ), 64 );
                return name;
            }

            int                                     GetOffset( void ) { return Get<int>( 0x2C ); }
            uintptr_t                               GetTable( void ) { return Get<uintptr_t>( 0x28 ); }
            const int&                              GetRun( void ) const { return _run; }


        protected:

            int                                     _run;                       // deepness
        };

        class ClientClass : public Remote::CMemory
        {
        public:

            explicit                                ClientClass( const uintptr_t& base );
                                                    ~ClientClass( void );


        public:

            std::string&                            GetName( std::string& name = std::string() )
            {
                name.resize( 64 );
                pProcess->ReadMemory( Get<DWORD>( 0x8 ), &name.at( 0 ), 64 );
                return name;
            }

            uintptr_t                               GetTable( void ) { return Get<uintptr_t>( 0xC ); }
            uintptr_t                               GetNextClass( void ) { return Get<uintptr_t>( 0x10 ); }
            int                                     GetId( void ) { return Get<int>( 0x14 ); }
        };

        typedef std::pair < std::string, RecvProp* >         stringProp;
        typedef std::vector< stringProp >                    vecProp;
        typedef std::unordered_map< std::string, vecProp >   mapTable;

        class CNetVarManager
        {
        public:

                                                    CNetVarManager( void );
                                                    ~CNetVarManager( void );


        public:

            bool                                    Load( void );
            void                                    Dump( void ) const;
            void                                    Release( void );


        public:

            int                                     GetNetVar( const std::string& tablename, const std::string& varname );


        private:

            void                                    ScanTable( RecvTable& table, int run, const char* name );


        protected:

            mapTable                                _tables;                    // recvtables dumped
        };

        inline CNetVarManager* Singleton( void )
        {
            static auto g_pNetVarManager = new CNetVarManager();
            return g_pNetVarManager;
        }
    }
}

#ifndef pNetVarManager
#define pNetVarManager Dumper::NetVarManager::Singleton( )
#endif

#pragma warning( default : 4172 )
#pragma warning( default : 4227 )

#endif /* _HNETVARMANAGER_H_ */
