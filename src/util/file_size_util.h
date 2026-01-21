#pragma once
class FileSizeUtil
{
public:
	static float BytesToMegabytes(float bytes);
	static float MegabytesToGigabytes(float megabytes);
	static float GigabytesToTerabytes(float gigabytes);

private:
	FileSizeUtil();

	//static bool m_Megabytes;
};

