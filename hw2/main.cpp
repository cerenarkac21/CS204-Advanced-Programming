/*********************************
Purpose: Simplied Add Drop Period
Author: Ceren Arkac / 28269
Date: 30.10.2021
**********************************/

#include <iostream>

#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct courseNode
{
  string courseCode, courseName;
  vector <int> studentsAttendingIDs;
  courseNode * next;  


  // constructor
  courseNode::courseNode(string courseCode_, string courseName_, courseNode * next_ = NULL)
	  : courseCode(courseCode_), courseName(courseName_), next(next_){};


};

void PrintList(courseNode * nodePtr) // as we did in week 3 lab 
{
	// input: the copy of the head of the linked list
	// output: prints the content of the LL until nodePtr points to NULL, which means the end of the LL.
	while ( nodePtr != NULL)
	{
		cout << nodePtr->courseCode << " " << nodePtr->courseName << ": ";
		for (int i = 0; i < nodePtr->studentsAttendingIDs.size(); i++)
		{
			cout << nodePtr->studentsAttendingIDs[i] << " ";
		}
		cout << endl;
		nodePtr = nodePtr->next; // as the content of a node is printed, nodePtr points to the following node.
	}
}

void PrintListForChoice4(courseNode * nodePtr)
{
	while ( nodePtr != NULL)
	{
		cout << nodePtr->courseCode << " " << nodePtr->courseName << ": ";
		for (int i = 0; i < nodePtr->studentsAttendingIDs.size(); i++)
		{
			cout << nodePtr->studentsAttendingIDs[i] << " ";
		}
		if (nodePtr->studentsAttendingIDs.size() < 3)
		{
			cout << "-> This course will be closed";
		}
		cout << endl;
		nodePtr = nodePtr->next;
	}
}


bool SearchList(courseNode *head, const string & searchedCourseName, const string & searchedCourseCode) // FROM CS204 LAB CODES
{
	// input: the copy of the head of the LL and the string whose existence is traced in LL
	// output: if searchedValue does exist in a node of the LL, return true
	courseNode * ptr = head; // I created another pointer to traverse LL but it was not mandotary.
	while (ptr != NULL)
	{
		if(ptr->courseName == searchedCourseName && ptr->courseCode == searchedCourseCode)
			return true;			
		ptr = ptr->next;
	} 
	return false; // if whole list was traversed but searchedCourseName and searchedCourseCode cannot be found, return false.
}

/*******************************************************************************************
This function was created to be used in such cases that 
the node with a certain CourseName should be found and 
done operations related to its content or content of its content etc.

Not all control paths of this function returns a value because, 
it will always be called when that a node with courseName is necessarily on that LL.
*********************************************************************************************/
courseNode * PtrPointingTheNodeWithCoursename(courseNode * ptr, const string & courseName, const string & courseCode){
	while (ptr != NULL) // ptr is initially points to the first node, to which also the head of the LL points.
	{
		if ((ptr->courseName == courseName) && (ptr->courseCode == courseCode)){ // if the node with courseName and courseCode is found, return the pointer.
			return ptr;
		}
		ptr = ptr->next;
	}


}
/******************************************************************
This function was created to be used when the existence of a stuID 
will be checked on a specific node (course).
ptr is the pointer which points to that courseNode.
*******************************************************************/
bool isAlreadyPresentStuID(courseNode * ptr, int stuID){
	for (int i = 0; i < ptr->studentsAttendingIDs.size(); i++)
	{
		if (ptr->studentsAttendingIDs[i] == stuID)
		{
			return true;
		}
	}
	return false;
}
/****************************************************************
This function is FROM CS201 VECTORS SLIDE. It searches the vector, 
finds the appropriate index to put stuID in (keeps order), and inserts stuID.
******************************************************************/
void insert(courseNode * ptr, int stuID){ 

    int vecSize = ptr->studentsAttendingIDs.size();  // initial size
    ptr->studentsAttendingIDs.push_back(stuID);   // increase size to make shifts
    int loc = vecSize;   
   
    while (loc > 0 && ptr->studentsAttendingIDs[loc-1] > stuID){ // search the appropriate location
		ptr->studentsAttendingIDs[loc] = ptr->studentsAttendingIDs[loc-1];
		loc--;        // shift right
    }
    ptr->studentsAttendingIDs[loc] = stuID; // edit approprite location with stuID 
}


/****************************************************
This function keeps the sorted LL and adds newCourseName to the appropriate position.
This function should return the head of the LL, 
because at the end of the function, head may change.

! This function was shown in lecture.
*****************************************************/
courseNode * AddInOrder(courseNode * head, string newCourseName, string courseCode, int stuID)
{
   courseNode *  ptr = head;   
   /* another pointer should be created to trace the LL. 
   Because, head will be returned at the end. It should be protected.*/

   if (head == NULL || newCourseName < head->courseName)  // first node is appropriate for newCourseName.     
   {
	   courseNode * temp = new courseNode(courseCode, newCourseName, head);  //node to be inserted 
	   temp->studentsAttendingIDs.push_back(stuID);
	   return temp; // head changes and temp will be the output of this function as the new head.
   }
   else // head will not change.
   {
	   /*at the end of this while loop, ptr points to the node 
       after which the newCourseName will be inserted then.*/
	   while (ptr->next != NULL && ptr->next->courseName < newCourseName)
	   {
		   ptr = ptr->next;
	   }

	   //insertion
	   courseNode * temp = new courseNode(courseCode, newCourseName, ptr->next);  //node to be inserted 
	   temp->studentsAttendingIDs.push_back(stuID);
	   ptr->next = temp;
   }

   return head;
}

courseNode * AddInOrderWithoutStuID(courseNode * head, string newCourseName, string courseCode)
// same as AddInOrder function, except excluding the addition of stuID while courseNode is being created.
{
   courseNode *  ptr = head;  

   if (head == NULL || newCourseName < head->courseName)        
    {   
		courseNode * temp = new courseNode(courseCode, newCourseName, head); 
		return temp;
    }
   else
   {
	   while (ptr->next != NULL && ptr->next->courseName < newCourseName)
	   {
		   ptr = ptr->next;
	   }
	   courseNode * temp = new courseNode(courseCode, newCourseName, ptr->next);  
	   ptr->next = temp;
   }

	return head;
}

void RemoveStuIDFromVector(courseNode * ptr, int idx){ // from CS201 Vectors slides
    // removes ptr->studentsAttendingIDs[idx] and keeps the vector sorted.
    // if the element which will be removed is the last index of vector, get out of the loop directly and .pop_back()
	// otherwise, shift all elements after ptr->studentsAttendingIDs[idx] to the previous of indexes, get out the loop,
   int lastIndex = ptr->studentsAttendingIDs.size()-1;
   for (int k = idx; k < lastIndex; k++){
	   ptr->studentsAttendingIDs[k] = ptr->studentsAttendingIDs[k+1]; 
   }
   // then .pop_back() the last index, which is empty.
   ptr->studentsAttendingIDs.pop_back(); 
}


void DeleteList (courseNode * head) // as we saw in CS 204 week 4 lecture (iterative version)
{
	// deletes the LL from the beginning.
  courseNode * temp;				
  while (head != NULL) 
  {				
      temp = head->next;			
      delete head;
      head = temp;
  }
}

int main() {
    string filename;
    cout << "Please enter file name: ";
    cin >> filename;
    ifstream in;
    in.open(filename.c_str());
	if (!in.fail())
	{
		/***** reading the txt file *****/
		cout << "Successfully opened file " << filename << endl;
		string line;
		courseNode * head = NULL; // to create a LL, firstly a pointer to point it should be created so that keep track of the LL which is in the heap.
		while (getline(in, line)) {
			if (line != "\r" && line != "") // to pass empty lines (something we used in CS201)
			{
				string courseCode, courseName;
				int stuID;
				istringstream ss(line);
				ss >> courseCode >> courseName >> stuID;

				// as the file is read, there are 3 possibilities for my LL.

				if (head == NULL)  // don't have even the LL. (no node) 
				{
					head = new courseNode(courseCode, courseName); // create a node with courseCode and courseName
					head->studentsAttendingIDs.push_back(stuID); // push the stuID to the vector inside the node.
					// now, head is pointing to the first node of the LL.
				}
				else if (!SearchList(head, courseName, courseCode)) 
				{
					// There is at least one node in the LL. But, no node with this courseName and courseCode. 
					// (SearchList returns false)
					head = AddInOrder(head, courseName, courseCode, stuID); // got the current head.
				}
				else // LL is not empty, also have a node with courseName, but that node doesn't involve this stuID.
				{  
					courseNode * ptr = head;
					ptr = PtrPointingTheNodeWithCoursename(head, courseName, courseCode); // finds the node with courseName. ptr points to it.
					insert(ptr, stuID);
				}
			}
		}
		cout << "The linked list is created." << endl;
		cout << "The initial list is: " << endl;
		PrintList(head);


		bool periodFinished = false;
		while (periodFinished == false) {
			int choice;
			cout << "Please select one of the choices: " << endl;
			cout << "1. Add to List" << endl;
			cout << "2. Drop from List" << endl;
			cout << "3. Display List" << endl;
			cout << "4. Finish Add/Drop and Exit" << endl;

			cin >> choice;

			if (choice == 1) {
				string inputStr;
				cout << "Give the student ID and the course names and course codes that he/she wants to add: ";
				cin.get();
				getline(cin, inputStr);
				string courseCode, courseName;
				istringstream ss(inputStr);
				int stuIDX;
				while (ss >> courseCode)
				{
					bool thisIsANewCourseNode = false;
					ss >> courseName;
					// first, need to check whether this course is present in LL or not
					bool doesAlreadyExistCourse = SearchList(head, courseName, courseCode);
					courseNode * ptr = head;
					if (doesAlreadyExistCourse){
						ptr = PtrPointingTheNodeWithCoursename(head, courseName, courseCode); // find the location of that node 
					}
					else
					{
						thisIsANewCourseNode = true;
						if (head == NULL)  // LL is empty.
						{
							head = new courseNode(courseCode, courseName);
						}
						else  // LL is not empty but a node with courseName and courseCode does not exist.
						{
							head = AddInOrderWithoutStuID(head, courseName, courseCode); // create new node with courseName and courseCode
						}
						cout << courseCode << " does not exist in the list of Courses. It is added up." << endl;
					}
					while (ss >> stuIDX)
					{
						if (thisIsANewCourseNode) // if this is a new course, stuID is also new.
						{
							courseNode * ptr2 = head;
							ptr2 = PtrPointingTheNodeWithCoursename(head, courseName, courseCode);
							insert(ptr2, stuIDX);
							cout << "Student with id " << stuIDX << " is enrolled to " << courseCode <<"." << endl;
						}
						else // if this course already exists, stuID may either exists or not.
						{
							bool AlreadyPresentStuID = isAlreadyPresentStuID(ptr, stuIDX);
							if (AlreadyPresentStuID) // stuID is already exist in this course
							{
								cout << "Student with id " << stuIDX << " already is enrolled to " << courseCode << ". No action taken." << endl;

							}
							else // new stuID for this course
							{
								insert(ptr, stuIDX);
								cout << "Student with id " << stuIDX << " is enrolled to " << courseCode << "." << endl;
							}
						}

					}
					ss.clear(); // remove the flag which will be caused by ss's reading string after integer
				}

			cout << endl;
			}		
			else if (choice == 2){
				cout << "Give the student ID and the course names and course codes that he/she wants to drop: ";
				string inputStr;
				cin.get();
				getline(cin, inputStr);
				string courseCode, courseName;
				istringstream ss(inputStr);
				int stuIDX;
				while (ss >> courseCode)
				{
					ss >> courseName;
					bool doesAlreadyExistCourse = SearchList(head, courseName, courseCode);
					while (ss >> stuIDX)
					{
						if (doesAlreadyExistCourse)
						{
							// find the location of this course in LL
							courseNode * ptr = head;
							ptr = PtrPointingTheNodeWithCoursename(head, courseName, courseCode);
							// inputted stuIDs can be either already exist or not.
							if (isAlreadyPresentStuID(ptr, stuIDX)){ 

								for (int i = 0; i < ptr->studentsAttendingIDs.size(); i++)
								{
									if (ptr->studentsAttendingIDs[i] == stuIDX)
									{
										RemoveStuIDFromVector(ptr, i);
										cout << "Student with id " << stuIDX << " has dropped " << courseCode <<"." << endl;
									}
								}
							}
							else // stuID is not present in the courseNode's vector.
							{
								cout << "Student with id " << stuIDX << " is not enrolled to " << courseCode << ", thus he can't drop that course." << endl;

							}
						}
						else
						{
							cout << "The " << courseCode <<" course is not in the list, thus student with id " << stuIDX << " can't be dropped" << endl;
						}

					}
					ss.clear();
				}
			cout << endl;
			}		

			else if (choice == 3){
				cout << "The current list of course and the students attending them: " << endl;
				PrintList(head);

			}
			else if (choice == 4){
				cout << "The add/drop period is finished. Printing the final list of courses and students attending them." << endl;
				cout << "NOTE: Courses with less than 3 students will be closed this semester." << endl;
				PrintListForChoice4(head);
				DeleteList(head); // return all the dynamically allocated memory to the heap
				periodFinished = true;
			}
		}
	}
	else
	{
		cout << "Wrong file name!" << endl;
	}
    
    return 0;

}

