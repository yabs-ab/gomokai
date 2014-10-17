#ifndef TESTFRAMEWORK_HPP_
#define TESTFRAMEWORK_HPP_

#include <iostream>
#include <vector>
#include <string>

#define TF_TEST(NAME)							\
	struct TF_ ## NAME ## _test : public TestFramework::Test {	\
		using Test::Test;					\
		void run() const;					\
	} TF_ ## NAME ## _instance{#NAME};				\
									\
	void TF_ ## NAME ## _test::run() const

#define TF_ASSERT(COND)					\
	if (!(COND))					\
		throw TestFramework::Failure{#COND};

namespace TestFramework {

	class Test;
	std::vector<Test const*> g_tests;

	class Test {
	public:
		explicit Test(std::string const& name)
			: name{name}
		{
			g_tests.push_back(this);
		}

		virtual void run() const = 0;

		const std::string name;
	};

	struct Failure {
		explicit Failure(std::string const& message)
			: message(message)
		{
		}

		std::string const message;
	};

	int runTests()
	{
		int failureCount = 0;

		for (auto t : g_tests) {
			try {
				t->run();
			}
			catch (Failure& e) {
				std::cout << t->name << ": "
					  << e.message << std::endl;
				++failureCount;
			}
		}

		return failureCount;
	}

}

int main(int, char**)
{
	return TestFramework::runTests();
}

#endif // TESTFRAMEWORK_HPP_
