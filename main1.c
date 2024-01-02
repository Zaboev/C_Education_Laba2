#include <stdio.h>
#include <stdlib.h>

int main(int argi, char* argv[])
{
	if (argi < 3)
	{
		printf("Insufficient number of arguments");
		return 1;
	}
	if (argv[1][0] == '-')
	{
		if (argv[1][1] == 'l')
		{
			if (argi > 3)
			{
				printf("There is more than one line in the command line arguments, check that the entered data is correct\n");
			}
			printf("Number of characters per line %d\n", strlen(argv[2]));
		}
		else if (argv[1][1] == 'r')
		{
			if (argi > 3)
			{
				printf("There is more than one line in the command line arguments, check that the entered data is correct\n");
			}
			char* reverse_array = (char*)malloc(strlen(argv[2]) * sizeof(char) + 1);
			if (reverse_array == NULL)
			{
				printf("Failed to allocate memory");
				return 5;
			}
			int x = strlen(argv[2]) - 1;
			for (int i = 0; i < strlen(argv[2]); i++)
			{
				reverse_array[i] = argv[2][x];
				x--;
				printf("%c", reverse_array[i]);
			}
			free(reverse_array);
			reverse_array = NULL;
		}
		else if (argv[1][1] == 'u')
		{
			if (argi > 3)
			{
				printf("There is more than one line in the command line arguments, check that the entered data is correct\n");
			}
			char* new_array = (char*)malloc(strlen(argv[2]) * sizeof(char) + 1);
			if (new_array == NULL)
			{
				printf("Failed to allocate memory");
				return 5;
			}
			for (int i = 0; i < strlen(argv[2]); i++)
			{
				if (i % 2 == 1)
				{
					if (isalpha(argv[2][i]))
					{
						new_array[i] = (int)argv[2][i] - 32;
					}
					else
					{
						new_array[i] = argv[2][i];
					}
				}
				else
				{
					new_array[i] = argv[2][i];
				}
				printf("%c", argv[2][i]);
			}
			printf("\n");
			for (int i = 0; i < strlen(argv[2]); i++)
			{
				printf("%c", new_array[i]);
			}
			free(new_array);
			new_array = NULL;
		}
		else if (argv[1][1] == 'n')
		{
			if (argi > 3)
			{
				printf("There is more than one line in the command line arguments, check that the entered data is correct\n");
			}
			char* new_array = (char*)malloc(strlen(argv[2]) * sizeof(char) + 1);
			if (new_array == NULL)
			{
				printf("Failed to allocate memory");
				return 5;
			}
			char* alpha_array;
			char* digit_array;
			char* symbol_array;
			int count_a = 0, count_d = 0, count_s = 0, x = 0, y = 0, z = 0, Rx = 0, Ry = 0, Rz = 0;
			for (int i = 0; i < strlen(argv[2]); i++)
			{
				if (isalpha(argv[2][i]))
				{
					count_a++;
				}
				else if (isdigit(argv[2][i]))
				{
					count_d++;
				}
				else
				{
					count_s++;
				}
			}
			alpha_array = (char*)malloc(count_a * sizeof(char) + 1);
			if (alpha_array == NULL)
			{
				free(new_array);
				new_array = NULL;
				printf("Failed to allocate memory");
				return 51;
			}
			digit_array = (char*)malloc(count_d * sizeof(char) + 1);
			if (digit_array == NULL)
			{
				free(new_array);
				free(alpha_array);
				new_array = NULL;
				alpha_array = NULL;
				printf("Failed to allocate memory");
				return 52;
			}
			symbol_array = (char*)malloc(count_s * sizeof(char) + 1);
			if (symbol_array == NULL)
			{
				free(new_array);
				free(alpha_array);
				free(digit_array);
				new_array = NULL;
				alpha_array = NULL;
				digit_array = NULL;
				printf("Failed to allocate memory");
				return 53;
			}
			for (int i = 0; i < strlen(argv[2]); i++)
			{
				if (isdigit(argv[2][i]))
				{
					digit_array[x] = argv[2][i];
					x++;
				}
				else if (isalpha(argv[2][i]))
				{
					alpha_array[y] = argv[2][i];
					y++;
				}
				else
				{
					symbol_array[z] = argv[2][i];
					z++;
				}
			}
			for (int i = 0; i < strlen(argv[2]); i++)
			{
				if (Rx != x)
				{
					new_array[i] = digit_array[Rx];
					Rx++;
				}
				else if (Ry != y)
				{
					new_array[i] = alpha_array[Ry];
					Ry++;
				}
				else
				{
					new_array[i] = symbol_array[Rz];
					Rz++;
				}
				printf("%c", new_array[i]);
			}
			free(new_array);
			free(digit_array);
			free(alpha_array);
			free(symbol_array);
			new_array = NULL;
			digit_array = NULL;
			alpha_array = NULL;
			symbol_array = NULL;
		}
		else if (argv[1][1] == 'c')
		{
			if (argi < 4)
			{
				printf("Insufficient number of arguments");
				return 11;
			}
			for (int i = 0; i < strlen(argv[3]); i++)
			{
				if (!isdigit(argv[3][i]))
				{
					printf("Incorrect seed specified");
					return 4;
				}
			}
			int arr = strlen(argv) - 3;
			int seed = atoi(argv[3]);
			int i, j, k, x = 1;
			char* new_array = (char*)malloc(arr * sizeof(char));
			if (new_array == NULL)
			{
				printf("Failed to allocate memory");
				return 5;
			}
			int* index_array = (int*)malloc(arr * sizeof(int));
			if (index_array == NULL)
			{
				printf("Failed to allocate memory");
				free(new_array);
				new_array = NULL;
				return 51;
			}
			srand(seed);
			j = rand() % arr;
			index_array[0] = j;
			new_array[j] = argv[2];
			for (i = 4; i < strlen(argv); i++)
			{
				j = rand() % arr;
				for (k = 0; k < arr; k++)
				{
					if (index_array[k] == j)
					{
						j = rand() % arr;
						k = -1;
					}
				}
				new_array[j] = argv[i];
				if (x < arr)
				{
					index_array[x] = j;
					x++;
				}
				else
				{
					printf("Buffer overflow");
					return 6;
				}
			}
			for (int i = 0; i < arr; i++)
			{
				printf("%s", new_array[i]);
			}
			free(new_array);
			new_array = NULL;
			free(index_array);
			index_array = NULL;
		}
		else if (argv[1][1] == NULL)
		{
			printf("Missing flag");
			return 2;
		}
		else
		{
			printf("No flags available in registry");
			return 3;
		}
	}
	else
	{
		printf("Invalid character for flag input");
		return 501;
	}
	return 0;
}