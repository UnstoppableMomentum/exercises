#include <iostream>
#include <memory>
#include <string>

// The provided code demonstrates creating a std::unique_ptr with a custom deleter, using variadic templates and perfect forwarding to instantiate objects. This approach is a safer alternative to raw pointers, as it guarantees proper resource cleanup (RAII) and customization of the deletion process.
// The Investment class:
// This is a base class with a virtual destructor and a logging function.
// virtual ~Investment():
// The destructor is declared as virtual, which is crucial for proper cleanup in class hierarchies.
// When delete is called on a base-class pointer that points to a derived-class object,
// the virtual keyword ensures the correct derived-class destructor is called first, followed by the base-class destructor.
// __PRETTY_FUNCTION__: This is a non-standard, compiler-specific macro (common in GCC and Clang) that expands to a string containing the "pretty" signature of the current function. It is used here to log which function is being executed.
// The custom deleter delInvmt:
// auto delInvmt = [](Investment *pInvestment) { ... };:
// This defines a custom deleter as a stateless lambda function.
// pInvestment->Log();: The custom deleter calls the Log() function on the object before deleting it,
//  demonstrating a custom action to be performed during cleanup.
// delete pInvestment;: This line performs the actual deallocation of the memory managed by the unique_ptr.
// The makeInvestment function template:
//
// template<typename... Ts> ...: This is a variadic template, which allows the function to accept
// any number of arguments of different types.
// std::unique_ptr<Investment, decltype(delInvmt)>: This specifies the function's return type.
// It returns a std::unique_ptr that owns an Investment object and uses the custom delInvmt lambda as its deleter.
// Ts&&... params: This uses a forwarding reference (or universal reference)
// parameter pack to accept the function arguments.
// ...: Within the function body, the code would use perfect
// forwarding (std::forward<Ts>(params)...) to pass the arguments to the constructor of a derived Investment type.
// The function would then return a std::unique_ptr to the newly constructed object.
//  This ensures that the original argument's value category (lvalue or rvalue) is preserved, avoiding unnecessary copies.

class Investment
{
public:
    explicit Investment(const std::string &name)
        : name_(name)
    {
        std::cout << __PRETTY_FUNCTION__ << " name:" << name_ << std::endl;
    }
    virtual void Log()
    {
        std::cout << __PRETTY_FUNCTION__ << " name:" << name_ << std::endl;
    }
    virtual ~Investment()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    };
    std::string name_;
};

class Stock : public Investment
{
public:
    explicit Stock(const std::string &name, int stock)
        : Investment(name), stock_(stock)
    {
        std::cout << __PRETTY_FUNCTION__ << " name:" << name_ << " stock:" << stock_ << std::endl;
    }
    ~Stock()
    {
        std::cout << __PRETTY_FUNCTION__ << " name:" << name_ << " stock:" << stock_ << std::endl;
    }
    void Log() override
    {
        std::cout << __PRETTY_FUNCTION__ << " name:" << name_ << " stock:" << stock_ << std::endl;
    }

    int stock_;
};

// Example derived class: Bond
class Bond : public Investment
{
public:
    Bond(int value)
        : Investment("Bond"), value_(value)
    {
        std::cout << __PRETTY_FUNCTION__ << " with value: " << value_ << std::endl;
    }
    ~Bond() override
    {
        std::cout << __PRETTY_FUNCTION__ << " with value: " << value_ << std::endl;
    }
    void Log() override
    {
        std::cout << __PRETTY_FUNCTION__ << " name:" << name_ << " value_:" << value_ << std::endl;
    }

private:
    int value_;
};

// This defines a custom deleter as a stateless lambda function.
auto delInvmt = [](Investment *pInvestment) // user deleter
{
    std::cout << "-> Invoking custom deleter..." << std::endl;
    pInvestment->Log(); // Lambda
    delete pInvestment;
    std::cout << "-> Custom deleter finished." << std::endl;
};

template <typename InvestmentType, typename... Ts>
std::unique_ptr<Investment, decltype(delInvmt)> // return type
makeInvestment(Ts &&...params)
{
    std::unique_ptr<Investment, decltype(delInvmt)> // ptr to be
        pInv(nullptr, delInvmt);                    // returned

    // Process params via perfect forwarding to the derived class constructor
    InvestmentType *pInvestment = new InvestmentType(std::forward<Ts>(params)...);

    // Return the unique_ptr with the custom deleter
    return std::unique_ptr<Investment, decltype(delInvmt)>(pInvestment, delInvmt);

    // if (/* a Stock object should be created */)
    // {
    //     pInv.reset(new Stock(std::forward<Ts>(params)...));
    // }
    // else if (/* a Bond object should be created */)
    // {
    //     pInv.reset(new Bond(std::forward<Ts>(params)...));
    // }
    // else if (/* a RealEstate object should be created */)
    // {
    //     pInv.reset(new RealEstate(std::forward<Ts>(params)...));
    // }
    return pInv;
}

void Test2()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << "Creating a Stock investment:" << std::endl;
    auto myStock = makeInvestment<Stock>("Tesla", 1500);

    std::cout << "\nCreating a Bond investment:" << std::endl;
    auto myBond = makeInvestment<Bond>(5000);

    // std::unique_ptr<Stock, decltype(delInvmt)> vaz = std::make_unique("VAZ", 500000);

    // The code std::unique_ptr<Stock, decltype(delInvmt)> vaz = std::make_unique("VAZ", 500000);
    // is incorrect because std::make_unique does not support custom deleters.
    // It is designed to work exclusively with std::default_delete, which simply calls delete on the managed pointer.
    // The type of std::unique_ptr with a custom deleter,
    // like std::unique_ptr<Stock, decltype(delInvmt)>, is fundamentally different
    // from a standard std::unique_ptr<Stock>, and std::make_unique cannot produce a pointer of that specialized type.

    auto vaz = std::unique_ptr<Stock, decltype(delInvmt)>(new Stock("VAZ", 500000), delInvmt);
    vaz->Log();
}