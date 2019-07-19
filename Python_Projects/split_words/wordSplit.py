import pandas as pd
import re


class WordSplit:
    def __init__(self, text_file):
        self.word_frame = self.init_frame(text_file)

    def init_frame(self, text_file):
        try:
            # verify that specified file is correct
            f = open(text_file, "r")
        except Exception:
            print("Invalid file")
            return -1
        regex = re.compile(r"[^a-z\-\'\s]|(?<=[a-b])-(?=(e))|(?<!e)'(?!([a-b]))", re.IGNORECASE)
        data = f.read().lower()
        data = re.sub(regex, " ", data)
        print(data)
        print('u\n')


