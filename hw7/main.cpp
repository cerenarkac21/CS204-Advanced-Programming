// Ceren Arkac

/**Artrim Kjamilji, 20.12.2021**/

#include <iostream>
#include <string>
#include "TwoDShapes.h"
#include "ThreeDShapes.h"

using namespace std;

Shape * getShape() {
	bool done = false;
	while (done == false){
		string choice, name;
		float width, length;
		Shape *myShape;
		cout << "Choose an option <1 or 2>: " << endl;
		cout << "1. Rectangle" << endl;
		cout << "2. Box" << endl;
		cin >> choice;
		if (choice == "1")
		{
			cout << "You chose rectangle. Give it's width, length and name: " << endl;
			cin >> width >> length >> name;
			myShape = new Rectangle(width, length, name);
			done = true;
			return myShape;
		}
		else if (choice == "2")
		{
			float height;
			cout << "You chose box. Give it's width, length, height and name: " << endl;
			cin >> width >> length >> height >> name;
			myShape = new Box(width, length, height, name);
			done = true;
			return myShape;
		}
		else{
			cout << "UNAVAILABLE OPTION CHOSEN. Try again." << endl;
		}
	}

}//getShape()


int main()
{
	cout<<"WELCOME TO THE SHAPE COMPARISONN PROGRAM"<<endl;
	cout<<"FOR EXITIING PRESS Y/y, OTHERWISE PRESS ANY KEY"<<endl;
	Shape *shape_1, *shape_2; 
	char c;
	while (tolower(c = getchar())!='y')
	{
		cout<<"Defining (getting) shape 1..."<<endl;
		
		shape_1 = getShape();
		cout<<"Defining (getting) shape 2..."<<endl;
		shape_2 = getShape();
		cout<<"********************************************************************"<<endl;
		cout<<"PRINTING SHAPE_1 INFOS:"<<endl<<"Name: "<<shape_1->getName()<<", perimeter: "
			<<shape_1->perimeter()<<", area: "<<shape_1->area()<<", volume: "<<shape_1->volume()<<endl<<endl;
		cout<<"PRINTING SHAPE_2 INFOS:"<<endl<<"Name: "<<shape_2->getName()<<", perimeter: "
			<<shape_2->perimeter()<<", area: "<<shape_2->area()<<", volume: "<<shape_2->volume()<<endl;		
		bool nothingInCommon=true; // to check whether they have anything in common (perimeter, area, volume)
		if(shape_1->perimeter()==shape_2->perimeter())
		{
			nothingInCommon = false;
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same perimeter, which is: "
				<<shape_1->perimeter()<<" cm."<<endl;
		}
		if(shape_1->area()==shape_2->area())
		{
			nothingInCommon = false;
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same area, which is: "
				<<shape_1->area()<<" cm^2."<<endl;
		}
		if(shape_1->volume()==shape_2->volume())
		{
			nothingInCommon = false;
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same volume, which is: "
				<<shape_1->volume()<<" cm^3."<<endl;
		}
		if (nothingInCommon)
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" don't have anything in common."<<endl;		
		
		delete shape_1;
		delete shape_2;

		cout<<"********************************************************************"<<endl;
		cout<<"FOR EXITIING PRESS Y/y, OTHERWISE, FOR ANOTHER COMPARISON PRESS ANY KEY"<<endl<<endl;
		cin.ignore();//flushing the buffer for remaining character(s), in order getchar() to work
  	}//while(tolower(c = getchar())!='y')
	cout<<"PROGRAM EXITING. THANKS FOR USING IT."<<endl;
	system("pause");
	return 0;
}
