#include "../include/Identifier.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

/*
** Unknown type
*/
class D : public Base
{
};

/*
** Derived from A / B / C
*/
class AA : public A
{
};

class BB : public B
{
};

class CC : public C
{
};

int main()
{
	std::srand(std::time(NULL));

	/*
	** ============================================================
	** 1. BASIC TESTS
	** ============================================================
	*/
	std::cout << "\n========== 1. BASIC TESTS ==========" << std::endl;

	Base* a = new A();
	Base* b = new B();
	Base* c = new C();

	std::cout << "[Pointer]" << std::endl;
	identify(a);
	identify(b);
	identify(c);

	std::cout << "[Reference]" << std::endl;
	identify(*a);
	identify(*b);
	identify(*c);

	delete a;
	delete b;
	delete c;


	/*
	** ============================================================
	** 2. NULL / NULLPTR
	** ============================================================
	*/
	std::cout << "\n========== 2. NULL TESTS ==========" << std::endl;

	std::cout << "[NULL]" << std::endl;
	identify(NULL);

	std::cout << "[nullptr]" << std::endl;
	identify(NULL);


	/*
	** ============================================================
	** 3. UNKNOWN TYPE
	** ============================================================
	*/
	std::cout << "\n========== 3. UNKNOWN TYPE ==========" << std::endl;

	D d;

	std::cout << "[Pointer]" << std::endl;
	identify(&d);

	std::cout << "[Reference]" << std::endl;
	identify(d);


	/*
	** ============================================================
	** 4. DERIVED CLASSES
	** ============================================================
	*/
	std::cout << "\n========== 4. DERIVED CLASSES ==========" << std::endl;

	AA aa;
	BB bb;
	CC cc;

	std::cout << "[Pointer]" << std::endl;
	identify(&aa);
	identify(&bb);
	identify(&cc);

	std::cout << "[Reference]" << std::endl;
	identify(aa);
	identify(bb);
	identify(cc);


	/*
	** ============================================================
	** 5. POLYMORPHISM THROUGH Base*
	** ============================================================
	*/
	std::cout << "\n========== 5. POLYMORPHISM ==========" << std::endl;

	Base* p1 = new AA();
	Base* p2 = new BB();
	Base* p3 = new CC();

	identify(p1);
	identify(p2);
	identify(p3);

	delete p1;
	delete p2;
	delete p3;


	/*
	** ============================================================
	** 6. generate()
	** ============================================================
	*/
	std::cout << "\n========== 6. generate() ==========" << std::endl;

	for (int i = 0; i < 20; ++i)
	{
		Base* p = generate();

		if (p == NULL)
		{
			std::cerr << "ERROR: generate() returned NULL at iteration "
				<< i << std::endl;
			return 1;
		}

		std::cout << "[" << i << "] ";
		identify(p);

		delete p;
	}


	/*
	** ============================================================
	** 7. HEAVY STRESS TEST
	** ============================================================
	*/
	std::cout << "\n========== 7. STRESS TEST ==========" << std::endl;

	const int iterations = 10;

	for (int i = 0; i < iterations; ++i)
	{
		Base* p = generate();

		if (p == NULL)
		{
			std::cerr << "ERROR: generate() returned NULL at iteration "
				<< i << std::endl;
			return 1;
		}

		/*
		** Test pointer identification
		*/
		identify(p);

		/*
		** Test reference identification
		*/
		identify(*p);

		delete p;
	}

	std::cout << "\nStress test completed: "
		<< iterations << " iterations." << std::endl;


	/*
	** ============================================================
	** 8. REPEATED ALLOCATION / DELETION
	** ============================================================
	*/
	std::cout << "\n========== 8. ALLOCATION TEST ==========" << std::endl;

	for (int i = 0; i < 10; ++i)
	{
		Base* a = new A();
		Base* b = new B();
		Base* c = new C();

		if (a == NULL || b == NULL || c == NULL)
		{
			std::cerr << "ERROR: allocation returned NULL."
				<< std::endl;

			delete a;
			delete b;
			delete c;

			return 1;
		}

		identify(a);
		identify(b);
		identify(c);

		delete a;
		delete b;
		delete c;
	}

	std::cout << "Allocation/deletion test completed: "
		<< "10 rounds." << std::endl;


	/*
	** ============================================================
	** 9. FINAL TEST
	** ============================================================
	*/
	std::cout << "\n========== 9. FINAL TEST ==========" << std::endl;

	Base* final_a = new A();
	Base* final_b = new B();
	Base* final_c = new C();

	identify(final_a);
	identify(final_b);
	identify(final_c);

	delete final_a;
	delete final_b;
	delete final_c;

	std::cout << "\n========== ALL TESTS COMPLETED =========="
		<< std::endl;

	return 0;
}

