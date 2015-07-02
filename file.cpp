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

#include "File.hpp"

File::File( const std::string& file_path, const bool read_access, const bool write_access )
{
	open( file_path, read_access, write_access );
}

File::~File()
{
	m_file.close();
}

/// ///////////////////////////////////////////////////////////////////
int File::open( const std::string& file_path, const bool read_access, const bool write_access )
{
	m_file.close();
	m_file_path = file_path;

	auto mode = std::ios::binary;
	if( read_access )  mode |= std::ios::in;
	if( write_access ) mode |= std::ios::out;

	m_file.open( file_path, mode );

	if( !m_file.is_open() )
	{
        /// failed to load file
        return 0;
	}
    return 1;
}

/// ///////////////////////////////////////////////////////////////////
void File::close()
{
	m_file.close();
}

/// ///////////////////////////////////////////////////////////////////
bool File::is_open()
{
	return m_file.is_open();
}

/// ///////////////////////////////////////////////////////////////////
std::string File::read_line()
{
	std::string str;
	std::getline( m_file, str, '\n' );
	return str;
}

/// ///////////////////////////////////////////////////////////////////
std::string File::read_string()
{
	std::string str;
	std::getline( m_file, str, '\0' );
	return str;
}

/// ///////////////////////////////////////////////////////////////////
std::string File::read_token( const char delim )
{
	std::string str;
	std::getline( m_file, str, delim );
	return str;
}

/// ///////////////////////////////////////////////////////////////////
void File::write( const std::string& str )
{
	if( !m_file.is_open() )
	{
		return;
	}

	m_file.flush();
	m_file.write( str.data(), str.length() );
}

/// ///////////////////////////////////////////////////////////////////
unsigned int File::get_write_position()
{
	if( !m_file.is_open() )
	{
		return 0;
	}

	return static_cast<unsigned int>( m_file.tellp() );
}

/// ///////////////////////////////////////////////////////////////////
void File::set_write_position( unsigned int pos )
{
	if( !m_file.is_open() )
	{
		return;
	}
	m_file.seekp( pos );
}

/// ///////////////////////////////////////////////////////////////////
unsigned int File::get_read_position()
{
	if( !m_file.is_open() )
	{
		return 0;
	}

	return static_cast<unsigned int>( m_file.tellg() );
}

/// ///////////////////////////////////////////////////////////////////
void File::set_read_position( unsigned int pos )
{
	if( !m_file.is_open() )
	{
		return;
	}
	m_file.seekg( pos );
}

/// ///////////////////////////////////////////////////////////////////
unsigned int File::get_size()
{
	if( !m_file.is_open() )
	{
		return 0;
	}

	const auto current_position = get_read_position();
	m_file.seekg( 0, std::ios::end );
	auto end_position = get_read_position();
	set_read_position( current_position );
	return end_position;
}

/// ///////////////////////////////////////////////////////////////////
int File::get_state()
{
	auto error_state = m_file.rdstate();
	m_file.clear();
	return error_state;
}

int File::eof()
{
	return m_file.eof();
}
