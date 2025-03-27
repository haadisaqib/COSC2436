# Convert the questions to the formatted text required for the online QTI converter

qti_text = """\
1. What is the base case in recursion?
a) The last function call
b) The first function call
*c) The condition where recursion stops
d) The recursive step

2. A linked list uses contiguous memory allocation like an array.
*a) True
b) False

3. What notation is used to describe the worst-case time complexity of an algorithm?
* Big O

4. The process where a recursive function continues to call itself indefinitely without reaching a base case is called a(n) __________ recursion.
* infinite

5. Which of the following operations is fastest on a linked list compared to an array?
a) Random access
*b) Insertion at the beginning
c) Deleting from the end
d) Searching for an element

6. Dynamic arrays automatically adjust their size when they become full.
*a) True
b) False

7. What is the time complexity of appending an element to a dynamic array in the average case?
* O(1)

8. In Big-O notation, the function O(n²) is called __________ time complexity.
* quadratic

9. When implementing a linked list in C++, what pointer is required to keep track of the beginning of the list?
a) prev
*b) head
c) tail
d) middle

10. Recursion can always be replaced by an iterative solution.
*a) True
b) False

11. What is the worst-case time complexity of searching for an element in an unsorted linked list?
* O(n)

12. If an algorithm has a time complexity of O(1), its runtime is __________ regardless of input size.
* constant

13. If a recursive function has multiple recursive calls within its body, it is called a:
a) Direct recursion
b) Tail recursion
*c) Binary recursion
d) Infinite recursion

14. A dynamic array must be resized manually by the programmer.
a) True
*b) False

15. What is the time complexity of inserting an element at the beginning of a singly linked list?
* O(1)

16. What happens when a dynamic array reaches its capacity?
a) It deletes the first element
*b) It creates a new array with double the size and copies the elements
c) It creates a linked list from the elements
d) It throws an error

17. The time complexity of inserting an element at the end of a dynamic array (without resizing) is O(1).
*a) True
b) False

18. What is the term for a function calling itself?
* Recursion

19. In a doubly linked list, each node contains a pointer to both the __________ and __________ nodes.
* previous, next

20. What is the time complexity of deleting an element from the middle of a singly linked list?
a) O(1)
b) O(log n)
*c) O(n)
d) O(n²)

21. The call stack is used to keep track of recursive function calls.
*a) True
b) False

22. What is the advantage of using a linked list over an array?
* Dynamic size

23. The worst-case time complexity of accessing an element in a dynamic array is __________.
* O(1)

24. If an algorithm has a time complexity of O(n log n), which of the following is a possible sorting algorithm?
a) Bubble Sort
*b) Merge Sort
c) Selection Sort
d) Insertion Sort

25. Inserting an element at the end of a singly linked list requires traversing the entire list if there's no tail pointer.
*a) True
b) False

26. What happens if recursion has no base case?
* Infinite recursion

27. The memory structure that recursion uses to store function calls is called the __________.
* call stack

28. Which of the following best describes the time complexity of a function that contains two nested loops, each iterating from 1 to n?
a) O(n)
b) O(n log n)
*c) O(n²)
d) O(2^n)

29. A linked list supports constant-time indexing like an array.
a) True
*b) False

30. What is the time complexity of reversing a singly linked list?
* O(n)

31. Which of the following is an example of a divide and conquer algorithm that heavily relies on recursion?
a) Bubble Sort
*b) Merge Sort
c) Linear Search
d) Selection Sort

32. The new keyword in C++ is used to allocate dynamic memory for a dynamic array.
*a) True
b) False

33. What is the worst-case time complexity of the recursive Fibonacci sequence implementation?
* O(2^n)

34. The process of breaking a problem into smaller subproblems and solving them recursively is called __________.
* divide and conquer

35. If a function has a recursive call as its last operation before returning, what type of recursion is it?
a) Direct recursion
*b) Tail recursion
c) Mutual recursion
d) Nested recursion

36. The time complexity of inserting an element at the front of a dynamic array is O(1).
a) True
*b) False

37. What is the time complexity of accessing an element in a singly linked list by index?
* O(n)

38. In recursion, each function call creates a new __________ in memory to store local variables and return addresses.
* stack frame

39. When doubling the size of a dynamic array, how many elements need to be copied in the worst-case scenario?
a) 1
*b) n
c) n/2
d) log n

40. A recursive function with multiple base cases is invalid in C++.
a) True
*b) False
"""

# Save formatted text to a file
qti_text_file_path = "./qti_temp.txt"
with open(qti_text_file_path, "w") as file:
    file.write(qti_text)

# Provide download link
qti_text_file_path
