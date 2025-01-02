#include <ranges>
#include <vector>
#include <concepts>
#include <iterator>
#include <utility>

// -----------------------------------------------------
// A simple concept to ensure we accept only range types
// -----------------------------------------------------
template <typename T>
concept RangeType = std::ranges::input_range<T>;

// -----------------------------------------------------
// Query class that wraps a range and allows chaining
// -----------------------------------------------------
template <RangeType R>
    requires RangeType<std::decay_t<R>>
class Query {
private:
    // We store the range "pipeline" in data_
    R data_;

public:
    // -------------------------------------------------
    // Constructor: takes ownership or reference of 'data'
    // -------------------------------------------------
    explicit Query(R data) : data_(std::move(data)) {}

    // -------------------------------------------------
    // where(...) – filters elements (like LINQ .Where)
    //
    // 'Pred' must be callable as: bool pred(range_reference_t<R>)
    // and must satisfy the 'std::predicate' concept
    // -------------------------------------------------
    template <typename Pred>
        requires std::predicate<Pred, std::ranges::range_reference_t<R>>
    auto where(Pred pred) {
        // Create a new filtered range using std::views::filter
        auto filteredRange = data_ | std::views::filter(pred);
        // Return a new Query with that filtered range
        return Query<decltype(filteredRange)>(std::move(filteredRange));
    }

    // -------------------------------------------------
    // select(...) – transforms elements (like LINQ .Select)
    //
    // 'Func' must be callable with the range's reference type
    // -------------------------------------------------
    template <typename Func>
        requires std::regular_invocable<Func, std::ranges::range_reference_t<R>>
    auto select(Func func) {
        // Transform the range using std::views::transform
        auto transformedRange = data_ | std::views::transform(func);
        // Return a new Query with that transformed range
        return Query<decltype(transformedRange)>(std::move(transformedRange));
    }

    // -------------------------------------------------
    // toVector() – materialize the lazy pipeline into a std::vector
    // -------------------------------------------------
    auto toVector() {
        // The final 'value type' might differ from the original input
        using OutT = std::ranges::range_value_t<decltype(data_)>;
        std::vector<OutT> result;
        // Note: you can also use std::ranges::to if your STL/library supports it
        for (auto&& elem : data_) {
            result.push_back(elem);
        }
        return result;
    }
};

// -----------------------------------------------------
// Helper function "from(...)" to create a Query easily
// -----------------------------------------------------
template <RangeType R>
    requires RangeType<std::decay_t<R>>
auto from(R&& range) {
    using Decayed = std::decay_t<R>;
    return Query<Decayed>(std::forward<R>(range));
}
