
#include "GlobalIncludes.h"
#include "TextureManager.h"
#include "SmartPointer.h"
#include "RenderObject.h"
using namespace std;

int main3()
{
 	int i = 1;
	std::cout << NULL;
	SmartPntr<int> p0;
	SmartPntr<int> p(&i);
	SmartPntr<int> p2(p);
	p0 = p2;
	cout<< *p0 <<endl<< p0.isNull()<<endl;
	(&p0)->isNull();
	//CRenderObject testobj("testt.obj");

	return 0;
}
