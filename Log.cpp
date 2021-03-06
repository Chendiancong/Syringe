#include "Log.h"

#include <share.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

FileHandle Log::File;

void Log::Open(char const* const pFilename) noexcept
{
	if(pFilename && *pFilename) {
		File = FileHandle(_fsopen(pFilename, "w", _SH_DENYWR));
	}
}

void Log::Flush() noexcept
{
	if(File) {
		fflush(File);
	}
}

void Log::WriteTimestamp() noexcept
{
	if(File) {
		time_t raw;
		time(&raw);

		tm t;
		localtime_s(&t, &raw);

		fprintf(File, "[%02d:%02d:%02d] ", t.tm_hour, t.tm_min, t.tm_sec);
	}
}

void Log::WriteLine() noexcept
{
	if(File) {
		fputs("\n", File);
	}
}

void Log::WriteLine(char const* const pFormat, ...) noexcept
{
	if(File) {
		va_list args;
		va_start(args, pFormat);

		WriteTimestamp();
		vfprintf(File, pFormat, args);
		WriteLine();

		va_end(args);
	}
}
