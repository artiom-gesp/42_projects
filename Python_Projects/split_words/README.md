# Simple Python Class to count english words from text file

Python version : 3.7

Install required frameworks :
```pip install -r requirements.txt```

How to use : 
```
  from wordSplit import *
  
  split = WordSplit('/path/to/file.txt')
  print(split.get_word_occurrences(n=10, pattern='xxx'))
```

See main.py for more examples
