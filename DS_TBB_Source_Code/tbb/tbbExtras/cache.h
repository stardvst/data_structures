#pragma once

#include <map>
#include "tbb/tbb.h"

template<class Key, class Value, typename RwMutex>
class cache {
private:
    // Our cached data
    std::map<Key, Value> data;

    // The read-write mutex protecting the 
    // cached data
    RwMutex mutex;
public:
    void cache::update(const Key& key, Value value) {
        // since we're always updating, take a write lock
        RwMutex::scoped_lock lock(mutex, true);

        // we can now write to the data
        data[key] = value;
    }

    int cache::remove(const Key& key) {
        // since it might not exist, take a read lock
        RwMutex::scoped_lock lock(mutex, false);

        if (0 == data.count(key)) {
            // if the key exists, upgrade to a write lock
            lock.upgrade_to_writer();

            // so that we can safely update the cache
            return data.erase(key);
        }

        return 0;
    }

    bool cache::read(const Key& key, Value& value) {
        bool found = false;

        // we are never updating, so take a read lock
        RwMutex::scoped_lock lock(mutex, false);

        auto iter = data.find(key);
        if (iter != data.end()) {
            // if the value exists retrieve it
            value = iter->second;

            // and record we found it
            found = true;
        }

        //true if value is set, false otherwise
        return found;
    }
};