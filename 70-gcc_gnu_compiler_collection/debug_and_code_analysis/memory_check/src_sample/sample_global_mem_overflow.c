int global_array[100] = {0};

int main(void) 
{
	int res = global_array[100];  // out of bounds
	return res;
}
