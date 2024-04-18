#pragma once
#include <iostream>
#include <list>
#include <functional>
#include <vector>

template<typename Key, typename Value, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>>
class Unordered_map {

public:
    //only four opreation are allowed in the unordered_map
    //1. insert
    //2. find
    //3. erase
    //4. operator[]


    //making a vector of list of pairs , such that if there's a collision, we can store the key-value pair in the list chaining it .
    using Bucket = std::list<std::pair<Key, Value>>;
    using BucketList = std::vector<Bucket>;

    //constructor
    Unordered_map(size_t bucketCount = 10) : buckets(bucketCount) {}

    //inserting the key-value pair in the map
    void insert(const Key& key, const Value& value) {
        size_t index = hash(key) % buckets.size();
        for (auto& pair : buckets[index]) {
            if (keyEqual(pair.first, key)) {
                pair.second = value;
                return;
            }
        }
        buckets[index].emplace_back(key, value);
    }

    //overloading the operator[] to access the value of a key
    Value& operator[](const Key& key) {
        size_t index = hash(key) % buckets.size();
        for (auto& pair : buckets[index]) {
            if (keyEqual(pair.first, key)) {
                return pair.second;
            }
        }
        buckets[index].emplace_back(key, Value());
        return buckets[index].back().second;
    }

    //finding the key in the map
    bool find(const Key& key) const {
        size_t index = hash(key) % buckets.size();
        for (const auto& pair : buckets[index]) {
            if (keyEqual(pair.first, key)) {
                return true;
            }
        }
        return false;
    }

    //erasing the key-value pair from the map
    void erase(const Key& key) {
        size_t index = hash(key) % buckets.size();
        for (auto it = buckets[index].begin(); it != buckets[index].end(); ++it) {
            if (keyEqual(it->first, key)) {
                buckets[index].erase(it);
                return;
            }
        }
    }

    // function to get the first element of the map
    std::pair<Key, Value> begin() {
        for (auto& bucket : buckets) {
            if (!bucket.empty()) {
                return bucket.front();
            }
        }
        return std::pair<Key, Value>();
    }

    // implementation of first function of a map
    Key first() {
        for (auto& bucket : buckets) {
            if (!bucket.empty()) {
                return bucket.front().first;
            }
        }
        return Key();
    }
     
    // implementation of second function of a map
    Value second() {
        for (auto& bucket : buckets) {
            if (!bucket.empty()) {
                return bucket.front().second;
            }
        }
        return Value();
    }
    
    int mysize() const {
        int count = 0;
        //iterate through every bucket and count the number of elements in each bucket if it is not empty
        for (const auto& bucket : buckets) {
            if(!bucket.empty())
                count += 1;
        }
        return count;
    }

    


private:
    Hash hash;
    KeyEqual keyEqual;
    BucketList buckets;
};
