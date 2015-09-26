#ifndef _HOFFSETMANAGER_H_
#define _HOFFSETMANAGER_H_

#include "..\Include\HWin.h"

#include "..\Remote\HRemote.h"

#include <sstream>

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

            void                                    Dump( void ) const;


        private:

            void                                    DumpNetVar( const std::string& tablename, const std::string& varname, uintptr_t offset, std::stringstream& ss ) const;
            void                                    DumpPatternOffset( const std::string& tablename, const std::string& varname, Remote::CModule* pModule, const unsigned char* pPattern, const char* pMask, int type, uintptr_t pattern_offset, uintptr_t address_offset, std::stringstream& ss ) const;
            void                                    LogToStringStream( const std::string& tablename, const std::string& varname, uintptr_t offset, std::stringstream& ss ) const;
        };

        inline COffsetManager* Singleton( void ) {
            static auto g_pOffsetManager = new COffsetManager( );
            return g_pOffsetManager;
        }
    }
}

#ifndef pOffsetManager
#define pOffsetManager Dumper::OffsetManager::Singleton( )
#endif

#endif /* _HOFFSETMANAGER_H_ */
