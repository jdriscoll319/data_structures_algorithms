#include <iostream>
#include <vector>
#include <algorithm>


unsigned long int MaxPairwiseProduct(const std::vector<unsigned long int>& numbers) {
    unsigned long int max_product;
    int n = numbers.size();

    // for (int first = 0; first < n; ++first) {
    //     for (int second = first + 1; second < n; ++second) {
    //         max_product = std::max(max_product,
    //             numbers[first] * numbers[second]);
    //     }
    // }

    size_t index1 = 0;

    for(size_t i = 1; i < n; ++i)
    {
        index1 = (numbers[i] > numbers[index1]) ? i : index1;
    }
    
    size_t index2 = (index1 == 0) ? 1 : 0;
    
    for(size_t i = 1; i < n; ++i)
    {
        if ( numbers[i] > numbers[index2] && i != index1 )
            index2 = i;
    }

    // std::cout << index1 << " " << index2 << std::endl;

    max_product = numbers[index1] * numbers[index2];
    return max_product;
}

std::vector<unsigned long int> createBigVector()
{
    std::vector<unsigned long int> big_vec;
    for (unsigned long int i = 0; i <= 2 * std::pow(10, 5); ++i)
        big_vec.push_back(i);
    
    return big_vec;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<unsigned long int> numbers(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }

    // std::vector<unsigned long int> numbers = createBigVector();
    unsigned long int result = MaxPairwiseProduct(numbers);
    std::cout << result << "\n";
    return 0;
}
