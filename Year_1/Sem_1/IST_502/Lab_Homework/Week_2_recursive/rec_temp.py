# return the number of times c occurs in s, e.g.,
# number_c("a", "ababccaad") -> 4
def number_c(c, s):
        count = 0
        if len(s) == 0:
                return 0
        else:
                if s[0] == c:
                        count = 1
                return count + number_c(c, s[1:])


# return the number of chars in s that are not c, e.g.,
# number_not_c("a", "ababccaad") -> 5
def number_not_c(c, s):
        count = 0
        if len(s) == 0:
                return 0
        else:
                if s[0] != c:
                        count = 1
                return count + number_not_c(c, s[1:])


# return a copy of s but with all occurrences of c replaced by d, e.g.,
# replace("abeabe", 'e', '$') -> "ab$ab$"
# you are not allowed to use any Python libraries
def replace(s, c, d):
        if len(s) == 0:
                return ""
        else:
                if s[0] == c:
                        return d + replace(s[1:], c, d)
                else:
                        return s[0] + replace(s[1:], c, d)


# return a copy of s with char_to_remove removed, e.g.,
# remove_char("abeabe", 'e') -> "abab"
# you are not allowed to use any Python libraries
def remove_char(s, char_to_remove):
        if len(s) == 0:
                return ""
        else:
                if s[0] == char_to_remove:
                        return remove_char(s[1:], char_to_remove) # remove the char
                else:
                        return s[0] + remove_char(s[1:], char_to_remove) # keep the char


# return a copy of s with characters in reverse order, e.g.,
# reverse("abcdefg") = "gfedcab"
def reverse(s):
        if len(s) == 0:
                return ""
        else:
                return s[-1] + reverse(s[:-1]) 


# return a copy of s with adjacent duplicates removed, e.g.,
# rem1("abbcccdeaaa") -> "abcdea"
def rem1(s):
        if len(s) == 0:
                return ""
        else:
                if len(s) == 1:
                        return s[0]
                else:
                        if s[0] == s[1]:
                                return rem1(s[1:]) # remove duplicate
                        else:
                                return s[0] + rem1(s[1:]) # keep the char


# return the number of the digits in the decimal representation of n, e.g.,
# num_digits(0) -> 1, num_digits(34) -> 2, num_digits(1356) -> 4
# Precondition: n >= 0
def num_digits(n):
    if n < 10:
            return 1
    else:
            return 1 + num_digits(n // 10)

    # count = 0
    # if len(str(n)) == 0:
    #         return 0
    # else:
    #         count = 1
    #         return count + num_digits(str(n)[1:])
    


# return the sum of the digits in the decimal representation of n, e.g.,
# sum_digits(0) -> 0, sum_digits(3) -> 3, sum_digits(345) -> 12
# Precondition: n >= 0
def sum_digits(n):
    if n < 10:
            return n
    else:
            return n % 10 + sum_digits(n // 10)


    # sum = 0
    # if len(str(n)) == 0:
    #         return 0
    # else:
    #         sum = int(str(n)[0])  #Cast string to int 
    #         return sum + sum_digits(str(n)[1:])

print("number_c")
print(number_c('a', "aaabbbaccabda"))
print(number_c('b', "aaabbbaccabda"))
print(number_c('c', "aaabbbaccabda"))
print(number_c('d', "aaabbbaccabda"))
print()
print("number_not_c")
print(number_not_c('a', "aaabbbaccabda"))
print(number_not_c('b', "aaabbbaccabda"))
print(number_not_c('c', "aaabbbaccabda"))
print(number_not_c('d', "aaabbbaccabda"))
print()
print("replace")
print(replace("aaabbbaccabda", 'a', 'b'))
print(replace("aaabbbaccabda", 'b', 'c'))
print(replace("aaabbbaccabda", 'c', 'd'))
print(replace("aaabbbaccabda", 'd', 'a'))
print(replace("a", 'a', 'd'))
print(replace("a", 'd', 'a'))
print(replace("", 'a', 'a'))
print()
print("remove_char")
print(remove_char("eawabbcceccddeeaaeeeee", 'e'))
print(remove_char("acacacacac", 'a'))
print(remove_char("a", 'a'))
print(remove_char("", 'a'))
print()
print("reverse")
print(reverse("aaabbbaccabda"))
print(reverse("abbcccdeaaa"))
print(reverse("AMANAPLANACANALPANAMA"))
print()
print('rem1')
print(rem1("aaabbbaccabda"))
print(rem1("abbcccdeaaa"))
print(rem1("aaaaaaaaaaaaaaaaaaa"))
print(rem1("aabbbccccdddddeeeeeee"))
print(rem1("a"))
print(rem1(""))
print()
print("num_digits")
print(num_digits(123))
print(num_digits(123456))
print(num_digits(1))
print(num_digits(0))
print()
print("sum_digits")
print(sum_digits(123))
print(sum_digits(123456))
print(sum_digits(1))
print(sum_digits(0))