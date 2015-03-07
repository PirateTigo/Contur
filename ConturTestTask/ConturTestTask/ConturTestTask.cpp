#include "stdafx.h"

using namespace std;
using namespace relationships;

int _tmain(int argc, _TCHAR* argv[])
{
	char *ptNames, *ptRelationships;	
	
	if (argc == 3)
	{ 
		ptNames = argv[1];
		ptRelationships = argv[2];
				
		cout << endl << "The obtained files: " << endl << endl <<
			"File with Names: " << ptNames << endl <<
			"File with Relationships: " << ptRelationships << endl;

		ifstream ifNames(ptNames);
		ifstream ifRelationships(ptRelationships);

		if (!ifNames) {
			cerr << endl << "Can't to open file of Names!" << endl;
			_getch();
		}
		else if (!ifRelationships) {
			cerr << endl << "Can't to open file of Relationships!" << endl;
			_getch();
		}
		else
		{
			cout << endl << "Loading database..." << endl;			
			RelationshipsDatabase rdbChilds(ifNames, ifRelationships);

			cout << endl << "Ok, database has loaded successfully, press any key to start...";
			_getch();
			
			char cSimb;
			
			bool bExit = false;
			while (!bExit)
			{	
				system("cls");
				cout << "Choose action:" << endl << endl << 
					"1 - show unloved childs" << endl <<
					"2 - show wretched childs (except nobody likes)" << endl <<
					"3 - show beloved childs" << endl <<
					"4 - show all childs (*bonus action)" << endl <<
					"5 - show all relations (*bonus action)" << endl <<
					"0 - exit" << endl << endl << "> ";				
				cSimb = _getch();
				cout << cSimb;

				switch (cSimb)
				{
				case '0':
					system("cls");
					bExit = true;
					break;
				case '1' :
					cout << endl << endl << "Result:" << endl << endl;
					rdbChilds.ShowUnloved(cout);
					cout << endl << "Press any key to continue...";
					_getch();
					break;
				case '2' :			
					cout << endl << endl << "Result:" << endl << endl;
					rdbChilds.ShowWretched(cout);
					cout << endl << "Press any key to continue...";
					_getch();
					break;
				case '3':			
					cout << endl << endl << "Result:" << endl << endl;
					rdbChilds.ShowBeloved(cout);
					cout << endl << "Press any key to continue...";
					_getch();
					break;
				case '4':
					cout << endl << endl << "Result:" << endl << endl;
					rdbChilds.ShowAll(cout);
					cout << endl << "Press any key to continue...";
					_getch();
					break;
				case '5':
					cout << endl << endl << "Result:" << endl << endl;
					rdbChilds.ShowRelations(cout);
					cout << endl << "Press any key to continue...";
					_getch();
					break;
				default:
					break;
				}
			}
		}

		ifRelationships.close();
		ifNames.close();		
	}
	else
		cerr << endl << "Incorrect input!" << endl << endl <<
			"Enter information in the following format:" << endl << endl <<
			"conturtesttask PATH/TO/NAMES PATH/TO/RELATIONSHIPS" << endl;	

	return 0;
}

