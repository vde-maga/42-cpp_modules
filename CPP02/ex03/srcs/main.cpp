#include "Point.hpp"
#include "Colors.hpp"
#include <iostream>

// Função auxiliar para imprimir o resultado de forma visual e verificar a correção
static void printBspResult(Point const &a, Point const &b, Point const &c, Point const &point, bool expected, bool &all_passed)
{
	bool result = bsp(a, b, c, point);

	std::cout << "  Point(" << BRIGHT_YELLOW << point.getX() << RESET
			  << ", " << BRIGHT_YELLOW << point.getY() << RESET << ") "
			  << "inside Triangle{A(" << a.getX() << "," << a.getY()
			  << "), B(" << b.getX() << "," << b.getY()
			  << "), C(" << c.getX() << "," << c.getY() << ")} ? "
			  << BRIGHT_CYAN << (result ? "True" : "False") << RESET;

	if (result == expected)
		std::cout << GREEN << "  -> PASS" << RESET << std::endl;
	else
	{
		std::cout << RED << "  -> FAIL (Expected: " << (expected ? "True" : "False") << ")" << RESET << std::endl;
		all_passed = false;
	}
}

int main(void)
{
	bool all_passed = true;

	std::cout << CYAN << "================================================" << RESET << std::endl;
	std::cout << CYAN << "   UNIT TESTS: BSP (Binary Space Partitioning)" << RESET << std::endl;
	std::cout << CYAN << "================================================" << RESET << std::endl;

	// Test 1: Standard Right Triangle (First Quadrant)
	{
		std::cout << std::endl
				  << MAGENTA << "Test 1: Standard Right Triangle..." << RESET << std::endl;
		Point a(0.0f, 0.0f);
		Point b(10.0f, 0.0f);
		Point c(0.0f, 10.0f);

		printBspResult(a, b, c, Point(1.0f, 1.0f), true, all_passed);	 // Clearly Inside
		printBspResult(a, b, c, Point(10.0f, 10.0f), false, all_passed); // Clearly Outside
		printBspResult(a, b, c, Point(5.0f, 0.0f), false, all_passed);	 // On Edge (AB)
		printBspResult(a, b, c, Point(0.0f, 0.0f), false, all_passed);	 // On Vertex (A)
	}

	// Test 2: Triangle in Negative Quadrants
	{
		std::cout << std::endl
				  << MAGENTA << "Test 2: Negative Coordinates Triangle..." << RESET << std::endl;
		Point a(-5.0f, -5.0f);
		Point b(5.0f, -5.0f);
		Point c(0.0f, 5.0f);

		printBspResult(a, b, c, Point(0.0f, 0.0f), true, all_passed);	   // Inside
		printBspResult(a, b, c, Point(-10.0f, -10.0f), false, all_passed); // Outside
		printBspResult(a, b, c, Point(0.0f, -5.0f), false, all_passed);	   // On Edge (Base)
		printBspResult(a, b, c, Point(-5.0f, -5.0f), false, all_passed);   // On Vertex (A)
	}

	// Test 3: Epsilon / Near Edge test
	{
		std::cout << std::endl
				  << MAGENTA << "Test 3: Epsilon / Near Edge Precision..." << RESET << std::endl;
		Point a(0.0f, 0.0f);
		Point b(10.0f, 0.0f);
		Point c(0.0f, 10.0f);

		// A hipotenusa é a linha x + y = 10. O ponto (5, 5) está exatamente NELA.
		printBspResult(a, b, c, Point(5.0f, 5.0f), false, all_passed);	// Exactly on Hypotenuse
		printBspResult(a, b, c, Point(4.99f, 5.0f), true, all_passed);	// Slightly inside
		printBspResult(a, b, c, Point(5.01f, 5.0f), false, all_passed); // Slightly outside
	}

	// Test 4: Degenerate Triangle (Collinear points)
	{
		std::cout << std::endl
				  << MAGENTA << "Test 4: Degenerate Triangle (Collinear points)..." << RESET << std::endl;
		Point a(0.0f, 0.0f);
		Point b(5.0f, 5.0f);
		Point c(10.0f, 10.0f); // Points form a line, not a triangle

		// Any point should logically be false because it has no area.
		// Mathematically, signs will be 0 or inconsistent.
		printBspResult(a, b, c, Point(2.0f, 2.0f), false, all_passed);
		printBspResult(a, b, c, Point(20.0f, 20.0f), false, all_passed);
	}

	// Test 5: Subject Constructor Validation (Float vs Fixed)
	{
		std::cout << std::endl
				  << MAGENTA << "Test 5: Subject Float Constructor Validation..." << RESET << std::endl;
		// Ensuring Point(const float, const float) works flawlessly with fractional values
		Point a(0.5f, 0.5f);
		Point b(10.25f, 0.5f);
		Point c(0.5f, 10.25f);

		printBspResult(a, b, c, Point(1.1f, 1.1f), true, all_passed);  // Inside
		printBspResult(a, b, c, Point(0.5f, 0.5f), false, all_passed); // Vertex
	}

	std::cout << std::endl
			  << BRIGHT_CYAN << "================================================" << RESET << std::endl;

	if (all_passed)
		std::cout << BRIGHT_GREEN << "   All BSP tests passed!" << RESET << std::endl;
	else
		std::cout << BRIGHT_RED << "   Some BSP tests failed." << RESET << std::endl;
	std::cout << BRIGHT_CYAN << "================================================" << RESET << std::endl;

	return (all_passed ? 0 : 1);
}