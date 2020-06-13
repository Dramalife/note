
int main(void) 
{
	//int *array = new int[100];
	int array[100];
	array[0] = 0;
	int res = array[100];  // out of bounds
	return res;
}
