#include "HalfFpBuildTime.h"

HalfFpBuildTime::HalfFpBuildTime()
: dateTime(__DATE__ " " __TIME__)
{
}

HalfFpBuildTime::~HalfFpBuildTime()
{
}

const char* HalfFpBuildTime::GetDateTime()
{
    return dateTime;
}

