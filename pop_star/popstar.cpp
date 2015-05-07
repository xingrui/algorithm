#include <iostream.h>
using namespace std;

#define color_type 7

char stars[10][10] = {
{1,3,5,2,1,2,3,2,6,0},
{5,3,2,3,1,0,2,4,6,1},
{4,1,5,6,1,3,0,1,3,1},
{6,4,3,1,1,5,6,0,1,1},
{4,3,1,2,6,6,6,3,1,4},
{1,2,5,2,6,2,6,2,1,2},
{0,4,2,2,4,0,2,1,1,5},
{2,1,5,6,1,2,3,0,1,3},
{2,1,5,3,2,0,2,1,4,6},
{1,6,3,1,6,2,1,0,1,2}
};
char new_stars[10][10];
bool clickBoard[10][10];
int every_color_count[100];
int star_color_type_count;

int  rename()
{
	int color_count = 0;
	bool found_at_last_col, found_at_this_col;

	for(int type = 0; type < color_type; type++)
	{
		found_at_last_col = false;
		for(int j = 0; j < 10; j++) 
		{
			found_at_this_col = false;
			for(int i = 0; i < 10; i++)
			{
				if(stars[i][j] == type)
				{
					if(found_at_this_col == false && found_at_last_col == false)
					{
						color_count++;
						every_color_count[color_count] = 0;
					}
					new_stars[i][j] = color_count;
					every_color_count[color_count]++; 
					found_at_this_col = true;
				}
			}
			if(found_at_this_col)
				found_at_last_col = true;
			else
				found_at_last_col = false;
		}
	}

	return color_count;
}

int clickOn(int i, int j, bool ifChange)
{
	char color = new_stars[i][j];
	clickBoard[i][j] = true;
	int count = 1;

	if(i > 0 && new_stars[i - 1][j] == color && !clickBoard[i - 1][j])
	{
		count += clickOn(i - 1, j, ifChange);
	}
	if(j > 0 && new_stars[i][j - 1] == color && !clickBoard[i][j - 1])
	{
		count += clickOn(i, j - 1, ifChange);
	}
	if(i < 9 && new_stars[i + 1][j] == color && !clickBoard[i + 1][j])
	{
		count += clickOn(i + 1, j, ifChange);
	}
	if(j < 9 && new_stars[i][j + 1] == color && !clickBoard[i][j + 1])
	{
		count += clickOn(i, j + 1, ifChange);
	}

	if(ifChange)
	{
		for(int k = i; k > 0; k--)
		{
			if(new_stars[k - 1][j] != -1)
			{
				char a = new_stars[k][j];
				new_stars[k][j] = new_stars[k - 1][j];
				new_stars[k - 1][j] = -1;
			}
		}
	}

	//cout << "click i-1 j : " << clickBoard[i - 1][j] << endl;
	//cout << "click i+1 j : " << clickBoard[i + 1][j] << endl;
	//cout << "click i j-1 : " << clickBoard[i][j - 1] << endl;
	//cout << "click i j+1 : " << clickBoard[i][j + 1] << endl;

	return count;
}

/*
 * return : 0 -> can not be clicked, other -> max evaluate at that situation.
*/
int getEvaluate(int i, int j)
{
	memset(clickBoard, false, sizeof(bool) * 100);
	int num = clickOn(i, j, false);
	int rnt = 0;
	char curr_color = new_stars[i][j];

	if(num < 2)
		return 0;
	
	rnt += num * num * 5;
	for(int k = 0; k < star_color_type_count; k++)
	{
		if(every_color_count[k] != curr_color)
		{
			rnt += every_color_count[k] * every_color_count[k] * 5;
		}
		else
		{
			rnt += (every_color_count[k] - num) * 
				(every_color_count[k] - num) * 5;
		}
	}

	return rnt;
}

int clickOnTheCurrMax()
{
	int clear_cnt = 0, max_i = 0, max_j = 0, max_eval = 0;
	int eval;
	
	for(int i = 0; i < 10; i++)
		for(int j = 0; j < 10; j++)
		{
			if(new_stars[i][j] != -1)
			{
				eval = getEvaluate(i, j);
				if(eval > max_eval)
				{
					max_i = i;
					max_j = j;
					max_eval = eval;
				}
			}
		}

	if(max_eval != 0)
	{
		clickOn(max_i, max_j, true);
		return 1;
	}

	return 0;
}

void printAll(char s[][10])
{
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			cout << (int)s[i][j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	printAll(stars);
	int star_color_type_count = rename();
	while(clickOnTheCurrMax())
	{
		cout << "*************************************" << endl;
		printAll(new_stars);
	}
	
	printAll(new_stars);

	return 0;
}
