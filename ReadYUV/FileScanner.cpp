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
    //�ļ���·������д�� C:\windows\tmp\   (�ִ���Ҫ˫б��)
    //Ҳ��д��C:\windows\tmp\*.dat    (��������.dat�ļ�)
    //����C:\windows\tmp\abc*  (����abc��ͷ���ļ�)
    do
    {
        ret.push_back(std::string(p.cFileName));
        //printf("%s\n", p.cFileName);//����ļ�����
        //���������ǰ���� �ֱ��ǡ�.���͡�..�� ����ǰĿ¼����һĿ¼�����Թ�
        //�õ��ļ�������֮�� �Ϳ��Ժ�ǰ���·��ƴ������ļ��ľ���·��
        //Ȼ��ʹ��fopen���ļ����ж�д����
    } while (FindNextFile(h, &p));
    return ret;
}
