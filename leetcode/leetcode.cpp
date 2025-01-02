// leetcode.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "cpplinq.cpp"

int main()
{
	struct MyData{
        int Member;
        std::string Name;
    };

    std::vector<MyData> items = {
        {1, "Alpha"},
        {6, "Bravo"},
        {10, "Charlie"},
        {4, "Delta"}
    };

    // Create a pipeline:
    // 1) where(x => x.Member > 5)
    // 2) select(x => x.Name)
    auto resultStrings = from(items)
        .where([](auto& x) { return x.Member > 5; })
        .select([](auto& x) { return x.Name; })
        .toVector();
    
    for (auto&& name : resultStrings) {
        std::cout << name << std::endl;
        // Output: "Bravo", "Charlie"
    }

	return 0;
}