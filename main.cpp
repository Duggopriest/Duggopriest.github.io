#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int ac, char **av)
{
	bool		fail = true;

	int			i = 0;
	int			j = 0;

	int			score;
	int			current;

	string		team;
	string		array[20];

	team.append(av[1]);
	team.append(":");
	score = atoi(av[2]);


	string		line;
	ifstream	file;
	file.open("teams.txt");


	while (getline(file, line))
		array[i++] = line;
	file.close();
	

	ofstream	out_file;
	out_file.open("teams.txt");
	while (j < i)
	{
		cout << array[j] << endl;
		if (array[j].compare(0, team.size(), team) == 0)
		{
			current = atoi(&array[j].at(2));
			current += score;
			team.append(to_string(current));
			team.append("\n");
			out_file << team;
			fail = false;
		}
		else
			out_file << array[j] << endl;
		j++;
	}
	out_file.close();


	if (fail)
		cout << "Could Not Find" << team << endl;
}