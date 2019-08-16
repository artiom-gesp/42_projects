import requests
from bs4 import BeautifulSoup
import pandas as pd
import progressbar


class ParseComments:
    """
    This class allows easy analysis of commentaries from opinion-assurance.fr
    """

    url = 'https://www.opinion-assurances.fr/assureur-ag2r-assurance-sante.html'
    root = 'https://www.opinion-assurances.fr'

    def __init__(self):
        """
        ParseComments constructor
        tries to establish connection to website
        """
        self.comment_urls = []

    def extract_links(self, url):
        """
        Locates "Lire la suite" links from website and extracts redirection urls
        The function visits every web page from this.url to last page recursively
        :return all urls in a list:
        """

        request = requests.get(url, timeout=5)

        if not request.ok:
            raise requests.ConnectionError('Could not establish connection to url')

        parsed_html = BeautifulSoup(request.text, "html.parser")
        links = parsed_html.find_all('a', attrs={"title": "Lire la suite"})

        self.comment_urls += [ParseComments.url + link['href'] for link in links]   # Add new urls to list

        next_url = parsed_html.find('a', attrs={"title": "Suivant >"})         # Find next url to visit
        if not next_url:
            return
        else:
            # next_url contains a relative path, thus we need to prepend the website root
            self.extract_links(ParseComments.root + next_url['href'])

    def extract_data(self, url):
        """
        Extract data from comment at url
        :return data as list:
        """
        request = requests.get(url, timeout=5)

        if not request.ok:
            raise requests.ConnectionError('Could not establish connection to url')

        parsed_html = BeautifulSoup(request.text, "html.parser")
        comments = self.extract_comment(parsed_html)
        grades = self.extract_grade(parsed_html)
        date = [parsed_html.find('span', attrs={"id": "MC_lbDate"}).contents[0].strip()]

        return comments + date + grades

    @staticmethod
    def extract_comment(parsed_html):
        """
        Extracts global comment, positive and negative feedbacks
        :param parsed_html: Beautiful Soup parsed html:
        :return list of commentaries:
        """
        try:    # if comment not found, replace it by '-'
            com_general = parsed_html.find('div', class_='well break').findChild('h2').contents[0].strip()
        except Exception:
            com_general = "-"
            pass

        try:
            com_plus = parsed_html.find('div', class_='plus').findChild('h3').contents[0].strip()
        except Exception:
            com_plus = "-"
            pass

        try:
            com_minus = parsed_html.find('div', class_='moins').findChild('h3').contents[0].strip()
        except Exception:
            com_minus = "-"
            pass

        return [com_general, com_plus, com_minus]

    @staticmethod
    def extract_grade(parsed_html):
        """
        Extracts grades from comment structure
        :param parsed_html: Beautiful Soup parsed html
        :return list of grades:
        """
        grade_wrap = parsed_html.find('div', attrs={"itemprop": "reviewRating"})
        unparsed_grades = grade_wrap.findChildren('div', class_='alf_label')
        parsed_grades = [grade.contents[0].strip() for grade in unparsed_grades]

        return parsed_grades

    def get_comments(self):
        """
        Visits every urls form self.comment_urls and store the collected data in DataFrame
        Creates an excel file containing all comments
        """

        data = []
        #  Initializing progress bar
        bar = progressbar.ProgressBar(maxval=len(self.comment_urls),
                                      widgets=[progressbar.Bar('=', '[', ']'), ' ', progressbar.Percentage()])
        bar.start()

        # Call extract_data for every urls in comment_urls
        for url, j in zip(self.comment_urls, range(len(self.comment_urls))):
            # for loop could be replaced by a list comprehension, but I really wanted to add a progress bar :)
            bar.update(j + 1)
            comment_info = self.extract_data(url)
            data.append(comment_info)

        bar.finish()
        data_frame = pd.DataFrame(data, columns=['com_general', 'com_moins',
                                                 'com_plus', 'date',
                                                 'niveaux des prix', 'qualite du service client',
                                                 'qualite des garanties', 'satisfaction'])

        data_frame = data_frame.assign(assureur='Ag2r La Mondiale').assign(produit='sante')
        data_frame.to_excel('data/data.xlsx')
