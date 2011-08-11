#include <iostream>
int StrToInt(const std::string &str) {

	int length = str.length();
	int index = 0;
	int num = 0;
	bool isNeg = false;

	if (str[0] == '-')
	{
		isNeg = true;
		index = 1;
	}

	while (index < length)
		num = (num * 10) + ( str[index++] - '0' );

	if (isNeg)
		num *= -1;

	return num;
}

int main()
{
	std::string input = "-1435";
	int result = StrToInt(input);
	std::cout << "After conversion: " << result << std::endl;
	return 0;
}
