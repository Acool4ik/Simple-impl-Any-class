#pragma once
#include <exception>

namespace any {

namespace {

struct IClonable
{
    virtual IClonable * clone() const = 0;
    virtual ~IClonable() = default;
};

template<typename T>
struct ValueHolder : IClonable
{
    ValueHolder(T const& value) : value_(value)
    {}
    IClonable * clone() const override
    {   return new ValueHolder<T>(value_);  }
    T const& value() const { return value_; }
    T& value() { return value_; }
private:
    T value_;
};

} // namespace

struct Any
{
    Any() = default;
    ~Any() { delete clone_; }

    template<typename T>
    Any(T const& value) : clone_(new ValueHolder<T>(value))
    {}
    Any(Any const& any) : clone_(any.clone_ ? any.clone_->clone() : nullptr)
    {}
    Any(Any && any)     { any.swap_(*this); }

    Any& operator=(Any const& any)
    {
        if (this != &any) Any(any).swap_(*this);
        return *this;
    }
    Any& operator=(Any && any)
    {
        if (this != &any) any.swap_(*this);
        return *this;
    }

    template<typename T>
    T const& cast() const
    {
        if (!check_cast_<T>()) throw std::bad_cast();
        return static_cast<ValueHolder<T>*>(clone_)->value();
    }
    template<typename T>
    T& cast()
    {
        if (!check_cast_<T>()) throw std::bad_cast();
        return static_cast<ValueHolder<T>*>(clone_)->value();
    }
private:
    template<typename T>
    bool check_cast_() const noexcept
    {   return dynamic_cast<ValueHolder<T>*>(clone_) != nullptr; }
    void swap_(Any& any) noexcept
    {   std::swap(any.clone_, clone_);  }
private:
    IClonable * clone_ = nullptr;
};

} // namespace any
