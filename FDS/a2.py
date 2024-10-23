def longest_word(sentence):
    words = sentence.split()
    longest = max(words, key=len)
    return longest

def character_frequency(sentence, char):
    count = 0
    for c in sentence:
        if c == char:
            count += 1
    return count

def is_palindrome(sentence):
    cleaned_sentence = ''.join(e for e in sentence if e.isalnum()).lower()
    return cleaned_sentence == cleaned_sentence[::-1]

def substring_index(sentence, substring):
    return sentence.find(substring)

def word_count(sentence):
    words = sentence.split()
    count_dict = {}
    for word in words:
        if word in count_dict:
            count_dict[word] += 1
        else:
            count_dict[word] = 1
    return count_dict

# Input string
sentence = "Python is fun and Python is powerful"
char = 'P'
substring = "fun"

# a) Display word with the longest length
print("Word with the longest length:", longest_word(sentence))

# b) Frequency of occurrence of a particular character
print(f"Frequency of character '{char}':", character_frequency(sentence, char))

# c) Check if the string is palindrome
print("Is the given string a palindrome?:", is_palindrome(sentence))

# d) Index of first appearance of a substring
print(f"First appearance of substring '{substring}':", substring_index(sentence, substring))

# e) Count occurrences of each word in the given string
print("Word count:", word_count(sentence))
