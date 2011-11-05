#include "GlobalIncludes.h"
#include "TextureManager.h"
#include "SmartPointer.h"
using namespace std;
int main()
{
	int i = 1;
	std::cout << NULL;
	SmartPntr<int> p0;
	SmartPntr<int> p(&i);
	SmartPntr<int> p2(p);
	p0 = p2;
	cout<< *p0 <<endl<< p0.isNull()<<endl;
	int *j;
	(&p0)->isNull();
	return 0;
}