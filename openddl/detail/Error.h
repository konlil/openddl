#pragma once
#include <string>
namespace openddl
{
	namespace detail
	{
		struct Error
		{

			std::string payload;				//The literal (as string) which caused the error
			std::string message;				//Plain text key describing error		

			unsigned int range_start;			//Position of offset of offending literal in string
			unsigned int range_length;
		};
	}
}
