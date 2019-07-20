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

        # [^a-z\-\'\s] : match all characters except latin letters, hyphens, apostrophe and whitespaces
        # (?<![a-z])- : match all hyphens not directly preceded by letters e.g. --test
        # -(?![a-z]) : match all hyphens not directly followed by letters e.g. this--
        # ('(?!([a-z])) : match all apostrophes not directly followed by a letter e.g. ' test
        regex = re.compile(r"[^a-z\-\'\s]|(?<!([a-z]))-|-(?!([a-z]))|'(?!([a-z]))", re.IGNORECASE)

        clean_text = re.sub(regex, " ", text)  # We remove everything superfluous e.g. dots, commas, etc..

        words = clean_text.split()

        # Creating DataFrame containing words from text_file and counting occurrences
        count_uniq = pd.DataFrame(words, columns=['words']).groupby('words').size().reset_index(name='count')

        return count_uniq

    def get_word_occurrence(self, n=10, pattern=None):
        """
            n (int) : number of words to display, sorted by occurrence
            pattern (string) : search for words given a specific pattern
        """
        if pattern:  # Search for given pattern in DataFrame
            select_by_pattern = self.word_frame[self.word_frame.words.str.contains(pattern)]
            n_first_occurrence = select_by_pattern.sort_values('count', ascending=False).head(n)
        else: # select n first
            n_first_occurrence = self.word_frame.sort_values('count', ascending=False).head(n)
        return n_first_occurrence.to_string(index=False)
