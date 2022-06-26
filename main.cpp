#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <cstring>

using namespace std;

// char	*ft_strstr(string *haystack, string *needle)
// {
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	j = 0;
// 	if (needle == NULL || needle[0] == '\0')
// 		return ((char *)haystack);
// 	while (haystack[i] != '\0')
// 	{
// 		if (haystack[i] == needle[j])
// 		{
// 			while (haystack[i + j] == needle[j] && i + j < n)
// 			{
// 				if (needle[j + 1] == '\0')
// 					return ((char *)haystack + i);
// 				j++;
// 			}
// 			j = 0;
// 		}	
// 		i++;
// 	}
// 	return (NULL);
// }

void	resetfiles()
{
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
		while (getline(file, array[i++]));
		file.close();

		out_file.open(fname);
		while (j < i)
			out_file << array[j++] << endl;
			out_file.close();
	}
	cout << "files have been reset" << endl;

	exit(0);
}

void	next(char r)
{
	int	i = 0;
	string	array[100];
	// string list;

	// list.append("round");
	// list.append(atoi(r));
	// list.append(".html");

	string roun;
	string quest;

	roun.append("round");
	quest.append("round");
	roun.push_back(r);
	quest.push_back(r);

	cout << "target is " << roun << endl;

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
		j = 0;
		exists = false;
		while (j < i)
		{
			if (strncmp(&line.at(0), &array[j].at(0), 5) == 0)
			{
				exists = true;
			}
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
	exit(0);
}

int main(int ac, char **av)
{
	if (ac <= 0)
		return (0);
	if (av[1][0] == 'r')
		resetfiles();
	else if (av[1][0] == 'n')
		next(av[1][1]);
	if (ac != 3)
	{
		cout << "plz include a team and score to add" << endl;
		return (0);
	}
	bool		fail = true;

	int			i = 0;
	int			j = 0;
	int			off;

	int			score;
	int			current;

	string		team;
	string		array[50];

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
		return (0);
	}

	file.open("teams.html");
	j = 0;
	i = 0;
	while (getline(file, line))
		array[i++] = line;
	file.close();

	team.clear();
	team.append(av[1]);
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
		cout << "Could Not Find" << team << endl;
		return (0);
	}

	if (fail)
	{
		cout << "Could Not Find on html" << team << endl;
		return (0);
	}
}