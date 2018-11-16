namespace GES {
	// also manually copy the dll
	_declspec(dllimport) void Print();
}

int main(int argc, char *argv[])
{
	GES::Print();
	return 0;
}
