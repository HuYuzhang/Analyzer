#include "def.h"
using namespace std;
using namespace cv;
class FileScanner
{
public:
    FileScanner();
    ~FileScanner();
    vector<string> find_file(string dir);
};

