#include "DB.h"

std::string unit::BasicDB::getWithIO(std::string &key) {
        rocksdb::DB *db;
        rocksdb::Status status = rocksdb::DB::OpenForReadOnly(this->options, this->path, &db);
        if (status.code() == rocksdb::Status::Code::kCorruption) throw unit::error::DBCorruption();
        if (status.code() == rocksdb::Status::Code::kIOError) throw unit::error::DBIOError();
        while (status.code() != rocksdb::Status::Code::kOk) {
            status = rocksdb::DB::OpenForReadOnly(this->options, this->path, &db);
            if (status.code() != rocksdb::Status::Code::kOk) std::this_thread::sleep_for(std::chrono::seconds(3));
        }
        std::string response;
        status = db->Get(rocksdb::ReadOptions(), rocksdb::Slice(key), &response);
        if (!status.ok()) {
            if (status.code() == rocksdb::Status::Code::kNotFound) {
                DB::close(&db);
                throw unit::error::DBNotFound();
            }
            while (status.code() != rocksdb::Status::Code::kOk) {
                status = db->Get(rocksdb::ReadOptions(), rocksdb::Slice(key), &response);
                std::this_thread::sleep_for(std::chrono::seconds ( 3));
            }
        }
        return {response};
    }
std::optional<std::exception> unit::BasicDB::commit(std::shared_ptr<rocksdb::WriteBatch> &batch) {
        rocksdb::DB *db;
        rocksdb::Status status = rocksdb::DB::Open(this->options, this->path, &db);
	std::cout << "path:" << this->path << ",status: " << status.ToString() << std::endl;
        if (status.code() == rocksdb::Status::Code::kCorruption) return {unit::error::DBCorruption()};
        if (status.code() == rocksdb::Status::Code::kIOError) return {unit::error::DBIOError()};
        while (status.code() != rocksdb::Status::Code::kOk) {
            status = rocksdb::DB::OpenForReadOnly(this->options, this->path, &db);
            if (status.code() != rocksdb::Status::Code::kOk) std::this_thread::sleep_for(std::chrono::seconds(3));

	std::cout << "passed second test" << std::endl; // cant go further
            return {unit::error::DBIOError()};
        }

	std::cout << "passed thirds test" << std::endl; // cant get here
        status = db->Write(this->writeOptions, batch.get());
        if (status.code() == rocksdb::Status::Code::kCorruption) return {unit::error::DBCorruption()};
        close(&db);
        return std::nullopt;
    }
std::shared_ptr<rocksdb::DB *> unit::BasicDB::newDB() {
        rocksdb::DB *db;
        rocksdb::Status status = rocksdb::DB::OpenForReadOnly(this->options, this->path, &db);
        if (status.code() == rocksdb::Status::Code::kCorruption) throw unit::error::DBCorruption();
        if (status.code() == rocksdb::Status::Code::kIOError) throw unit::error::DBIOError();
        while (status.code() != rocksdb::Status::Code::kOk) {
            status = rocksdb::DB::OpenForReadOnly(this->options, this->path, &db);
            if (status.code() != rocksdb::Status::Code::kOk) std::this_thread::sleep_for(std::chrono::seconds(3));
        }
        return std::make_shared<rocksdb::DB*>(db);
    }
std::tuple<std::vector<rocksdb::Status>, std::vector<std::string>> unit::BasicDB::multiGet(std::vector<std::string> *keys) {
        rocksdb::DB *db;
        rocksdb::Status status = rocksdb::DB::OpenForReadOnly(this->options, this->path, &db);
        if (status.code() == rocksdb::Status::Code::kCorruption) throw unit::error::DBCorruption();
        if (status.code() == rocksdb::Status::Code::kIOError) throw unit::error::DBIOError();
        std::vector<rocksdb::Slice> slices{};
        slices.reserve(keys->size());
        while (status.code() != rocksdb::Status::Code::kOk) {
            status = rocksdb::DB::OpenForReadOnly(this->options, this->path, &db);
            if (status.code() != rocksdb::Status::Code::kOk) {
                if (slices.empty()) for (auto &key : (*keys)) slices.emplace_back(rocksdb::Slice(key));
                else std::this_thread::sleep_for(std::chrono::seconds(3));
                std::this_thread::sleep_for(std::chrono::seconds(3));
            }
        }
        if (slices.empty()) for (const auto& key : *keys) slices.emplace_back(rocksdb::Slice(key));
        std::vector<std::string> response;
        std::vector<rocksdb::Status> statuses = db->MultiGet(rocksdb::ReadOptions(), slices, &response);
        return {std::make_tuple(std::move(statuses), std::move(response))};
    }
std::variant<std::string, std::exception> unit::BasicDB::seek(std::string &key) {
        return {};
    }

    std::variant<bool, std::exception> unit::BasicDB::has(std::string &key) {
        return {};
    }
    std::exception unit::BasicDB::put(std::string &key, std::string &value) {
        return {};
    }
    std::optional<std::exception> unit::BasicDB::deleteKey(std::string &key) {
        return std::exception();
    }
    std::variant<std::shared_ptr<rocksdb::Snapshot*>, std::exception> unit::BasicDB::getSnapshot(std::shared_ptr<rocksdb::DB*> &dbPtr) {
        return {};
    }

    std::variant<bool, std::exception> unit::BasicDB::has(std::shared_ptr<rocksdb::Snapshot *> &snapshot) {
        return {};
    }

    std::string unit::BasicDB::get(std::string &key, std::shared_ptr<rocksdb::DB *> &db) {
        std::string response;
        std::vector<rocksdb::ColumnFamilyHandle*> handles;
        rocksdb::Status status = (*db)->Get(rocksdb::ReadOptions(), rocksdb::Slice(key), &response);
        if (!status.ok()) {
            if (status.code() == rocksdb::Status::Code::kNotFound) {
                close(db);
                throw unit::error::DBNotFound();
            }
            while (status.code() != rocksdb::Status::Code::kOk) {
                status = (*db)->Get(rocksdb::ReadOptions(), rocksdb::Slice(key), &response);
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
        }
//        close(db);
        return {response};
    }

std::string unit::BasicDB::get(std::string &key) {
    rocksdb::DB *db;
    rocksdb::Status status = rocksdb::DB::OpenForReadOnly(this->options, this->path, &db);
    if (status.code() == rocksdb::Status::Code::kCorruption) throw unit::error::DBCorruption();
    while (status.code() != rocksdb::Status::Code::kOk) {
        status = rocksdb::DB::OpenForReadOnly(this->options, this->path, &db);
        if (status.code() != rocksdb::Status::Code::kOk) {
            std::cout << "rocksdb status is NOT OK, sleep while it become OK" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }
    std::string response;
    status = db->Get(rocksdb::ReadOptions(), rocksdb::Slice(key), &response);
    if (!status.ok()) {
        if (status.code() == rocksdb::Status::Code::kNotFound) {
            DB::close(&db);
            throw unit::error::DBNotFound();
        }
        while (status.code() != rocksdb::Status::Code::kOk) {
            status = db->Get(rocksdb::ReadOptions(), rocksdb::Slice(key), &response);
            std::this_thread::sleep_for(std::chrono::seconds ( 3));
        }
    }
    return {response};
}
