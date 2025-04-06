/* ?? ??? ???? */
#include <iostream>
using namespace std;

int main()
{
	int x;

	while (1)
	{
		cout << "ÇëÊäÈëxµÄÖµ[0-100] : ";
		cin >> x; 
		if ((x < 0 || x > 100) || cin.good() != 1)
		{
			cin.clear();
			cin.ignore(100000, '\n');
		}

		else
			break;
	}

	cout << "cin.good()=" << cin.good() << " x=" << x << endl; 

	return 0;
}
