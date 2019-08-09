import pandas as pd
import re


class WordSplit:

    """This class is for smart analysis and storage of english words from text file"""
    def __init__(self, text_file):
        """Constructor of WordSplit Class

            text_file (path-like-object) : Absolute or relative path to text_file
        """
        self.word_frame = self.init_frame(text_file)

    @ staticmethod
    def init_frame(text_file):
        """Function to verify if provided text file is correct and if it is store words in DataFrame

            text_file (path-like-object) : Absolute or relative path to text_file
        """
        try:
            f = open(text_file, "r")
        except Exception:
            print("Invalid file")
            exit(-1)

        text = f.read().lower()  # Read text_file into string

        regex = re.compile(r"[a-zA-Z\-']*[a-zA-Z][a-zA-Z\-']*")
        print(re.findall(regex, text))
        clean_text = re.sub(regex, " ", text)  # We remove everything superfluous e.g. dots, commas, etc..

        words = clean_text.split()

        frame = pd.DataFrame(words, columns=['words'])

        # frame = frame[frame.words.str.contains('[a-z]')]  # Drop rows not containing letters

        # Creating DataFrame containing words from text_file and counting occurrences
        count_uniq = frame.groupby('words').size().reset_index(name='count')

        return count_uniq

    def get_word_occurrence(self, n=10, pattern=None):
        """
            n (int) : number of words to display, sorted by occurrence
            pattern (string) : search for words given a specific pattern
        """
        if pattern:  # Search for given pattern in DataFrame
            select_by_pattern = self.word_frame[self.word_frame.words.str.contains(pattern)]
            n_first_occurrence = select_by_pattern.sort_values('count', ascending=False).head(n)
        else:  # select n first
            n_first_occurrence = self.word_frame.sort_values('count', ascending=False).head(n)
        return n_first_occurrence.to_string(index=False)
