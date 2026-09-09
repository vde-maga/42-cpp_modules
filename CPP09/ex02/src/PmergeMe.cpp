#include "../include/PmergeMe.hpp"
#include <utility>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const std::vector<int>& input) 
    : vec_(input), deq_(input.begin(), input.end()),
      original_vec_(input), original_deq_(input.begin(), input.end()) {}

PmergeMe::PmergeMe(const PmergeMe& other) 
    : vec_(other.vec_), deq_(other.deq_),
      original_vec_(other.original_vec_), original_deq_(other.original_deq_) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        this->vec_ = other.vec_;
        this->deq_ = other.deq_;
        this->original_vec_ = other.original_vec_;
        this->original_deq_ = other.original_deq_;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

const char* PmergeMe::PmergeMeException::what() const throw() {
    return "Error";
}

double getTimeMicroseconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000.0 + tv.tv_usec);
}

void PmergeMe::run() {
    std::cout << "Before: ";
    for (size_t i = 0; i < original_vec_.size(); ++i) {
        if (i > 0) std::cout << " ";
        std::cout << original_vec_[i];
    }
    std::cout << std::endl;

    double start_vec = getTimeMicroseconds();
    sortVector();
    double end_vec = getTimeMicroseconds();
    double time_vec = end_vec - start_vec;

    std::cout << "After: ";
    for (size_t i = 0; i < vec_.size(); ++i) {
        if (i > 0) std::cout << " ";
        std::cout << vec_[i];
    }
    std::cout << std::endl;

    double start_deq = getTimeMicroseconds();
    sortDeque();
    double end_deq = getTimeMicroseconds();
    double time_deq = end_deq - start_deq;

    std::cout << "Time to process a range of " << vec_.size() 
              << " elements with std::vector : " << time_vec << " us" << std::endl;
    std::cout << "Time to process a range of " << deq_.size() 
              << " elements with std::deque : " << time_deq << " us" << std::endl;
}

// --- FORD-JOHNSON PARA STD::VECTOR ---
void PmergeMe::sortVectorRecursive(std::vector<int>& indices) {
    if (indices.size() < 2) return;
    
    std::vector<std::pair<int, int> > pairs;
    int last_idx = -1;
    
    for (size_t i = 0; i + 1 < indices.size(); i += 2) {
        int idx1 = indices[i];
        int idx2 = indices[i+1];
        if (original_vec_[idx1] > original_vec_[idx2]) {
            pairs.push_back(std::make_pair(idx1, idx2));
        } else {
            pairs.push_back(std::make_pair(idx2, idx1));
        }
    }
    if (indices.size() % 2 != 0) {
        last_idx = indices.back();
    }
    
    std::vector<int> main_indices;
    for (size_t i = 0; i < pairs.size(); ++i) {
        main_indices.push_back(pairs[i].first);
    }
    
    sortVectorRecursive(main_indices);
    
    std::vector<int> sorted_indices;
    std::vector<int> sub_map(original_vec_.size(), -1);
    
    for (size_t i = 0; i < pairs.size(); ++i) {
        sub_map[pairs[i].first] = pairs[i].second;
    }
    
    for (size_t i = 0; i < main_indices.size(); ++i) {
        sorted_indices.push_back(main_indices[i]);
    }
    
    if (!main_indices.empty()) {
        int first_sub = sub_map[main_indices[0]];
        sorted_indices.insert(sorted_indices.begin(), first_sub);
    }
    
    int jacobsthal_prev = 1;
    int jacobsthal_curr = 3;
    int num_subs = pairs.size();
    int inserted_subs = 1;
    
    while (inserted_subs < num_subs) {
        int group_end = jacobsthal_curr;
        if (group_end > num_subs) group_end = num_subs;
        
        for (int i = group_end - 1; i >= inserted_subs; --i) {
            int sub_idx = sub_map[main_indices[i]];
            int sub_val = original_vec_[sub_idx];
            
            int left = 0;
            int right = 0;
            for (size_t k = 0; k < sorted_indices.size(); ++k) {
                if (sorted_indices[k] == main_indices[i]) {
                    right = k;
                    break;
                }
            }
            
            while (left < right) {
                int mid = left + (right - left) / 2;
                if (original_vec_[sorted_indices[mid]] < sub_val) {
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }
            
            sorted_indices.insert(sorted_indices.begin() + left, sub_idx);
        }
        
        inserted_subs = group_end;
        int next_jacobsthal = jacobsthal_curr + 2 * jacobsthal_prev;
        jacobsthal_prev = jacobsthal_curr;
        jacobsthal_curr = next_jacobsthal;
    }
    
    if (last_idx != -1) {
        int last_val = original_vec_[last_idx];
        int left = 0;
        int right = sorted_indices.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (original_vec_[sorted_indices[mid]] < last_val) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        sorted_indices.insert(sorted_indices.begin() + left, last_idx);
    }
    
    indices = sorted_indices;
}

void PmergeMe::sortVector() {
    if (vec_.size() < 2) return;
    std::vector<int> indices(vec_.size());
    for (size_t i = 0; i < vec_.size(); ++i) indices[i] = i;
    
    sortVectorRecursive(indices);
    
    std::vector<int> sorted_vec(vec_.size());
    for (size_t i = 0; i < indices.size(); ++i) {
        sorted_vec[i] = original_vec_[indices[i]];
    }
    vec_ = sorted_vec;
}

// --- FORD-JOHNSON PARA STD::DEQUE ---
void PmergeMe::sortDequeRecursive(std::deque<int>& indices) {
    if (indices.size() < 2) return;
    
    std::deque<std::pair<int, int> > pairs;
    int last_idx = -1;
    
    for (size_t i = 0; i + 1 < indices.size(); i += 2) {
        int idx1 = indices[i];
        int idx2 = indices[i+1];
        if (original_deq_[idx1] > original_deq_[idx2]) {
            pairs.push_back(std::make_pair(idx1, idx2));
        } else {
            pairs.push_back(std::make_pair(idx2, idx1));
        }
    }
    if (indices.size() % 2 != 0) {
        last_idx = indices.back();
    }
    
    std::deque<int> main_indices;
    for (size_t i = 0; i < pairs.size(); ++i) {
        main_indices.push_back(pairs[i].first);
    }
    
    sortDequeRecursive(main_indices);
    
    std::deque<int> sorted_indices;
    std::deque<int> sub_map(original_deq_.size(), -1);
    
    for (size_t i = 0; i < pairs.size(); ++i) {
        sub_map[pairs[i].first] = pairs[i].second;
    }
    
    for (size_t i = 0; i < main_indices.size(); ++i) {
        sorted_indices.push_back(main_indices[i]);
    }
    
    if (!main_indices.empty()) {
        int first_sub = sub_map[main_indices[0]];
        sorted_indices.insert(sorted_indices.begin(), first_sub);
    }
    
    int jacobsthal_prev = 1;
    int jacobsthal_curr = 3;
    int num_subs = pairs.size();
    int inserted_subs = 1;
    
    while (inserted_subs < num_subs) {
        int group_end = jacobsthal_curr;
        if (group_end > num_subs) group_end = num_subs;
        
        for (int i = group_end - 1; i >= inserted_subs; --i) {
            int sub_idx = sub_map[main_indices[i]];
            int sub_val = original_deq_[sub_idx];
            
            int left = 0;
            int right = 0;
            for (size_t k = 0; k < sorted_indices.size(); ++k) {
                if (sorted_indices[k] == main_indices[i]) {
                    right = k;
                    break;
                }
            }
            
            while (left < right) {
                int mid = left + (right - left) / 2;
                if (original_deq_[sorted_indices[mid]] < sub_val) {
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }
            
            sorted_indices.insert(sorted_indices.begin() + left, sub_idx);
        }
        
        inserted_subs = group_end;
        int next_jacobsthal = jacobsthal_curr + 2 * jacobsthal_prev;
        jacobsthal_prev = jacobsthal_curr;
        jacobsthal_curr = next_jacobsthal;
    }
    
    if (last_idx != -1) {
        int last_val = original_deq_[last_idx];
        int left = 0;
        int right = sorted_indices.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (original_deq_[sorted_indices[mid]] < last_val) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        sorted_indices.insert(sorted_indices.begin() + left, last_idx);
    }
    
    indices = sorted_indices;
}

void PmergeMe::sortDeque() {
    if (deq_.size() < 2) return;
    std::deque<int> indices(deq_.size());
    for (size_t i = 0; i < deq_.size(); ++i) indices[i] = i;
    
    sortDequeRecursive(indices);
    
    std::deque<int> sorted_deq(deq_.size());
    for (size_t i = 0; i < indices.size(); ++i) {
        sorted_deq[i] = original_deq_[indices[i]];
    }
    deq_ = sorted_deq;
}
