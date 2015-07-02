//The MIT License (MIT)
//
//Copyright (c) 2015 Stefan Paunovic
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.  

#pragma once

#include <fstream>
#include <string>

class File
{
    public:

        File( const std::string& file, const bool read_access = true, const bool write_access = false );

        ~File();

        /// open an existing file for binary read and write operation
        int open( const std::string& file_path, const bool read_access = true, const bool write_access = false );

        /// close file
        void close();

        /// return true if a file is open
        bool is_open();

        /// read a line
        std::string read_line();

        /// read a string until string termination token '0'
        std::string read_string();

        /// read a strung until delimeter token
        std::string read_token( const char delim );

        /// write a string
        void write( const std::string& str );

        /// return the current write position
        unsigned int get_write_position();

        /// set the current write position
        void set_write_position( unsigned int pos );

        /// get the current read position
        unsigned int get_read_position();

        /// set the current read position
        void set_read_position( unsigned int pos );

        /// return the size of the file in bytes
        unsigned int get_size();

        /// return error flag state
        int get_state();

        /// return eof state flag
        int eof();

        /// Write a templated type
        /// ///////////////////////////////////////////////////////////////////
        template<typename T>
        void write( T data )
        {
            if( !m_file.is_open() )
            {
                return;
            }

            union Type_Alias
            {
                Type_Alias() {}
                ~Type_Alias() {}

                T as_type;
                char as_char[sizeof( T )];
            };

            Type_Alias buffer;
            buffer.as_type = data;

            m_file.flush();
            m_file.write( &buffer.as_char[0], sizeof( T ) );
        }

        /// Write a 'size' number of templated types
        /// ///////////////////////////////////////////////////////////////////
        template<typename T>
        void write_buffer( T* data, std::size_t size )
        {
            if( !m_file.is_open() )
            {
                return;
            }

            typedef union
            {
                T* as_type;
                char* as_char[sizeof( T )];
            } type_alias;

            type_alias buffer;
            buffer.as_type = data;

            m_file.flush();
            m_file.write( buffer.as_char[0], sizeof( T ) * size );
        }

        /// Read a T type from a file
        /// ///////////////////////////////////////////////////////////////////
        template<typename T>
        T read()
        {
            /*
               Example:
               struct must be composed of pod types
               such that sizeof() gives the proper size to load

               struct Pack
               {
                  int a;
                  int b;
               };

               file.set_read_position(0);
               auto my_pack = file.read_buffer<Pack>()
            */

            if( !m_file.is_open() )
            {
                return T();
            }

            union Type_Alias
            {
                Type_Alias() {}
                ~Type_Alias() {}

                T as_type;
                char as_char[sizeof( T )];
            };

            Type_Alias buffer;
            m_file.read( &buffer.as_char[0], sizeof( T ) );
            return buffer.as_type;
        }

        /// Read 'size' number of templated types
        /// ///////////////////////////////////////////////////////////////////
        template<typename T>
        void read_buffer( T* data, std::size_t size )
        {
            if( !m_file.is_open() )
            {
                return;
            }

            typedef union
            {
                T* as_type;
                char* as_char[sizeof( T )];
            } type_alias;

            type_alias buffer;
            buffer.as_type = data;

            m_file.read( buffer.as_char[0], sizeof( T ) * size );
        }

    private:

        std::fstream m_file;
        std::string m_file_path;

};
