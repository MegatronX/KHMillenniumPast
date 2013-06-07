#include "CompressionUtils.h"
#include <stdio.h>
#include <stdlib.h>
std::string GunzipString(const std::string &compressedString)
{
	std::stringstream src(compressedString);
	if (src.good())
	{
		try
		{
			boost::iostreams::filtering_streambuf<boost::iostreams::input> in;//(src);
			in.push(boost::iostreams::gzip_decompressor());
			in.push(src);
			std::stringstream dst;
			boost::iostreams::filtering_streambuf<boost::iostreams::output> out;//(dst);
			out.push(dst);
			boost::iostreams::copy(in, out);   
			return dst.str();
		}
		catch (std::exception ex)
		{
			std::cerr << "Could not perform gunzip. Exception occured " << ex.what() << std::endl;
		}
	}
	return compressedString;
}

void logZlibError(int error)
{
    switch (error)
    {
        case Z_MEM_ERROR:
            std::cerr << "Out of memory while (de)compressing data! \n";
            //exit(0);
            break;
        case Z_VERSION_ERROR:
            std::cerr <<  "Incompatible zlib version! \n";
            //exit(0);
            break;
        case Z_NEED_DICT:
        case Z_DATA_ERROR:
            std::cerr << "Incorrect zlib compressed data! \n";
            //exit(0);
            break;
        default:
            std::cerr << "Unknown error while (de)compressing data! \n";
            //exit(0);
    }
}

std::string UnZlibString(const std::string &compressedString)
{
	int bufferSize = compressedString.size();
    int ret;
    z_stream strm;
    char *out = (char *) malloc(bufferSize);
	//std::string outstr;
	//outstr.reserve(bufferSize);
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.next_in = (Bytef *) compressedString.data();
    strm.avail_in = compressedString.length();
    strm.next_out = (Bytef *) out;
    strm.avail_out = bufferSize;

    ret = inflateInit2(&strm, 15 + 32);

    if (ret != Z_OK)
    {
        logZlibError(ret);
        free(out);
        return NULL;
    }

    do
    {
        ret = inflate(&strm, Z_SYNC_FLUSH);

        switch (ret)
        {
            case Z_NEED_DICT:
            case Z_STREAM_ERROR:
                ret = Z_DATA_ERROR;
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                inflateEnd(&strm);
                logZlibError(ret);
                free(out);
                return NULL;
        }

        if (ret != Z_STREAM_END)
        {
            out = (char *) realloc(out, bufferSize * 2);

            if (!out)
            {
                inflateEnd(&strm);
                logZlibError(Z_MEM_ERROR);
                free(out);
                return NULL;
            }

            strm.next_out = (Bytef *)(out + bufferSize);
            strm.avail_out = bufferSize;
            bufferSize *= 2;
        }
    }
    while (ret != Z_STREAM_END);

    if (strm.avail_in != 0)
    {
        logZlibError(Z_DATA_ERROR);
        free(out);
        return NULL;
    }

    //const int outLength = bufferSize - strm.avail_out;
    inflateEnd(&strm);
	std::string outstr(out);
	free(out);
    return outstr;

}

void FileTest(const std::string &fileName)
{
	using namespace std;
	std::ifstream file(fileName, ios_base::in | ios_base::binary);
	boost::iostreams::filtering_streambuf<boost::iostreams::input> in;
	in.push(boost::iostreams::zlib_decompressor());
	in.push(file);
	boost::iostreams::copy(in, cout);
}



static const std::string base64_chars = 
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


static inline bool is_base64(unsigned char c) {
	return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
	std::string ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	while (in_len--) {
		char_array_3[i++] = *(bytes_to_encode++);
		if (i == 3) {
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for(i = 0; (i <4) ; i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if (i)
	{
		for(j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while((i++ < 3))
			ret += '=';

	}

	return ret;

}

std::string base64_decode(std::string const& encoded_string) {
	int in_len = encoded_string.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];
	std::string ret;

	while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
		char_array_4[i++] = encoded_string[in_]; 
		in_++;
		if (i ==4) {
			for (i = 0; i <4; i++)
				char_array_4[i] = base64_chars.find(char_array_4[i]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				ret += char_array_3[i];
			i = 0;
		}
	}

	if (i) {
		for (j = i; j <4; j++)
			char_array_4[j] = 0;

		for (j = 0; j <4; j++)
			char_array_4[j] = base64_chars.find(char_array_4[j]);

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++) 
			ret += char_array_3[j];
	}

	return ret;
}


CompressionUtils::CompressionUtils(void)
{
}


CompressionUtils::~CompressionUtils(void)
{
}
