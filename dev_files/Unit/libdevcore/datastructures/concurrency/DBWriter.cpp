#include "DBWriter.h"

[[noreturn]] void commit(std::deque<rocksdb::WriteBatch> *deque, unit::BasicDB* dbProvider) {
    while (true) {
        if (!deque->empty()) {
            std::shared_ptr<rocksdb::WriteBatch> batchPtr = std::make_shared<rocksdb::WriteBatch>(deque->back());
            std::optional<std::exception> dbCode = dbProvider->commit(batchPtr);
            deque->pop_back();
            std::cout << "in-thread committing code: " << ((dbCode.has_value()) ? dbCode.value().what() : "0")  << std::endl;
        }
    }
}
void DBWriter::init() {
    dbThread = std::thread(commit, &(this->deque), &(this->dbProvider));
    dbThread.detach();
}

std::deque<rocksdb::WriteBatch> *DBWriter::getDeque() {
    return &(this->deque);
}
