import parseComments as Parse

if __name__ == "__main__":
    parser = Parse.ParseComments()
    parser.extract_links(parser.url)    # Find comments' urls
    parser.get_comments()   # Collect data from urls
