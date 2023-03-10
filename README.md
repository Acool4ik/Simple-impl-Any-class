## Simple impl of class Any (~70 lines)
### How to use
`just include file 'any.hpp' to your project`
### Main idea 
```c++
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
    T& value() { return value_; }
private:
    T value_;
};
struct Any
{
    template<typename T>
    Any(T const& value) : clone_(new ValueHolder<T>(value))
    {}
    template<typename T>
    T& cast()
    {
        if (dynamic_cast<ValueHolder<T>*>(clone_) == nullptr) 
            throw std::bad_cast();
        return static_cast<ValueHolder<T>*>(clone_)->value();
    }
private:
    IClonable * clone_ = nullptr;
};
```
