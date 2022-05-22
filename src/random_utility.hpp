#pragma once

#include <chrono>
#include <random>

namespace rng
{
	// ideally would use std::random_device{}(), but not portable
	// seeding with timestamp is good enough
	static std::default_random_engine engine(
		static_cast<unsigned int>(
			std::chrono::system_clock::now().time_since_epoch().count()
		)
	);

	// generate random number whithin interval [lo, hi] with uniform distribution
	static int rand_int(int lo, int hi)
	{
		std::uniform_int_distribution<> distribution(lo, hi);
		return distribution(engine);
	}

	// wrapper function to use static rng::engine for std::shuffle
	template <class T>
	static void shuffle(T beg, T end)
	{
		// static_assert(detail::is_iterator<T>::type);
		std::shuffle(beg, end, engine);
	}
}
