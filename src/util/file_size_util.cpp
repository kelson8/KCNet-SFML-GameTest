#include "file_size_util.h"

// The file sizes in this file can either be for Mebibytes, or Megabytes.
// Mebibytes is values like 1024, and Megabytes is values like 1000.

// These file size converters seem to work.

FileSizeUtil::FileSizeUtil()
{
	//m_Megabytes = true;
}

/**
 * @brief Convert bytes to megabytes
 * @param bytes 
 * @return
 */
float FileSizeUtil::BytesToMegabytes(float bytes)
{
	//if (m_Megabytes)
	//{
	//	return bytes / 1000000.0f;
	//}
	//else
	//{
	//	return bytes / 1048576.0f;
	//}

	//return bytes / 1048576;
	return bytes / 1000000;
}

/**
 * @brief Convert megabytes to gigabytes
 * @param megabytes 
 * @return 
 */
float FileSizeUtil::MegabytesToGigabytes(float megabytes)
{
	//return megabytes / 1024;
	return megabytes / 1000.0f;
}

/**
 * @brief Convert gigabytes to terabytes
 * @param gigabytes
 * @return
 */
float FileSizeUtil::GigabytesToTerabytes(float gigabytes)
{
	//return gigabytes / 1024;
	return gigabytes / 1000.0f;
}