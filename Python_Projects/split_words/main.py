import importlib
import wordSplit as Ws
import pandas as pd
importlib.reload(Ws)    # useful if using PyCharm

if __name__ == "__main__":

    my_split = Ws.WordSplit('ressources/test.txt')

    with pd.option_context('display.max_rows', None, 'display.max_columns',
                           None):
        print(my_split.get_word_occurrence(n=10), '\n')  # 10 most frequent words with their number of occurrences
        print(my_split.get_word_occurrence(n=2, pattern='and\'s'), '\n')  # Search by pattern
        print(my_split.get_word_occurrence(n=10, pattern='that'), '\n')
        print(my_split.get_word_occurrence(n=10, pattern='-'), '\n')
        print(my_split.get_word_occurrence(n=10, pattern='thou'), '\n')
        print(my_split.get_word_occurrence(n=10, pattern='^i'))
        print(my_split.get_word_occurrence(n=50, pattern='\-'))






