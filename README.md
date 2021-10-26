# static_vector
static_vector implementation in terms of std::vector. 
No need to implement each function again and again ;)

The usage is basically the same as with a regular std::vector
the main difference is that the memory is allocated on stack instead
of the heap. Additionally there is a limitation of the size of the vector.

example:

```cpp
nstl::vector<int, 10> v{1,2,3,4};
v.push_back(5);

for(int a: v){
   std::cout << a << ', ';
}
```

Result:
```
1, 2, 3, 4, 5
```
