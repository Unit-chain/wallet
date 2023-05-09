//
// Created by Kirill Zhukov on 29.10.2022.
//

#ifndef UNIT_DBWRITER_H
#define UNIT_DBWRITER_H
#include <utility>
#include "iostream"
#include "deque"
#include "thread"
#include "../../db/DB.h"
//#include "db/DB.h"

class DBWriter {
public:
    explicit DBWriter(const std::string& blockPath) : dbProvider(blockPath) {}
    static inline std::shared_ptr<rocksdb::WriteBatch> getBatch() { return unit::BasicDB::getBatch(); }
    inline unit::BasicDB *getProvider() { return &(this->dbProvider); };
    inline void join() { this->dbThread.join(); }
    void init();
    inline void emplaceBack(const rocksdb::WriteBatch &batch) {
        this->deque.emplace_back(batch);
    }

    [[nodiscard]] std::deque<rocksdb::WriteBatch> *getDeque();
protected:
    std::deque<rocksdb::WriteBatch> deque;
    unit::BasicDB dbProvider;
    std::thread dbThread;
};


#endif //UNIT_DBWRITER_H

