#include <string>
#include <vector>


std::string base64_Encode(unsigned char const* , unsigned int len);
std::vector<int> base64_Decode(std::string const& s);
std::vector<int> Base64_DecodeInFours(std::string const& s);
int* Base64TMXDecode(std::string const& s, int size);
std::string Base64_StringDecode(std::string const& s);
std::string Base64_StringDecodeX(std::string const& s);
