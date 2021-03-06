#include <cstdio>

const int lowStress[4] =  {10, 1, 10, 10};
const int highStress[4] = {5, 50,  5,  1};

int RevenueVals[4];
int TotalVals[4][4];

enum JobIndex { NONE, LOW, HIGH, SUB };

int max(int, int);
int max(int, int, int);

void B();

void C();

void D();

void Table();


int main(int argc, char const *argv[])
{
	printf("\n");

	B();

	C();

	D();

	return 0;
}


void B()
{

	printf("Part B:\n\n");

	RevenueVals[0] = max(lowStress[0], highStress[0]);
	RevenueVals[1] = max(RevenueVals[0], lowStress[1] + RevenueVals[0], highStress[1]);

	for(int i = 2; i < 4; i++)
	{
		RevenueVals[i] = max(RevenueVals[i-1], lowStress[i] + RevenueVals[i-1],
							highStress[i] + RevenueVals[i-2]);
	}

	printf("%-10s%5d%5d%5d%5d\n%-10s", "  i", 1, 2, 3, 4, "R(i)");

	for(int i = 0; i < 4; i++)
	{
		printf("%5d", RevenueVals[i]);
	}

	printf("\n\n");

}

void C()
{
	printf("Part C:\n\n");

	TotalVals[0][NONE] = 0;
	TotalVals[0][LOW] 	= lowStress[0];
	TotalVals[0][HIGH]	= highStress[0];
	TotalVals[0][SUB]	= max(TotalVals[0][LOW], TotalVals[0][HIGH]);

	TotalVals[1][NONE] = TotalVals[0][SUB];
	TotalVals[1][LOW] 	= lowStress[1] + TotalVals[0][SUB];
	TotalVals[1][HIGH]	= highStress[1];
	TotalVals[1][SUB]	= max(TotalVals[1][NONE], TotalVals[1][LOW],
								TotalVals[1][HIGH]);

	for(int i = 2; i < 4; i++)
	{
		TotalVals[i][NONE] = TotalVals[i-1][SUB];
		TotalVals[i][LOW] 	= lowStress[i] + TotalVals[i-1][SUB];
		TotalVals[i][HIGH]	= highStress[i] + TotalVals[i-2][SUB];
		TotalVals[i][SUB]	= max(TotalVals[i][NONE], TotalVals[i][LOW],
									TotalVals[i][HIGH]);
	}

	Table();

	printf("\n\n");
}

void D()
{
	printf("Part D:\n\n");

	int ChoosenJobs[4];

	for(int i = 3; i >= 0; i--)
	{
		int sub_solu = TotalVals[i][SUB];

		if(sub_solu == TotalVals[i][NONE])
			ChoosenJobs[i] = NONE;

		if(sub_solu == TotalVals[i][LOW])
			ChoosenJobs[i] = LOW;

		if(sub_solu == TotalVals[i][HIGH])
		{
			ChoosenJobs[i] = HIGH;
			ChoosenJobs[--i] = NONE;
		}
	}

	printf("%-10s%8d%8d%8d%8d\n%-10s", "   i", 1, 2, 3, 4, "  Jobs");

	for(int i = 0; i < 4; i++)
	{
		switch(ChoosenJobs[i])
		{
			case NONE:
				printf("%8s", "None"); 	break;
			case LOW:
				printf("%8s", "Low"); 	break;
			case HIGH:
				printf("%8s", "High"); 	break;
			default:
				printf("%8s", "ERR"); 	break;
		}
	}
	printf("\n\n  Total Revenue: %d", TotalVals[3][SUB]);
	printf("\n\n");
}

void Table()
{
	for(int r = 0; r <= 4; r++)
	{
		if(r == 0)
			printf("%-10s%5d%5d%5d%5d\n", "     i", 1, 2, 3, 4);
		else
		{
			for(int i = -1; i < 4; i++)
			{
				if(r == 1)
				{
					if( i < 0)
						printf("%-10s", "None[i]");
					else
						printf("%5d", TotalVals[i][NONE]);
				}
				else if(r == 2)
				{
					if( i < 0)
						printf("%-10s", " Low[i]");
					else
						printf("%5d", TotalVals[i][LOW]);
				}
				else if(r == 3)
				{
					if( i < 0)
						printf("%-10s", "High[i]");
					else
						printf("%5d", TotalVals[i][HIGH]);
				}
				else if(r == 4)
				{
					if( i < 0)
						printf("%-10s", "   R[i]");
					else
						printf("%5d", TotalVals[i][SUB]);;
				}

			}
			printf("\n");
		}

	}
}

int max(int x, int y)
{
	return (x > y) ? x : y;
}

int max(int x, int y, int z)
{
	return max(max(x, y), z);
}
