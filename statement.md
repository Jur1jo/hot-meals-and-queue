As you know, there is a big problem in the educational system of Chefland - impudent students who cuts in line in the cafeteria. Chef wants to assess the problem. He was able to understand how the queue works:

- Each student has value of discontent, which is initially equal to $0$;

- Initially the queue is empty;

- Students arrive at the queue one by one. Each student can either enter the queue in the end, or \textit{cut in line}, by which we mean stand in front of one or more students already in the queue;

- When someone cuts in line, the value of discontent of every student who ended up behind the new one is increased by $1$.

For example, if the students will enter the queue in the following order:

$[] \rightarrow [1] \rightarrow [1,2] \rightarrow [1,3,2] \rightarrow [1,3,2,4] \rightarrow [1,3,5,2,4]$

The discontent of the students in the queue will change as follows:

$[] \rightarrow [0] \rightarrow [0,0] \rightarrow [0,0,1] \rightarrow [0,0,1,0] \rightarrow [0,0,0,2,1]$

Note that the values of discontent are given in the same order as students are in the queue in the end of the process, not in order they were entering the queue.

Let's call the array of discontent values in the same order as students are in the queue in the end of the process \textit{the array of discontent}. Chef notices that if one knows the array of discontent then it is possible to find out how many students cut in line. And then Chef decides to make a competitive programming problem out of it!

You are given array $a_{1}, a_{2}, \ldots, a_{n}$. You have to process queries of two types:

- Find the number of students who cut in line if the array of discontent is $[a_{l}, a_{l+1}, \ldots, a_{r}]$ - that is, the subsegment of the array $a$;

- Add a number $w$ to $a_{l}, a_{l+1}, \ldots, a_{r}$ - that is, the subsegment of the array $a$.

You also have to find the number of students who cut in line using the initial $a$ as array of discontent.

###Input:

- The first line of input contains one integer $n$ ($3 \le n \le 5 \cdot 10^5$) - the size of the array $a$.

- The second line of input contains $n$ integers $a_1, a_2, \ldots, a_n$ separated by spaces - the array $a$ itself.

- The third line on input contains one integer $q$ ($0 \le q \le 5 \cdot 10^5$) - the number of queries.

- Then $q$ lines describing the queries follow.

- Each line starts with integer $t$ - the type of the query.

- If $t = 1$, then two more integers $l, r$ follow ($1 \le l \le r \le n$). For this query you have to print the number of students who cut in line if the array of discontent is $[a_{l}, a_{l+1}, \ldots, a_{r}]$.

- If $t = 2$, then three more numbers $l, r, w$ follow ($1 \le l \le r \le n$, $|w| < n$). For this query you have to add $w$ to numbers $a_{l}, a_{l+1}, \ldots, a_{r}$.

It is guaranteed that at any given time $|a_{i}| \le 10^9$, and also that every time you have to find the number of students who cut in line the corresponding array of discontent will be consistent, that is, there exists at least one process which results in the given array of discontent.

###Output:
In the first line of output you should print the answer for the initial array $a$. Then print answers for each query of type $1$ in the order they are given in input.

###Constraints 
- $3 \leq N \leq 5 \cdot 10^5$
- $0 \leq Q \leq 5 \cdot 10^5$
- $0 \leq a_i < n$
- $0 \leq |w_i| < n$

###Subtasks
- 10 points : $3 \leq N \leq 10^5$, $q = 0$
- 10 points : $3 \leq N \leq 10^5$, $q \leq 1000$
- 40 points : $3 \leq N \leq 10^5$, $q \leq  10^5$
- 40 points : $3 \leq N \leq 5 \cdot 10^5$, $q \leq 5\cdot 10^5$