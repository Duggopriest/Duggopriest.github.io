#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <cstring>

using namespace std;

void	resetfiles()
{
	char	confirm;
	cout << "are you sure you want to reset all the files? Y/n\n";
	cin >> confirm;
	if (confirm != 'y' || confirm != 'Y')
		return ;

	int			i = 0;
	int			j = 0;
	string		array[50];
	string		line;

	ifstream	file;

	file.open("teams_copy.txt");
	while (getline(file, array[i++]));
	file.close();

	ofstream	out_file;
	out_file.open("teams.txt");
	while (j < i)
		out_file << array[j++] << endl;
	out_file.close();

	i = 0;
	j = 0;

	file.open("teams_copy.html");
	while (getline(file, array[i++]));
	file.close();

	out_file.open("teams.html");
	while (j < i)
		out_file << array[j++] << endl;
	out_file.close();
	cout << "teams.html has been reset" << endl;
	// ---------------------------------------------------------------

	i = 0;
	j = 0;

	int num = 0;
	string fname;
	string copy;
	while (++num <= 4)
	{
		fname.clear();
		copy.clear();
		fname.append("round");
		fname.append(to_string(num));
		copy.append(fname);
		copy.append("_copy");
		fname.append(".html");
		copy.append(".html");
		file.open(copy);
		i = 0;
		while (getline(file, array[i++]));
		file.close();

		out_file.open(fname);
		out_file.clear();
		j = 0;
		while (j < i)
			out_file << array[j++] << endl;
		out_file.close();
		cout << fname << " has been reset" << endl;
	}

	cout << "files have been reset" << endl;
	cout << "\npress enter to continue... " << endl;
	cin.ignore();
	cin.get();
}

void	next()
{
	int	i = 0;
	string	array[100];

	char	r;
	cout << "what round? 1-4\n";
	cin >> r;

	string roun;
	string quest;

	roun.append("round");
	quest.append("round");
	roun.push_back(r);
	quest.push_back(r);

	roun.append(".html");
	quest.append(".txt");


	string		line;
	ifstream	file;
	file.open(roun);
	while (getline(file, line))
		array[i++] = line;
	file.close();
	file.open(quest);
	bool	exists = false;
	int	j;
	while (getline(file, line))
	{
		j = 20;
		exists = false;
		while (j < i)
		{
			if (array[j].size() > 0)
				if (line.at(0) == array[j].at(0))
					exists = true;
			j++;
		}
		if (!exists)
			break ;
	}
	file.close();

	cout << "next question is " << line << endl;
	if (!exists)
	{
		ofstream out_file;
		out_file.open(roun, std::ios_base::app);
		out_file << "\n";
		out_file << line;
		out_file << "<p>----------------------------------------<p>";
		out_file.close();
	}
	cout << "next questing writtin" << endl;
}

void	team(void)
{
	bool		fail = true;

	int			i = 0;
	int			j = 0;
	int			off;

	int			score;
	int			current;

	string		team;
	string		array[50];

	string av;
	cout << "team Letters" << endl;
	cin >> av;

	string new_score;
	cout << "add score" << endl;
	cin >> new_score;

	team.append(&av.at(0));
	team.append(":");
	score = atoi(&new_score.at(0));


	string		line;
	ifstream	file;

	file.open("teams.txt");
	while (getline(file, line))
		array[i++] = line;
	file.close();



	ofstream	out_file;
	char *of;
	out_file.open("teams.txt");
	cout << "setting txt" << endl;
	while (j < i)
	{
		of = strstr(&array[j].at(0), &team.at(0));
		if (of)
		{
			current = atoi(of + team.size());
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
	{
		cout << "Could Not Find" << team << endl;
		cout << "\npress enter to continue... " << endl;
		cin.ignore();
		cin.get();
		return ;
	}

	file.open("teams.html");
	j = 0;
	i = 0;
	while (getline(file, line))
		array[i++] = line;
	file.close();

	team.clear();
	team.append(&av.at(0));
	team.append(":");

	cout << "setting html" << endl;
	out_file.open("teams.html");
	while (j < i)
	{
		of = strstr(&array[j].at(0), &team.at(0));
		if (of)
		{
			current = atoi(of + team.size());
			current += score;
			team.append(to_string(current));
			team.append("<p>\n");
			out_file << team;
			fail = false;
		}
		else
			out_file << array[j] << endl;
		j++;
	}
	out_file.close();

	if (fail)
	{
		cout << "Could Not Find on html" << team << endl;
		cout << "\npress enter to continue... " << endl;
		cin.ignore();
		cin.get();
		return ;
	}
}

int main(void)
{
	string input;
	while (1)
	{
		system("clear");
		cout << "commands are:\n	r = reset files\n	n = next question (will be prompt with what round)\n	t = add team score\n	  = exit\n";
		cin >> input;
		if (input.size() <= 0)
			return (0);
		else if (input.at(0) == 'r')
			resetfiles();
		else if (input.at(0) == 'n')
			next();
		else if (input.at(0) = 't')
			team();
	}
}