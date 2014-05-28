#include <iostream>
#include <sprout/algorithm.hpp>
#include <sprout/string.hpp>
#include <sprout/iterator.hpp>

template<typename T, typename U>
constexpr auto brainfuck(T const & code, U const & input)
{
	sprout::string<64> output;
	auto outit = output.begin();
	auto inputit = input.cbegin();
	auto codeit = code.cbegin();
	unsigned char memory[256] = {};
	auto ptr = sprout::begin(memory);
	
	while (codeit != code.cend())
	{
		switch (*codeit)
		{
		case '>':
			++ptr;
			break;

		case '<':
			--ptr;
			break;

		case '+':
			++(*ptr);
			break;

		case '-':
			--(*ptr);
			break;

		case '.':
			*(outit++) = *ptr;
			break;

		case ',':
			*ptr = *(inputit++);
			break;

		case '[':
			if (!*ptr)
			{
				codeit = sprout::find(codeit, code.cend(), ']');
			}
			break;

		case ']':
			if (*ptr)
			{
				codeit = sprout::find(sprout::reverse_iterator<decltype(codeit)>(codeit), code.crend(), '[').base() - 1;
			}
			break;
		}
		++codeit;
	}

	return output;
}

int main()
{
	constexpr auto s = brainfuck(sprout::to_string("+++++++++[>++++++++>+++++++++++>+++++<<<-]>.>++.+++++++..+++.>-.------------.<++++++++.--------.+++.------.--------.>+."), sprout::to_string(""));
	std::cout << s << std::endl;
	return 0;
}
/
