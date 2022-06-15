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

	cout << "files have been reset" << endl;
	exit(0);
}

int main(int ac, char **av)
{
	if (ac <= 0)
		return (0);
	if (av[1][0] == 'r')
		resetfiles();
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