# multiple-reader-writer-system
A multiple reader writer system with synchronisation with threads using mutex
Each element of the queue is a struct with one of its members as pthread_mutex. So whenever the element is accessed by the writer that lock is acquired. Reader will have to acquire that lock to see it.
SO the queue can be read excluding the element that is being written to. There is a global writer lock that has to be acquired for any writer to write.
The program starts with the insertion of 5 elements in the queue. Followed by 4 read at kth postion thread generation. The index value is generated using random function. 4 print() threads are also created which print the entire queue.
1 thread of dequeue, 1 thread of insert, 1 thread of update is created.
Error handling is done by handling situations like reading while the queue is empty or dequeue when queue is empty. Error is also handled during dequeue operation when the queue has a single element.
