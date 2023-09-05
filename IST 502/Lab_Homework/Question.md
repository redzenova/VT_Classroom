# IST502 Data Structure

## Homework 1: Basic Recursion

1. Complete the code in ${\color{yellow}rec_temp.py}$ using recursion. Implement and test all the recursive functions in that file. No credits will be given to non-recursive solutions.

2. Write a recursive function:

```
def pascal(n);

that accepts an integer argument and prints out a Pascal triangle of depth n. For example, a call to:

pascal(3) will output:
1
1 1
1 2 1

pascal(5) will output:
1
1 1
1 2 1
1 3 3 1
1 4 6 4 1

```

Save your work in a file named ${\color{yellow}pascal.py}$

3. Write a recursive function ${\color{yellow}ruler.py}$ that draws the scale marks of a vertical ruler using dash “-” symbol. The middle mark should be the longest and mark the 1⁄2 way point, slightly shorter marks should mark the 1⁄4 way points, even slightly shorter marks should mark the 1⁄8 way points and so on. The function should take one argument: the height of the middle scale mark (i.e. the number of dashes). Example:

```
ruler(1)    ruler(2)    ruler(3)
  -           -           -
              --          --
              -           -
                          ---
                          -
                          --
                          -
```

## Submission

- Create a submission folder, StudentID_Firstname_HW1, where StudentID is your VISTEC
- ID and Firstname is your given name
- Put the files to submit, rec_temp.py, pascal.py, and ruler.py into this folder
- Write a report in a file called HW1_report.pdf to tell the instructor, for each problem:
  - Do you completely finish it or there are parts that you cannot finish because of bugs or other difficulties?
  - Approximately how long do you take to tackle it and what is the most difficult part of that problem?
  - Provide sample screenshot results for each problem.
- Include this HW1_report.pdf to the submission folder. ${\color{red}No report = no scores.}$
- Zip the submission folder and submit the zip file to the link posted on the class website on or before the due date
