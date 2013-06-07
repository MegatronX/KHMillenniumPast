#pragma once
#ifndef _COMPRESSIONUTILS_H_
#define _COMPRESSIONUTILS_H_
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
//#include <Compression\gzstream.h>
#include <boost\iostreams\filter\gzip.hpp>
#include <boost\iostreams\filtering_streambuf.hpp>
#include <boost\iostreams\copy.hpp>

#include <zlib\zlib.h>
std::string GunzipString(const std::string &compressedString);
std::string UnZlibString(const std::string &compressedString);
void FileTest(const std::string &file);

std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);



class CompressionUtils
{
public:
	CompressionUtils(void);
	~CompressionUtils(void);
};

#endif

