from flask import Flask
from flaskext.mysql import MySQL

mysql = MySQL()


def create_app():
    """Construct the core application."""
    app = Flask( __name__ , instance_relative_config=False)
    #: Get MySQL config from config.py
    app.config.from_pyfile('config.py')
    mysql.init_app(app)
    with app.app_context():
        return app

