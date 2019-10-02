from flask import Flask, request, render_template, current_app
# from flask import current_app as app
from flask import Blueprint
from flaskext.mysql import MySQL
from flask_bcrypt import Bcrypt
from ..app import app
import json

mysql = MySQL()
bcrypt = Bcrypt()
#
# mysql.init_app(app.app)
# connection = mysql.connect()
# cursor = connection.cursor()
with current_app.app_context():
    print('i')
test_api = Blueprint('test_api', __name__)
@test_api.route('/test')
def hello_world():
    return render_template('index.html')


@test_api.route('/users', methods=['GET'])
def get_user_list():
    if request.method == "GET":
        cursor.execute("SELECT `name` FROM `mailuser`")
        users = connection.cursor.fetchall()
        connection.cursor.close()
        return json.dumps(users)
