#pragma once

#include <cstdio>


namespace GribCoder {

class GribMessageHandler {
public:
	GribMessageHandler();
	~GribMessageHandler();

	bool parseFile(std::FILE* file);

private:
	
};

} // namespace GribCoder

