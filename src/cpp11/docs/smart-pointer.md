
## unique_ptr
    Allows exactly one owner of the underlying raw-pointer.

## shared_ptr
    reference-counted smart pointer. Use when we want to assign one raw-pointer
    to multiple owners.

    The raw-pointer is not deleted untial all shard_ptr owners go out of scope 
    or give up ownership.

    The size is two pointers, one for the object and one for the shared control 
    block that contains the reference count.


## weak_ptr
    Special smart pointer used with shared_ptr. 
    Provides access to an object that is owned by one or more shared_ptr instances,
    but does not participate in reference count.
    Use when you want to observe an object, but do not require it to remain alive.
    Required in some cases to break circular reference between shared_ptr.
