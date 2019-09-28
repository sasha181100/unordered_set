//
// Created by pokerstar on 14.09.19.
//

#ifndef UNORDERED_SET_UNORDERED_SET_H
#define UNORDERED_SET_UNORDERED_SET_H


#include <vector>
#include <iostream>
#include <math.h>

template<typename T>

struct unordered_set {

    
    struct iterator {
        iterator() = default;
        iterator(iterator const &other) = default;
        iterator& operator=(iterator const &other) = default;
        T const &operator *() const {
            return table[position_in_table][cell_number];
        }
        T const *operator ->() const {
            return &table[position_in_table][cell_number];
        }
        iterator &operator++() {
            cell_number++;
            if (cell_number == table[position_in_table].size()) {
                position_in_table++;
                while (table[position_in_table].size() == 0) {
                    position_in_table++;
                }
                cell_number = 0;
            }
            return *this;
        }
        iterator operator++(int) {
            iterator res = *this;
            ++(*this);
            return res;
        }
        friend bool operator==(iterator const &q, iterator const &w) {
            return (q.table.begin() == w.table.begin()) && (q.position_in_table == w.position_in_table) && (q.cell_number == w.cell_number);
        }
        friend bool operator!=(iterator const &q, iterator const &w) {
            return !(q == w);
        }
    private:
        std::vector<std::vector<T>> const &table;
        size_t position_in_table, cell_number;
        friend unordered_set;
        explicit iterator(std::vector<std::vector<T>> const &a, size_t const p, size_t const c) :table(a), position_in_table(p), cell_number(c) {

        }
    };
    //typedef iterator Iterator;
    typedef iterator const_iterator;

    size_t size() {
        return cnt;
    }


    const_iterator begin() const {
        for (size_t i = 0; i < hash_table.size(); i++) {
            if (hash_table.size() != 0) {
                return const_iterator(hash_table, i, 0);
            }
        }
    }

    const_iterator end() const {
        return const_iterator(hash_table, hash_table.size(), 0);
    }

    unordered_set() : hash_table(8), capacity(8), cnt(0) {

    }
    unordered_set(unordered_set const &other) = default;
    unordered_set &operator=(unordered_set const &other) = default;
    const_iterator find(T const&x) {
        size_t hash = count_hash(x);
        for (size_t i = 0; i < hash_table[hash].size(); i++) {
            if (hash_table[hash][i] == x) {
                return const_iterator(hash_table, hash, i);
            }
        }
        //Iterator it = end();
        return end();
    }
    std::pair<const_iterator, bool> insert(T const&x) {
        const_iterator it = find(x);
        const_iterator it1 = end();
        if (it != end()) {
            return {it, 0};
        }
        size_t hash = count_hash(x);
        hash_table[hash].push_back(x);

        if (hash_table[hash].size() > sqrt(capacity)) {
            enlargement();
        }
        return {const_iterator(hash_table, hash, hash_table[hash].size() - 1), 1};
    }
    void erase(T const &x) {
        const_iterator it = find(x);
        if (it != end()) {
            size_t hash = count_hash(x);
            for (size_t i = 0; i < hash_table[hash].size(); i++) {
                if (hash_table[hash][i] == x) {
                    hash_table[hash].erase(hash_table[hash].begin() + i);
                    return;
                }
            }
        }
    }
private:
    size_t capacity, cnt;
    std::vector<std::vector<T>> hash_table;
    size_t count_hash(T const&x) {
        return std::hash<T>()(x) % capacity;
    }
    void enlargement() {
        capacity *= 2;
        std::vector<std::vector<T>> tmp(capacity);
        for (const_iterator it = begin(); it != end(); it++) {
            size_t new_hash = count_hash(*it);
            tmp[new_hash].push_back(*it);
        }
        hash_table.swap(tmp);
    }

};


#endif //UNORDERED_SET_UNORDERED_SET_H
