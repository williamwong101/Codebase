#include <utility>
#include <string>
#include <iostream>


template <typename T>
class ResourceManager{
public:
    ResourceManager(): resource_ptr_(new T()), id_(0), other_info_("") {};
    ~ResourceManager() {
        delete resource_ptr_;
        std::cout<< resource_ptr_ << " resource released\n";
    }
    ResourceManager(const ResourceManager& rhs) {
        resource_ptr_ = new T(*rhs.resource_ptr_);
        id_ = rhs.id_;
        other_info_ = rhs.other_info_;
    }
    ResourceManager(ResourceManager&& rhs) noexcept 
        : ResourceManager() {
        swap(*this, rhs);
        std::cout<< resource_ptr_ << " move ctor called\n";
    }
    ResourceManager& operator=(ResourceManager rhs) {
        swap(*this, rhs);
        return *this;
    }
    friend void swap(ResourceManager& lhs, ResourceManager& rhs) {
        std::swap(lhs.resource_ptr_, rhs.resource_ptr_);
        std::swap(lhs.id_, rhs.id_);
        std::swap(lhs.other_info_, rhs.other_info_);
    }

public:
    T* get(){
        return resource_ptr_;
    }

    void set_id(int id_in) {
        id_ = id_in;
    }

    void set_other_info(const std::string& other_info_in) {
        other_info_ = other_info_in;
    }

private:
    T* resource_ptr_;
    int id_;
    std::string other_info_;
};
