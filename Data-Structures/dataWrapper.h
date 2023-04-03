#ifndef DATAWRAPPER_H
#define DATAWRAPPER_H


#include<vector>
#include<unordered_map>
#include<string>

/**
 * @brief Made for storing data in an array(Handled by a vector) and a map together.
 * 
 */
template <typename U,typename T>
class DataStorage{
    private:
        /**
         * @brief The array the elements in this object are stored in
         */
        std::vector<T> storageArr;
        /**
         * @brief The map the elements in this object are stored in 
         */
        std::unordered_map<U,T> storageMap;
        /**
         * @brief How many elements are in this object
         */
        int size_;
    public:
        DataStorage(){size_ = 0;}
        /**
         * @brief Get an entry in this object from its key
         * 
         * @param key The key to get the entry for
         * @return The entry corresponding to the given key
         */
        T getEntry(U key) {return storageMap[key];}
        /**
         * @brief Get an entry stored at a specific index in thus object
         * 
         * @param index The index to get the entry at
         * @return The entry stored at the given index
         */
        T getEntryAtIndex(int index) {return  storageArr[index];}
        /**
         * @brief Add an entry to be stored in this object
         * 
         * @param key The key to associate with the entry
         * @param toAdd The entry to add
         * @return 0 on success or something else on failure
         */
        int add(U key, T toAdd){
            storageArr.push_back(toAdd);
            storageMap.insert({key,toAdd});
            size_  += 1;

            return 0;
        }
        /**
         * @brief Remove an entry  stored in this object
         * 
         * @param key The key associated with the entry to remove
         * @param toAdd The index of the entry to remove
         * @return 0 on success or something else on failure
         */
        int remove(U keyToRemove, int indexToRemove){
            if(size == 0){
                return 1;
            }
            storageArr.erase(indexToRemove);
            storageMap.erase(keyToRemove);

            size_ -= 1;
        }
        /**
         * @brief Gets an entry at a given index
         * 
         * @param n The index to get the entry for
         * @return The entry at the given index
         */
        T operator[](int n) {return storageArr[n];}
        /**
         * @brief Returns the number of entries stored in this object
         * 
         * @return The number of entries in this object
         */
        int size() {return size_;}

};

/*
template <typename U,typename T>
int DataStorage<U,T>::add(U key, T toAdd){
    storageArr.push_back(toAdd);
    storageMap.insert({key,toAdd});
    size_  += 1;

    return 0;
}
*/

#endif