
## memory model
### reference material
* https://stackoverflow.com/questions/6319146/c11-introduced-a-standardized-memory-model-what-does-it-mean-and-how-is-it-g
* https://devtut.github.io/cpp/c-11-memory-model.html#need-for-memory-model
* https://www.theregister.com/2011/06/11/herb_sutter_next_c_plus_plus?page=2
* https://kernelgo.org/memory-model.html  a blog write in Chinese

### stl memory orders  
  https://en.cppreference.com/w/cpp/atomic/memory_order
  
* std::memory_order_relaxed
* std::memory_order_consume
* std::memory_order_acquire
* std::memory_order_release
  - not use alone, used with memory_order_consume, memory_order_acquire
* std::memory_order_acq_rel
  - combine of memory_order_acquire and memory_order_release
  - read-modify-write operation
* std::memory_order_cst

