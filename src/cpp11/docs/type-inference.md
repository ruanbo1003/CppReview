
## type inference
    Type reference refers to automatic deduction the data type of an expression in c++.   
    Before C++11, each data type needed to be explicitly declared at compile-time, limiting
    the values of an expression at runtime. But after the new version of C++, many keywords 
    are included which allows a programmer to leave the type deduction to the compiler itself.
    With type inference, we can speed less time having to write out things the compiler 
    alerady knows. This can save out time for develop.

### auto
    The auto keywork specifies that the type of the variable will be automaticlly 
    deducted from it's initializer. 
    In case of functions, if their return type is auto then it will be evaluated by 
    return type expression at runtime.

### decltype
    extract the type from the variable, the than we can use the type to declare a
    new variable.


### typeid
    https://en.cppreference.com/w/cpp/language/typeid
* typeid operator  
    queries information of a type.  
    typeid(x).name() returns the data type of x.
* Syntax  
  * typeid(type)
  * typeid(expression)


