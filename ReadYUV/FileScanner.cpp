#include "FileScanner.h"


FileScanner::FileScanner()
{
}


FileScanner::~FileScanner()
{
}

vector<string>FileScanner::find_file(string dir)
{
    std::vector<std::string> ret;
    WIN32_FIND_DATA p;
    HANDLE h = FindFirstFile(dir.c_str(), &p);
    //文件夹路径可以写成 C:\windows\tmp\   (字串内要双斜线)
    //也可写成C:\windows\tmp\*.dat    (检索所有.dat文件)
    //或者C:\windows\tmp\abc*  (检索abc开头的文件)
    do
    {
        ret.push_back(std::string(p.cFileName));
        //printf("%s\n", p.cFileName);//输出文件名称
        //输出的名称前两个 分别是“.”和“..” 代表当前目录和上一目录可以略过
        //得到文件的名称之后 就可以和前面的路径拼合组成文件的绝对路径
        //然后使用fopen对文件进行读写操作
    } while (FindNextFile(h, &p));
    return ret;
}
