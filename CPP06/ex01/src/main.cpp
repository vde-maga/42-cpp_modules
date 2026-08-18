#include "../include/Data.hpp"
#include "../include/Serializer.hpp"
#include <iostream>
#include <stdint.h>

static void printResult(const std::string &test, bool passed)
{
	std::cout << (passed ? "[OK]   " : "[FAIL] ")
			  << test << std::endl;
}

int main()
{
	// ============================================================
	// TEST 1: Data por defeito
	// ============================================================
	{
		Data data;

		bool passed = (data.id == 0 && data.name == "");

		printResult("Data default constructor", passed);
	}

	// ============================================================
	// TEST 2: Data com valores
	// ============================================================
	{
		Data data(42, "Hello");

		bool passed = (data.id == 42 && data.name == "Hello");

		printResult("Data parameterized constructor", passed);
	}

	// ============================================================
	// TEST 3: serialize() não deve alterar o Data
	// ============================================================
	{
		Data data(42, "Alice");

		int originalId = data.id;
		std::string originalName = data.name;

		Serializer::serialize(&data);

		bool passed = (data.id == originalId
			&& data.name == originalName);

		printResult("serialize() does not modify Data", passed);
	}

	// ============================================================
	// TEST 4: serialize() + deserialize()
	// O ponteiro final deve ser exatamente o mesmo
	// ============================================================
	{
		Data data(42, "Alice");

		uintptr_t raw = Serializer::serialize(&data);
		Data *result = Serializer::deserialize(raw);

		bool passed = (result == &data);

		printResult("serialize -> deserialize preserves pointer", passed);
	}

	// ============================================================
	// TEST 5: Dados continuam iguais depois do round-trip
	// ============================================================
	{
		Data data(123, "Bob");

		uintptr_t raw = Serializer::serialize(&data);
		Data *result = Serializer::deserialize(raw);

		bool passed = (result != NULL
			&& result->id == 123
			&& result->name == "Bob");

		printResult("Data values survive round-trip", passed);
	}

	// ============================================================
	// TEST 6: Dois objetos diferentes devem produzir ponteiros
	// diferentes depois do deserialize
	// ============================================================
	{
		Data data1(1, "One");
		Data data2(2, "Two");

		uintptr_t raw1 = Serializer::serialize(&data1);
		uintptr_t raw2 = Serializer::serialize(&data2);

		Data *result1 = Serializer::deserialize(raw1);
		Data *result2 = Serializer::deserialize(raw2);

		bool passed = (result1 == &data1
			&& result2 == &data2
			&& result1 != result2);

		printResult("Different Data objects stay different", passed);
	}

	// ============================================================
	// TEST 7: Alterar através do ponteiro desserializado
	// deve alterar o objeto original
	// ============================================================
	{
		Data data(10, "Original");

		uintptr_t raw = Serializer::serialize(&data);
		Data *result = Serializer::deserialize(raw);

		result->id = 99;
		result->name = "Changed";

		bool passed = (data.id == 99
			&& data.name == "Changed");

		printResult("Deserialized pointer refers to original object", passed);
	}

	// ============================================================
	// TEST 8: nullptr
	// ============================================================
	{
		Data *ptr = NULL;

		uintptr_t raw = Serializer::serialize(ptr);
		Data *result = Serializer::deserialize(raw);

		bool passed = (raw == 0 && result == NULL);

		printResult("nullptr serialize/deserialize", passed);
	}

	// ============================================================
	// TEST 9: Vários objetos
	// ============================================================
	{
		Data a(1, "A");
		Data b(2, "B");
		Data c(3, "C");
		Data d(4, "D");

		uintptr_t rawA = Serializer::serialize(&a);
		uintptr_t rawB = Serializer::serialize(&b);
		uintptr_t rawC = Serializer::serialize(&c);
		uintptr_t rawD = Serializer::serialize(&d);

		Data *A = Serializer::deserialize(rawA);
		Data *B = Serializer::deserialize(rawB);
		Data *C = Serializer::deserialize(rawC);
		Data *D = Serializer::deserialize(rawD);

		bool passed = (A == &a
			&& B == &b
			&& C == &c
			&& D == &d);

		printResult("Multiple objects round-trip correctly", passed);
	}

	// ============================================================
	// TEST 10: Valores extremos no Data
	// ============================================================
	{
		Data data(-2147483647, "");

		uintptr_t raw = Serializer::serialize(&data);
		Data *result = Serializer::deserialize(raw);

		bool passed = (result == &data
			&& result->id == -2147483647
			&& result->name == "");

		printResult("Extreme/empty Data values", passed);
	}

	// ============================================================
	// TEST 11: String grande
	// ============================================================
	{
		std::string bigName(10000, 'X');
		Data data(999, bigName);

		uintptr_t raw = Serializer::serialize(&data);
		Data *result = Serializer::deserialize(raw);

		bool passed = (result == &data
			&& result->id == 999
			&& result->name == bigName);

		printResult("Large string survives round-trip", passed);
	}

	// ============================================================
	// TEST 12: serialize() duas vezes deve dar o mesmo raw
	// ============================================================
	{
		Data data(42, "Same");

		uintptr_t raw1 = Serializer::serialize(&data);
		uintptr_t raw2 = Serializer::serialize(&data);

		bool passed = (raw1 == raw2);

		printResult("Same pointer produces same raw value", passed);
	}

	return 0;
}
