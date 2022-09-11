/*
Task 3: Threads using FIFO files
Here, we use FIFO files to transfer the data from map3() to reduce3(). Specifically

•
The main program calls the filter function to clean the data. The function will return a global string array of valid
words. then main() creates both the map3() and reduce3() threads.

The map3() function creates 13 index arrays and threads, one for each word length, indexing into the main string
array. So if the global array contained [ “air”, ”airbag”, ”and” ] an index array had [1,3,…] then global[index[0]] is
‘air’, global[index[1]] = ‘and’.
Global[] is only ever read by map before the threads, and only thread3 reads index3[]. Since no word can be two
lengths at the same time, there will never be a conflict between threads .
Having created the mapping, map3() now creates 13 threads. Each thread uses the C function qsort() to perform
the same sort as before – on the third letter onwards – and when done, it creates 13 FIFO files opened for write
and each thread will then output words to their corresponding file.
In this case, the reduce3() function will wait, and then read those same 13 files, one line at a time in sort order.
a. Note that an efficient way to sort is to swap indexes or pointers in the compare instead of swapping
strings.
This should produce the same file as Task2 (and Task 1 – after sorting ) (ignoring chars 1,2).
This should produce the same file as Task2 (and Task 1 – after sorting. ) (ignoring chars 1,2).
At the end, each thread opens a FIFO file for writing, and dumps the global strings in sorted index order.
reduce3() should keep a count of words for each thread.
Meanwhile, reduce3() needs only to perform the reduction merge step. It waits for each map3() thread to signal
its completion. When all are done, reduce3() will open all 13 FIFO files for read, and perform the merge step as in
Task2,
a. Note that it may be necessary to set up all FIFO files before anything is read, as a FIFO open for read has to
be created before an open for write. Thus this ‘wiring’ can be done in main() before the threads are
created, and they inherit their files.
At the end, task3 should output the word counts for each word length. Also present these as a percentage (for
example 8% were words of length 10)

Report: Compare performance. Consider where the time was saved or lost.*/

void map3(){
    //Move to main()
    char** validWords = taskOneFilter("tester.txt", "CTask1.txt");
}

void reduce3(){

}